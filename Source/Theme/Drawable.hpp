#pragma once

#include <cstdlib>

namespace Twil {
namespace Theme {

template<typename T>
class StreamArrayT;

template<typename T>
class DrawableT
{
	friend class StreamArrayT<T>;

	private:
	std::size_t mSize;
	std::size_t mIsDeleted;

	public:
	virtual ~DrawableT() {}
	virtual void draw(T *) const = 0;
};

}
}
