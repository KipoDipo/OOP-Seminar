#pragma once

#include "ArrayDataSource.h"

template <typename T>
class AlternateDataSource : public DataSource<T>
{
public:
	AlternateDataSource(const DataSource<T>* const* dataSources, size_t size);

	AlternateDataSource(const AlternateDataSource& other);
	AlternateDataSource(AlternateDataSource&& other) noexcept;

	~AlternateDataSource() noexcept override;

	AlternateDataSource& operator=(const AlternateDataSource& other);
	AlternateDataSource& operator=(AlternateDataSource&& other) noexcept;

	AlternateDataSource* clone() const override;

	T getNext() override;
	DataSourceArray<T> getNext(size_t count) override;

	bool reset() override;
	bool hasNext() override;

private:
	void nullify();
	bool hasEnough(size_t count) const;
	static DataSource<T>** copyDataSources(const DataSource<T>* const* dataSources, size_t size);

private:
	DataSource<T>** dataSources;
	size_t size;
	size_t position;
};

#include "AlternateDataSource.inl"
