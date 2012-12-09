#pragma once

#include <ft2build.h>
#include FT_FREETYPE_H
#include <string>

namespace Twil {
namespace Ft {

class Bitmap;
class Library;
class Size;
class Stroker;

class Face
{
	friend class Ft::Bitmap;
	friend class Ft::Size;
	friend class Ft::Stroker;

	private:
	Ft::Library & mLibrary;
	FT_Face mId;

	public:
	Face(Ft::Library &, std::string const &, FT_Long);
	~Face();

	void setActiveSize(Ft::Size const &);
	FT_UInt getCharIndex(char32_t);
	FT_BBox getCBox();
	FT_Vector getAdvance();
	FT_Pos getLsbDelta();
	FT_Pos getRsbDelta();
	FT_Vector getKerning(FT_UInt, FT_UInt);

	void loadGlyph(FT_UInt);
	void loadGlyph(char32_t);
	void translate(FT_Pos, FT_Pos);
};

}
}
