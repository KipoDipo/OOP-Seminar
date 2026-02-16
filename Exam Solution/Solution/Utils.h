#pragma once
#pragma warning (disable: 4996)

template <typename T>
inline T* copyArray(const T* arr, size_t size, size_t capacity)
{
	if (arr == nullptr)
		return nullptr;

	if (size > capacity)
		throw std::invalid_argument("Size can not be larger than capacity!");

	T* arrayCopy = new T[capacity];

	try
	{
		for (size_t i = 0; i < size; i++)
		{
			// This assignment may throw an exception
			arrayCopy[i] = arr[i];
		}
	}
	catch (...)
	{
		delete[] arrayCopy;
		throw;
	}

	return arrayCopy;
}

template <typename T>
inline T* copyArray(const T* arr, size_t size)
{
	return copyArray(arr, size, size);
}

inline char* copyString(const char* str)
{
    return strcpy(new char[strlen(str) + 1], str);
}