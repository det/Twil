#include "Png.hpp"

#include "Data/Memory.hpp"

#include <fstream>
#include <stdexcept>

#include <png.h>

namespace {

// Make sure we release our resources on an exception

class PngStructsT
{
private:
	png_structp mPng;
	png_infop mInfo;

public:
	PngStructsT()
	{
		mPng = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
		if (mPng == nullptr) throw std::runtime_error{"PNG load error"};

		mInfo = png_create_info_struct(mPng);
		if (mInfo == nullptr)
		{
			png_destroy_read_struct(&mPng, nullptr, nullptr);
			throw std::runtime_error{"PNG load error"};
		}
	}

	~PngStructsT() noexcept
	{
		png_destroy_read_struct(&mPng, &mInfo, nullptr);
	}

	png_structp & getPng()
	{
		return mPng;
	}

	png_infop & getInfo()
	{
		return mInfo;
	}
};

// Custom error handler to avoid libpng's longjmp error handling

void throwPngError(png_structp PngPointer, png_const_charp ErrorMessage)
{
	throw std::runtime_error{ErrorMessage};
}

// Custom read function to read via std::ifstream instead of FILE *

void readPngData(png_structp PngPointer, png_bytep Data, png_size_t Length)
{
	auto & File = *static_cast<std::ifstream *>(png_get_io_ptr(PngPointer));
	auto Size = static_cast<std::streamsize>(Length);
	File.read(reinterpret_cast<char *>(Data), Size);
	if (File.fail()) throw std::runtime_error{"Png read error"};
	if (File.gcount() != Size) throw std::runtime_error{"Png read error"};
}

}

namespace Twil {
namespace Loader {

PngT::PngT(char const * Path)
:
	mBytes{nullptr}
{
	std::ifstream File;
	File.open(Path, std::ios::in);
	if (!File.is_open()) throw std::runtime_error{"Unable to open png"};

	png_byte Magic[8];
	File.read(reinterpret_cast<char *>(Magic), sizeof(Magic));
	if (File.fail()) throw std::runtime_error{"Png read error"};
	if (File.gcount() != sizeof(Magic)) throw std::runtime_error{"Png read error"};
	if (!png_check_sig(Magic, sizeof(Magic))) throw std::runtime_error{"PNG load error"};

	PngStructsT Structs;
	auto & Png = Structs.getPng();
	auto & Info = Structs.getInfo();

	png_set_read_fn(Png, &File, readPngData);
	png_set_error_fn(Png, nullptr, throwPngError, nullptr);

	// Tell libpng that we have already read the magic number
	png_set_sig_bytes(Png, sizeof(Magic));

	// Ensure format is RGBA8
	png_read_info(Png, Info);
	int BitDepth = png_get_bit_depth(Png, Info);
	int ColorType = png_get_color_type(Png, Info);

	switch (ColorType) {
	case PNG_COLOR_TYPE_PALETTE:
	{
		png_set_palette_to_rgb(Png);
		png_set_add_alpha(Png, 255, PNG_FILLER_AFTER);
	} break;
	case PNG_COLOR_TYPE_GRAY:
	{
		if (BitDepth < 8) png_set_gray_1_2_4_to_8(Png);
		png_set_gray_to_rgb(Png);
		png_set_add_alpha(Png, 255, PNG_FILLER_AFTER);
	} break;
	case PNG_COLOR_TYPE_GRAY_ALPHA:
	{
		png_set_gray_to_rgb(Png);
	} break;
	case PNG_COLOR_TYPE_RGB:
	{
		png_set_add_alpha(Png, 255, PNG_FILLER_AFTER);
	} break;
	}

	if (png_get_valid(Png, Info, PNG_INFO_tRNS))
	{
		png_set_tRNS_to_alpha(Png);
	}

	if (BitDepth == 16) png_set_strip_16(Png);
	else if (BitDepth < 8) png_set_packing(Png);

	// XXX: Assume sRGB approximated input, output linear colorspace, need a more robust method
	png_set_gamma(Png, 1, .45455);

	// Update info structure to apply transformations
	png_read_update_info(Png, Info);

	// Retrieve updated information
	png_uint_32 Width;
	png_uint_32 Height;
	png_get_IHDR(
		Png, Info,
		&Width, &Height, &BitDepth, &ColorType,
		nullptr, nullptr, nullptr);
	mWidth = Width;
	mHeight = Height;

	// Setup a pointer array.  Each one points at the begening of a row
	mBytes = Data::allocUnique<unsigned char>(Width * Height * 4);
	auto Rows = Data::allocUnique<unsigned char *>(Height);
	for (std::size_t I = 0; I < Height; ++I) Rows[I] = &mBytes[(Height - I - 1) * Width * 4];

	// Read pixel data using row pointers
	png_read_image(Png, Rows.get());
	png_read_end(Png, nullptr);
}

std::uint16_t PngT::getWidth() const
{
	return mWidth;
}

std::uint16_t PngT::getHeight() const
{
	return mHeight;
}

unsigned char const * PngT::begin() const
{
	return mBytes.get();
}

unsigned char const * PngT::end() const
{
	return mBytes.get() + mWidth * mHeight * 4;
}

}
}
