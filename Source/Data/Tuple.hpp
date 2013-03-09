#pragma once

#include <tuple>

namespace Twil {
namespace Data {

// iterate

template<std::size_t, typename ...>
struct IterateFunctor;

template<std::size_t N, typename T, typename ... ArgsT>
struct IterateFunctor<N, T, ArgsT ...>
{
	template<typename TupleT, typename FunctorT>
	void operator()(TupleT & Tuple, FunctorT Functor)
	{
		Functor(std::get<N>(Tuple));
		IterateFunctor<N + 1, ArgsT ...>{}(Tuple, Functor);
	}
};

template<std::size_t N>
struct IterateFunctor<N>
{
	template<typename TupleT, typename FunctorT>
	void operator()(TupleT &, FunctorT)
	{}
};

template<typename FunctorT, typename ... ArgsT>
void iterate(std::tuple<ArgsT ...> & Tuple, FunctorT Functor)
{
	IterateFunctor<0, ArgsT ...>{}(Tuple, Functor);
}


// iterateUntil

template<std::size_t, typename ...>
struct IterateUntilFunctor;

template<std::size_t N, typename T, typename ... ArgsT>
struct IterateUntilFunctor<N, T, ArgsT ...>
{
	template<typename TupleT, typename FunctorT>
	void operator()(TupleT & Tuple, FunctorT Functor)
	{
		if (Functor(std::get<N>(Tuple))) IterateUntilFunctor<N + 1, ArgsT ...>{}(Tuple, Functor);
	}
};

template<std::size_t N>
struct IterateUntilFunctor<N>
{
	template<typename TupleT, typename FunctorT>
	void operator()(TupleT &, FunctorT)
	{}
};

template<typename FunctorT, typename ... ArgsT>
void iterateUntil(std::tuple<ArgsT ...> & Tuple, FunctorT Functor)
{
	IterateUntilFunctor<0, ArgsT ...>{}(Tuple, Functor);
}

}
}
