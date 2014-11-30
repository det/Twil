#pragma once

#include "fill_solid.hxx"

#include "gl/context.hpp"
#include "gl/program.hpp"

#include <cstdint>

namespace twil {
namespace program {

class FillSolid
{
private:
	gl::Program program_;
	GLint scaling_loc_;

public:
	FillSolid();

	operator std::uint32_t() const;
	void SetScaling(float, float);
};

}
}
