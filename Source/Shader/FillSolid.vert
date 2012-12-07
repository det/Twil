#version 330

uniform mat3 ModelView;

layout(location = 0) in vec4 Color;
layout(location = 1) in int Offset;
layout(location = 2) in vec2 Position;
layout(location = 3) in ivec2 Size;

out GeometryData {
	flat vec4 Color;
	flat vec4 Position;
	flat vec2 PositionSize;
	flat ivec2 Size;
	flat int Offset;
} Geometry;

void main(void)
{
	vec3 Position = vec3(Position, 1.0) * ModelView;
	vec2 PositionScale = vec2(ModelView[0][0], ModelView[1][1]);

	Geometry.Color = Color;
	Geometry.Position = vec4(Position.xy, 0.0, Position.z);
	Geometry.PositionSize = Size * PositionScale;
	Geometry.Size = Size;
	Geometry.Offset = Offset;
}
