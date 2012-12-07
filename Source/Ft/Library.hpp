#pragma once

#include <ft2build.h>
#include FT_FREETYPE_H

namespace Twil {
namespace Ft {

class Bitmap;
class Outline;
class Face;
class Stroker;

class Library {
	friend class Ft::Bitmap;
	friend class Ft::Face;
	friend class Ft::Outline;
	friend class Ft::Stroker;

	private:
	FT_Library mId;
	
	public:
	Library();
	~Library();
};

}
}
