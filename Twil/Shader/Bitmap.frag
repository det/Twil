#version 330

uniform samplerBuffer Texture;

in FragmentT
{
	flat int Pitch;
	flat int Offset;
	smooth vec2 Texcoord;
} Fragment;

layout(location = 0, index = 0) out vec4 Color;

void main (void)
{
	int S = int(Fragment.Texcoord.s);
	int T = int(Fragment.Texcoord.t);
	Color = texelFetch(Texture, Fragment.Offset + S + T * Fragment.Pitch);
}


