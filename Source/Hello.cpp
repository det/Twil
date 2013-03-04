#include "Ui/Application.hpp"
#include "Ui/Button.hpp"
#include "Ui/Centered.hpp"
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
	using LabelT = Twil::Ui::LabelT<CenteredT>;
	using ButtonT = Twil::Ui::ButtonT<LabelT>;
	using SpacedButtonT = Twil::Ui::MarginT<4, 4, ButtonT>;
	using ColumnT = Twil::Ui::PartitionBoxT<false, SpacedButtonT, SpacedButtonT, SpacedButtonT>;
	using GridT = Twil::Ui::PartitionBoxT<true, ColumnT, ColumnT, ColumnT>;
	using VerticalBox0T = Twil::Ui::SplitBoxT<false, false, GridT, SpacedButtonT>;
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
	ButtonT & getButton00() { return getColumn0().getChild<0>().getChild(); }
	ButtonT & getButton10() { return getColumn0().getChild<1>().getChild(); }
	ButtonT & getButton20() { return getColumn0().getChild<2>().getChild(); }
	ButtonT & getButton01() { return getColumn1().getChild<0>().getChild(); }
	ButtonT & getButton11() { return getColumn1().getChild<1>().getChild(); }
	ButtonT & getButton21() { return getColumn1().getChild<2>().getChild(); }
	ButtonT & getButton02() { return getColumn2().getChild<0>().getChild(); }
	ButtonT & getButton12() { return getColumn2().getChild<1>().getChild(); }
	ButtonT & getButton22() { return getColumn2().getChild<2>().getChild(); }
	ButtonT & getTopButton() { return getVerticalBox0().getSecond().getChild(); }
	LabelT & getBottomLabel() { return getVerticalBox1().getFirst(); }
	LabelT & getLabel00() { return getButton00().getChild(); }
	LabelT & getLabel10() { return getButton10().getChild(); }
	LabelT & getLabel20() { return getButton20().getChild(); }
	LabelT & getLabel01() { return getButton01().getChild(); }
	LabelT & getLabel11() { return getButton11().getChild(); }
	LabelT & getLabel21() { return getButton21().getChild(); }
	LabelT & getLabel02() { return getButton02().getChild(); }
	LabelT & getLabel12() { return getButton12().getChild(); }
	LabelT & getLabel22() { return getButton22().getChild(); }
	LabelT & getTopLabel() { return getTopButton().getChild(); }

	public:
	HelloT()
	{
		getBottomLabel().setText(U"Bottom");
		getLabel00().setText(U"0");
		getLabel10().setText(U"1");
		getLabel20().setText(U"2");
		getLabel01().setText(U"3");
		getLabel11().setText(U"4");
		getLabel21().setText(U"5");
		getLabel02().setText(U"6");
		getLabel12().setText(U"7");
		getLabel22().setText(U"8");
		getTopLabel().setText(U"Top");
		getButton00().Clicked += [&]() { getLabel00().setText(U"Clicked"); };
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
