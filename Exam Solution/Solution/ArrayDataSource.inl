#include "ArrayDataSource.h"
#include "Utils.h"

template<typename T>
inline ArrayDataSource<T>::ArrayDataSource(const T* array, size_t size)
	: array(nullptr), size(size), position(0)
{
	if (size != 0)
		this->array = copyArray(array, size);
}

template<typename T>
inline ArrayDataSource<T>::ArrayDataSource(const ArrayDataSource& other)
	: ArrayDataSource(other.array, other.size)
{
	position = other.position;
}

template<typename T>
inline ArrayDataSource<T>::ArrayDataSource(ArrayDataSource&& other) noexcept
	: array(other.array), size(other.size), position(other.position)
{
	other.nullify();
}

template<typename T>
inline ArrayDataSource<T>::~ArrayDataSource() noexcept
{
	delete[] array;
}

template<typename T>
inline ArrayDataSource<T>& ArrayDataSource<T>::operator=(const ArrayDataSource& other)
{
	if (this == &other)
		return *this;

	T* copy = copyArray(other.array, other.size);
	delete[] array;
	array = copy;
	size = other.size;
	position = other.position;
}

template<typename T>
inline ArrayDataSource<T>& ArrayDataSource<T>::operator=(ArrayDataSource&& other) noexcept
{
	if (this == &other)
		return *this;

	array = other.array;
	size = other.size;
	position = other.position;

	other.nullify();
}

template<typename T>
inline ArrayDataSource<T>* ArrayDataSource<T>::clone() const
{
	return new ArrayDataSource(*this);
}

template<typename T>
inline ArrayDataSource<T>& ArrayDataSource<T>::operator+=(const T& value)
{
	T* arrayCopy = copyArray(array, size, size + 1);

	try 
	{
		arrayCopy[size] = value;
	}
	catch (...)
	{
		delete[] arrayCopy;
		throw;
	}

	delete[] array;
	array = arrayCopy;
	size++;

	return *this;
}

template<typename T>
inline ArrayDataSource<T>& ArrayDataSource<T>::operator--()
{
	if (position > 0)
		position--;

	return *this;
}

template<typename T>
inline ArrayDataSource<T> ArrayDataSource<T>::operator--(int)
{
	ArrayDataSource copy(*this);
	operator--();
	return copy;
}

template<typename T>
inline T ArrayDataSource<T>::getNext()
{
	if (position == size)
		throw EmptyDataSourceException();

	return array[position++];
}

template<typename T>
inline DataSourceArray<T> ArrayDataSource<T>::getNext(size_t count)
{
	if (count == 0)
		return DataSourceArray<T>{ nullptr, 0 };

	if (!hasEnough(count))
		throw InsufficientDataSourceException();

	T* elements = copyArray(array + position, count);
	position += count;

	return DataSourceArray<T>{ elements, count };
}

template<typename T>
inline bool ArrayDataSource<T>::reset()
{
	position = 0;
	return true;
}

template<typename T>
inline bool ArrayDataSource<T>::hasNext() 
{
	return position < size;
}

template<typename T>
inline bool ArrayDataSource<T>::hasEnough(size_t count) const
{
	size_t distance = size - position;
	return distance >= count;
}

template<typename T>
inline void ArrayDataSource<T>::nullify()
{
	array = nullptr;
	size = 0;
	position = 0;
}
