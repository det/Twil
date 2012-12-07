#version 330

uniform mat3 ModelView;

layout(location = 0) in vec4 BorderColor;
layout(location = 1) in vec4 TopColor;
layout(location = 2) in vec4 BottomColor;
layout(location = 3) in int InsideOffset;
layout(location = 4) in int OutsideOffset;
layout(location = 5) in vec2 Position;
layout(location = 6) in ivec2 Size;
layout(location = 7) in ivec2 Scale;

out GeometryData {
	flat vec4 BorderColor;
	flat vec4 TopColor;
	flat vec4 BottomColor;
	flat int InsideOffset;
	flat int OutsideOffset;
	flat vec4 Position;
	flat vec2 PositionSize;
	flat ivec2 Size;
} geometry;

void main(void)
{
	vec3 Position = vec3(Position, 1.0) * ModelView;
	vec2 PositionScale = vec2(ModelView[0][0], ModelView[1][1]) * Scale;

	geometry.BorderColor = BorderColor;
	geometry.TopColor = TopColor;
	geometry.BottomColor = BottomColor;
	geometry.InsideOffset = InsideOffset;
	geometry.OutsideOffset = OutsideOffset;
	geometry.Position = vec4(Position.xy, 0.0, Position.z);
	geometry.PositionSize = Size * PositionScale;
	geometry.Size = Size;
}
