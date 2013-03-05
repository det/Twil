#include "Png.hpp"

#include <cstdio>
#include <fstream>
#include <stdexcept>

#include <png.h>

namespace Twil {
namespace Loader {

PngT::PngT(char const * Path) :
	mBytes{nullptr}
{
	// XXX: convert to use ifstream and custom error handler
	auto File = std::fopen(Path, "rb");
	if (File == nullptr) throw std::runtime_error{"Unable to open PNG file"};

	png_byte Magic[8];
	if (std::fread(Magic, 1, sizeof(Magic), File) != sizeof(Magic)) {
		std::fclose(File);
		throw std::runtime_error{"PNG load error"};
	}
	if (!png_check_sig(Magic, sizeof(Magic))) {
		std::fclose(File);
		throw std::runtime_error{"PNG load error"};
	}

	auto PngPointer = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if (!PngPointer) {
		std::fclose(File);
		throw std::runtime_error{"PNG load error"};
	}

	auto InfoPointer = png_create_info_struct(PngPointer);
	if (!InfoPointer) {
		std::fclose(File);
		png_destroy_read_struct(&PngPointer, NULL, NULL);
		throw std::runtime_error{"PNG load error"};
	}

	png_bytep * RowPointers = nullptr;
	// Initialize the setjmp for returning properly after a libpng error occured
	if (setjmp(png_jmpbuf(PngPointer))) {
		png_destroy_read_struct(&PngPointer, &InfoPointer, NULL);
		std::fclose(File);
		delete[] RowPointers;
		throw std::runtime_error{"PNG load error"};
	}

	// Setup libpng for using standard C fread() function with our FILE pointer
	png_init_io(PngPointer, File);

	// Tell libpng that we have already read the magic number
	png_set_sig_bytes(PngPointer, sizeof(Magic));

	// Ensure format is RGBA8
	png_read_info(PngPointer, InfoPointer);
	int BitDepth = png_get_bit_depth(PngPointer, InfoPointer);
	int ColorType = png_get_color_type(PngPointer, InfoPointer);

	switch (ColorType) {
	case PNG_COLOR_TYPE_PALETTE: {
		png_set_palette_to_rgb(PngPointer);
		png_set_add_alpha(PngPointer, 255, PNG_FILLER_AFTER);
	} break;
	case PNG_COLOR_TYPE_GRAY: {
		if (BitDepth < 8) png_set_gray_1_2_4_to_8(PngPointer);
		png_set_gray_to_rgb(PngPointer);
		png_set_add_alpha(PngPointer, 255, PNG_FILLER_AFTER);
	} break;
	case PNG_COLOR_TYPE_GRAY_ALPHA: {
		png_set_gray_to_rgb(PngPointer);
	} break;
	case PNG_COLOR_TYPE_RGB: {
		png_set_add_alpha(PngPointer, 255, PNG_FILLER_AFTER);
	} break;
	}

	if (png_get_valid(PngPointer, InfoPointer, PNG_INFO_tRNS)) png_set_tRNS_to_alpha(PngPointer);
	if (BitDepth == 16) png_set_strip_16(PngPointer);
	else if (BitDepth < 8) png_set_packing(PngPointer);

	// XXX: Assume sRGB approximated input, output linear colorspace, need a more robust method
	png_set_gamma(PngPointer, 1, .45455);

	// Update info structure to apply transformations
	png_read_update_info(PngPointer, InfoPointer);

	// Retrieve updated information
	png_uint_32 Width;
	png_uint_32 Height;
	png_get_IHDR(PngPointer, InfoPointer, &Width, &Height, &BitDepth, &ColorType, NULL, NULL, NULL);
	mWidth = Width;
	mHeight = Height;

	// We can now allocate memory for storing pixel data
	mBytes = new GLubyte[Width * Height * 4];

	// Setup a pointer array.  Each one points at the begening of a row
	RowPointers = new png_bytep[Height];
	for (std::size_t I = 0; I < Height; ++I) {
		RowPointers[I] = mBytes + ((Height - (I + 1)) * Width * 4);
	}

	// Read pixel data using row pointers
	png_read_image(PngPointer, RowPointers);

	// Finish decompression and release memory
	png_read_end(PngPointer, NULL);
	png_destroy_read_struct(&PngPointer, &InfoPointer, NULL);
	delete[] RowPointers;
	std::fclose(File);
}

PngT::~PngT()
{
	delete[] mBytes;
}

unsigned short PngT::getWidth()
{
	return mWidth;
}

unsigned short PngT::getHeight()
{
	return mHeight;
}

GLubyte * PngT::begin()
{
	return mBytes;
}

GLubyte * PngT::end()
{
	return mBytes + mWidth * mHeight * 4;
}

}
}
