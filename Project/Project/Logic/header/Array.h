#ifndef ARRAY_H
#define ARRAY_H

template<typename T>
class Array
{
private:
	T * data;
	int size;
	int capacity;
public:
	static const int DEFAULT_SIZE = 10;

	Array() : size(0), capacity(DEFAULT_SIZE)
	{
		data = new T[capacity];
	}

	Array(const Array& ref) : size(ref.size), capacity(ref.capacity)
	{
		data = new T[capacity];
		for (int i = 0; i<size; i++)
		{
			data[i] = ref.data[i];
		}
	}

	Array(int initialSize) : size(0), capacity(initialSize)
	{
		data = new T[capacity];
	}

	virtual ~Array()
	{
		delete[] data;
	}

	Array& operator=(const Array& ref)
	{
		if (ref.capacity > capacity)
		{
			capacity = ref.capacity;

			delete[] data;
			data = new T[capacity];
		}

		size = ref.size;
		for (int i = 0; i<size; i++)
		{
			data[i] = ref.data[i];
		}

		return *this;
	}

	T& operator[](int index)
	{
		// TODO: Check if this is slow and if so, remove it
		assert(index >= 0 && index < size);

		return data[index];
	}

	T& at(int index)
	{
		// TODO: Check if this is slow and if so, remove it
		assert(index >= 0 && index < size);

		return data[index];
	}

	void add(T item)
	{
		// Expand if memory is full
		if (size >= capacity)
		{
			capacity *= 2;

			T* tempData = new T[capacity];
			for (int i = 0; i<size; i++)
			{
				tempData[i] = data[i];
			}

			delete[] data;
			data = tempData;
		}

		// Add the new item
		data[size] = item;
		size++;
	}

	void removeItem(const T& item)
	{
		int index = find(item);
		if (index >= 0)
		{
			removeAt(index);
		}
	}

	void removeAt(int index)
	{
		assert(index >= 0 && index <= size);

		// Swap the last item with the one we're removing
		data[index] = data[size - 1];
		size--;
	}

	void clear()
	{
		size = 0;
	}

	void reserve(int newCapacity)
	{
		if (newCapacity > capacity)
		{
			capacity = newCapacity;

			T* tempData = new T[capacity];
			for (int i = 0; i<size; i++)
			{
				tempData[i] = data[i];
			}

			delete[] data;
			data = tempData;
		}
	}

	int find(const T& item)
	{
		// Linear search
		int result = -1;
		for (int i = 0; i<size; i++)
		{
			if (data[i] == item)
			{
				result = i;
			}
		}

		return result;
	}

	T* getData() { return data; }
	int getSize() const { return size; }
	int getCapacity() const { return capacity; }
};
#endif
