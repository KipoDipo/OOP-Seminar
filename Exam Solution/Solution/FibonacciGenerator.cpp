#include "FibonacciGenerator.h"

FibonacciGenerator::FibonacciGenerator(size_t maxTerms)
	: currentIndex(0), maxTerms(maxTerms),
	  first(0), second(1)
{
}

uint64_t FibonacciGenerator::operator()()
{
	if (!hasNext())
		throw EmptyGeneratorException();

	uint64_t nextFib = first;

	first = second;
	second = first + nextFib;

	currentIndex++;
	return nextFib;
}

bool FibonacciGenerator::reset()
{
	currentIndex = 0;

	first = 0;
	second = 1;
	
	return true;
}

bool FibonacciGenerator::hasNext()
{
	return currentIndex < maxTerms;
}

bool FibonacciGenerator::hasNext(size_t count)
{
	size_t distance = maxTerms - currentIndex;
	return distance >= count;
}
