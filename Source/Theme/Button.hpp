#pragma once

#include "Vertex/OutlineGradient.hpp"

#include <vector>

namespace Twil {
namespace Theme {

class Manager;

class Button
{
	private:
	Theme::Manager & mManager;
	std::vector<Vertex::OutlineGradient> mVertices;
	signed short mX = 0;
	signed short mY = 0;
	unsigned short mWidth = 0;
	unsigned short mHeight = 0;
	bool mIsDown = false;

	public:
	Button(Theme::Manager &);
	void setIsDown(bool);
	void render();

	void setX(signed short);
	void setY(signed short);
	void setHeight(unsigned short);
	void setWidth(unsigned short);
	signed short getX();
	signed short getY();
	unsigned short getWidth();
	unsigned short getHeight();

	short getChildX();
	short getChildY();
	unsigned short getChildWidth();
	unsigned short getChildHeight();
	unsigned short getFitWidth(unsigned short);
	unsigned short getFitHeight(unsigned short);
};

}
}
