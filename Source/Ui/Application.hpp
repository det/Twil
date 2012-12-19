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
	Application() :
		mChild{mApplication}
	{}

	void run()
	{
		mApplication.run(mChild);
	}

	void stop()
	{
		mApplication.stop();
	}

	T & getChild()
	{
		return mChild;
	}
};

}
}
