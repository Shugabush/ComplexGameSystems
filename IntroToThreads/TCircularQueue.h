#pragma once

#include <atomic>
#include <iostream>

// let T represent the type of object stored in the queue
template<typename T>
class TCircularQueue
{
	// pointer to the underlying array
	T* Arr;

	// capacity of the raw array
	static const size_t RAW_CAPACITY = 16;

	// the first index to read from (aka front)
	std::atomic<size_t> ReadIndex;
	// the next index to write to (aka back)
	std::atomic<size_t> WriteIndex;

public:
	// dynamically allocates the array
	TCircularQueue()
	{
		Arr = new T[RAW_CAPACITY];
		ReadIndex.store(0);
		WriteIndex.store(0);
	}
	// cleans up any dynamically allocated data
	~TCircularQueue()
	{
		delete[] Arr;
	}

	// returns true if it writes a value at the write index, otherwise false
	bool Push(const T& val)
	{
		if (Size() < Capacity())
		{
			WriteIndex = WriteIndex.load() % RAW_CAPACITY;

			Arr[WriteIndex.load()] = val;

			WriteIndex++;

			return true;
		}
		return false;
	}
	// returns true if it pops the value at the read index, otherwise false
	bool Pop()
	{
		ReadIndex = ReadIndex.load() % RAW_CAPACITY;

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
			return WriteIndex - (RAW_CAPACITY - ReadIndex);
		}

		return WriteIndex - ReadIndex;
	}
	// returns the maximum number of elements that can be pushed
	size_t Capacity() const
	{
		return RAW_CAPACITY;
	}
};
