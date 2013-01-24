#pragma once

#include <functional>
#include <vector>

namespace Twil {
namespace Ui {

/// \brief A multicast event class.
template<typename ... ArgsT>
class EventT
{
	typedef std::function<void(ArgsT ...)> FunctionT;

	private:
	std::vector<FunctionT> mCallbacks;

	public:
	/// \brief Append a callback to the event.
	void operator+=(FunctionT f)
	{
		mCallbacks.push_back(f);
	}

	/// \brief Call all callbacks.
	void operator()(ArgsT && ... Args) const
	{
		for (auto Callback : mCallbacks) Callback(std::forward<ArgsT>(Args) ...);
	}
};

}
}
