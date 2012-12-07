#version 330

layout(points) in;
layout(triangle_strip, max_vertices=4) out;

in GeometryData {
	flat vec4 BorderColor;
	flat vec4 TopColor;
	flat vec4 BottomColor;
	flat int InsideOffset;
	flat int OutsideOffset;
	flat vec4 Position;
	flat vec2 PositionSize;
	flat ivec2 Size;
} Geometry[];

out FragmentData {
	flat vec4 BorderColor;
	flat int InsideOffset;
	flat int OutsideOffset;
	flat ivec2 Size;
	smooth vec2 Texcoord;
	smooth vec4 Color;
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
	Fragment.Color = Geometry[0].BottomColor;
	EmitVertex();

	gl_Position = vec4(PosX + PosWidth, PosY, PosZ, PosW);
	Fragment.Texcoord = vec2(TexX + TexWidth, TexY);
	Fragment.Color = Geometry[0].BottomColor;
	EmitVertex();

	gl_Position = vec4(PosX, PosY + PosHeight, PosZ, PosW);
	Fragment.BorderColor = Geometry[0].BorderColor;
	Fragment.InsideOffset = Geometry[0].InsideOffset;
	Fragment.OutsideOffset = Geometry[0].OutsideOffset;
	Fragment.Texcoord = vec2(TexX, TexY + TexHeight);
	Fragment.Size = Geometry[0].Size;
	Fragment.Color = Geometry[0].TopColor;
	EmitVertex();

	gl_Position = vec4(PosX + PosWidth, PosY + PosHeight, PosZ, PosW);
	Fragment.BorderColor = Geometry[0].BorderColor;
	Fragment.InsideOffset = Geometry[0].InsideOffset;
	Fragment.OutsideOffset = Geometry[0].OutsideOffset;
	Fragment.Texcoord = vec2(TexX + TexWidth, TexY + TexHeight);
	Fragment.Size = Geometry[0].Size;
	Fragment.Color = Geometry[0].TopColor;
	EmitVertex();
}
