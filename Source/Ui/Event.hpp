#pragma once

#include <functional>
#include <vector>

namespace Twil {
namespace Ui {

template<typename... Args>
class Event {
	typedef std::function<void(Args...)> Function;

	private:
	std::vector<Function> mCallbacks;

	public:
	void operator+=(Function f)
	{
		mCallbacks.push_back(f);
	}

	void operator()(Args &&... args) const
	{
		for (auto Callback : mCallbacks) Callback(std::forward<Args>(args)...);
	}
};

}
}
