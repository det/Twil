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
	vec2 PositionMin;
	vec2 PositionMax;
	vec2 TextureMin;
	vec2 TextureMax;
	int Pitch;
	int Offset;
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
