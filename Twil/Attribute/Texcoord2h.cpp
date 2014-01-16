#include "Texcoord2h.hpp"

#include "Gl/Context.hpp"

namespace Twil {
namespace Attribute {

void Texcoord2hT::setup(std::uint32_t Index, std::int32_t Stride, const void * Offset)
{
	glEnableVertexAttribArray(Index);
	glVertexAttribPointer(Index, 2, GL_UNSIGNED_SHORT, true, Stride, Offset);
}

}
}
