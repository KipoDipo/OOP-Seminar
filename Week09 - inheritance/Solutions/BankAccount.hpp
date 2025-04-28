#pragma once
#include <iostream>

class BankAccount
{
public:
	BankAccount();
	BankAccount(double balance);

	BankAccount(const BankAccount& other) = delete;
	BankAccount& operator=(const BankAccount& other) = delete;

	~BankAccount();

	void deposit(double money);
	double withdraw(double money);

	double getBalance() const;
	int getNumber() const;

	static double getTreasury();

protected:
	double balance;

	static double treasury;

private:
	int number;

	static int nextNumber;
};

std::ostream& operator<<(std::ostream& o, const BankAccount& account);

BankAccount operator+(BankAccount& left, BankAccount& right);

bool operator==(const BankAccount& left, const BankAccount& right);