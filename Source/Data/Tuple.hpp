#pragma once

#include <tuple>

namespace Twil {
namespace Data {

// iterate

template<std::size_t, typename ...>
struct IterateFunctorT;

template<std::size_t N, typename T, typename ... ArgsT>
struct IterateFunctorT<N, T, ArgsT ...>
{
	template<typename TupleT, typename FunctorT>
	void operator()(TupleT & Tuple, FunctorT Functor)
	{
		Functor(std::get<N>(Tuple));
		IterateFunctorT<N + 1, ArgsT ...>{}(Tuple, Functor);
	}
};

template<std::size_t N>
struct IterateFunctorT<N>
{
	template<typename TupleT, typename FunctorT>
	void operator()(TupleT &, FunctorT)
	{}
};

template<typename FunctorT, typename ... ArgsT>
void iterate(std::tuple<ArgsT ...> & Tuple, FunctorT Functor)
{
	IterateFunctorT<0, ArgsT ...>{}(Tuple, Functor);
}

template<typename FunctorT, typename ... ArgsT>
void iterate(std::tuple<ArgsT ...> const & Tuple, FunctorT Functor)
{
	IterateFunctorT<0, ArgsT ...>{}(Tuple, Functor);
}

// iterateUntil

template<std::size_t, typename ...>
struct IterateUntilFunctorT;

template<std::size_t N, typename T, typename ... ArgsT>
struct IterateUntilFunctorT<N, T, ArgsT ...>
{
	template<typename TupleT, typename FunctorT>
	void operator()(TupleT & Tuple, FunctorT Functor)
	{
		if (Functor(std::get<N>(Tuple))) IterateUntilFunctorT<N + 1, ArgsT ...>{}(Tuple, Functor);
	}
};

template<std::size_t N>
struct IterateUntilFunctorT<N>
{
	template<typename TupleT, typename FunctorT>
	void operator()(TupleT &, FunctorT)
	{}
};

template<typename FunctorT, typename ... ArgsT>
void iterateUntil(std::tuple<ArgsT ...> & Tuple, FunctorT Functor)
{
	IterateUntilFunctorT<0, ArgsT ...>{}(Tuple, Functor);
}

template<typename FunctorT, typename ... ArgsT>
void iterateUntil(std::tuple<ArgsT ...> const & Tuple, FunctorT Functor)
{
	IterateUntilFunctorT<0, ArgsT ...>{}(Tuple, Functor);
}

}
}
