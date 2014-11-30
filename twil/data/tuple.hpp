#pragma once

#include "tuple.hxx"

#include <array>
#include <tuple>

namespace twil {
namespace data {

// Iterate

template<std::size_t n, std::size_t i>
struct IterateFunctor
{
	template<typename Tuple, typename Functor>
	void operator()(Tuple & tuple, Functor functor)
	{
		functor(std::get<n>(tuple));
		IterateFunctor<n + 1, i - 1> Iterator;
		Iterator(tuple, functor);
	}
};

template<std::size_t n>
struct IterateFunctor<n, 0>
{
	template<typename T, typename Functor>
	void operator()(T &, Functor)
	{}
};

template<typename Functor, typename Tuple>
void Iterate(Tuple & tuple, Functor functor)
{
	IterateFunctor<0, std::tuple_size<Tuple>::value> iterator;
	iterator(tuple, functor);
}

template<typename Functor, typename Tuple>
void Iterate(Tuple const & tuple, Functor functor)
{
	IterateFunctor<0, std::tuple_size<Tuple>::value> iterator;
	iterator(tuple, functor);
}

// IterateUntil

template<std::size_t n, std::size_t i>
struct IterateUntilFunctor
{
	template<typename Tuple, typename Functor>
	void operator()(Tuple & tuple, Functor functor)
	{
		if (functor(std::get<n>(tuple)))
		{
			IterateUntilFunctor<n + 1, i - 1> iterator;
			iterator(tuple, functor);
		}
	}
};

template<std::size_t n>
struct IterateUntilFunctor<n, 0>
{
	template<typename Tuple, typename Functor>
	void operator()(Tuple &, Functor)
	{}
};

template<typename Functor, typename Tuple>
void IterateUntil(Tuple & tuple, Functor functor)
{
	IterateUntilFunctor<0, std::tuple_size<Tuple>::value> iterator;
	iterator(tuple, functor);
}

template<typename Functor, typename Tuple>
void IterateUntil(Tuple const & tuple, Functor functor)
{
	IterateUntilFunctor<0, std::tuple_size<Tuple>::value> iterator;
	iterator(tuple, functor);
}

}
}
