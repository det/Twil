#include "Color4b.hpp"

#include "Gl/Context.hpp"

namespace Twil {
namespace Attribute {

void Color4bT::setup(std::uint32_t Index, std::int32_t Stride, const void * Offset)
{
	glEnableVertexAttribArray(Index);
	glVertexAttribPointer(Index, 4, GL_UNSIGNED_BYTE, true, Stride, Offset);
}

Color4bT mix(Color4bT const & A, Color4bT const & B, std::uint16_t Weight1)
{
	std::uint16_t Weight2 = 65535 - Weight1;

	std::uint8_t Red = (A.Red * Weight1 + B.Red * Weight2) / 65535;
	std::uint8_t Green = (A.Green * Weight1 + B.Green * Weight2) / 65535;
	std::uint8_t Blue = (A.Blue * Weight1 + B.Blue * Weight2) / 65535;
	std::uint8_t Alpha = (A.Alpha * Weight1 + B.Alpha * Weight2) / 65535;

	return {Red, Green, Blue, Alpha};
}

}
}
