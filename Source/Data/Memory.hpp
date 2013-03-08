#pragma once

#include <memory>

namespace Twil {
namespace Data {

template<typename T, typename ... ArgsT>
std::unique_ptr<T> makeUnique(ArgsT && ... args)
{
	return std::unique_ptr<T>(new T{std::forward<ArgsT>(args) ...});
}

template<typename T>
std::unique_ptr<T[]> makeArray(std::size_t Size)
{
	return std::unique_ptr<T[]>{new T[Size]};
}

}
}
