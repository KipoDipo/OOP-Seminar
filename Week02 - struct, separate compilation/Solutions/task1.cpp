#include <iostream>

const char* GENDER_STRINGS[3] {"Male", "Female", "Prefer not to say"};
enum class Gender
{
	Male,
	Female,
	PreferNotToSay
};

struct Person
{
	char name[25 + 1];
	int age;
	Gender gender;
};

void printPerson(Person person)
{
	std::cout << "Name: " << person.name << "\tAge: " << person.age << "\tGender: " << GENDER_STRINGS[(int)person.gender] << "\n";
}

void printMalesAndFemales(Person people[], unsigned size)
{
	for (unsigned i = 0; i < size; i++)
	{
		if (people[i].gender == Gender::Male)
		{
			printPerson(people[i]);
		}
	}

	for (unsigned i = 0; i < size; i++)
	{
		if (people[i].gender == Gender::Female)
		{
			printPerson(people[i]);
		}
	}
}

int main()
{
	Person people[6]
	{
		{"Kiril", 22, Gender::Male},
		{"Damyan", 25, Gender::Male},
		{"Vili", 20, Gender::Female},
		{"Alex", 15, Gender::Male},
		{"Kalin", 62, Gender::PreferNotToSay},
		{"David", 99, Gender::Female},
	};

	printMalesAndFemales(people, 6);
}
