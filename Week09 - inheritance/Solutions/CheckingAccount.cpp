#include "CheckingAccount.hpp"

CheckingAccount::CheckingAccount()
	: BankAccount(), overdraftLimit(0)
{
}

CheckingAccount::CheckingAccount(double balance, double overdraftLimit)
	: BankAccount(balance), overdraftLimit(overdraftLimit)
{
}

double CheckingAccount::withdraw(double money)
{
	if (money < 0)
		return 0;

	if (balance + overdraftLimit < money)
	{
		double leftover = balance + overdraftLimit;
		balance = -overdraftLimit;

		treasury -= leftover;
		return leftover;
	}

	balance -= money;
	treasury -= money;

	return money;
}
