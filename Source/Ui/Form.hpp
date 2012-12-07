#pragma once

#include "Math/Vector2.hpp"
#include "Ui/Widget.hpp"

namespace Twil {
namespace Ui {

class WindowControl;

template<typename T>
class Form : public Widget {
	private:
	T mChild;

	public:
	T & getChild();

	Form(Ui::WindowControl &);
	virtual void handleResized(Math::Vector2 const &);
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
void Form<T>::handleResized(Math::Vector2 const & Size)
{
	mChild.GetWidget().Resize(Size);
}

template<typename T>
void Form<T>::draw()
{
	mChild.GetWidget().Draw();
}

template<typename T>
void Form<T>::handleMouseEnter(int X, int Y)
{
	mChild.GetWidget().OnMouseEnter(X, Y);
}

template<typename T>
void Form<T>::handleMouseLeave(int X, int Y)
{
	mChild.GetWidget().OnMouseLeave(X, Y);
}

template<typename T>
void Form<T>::handleMouseMotion(int X, int Y)
{
	mChild.GetWidget().OnMouseMotion(X, Y);
}

template<typename T>
void Form<T>::handleButtonPressed(int X, int Y, unsigned Button)
{
	mChild.GetWidget().OnButtonPressed(X, Y, Button);
}

template<typename T>
void Form<T>::handleButtonReleased(int X, int Y, unsigned Button)
{
	mChild.GetWidget().OnButtonReleased(X, Y, Button);
}

template<typename T>
void Form<T>::handleKeyPressed(Platform::Key Key)
{
	mChild.GetWidget().OnKeyPressed(Key);
}

template<typename T>
void Form<T>::handleKeyReleased(Platform::Key Key)
{
	mChild.GetWidget().OnKeyReleased(Key);
}

}
}
