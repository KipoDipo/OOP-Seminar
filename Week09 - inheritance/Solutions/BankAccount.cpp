#include "BankAccount.hpp"

int BankAccount::nextNumber = 1000;

double BankAccount::treasury = 0;

BankAccount::BankAccount()
	: BankAccount(0)
{
}

BankAccount::BankAccount(double balance)
	: balance(balance), number(nextNumber++)
{
	treasury += balance;
}

BankAccount::~BankAccount()
{
	treasury -= balance;
}

void BankAccount::deposit(double money)
{
	balance += money;
	treasury += money;
}

double BankAccount::withdraw(double money)
{
	if (money < 0)
		return 0;

	if (balance < money)
	{
		double leftover = balance;
		balance = 0;

		treasury -= leftover;
		return leftover;
	}

	balance -= money;
	treasury -= money;

	return money;
}

double BankAccount::getBalance() const
{
	return balance;
}

int BankAccount::getNumber() const
{
	return number;
}

double BankAccount::getTreasury()
{
	return treasury;
}

std::ostream& operator<<(std::ostream& o, const BankAccount& account)
{
	o << "Bank Account #" << account.getNumber() << " has a balance of $"
		<< account.getBalance() << " (Treasury: $" << BankAccount::getTreasury() << ")";
	return o;
}

BankAccount operator+(BankAccount& left, BankAccount& right)
{
	double leftAmount = left.getBalance();
	double rightAmount = right.getBalance();

	left.withdraw(leftAmount);
	right.withdraw(rightAmount);

	return BankAccount(leftAmount + rightAmount);
}

bool operator==(const BankAccount& left, const BankAccount& right)
{
	return left.getNumber() == right.getNumber();
}