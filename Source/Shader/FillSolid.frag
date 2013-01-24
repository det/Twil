#version 330

uniform samplerBuffer Texture;

in FragmentData
{
	flat vec4 Color;
	flat int Pitch;
	flat int Offset;
	smooth vec2 Texcoord;
} Fragment;

layout(location = 0, index = 0) out vec4 Color;

void main (void)  
{
	int S = int(Fragment.Texcoord.s);
	int T = int(Fragment.Texcoord.t);
	float Red = texelFetch(Texture, Fragment.Offset + S + T * Fragment.Pitch).r;
	Color = Fragment.Color * vec4(Red);
}


