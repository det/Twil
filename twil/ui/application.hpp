#pragma once

#include "application.hxx"

#include "gl/context.hpp"
#include "platform/application.hpp"

namespace twil {
namespace ui {

/// \brief An application with a single window.
///
/// \param T Type of the window.
template<typename T>
class Application
:
	public platform::Application
{
	Application(Application const &) = delete;
	Application & operator =(Application const &) = delete;

private:
	T child_;

public:
	Application()
	:
		child_{*this}
	{
		child_.Init();
	}

	/// \returns A reference to the child window.
	T & GetChild()
	{
		return child_;
	}

	/// \returns A const reference to the child window.
	T const & GetChild() const
	{
		return child_;
	}
};

template<typename T>
class ApplicationAdaptor
:
	public T
{
protected:
	using T::GetApplication;

public:
	// Application
	void Run()
	{
		GetApplication().Run();
	}

	void stop()
	{
		GetApplication().Stop();
	}
};

}
}
