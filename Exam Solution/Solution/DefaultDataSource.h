#pragma once

#include "DataSource.h"

template <typename T>
class DefaultDataSource : public DataSource<T>
{
public:
	DefaultDataSource* clone() const override;

	T getNext() override;
	DataSourceArray<T> getNext(size_t count) override;

	bool reset() override;
	bool hasNext() override;
};

// Too short of an implementation to put it into .inl file

template<typename T>
inline DefaultDataSource<T>* DefaultDataSource<T>::clone() const
{
	return new DefaultDataSource(*this);
}

template<typename T>
inline T DefaultDataSource<T>::getNext()
{
	return T();
}

template<typename T>
inline DataSourceArray<T> DefaultDataSource<T>::getNext(size_t count)
{
	if (count == 0)
		return DataSourceArray<T>{ nullptr, 0 };

	return DataSourceArray<T>{ new T[count]{}, count };
}

template<typename T>
inline bool DefaultDataSource<T>::reset()
{
	return true;
}

template<typename T>
inline bool DefaultDataSource<T>::hasNext()
{
	return true;
}
