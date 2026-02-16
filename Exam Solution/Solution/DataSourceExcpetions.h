#pragma once

#include <stdexcept>

class DataSourceException : public std::exception
{
protected:
	DataSourceException(const char* what)
		: exception(what)
	{ }
};

class EmptyDataSourceException : public DataSourceException
{
public:
	EmptyDataSourceException()
		: DataSourceException("No more items can be fetched from the data source")
	{
	}
};

class InsufficientDataSourceException : public DataSourceException
{
public:
	InsufficientDataSourceException()
		: DataSourceException("Can not fetch that many elements from the data source")
	{
	}
};