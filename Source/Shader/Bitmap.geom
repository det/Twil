#version 330

layout(points) in;
layout(triangle_strip, max_vertices=4) out;

in GeometryT
{
	flat vec2 PositionMin;
	flat vec2 PositionMax;
	flat vec2 TextureMin;
	flat vec2 TextureMax;
	flat int Pitch;
	flat int Offset;
} Geometry[];

out FragmentT
{
	flat int Pitch;
	flat int Offset;
	smooth vec2 Texcoord;
} Fragment;

void main()
{
	gl_Position = vec4(Geometry[0].PositionMin.x, Geometry[0].PositionMin.y, 0, 1);
	Fragment.Texcoord = vec2(Geometry[0].TextureMin.x, Geometry[0].TextureMin.y);
	EmitVertex();

	gl_Position = vec4(Geometry[0].PositionMax.x, Geometry[0].PositionMin.y, 0, 1);
	Fragment.Texcoord = vec2(Geometry[0].TextureMax.x, Geometry[0].TextureMin.y);
	EmitVertex();

	gl_Position = vec4(Geometry[0].PositionMin.x, Geometry[0].PositionMax.y, 0, 1);
	Fragment.Pitch = Geometry[0].Pitch;
	Fragment.Offset = Geometry[0].Offset;
	Fragment.Texcoord = vec2(Geometry[0].TextureMin.x, Geometry[0].TextureMax.y);
	EmitVertex();

	gl_Position = vec4(Geometry[0].PositionMax.x, Geometry[0].PositionMax.y, 0, 1);
	Fragment.Pitch = Geometry[0].Pitch;
	Fragment.Offset = Geometry[0].Offset;
	Fragment.Texcoord = vec2(Geometry[0].TextureMax.x, Geometry[0].TextureMax.y);
	EmitVertex();
}
