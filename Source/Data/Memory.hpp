#pragma once

#include <cstdlib>
#include <memory>

namespace Twil {
namespace Data {

template<typename T, typename ... ArgsT>
std::unique_ptr<T> makeUnique(ArgsT && ... Args)
{
	return std::unique_ptr<T>(new T{std::forward<ArgsT>(Args) ...});
}

template<typename T>
std::unique_ptr<T[]> makeArray(std::size_t Size)
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
