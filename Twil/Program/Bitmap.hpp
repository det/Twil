#pragma once

#include "Gl/Context.hpp"
#include "Gl/Program.hpp"

namespace Twil {
namespace Program {

class BitmapT
{
private:
	Gl::ProgramT mProgram;
	GLint mScalingLoc;

public:
	BitmapT();

	operator GLuint() const;
	void setScaling(float, float);
};

}
}
