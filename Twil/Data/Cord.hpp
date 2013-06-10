#pragma once

#include <cassert>
#include <iostream>
#include <limits>
#include <string>
#include <type_traits>

template<
	typename T,
	std::size_t TargetBranchSize = 512,
	std::size_t TargetLeafSize = 512,
	std::size_t MaximumSize = std::numeric_limits<std::size_t>::max()>
class BasicRopeT
{
	private:
	struct NodeT
	{
		std::size_t Size;
		void * Pointer;
	};

	// Compute the logarithm rounded up to the nearest int

	static std::size_t constexpr log(std::size_t Num, std::size_t Base, std::size_t Log)
	{
		return Num != 0 ? log(Num / Base, Base, Log + 1) : Log;
	}

	static std::size_t constexpr log(std::size_t Num, std::size_t Base)
	{
		return log(Num - 1, Base, 0);
	}

	static_assert(std::is_pod<T>::value, "T must be a pod");

	static std::size_t constexpr Order = TargetBranchSize  / sizeof(NodeT);
	static std::size_t constexpr BlockSize = TargetLeafSize / sizeof(T);

	static_assert(Order >= 3, "Order must be at least 3");

	static std::size_t constexpr MinimumOrder = (Order + 1) / 2;
	static std::size_t constexpr MinimumBlockSize = (BlockSize + 1) / 2;
	static std::size_t constexpr StackSize = log(MaximumSize / MinimumBlockSize, MinimumOrder);

	struct BranchT
	{
		NodeT Children[Order];
	};

	struct LeafT
	{
		T Buffer[BlockSize];
	};

	struct BranchEntryT
	{
		std::size_t Size;
		std::size_t Index;
		BranchT * Pointer;
	};

	struct LeafEntryT
	{
		std::size_t Size;
		std::size_t Index;
		LeafT * Pointer;
	};

	NodeT mRoot;
	std::size_t mHeight;

	template<typename FunctorT>
	static void iterate(NodeT Node, std::size_t Height, FunctorT Functor)
	{
		if (Height != 0)
		{
			auto Branch = static_cast<BranchT *>(Node.Pointer);
			auto Size = Node.Size;
			std::size_t Index = 0;

			while (Size != 0)
			{
				iterate(Branch->Children[Index], Height - 1, Functor);
				Size -= Branch->Children[Index].Size;
				++Index;
			}
		}
		else
		{
			auto Leaf = static_cast<LeafT *>(Node.Pointer);
			Functor(Leaf->Buffer, Node.Size);
		}
	}

	static std::size_t getLength(BranchT * Branch, std::size_t Size)
	{
		std::size_t Index = 0;
		while (Size != 0)
		{
			Size -= Branch->Children[Index].Size;
			++Index;
		}
		return Index;
	}

	static void deleteNode(NodeT Node, std::size_t Height)
	{
		if (Height != 0)
		{
			auto Branch = static_cast<BranchT *>(Node.Pointer);
			std::size_t Index = 0;
			auto Size = Node.Size;

			while (Size != 0)
			{
				deleteNode(Branch->Children[Index], Height - 1);
				Size -= Branch->Children[Index].Size;
				++Index;
			}

			delete Branch;
		}
		else
		{
			auto Leaf = static_cast<LeafT *>(Node.Pointer);
			delete Leaf;
		}
	}

	template<typename KindT>
	static void merge(
		std::size_t Index,
		KindT * Orig, std::size_t OrigSize,
		KindT const * Data,	std::size_t DataSize)
	{
		std::char_traits<KindT>::move(
			Orig + Index + DataSize,
			Orig + Index,
			OrigSize - Index);
		std::char_traits<KindT>::copy(
			Orig + Index,
			Data,
			DataSize);
	}

	template<typename KindT>
	static void split(
		std::size_t Index,
		std::size_t LeftSize, std::size_t RightSize, KindT * Right,
		KindT * Orig, std::size_t OrigSize,
		KindT const * Data, std::size_t DataSize)
	{
		// Inserted data completely contained in left half
		if (Index <= LeftSize && Index + DataSize <= LeftSize)
		{
			std::char_traits<KindT>::copy(
				Right,
				Orig + OrigSize - RightSize,
				RightSize);
			std::char_traits<KindT>::move(
				Orig + Index + DataSize,
				Orig + Index,
				LeftSize - DataSize - Index);
			std::char_traits<KindT>::copy(
				Orig + Index,
				Data,
				DataSize);
		}
		// Inserted data completely contained in right half
		else if (Index >= LeftSize && Index + DataSize >= LeftSize)
		{
			std::char_traits<KindT>::copy(
				Right,
				Orig + LeftSize,
				Index - LeftSize);
			std::char_traits<KindT>::copy(
				Right + Index - LeftSize,
				Data,
				DataSize);
			std::char_traits<KindT>::copy(
				Right + Index + DataSize - LeftSize,
				Orig + Index,
				OrigSize - Index);

		}
		// Inserted data split across both halves
		else
		{
			std::char_traits<KindT>::copy(
				Right,
				Data + LeftSize - Index,
				DataSize + Index - LeftSize);
			std::char_traits<KindT>::copy(
				Right + DataSize + Index - LeftSize,
				Orig + Index,
				OrigSize - Index);
			std::char_traits<KindT>::copy(
				Orig + Index,
				Data,
				LeftSize - Index);
		}
	}

	template<typename KindT>
	static void remove(KindT * Data, std::size_t DataSize, std::size_t Index, std::size_t Length)
	{
		std::char_traits<KindT>::move(
			Data + Index,
			Data + Index + Length,
			DataSize - Index - Length);
	}

	LeafEntryT seek(BranchEntryT * First, BranchEntryT * Last, NodeT Current, std::size_t Index)
	{
		while (First != Last)
		{
			auto Branch = static_cast<BranchT *>(Current.Pointer);

			std::size_t BranchIndex = 0;
			while (true)
			{
				auto ChildSize = Branch->Children[BranchIndex].Size;
				if (Index <= ChildSize) break;
				Index -= ChildSize;
				++BranchIndex;
			}
			BranchEntryT Entry;
			Entry.Size = Current.Size;
			Entry.Index = BranchIndex;
			Entry.Pointer = Branch;
			*--Last = Entry;
			Current = Branch->Children[BranchIndex];
		}

		LeafEntryT Entry;
		Entry.Size = Current.Size;
		Entry.Index = Index;
		Entry.Pointer = static_cast<LeafT *>(Current.Pointer);
		return Entry;
	}

	void updateSizes(BranchEntryT * First, BranchEntryT * Last, std::size_t DataSize)
	{
		while (First != Last)
		{
			auto & Entry = *First++;
			Entry.Pointer->Children[Entry.Index].Size += DataSize;
		}

		mRoot.Size += DataSize;
	}

	void insert(
		BranchEntryT * First, BranchEntryT * Last,
		T const * Data, std::size_t DataSize,
		LeafEntryT & Entry)
	{
		auto Sum = Entry.Size + DataSize;

		// If we have room for the data in this leaf, we are done
		if (Sum <= BlockSize)
		{
			merge(Entry.Index, Entry.Pointer->Buffer, Entry.Size, Data, DataSize);
			updateSizes(First, Last, DataSize);
			Entry.Index += DataSize;
			Entry.Size += DataSize;
			return;
		}

		// No room, split into 2 and insert the first half in the parent
		auto LeftSize = Sum / 2;
		auto RightSize = Sum - LeftSize;
		auto Right = new LeafT;
		split(
			Entry.Index,
			LeftSize, RightSize, Right->Buffer,
			Entry.Pointer->Buffer, Entry.Size,
			Data, DataSize);
		insert(First, Last, DataSize, LeftSize, {RightSize, Right});
	}

	void insert(
		BranchEntryT * First, BranchEntryT * Last,
		std::size_t DataSize, std::size_t LeftSize,
		NodeT RightNode)
	{
		while (First != Last)
		{
			auto & Entry = *First++;
			auto BranchLength = getLength(Entry.Pointer, Entry.Size);
			auto Sum = BranchLength + 1;
			Entry.Pointer->Children[Entry.Index].Size = LeftSize;

			// If we have room for the child we are done
			if (Sum <= Order)
			{
				merge(Entry.Index + 1, Entry.Pointer->Children, BranchLength, &RightNode, 1);
				updateSizes(First, Last, DataSize);
				return;
			}

			// No room, split into 2 and insert the first half in the parent
			auto LeftLength = Sum / 2;
			auto RightLength = Sum - LeftLength;
			auto Right = new BranchT;
			split(
				Entry.Index + 1,
				LeftLength, RightLength, Right->Children,
				Entry.Pointer->Children, BranchLength,
				&RightNode, 1);
			std::size_t RightSize = 0;
			for (std::size_t I = 0; I != RightLength; ++I) RightSize += Right->Children[I].Size;
			RightNode = {RightSize, Right};
			LeftSize = Entry.Size + DataSize - RightSize;
		}

		// We have reached the root, grow upward
		auto Branch = new BranchT;
		Branch->Children[0].Pointer = mRoot.Pointer;
		Branch->Children[0].Size = LeftSize;
		Branch->Children[1] = RightNode;
		mRoot.Pointer = Branch;
		mRoot.Size = LeftSize + RightNode.Size;
		mHeight++;
	}

	public:
	BasicRopeT()
	:
		mRoot{0, new LeafT},
		mHeight{0}
	{}

	~BasicRopeT()
	{
		deleteNode(mRoot, mHeight);
	}

//	void remove(std::size_t Index, std::size_t DataSize)
//	{
//		assert(Index + DataSize <= mRoot.Size);

//		BranchEntryT Stack[StackSize];

//		auto Entry = seek(Stack, Stack + mHeight, mRoot, Index);

//	}

	void insert(std::size_t Index, T const * Data, std::size_t DataSize)
	{
		assert(Index <= mRoot.Size);

		BranchEntryT Stack[StackSize];

		while (DataSize > BlockSize)
		{
			auto Entry = seek(Stack, Stack + mHeight, mRoot, Index);
			insert(Stack, Stack + mHeight, Data, BlockSize, Entry);
			Data += BlockSize;
			DataSize -= BlockSize;
			Index += BlockSize;
		}

		auto Entry = seek(Stack, Stack + mHeight, mRoot, Index);
		insert(Stack, Stack + mHeight, Data, DataSize, Entry);
	}

	void insert(std::size_t Index, T const * Data)
	{
		insert(Index, Data, std::char_traits<T>::length(Data));
	}

	void append(T const * Data, std::size_t DataSize)
	{
		insert(getSize(), Data, DataSize);
	}

	void append(T const * Data)
	{
		append(Data, std::char_traits<T>::length(Data));
	}

	void prepend(T const * Data, std::size_t DataSize)
	{
		insert(0, Data, DataSize);
	}

	void prepend(T const * Data)
	{
		prepend(Data, std::char_traits<T>::length(Data));
	}

	template<typename FunctorT>
	void iterate(FunctorT Functor) const
	{
		iterate(mRoot, mHeight, Functor);
	}

	std::size_t getHeight() const
	{
		return mHeight;
	}

	std::size_t getSize() const
	{
		return mRoot.Size;
	}
};

using RopeT = BasicRopeT<char>;

template<typename StreamT>
StreamT & operator <<(StreamT & Stream, RopeT const & Rope)
{
	Rope.iterate([&](char const * Data, std::size_t Size)
	{
		Stream.write(Data, Size);
	});

	return Stream;
}
