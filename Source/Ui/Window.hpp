#pragma once

#include "Application.hpp"
#include "Container.hpp"
#include "Event.hpp"
#include "KeyboardHandler.hpp"
#include "KeyboardManager.hpp"
#include "MouseHandler.hpp"
#include "MouseManager.hpp"
#include "Gl/Context.hpp"
#include "Theme/Manager.hpp"

namespace Twil {
namespace Ui {

/// \brief A resizable window that holds a single child widget.
/// \param T The type of the child widget.
template <typename T>
class WindowT :
	public ContainerT,
	public KeyboardHandlerT,
	public MouseHandlerT
{
	private:
	Platform::WindowT mPlatformWindow;
	Theme::ManagerT mThemeManager;
	KeyboardManagerT mKeyboardManager;
	MouseManagerT mMouseManager;
	T mChild;
	bool mIsFullscreen = false;

	// Non-copyable
	WindowT(WindowT const &) = delete;
	WindowT & operator=(WindowT const &) = delete;

	bool checkChildContains(signed short X, signed short Y)
	{
		return X >= 0 && X <= mChild.getRight() && Y >= 0 && Y <= mChild.getTop();
	}

	public:
	// Window
	EventT<> Deleted;

	WindowT(Platform::ApplicationT & Application) :
		mPlatformWindow{Application}
	{}

	void init()
	{
		mMouseManager.setHandler(*this);
		mKeyboardManager.setHandler(*this);
		mChild.init(*this, mThemeManager);
	}

	MouseManagerT & getMouseManager()
	{
		return mMouseManager;
	}

	KeyboardManagerT & getKeyboardManager()
	{
		return mKeyboardManager;
	}

	/// \brief Show the window.
	void show()
	{
		mPlatformWindow.show();
	}

	/// \brief Hide the window.
	void hide()
	{
		mPlatformWindow.hide();
	}

	/// \brief Set whether the window is fullscreen.
	void setFullscreen(bool IsFullScreen)
	{
		mPlatformWindow.setFullscreen(IsFullScreen);
	}

	/// \brief Resize the window.
	void resize(unsigned short Width, unsigned short Height)
	{
		mPlatformWindow.resize(Width, Height);
	}

	/// \brief Set the title.
	void setTitle(char const * String)
	{
		mPlatformWindow.setTitle(String);
	}

	/// \brief Toggle the fullscreen status of the window.
	void toggleFullscreen()
	{
		mIsFullscreen = !mIsFullscreen;
		setFullscreen(mIsFullscreen);
	}

	/// \returns The width.
	unsigned short getWidth() const
	{
		return mChild.getRight();
	}

	/// \returns The height.
	unsigned short getHeight() const
	{
		return mChild.getTop();
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

	void handleExposed()
	{
		mThemeManager.markNeedsRedraw();
	}

	void handleDeleted()
	{
		Deleted();
	}

	void handleResize(unsigned short Width, unsigned short Height)
	{
		if (Width != getWidth()) mChild.resizeWidth(Width - getWidth());
		if (Height != getHeight()) mChild.resizeHeight(Height - getHeight());
	}

	void update()
	{
		if (mThemeManager.update(getWidth(), getHeight())) mPlatformWindow.swapBuffers();
	}

	// Container
	void releaseMouse(MouseManagerT & Manager, signed short, signed short) final
	{
		Manager.setHandler(*this);
	}

	void handleChildBaseWidthChanged(void *) final
	{}

	void handleChildBaseHeightChanged(void *) final
	{}

	// MouseHandler
	void handleMouseMotion(MouseManagerT & Manager, signed short X, signed short Y) final
	{
		if (checkChildContains(X, Y)) mChild.delegateMouse(Manager, X, Y);
	}
};

}
}
