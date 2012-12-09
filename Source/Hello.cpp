#include "Ui/Application.hpp"
#include "Ui/Button.hpp"
#include "Ui/Centered.hpp"
#include "Ui/Label.hpp"
#include "Ui/Window.hpp"

#include <iostream>

int main(void)
{	
	using MyCentered = Twil::Ui::Centered;
	using MyLabel = Twil::Ui::Label<MyCentered>;
	using MyButton = Twil::Ui::Button<MyLabel>;
	using MyWindow = Twil::Ui::Window<MyButton>;
	using MyApplication = Twil::Ui::Application<MyWindow>;

	MyApplication Application;
	MyWindow & Window = Application.getChild();
	MyButton & Button = Window.getChild();
	MyLabel & Label = Button.getChild();

	Label.setText(U"nymphs blitz quick vex dwarf jog");
//	Label.setText(U"Hello");
	Button.Clicked += [&]() { std::cout << "Hello world\n"; };
	Window.Deleted += [&]() { Application.stop(); };
	Window.fitChild(8, 16);
	Window.show();
	Application.run();
}
