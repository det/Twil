#include "FreeDeleter.hpp"

namespace Twil {
namespace Platform {

void FreeDeleterT::operator()(void * Object)
{
	std::free(Object);
}

}
}
