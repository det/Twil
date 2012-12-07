#include "Ft/Library.hpp"

#include <iostream>
#include <stdexcept>

namespace Twil {
namespace Ft {

Library::Library() :
	mId{nullptr}
{
	auto Error = FT_Init_FreeType(&mId);
	if (Error) throw std::runtime_error{"Unable to initialize FreeType"};
}

Library::~Library()
{
	FT_Done_FreeType(mId);
}

}
}
