#include "ui/application.hpp"
#include "ui/button.hpp"
#include "ui/centered.hpp"
#include "ui/grid.hpp"
#include "ui/image.hpp"
#include "ui/label.hpp"
#include "ui/margin.hpp"
#include "ui/partition_box.hpp"
#include "ui/split_box.hpp"
#include "ui/unit.hpp"
#include "ui/window.hpp"

#include <iostream>

using namespace twil::ui::udl;

class HelloBase
{
private:
	using Centered = twil::ui::Centered;
	using Image = twil::ui::Image<Centered>;
	using Label = twil::ui::Label<Centered>;
	using ImageButton = twil::ui::Button<Image>;
	using LabelButton = twil::ui::Button<Label>;
	using SpacedImageButton = twil::ui::Margin<4_dip, 4_dip, ImageButton>;
	using SpacedLabelButton = twil::ui::Margin<4_dip, 4_dip, LabelButton>;
	using Grid = twil::ui::Grid<3, 3, SpacedImageButton>;
	using VerticalBox0 = twil::ui::SplitBox<false, false, Grid, SpacedLabelButton>;
	using VerticalBox1 = twil::ui::SplitBox<false, true, Label, VerticalBox0>;
	using Window = twil::ui::Window<twil::ui::Margin<4_dip, 4_dip, VerticalBox1>>;
	using Application = twil::ui::Application<Window>;
	Application application_;

protected:
	Application & GetApplication()
	{
		return application_;
	}

	Application const & GetApplication() const
	{
		return application_;
	}

	Window & GetWindow()
	{
		return GetApplication().GetChild();
	}

	VerticalBox1 & GetVerticalBox1()
	{
		return GetWindow().GetChild().GetChild();
	}

	VerticalBox0 & GetVerticalBox0()
	{
		return GetVerticalBox1().GetSecond();
	}

	Label & GetBottomLabel()
	{
		return GetVerticalBox1().GetFirst();
	}

	template<std::size_t x, std::size_t y>
	ImageButton & GetButton()
	{
		return GetVerticalBox0().GetFirst().GetChild<x, y>().GetChild();
	}

	template<std::size_t x, std::size_t y>
	Image & GetImage()
	{
		return GetButton<x, y>().GetChild();
	}

	LabelButton & GetTopButton()
	{
		return GetVerticalBox0().GetSecond().GetChild();
	}

	Label & GetTopLabel()
	{
		return GetTopButton().GetChild();
	}

	HelloBase()
	{
		GetTopLabel().SetText(U"Top");
		GetImage<0, 0>().SetImage("/usr/share/icons/mate/48x48/mimetypes/text-x-boo.png");
		GetImage<0, 1>().SetImage("/usr/share/icons/mate/48x48/mimetypes/misc.png");
		GetImage<0, 2>().SetImage("/usr/share/icons/mate/48x48/mimetypes/text-x-makefile.png");
		GetImage<1, 0>().SetImage("/usr/share/icons/mate/48x48/mimetypes/vcalendar.png");
		GetImage<1, 1>().SetImage("/usr/share/icons/mate/48x48/mimetypes/x-office-spreadsheet.png");
		GetImage<1, 2>().SetImage("/usr/share/icons/mate/48x48/mimetypes/contents2.png");
		GetImage<2, 0>().SetImage("/usr/share/icons/mate/48x48/mimetypes/video.png");
		GetImage<2, 1>().SetImage("/usr/share/icons/mate/48x48/mimetypes/font_truetype.png");
		GetImage<2, 2>().SetImage("/usr/share/icons/mate/48x48/mimetypes/gnome-mime-text-x-vcalendar.png");
		GetBottomLabel().SetText(U"Bottom");

		GetButton<1, 1>().Clicked += [&]
		{
			GetImage<1, 1>().SetImage("/usr/share/icons/mate/48x48/mimetypes/exec.png");
		};

		GetTopButton().Clicked += [&]
		{
			GetBottomLabel().SetText(U"Clicked!");
		};

		GetWindow().Deleted += [&]
		{
			GetApplication().Stop();
		};

		GetWindow().SetTitle("Hello");
	}
};

using Hello = twil::ui::ApplicationAdaptor<HelloBase>;

int main(void)
{
	Hello Hello;
	Hello.Run();
}
