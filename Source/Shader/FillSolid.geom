#version 330

layout(points) in;
layout(triangle_strip, max_vertices=4) out;

in GeometryData {
	flat vec4 Color;
	flat vec4 Position;
	flat vec2 PositionSize;
	flat ivec2 Size;
	flat int Offset;
} Geometry[];

out FragmentData {
	flat vec4 Color;
	flat int Offset;
	flat ivec2 Size;
	smooth vec2 Texcoord;
} Fragment;

void main()
{
	float PosX = Geometry[0].Position.x;
	float PosY = Geometry[0].Position.y;
	float PosZ = Geometry[0].Position.z;
	float PosW = Geometry[0].Position.w;
	float PosWidth = Geometry[0].PositionSize.x;
	float PosHeight = Geometry[0].PositionSize.y;
	float TexX = 0.0;
	float TexY = 0.0;
	float TexWidth = Geometry[0].Size.x;
	float TexHeight = Geometry[0].Size.y;

	gl_Position = vec4(PosX, PosY, PosZ, PosW);
	Fragment.Texcoord = vec2(TexX, TexY);
	EmitVertex();

	gl_Position = vec4(PosX + PosWidth, PosY, PosZ, PosW);
	Fragment.Texcoord = vec2(TexX + TexWidth, TexY);
	EmitVertex();

	gl_Position = vec4(PosX, PosY + PosHeight, PosZ, PosW);
	Fragment.Color = Geometry[0].Color;
	Fragment.Texcoord = vec2(TexX, TexY + TexHeight);
	Fragment.Offset = Geometry[0].Offset;
	Fragment.Size = Geometry[0].Size;
	EmitVertex();

	gl_Position = vec4(PosX + PosWidth, PosY + PosHeight, PosZ, PosW);
	Fragment.Color = Geometry[0].Color;
	Fragment.Texcoord = vec2(TexX + TexWidth, TexY + TexHeight);
	Fragment.Offset = Geometry[0].Offset;
	Fragment.Size = Geometry[0].Size;
	EmitVertex();
}
