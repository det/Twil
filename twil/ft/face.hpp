#pragma once

#include "face.hxx"

#include "bitmap.hxx"
#include "library.hxx"
#include "size.hxx"
#include "stroker.hxx"

#include <ft2build.h>
#include FT_FREETYPE_H
#include <string>

namespace twil {
namespace ft {

/// \brief A FreeType font face.
class Face
{
	friend Bitmap;
	friend Size;
	friend Stroker;

	Face(Face const &) = delete;
	Face & operator =(Face const &) = delete;

private:
	Library * library_;
	FT_Face id_;

public:
	/// \brief Load a font face.
	///
	/// \param path Filename of the font to open.
	/// \param index Index of the face to use.
	/// \throws std::runtime_error If the font face cant be loaded.
	Face(Library & library, char const * path, FT_Long index);
	~Face() noexcept;

	/// \brief Set the active size.
	void SetActiveSize(Size const &);

	/// \returns The face index for the unicode Codepoint.
	FT_UInt GetCharIndex(char32_t codepoint) const;

	/// \returns The FreeType control box for currently loaded glyph.
	FT_BBox GetCBox() const;

	/// \returns The advance value for currently loaded glyph.
	FT_Vector GetAdvance() const;

	/// \returns The left side bearing currently loaded glyph.
	FT_Pos GetLsbDelta() const;

	/// \returns The right side bearing currently loaded glyph.
	FT_Pos GetRsbDelta() const;

	/// \returns The kerning delta for a pair of characters
	FT_Vector GetKerning(FT_UInt first, FT_UInt second) const;

	/// \brief Load a glyph from a face index.
	void LoadGlyph(FT_UInt index);

	/// \brief Load a glyph from a unicode codepoint.
	void LoadGlyph(char32_t codepoint);

	/// \brief Add values to each point of the font face outline.
	void Translate(FT_Pos x, FT_Pos y);
};

}
}
