#include "XDeleter.hpp"

namespace Twil {
namespace Platform {

void XDeleterT::operator()(void * Object)
{
	XFree(Object);
}

}
}
