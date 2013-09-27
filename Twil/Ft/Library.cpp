#include "Library.hpp"

#include <stdexcept>

namespace Twil {
namespace Ft {

LibraryT::LibraryT()
:
	mId{nullptr}
{
	auto Error = FT_Init_FreeType(&mId);
	if (Error) throw std::runtime_error{"Unable to initialize FreeType"};
}

LibraryT::~LibraryT() noexcept
{
	FT_Done_FreeType(mId);
}

}
}
