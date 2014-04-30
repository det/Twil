#pragma once

#include "ApplicationFwd.hpp"

#include "Gl/Context.hpp"
#include "Platform/Application.hpp"

namespace Twil {
namespace Ui {

/// \brief An application with a single window.
///
/// \param T Type of the window.
template<typename T>
class ApplicationT
:
	public Platform::ApplicationT
{
	ApplicationT(ApplicationT const &) = delete;
	ApplicationT & operator =(ApplicationT const &) = delete;

private:
	T mChild;

public:
	ApplicationT()
	:
		mChild{*this}
	{
		mChild.init();
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
