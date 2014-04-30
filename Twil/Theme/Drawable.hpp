#pragma once

#include "DrawableFwd.hpp"
#include "StreamArrayFwd.hpp"

#include <cstdlib>

namespace Twil {
namespace Theme {

template<typename T>
class DrawableT
{
	friend class StreamArrayT<T>;

private:
	std::size_t mSize = 0;
	std::size_t mDrawCycles = 0;
	bool mNeedsResize = false;

public:
	virtual ~DrawableT() = default;
	virtual void draw(T *) const = 0;
};

}
}
