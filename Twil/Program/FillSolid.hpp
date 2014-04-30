#pragma once

#include "FillSolidFwd.hpp"

#include "Gl/Context.hpp"
#include "Gl/Program.hpp"

#include <cstdint>

namespace Twil {
namespace Program {

class FillSolidT
{
private:
	Gl::ProgramT mProgram;
	std::int32_t mScalingLoc;

public:
	FillSolidT();

	operator std::uint32_t() const;
	void setScaling(float, float);
};

}
}
