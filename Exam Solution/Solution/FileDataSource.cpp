#include <cstring>
#include <utility>

#include "FileDataSource.h"
#include "DataSourceExcpetions.h"
#include "Utils.h"

#pragma warning(disable:4996)

FileDataSource::FileDataSource(const char* filePath)
    : filePath(copyString(filePath)), 
      inputStream(filePath),
      streamPosition(inputStream.tellg())
{
    if (!inputStream.is_open())
    {
        delete[] filePath;
        throw std::invalid_argument("File could not be opened for reading!");
    }
}

FileDataSource::FileDataSource(const FileDataSource& other)
    : FileDataSource(other.filePath)
{
    streamPosition = other.streamPosition;
    inputStream.seekg(streamPosition);
}

FileDataSource::FileDataSource(FileDataSource&& other) noexcept
    : filePath(other.filePath), 
      inputStream(std::move(other.inputStream)),
      streamPosition(other.streamPosition)
{
    other.filePath = nullptr;
}

FileDataSource::~FileDataSource() noexcept
{
    delete[] filePath;
}

FileDataSource& FileDataSource::operator=(const FileDataSource& other)
{
    if (this == &other)
        return *this;

    std::ifstream newInputStream(other.filePath);
    if (!newInputStream.is_open())
        throw std::invalid_argument("File could not be opened for reading!");

    char* newFilePath = copyString(other.filePath);
    delete[] filePath;

    filePath = newFilePath;
    inputStream = std::move(newInputStream);
    streamPosition = other.streamPosition;
    
    return *this;
}

FileDataSource& FileDataSource::operator=(FileDataSource&& other) noexcept
{
    if (this == &other)
        return *this;

    filePath = other.filePath;
    inputStream = std::move(other.inputStream);
    streamPosition = other.streamPosition;

    other.filePath = nullptr;

    return *this;
}

FileDataSource* FileDataSource::clone() const
{
    return new FileDataSource(*this);
}

char FileDataSource::getNext()
{
    if (!hasNext())
        throw EmptyDataSourceException();

    char nextElement = inputStream.get();
    streamPosition = inputStream.tellg();
    
    return nextElement;
}

DataSourceArray<char> FileDataSource::getNext(size_t count)
{
    if (count == 0)
        return DataSourceArray<char>{ nullptr, 0 };

    if (!hasEnough(count))
        throw InsufficientDataSourceException();

    char* elements = new char[count];
    for (size_t i = 0; i < count; i++)
        elements[i] = inputStream.get();

    if (!inputStream.good())
    {
        delete[] elements;
        throw std::invalid_argument("A problem with the file stream has occurred")
    }

    streamPosition = inputStream.tellg();

    return DataSourceArray<char>{ elements, count };
}

bool FileDataSource::reset()
{
    inputStream.clear();
    inputStream.seekg(0, std::ios::beg);
    streamPosition = inputStream.tellg();

    return hasNext();
}

bool FileDataSource::hasNext()
{
    return inputStream.good() && inputStream.peek() != EOF;
}

bool FileDataSource::hasEnough(size_t count)
{
    const std::streampos currPos = inputStream.tellg();
    inputStream.seekg(0, std::ios::end);
    const std::streampos endPos = inputStream.tellg();
    inputStream.seekg(currPos, std::ios::beg);

    const std::streampos distance = endPos - currPos;
    return distance >= count;
}
