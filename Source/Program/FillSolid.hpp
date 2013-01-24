#pragma once

#include "Gl/Program.hpp"

#include <GL3/gl3.h>

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
