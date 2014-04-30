#pragma once

#include "LibraryFwd.hpp"

#include "BitmapFwd.hpp"
#include "OutlineFwd.hpp"
#include "FaceFwd.hpp"
#include "StrokerFwd.hpp"

#include <ft2build.h>
#include FT_FREETYPE_H

namespace Twil {
namespace Ft {

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
	~LibraryT() noexcept;
};

}
}
