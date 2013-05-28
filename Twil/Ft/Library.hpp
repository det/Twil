#pragma once

#include <ft2build.h>
#include FT_FREETYPE_H

namespace Twil {
namespace Ft {

class BitmapT;
class OutlineT;
class FaceT;
class StrokerT;

/// \brief A FreeType library.
class LibraryT
{
	friend class BitmapT;
	friend class FaceT;
	friend class OutlineT;
	friend class StrokerT;

	LibraryT(LibraryT const &) = delete;
	LibraryT & operator =(LibraryT const &) = delete;

	private:
	FT_Library mId;

	public:
	/// \throws std::runtime_error If the freetype library cant be initialized.
	LibraryT();
	~LibraryT();
};

}
}
