template<typename T>
inline AlternateDataSource<T>::AlternateDataSource(const DataSource<T>* const* dataSources, size_t size)
	: dataSources(nullptr), size(size), position(0)
{
	if (size != 0)
		this->dataSources = copyDataSources(dataSources, size);
}

template<typename T>
inline AlternateDataSource<T>::AlternateDataSource(const AlternateDataSource& other)
	: AlternateDataSource(other.dataSources, other.size)
{
}

template<typename T>
inline AlternateDataSource<T>::AlternateDataSource(AlternateDataSource&& other) noexcept
	: dataSources(other.dataSources), size(other.size), position(other.position)
{
	other.nullify();
}

template<typename T>
inline AlternateDataSource<T>::~AlternateDataSource() noexcept
{
	for (size_t i = 0; i < size; i++)
	{
		delete dataSources[i];
	}

	delete[] dataSources;
}

template<typename T>
inline AlternateDataSource<T>& AlternateDataSource<T>::operator=(const AlternateDataSource& other)
{
	if (this == &other)
		return *this;

	DataSource<T>** dataSourcesCopy = copyDataSources(other.dataSources, other.size);
	delete[] dataSources;

	dataSources = dataSourcesCopy;
	size = other.size;
	position = other.position;

	return *this;
}

template<typename T>
inline AlternateDataSource<T>& AlternateDataSource<T>::operator=(AlternateDataSource&& other) noexcept
{
	if (this == &other)
		return *this;

	dataSources = other.dataSources;
	size = other.size;
	position = other.position;

	other.nullify();
	return *this;
}

template<typename T>
inline AlternateDataSource<T>* AlternateDataSource<T>::clone() const
{
	return new AlternateDataSource(*this);
}

template<typename T>
inline T AlternateDataSource<T>::getNext()
{
	if (!hasNext())
		throw EmptyDataSourceException();

	size_t dataSourceIndex = position % size;
	while (!dataSources[dataSourceIndex]->hasNext())
	{
		position += 1;
		dataSourceIndex = position % size;
	}

	position += 1;
	return dataSources[dataSourceIndex]->getNext();
}

template<typename T>
inline DataSourceArray<T> AlternateDataSource<T>::getNext(size_t count)
{
	if (count == 0)
		return DataSourceArray<T>{ nullptr, 0 };

	if (!hasEnough(count))
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

	return DataSourceArray<T>{ elements, count };
}

template<typename T>
inline bool AlternateDataSource<T>::reset()
{
	for (size_t i = 0; i < size; i++)
	{
		dataSources[i]->reset();
	}

	return true;
}

template<typename T>
inline bool AlternateDataSource<T>::hasNext()
{
	if (size == 0)
		return false;

	for (size_t i = 0; i < size; i++)
	{
		if (dataSources[i]->hasNext())
			return true;
	}

	return false;
}

template<typename T>
inline bool AlternateDataSource<T>::hasEnough(size_t count) const
{
	// Easy to grasp method but not very optimized!
	AlternateDataSource<T> copy(*this);
	while (count > 0)
	{
		if (!copy.hasNext())
			return false;

		copy.getNext();
		count -= 1;
	}

	return true;
}

template<typename T>
inline void AlternateDataSource<T>::nullify()
{
	dataSources = nullptr;
	size = 0;
	position = 0;
}

template<typename T>
inline DataSource<T>** AlternateDataSource<T>::copyDataSources(const DataSource<T>* const* dataSources, size_t size)
{
	if (dataSources == nullptr)
		return nullptr;

	DataSource<T>** copiedDataSources = new DataSource<T>*[size] {}; // set all to nullptr

	try
	{
		for (size_t i = 0; i < size; i++)
		{
			copiedDataSources[i] = dataSources[i]->clone();
		}
	}
	catch (...)
	{
		for (size_t i = 0; i < size; i++)
		{
			delete copiedDataSources[i];
		}
		delete[] copiedDataSources;

		throw;
	}

	return copiedDataSources;
}
