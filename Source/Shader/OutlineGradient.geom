#version 330

layout(points) in;
layout(triangle_strip, max_vertices=4) out;

in GeometryData
{
	flat vec4 BorderColor;
	flat vec4 BottomColor;
	flat vec4 TopColor;
	flat vec2 PositionMin;
	flat vec2 PositionMax;
	flat vec2 TextureMin;
	flat vec2 TextureMax;
	flat int Pitch;
	flat int InsideIndex;
	flat int OutsideIndex;
} Geometry[];

out FragmentData
{
	flat vec4 BorderColor;
	flat int Pitch;
	flat int InsideIndex;
	flat int OutsideIndex;
	smooth vec4 Color;
	smooth vec2 Texcoord;
} Fragment;

void main()
{
	gl_Position = vec4(Geometry[0].PositionMin.x, Geometry[0].PositionMin.y, 0, 1);
	Fragment.Color = Geometry[0].BottomColor;
	Fragment.Texcoord = vec2(Geometry[0].TextureMin.x, Geometry[0].TextureMin.y);
	EmitVertex();

	gl_Position = vec4(Geometry[0].PositionMax.x, Geometry[0].PositionMin.y, 0, 1);
	Fragment.Color = Geometry[0].BottomColor;
	Fragment.Texcoord = vec2(Geometry[0].TextureMax.x, Geometry[0].TextureMin.y);
	EmitVertex();

	gl_Position = vec4(Geometry[0].PositionMin.x, Geometry[0].PositionMax.y, 0, 1);
	Fragment.Pitch = Geometry[0].Pitch;
	Fragment.BorderColor = Geometry[0].BorderColor;
	Fragment.InsideIndex = Geometry[0].InsideIndex;
	Fragment.OutsideIndex = Geometry[0].OutsideIndex;
	Fragment.Color = Geometry[0].TopColor;
	Fragment.Texcoord = vec2(Geometry[0].TextureMin.x, Geometry[0].TextureMax.y);
	EmitVertex();

	gl_Position = vec4(Geometry[0].PositionMax.x, Geometry[0].PositionMax.y, 0, 1);
	Fragment.BorderColor = Geometry[0].BorderColor;
	Fragment.Pitch = Geometry[0].Pitch;
	Fragment.InsideIndex = Geometry[0].InsideIndex;
	Fragment.OutsideIndex = Geometry[0].OutsideIndex;
	Fragment.Color = Geometry[0].TopColor;
	Fragment.Texcoord = vec2(Geometry[0].TextureMax.x, Geometry[0].TextureMax.y);
	EmitVertex();
}
