#version 330

uniform samplerBuffer Texture;

in FragmentT
{
	flat vec4 BorderColor;
	flat int Pitch;
	flat int InsideIndex;
	flat int OutsideIndex;
	smooth vec4 Color;
	smooth vec2 Texcoord;
} Fragment;

layout(location = 0, index = 0) out vec4 Color;

void main (void)  
{
	int S = int(Fragment.Texcoord.s);
	int T = int(Fragment.Texcoord.t);
	float InsideFactor = texelFetch(Texture, Fragment.InsideIndex + S + T * Fragment.Pitch).r;
	float OutsideFactor = texelFetch(Texture, Fragment.OutsideIndex + S + T * Fragment.Pitch).r;
	Color = mix(Fragment.BorderColor, Fragment.Color, InsideFactor);
	Color.a *= OutsideFactor;
}
