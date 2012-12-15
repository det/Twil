#pragma once

#include <cstddef>

namespace Twil {
namespace Ui {

template<typename ...Args>
struct Tuple;

template<typename First, typename Second, typename ...Rest>
struct Tuple<First, Second, Rest...>
{
	typedef First HeadType;
	typedef Tuple<Second, Rest...> TailType;

	HeadType Head;
	TailType Tail;

	template<typename... ConArgs>
	Tuple(ConArgs &... P) :
		Head{P...},
		Tail{P...}
	{}

	template<typename F>
	void iterate(F Function)
	{
		Function(Head);
		Tail.iterate(Function);
	}

	template<typename F>
	void iterateUntil(F Function)
	{
		if (Function(Head)) Tail.iterateUntil(Function);
	}
};

template<typename First, typename Second>
struct Tuple<First, Second>
{
	typedef First HeadType;
	typedef Second TailType;

	HeadType Head;
	TailType Tail;

	template<typename... ConArgs>
	Tuple(ConArgs &... P) :
		Head{P...},
		Tail{P...}
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
};

template<std::size_t I, typename T, typename ...Args>
struct TupleElement;

template<typename T, typename ...Args>
struct TupleElement<0, T, Args...>
{
	typedef T Type;

	Type & get(Ui::Tuple<T, Args...> & Tuple)
	{
		return Tuple.Head;
	}
};

template<typename T>
struct TupleElement<0, T>
{
	typedef T Type;

	Type & get(T & Value)
	{
		return Value;
	}
};

template<std::size_t I, typename T, typename ...Args>
struct TupleElement
{
	typedef typename Ui::TupleElement<I - 1, Args...>::Type Type;

	Type & get(Ui::Tuple<T, Args...> & Tuple)
	{
		return Ui::TupleElement<I - 1, Args...>().get(Tuple.Tail);
	}
};

}
}
