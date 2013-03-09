#include "Ui/Application.hpp"
#include "Ui/Button.hpp"
#include "Ui/Centered.hpp"
#include "Ui/Image.hpp"
#include "Ui/Label.hpp"
#include "Ui/Margin.hpp"
#include "Ui/PartitionBox.hpp"
#include "Ui/SplitBox.hpp"
#include "Ui/Window.hpp"

#include <iostream>

class HelloT
{
	private:
	using CenteredT = Twil::Ui::CenteredT;
	using ImageT = Twil::Ui::ImageT<CenteredT>;
	using LabelT = Twil::Ui::LabelT<CenteredT>;
	using ImageButtonT = Twil::Ui::ButtonT<ImageT>;
	using LabelButtonT = Twil::Ui::ButtonT<LabelT>;
	using SpacedImageButtonT = Twil::Ui::MarginT<4, 4, ImageButtonT>;
	using SpacedLabelButtonT = Twil::Ui::MarginT<4, 4, LabelButtonT>;
	using ColumnT = Twil::Ui::PartitionBoxT<false, SpacedImageButtonT, SpacedImageButtonT, SpacedImageButtonT>;
	using GridT = Twil::Ui::PartitionBoxT<true, ColumnT, ColumnT, ColumnT>;
	using VerticalBox0T = Twil::Ui::SplitBoxT<false, false, GridT, SpacedLabelButtonT>;
	using VerticalBox1T = Twil::Ui::SplitBoxT<false, true, LabelT, VerticalBox0T>;
	using WindowT = Twil::Ui::WindowT<Twil::Ui::MarginT<16, 16, VerticalBox1T>>;
	using ApplicationT = Twil::Ui::ApplicationT<WindowT>;
	ApplicationT mApplication;

	ApplicationT & getApplication() { return mApplication; }
	WindowT & getWindow() { return getApplication().getChild(); }
	VerticalBox1T & getVerticalBox1() { return getWindow().getChild().getChild(); }
	VerticalBox0T & getVerticalBox0() { return getVerticalBox1().getSecond(); }
	GridT & getGrid() { return getVerticalBox0().getFirst(); }
	ColumnT & getColumn0() { return getGrid().getChild<0>(); }
	ColumnT & getColumn1() { return getGrid().getChild<1>(); }
	ColumnT & getColumn2() { return getGrid().getChild<2>(); }
	ImageButtonT & getButton00() { return getColumn0().getChild<0>().getChild(); }
	ImageButtonT & getButton10() { return getColumn0().getChild<1>().getChild(); }
	ImageButtonT & getButton20() { return getColumn0().getChild<2>().getChild(); }
	ImageButtonT & getButton01() { return getColumn1().getChild<0>().getChild(); }
	ImageButtonT & getButton11() { return getColumn1().getChild<1>().getChild(); }
	ImageButtonT & getButton21() { return getColumn1().getChild<2>().getChild(); }
	ImageButtonT & getButton02() { return getColumn2().getChild<0>().getChild(); }
	ImageButtonT & getButton12() { return getColumn2().getChild<1>().getChild(); }
	ImageButtonT & getButton22() { return getColumn2().getChild<2>().getChild(); }
	LabelButtonT & getTopButton() { return getVerticalBox0().getSecond().getChild(); }
	LabelT & getBottomLabel() { return getVerticalBox1().getFirst(); }
	ImageT & getLabel00() { return getButton00().getChild(); }
	ImageT & getLabel10() { return getButton10().getChild(); }
	ImageT & getLabel20() { return getButton20().getChild(); }
	ImageT & getLabel01() { return getButton01().getChild(); }
	ImageT & getLabel11() { return getButton11().getChild(); }
	ImageT & getLabel21() { return getButton21().getChild(); }
	ImageT & getLabel02() { return getButton02().getChild(); }
	ImageT & getLabel12() { return getButton12().getChild(); }
	ImageT & getLabel22() { return getButton22().getChild(); }
	LabelT & getTopLabel() { return getTopButton().getChild(); }

	public:
	HelloT()
	{
		getBottomLabel().setText(U"Bottom");
		getLabel00().setImage("/usr/share/pixmaps/gnome-debian.png");
		getLabel10().setImage("/usr/share/pixmaps/gnome-irc.png");
		getLabel20().setImage("/usr/share/pixmaps/gnome-talk.png");
		getLabel01().setImage("/usr/share/pixmaps/gnome-windows.png");
		getLabel11().setImage("/usr/share/pixmaps/gnome-about-logo.png");
		getLabel21().setImage("/usr/share/pixmaps/gnome-diskfree.png");
		getLabel02().setImage("/usr/share/pixmaps/gnome-calendar.png");
		getLabel12().setImage("/usr/share/pixmaps/gnome-squeak.png");
		getLabel22().setImage("/usr/share/pixmaps/gnome-gemvt.png");
		getTopLabel().setText(U"Top");
		getButton00().Clicked += [&]() { getLabel00().setImage("/usr/share/pixmaps/gksu.png"); };
		getWindow().Deleted += [&]() { getApplication().stop(); };
		getWindow().setTitle("Hello");
	}

	void run()
	{
		getApplication().run();
	}
};

int main(void)
{
	HelloT Hello;
	Hello.run();
}
