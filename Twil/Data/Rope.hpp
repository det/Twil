#pragma once

#include <algorithm>
#include <cassert>
#include <iostream>
#include <string>

namespace Twil {
namespace Data {

static std::uint64_t const FibonacciTable[64] = {
	1UL, 2UL, 3UL, 5UL, 8UL, 13UL, 21UL, 34UL, 55UL, 89UL, 144UL, 233UL, 377UL, 610UL, 987UL,
	1597UL, 2584UL, 4181UL, 6765UL, 10946UL, 17711UL, 28657UL, 46368UL, 75025UL, 121393UL, 196418UL,
	317811UL, 514229UL, 832040UL, 1346269UL, 2178309UL, 3524578UL, 5702887UL, 9227465UL, 14930352UL,
	24157817UL, 39088169UL, 63245986UL, 102334155UL, 165580141UL, 267914296UL, 433494437UL,
	701408733UL, 1134903170UL, 1836311903UL, 2971215073UL, 4807526976UL, 7778742049UL,
	12586269025UL, 20365011074UL, 32951280099UL, 53316291173UL, 86267571272UL, 139583862445UL,
	225851433717UL, 365435296162UL, 591286729879UL, 956722026041UL, 1548008755920UL,
	2504730781961UL, 4052739537881UL, 6557470319842UL, 10610209857723UL, 17167680177565UL};

template<typename T, std::size_t BlockSize = 512>
class RopeT
{
private:
	struct NodeT
	{
		std::uint16_t Count;
		std::uint16_t Height;
	};

	struct BranchT
	:
		public NodeT
	{
		NodeT * Left;
		std::size_t LeftSize;
		NodeT * Right;
	};

	struct LeafT
	:
		public NodeT
	{
		T First;
	};

	struct StackEntryT
	{
		NodeT * Node;
		std::size_t Size;
		std::size_t Index;
	};

	struct StackT
	{
		StackEntryT Pointer[64];
		std::size_t Size = 0;
	};

	struct BalancerT
	{
		StackT & Stack;

		void operator()(NodeT * Node, std::size_t Size)
		{
			increment(Node);

			std::size_t Index = 0;
			std::size_t A = 1;
			std::size_t B = 2;
			while (Size >= B)
			{
				A += B;
				std::swap(A, B);
				++Index;
			}

			if (Stack.Size == 0 || Index < Stack.Pointer[Stack.Size - 1].Index)
			{
				Stack.Pointer[Stack.Size++] = {Node, Size, Index};
				return;
			}

			auto Entry = Stack.Pointer[--Stack.Size];

			if (Index == Entry.Index) ++Index;
			else
			{
				while (Stack.Size != 0 && Index > Stack.Pointer[Stack.Size - 1].Index)
				{
					auto Top = Stack.Pointer[--Stack.Size];
					Entry.Node = makeBranch(Top.Node, Top.Size, Entry.Node, Entry.Size);
					Entry.Size += Top.Size;
				}
			}

			Entry.Node = makeBranch(Entry.Node, Entry.Size, Node, Size);
			Entry.Size += Size;
			Entry.Index = Index;

			while (Stack.Size != 0 && Entry.Index == Stack.Pointer[Stack.Size - 1].Index)
			{
				auto Top = Stack.Pointer[--Stack.Size];
				Entry.Node = makeBranch(Top.Node, Top.Size, Entry.Node, Entry.Size);
				Entry.Size += Top.Size;
				++Entry.Index;
			}

			Stack.Pointer[Stack.Size++] = Entry;
		}

		NodeT * finish()
		{
			auto Entry = Stack.Pointer[--Stack.Size];

			while (Stack.Size != 0)
			{
				auto Top = Stack.Pointer[--Stack.Size];
				Entry.Node = makeBranch(Top.Node, Top.Size, Entry.Node, Entry.Size);
				Entry.Size += Top.Size;
			}

			return Entry.Node;
		}
	};

	NodeT * mRoot;
	std::size_t mSize;

	static NodeT * makeBranch(
		NodeT * Left, std::size_t LeftSize,
		NodeT * Right, std::size_t RightSize)
	{
		if (Left->Height == 0 && Right->Height == 0)
		{
			auto LeftLeaf = static_cast<LeafT *>(Left);
			auto RightLeaf = static_cast<LeafT *>(Right);

			if (LeftSize + RightSize <= BlockSize)
			{
				auto Leaf = makeLeaf(LeftLeaf, LeftSize, RightLeaf, RightSize);
				decrement(Left);
				decrement(Right);
				return Leaf;
			}
		}
		else if (Left->Height != 0 && Right->Height == 0)
		{
			auto LeftBranch = static_cast<BranchT *>(Left);
			auto RightLeaf = static_cast<LeafT *>(Right);

			if (LeftBranch->Right->Height == 0)
			{
				auto LeftRightLeaf = static_cast<LeafT *>(LeftBranch->Right);
				auto LeftRightSize = LeftSize - LeftBranch->LeftSize;
				auto LeftLeft = LeftBranch->Left;
				auto LeftLeftSize = LeftBranch->LeftSize;

				if (LeftRightSize + RightSize <= BlockSize)
				{
					auto Leaf = makeLeaf(LeftRightLeaf, LeftRightSize, RightLeaf, RightSize);
					increment(LeftLeft);
					decrement(Left);
					decrement(Right);
					return makeBranch(LeftLeft,	LeftLeftSize, Leaf, LeftRightSize + RightSize);
				}
			}
		}

		auto Branch = new BranchT;
		Branch->Count = 1;
		Branch->Height = std::max(Left->Height, Right->Height) + 1;
		Branch->Left = Left;
		Branch->LeftSize = LeftSize;
		Branch->Right = Right;
		return Branch;
	}

	static LeafT * makeLeaf(T const * Data, std::size_t Size)
	{
		auto LeafSize = sizeof(NodeT) + sizeof(T) * Size;
		auto Leaf = reinterpret_cast<LeafT *>(operator new(LeafSize));
		Leaf->Count = 1;
		Leaf->Height = 0;
		std::char_traits<T>::copy(&Leaf->First, Data, Size);
		return Leaf;
	}

	static LeafT * makeLeaf(
		LeafT * Left, std::size_t LeftSize,
		LeafT * Right, std::size_t RightSize)
	{
		auto LeafSize = sizeof(NodeT) + sizeof(T) * (LeftSize + RightSize);
		auto Leaf = reinterpret_cast<LeafT *>(operator new(LeafSize));
		Leaf->Count = 1;
		Leaf->Height = 0;
		std::char_traits<T>::copy(&Leaf->First, &Left->First, LeftSize);
		std::char_traits<T>::copy(&Leaf->First + LeftSize, &Right->First, RightSize);
		return Leaf;
	}

	static NodeT * makeEmpty()
	{
		return new NodeT{1, 0};
	}

	static void increment(NodeT * Node)
	{
		++Node->Count;
	}

	static void decrement(NodeT * Node)
	{
		if (--Node->Count != 0) return;

		if (Node->Height == 0)
		{
			auto Leaf = static_cast<LeafT *>(Node);
			operator delete(Leaf);
		}
		else
		{
			auto Branch = static_cast<BranchT *>(Node);
			decrement(Branch->Left);
			decrement(Branch->Right);
			delete Branch;
		};
	}

	static NodeT * splitBefore(NodeT * Node, std::size_t Size, std::size_t Index)
	{
		if (Node->Height == 0)
		{
			auto Leaf = static_cast<LeafT *>(Node);
			return makeLeaf(&Leaf->First, Index);
		}
		else
		{
			auto Branch = static_cast<BranchT *>(Node);
			if (Index < Branch->LeftSize)
			{
				return splitBefore(Branch->Left, Branch->LeftSize, Index);
			}
			else
			{
				increment(Branch->Left);
				return makeBranch(
					Branch->Left,
					Branch->LeftSize,
					splitBefore(Branch->Right, Size - Branch->LeftSize,	Index - Branch->LeftSize),
					Index - Branch->LeftSize);
			}
		}
	}

	static NodeT * splitAfter(NodeT * Node, std::size_t Size, std::size_t Index)
	{
		if (Node->Height == 0)
		{
			auto Leaf = static_cast<LeafT *>(Node);
			return makeLeaf(&Leaf->First + Index, Size - Index);
		}
		else
		{
			auto Branch = static_cast<BranchT *>(Node);
			if (Index < Branch->LeftSize)
			{
				increment(Branch->Right);
				return makeBranch(
					splitAfter(Branch->Left, Branch->LeftSize, Index),
					Branch->LeftSize - Index,
					Branch->Right,
					Size - Branch->LeftSize);
			}
			else
			{
				return splitAfter(Branch->Right, Size - Branch->LeftSize, Index - Branch->LeftSize);
			}
		}
	}

	template<typename FunctorT>
	static void iterateLeaves(NodeT * Node, std::size_t Size, FunctorT Functor)
	{
		if (Node->Height == 0)
		{
			auto Leaf = static_cast<LeafT *>(Node);
			Functor(Leaf, Size);
		}
		else
		{
			auto Branch = static_cast<BranchT *>(Node);
			iterateLeaves(Branch->Left, Branch->LeftSize, Functor);
			iterateLeaves(Branch->Right, Size - Branch->LeftSize, Functor);
		}
	}

	template<typename FunctorT>
	static void iterateBalancedNodes(NodeT * Node, std::size_t Size, FunctorT Functor)
	{
		if (Node->Height == 0 || Size >= FibonacciTable[Node->Height])
		{
			Functor(Node, Size);
		}
		else
		{
			auto Branch = static_cast<BranchT *>(Node);
			iterateBalancedNodes(Branch->Left, Branch->LeftSize, Functor);
			iterateBalancedNodes(Branch->Right, Size - Branch->LeftSize, Functor);
		}
	}

	void balanceIfNeeded()
	{
		if (mRoot->Height > 64) balance();
	}

public:
	RopeT()
	:
		mRoot{makeEmpty()},
		mSize{0}
	{}

	RopeT(T const * Data, std::size_t Size)
	{
		mRoot = makeLeaf(Data, Size);
		mSize = Size;
	}

	RopeT(T const * Data)
	:
		RopeT{Data, std::char_traits<T>::length(Data)}
	{}

	RopeT(RopeT const & Other)
	:
		mRoot{Other.mRoot},
		mSize{Other.mSize}
	{
		increment(mRoot);
	}

	~RopeT()
	{
		decrement(mRoot);
	}

	RopeT & operator =(RopeT const & Other)
	{
		decrement(mRoot);
		mRoot = Other.mRoot;
		mSize = Other.mSize;
		increment(mRoot);
	}

	void append(T const * Data, std::size_t Size)
	{
		mRoot = makeBranch(mRoot, mSize, makeLeaf(Data, Size), Size);
		mSize += Size;
		balanceIfNeeded();
	}

	void append(T const * Data)
	{
		append(Data, std::char_traits<T>::length(Data));
	}

	void prepend(T const * Data, std::size_t Size)
	{
		mRoot = makeBranch(makeLeaf(Data, Size), Size, mRoot, mSize);
		mSize += Size;
		balanceIfNeeded();
	}

	void prepend(T const * Data)
	{
		prepend(Data, std::char_traits<T>::length(Data));
	}

	void insert(std::size_t Index, T const * Data, std::size_t Size)
	{
		assert(Index <= mSize);

		auto Left = splitBefore(mRoot, mSize, Index);
		auto Right = splitAfter(mRoot, mSize, Index);
		decrement(mRoot);
		mRoot = makeBranch(
			makeBranch(Left, Index, makeLeaf(Data, Size), Size),
			Index + Size,
			Right,
			mSize - Index);
		mSize += Size;
		balanceIfNeeded();
	}

	void insert(std::size_t Index, T const * Data)
	{
		insert(Index, Data, std::char_traits<T>::length(Data));
	}

	void remove(std::size_t Index, std::size_t Size)
	{
		assert(Index + Size <= mSize);

		auto Left = splitBefore(mRoot, mSize, Index);
		auto Right = splitAfter(mRoot, mSize, Index + Size);
		decrement(mRoot);
		mRoot = makeBranch(Left, Index, Right, mSize - Index - Size);
		mSize -= Size;
		balanceIfNeeded();
	}

	void removeFront(std::size_t Size)
	{
		assert(Size <= mSize);

		auto Root = splitAfter(mRoot, mSize, Size);
		decrement(mRoot);
		mRoot = Root;
		mSize -= Size;
		balanceIfNeeded();
	}

	void removeBack(std::size_t Size)
	{
		assert(Size <= mSize);

		auto Root = splitBefore(mRoot, mSize, mSize - Size);
		decrement(mRoot);
		mRoot = Root;
		mSize -= Size;
		balanceIfNeeded();
	}

	void balance()
	{
		StackT Stack;
		BalancerT Balancer{Stack};
		iterateBalancedNodes(mRoot, mSize, Balancer);
		decrement(mRoot);
		mRoot = Balancer.finish();
	}

	void rebuild()
	{
		StackT Stack;
		BalancerT Balancer{Stack};
		iterateLeaves(mRoot, mSize, Balancer);
		decrement(mRoot);
		mRoot = Balancer.finish();
	}

	void clear()
	{
		decrement(mRoot);
		mRoot = makeEmpty();
		mSize = 0;
	}

	template<typename FunctorT>
	void iterate(FunctorT Functor)
	{
		iterateLeaves(mRoot, mSize, [=](LeafT * Leaf, std::size_t Size)
		{
			Functor(&Leaf->First, Size);
		});
	}

	std::size_t getSize()
	{
		return mSize;
	}

	std::uint16_t getHeight()
	{
		return mRoot->Height;
	}
};

}
}
