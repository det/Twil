#version 330

uniform samplerBuffer texture;

in FragmentData {
	flat vec4 BorderColor;
	flat int InsideOffset;
	flat int OutsideOffset;
	flat ivec2 Size;
	smooth vec2 Texcoord;
	smooth vec4 Color;
} Fragment;

layout(location = 0, index = 0) out vec4 Color;

void main (void)  
{
	int S = int(Fragment.Texcoord.s);
	int T = int(Fragment.Texcoord.t);
	float Inside = texelFetch(texture, Fragment.InsideOffset + S + T * Fragment.Size.x).r;
	float Outside = texelFetch(texture, Fragment.OutsideOffset + S + T * Fragment.Size.x).r;
	Color = mix(Fragment.BorderColor, Fragment.Color, Inside);
	Color.a *= Outside;
}


