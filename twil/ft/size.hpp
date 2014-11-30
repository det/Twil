#pragma once

#include "size.hxx"

#include "face.hxx"

#include <cstdint>

#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_SIZES_H

namespace twil {
namespace ft {

/// \brief A FreeType font face size.
class Size
{
	friend Face;

	Size(Size const &) = delete;
	Size & operator =(Size const &) = delete;

private:
	FT_Size id_;

public:
	/// \brief Load a size for a font face
	/// \param face The font face to load the size from.
	/// \param size The size to load in 26.6 fixpoint.
	/// \throws std::runtime_error If the size cant be loaded for the font face.
	Size(Face & face, FT_UInt width, FT_UInt height);
	~Size() noexcept;

	/// \returns The height in 26.6 fixpoint.
	FT_Short GetHeight() const;

	/// \returns The descender in 26.6 fixpoint.
	FT_Short GetDescender() const;

	/// \returns The ascender in 26.6 fixpoint.
	FT_Short GetAscender() const;
};

}
}
