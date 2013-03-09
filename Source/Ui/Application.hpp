#pragma once

#include "Gl/Context.hpp"
#include "Platform/Application.hpp"

namespace Twil {
namespace Ui {

/// \brief An application with a single window.
///
/// \param T Type of the window.
template<typename T>
class ApplicationT
{
	private:
	Platform::ApplicationT mApplication;
	T mChild;

	public:
	ApplicationT() :
		mChild{mApplication}
	{
		mChild.init();
	}

	/// \brief Start the event loop.
	void run()
	{
		mApplication.run(mChild);
	}

	/// \brief Stop the event loop.
	void stop()
	{
		mApplication.stop();
	}

	/// \returns A reference to the child window.
	T & getChild()
	{
		return mChild;
	}

	/// \returns A const reference to the child window.
	T const & getChild() const
	{
		return mChild;
	}
};

}
}
