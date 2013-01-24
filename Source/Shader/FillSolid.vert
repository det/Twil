#version 330

uniform vec2 Scaling;

layout(location = 0) in vec4 Color;
layout(location = 1) in ivec2 ClipMin;
layout(location = 2) in ivec2 ClipMax;
layout(location = 3) in ivec2 PositionMin;
layout(location = 4) in ivec2 PositionMax;
layout(location = 5) in ivec2 TextureSize;
layout(location = 6) in int Offset;

out GeometryData
{
	flat vec4 Color;
	flat vec2 PositionMin;
	flat vec2 PositionMax;
	flat vec2 TextureMin;
	flat vec2 TextureMax;
	flat int Pitch;
	flat int Offset;
} Geometry;

void main(void)
{
	vec2 InverseScale = TextureSize / vec2(PositionMax - PositionMin);
	Geometry.Color = Color;
	Geometry.TextureMin = (ClipMin - PositionMin) * InverseScale;
	Geometry.TextureMax = (ClipMax - PositionMin) * InverseScale;
	Geometry.PositionMin = ClipMin * Scaling - 1;
	Geometry.PositionMax = ClipMax * Scaling - 1;
	Geometry.Pitch = TextureSize.x;
	Geometry.Offset = Offset;
}
