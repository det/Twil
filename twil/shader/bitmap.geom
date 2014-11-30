#version 330

layout(points) in;
layout(triangle_strip, max_vertices=4) out;

in Geometry
{
	vec2 position_min;
	vec2 position_max;
	vec2 texture_min;
	vec2 texture_max;
	int pitch;
	int offset;
} geometry[];

out Fragment
{
	flat int pitch;
	flat int offset;
	smooth vec2 texcoord;
} fragment;

void main()
{
	gl_Position = vec4(geometry[0].position_min.x, geometry[0].position_min.y, 0, 1);
	fragment.pitch = geometry[0].pitch;
	fragment.offset = geometry[0].offset;
	fragment.texcoord = vec2(geometry[0].texture_min.x, geometry[0].texture_min.y);
	EmitVertex();

	gl_Position = vec4(geometry[0].position_max.x, geometry[0].position_min.y, 0, 1);
	fragment.pitch = geometry[0].pitch;
	fragment.offset = geometry[0].offset;
	fragment.texcoord = vec2(geometry[0].texture_max.x, geometry[0].texture_min.y);
	EmitVertex();

	gl_Position = vec4(geometry[0].position_min.x, geometry[0].position_max.y, 0, 1);
	fragment.pitch = geometry[0].pitch;
	fragment.offset = geometry[0].offset;
	fragment.texcoord = vec2(geometry[0].texture_min.x, geometry[0].texture_max.y);
	EmitVertex();

	gl_Position = vec4(geometry[0].position_max.x, geometry[0].position_max.y, 0, 1);
	fragment.pitch = geometry[0].pitch;
	fragment.offset = geometry[0].offset;
	fragment.texcoord = vec2(geometry[0].texture_max.x, geometry[0].texture_max.y);
	EmitVertex();
}
