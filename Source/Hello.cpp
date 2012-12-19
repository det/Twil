#include "Ui/Application.hpp"
#include "Ui/Button.hpp"
#include "Ui/Centered.hpp"
#include "Ui/Label.hpp"
#include "Ui/PartitionBox.hpp"
#include "Ui/Spacer.hpp"
#include "Ui/SplitBox.hpp"
#include "Ui/Window.hpp"

#include <iostream>

int main(void)
{
	using MyCentered = Twil::Ui::Centered;
	using MyLabel = Twil::Ui::Label<MyCentered>;
	using MyButton = Twil::Ui::Button<MyLabel>;
	using MySpacedButton = Twil::Ui::Spacer<2, MyButton>;
	using MyColumn = Twil::Ui::PartitionBox<false, MySpacedButton, MySpacedButton, MySpacedButton>;
	using MyGrid = Twil::Ui::PartitionBox<true, MyColumn, MyColumn, MyColumn>;
	using MyVerticalBox0 = Twil::Ui::SplitBox<false, false, false, MySpacedButton, MyGrid>;
	using MyVerticalBox1 = Twil::Ui::SplitBox<false, true, true, MyVerticalBox0, MySpacedButton>;
	using MyWindow = Twil::Ui::Window<MyVerticalBox1>;
	using MyApplication = Twil::Ui::Application<MyWindow>;

	MyApplication Application;

	auto & Window = Application.getChild();
	auto & VerticalBox1 = Window.getChild();
	auto & RightButton = VerticalBox1.getChild1().getChild();;
	auto & VerticalBox0 = VerticalBox1.getChild0();
	auto & LeftButton = VerticalBox0.getChild0().getChild();;
	auto & Grid = VerticalBox0.getChild1();
	auto & Column0 = Grid.getChild<0>();
	auto & Column1 = Grid.getChild<1>();
	auto & Column2 = Grid.getChild<2>();

	auto & Button00 = Column0.getChild<0>().getChild();
	auto & Button10 = Column0.getChild<1>().getChild();
	auto & Button20 = Column0.getChild<2>().getChild();
	auto & Button01 = Column1.getChild<0>().getChild();
	auto & Button11 = Column1.getChild<1>().getChild();
	auto & Button21 = Column1.getChild<2>().getChild();
	auto & Button02 = Column2.getChild<0>().getChild();
	auto & Button12 = Column2.getChild<1>().getChild();
	auto & Button22 = Column2.getChild<2>().getChild();

	auto & Label00 = Button00.getChild();
	auto & Label10 = Button01.getChild();
	auto & Label20 = Button02.getChild();
	auto & Label01 = Button10.getChild();
	auto & Label11 = Button11.getChild();
	auto & Label21 = Button12.getChild();
	auto & Label02 = Button20.getChild();
	auto & Label12 = Button21.getChild();
	auto & Label22 = Button22.getChild();
	auto & BottomLabel = LeftButton.getChild();
	auto & TopLabel = RightButton.getChild();

	Label00.setText(U"0");
	Label10.setText(U"1");
	Label20.setText(U"2");
	Label01.setText(U"3");
	Label11.setText(U"4");
	Label21.setText(U"5");
	Label02.setText(U"6");
	Label12.setText(U"7");
	Label22.setText(U"8");
	BottomLabel.setText(U"Bottom");
	TopLabel.setText(U"Top");

	Window.resize(320, 240);
	Window.show();

	Button00.Clicked += [&]() { std::cout << "0\n"; };
	Window.Deleted += [&]() { Application.stop(); };

	Application.run();
}
