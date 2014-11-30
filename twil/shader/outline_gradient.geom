#version 330

layout(points) in;
layout(triangle_strip, max_vertices=4) out;

in Geometry
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
} geometry[];

out Fragment
{
	flat vec4 border_color;
	flat int pitch;
	flat int inside_index;
	flat int outside_index;
	smooth vec4 color;
	smooth vec2 texcoord;
} fragment;

void main()
{
	gl_Position = vec4(geometry[0].position_min.x, geometry[0].position_min.y, 0, 1);
	fragment.pitch = geometry[0].pitch;
	fragment.border_color = geometry[0].border_color;
	fragment.inside_index = geometry[0].inside_index;
	fragment.outside_index = geometry[0].outside_index;
	fragment.color = geometry[0].bottom_color;
	fragment.texcoord = vec2(geometry[0].texture_min.x, geometry[0].texture_min.y);
	EmitVertex();

	gl_Position = vec4(geometry[0].position_max.x, geometry[0].position_min.y, 0, 1);
	fragment.pitch = geometry[0].pitch;
	fragment.border_color = geometry[0].border_color;
	fragment.inside_index = geometry[0].inside_index;
	fragment.outside_index = geometry[0].outside_index;
	fragment.color = geometry[0].bottom_color;
	fragment.texcoord = vec2(geometry[0].texture_max.x, geometry[0].texture_min.y);
	EmitVertex();

	gl_Position = vec4(geometry[0].position_min.x, geometry[0].position_max.y, 0, 1);
	fragment.pitch = geometry[0].pitch;
	fragment.border_color = geometry[0].border_color;
	fragment.inside_index = geometry[0].inside_index;
	fragment.outside_index = geometry[0].outside_index;
	fragment.color = geometry[0].top_color;
	fragment.texcoord = vec2(geometry[0].texture_min.x, geometry[0].texture_max.y);
	EmitVertex();

	gl_Position = vec4(geometry[0].position_max.x, geometry[0].position_max.y, 0, 1);
	fragment.border_color = geometry[0].border_color;
	fragment.pitch = geometry[0].pitch;
	fragment.inside_index = geometry[0].inside_index;
	fragment.outside_index = geometry[0].outside_index;
	fragment.color = geometry[0].top_color;
	fragment.texcoord = vec2(geometry[0].texture_max.x, geometry[0].texture_max.y);
	EmitVertex();
}
