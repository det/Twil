#pragma once

#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <memory>

namespace Twil {
namespace Data {

template<typename T>
struct RopeNodeT
{
	private:
	struct BaseT
	{
		std::size_t mutable Count;
		bool IsBranch;
	};

	struct BranchT :
		public BaseT
	{
		RopeNodeT const Left;
		std::size_t const LeftSize;
		RopeNodeT const Right;

		BranchT(RopeNodeT pLeft, std::size_t pLeftSize, RopeNodeT pRight) :
			BaseT{1, true},
			Left{std::move(pLeft)},
			LeftSize{pLeftSize},
			Right{std::move(pRight)}
		{}
	};

	struct LeafT :
		public BaseT
	{
		std::unique_ptr<T[]> const Data;

		LeafT(std::unique_ptr<T[]> pData) :
			BaseT{1, false},
			Data{std::move(pData)}
		{}
	};

	BranchT const & asBranch() const
	{
		return *static_cast<BranchT const *>(mPointer);
	}

	LeafT const & asLeaf() const
	{
		return *static_cast<LeafT const *>(mPointer);
	}

	BaseT const * mPointer;

	BaseT const * operator->() const
	{
		return mPointer;
	}

	public:
	using PairT = std::pair<RopeNodeT, RopeNodeT>;

	RopeNodeT(std::unique_ptr<T[]> Data) :
		mPointer{new LeafT{
			std::move(Data)
		}}
	{}

	RopeNodeT(RopeNodeT Left, std::size_t LeftSize, RopeNodeT Right) :
		mPointer{new BranchT{
			std::move(Left),
			LeftSize,
			std::move(Right)
		}}
	{}

	RopeNodeT(std::nullptr_t) :
		mPointer{nullptr}
	{}

	RopeNodeT() :
		RopeNodeT{nullptr}
	{}

	RopeNodeT(RopeNodeT const & Other)
	{
		mPointer = Other.mPointer;
		if (mPointer == nullptr) return;
		++mPointer->Count;
	}

	RopeNodeT(RopeNodeT && Other) :
		RopeNodeT{}
	{
		Other.swap(*this);
	}

	~RopeNodeT()
	{
		if (mPointer == nullptr || --mPointer->Count != 0) return;
		if (mPointer->IsBranch) delete &asBranch();
		else delete &asLeaf();
	}

	void operator=(RopeNodeT && Other)
	{
		RopeNodeT Temp;
		Other.swap(Temp);
		Temp.swap(*this);
	}

	bool operator==(std::nullptr_t) const
	{
		return mPointer == nullptr;
	}

	bool operator!=(std::nullptr_t) const
	{
		return mPointer != nullptr;
	}

	void swap(RopeNodeT & Other)
	{
		std::swap(mPointer, Other.mPointer);
	}

	static PairT split(RopeNodeT const & Node, std::size_t Size, std::size_t Index)
	{
		if (Node == nullptr) return {nullptr, nullptr};
		
		if (Node->IsBranch) {
			auto & Branch = Node.asBranch();
			
			if (Index < Branch.LeftSize) {
				auto Pair = split(Branch.Left, Branch.LeftSize, Index);				
				return PairT{
					std::move(Pair.first),
					RopeNodeT{std::move(Pair.second), Branch.LeftSize - Index, Branch.Right}
				};
			}
			else {
				auto Pair = split(Branch.Right, Size - Branch.LeftSize, Index - Branch.LeftSize);
				return PairT{
					RopeNodeT{Branch.Left, Branch.LeftSize, std::move(Pair.first)},
					std::move(Pair.second)
				};
			}
		}
		else {
			auto & Leaf = Node.asLeaf();

			T * Data = Leaf.Data.get();
			std::unique_ptr<T[]> Left{new T[Index]};
			std::unique_ptr<T[]> Right{new T[Size - Index]};
			std::copy(Data, Data + Index, Left.get());
			std::copy(Data + Index, Data + Size, Right.get());
			return PairT{std::move(Left), std::move(Right)};
		}
	}

	template<typename FunctorT>
	static void iterate(RopeNodeT const & Node, std::size_t Size, FunctorT Functor)
	{
		if (Node == nullptr) return;

		if (Node->IsBranch) {
			auto & Branch = Node.asBranch();
			iterate(Branch.Left, Branch.LeftSize, Functor);
			iterate(Branch.Right, Size - Branch.LeftSize, Functor);
		}
		else {
			auto & Leaf = Node.asLeaf();
			Functor(Leaf.Data.get(), Size);
		}
	}
};

template<typename T>
class RopeT
{
	private:
	RopeNodeT<T> mRoot;
	std::size_t mSize;

	RopeT(RopeNodeT<T> Node, std::size_t Size) :
		mRoot{std::move(Node)},
		mSize{Size}
	{}

	public:
	RopeT() :
		mSize{0}
	{}

	void append(T const * Pointer, std::size_t Size)
	{
		std::unique_ptr<T[]> Data{new T[Size]};
		std::copy(Pointer, Pointer + Size, Data.get());

		mRoot = RopeNodeT<T>{std::move(mRoot), mSize, std::move(Data)},
		mSize += Size;
	}

	void prepend(T const * Pointer, std::size_t Size)
	{
		std::unique_ptr<T[]> Data{new T[Size]};
		std::copy(Pointer, Pointer + Size, Data.get());

		mRoot = RopeNodeT<T>{std::move(Data), Size, std::move(mRoot)};
		mSize += Size;
	}

	void insert(std::size_t Index, T const * Pointer, std::size_t Size)
	{
		assert(Index <= mSize);

		std::unique_ptr<T[]> Data{new T[Size]};
		std::copy(Pointer, Pointer + Size, Data.get());

		auto Pair = RopeNodeT<T>::split(std::move(mRoot), mSize, Index);
		mRoot = RopeNodeT<T>{
			RopeNodeT<T>{
				std::move(Pair.first),
				Index,
				std::move(Data)
			},
			Index + Size,
			std::move(Pair.second)
		};
		mSize += Size;
	}

	void remove(std::size_t Index, std::size_t Size)
	{
		assert(Index + Size <= mSize);

		auto Pair1 = RopeNodeT<T>::split(std::move(mRoot), mSize, Index);
		auto Pair2 = RopeNodeT<T>::split(std::move(Pair1.second), mSize - Index, Size);

		mRoot = RopeNodeT<T>{
			std::move(Pair1.first),
			Index,
			std::move(Pair2.second)
		};

		mSize -= Size;
	}

	void removeFront(std::size_t Size)
	{
		assert(Size <= mSize);

		auto Pair = RopeNodeT<T>::split(std::move(mRoot), mSize, Size);
		mRoot = std::move(Pair.second);
		mSize -= Size;
	}

	void removeBack(std::size_t Size)
	{
		assert(Size <= mSize);

		auto Pair = RopeNodeT<T>::split(std::move(mRoot), mSize, mSize - Size);
		mRoot = std::move(Pair.first);
		mSize -= Size;
	}

	void clear()
	{
		mRoot = nullptr;
		mSize = 0;
	}

	template<typename FunctorT>
	void iterate(FunctorT Functor)
	{
		RopeNodeT<T>::iterate(mRoot, mSize, Functor);
	}
	
	std::size_t getSize()
	{
		return mSize;
	}
};

}
}
