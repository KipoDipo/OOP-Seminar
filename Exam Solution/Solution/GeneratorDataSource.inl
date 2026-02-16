template<typename T>
inline GeneratorDataSource<T>::GeneratorDataSource(Generator<T>* generator)
	: generator(generator)
{
}

template<typename T>
inline GeneratorDataSource<T>* GeneratorDataSource<T>::clone() const
{
	return new GeneratorDataSource<T>(*this);
}

template<typename T>
inline T GeneratorDataSource<T>::getNext()
{
	return generator->operator()();
}

template<typename T>
inline DataSourceArray<T> GeneratorDataSource<T>::getNext(size_t count)
{
	if (count == 0)
		return DataSourceArray<T>{nullptr, 0};

	if (!generator->hasNext(count))
		throw InsufficientDataSourceException();

	T* elements = new T[count];

	try
	{
		for (size_t i = 0; i < count; i++)
		{
			elements[i] = getNext();
		}
	}
	catch (...)
	{
		delete[] elements;
		throw;
	}

	return DataSourceArray<T>{elements, count};
}

template<typename T>
inline bool GeneratorDataSource<T>::hasNext()
{
	return generator->hasNext();
}

template<typename T>
inline bool GeneratorDataSource<T>::reset()
{
	return generator->reset();
}
