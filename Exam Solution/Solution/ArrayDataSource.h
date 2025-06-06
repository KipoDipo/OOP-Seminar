#pragma once

#include "DataSource.h"
#include "DataSourceExcpetions.h"

template<typename T>
class ArrayDataSource : public DataSource<T>
{
public:
	ArrayDataSource(const T* array, size_t size);

	ArrayDataSource(const ArrayDataSource& other);
	ArrayDataSource(ArrayDataSource&& other) noexcept;

	~ArrayDataSource() noexcept override;

	ArrayDataSource& operator=(const ArrayDataSource& other);
	ArrayDataSource& operator=(ArrayDataSource&& other) noexcept;

	ArrayDataSource* clone() const override;

	ArrayDataSource& operator+=(const T& value);

	ArrayDataSource& operator--();
	ArrayDataSource operator--(int);

	T getNext() override;
	DataSourceArray<T> getNext(size_t count) override;

	bool reset() override;
	bool hasNext() override;

private:
	void nullify();
	bool hasEnough(size_t count) const;

private:
	T* array;
	size_t size;
	size_t position;
};

template <typename T>
ArrayDataSource<T> operator+(ArrayDataSource<T> lhs, const T& rhs);

#include "ArrayDataSource.inl"

template<typename T>
inline ArrayDataSource<T> operator+(ArrayDataSource<T> lhs, const T& rhs)
{
	return lhs += rhs;
}
