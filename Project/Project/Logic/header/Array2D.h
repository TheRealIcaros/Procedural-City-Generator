#ifndef ARRAY2D_H
#define ARRAY2D_H

#include <assert.h>

template<typename T>
class Array2D
{
private:
	int width;
	int height;
	T* data;
public:
	static const int DEFAULT_SIZE = 10;

	Array2D() : width(DEFAULT_SIZE), height(DEFAULT_SIZE)
	{
		data = new T[width*height];
	}

	Array2D(int w, int h) : width(w), height(h)
	{
		data = new T[width*height];
	}

	Array2D(const Array2D& ref) : width(ref.width), height(ref.height)
	{
		data = new T[width*height];

		const int SIZE = width * height;
		for (int i = 0; i<SIZE; i++)
		{
			data[i] = ref.data[i];
		}
	}

	virtual ~Array2D()
	{
		delete[] data;
	}

	Array2D& operator=(const Array2D& ref)
	{
		resize(ref.width, ref.height);

		const int SIZE = width * height;
		for (int i = 0; i<SIZE; i++)
		{
			data[i] = ref.data[i];
		}

		return *this;
	}

	T& operator[](int index)
	{
		assert(index >= 0 && index < width*height);

		return data[index];
	}

	T& at(int x, int y)
	{
		assert(x >= 0 && x < width && y >= 0 && y < height);

		return data[y*width + x];
	}

	void fill(const T& value)
	{
		const int SIZE = width * height;
		for (int i = 0; i<SIZE; i++)
		{
			data[i] = value;
		}
	}

	void resize(int w, int h)
	{
		delete[] data;

		width = w;
		height = h;
		data = new T[width*height];
	}

	int getWidth() const { return width; }
	int getHeight() const { return height; }
	T* getData() { return data; }
};

#endif