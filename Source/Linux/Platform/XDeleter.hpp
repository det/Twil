#pragma once

#include <cstdlib>
#include <memory>

#include <X11/Xlib.h>

namespace Twil {
namespace Platform {

template<typename T>
struct XDeleterT
{
	void operator()(T * Object)
	{
		XFree(Object);
	}
};

}
}
