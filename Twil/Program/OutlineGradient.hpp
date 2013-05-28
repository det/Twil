#pragma once

#include "Gl/Context.hpp"
#include "Gl/Program.hpp"

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
