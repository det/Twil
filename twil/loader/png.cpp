#include "png.hpp"

#include "data/scope_guard.hpp"

#include <fstream>
#include <stdexcept>

#include <png.h>

namespace {

// Custom error handler to avoid libpng's longjmp error handling

void ThrowPngError(png_structp png_pointer, png_const_charp error_message)
{
	throw std::runtime_error{error_message};
}

// Custom read function to read via std::ifstream instead of FILE *

void ReadPngData(png_structp png_pointer, png_bytep data, png_size_t length)
{
	auto & file = *static_cast<std::ifstream *>(png_get_io_ptr(png_pointer));
	auto size = static_cast<std::streamsize>(length);
	file.read(reinterpret_cast<char *>(data), size);
	if (file.fail()) throw std::runtime_error{"Png read error"};
	if (file.gcount() != size) throw std::runtime_error{"Png read error"};
}

}

namespace twil {
namespace loader {

Png::Png(char const * path)
:
	bytes_{nullptr}
{
	std::ifstream file;
	file.open(path, std::ios::in);
	if (!file.is_open()) throw std::runtime_error{"Unable to open png"};

	png_byte magic[8];
	file.read(reinterpret_cast<char *>(magic), sizeof(magic));
	if (file.fail()) throw std::runtime_error{"Png read error"};
	if (file.gcount() != sizeof(magic)) throw std::runtime_error{"Png read error"};
	if (!png_check_sig(magic, sizeof(magic))) throw std::runtime_error{"PNG load error"};

	auto png = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
	if (png == nullptr) throw std::runtime_error{"PNG load error"};
	auto info = png_create_info_struct(png);
	if (info == nullptr)
	{
		png_destroy_read_struct(&png, nullptr, nullptr);
		throw std::runtime_error{"PNG load error"};
	}
	auto && png_guard = data::MakeScopeGuard([&] { png_destroy_read_struct(&png, &info, nullptr); });

	png_set_read_fn(png, &file, ReadPngData);
	png_set_error_fn(png, nullptr, ThrowPngError, nullptr);

	// Tell libpng that we have already read the magic number
	png_set_sig_bytes(png, sizeof(magic));

	// Ensure format is RGBA8
	png_read_info(png, info);
	int bit_depth = png_get_bit_depth(png, info);
	int color_type = png_get_color_type(png, info);

	switch (color_type) {
	case PNG_COLOR_TYPE_PALETTE:
	{
		png_set_palette_to_rgb(png);
		png_set_add_alpha(png, 255, PNG_FILLER_AFTER);
	} break;
	case PNG_COLOR_TYPE_GRAY:
	{
		if (bit_depth < 8) png_set_expand_gray_1_2_4_to_8(png);
		png_set_gray_to_rgb(png);
		png_set_add_alpha(png, 255, PNG_FILLER_AFTER);
	} break;
	case PNG_COLOR_TYPE_GRAY_ALPHA:
	{
		png_set_gray_to_rgb(png);
	} break;
	case PNG_COLOR_TYPE_RGB:
	{
		png_set_add_alpha(png, 255, PNG_FILLER_AFTER);
	} break;
	}

	if (png_get_valid(png, info, PNG_INFO_tRNS))
	{
		png_set_tRNS_to_alpha(png);
	}

	if (bit_depth == 16) png_set_strip_16(png);
	else if (bit_depth < 8) png_set_packing(png);

	// Assume sRGB approximated input, output linear colorspace
	png_set_gamma(png, 1, .45455);

	// Update info structure to apply transformations
	png_read_update_info(png, info);

	// Retrieve updated information
	png_uint_32 width;
	png_uint_32 height;
	png_get_IHDR(
		png, info,
		&width, &height, &bit_depth, &color_type,
		nullptr, nullptr, nullptr);
	width_ = width;
	height_ = height;

	// Setup a pointer array.  Each one points at the begening of a row
	std::unique_ptr<std::uint8_t[]> bytes{new std::uint8_t[width * height * 4]};
	std::unique_ptr<std::uint8_t *[]> rows{new std::uint8_t *[height]};
	for (std::size_t i = 0; i < height; ++i) rows[i] = &bytes[(height - i - 1) * width * 4];

	// Read pixel data using row pointers
	png_read_image(png, rows.get());
	png_read_end(png, nullptr);

	bytes_.reset(bytes.release());
}

std::uint16_t Png::GetWidth() const
{
	return width_;
}

std::uint16_t Png::GetHeight() const
{
	return height_;
}

std::uint8_t const * Png::begin() const
{
	return bytes_.get();
}

std::uint8_t const * Png::end() const
{
	return bytes_.get() + width_ * height_ * 4;
}

}
}
