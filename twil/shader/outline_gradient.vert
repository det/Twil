#version 330

uniform vec2 scaling;

layout(location = 0) in vec4 border_color;
layout(location = 1) in vec4 bottom_color;
layout(location = 2) in vec4 top_color;
layout(location = 3) in vec2 clip_min;
layout(location = 4) in vec2 clip_max;
layout(location = 5) in ivec2 position_min;
layout(location = 6) in ivec2 position_max;
layout(location = 7) in ivec2 texture_size;
layout(location = 8) in int inside_index;
layout(location = 9) in int outside_index;

out Geometry
{
	vec4 border_color;
	vec4 bottom_color;
	vec4 top_color;
	vec2 position_min;
	vec2 position_max;
	vec2 texture_min;
	vec2 texture_max;
	int pitch;
	int inside_index;
	int outside_index;
} geometry;

void main(void)
{
	geometry.border_color = vec4(border_color.rgb * 8 - 0.5, border_color.a);
	geometry.bottom_color = vec4(bottom_color.rgb * 8 - 0.5, bottom_color.a);
	geometry.top_color = vec4(top_color.rgb * 8 - 0.5, top_color.a);
	geometry.texture_min = texture_size * clip_min;
	geometry.texture_max = texture_size * clip_max;
	geometry.position_min = position_min * scaling - 1;
	geometry.position_max = position_max * scaling - 1;
	geometry.pitch = texture_size.x;
	geometry.inside_index = inside_index;
	geometry.outside_index = outside_index;
}
