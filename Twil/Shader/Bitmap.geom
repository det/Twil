#version 330

layout(points) in;
layout(triangle_strip, max_vertices=4) out;

in GeometryT
{
	vec2 PositionMin;
	vec2 PositionMax;
	vec2 TextureMin;
	vec2 TextureMax;
	int Pitch;
	int Offset;
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
	Fragment.Pitch = Geometry[0].Pitch;
	Fragment.Offset = Geometry[0].Offset;
	Fragment.Texcoord = vec2(Geometry[0].TextureMin.x, Geometry[0].TextureMin.y);
	EmitVertex();

	gl_Position = vec4(Geometry[0].PositionMax.x, Geometry[0].PositionMin.y, 0, 1);
	Fragment.Pitch = Geometry[0].Pitch;
	Fragment.Offset = Geometry[0].Offset;
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
