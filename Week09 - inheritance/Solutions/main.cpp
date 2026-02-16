#include <iostream>
#include "SavingsAccount.hpp"
#include "CheckingAccount.hpp"

int main()
{
	BankAccount b1(150);
	BankAccount b2(2000);

	std::cout << b1 << '\n';
	std::cout << b2 << '\n';

	BankAccount b3 = b1 + b2;

	std::cout << b1 << '\n';
	std::cout << b2 << '\n';
	std::cout << b3 << '\n' << '\n';

	SavingsAccount s1(700, 1.2);

	std::cout << s1 << '\n';
	std::cout << "Applying Interest...\n";

	s1.applyInterest();

	std::cout << s1 << '\n' << '\n';

	CheckingAccount c1(1000, 2000);

	std::cout << c1 << '\n';

	double cash1 = c1.withdraw(900);
	std::cout << "Wanted: 900\tWithdrawed: $" << cash1 << '\n';
	std::cout << c1 << '\n';

	double cash2 = c1.withdraw(900);
	std::cout << "Wanted: 900\tWithdrawed: $" << cash2 << '\n';
	std::cout << c1 << '\n';

	double cash3 = c1.withdraw(900);
	std::cout << "Wanted: 900\tWithdrawed: $" << cash3 << '\n';
	std::cout << c1 << '\n';

	double cash4 = c1.withdraw(900);
	std::cout << "Wanted: 900\tWithdrawed: $" << cash4 << '\n';
	std::cout << c1 << '\n';
}