#include "Ui/Application.hpp"
#include "Ui/Button.hpp"
#include "Ui/Centered.hpp"
#include "Ui/Dip.hpp"
#include "Ui/Grid.hpp"
#include "Ui/Image.hpp"
#include "Ui/Label.hpp"
#include "Ui/Margin.hpp"
#include "Ui/PartitionBox.hpp"
#include "Ui/SplitBox.hpp"
#include "Ui/Window.hpp"

#include <iostream>

using namespace Twil::Ui::Operator;

class HelloBaseT
{
private:
	using CenteredT = Twil::Ui::CenteredT;
	using ImageT = Twil::Ui::ImageT<CenteredT>;
	using LabelT = Twil::Ui::LabelT<CenteredT>;
	using ImageButtonT = Twil::Ui::ButtonT<ImageT>;
	using LabelButtonT = Twil::Ui::ButtonT<LabelT>;
	using SpacedImageButtonT = Twil::Ui::MarginT<4_dip, 4_dip, ImageButtonT>;
	using SpacedLabelButtonT = Twil::Ui::MarginT<4_dip, 4_dip, LabelButtonT>;
	using GridT = Twil::Ui::GridT<3, 3, SpacedImageButtonT>;
	using VerticalBox0T = Twil::Ui::SplitBoxT<false, false, GridT, SpacedLabelButtonT>;
	using VerticalBox1T = Twil::Ui::SplitBoxT<false, true, LabelT, VerticalBox0T>;
	using WindowT = Twil::Ui::WindowT<Twil::Ui::MarginT<4_dip, 4_dip, VerticalBox1T>>;
	using ApplicationT = Twil::Ui::ApplicationT<WindowT>;
	ApplicationT mApplication;

protected:
	ApplicationT & getApplication()
	{
		return mApplication;
	}

	ApplicationT const & getApplication() const
	{
		return mApplication;
	}

	WindowT & getWindow()
	{
		return getApplication().getChild();
	}

	VerticalBox1T & getVerticalBox1()
	{
		return getWindow().getChild().getChild();
	}

	VerticalBox0T & getVerticalBox0()
	{
		return getVerticalBox1().getSecond();
	}

	LabelT & getBottomLabel()
	{
		return getVerticalBox1().getFirst();
	}

	template<std::size_t X, std::size_t Y>
	ImageButtonT & getButton()
	{
		return getVerticalBox0().getFirst().getChild<X, Y>().getChild();
	}

	template<std::size_t X, std::size_t Y>
	ImageT & getImage()
	{
		return getButton<X, Y>().getChild();
	}

	LabelButtonT & getTopButton()
	{
		return getVerticalBox0().getSecond().getChild();
	}

	LabelT & getTopLabel()
	{
		return getTopButton().getChild();
	}

	HelloBaseT()
	{
		getTopLabel().setText(U"Top");
		getImage<0, 0>().setImage("/usr/share/icons/mate/48x48/mimetypes/text-x-boo.png");
		getImage<0, 1>().setImage("/usr/share/icons/mate/48x48/mimetypes/misc.png");
		getImage<0, 2>().setImage("/usr/share/icons/mate/48x48/mimetypes/text-x-makefile.png");
		getImage<1, 0>().setImage("/usr/share/icons/mate/48x48/mimetypes/vcalendar.png");
		getImage<1, 1>().setImage("/usr/share/icons/mate/48x48/mimetypes/x-office-spreadsheet.png");
		getImage<1, 2>().setImage("/usr/share/icons/mate/48x48/mimetypes/contents2.png");
		getImage<2, 0>().setImage("/usr/share/icons/mate/48x48/mimetypes/video.png");
		getImage<2, 1>().setImage("/usr/share/icons/mate/48x48/mimetypes/font_truetype.png");
		getImage<2, 2>().setImage("/usr/share/icons/mate/48x48/mimetypes/gnome-mime-text-x-vcalendar.png");
		getBottomLabel().setText(U"Bottom");

		getButton<1, 1>().Clicked += [&]
		{
			getImage<1, 1>().setImage("/usr/share/icons/mate/48x48/mimetypes/exec.png");
		};

		getTopButton().Clicked += [&]
		{
			getBottomLabel().setText(U"Clicked!");
		};

		getWindow().Deleted += [&]
		{
			getApplication().stop();
		};

		getWindow().setTitle("Hello");
	}
};

using HelloT = Twil::Ui::ApplicationAdaptorT<HelloBaseT>;

int main(void)
{
	HelloT Hello;
	Hello.run();
}
