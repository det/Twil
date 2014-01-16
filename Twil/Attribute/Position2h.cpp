#include "Position2h.hpp"

#include "Gl/Context.hpp"

namespace Twil {
namespace Attribute {

void Position2hT::setup(std::uint32_t Index, std::int32_t Stride, const void * Offset)
{
	glEnableVertexAttribArray(Index);
	glVertexAttribIPointer(Index, 2, GL_SHORT, Stride, Offset);
}

}
}
