#pragma once

#include <cstddef>
#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_SIZES_H
#include <memory>

namespace Twil {
namespace Ft {

class Face;

class Size
{
	friend class Ft::Face;

	private:
	FT_Size mId;

	public:
	Size(Face &, FT_F26Dot6);
	~Size();

	FT_Short getHeight();
	FT_Short getDescender();
	FT_Short getAscender();
};

}
}
