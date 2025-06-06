#pragma once

template <typename T>
struct DataSourceArray
{
	T* array;
	size_t size;
};

template <typename T>
class DataSource
{
public:
	virtual ~DataSource() noexcept = default;
	operator bool();
	T operator ()();

	virtual DataSource* clone() const = 0;

	virtual T getNext() = 0;
	virtual DataSourceArray<T> getNext(size_t count) = 0;

	virtual bool reset() = 0;
	virtual bool hasNext() = 0;
};

template <typename T>
DataSource<T>& operator >>(DataSource<T>& dataSource, T& value)
{
	value = dataSource.getNext();
	return dataSource;
}

template<typename T>
inline DataSource<T>::operator bool()
{
	return hasNext();
}

template<typename T>
inline T DataSource<T>::operator()()
{
	return getNext();
}