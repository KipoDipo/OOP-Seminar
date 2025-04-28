#include "SavingsAccount.hpp"

SavingsAccount::SavingsAccount()
	: BankAccount(), interestRate(1)
{
}

SavingsAccount::SavingsAccount(double balance, double interestRate)
	: BankAccount(balance), interestRate(interestRate)
{
}

void SavingsAccount::applyInterest()
{
	treasury -= balance;

	balance *= interestRate;

	treasury += balance;
}
