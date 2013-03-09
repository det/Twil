#pragma once

#include "Application.hpp"
#include "Container.hpp"
#include "Event.hpp"
#include "KeyboardHandler.hpp"
#include "MouseHandler.hpp"
#include "WindowBase.hpp"
#include "Gl/Context.hpp"
#include "Theme/Manager.hpp"

namespace Twil {
namespace Ui {

/// \brief A resizable window that holds a single child widget.
/// \param T The type of the child widget.
template <typename T>
class WindowT :
	public Platform::WindowT,
	public WindowBaseT,
	public ContainerT,
	public KeyboardHandlerT,
	public MouseHandlerT
{
	private:
	Theme::ManagerT mManager;
	T mChild;
	unsigned short mWidth = 0;
	unsigned short mHeight = 0;
	bool mIsFullscreen = false;

	// Non-copyable
	WindowT(WindowT const &) = delete;
	WindowT & operator=(WindowT const &) = delete;

	public:
	// Window
	EventT<> Deleted;

	WindowT(Platform::ApplicationT & Application) :
		Platform::WindowT{Application}
	{}

	void init()
	{
		mKeyboardHandler = this;
		mMouseHandler = this;
		mChild.init(*this, *this, mManager);
	}

	/// \brief Toggle the fullscreen status of the window.
	void toggleFullscreen()
	{
		mIsFullscreen = !mIsFullscreen;
		setFullscreen(mIsFullscreen);
	}

	/// \returns The width.
	unsigned short getWidth()
	{
		return mWidth;
	}

	/// \returns The height.
	unsigned short getHeight()
	{
		return mHeight;
	}

	/// \returns A reference to the child.
	T & getChild()
	{
		return mChild;
	}

	/// \returns A const reference to the child.
	T const & getChild() const
	{
		return mChild;
	}

	// Window
	void handleExposed()
	{
		mNeedsDraw = true;
	}

	void handleDeleted()
	{
		Deleted();
	}

	void handleResize(unsigned short Width, unsigned short Height)
	{
		mWidth = Width;
		mHeight = Height;
		auto ChildWidth = mChild.getRight();
		auto ChildHeight = mChild.getTop();
		if (Width != ChildWidth) mChild.resizeWidth(mWidth - ChildWidth);
		if (Height != ChildHeight) mChild.resizeHeight(mHeight - ChildHeight);
		mNeedsDraw = true;
	}

	void update()
	{
		if (mNeedsDraw) {
			mManager.draw(mWidth, mHeight);
			swapBuffers();
			mNeedsDraw = false;
		}
	}

	// Container
	void releaseMouse(signed short, signed short) final
	{
		setMouseHandler(*this);
	}

	void handleChildBaseWidthChanged(void *) final
	{}

	void handleChildBaseHeightChanged(void *) final
	{}

	// MouseHandler
	void handleMouseEnterWindow(signed short X, signed short Y) final
	{
		mChild.delegateMouse(X, Y);
	}

	void handleMouseMotion(signed short X, signed short Y) final
	{
		if (X >= 0 && X <= mWidth && Y >= 0 && Y <= mHeight) mChild.delegateMouse(X, Y);
	}
};

}
}
