#include "library.hpp"

#include <stdexcept>

namespace twil {
namespace ft {

Library::Library()
:
	id_{nullptr}
{
	auto error = FT_Init_FreeType(&id_);
	if (error) throw std::runtime_error{"Unable to initialize FreeType"};
}

Library::~Library() noexcept
{
	FT_Done_FreeType(id_);
}

}
}
