#pragma once

#include <cstdlib>
#include <memory>

namespace Twil {
namespace Data {

template<typename T>
struct FreeDeleterT
{
	void operator()(T * Object)
	{
		std::free(Object);
	}
};

}
}
