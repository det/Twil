#version 330

uniform vec2 Scaling;

layout(location = 0) in vec4 Color;
layout(location = 1) in vec2 ClipMin;
layout(location = 2) in vec2 ClipMax;
layout(location = 3) in ivec2 PositionMin;
layout(location = 4) in ivec2 PositionMax;
layout(location = 5) in ivec2 TextureSize;
layout(location = 6) in int Offset;

out GeometryT
{
	vec4 Color;
	vec2 PositionMin;
	vec2 PositionMax;
	vec2 TextureMin;
	vec2 TextureMax;
	int Pitch;
	int Offset;
} Geometry;

void main(void)
{
	Geometry.Color = Color;
	Geometry.TextureMin = TextureSize * ClipMin;
	Geometry.TextureMax = TextureSize * ClipMax;
	Geometry.PositionMin = PositionMin * Scaling - 1;
	Geometry.PositionMax = PositionMax * Scaling - 1;
	Geometry.Pitch = TextureSize.x;
	Geometry.Offset = Offset;
}
