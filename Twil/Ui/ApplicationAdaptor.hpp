#pragma once

#include <cstdint>

namespace Twil {
namespace Ui {

template<typename T>
class ApplicationAdaptorT
:
	public T
{
	protected:
	using T::getApplication;

	public:
	// Application
	void run()
	{
		getApplication().run();
	}

	void stop()
	{
		getApplication().stop();
	}
};

}
}
