#pragma once

#include "library.hxx"

#include "bitmap.hxx"
#include "outline.hxx"
#include "face.hxx"
#include "stroker.hxx"

#include <ft2build.h>
#include FT_FREETYPE_H

namespace twil {
namespace ft {

/// \brief A FreeType library.
class Library
{
	friend Bitmap;
	friend Face;
	friend Outline;
	friend Stroker;

	Library(Library const &) = delete;
	Library & operator =(Library const &) = delete;

private:
	FT_Library id_;

public:
	/// \throws std::runtime_error If the freetype library cant be initialized.
	Library();
	~Library() noexcept;
};

}
}
