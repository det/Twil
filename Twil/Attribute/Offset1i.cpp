#include "Offset1i.hpp"

#include "Gl/Context.hpp"

namespace Twil {
namespace Attribute {

void Offset1iT::setup(std::uint32_t Index, std::int32_t Stride, const void * Offset)
{
	glEnableVertexAttribArray(Index);
	glVertexAttribIPointer(Index, 1, GL_UNSIGNED_INT, Stride, Offset);
}

}
}
