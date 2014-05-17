#pragma once

#include "BitmapFwd.hpp"

#include "Gl/Context.hpp"
#include "Gl/Program.hpp"

#include <cstdint>

namespace Twil {
namespace Program {

class BitmapT
{
private:
	Gl::ProgramT mProgram;
	GLint mScalingLoc;

public:
	BitmapT();

	operator std::uint32_t() const;
	void setScaling(float, float);
};

}
}
