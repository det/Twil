#pragma once

#include <ft2build.h>
#include FT_FREETYPE_H
#include <string>

namespace Twil {
namespace Ft {

class BitmapT;
class LibraryT;
class SizeT;
class StrokerT;

/// \brief A FreeType font face.
class FaceT
{
	friend class BitmapT;
	friend class SizeT;
	friend class StrokerT;

	FaceT(FaceT const &) = delete;
	FaceT & operator =(FaceT const &) = delete;

private:
	LibraryT * mLibrary;
	FT_Face mId;

public:
	/// \brief Load a font face.
	///
	/// \param Path Filename of the font to open.
	/// \param Index Index of the face to use.
	/// \throws std::runtime_error If the font face cant be loaded.
	FaceT(LibraryT & Library, char const * Path, FT_Long Index);
	~FaceT();

	/// \brief Set the active size.
	void setActiveSize(SizeT const &);

	/// \returns The face index for the unicode Codepoint.
	FT_UInt getCharIndex(char32_t Codepoint) const;

	/// \returns The FreeType control box for currently loaded glyph.
	FT_BBox getCBox() const;

	/// \returns The advance value for currently loaded glyph.
	FT_Vector getAdvance() const;

	/// \returns The left side bearing currently loaded glyph.
	FT_Pos getLsbDelta() const;

	/// \returns The right side bearing currently loaded glyph.
	FT_Pos getRsbDelta() const;

	/// \returns The kerning delta for a pair of characters
	FT_Vector getKerning(FT_UInt First, FT_UInt Second) const;

	/// \brief Load a glyph from a face index.
	void loadGlyph(FT_UInt Index);

	/// \brief Load a glyph from a unicode codepoint.
	void loadGlyph(char32_t Codepoint);

	/// \brief Add values to each point of the font face outline.
	void translate(FT_Pos X, FT_Pos Y);
};

}
}
