#pragma once

#include "Ui/Widget.hpp"

namespace Twil {
namespace Ui {

class WindowControl;

template<typename T>
class Form : public Widget
{
	private:
	T mChild;

	public:
	T & getChild();

	Form(Ui::WindowControl &);
	virtual void handleResized(unsigned short, unsigned short);
	virtual void handleMoved(signed short, signed short);
	virtual void draw();
	virtual void handleMouseEnter(int, int);
	virtual void handleMouseLeave(int, int);
	virtual void handleMouseMotion(int, int);
	virtual void handleButtonPressed(int, int, unsigned);
	virtual void handleButtonReleased(int, int, unsigned);
	virtual void handleKeyPressed(Platform::Key);
	virtual void handleKeyReleased(Platform::Key);
};

template<typename T>
T & Form<T>::getChild()
{
	return mChild;
}

template<typename T>
Form<T>::Form(Ui::WindowControl & Control) :
	T{Control}
{
}


template<typename T>
void Form<T>::handleResized(unsigned short Width, unsigned short Height)
{
	mChild.GetWidget().handleResized(Width, Height);
}

template<typename T>
void Form<T>::handleMoved(signed short X, signed short Y)
{
	mChild.GetWidget().handleMoved(X, Y);
}

template<typename T>
void Form<T>::draw()
{
	mChild.GetWidget().draw();
}

template<typename T>
void Form<T>::handleMouseEnter(int X, int Y)
{
	mChild.GetWidget().handleMouseEnter(X, Y);
}

template<typename T>
void Form<T>::handleMouseLeave(int X, int Y)
{
	mChild.GetWidget().handleMouseLeave(X, Y);
}

template<typename T>
void Form<T>::handleMouseMotion(int X, int Y)
{
	mChild.GetWidget().handleMouseMotion(X, Y);
}

template<typename T>
void Form<T>::handleButtonPressed(int X, int Y, unsigned Button)
{
	mChild.GetWidget().handleButtonPressed(X, Y, Button);
}

template<typename T>
void Form<T>::handleButtonReleased(int X, int Y, unsigned Button)
{
	mChild.GetWidget().handleButtonReleased(X, Y, Button);
}

template<typename T>
void Form<T>::handleKeyPressed(Platform::Key Key)
{
	mChild.GetWidget().handleKeyPressed(Key);
}

template<typename T>
void Form<T>::handleKeyReleased(Platform::Key Key)
{
	mChild.GetWidget().handleKeyReleased(Key);
}

}
}
