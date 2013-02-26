#pragma once

#include "Gl/Context.hpp"
#include "Gl/Program.hpp"

namespace Twil {
namespace Program {

class FillSolidT
{
	private:
	Gl::ProgramT mProgram;
	GLint mScalingLoc;

	public:
	FillSolidT();

	operator GLuint() const;
	void setScaling(float, float);
};

}
}
