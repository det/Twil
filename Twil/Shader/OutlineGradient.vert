#version 330

uniform vec2 Scaling;

layout(location = 0) in vec4 BorderColor;
layout(location = 1) in vec4 BottomColor;
layout(location = 2) in vec4 TopColor;
layout(location = 3) in vec2 ClipMin;
layout(location = 4) in vec2 ClipMax;
layout(location = 5) in ivec2 PositionMin;
layout(location = 6) in ivec2 PositionMax;
layout(location = 7) in ivec2 TextureSize;
layout(location = 8) in int InsideIndex;
layout(location = 9) in int OutsideIndex;

out GeometryT
{
	vec4 BorderColor;
	vec4 BottomColor;
	vec4 TopColor;
	vec2 PositionMin;
	vec2 PositionMax;
	vec2 TextureMin;
	vec2 TextureMax;
	int Pitch;
	int InsideIndex;
	int OutsideIndex;
} Geometry;

void main(void)
{
	Geometry.BorderColor = BorderColor;
	Geometry.BottomColor = BottomColor;
	Geometry.TopColor = TopColor;
	Geometry.TextureMin = TextureSize * ClipMin;
	Geometry.TextureMax = TextureSize * ClipMax;
	Geometry.PositionMin = PositionMin * Scaling - 1;
	Geometry.PositionMax = PositionMax * Scaling - 1;
	Geometry.Pitch = TextureSize.x;
	Geometry.InsideIndex = InsideIndex;
	Geometry.OutsideIndex = OutsideIndex;
}
