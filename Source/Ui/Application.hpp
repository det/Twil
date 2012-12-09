#pragma once

#include "Gl/Context.hpp"
#include "Platform/Application.hpp"

namespace Twil {
namespace Ui {

template<typename T>
class Application
{
	private:
	Platform::Application mApplication;
	T mChild;

	public:
	Application();

	void run();
	void stop();

	T & getChild();
};

template<typename T>
Application<T>::Application() :
	mChild{mApplication}
{
}

template<typename T>
void Application<T>::run()
{
	mApplication.run(mChild);
}

template<typename T>
void Application<T>::stop()
{
	mApplication.stop();
}

template<typename T>
T & Application<T>::getChild()
{
	return mChild;
}

}
}
