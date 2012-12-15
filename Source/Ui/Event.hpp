#pragma once

#include <functional>
#include <vector>

namespace Twil {
namespace Ui {

template<typename... As>
class Event
{
	typedef std::function<void(As...)> Function;

	private:
	std::vector<Function> mCallbacks;

	public:
	void operator+=(Function f)
	{
		mCallbacks.push_back(f);
	}

	void operator()(As &&... Args) const
	{
		for (auto Callback : mCallbacks) Callback(std::forward<As>(Args)...);
	}
};

}
}
