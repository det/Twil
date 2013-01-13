#include "Ui/Application.hpp"
#include "Ui/Button.hpp"
#include "Ui/Centered.hpp"
#include "Ui/Label.hpp"
#include "Ui/PartitionBox.hpp"
#include "Ui/Border.hpp"
#include "Ui/SplitBox.hpp"
#include "Ui/Window.hpp"

#include <iostream>

class Hello
{
	private:
	using Label = Twil::Ui::Label;
	using CenteredLabel = Twil::Ui::Centered<Label>;
	using Button = Twil::Ui::Button<CenteredLabel>;
	using SpacedButton = Twil::Ui::Border<4, 4, Button>;
	using Column = Twil::Ui::PartitionBox<false, SpacedButton, SpacedButton, SpacedButton>;
	using Grid = Twil::Ui::PartitionBox<true, Column, Column, Column>;
	using VerticalBox0 = Twil::Ui::SplitBox<false, true, SpacedButton, Grid>;
	using VerticalBox1 = Twil::Ui::SplitBox<false, false, VerticalBox0, SpacedButton>;
	using Window = Twil::Ui::Window<VerticalBox1>;
	using Application = Twil::Ui::Application<Window>;
	Application mApplication;

	Application & getApplication() { return mApplication; }
	Window & getWindow() { return getApplication().getChild(); }
	VerticalBox1 & getVerticalBox1() { return getWindow().getChild(); }
	VerticalBox0 & getVerticalBox0() { return getVerticalBox1().getChild0(); }
	Grid & getGrid() { return getVerticalBox0().getChild1(); }
	Column & getColumn0() { return getGrid().getChild<0>(); }
	Column & getColumn1() { return getGrid().getChild<1>(); }
	Column & getColumn2() { return getGrid().getChild<2>(); }
	Button & getBottomButton() { return getVerticalBox0().getChild0().getChild(); }
	Button & getButton00() { return getColumn0().getChild<0>().getChild(); }
	Button & getButton10() { return getColumn0().getChild<1>().getChild(); }
	Button & getButton20() { return getColumn0().getChild<2>().getChild(); }
	Button & getButton01() { return getColumn1().getChild<0>().getChild(); }
	Button & getButton11() { return getColumn1().getChild<1>().getChild(); }
	Button & getButton21() { return getColumn1().getChild<2>().getChild(); }
	Button & getButton02() { return getColumn2().getChild<0>().getChild(); }
	Button & getButton12() { return getColumn2().getChild<1>().getChild(); }
	Button & getButton22() { return getColumn2().getChild<2>().getChild(); }
	Button & getTopButton() { return getVerticalBox1().getChild1().getChild(); }
	Label & getBottomLabel() { return getBottomButton().getChild().getChild(); }
	Label & getLabel00() { return getButton00().getChild().getChild(); }
	Label & getLabel10() { return getButton10().getChild().getChild(); }
	Label & getLabel20() { return getButton20().getChild().getChild(); }
	Label & getLabel01() { return getButton01().getChild().getChild(); }
	Label & getLabel11() { return getButton11().getChild().getChild(); }
	Label & getLabel21() { return getButton21().getChild().getChild(); }
	Label & getLabel02() { return getButton02().getChild().getChild(); }
	Label & getLabel12() { return getButton12().getChild().getChild(); }
	Label & getLabel22() { return getButton22().getChild().getChild(); }
	Label & getTopLabel() { return getTopButton().getChild().getChild(); }

	public:
	Hello()
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
		getWindow().resize(320, 240);
		getWindow().show();
		getButton00().Clicked += [&]() { getLabel00().setText(U"Clicked"); };
		getWindow().Deleted += [&]() { getApplication().stop(); };
	}

	void run()
	{
		getApplication().run();
	}
};

int main(void)
{
	::Hello Hello;
	Hello.run();
}
