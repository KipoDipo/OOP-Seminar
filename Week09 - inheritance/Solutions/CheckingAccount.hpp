#pragma once
#include "BankAccount.hpp"

class CheckingAccount : public BankAccount
{
public:
	CheckingAccount();
	CheckingAccount(double balance, double overdraftLimit);

	double withdraw(double money);

private:
	double overdraftLimit;
};
