#include "Png.hpp"

#include "Data/Memory.hpp"

#include <fstream>
#include <stdexcept>

#include <png.h>

namespace {

// Make sure we release our resources on an exception

struct PngPointersT
{
	png_structp Png = nullptr;
	png_infop Info = nullptr;

	~PngPointersT()
	{
		png_destroy_read_struct(&Png, &Info, nullptr);
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

PngT::PngT(char const * Path) :
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

	PngPointersT Pointers;
	Pointers.Png = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
	if (Pointers.Png == nullptr) throw std::runtime_error{"PNG load error"};
	Pointers.Info = png_create_info_struct(Pointers.Png);
	if (Pointers.Info == nullptr) throw std::runtime_error{"PNG load error"};

	png_set_read_fn(Pointers.Png, &File, readPngData);
	png_set_error_fn(Pointers.Png, nullptr, throwPngError, nullptr);

	// Tell libpng that we have already read the magic number
	png_set_sig_bytes(Pointers.Png, sizeof(Magic));

	// Ensure format is RGBA8
	png_read_info(Pointers.Png, Pointers.Info);
	int BitDepth = png_get_bit_depth(Pointers.Png, Pointers.Info);
	int ColorType = png_get_color_type(Pointers.Png, Pointers.Info);

	switch (ColorType) {
	case PNG_COLOR_TYPE_PALETTE: {
		png_set_palette_to_rgb(Pointers.Png);
		png_set_add_alpha(Pointers.Png, 255, PNG_FILLER_AFTER);
	} break;
	case PNG_COLOR_TYPE_GRAY: {
		if (BitDepth < 8) png_set_gray_1_2_4_to_8(Pointers.Png);
		png_set_gray_to_rgb(Pointers.Png);
		png_set_add_alpha(Pointers.Png, 255, PNG_FILLER_AFTER);
	} break;
	case PNG_COLOR_TYPE_GRAY_ALPHA: {
		png_set_gray_to_rgb(Pointers.Png);
	} break;
	case PNG_COLOR_TYPE_RGB: {
		png_set_add_alpha(Pointers.Png, 255, PNG_FILLER_AFTER);
	} break;
	}

	if (png_get_valid(Pointers.Png, Pointers.Info, PNG_INFO_tRNS)) {
		png_set_tRNS_to_alpha(Pointers.Png);
	}

	if (BitDepth == 16) png_set_strip_16(Pointers.Png);
	else if (BitDepth < 8) png_set_packing(Pointers.Png);

	// XXX: Assume sRGB approximated input, output linear colorspace, need a more robust method
	png_set_gamma(Pointers.Png, 1, .45455);

	// Update info structure to apply transformations
	png_read_update_info(Pointers.Png, Pointers.Info);

	// Retrieve updated information
	png_uint_32 Width;
	png_uint_32 Height;
	png_get_IHDR(
		Pointers.Png, Pointers.Info,
		&Width, &Height, &BitDepth, &ColorType,
		nullptr, nullptr, nullptr
	);
	mWidth = Width;
	mHeight = Height;

	// Setup a pointer array.  Each one points at the begening of a row
	mBytes = Data::makeArray<unsigned char>(Width * Height * 4);
	auto Rows = Data::makeArray<unsigned char *>(Height);
	for (std::size_t I = 0; I < Height; ++I) {
		Rows[I] = mBytes.get() + (Height - I - 1) * Width * 4;
	}

	// Read pixel data using row pointers
	png_read_image(Pointers.Png, Rows.get());
	png_read_end(Pointers.Png, nullptr);
}

unsigned short PngT::getWidth() const
{
	return mWidth;
}

unsigned short PngT::getHeight() const
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
