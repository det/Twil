#pragma once

#include "bitmap.hxx"

#include "gl/context.hpp"
#include "gl/program.hpp"

#include <cstdint>

namespace twil {
namespace program {

class Bitmap
{
private:
	gl::Program program_;
	GLint scaling_loc_;

public:
	Bitmap();

	operator std::uint32_t() const;
	void SetScaling(float, float);
};

}
}
