#pragma once

#include "Application.hpp"
#include "Container.hpp"
#include "KeyboardHandler.hpp"
#include "MouseHandler.hpp"
#include "WindowBase.hpp"
#include "Data/Event.hpp"
#include "Gl/Context.hpp"


namespace Twil {
namespace Ui {

/// \brief A resizable window that holds a single child widget.
/// \param T The type of the child widget.
template <typename T>
class WindowT
:
	public ContainerT,
	public KeyboardHandlerT,
	public MouseHandlerT
{
	WindowT(WindowT const &) = delete;
	WindowT & operator =(WindowT const &) = delete;

private:
	Platform::WindowT mPlatformWindow;
	WindowBaseT mBase;

	T mChild;
	bool mIsFullscreen = false;

	bool checkChildContains(std::int16_t X, std::int16_t Y)
	{
		return X >= 0 && X <= mChild.getRight() && Y >= 0 && Y <= mChild.getTop();
	}

public:
	// Window
	Data::EventT<> Deleted;

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
	void resize(std::uint16_t Width, std::uint16_t Height)
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
	std::uint16_t getWidth() const
	{
		return mChild.getRight();
	}

	/// \returns The height.
	std::uint16_t getHeight() const
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

	void handleResize(std::uint16_t Width, std::uint16_t Height)
	{
		if (Width != getWidth()) mChild.resizeWidth(Width - getWidth());
		if (Height != getHeight()) mChild.resizeHeight(Height - getHeight());
	}

	void update()
	{
		if (getThemeManager().update(getWidth(), getHeight())) mPlatformWindow.swapBuffers();
	}

	// Container
	void releaseMouse(std::int16_t, std::int16_t) final
	{
		getMouseManager().setHandler(*this);
	}

	void handleChildBaseWidthChanged(void *) final
	{}

	void handleChildBaseHeightChanged(void *) final
	{}

	// MouseHandler
	void handleMouseMotion(std::int16_t X, std::int16_t Y) final
	{
		if (checkChildContains(X, Y)) mChild.delegateMouse(X, Y);
	}
};

}
}
