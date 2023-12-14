#pragma once

#include <atomic>
#include <iostream>
#include <cassert>

// let T represent the type of object stored in the queue
template<typename T>
class TCircularQueue
{
	// pointer to the underlying array
	T* Arr;

	// capacity of the raw array
	size_t RawCapacity = 16;

	// the first index to read from (aka front)
	std::atomic<size_t> ReadIndex;
	// the next index to write to (aka back)
	std::atomic<size_t> WriteIndex;

public:
	// dynamically allocates the array
	TCircularQueue()
	{
		RawCapacity = 16;
		Arr = new T[RawCapacity];
		ReadIndex.store(0);
		WriteIndex.store(0);
	}
	TCircularQueue(size_t minCapacity)
	{
		RawCapacity = minCapacity;
		Arr = new T[RawCapacity];
		ReadIndex.store(0);
		WriteIndex.store(0);
	}
	// move constructor
	TCircularQueue(TCircularQueue&& other)
	{
		this = &other;
	}
	// copy constructor
	TCircularQueue(const TCircularQueue& other)
	{
		*this = other;
	}
	// cleans up any dynamically allocated data
	~TCircularQueue()
	{
		delete[] Arr;
	}

	// move assignment
	TCircularQueue& operator =(TCircularQueue&& other)
	{
		Arr = other.Arr;
		&RawCapacity = &other.RawCapacity;
		&ReadIndex = &other.ReadIndex;
		&WriteIndex = &other.WriteIndex;
		return *this;
	}
	// copy assignment
	TCircularQueue& operator =(const TCircularQueue& other)
	{
		Arr = new T[other.RawCapacity];
		for (size_t i = 0; i < other.RawCapacity; i++)
		{
			Arr[i] = other.Arr[i];
		}

		RawCapacity = other.RawCapacity;
		ReadIndex = other.ReadIndex.load();
		WriteIndex = other.WriteIndex.load();
		return *this;
	}

	// writes a value at the write index
	void Push(const T& val)
	{
		assert(Size() < Capacity() && "No more room for queue!");
		if (Size() < Capacity())
		{
			WriteIndex = WriteIndex.load() % RawCapacity;

			Arr[WriteIndex.load()] = val;

			WriteIndex++;
		}
	}
	// returns true if it pops the value at the read index, otherwise false
	bool Pop()
	{
		if (Empty()) return false;

		ReadIndex = ReadIndex.load() % RawCapacity;

		Arr[ReadIndex.load()].~T();
		ReadIndex++;
		return true;
	}

	// retrieves the value at the front (read index)
	const T& Front() const
	{
		return Arr[ReadIndex.load()];
	}

	// returns true if all elements in the array are popped
	bool Empty() const
	{
		return Size() == 0;
	}
	// returns the current number of elements pushed
	size_t Size() const
	{
		if (WriteIndex < ReadIndex)
		{
			return WriteIndex - (RawCapacity - ReadIndex);
		}

		return WriteIndex - ReadIndex;
	}
	// returns the maximum number of elements that can be pushed
	size_t Capacity() const
	{
		return RawCapacity;
	}

	void Reserve(size_t minCapacity)
	{
		if (RawCapacity < minCapacity)
		{
			// Remake the array with the new capacity
			T* newArray = new T[minCapacity];
			for (size_t i = 0; i < RawCapacity; i++)
			{
				newArray[i] = Arr[i];
			}

			Arr = newArray;

			RawCapacity = minCapacity;
		}
	}
};
