#pragma once

#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_STROKER_H

namespace Twil {
namespace Ft {

class Face;
class Library;
class Outline;

class Stroker {
	friend class Ft::Outline;

	private:
	FT_Stroker mId;

	public:
	Stroker(Ft::Library &);
	~Stroker();

	void clear();
	void setOptions(FT_Fixed, FT_Stroker_LineCap, FT_Stroker_LineJoin, FT_Fixed);
	void beginPath(FT_Vector, FT_Bool = false);
	void endPath();
	void addLine(FT_Vector);
	void addQuadratic(FT_Vector, FT_Vector);
	void addCubic(FT_Vector, FT_Vector, FT_Vector);
	void set(Ft::Outline &);
	void set(Ft::Face &);
};

}
}
