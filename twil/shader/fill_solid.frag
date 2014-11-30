#version 330

uniform samplerBuffer texture;

in Fragment
{
	flat vec4 color;
	flat int pitch;
	flat int offset;
	smooth vec2 texcoord;
} fragment;

layout(location = 0, index = 0) out vec4 color;

void main (void)  
{
	int s = int(fragment.texcoord.s);
	int t = int(fragment.texcoord.t);
	float red = texelFetch(texture, fragment.offset + s + t * fragment.pitch).r;
	color = fragment.color * vec4(red);
}


