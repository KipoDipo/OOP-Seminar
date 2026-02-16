#pragma once
#include "BankAccount.hpp"

class SavingsAccount : public BankAccount
{
public:
	SavingsAccount();
	SavingsAccount(double balance, double interestRate);

	void applyInterest();

private:
	double interestRate;
};
