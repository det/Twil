#pragma once

#include "EventFwd.hpp"

#include <functional>
#include <utility>
#include <list>

namespace Twil {
namespace Data {

/// \brief A multicast event class.
template<typename ... ArgsT>
class EventT
{
	EventT(EventT const &) = delete;
	EventT & operator =(EventT const &) = delete;

private:
	using ListT = std::list<std::function<void(ArgsT ...)>>;
	ListT mCallbacks;

public:
	class HandleT
	{
		friend class EventT;
	private:
		typename ListT::iterator mIterator;
	public:
		HandleT(typename ListT::iterator Iterator) : mIterator{Iterator} {}
	};

	EventT() = default;

	/// \brief Append a callback to the event.
	template<typename FunctorT>
	HandleT operator +=(FunctorT && Functor)
	{
		return {mCallbacks.emplace(mCallbacks.end(), std::forward<FunctorT>(Functor))};
	}

	/// \brief Remove a callback from the event.
	void operator -=(HandleT Handle)
	{
		mCallbacks.erase(Handle.mIterator);
	}

	/// \brief Call all callbacks.
	void operator ()(ArgsT && ... Args) const
	{
		for (auto & Callback : mCallbacks) Callback(std::forward<ArgsT>(Args) ...);
	}
};

}
}
