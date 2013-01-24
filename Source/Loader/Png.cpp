#include "Png.hpp"

#include "Gl/Context.hpp"

#include <cstdio>
#include <fstream>
#include <stdexcept>
#include <GL3/gl3.h>

namespace Twil {
namespace Loader {

void PngT::Load(char const * Path)
{
	std::FILE * File;
	png_byte Magic[8];
	png_structp PngPointer;
	png_infop InfoPointer;
	int BitDepth;
	int ColorType;
	png_bytep * RowPointers = nullptr;
	GLubyte * Texels = nullptr;
	png_uint_32 W, H;
	std::size_t I;
	GLsizei Width;
	GLsizei Height;
	GLenum Format;
	GLint InternalFormat;
	GLuint BytesPerPixel;
	GLint Alignment;

	// libpng makes it much easier to use C FILE * than std::ifstream
	File = std::fopen(Path, "rb");
	if (File == nullptr) throw std::runtime_error{"Unable to open PNG file"};

	if (std::fread(Magic, 1, sizeof(Magic), File) != sizeof(Magic)) {
		std::fclose(File);
		throw std::runtime_error{"PNG load error"};
	}
	if (!png_check_sig(Magic, sizeof(Magic))) {
		std::fclose(File);
		throw std::runtime_error{"PNG load error"};
	}

	PngPointer = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if (!PngPointer) {
		std::fclose(File);
		throw std::runtime_error{"PNG load error"};
	}

	InfoPointer = png_create_info_struct(PngPointer);
	if (!InfoPointer) {
		std::fclose(File);
		png_destroy_read_struct(&PngPointer, NULL, NULL);
		throw std::runtime_error{"PNG load error"};
	}

	// Initialize the setjmp for returning properly after a libpng error occured
	if (setjmp(png_jmpbuf(PngPointer))) {
		std::fclose(File);
		png_destroy_read_struct(&PngPointer, &InfoPointer, NULL);

		if (RowPointers) delete[] RowPointers;
		if (Texels) delete[] Texels;
		throw std::runtime_error{"PNG load error"};
	}

	// Setup libpng for using standard C fread() function with our FILE pointer
	png_init_io(PngPointer, File);

	// Tell libpng that we have already read the magic number
	png_set_sig_bytes(PngPointer, sizeof(Magic));

	// Read png info
	png_read_info(PngPointer, InfoPointer);

	// Get some usefull information from header
	BitDepth = png_get_bit_depth(PngPointer, InfoPointer);
	ColorType = png_get_color_type(PngPointer, InfoPointer);

	// Convert index color images to RGB images
	if (ColorType == PNG_COLOR_TYPE_PALETTE) png_set_palette_to_rgb(PngPointer);

	// Convert 1-2-4 bits grayscale images to 8 bits grayscale
	if (ColorType == PNG_COLOR_TYPE_GRAY && BitDepth < 8) png_set_gray_1_2_4_to_8(PngPointer);

	if (png_get_valid(PngPointer, InfoPointer, PNG_INFO_tRNS)) png_set_tRNS_to_alpha(PngPointer);

	if (BitDepth == 16) png_set_strip_16(PngPointer);
	else if (BitDepth < 8) png_set_packing(PngPointer);

	// Update info structure to apply transformations
	png_read_update_info(PngPointer, InfoPointer);

	// Retrieve updated information
	png_get_IHDR(PngPointer, InfoPointer, &W, &H, &BitDepth, &ColorType, NULL, NULL, NULL);
	Width = W;
	Height = H;

	/* Get image format and components per pixel */
	switch (ColorType) {

	case PNG_COLOR_TYPE_GRAY: {
		Format = GL_RED;
		BytesPerPixel = 1;
		InternalFormat = GL_RED;
	} break;

	case PNG_COLOR_TYPE_RGB: {
		Format = GL_RGB;
		BytesPerPixel = 3;
		InternalFormat = GL_RGB;
	} break;

	case PNG_COLOR_TYPE_RGB_ALPHA: {
		Format = GL_RGBA;
		BytesPerPixel = 4;
		InternalFormat = GL_RGBA;
	} break;

	default: {
		throw std::runtime_error{"PNG load error"};
	} break;

	}

	// We can now allocate memory for storing pixel data
	Texels = new GLubyte[W * H * BytesPerPixel];

	// Setup a pointer array.  Each one points at the begening of a row
	RowPointers = new png_bytep[Height];

	for (I = 0; I < H; ++I) RowPointers[I] = Texels + ((H - (I + 1)) * W * BytesPerPixel);

	// Read pixel data using row pointers
	png_read_image(PngPointer, RowPointers);

	// Finish decompression and release memory
	png_read_end(PngPointer, NULL);
	png_destroy_read_struct(&PngPointer, &InfoPointer, NULL);

	// We don't need row pointers anymore
	delete[] RowPointers;

	fclose(File);

	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &mId);
	Bind();

	// Setup some parameters for texture filters and mipmapping
//	context.TexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
//	context.TexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glGetIntegerv(GL_UNPACK_ALIGNMENT, &Alignment);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage2D(GL_TEXTURE_2D, 0, InternalFormat, Width, Height, 0, Format, GL_UNSIGNED_BYTE, Texels);
	glPixelStorei(GL_UNPACK_ALIGNMENT, Alignment);
//	context.GenerateMipmap(GL_TEXTURE_2D);

	// OpenGL has its own copy of texture data
	delete Texels;
}

void PngT::Bind() const
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mId);
}

}
}
