#pragma once

#include "Generator.h"
#include "DataSource.h"
#include "DataSourceExcpetions.h"

// Big note with this class!
// The generator is being borrowed (this is by design).
// This means that if it gets deleted either by 
// stack deallocation or manually with 'delete' 
// an object of this class will misbehave.

template <typename T>
class GeneratorDataSource : public DataSource<T>
{
public:
	GeneratorDataSource(Generator<T>* generator);

	GeneratorDataSource<T>* clone() const override;

	T getNext() override;

	bool reset() override;
	bool hasNext() override;
	DataSourceArray<T> getNext(size_t count) override;

private:
	Generator<T>* generator;
};

#include "GeneratorDataSource.inl"
