#pragma once

#include "Gl/Program.hpp"

#include <GL3/gl3.h>

namespace Twil {
namespace Program {

class OutlineGradientT
{
	private:
	Gl::ProgramT mProgram;
	GLint mScalingLoc;

	public:	
	OutlineGradientT();

	operator GLuint() const;
	void setScaling(float, float);
};

}
}
