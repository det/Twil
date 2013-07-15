#pragma once

#include <array>
#include <tuple>

namespace Twil {
namespace Data {

// iterate

template<std::size_t, std::size_t>
struct IterateFunctorT;

template<std::size_t N, std::size_t I>
struct IterateFunctorT
{
	template<typename TupleT, typename FunctorT>
	void operator()(TupleT & Tuple, FunctorT Functor)
	{
		Functor(std::get<N>(Tuple));
		IterateFunctorT<N + 1, I - 1>{}(Tuple, Functor);
	}
};

template<std::size_t N>
struct IterateFunctorT<N, 0>
{
	template<typename T, typename FunctorT>
	void operator()(T &, FunctorT)
	{}
};

template<typename FunctorT, typename TupleT>
void iterate(TupleT & Tuple, FunctorT Functor)
{
	IterateFunctorT<0, std::tuple_size<TupleT>::value>{}(Tuple, Functor);
}

template<typename FunctorT, typename TupleT>
void iterate(TupleT const & Tuple, FunctorT Functor)
{
	IterateFunctorT<0, std::tuple_size<TupleT>::value>{}(Tuple, Functor);
}

// iterateUntil

template<std::size_t, std::size_t>
struct IterateUntilFunctorT;

template<std::size_t N, std::size_t I>
struct IterateUntilFunctorT
{
	template<typename TupleT, typename FunctorT>
	void operator()(TupleT & Tuple, FunctorT Functor)
	{
		if (Functor(std::get<N>(Tuple))) IterateUntilFunctorT<N + 1, I - 1>{}(Tuple, Functor);
	}
};

template<std::size_t N>
struct IterateUntilFunctorT<N, 0>
{
	template<typename TupleT, typename FunctorT>
	void operator()(TupleT &, FunctorT)
	{}
};

template<typename FunctorT, typename TupleT>
void iterateUntil(TupleT & Tuple, FunctorT Functor)
{
	IterateUntilFunctorT<0, std::tuple_size<TupleT>::value>{}(Tuple, Functor);
}

template<typename FunctorT, typename TupleT>
void iterateUntil(TupleT const & Tuple, FunctorT Functor)
{
	IterateUntilFunctorT<0, std::tuple_size<TupleT>::value>{}(Tuple, Functor);
}

}
}
