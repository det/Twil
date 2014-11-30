#pragma once

#include "drawable.hxx"
#include "stream_array.hxx"

#include <cstdlib>

namespace twil {
namespace theme {

template<typename T>
class Drawable
{
	friend StreamArray<T>;

private:
	std::size_t size_ = 0;
	std::size_t draw_cycles_ = 0;
	bool needs_resize_ = false;

public:
	virtual ~Drawable() = default;
	virtual void Draw(T *) const = 0;
};

}
}
