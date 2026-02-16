#include <iostream>

const char* Suits[] = { "Hearts", "Spades", "Diamonds", "Clubs" };
enum class Suit
{
    Hearts,
    Spades,
    Diamonds,
    Clubs
};

const char* Ranks[] = { "Ace", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King" };
enum class Rank
{
    Ace,
    Two,
    Three,
    Four,
    Five,
    Six,
    Seven,
    Eight,
    Nine,
    Ten,
    Jack,
    Queen,
    King
};

int main()
{
    Rank rank;
    Suit suit;

    int input;

    std::cout << "Enter rank: ";
    std::cin >> input;
    rank = (Rank)(input - 1);

    std::cout << "Enter suit: ";
    std::cin >> input;
    suit = (Suit)input;

    std::cout << Ranks[(int)rank] << " of " << Suits[(int)suit];
}