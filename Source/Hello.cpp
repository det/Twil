#include "Ui/Application.hpp"
#include "Ui/Button.hpp"
#include "Ui/Centered.hpp"
#include "Ui/HorizontalBox.hpp"
#include "Ui/Label.hpp"
#include "Ui/Window.hpp"

#include <iostream>

int main(void)
{
	using MyLabel = Twil::Ui::Label<Twil::Ui::Centered>;
	using MyButton = Twil::Ui::Button<MyLabel>;
	using MyHorizontalBox = Twil::Ui::HorizontalBox<MyButton, MyButton, MyButton>;
	using MyWindow = Twil::Ui::Window<MyHorizontalBox>;
	using MyApplication = Twil::Ui::Application<MyWindow>;

	MyApplication Application;
	auto & Window = Application.getChild();
	auto & HorizontalBox = Window.getChild();
	auto & Button1 = HorizontalBox.getChild<0>();
	auto & Button2 = HorizontalBox.getChild<1>();
	auto & Button3 = HorizontalBox.getChild<2>();
	auto & Label1 = Button1.getChild();
	auto & Label2 = Button2.getChild();
	auto & Label3 = Button3.getChild();

	Label1.setText(U"Button1");
	Label2.setText(U"Button2");
	Label3.setText(U"Button3");
	Window.fitChild(0, 0);
	Window.show();

	Button1.Clicked += [&]() { std::cout << "Button1\n"; };
	Button2.Clicked += [&]() { std::cout << "Button2\n"; };
	Button3.Clicked += [&]() { std::cout << "Button3\n"; };
	Window.Deleted += [&]() { Application.stop(); };

	Application.run();
}
