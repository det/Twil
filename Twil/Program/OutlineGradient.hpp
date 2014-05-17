#pragma once

#include "OutlineGradientFwd.hpp"

#include "Gl/Context.hpp"
#include "Gl/Program.hpp"

#include <cstdint>

namespace Twil {
namespace Program {

class OutlineGradientT
{
private:
	Gl::ProgramT mProgram;
	GLint mScalingLoc;

public:	
	OutlineGradientT();

	operator std::uint32_t() const;
	void setScaling(float, float);
};

}
}
