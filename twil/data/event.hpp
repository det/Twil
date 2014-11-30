#pragma once

#include "event.hxx"

#include <functional>
#include <utility>
#include <list>

namespace twil {
namespace data {

/// \brief A multicast event class.
template<typename ... Args>
class Event
{
	Event(Event const &) = delete;
	Event & operator =(Event const &) = delete;

private:
	using List = std::list<std::function<void(Args ...)>>;
	List callbacks_;

public:
	class Handle
	{
		friend Event;
	private:
		typename List::iterator iterator_;
	public:
		Handle(typename List::iterator iterator) : iterator_{iterator} {}
	};

	Event() = default;

	/// \brief Append a callback to the event.
	template<typename Functor>
	Handle operator +=(Functor && functor)
	{
		return {callbacks_.emplace(callbacks_.end(), std::forward<Functor>(functor))};
	}

	/// \brief Remove a callback from the event.
	void operator -=(Handle handle)
	{
		callbacks_.erase(handle.iterator_);
	}

	/// \brief Call all callbacks.
	void operator ()(Args && ... args) const
	{
		for (auto & callback : callbacks_) callback(std::forward<Args>(args) ...);
	}
};

}
}
