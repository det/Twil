#pragma once

#include <functional>
#include <utility>
#include <vector>

namespace Twil {
namespace Data {

/// \brief A multicast event class.
template<typename ... ArgsT>
class EventT
{
	EventT(EventT const &) = delete;
	EventT & operator =(EventT const &) = delete;

private:
	std::vector<std::function<void(ArgsT ...)>> mCallbacks;

public:
	EventT() = default;

	/// \brief Append a callback to the event.
	template<typename FunctorT>
	void operator +=(FunctorT && Functor)
	{
		mCallbacks.push_back(std::forward<FunctorT>(Functor));
	}

	/// \brief Call all callbacks.
	void operator ()(ArgsT && ... Args) const
	{
		for (auto & Callback : mCallbacks) Callback(std::forward<ArgsT>(Args) ...);
	}
};

}
}
