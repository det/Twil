#pragma once

#include <cstddef>

namespace Twil {
namespace Ui {

template<typename ...>
struct TupleT;

/// \brief A variadic container that can be iterated over with a functor.
template<typename T, typename ... ArgsT>
struct TupleT<T, ArgsT ...>
{
	T Head;
	TupleT<ArgsT ...> Tail;

	template<typename ... ConArgsT>
	TupleT(ConArgsT & ... ConArgs) :
		Head{ConArgs ...},
		Tail{ConArgs ...}
	{}

	template<typename FunctionT>
	void iterate(FunctionT Function)
	{
		Function(Head);
		Tail.iterate(Function);
	}

	template<typename FunctionT>
	void iterateUntil(FunctionT Function)
	{
		if (Function(Head)) Tail.iterateUntil(Function);
	}

	template<typename FunctionT>
	void iterate(FunctionT Function) const
	{
		Function(Head);
		Tail.iterate(Function);
	}

	template<typename FunctionT>
	void iterateUntil(FunctionT Function) const
	{
		if (Function(Head)) Tail.iterateUntil(Function);
	}
};

/// \brief A pair container that can be iterated over with a functor.
template<typename FirstT, typename SecondT>
struct TupleT<FirstT, SecondT>
{
	FirstT Head;
	SecondT Tail;

	template<typename ... ConArgsT>
	TupleT(ConArgsT & ... ConArgs) :
		Head{ConArgs ...},
		Tail{ConArgs ...}
	{}

	template<typename F>
	void iterate(F Function)
	{
		Function(Head);
		Function(Tail);
	}

	template<typename F>
	void iterateUntil(F Function)
	{
		if (Function(Head)) Function(Tail);
	}

	template<typename F>
	void iterate(F Function) const
	{
		Function(Head);
		Function(Tail);
	}

	template<typename F>
	void iterateUntil(F Function) const
	{
		if (Function(Head)) Function(Tail);
	}
};

template<std::size_t, typename, typename ...>
struct TupleElementT;

template<typename T, typename ... ArgsT>
struct TupleElementT<0, T, ArgsT ...>
{
	typedef T ElementT;

	ElementT & get(TupleT<T, ArgsT ...> & Tuple)
	{
		return Tuple.Head;
	}

	ElementT const & get(TupleT<T, ArgsT ...> const & Tuple)
	{
		return Tuple.Head;
	}
};

template<typename T>
struct TupleElementT<0, T>
{
	typedef T ElementT;

	ElementT & get(T & Value)
	{
		return Value;
	}

	ElementT const & get(T const & Value)
	{
		return Value;
	}
};

template<std::size_t I, typename T, typename ... ArgsT>
struct TupleElementT
{
	typedef typename TupleElementT<I - 1, ArgsT ...>::ElementT ElementT;

	ElementT & get(TupleT<T, ArgsT ...> & Tuple)
	{
		return TupleElementT<I - 1, ArgsT ...>().get(Tuple.Tail);
	}

	ElementT const & get(TupleT<T, ArgsT ...> const & Tuple)
	{
		return TupleElementT<I - 1, ArgsT ...>().get(Tuple.Tail);
	}
};

}
}
