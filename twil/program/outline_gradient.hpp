#pragma once

#include "outline_gradient.hxx"

#include "gl/context.hpp"
#include "gl/program.hpp"

#include <cstdint>

namespace twil {
namespace program {

class OutlineGradient
{
private:
	gl::Program program_;
	GLint scaling_loc_;

public:	
	OutlineGradient();

	operator std::uint32_t() const;
	void SetScaling(float, float);
};

}
}
