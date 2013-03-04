#pragma once

#include <cstdlib>
#include <memory>

namespace Twil {
namespace Platform {

struct FreeDeleterT
{
	void operator()(void *);
};

}
}
