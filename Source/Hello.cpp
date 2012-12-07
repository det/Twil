#include "Ui/Application.hpp"
#include "Ui/Button.hpp"
#include "Ui/Label.hpp"
#include "Ui/Window.hpp"

#include <iostream>

int main(void)
{	
	using Label = Twil::Ui::Label;
	using Button = Twil::Ui::Button<Label>;
	using Window = Twil::Ui::Window<Button>;
	using Application = Twil::Ui::Application<Window>;

	Application application;
	Window & window = application.getChild();
	Button & button = window.getChild();
	Label & label = button.getChild();

	label.setText(U"nymphs blitz quick vex dwarf jog");
//	label.setText(U"Cancel");
	button.Clicked += [&]() { std::cout << "Hello world\n"; };
	window.Deleted += [&]() { application.stop(); };

	application.run();
	return 0;
}
