#include <iostream>
#pragma warning (disable: 4996)

struct Item
{
	double price;
	unsigned quantity;
};

double sumOfItems(Item* items, unsigned size)
{
	double result = 0;

	for (unsigned i = 0; i < size; i++)
	{
		result += items[i].price * items[i].quantity;
	}

	return result;
}

unsigned quantityOfMostExpensive(Item items[], unsigned size)
{
	int index = 0;

	for (unsigned i = 1; i < size; i++)
	{
		if (items[i].price > items[index].price)
		{
			index = i;
		}
	}

	return items[index].quantity;
}

int main()
{
	Item items[5];

	//items[0].price = 5.50;
	//items[0].quantity = 5.50;
	
	items[0] = { 5.50, 10 };
	items[1] = { 6, 60 };
	items[2] = { 4, 1 };
	items[3] = { 2.10, 2 };
	items[4] = { 400, 13 };

	std::cout << sumOfItems(items, 5) << std::endl;
	std::cout << quantityOfMostExpensive(items, 5) << std::endl;
}