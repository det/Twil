#pragma once

#include "MemoryFwd.hpp"

#include <cstdlib>
#include <memory>

namespace Twil {
namespace Data {

template<typename T>
std::unique_ptr<T[]> makeUniqueArray(std::size_t Size)
{
	return std::unique_ptr<T[]>{new T[Size]};
}

struct FreeDeleterT
{
	template<typename T>
	void operator()(T * Object)
	{
		std::free(Object);
	}
};

}
}
