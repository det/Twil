#pragma once

#include <algorithm>
#include <cstdlib>

namespace Twil {
namespace Data {

template<typename T>
struct DefaultArrayDeleterT
{
	void operator()(T * Object)
	{
		delete[] Object;
	}
};

template<typename T, typename DeleterT = DefaultArrayDeleterT<T>>
class UniqueArrayT
{
	private:
	T * mPointer;

	public:
	UniqueArrayT(UniqueArrayT const &) = delete;
	UniqueArrayT<T> & operator=(UniqueArrayT<T> const &) = delete;

	UniqueArrayT() :
		mPointer{nullptr}
	{}

	UniqueArrayT(T * Pointer) :
		mPointer{Pointer}
	{}

	UniqueArrayT(UniqueArrayT<T> && Other) :
		mPointer{nullptr}
	{
		*this = std::move(Other);
	}

	~UniqueArrayT()
	{
		DeleterT{}(mPointer);
	}

	UniqueArrayT<T> & operator=(UniqueArrayT<T> && Other)
	{
		UniqueArrayT<T> Temp;
		Other.swap(Temp);
		Temp.swap(*this);
		return *this;
	}

	bool operator==(T * Pointer)
	{
		return mPointer == Pointer;
	}

	void swap(UniqueArrayT<T> & Other)
	{
		std::swap(mPointer, Other.mPointer);
	}

	T & operator[](std::size_t Index)
	{
		return mPointer[Index];
	}

	T const & operator[](std::size_t Index) const
	{
		return mPointer[Index];
	}

	void reset(T * Pointer)
	{
		UniqueArrayT<T> Temp{Pointer};
		*this = std::move(Temp);
	}

	T * release()
	{
		T * Temp = nullptr;
		std::swap(mPointer, Temp);
		return Temp;
	}

	T * data()
	{
		return mPointer;
	}

	T const * data() const
	{
		return mPointer;
	}
};

template<typename T>
UniqueArrayT<T> makeArray(std::size_t Size)
{
	return UniqueArrayT<T>{new T[Size]};
}

}
}
