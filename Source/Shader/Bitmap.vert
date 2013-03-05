#version 330

uniform vec2 Scaling;

layout(location = 0) in vec2 ClipMin;
layout(location = 1) in vec2 ClipMax;
layout(location = 2) in ivec2 PositionMin;
layout(location = 3) in ivec2 PositionMax;
layout(location = 4) in ivec2 TextureSize;
layout(location = 5) in int Offset;

out GeometryT
{
	flat vec2 PositionMin;
	flat vec2 PositionMax;
	flat vec2 TextureMin;
	flat vec2 TextureMax;
	flat int Pitch;
	flat int Offset;
} Geometry;

void main(void)
{
	Geometry.TextureMin = TextureSize * ClipMin;
	Geometry.TextureMax = TextureSize * ClipMax;
	Geometry.PositionMin = PositionMin * Scaling - 1;
	Geometry.PositionMax = PositionMax * Scaling - 1;
	Geometry.Pitch = TextureSize.x;
	Geometry.Offset = Offset;
}
