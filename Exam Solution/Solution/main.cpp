#include <cstdlib>
#include <fstream>
#include <iostream>

#include "DefaultDataSource.h"
#include "AlternateDataSource.h"
#include "FibonacciGenerator.h"
#include "FunctionGenerator.h"

void firstTask()
{
	DefaultDataSource<uint64_t> defaultDataSource;
	
	FunctionGenerator<uint64_t, uint64_t(*)()> randomGenerator([]() {return (uint64_t)rand(); });
	GeneratorDataSource<uint64_t> randomDataSource(&randomGenerator);

	FibonacciGenerator fibonacciGenerator(25);
	GeneratorDataSource<uint64_t> fibonacciDataSource(&fibonacciGenerator);


	DataSource<uint64_t>* integerDataSources[3]{ &defaultDataSource, &randomDataSource, &fibonacciDataSource };
	AlternateDataSource<uint64_t> integerDataSource(integerDataSources, 3);

	char filePath[256];
	std::cout << "Enter file name[max 255 symbols]: ";
	std::cin.getline(filePath, 256);

	std::ofstream binaryOutStream(filePath, std::ios::binary | std::ios::trunc);
	DataSourceArray<uint64_t> generatedIntergers = integerDataSource.getNext(1000);
	binaryOutStream.write(reinterpret_cast<const char*>(generatedIntergers.array), sizeof(unsigned) * generatedIntergers.size);
	delete[] generatedIntergers.array;
}

template<size_t LENGTH>
char* generateString()
{
	const size_t lettersCount = 'z' - 'a';

	char* generatedString = new char[LENGTH + 1];
	for (size_t i = 0; i < LENGTH; i++)
	{
		generatedString[i] = (rand() % lettersCount) + 'a';
	}
	generatedString[LENGTH] = '\0';

	return generatedString;
}

void secondTask()
{
	FunctionGenerator<char*, char* (*)()> stringGenerator(generateString<10>);
	GeneratorDataSource<char*> stringDataSource(&stringGenerator);

	char filePath[256];
	std::cout << "Enter file name[max 255 symbols]: ";
	std::cin.getline(filePath, 256);

	std::ofstream outBinStream(filePath, std::ios::binary | std::ios::trunc);

	DataSourceArray<char*> generatedStrings = stringDataSource.getNext(50);
	for (size_t i = 0; i < generatedStrings.size; i++)
	{
		char* generatedString = generatedStrings.array[i];
		outBinStream.write(generatedString, strlen(generatedString) + 1); // Add \0 as well :)
		delete[] generatedString;
	}

	delete[] generatedStrings.array;
}

int main()
{
	// Used to seed rand()
	srand(time(NULL));

	firstTask();
	secondTask();
}