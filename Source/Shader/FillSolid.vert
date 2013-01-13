#version 330

uniform mat3 ModelView;

layout(location = 0) in vec4 Color;
layout(location = 1) in int Offset;
layout(location = 2) in vec2 Position;
layout(location = 3) in ivec2 Size;
layout(location = 4) in ivec2 ClipMin;
layout(location = 5) in ivec2 ClipMax;


out GeometryData {
	flat vec4 Color;
	flat vec4 Position;
	flat vec2 PositionSize;
	flat ivec2 TextureSize;
	flat int Pitch;
	flat int Offset;
} Geometry;

void main(void)
{

	vec3 Position = vec3(Position + ClipMin, 1.0) * ModelView;
	vec2 PositionScale = vec2(ModelView[0][0], ModelView[1][1]);
	ivec2 ShrunkenSize = Size - ClipMin - ClipMax;

	Geometry.Color = Color;
	Geometry.Position = vec4(Position.xy, 0.0, Position.z);
	Geometry.PositionSize = ShrunkenSize * PositionScale;
	Geometry.TextureSize = ShrunkenSize;
	Geometry.Pitch = Size.x;
	Geometry.Offset = Offset + ClipMin.x + ClipMin.y * Size.x;
}
