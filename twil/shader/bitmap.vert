#version 330

uniform vec2 scaling;

layout(location = 0) in vec2 clip_min;
layout(location = 1) in vec2 clip_max;
layout(location = 2) in ivec2 position_min;
layout(location = 3) in ivec2 position_max;
layout(location = 4) in ivec2 texture_size;
layout(location = 5) in int offset;

out Geometry
{
	vec2 position_min;
	vec2 position_max;
	vec2 texture_min;
	vec2 texture_max;
	int pitch;
	int offset;
} geometry;

void main(void)
{
	geometry.texture_min = texture_size * clip_min;
	geometry.texture_max = texture_size * clip_max;
	geometry.position_min = position_min * scaling - 1;
	geometry.position_max = position_max * scaling - 1;
	geometry.pitch = texture_size.x;
	geometry.offset = offset;
}
