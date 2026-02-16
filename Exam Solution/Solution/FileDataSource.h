#pragma once

#include <fstream>
#include "DataSource.h"

class FileDataSource : DataSource<char>
{
public:
	FileDataSource(const char* filePath);

	FileDataSource(const FileDataSource& other);
	FileDataSource(FileDataSource&& other) noexcept;

	~FileDataSource() noexcept override;
	
	FileDataSource& operator=(const FileDataSource& other);
	FileDataSource& operator=(FileDataSource&& other) noexcept;

	FileDataSource* clone() const override;

	char getNext() override;
	DataSourceArray<char> getNext(size_t count) override;

	bool reset() override;
	bool hasNext() override;

private:
	bool hasEnough(size_t count);

private:
	char* filePath;
	std::ifstream inputStream;
	std::streampos streamPosition;
};