// CSLabs.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <fstream>

int main()
{
	const int characterArraySize = 80;
	char firstName[characterArraySize];
	char lastName[characterArraySize];

	printf("First name: ");
	std::cin.getline(firstName, sizeof firstName);

	printf("\nLast name: ");
	std::cin.getline(lastName, sizeof lastName);

	printf("\nYour name is: %s %s\n\n", firstName, lastName);
}