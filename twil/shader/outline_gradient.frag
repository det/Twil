#version 330

uniform samplerBuffer texture;

in Fragment
{
	flat vec4 border_color;
	flat int pitch;
	flat int inside_index;
	flat int outside_index;
	smooth vec4 color;
	smooth vec2 texcoord;
} fragment;

layout(location = 0, index = 0) out vec4 color;

void main (void)  
{
	int s = int(fragment.texcoord.s);
	int t = int(fragment.texcoord.t);
	float inside_factor = texelFetch(texture, fragment.inside_index + s + t * fragment.pitch).r;
	float outside_factor = texelFetch(texture, fragment.outside_index + s + t * fragment.pitch).r;
	color = mix(fragment.border_color, fragment.color, inside_factor);
	color.a *= outside_factor;
}
