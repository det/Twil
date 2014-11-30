#pragma once

#include "scope_guard.hxx"

#include <utility>

namespace twil {
namespace data {

template<typename Deleter>
class ScopeGuard
{
private:
	bool active_;
	Deleter deleter_;

public:
	ScopeGuard() = delete;
	ScopeGuard(ScopeGuard const &) = delete;
	ScopeGuard(ScopeGuard &&) = delete;
	ScopeGuard & operator =(ScopeGuard const &) = delete;
	ScopeGuard & operator =(ScopeGuard &&) = delete;

	ScopeGuard(Deleter deleter)
	:
		active_{true},
		deleter_(std::move(deleter))
	{}

	~ScopeGuard() noexcept
	{
		if (active_) deleter_();
	}

	void Dismiss()
	{
		active_ = false;
	}
};

template<typename Deleter>
ScopeGuard<Deleter> MakeScopeGuard(Deleter deleter)
{
	return {std::move(deleter)};
}

}
}
