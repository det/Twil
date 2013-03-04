#pragma once

#include <cstdlib>
#include <memory>

#include <X11/Xlib.h>

namespace Twil {
namespace Platform {

struct XDeleterT
{
	void operator()(void *);
};

}
}
