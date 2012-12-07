#pragma once

#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_OUTLINE_H
#include FT_STROKER_H

namespace Twil {
namespace Ft {

class Bitmap;
class Library;
class Path;
class Stroker;

class Outline {
	friend class Bitmap;
	friend class Stroker;

	private:
	Ft::Library const & mLibrary;
	FT_Outline mId;
	FT_Vector mA;
	short mPointCapacity;
	short mContourCapacity;

	public:
	Outline(Ft::Library const &);
	~Outline();

	// Movable only
	Outline(Ft::Outline &) = delete;
	//Outline(Ft::Outline &&) = default;
	Outline & operator=(Ft::Outline &) = delete;
	//Outline & operator=(Ft::Outline &&) = default;

	void reservePoints(short);
	void reserveContours(short);
	void clear();
	void reverse();
	void translate(FT_Pos, FT_Pos);
	void transform(FT_Matrix const &);
	void beginPath(FT_Vector);
	void endPath();
	void addLine(FT_Vector);
	void addQuadratic(FT_Vector, FT_Vector);
	void addCubic(FT_Vector, FT_Vector, FT_Vector);
	void add(Ft::Stroker const &, FT_StrokerBorder);
	void add(Ft::Stroker const &);
	void stroke(Ft::Stroker &);
};

}
}
