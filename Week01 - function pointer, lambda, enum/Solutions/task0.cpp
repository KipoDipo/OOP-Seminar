#include <iostream>

void filter(int*& arr, int& size, bool (*predicate)(int))
{
    int newSize = 0;
    for (int i = 0; i < size; i++)
    {
        if (predicate(arr[i]))
            newSize++;
    }   

    int* newArr = new int[newSize];

    int counter = 0;
    for (int i = 0; i < size; i++)
    {
        if (predicate(arr[i]))
        {
            newArr[counter] = arr[i];
            counter++;
        }
    }

    delete[] arr;
    arr = newArr;
    size = newSize;
}

bool isEven(int number)
{
    return number % 2 == 0;
}

int main()
{
    int size = 10;
    int *arr = new int[size] {1,2,3,4,5,6,7,8,9,10};

    filter(arr, size, isEven);
    filter(arr, size, [](int e){return e <= 5;});

    for (int i = 0; i < size; i++)
        std::cout << arr[i] << " ";

    delete[] arr;
}