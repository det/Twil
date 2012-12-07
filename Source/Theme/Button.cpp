#include "Theme/Button.hpp"

#include "Theme/Manager.hpp"

namespace Twil {
namespace Theme {

Button::Button(Theme::Manager & Manager) :
	mManager{Manager}
{}

void Button::update(unsigned short Width, unsigned short Height, bool IsPressed)
{
	mVertices.clear();

	GLshort Middle = 5;
	GLshort Left = 0;
	GLshort Right = Width - 5;
	GLshort Bottom = 0;
	GLshort Top = Height - Middle;
	GLushort ScaleX = Width - 10;
	GLushort ScaleY = Height - 10;

	Attribute::Color4b Color1;
	Attribute::Color4b Color2;

	if (IsPressed) {
		Color1 =  {191, 191, 191, 255};
		Color2 = {111, 111, 111, 255};
	}
	else {
		Color1 =  {255, 255, 255, 255};
		Color2 = {159, 159, 159, 255};
	}

	Attribute::Color4b TopColor1 = mix(Color2, Color1, Height, Height - 1);
	Attribute::Color4b TopColor2 = mix(Color2, Color1, Height, Height - 4);
	Attribute::Color4b BottomColor2 = mix(Color2, Color1, Height, 4);
	Attribute::Color4b BottomColor1 = mix(Color2, Color1, Height, 1);
	Attribute::Color4b BorderColor{127, 127, 127, 255};

	Vertex::OutlineGradient Vertex;

	Vertex.TopColor = BottomColor2;
	Vertex.BottomColor = BottomColor1;
	Vertex.BorderColor = BorderColor;
	Vertex.InsideOffset = {mManager.mButtonSwInside};
	Vertex.OutsideOffset = {mManager.mButtonSwOutside};
	Vertex.Position = {Left, Bottom};
	Vertex.Size = {5, 5};
	Vertex.Scale = {1, 1};
	mVertices.push_back(Vertex);

	Vertex.TopColor = BottomColor2;
	Vertex.BottomColor = BottomColor1;
	Vertex.BorderColor = BorderColor;
	Vertex.InsideOffset = {mManager.mButtonSeInside};
	Vertex.OutsideOffset = {mManager.mButtonSeOutside};
	Vertex.Position = {Right, Bottom};
	Vertex.Size = {5, 5};
	Vertex.Scale = {1, 1};
	mVertices.push_back(Vertex);

	Vertex.TopColor = TopColor1;
	Vertex.BottomColor = TopColor2;
	Vertex.BorderColor = BorderColor;
	Vertex.InsideOffset = {mManager.mButtonNeInside};
	Vertex.OutsideOffset = {mManager.mButtonNeOutside};
	Vertex.Position = {Right, Top};
	Vertex.Size = {5, 5};
	Vertex.Scale = {1, 1};
	mVertices.push_back(Vertex);

	Vertex.TopColor = TopColor1;
	Vertex.BottomColor = TopColor2;
	Vertex.BorderColor = BorderColor;
	Vertex.InsideOffset = {mManager.mButtonNwInside};
	Vertex.OutsideOffset = {mManager.mButtonNwOutside};
	Vertex.Position = {Left, Top};
	Vertex.Size = {5, 5};
	Vertex.Scale = {1, 1};
	mVertices.push_back(Vertex);

	Vertex.TopColor = BottomColor2;
	Vertex.BottomColor = BottomColor1;
	Vertex.BorderColor = BorderColor;
	Vertex.InsideOffset = {mManager.mButtonBottomInside};
	Vertex.OutsideOffset = {mManager.mButtonBottomOutside};
	Vertex.Position = {Middle, Bottom};
	Vertex.Size = {1, 5};
	Vertex.Scale = {ScaleX, 1};
	mVertices.push_back(Vertex);

	Vertex.TopColor = TopColor1;
	Vertex.BottomColor = TopColor2;
	Vertex.BorderColor = BorderColor;
	Vertex.InsideOffset = {mManager.mButtonTopInside};
	Vertex.OutsideOffset = {mManager.mButtonTopOutside};
	Vertex.Position = {Middle, Top};
	Vertex.Size = {1, 5};
	Vertex.Scale = {ScaleX, 1};
	mVertices.push_back(Vertex);

	Vertex.TopColor = TopColor2;
	Vertex.BottomColor = BottomColor2;
	Vertex.BorderColor = BorderColor;
	Vertex.InsideOffset = {mManager.mButtonLeftInside};
	Vertex.OutsideOffset = {mManager.mButtonLeftOutside};
	Vertex.Position = {Left, Middle};
	Vertex.Size = {5, 1};
	Vertex.Scale = {1, ScaleY};
	mVertices.push_back(Vertex);

	Vertex.TopColor = TopColor2;
	Vertex.BottomColor = BottomColor2;
	Vertex.BorderColor = BorderColor;
	Vertex.InsideOffset = {mManager.mButtonRightInside};
	Vertex.OutsideOffset = {mManager.mButtonRightOutside};
	Vertex.Position = {Right, Middle};
	Vertex.Size = {5, 1};
	Vertex.Scale = {1, ScaleY};
	mVertices.push_back(Vertex);

	Vertex.TopColor = TopColor2;
	Vertex.BottomColor = BottomColor2;
	Vertex.BorderColor = BorderColor;
	Vertex.InsideOffset = {mManager.mButtonCenterInside};
	Vertex.OutsideOffset = {mManager.mButtonCenterOutside};
	Vertex.Position = {Middle, Middle};
	Vertex.Size = {1, 1};
	Vertex.Scale = {ScaleX, ScaleY};
	mVertices.push_back(Vertex);
}

void Button::render()
{
	mManager.mOutlineArray.add(mVertices);
}

}
}
