#pragma once

#include "Application.hpp"
#include "Container.hpp"
#include "Event.hpp"
#include "KeyboardHandler.hpp"
#include "MouseHandler.hpp"
#include "WindowBase.hpp"
#include "Gl/Context.hpp"


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
	WindowBaseT mBase;
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
		getMouseManager().setHandler(*this);
		getKeyboardManager().setHandler(*this);
		mChild.init(*this, mBase);
	}

	/// \returns The mouse manager
	MouseManagerT & getMouseManager()
	{
		return mBase.getMouseManager();
	}

	/// \returns The keyboard manager
	KeyboardManagerT & getKeyboardManager()
	{
		return mBase.getKeyboardManager();
	}

	/// \returns The theme manager
	Theme::ManagerT & getThemeManager()
	{
		return mBase.getThemeManager();
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
		getThemeManager().markNeedsRedraw();
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
		if (getThemeManager().update(getWidth(), getHeight())) mPlatformWindow.swapBuffers();
	}

	// Container
	void releaseMouse(signed short, signed short) final
	{
		getMouseManager().setHandler(*this);
	}

	void handleChildBaseWidthChanged(void *) final
	{}

	void handleChildBaseHeightChanged(void *) final
	{}

	// MouseHandler
	void handleMouseMotion(signed short X, signed short Y) final
	{
		if (checkChildContains(X, Y)) mChild.delegateMouse(X, Y);
	}
};

}
}
