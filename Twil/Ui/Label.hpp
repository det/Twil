#pragma once

#include "Container.hpp"
#include "MouseHandler.hpp"
#include "WindowBase.hpp"
#include "Theme/Label.hpp"

#include <string>

namespace Twil {

namespace Theme {
class ManagerT;
}

namespace Ui {

/// \brief A Widget that draws text on the screen.
/// \param LayoutT A layout class used for positioning and clipping.
template<typename LayoutT>
class LabelT
:
	public MouseHandlerT
{
	LabelT(LabelT const &) = delete;
	LabelT & operator =(LabelT const &) = delete;

private:
	ContainerT * mParent;
	WindowBaseT * mWindow;
	LayoutT mLayout;
	Theme::LabelT mThemeLabel;
	std::u32string mText;

private:
	void layoutX()
	{
		std::int16_t Delta = mLayout.getLayoutLeft(getBaseWidth()) - mThemeLabel.getLeft();
		mThemeLabel.moveX(Delta);
		mThemeLabel.setClipLeft(mLayout.getLayoutClipLeft());
		mThemeLabel.setClipRight(mLayout.getLayoutClipRight());
	}

	void layoutY()
	{
		std::int16_t Delta = mLayout.getLayoutBottom(getBaseHeight()) - mThemeLabel.getBottom();
		mThemeLabel.moveY(Delta);
		mThemeLabel.setClipBottom(mLayout.getLayoutClipBottom());
		mThemeLabel.setClipTop(mLayout.getLayoutClipTop());
	}

	bool checkThisContains(std::int16_t X, std::int16_t Y)
	{
		return (
			X >= getLeft() && X >= getClipLeft() &&
			X <= getRight() && X <= getClipRight() &&
			Y >= getBottom() && Y >= getClipBottom() &&
			Y <= getTop() && Y <= getClipTop());
	}

public:
	// Label
	LabelT() = default;

	void init(ContainerT & Parent, WindowBaseT & Window)
	{
		mParent = &Parent;
		mWindow = &Window;
		mThemeLabel.init(Window.getThemeManager());
	}

	/// \brief Set the text that the label displays.
	void setText(std::u32string const & Text)
	{
		mText = Text;
		mThemeLabel.setText(Text);
		layoutX();
		mParent->handleChildBaseWidthChanged(this);
	}

	// Widget
	void moveX(std::int16_t X)
	{
		mLayout.moveX(X);
		mThemeLabel.moveX(X);
	}

	void moveY(std::int16_t Y)
	{
		mLayout.moveY(Y);
		mThemeLabel.moveY(Y);
	}

	void resizeWidth(std::int16_t X)
	{
		mLayout.resizeWidth(X);
		layoutX();
	}

	void resizeHeight(std::int16_t Y)
	{
		mLayout.resizeHeight(Y);
		layoutY();
	}

	void setClipLeft(std::int16_t X)
	{
		mLayout.setClipLeft(X);
		mThemeLabel.setClipLeft(mLayout.getLayoutClipLeft());
	}

	void setClipRight(std::int16_t X)
	{
		mLayout.setClipRight(X);
		mThemeLabel.setClipRight(mLayout.getLayoutClipRight());
	}

	void setClipBottom(std::int16_t Y)
	{
		mLayout.setClipBottom(Y);
		mThemeLabel.setClipBottom(mLayout.getLayoutClipBottom());
	}

	void setClipTop(std::int16_t Y)
	{
		mLayout.setClipTop(Y);
		mThemeLabel.setClipTop(mLayout.getLayoutClipTop());
	}

	std::int16_t getLeft() const
	{
		return mLayout.getLeft();
	}

	std::int16_t getBottom() const
	{
		return mLayout.getBottom();
	}

	std::int16_t getRight() const
	{
		return mLayout.getRight();
	}

	std::int16_t getTop() const
	{
		return mLayout.getTop();
	}

	std::int16_t getClipLeft() const
	{
		return mLayout.getClipLeft();
	}

	std::int16_t getClipBottom() const
	{
		return mLayout.getClipBottom();
	}

	std::int16_t getClipRight() const
	{
		return mLayout.getClipRight();
	}

	std::int16_t getClipTop() const
	{
		return mLayout.getClipTop();
	}

	std::int16_t getBaseWidth() const
	{
		return mThemeLabel.getBaseWidth();
	}

	std::int16_t getBaseHeight() const
	{
		return mThemeLabel.getBaseHeight();
	}

	void delegateMouse(std::int16_t, std::int16_t)
	{
		mWindow->getMouseManager().setHandler(*this);
	}

	// MouseHandler
	void handleMouseMotion(std::int16_t X, std::int16_t Y) final
	{
		if (!checkThisContains(X, Y)) mParent->releaseMouse(X, Y);
	}
};

}
}
