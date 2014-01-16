#pragma once

#include "Application.hpp"
#include "Container.hpp"
#include "KeyboardHandler.hpp"
#include "MouseHandler.hpp"
#include "WindowBase.hpp"
#include "Data/Event.hpp"
#include "Gl/Context.hpp"
#include "Theme/Settings.hpp"

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
	std::int16_t mPixelWidth;
	std::int16_t mPixelHeight;

	T mChild;
	bool mIsFullscreen = false;

	bool checkChildContains(float X, float Y)
	{
		return X >= 0 && X <= mChild.getRight() && Y >= 0 && Y <= mChild.getTop();
	}

public:
	// Window
	Data::EventT<> Deleted;

	WindowT(Platform::ApplicationT & Application) :
		mPlatformWindow{
			Application,
			static_cast<std::int16_t>(320 * Theme::Settings::Global::HorizontalScale),
			static_cast<std::int16_t>(240 * Theme::Settings::Global::VerticalScale)}
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
		mPlatformWindow.resize(
			getThemeManager().fitHorizontalGrid(Width),
			getThemeManager().fitVerticalGrid(Height));
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

	std::int16_t getPixelWidth()
	{
		return mPixelWidth;
	}

	std::int16_t getPixelHeight()
	{
		return mPixelHeight;
	}


	/// \returns The width.
	float getWidth() const
	{
		return mChild.getRight();
	}

	/// \returns The height.
	float getHeight() const
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

	void onMouseEnterWindow(std::int16_t X, std::int16_t Y)
	{
		getMouseManager().handleMouseEnterWindow(
			X / Theme::Settings::Global::HorizontalScale,
			Y / Theme::Settings::Global::VerticalScale);
	}

	void onMouseLeaveWindow(std::int16_t X, std::int16_t Y)
	{
		getMouseManager().handleMouseLeaveWindow(
			X / Theme::Settings::Global::HorizontalScale,
			Y / Theme::Settings::Global::VerticalScale);
	}

	void onMouseMotion(std::int16_t X, std::int16_t Y)
	{
		getMouseManager().handleMouseMotion(
			X / Theme::Settings::Global::HorizontalScale,
			Y / Theme::Settings::Global::VerticalScale);
	}

	void onButtonPress(std::int16_t X, std::int16_t Y, std::int8_t Button)
	{
		getMouseManager().handleButtonPress(
			X / Theme::Settings::Global::HorizontalScale,
			Y / Theme::Settings::Global::VerticalScale,
			Button);
	}

	void onButtonRelease(std::int16_t X, std::int16_t Y, std::int8_t Button)
	{
		getMouseManager().handleButtonRelease(
			X / Theme::Settings::Global::HorizontalScale,
			Y / Theme::Settings::Global::VerticalScale,
			Button);
	}

	void onExposed()
	{
		getThemeManager().markNeedsRedraw();
	}


	void onDeleted()
	{
		Deleted();
	}

	void onResize(std::int16_t Width, std::int16_t Height)
	{
		if (Width != mPixelWidth)
		{
			mPixelWidth = Width;
			mChild.resizeWidth(Width / Theme::Settings::Global::HorizontalScale - getWidth());
		}

		if (Height != mPixelHeight)
		{
			mPixelHeight = Height;
			mChild.resizeHeight(Height / Theme::Settings::Global::VerticalScale - getHeight());
		}

	}

	void update()
	{
		auto b = getThemeManager().update(
			getWidth() * Theme::Settings::Global::HorizontalScale,
			getHeight() * Theme::Settings::Global::VerticalScale);
		if (b) mPlatformWindow.swapBuffers();
	}

	// Container
	void releaseMouse(float, float) final
	{
		getMouseManager().setHandler(*this);
	}

	void handleChildBaseWidthChanged(void *) final
	{}

	void handleChildBaseHeightChanged(void *) final
	{}

	// MouseHandler
	void handleMouseMotion(float X, float Y) final
	{
		if (checkChildContains(X, Y)) mChild.delegateMouse(X, Y);
	}
};

}
}
