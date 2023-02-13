// CSLabs.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <string>
#include <fstream>

int main()
{
	const int characterArraySize = 80;
	char firstName[characterArraySize];
	char lastName[characterArraySize];

	std::ifstream inFromTextFile;
	std::ofstream outToTextFile;

	inFromTextFile.open("inputfile.txt");
	outToTextFile.open("outputfile.txt");



	printf("First name: ");
	std::cin.getline(firstName, sizeof firstName);
	outToTextFile << firstName; //how to add newline to character array? or other way to do it?
	inFromTextFile >> firstName;

	printf("\nLast name: ");
	std::cin.getline(lastName, sizeof lastName);
	outToTextFile << lastName;
	inFromTextFile >> lastName;

	printf("\nYour name is: %s %s\n\n", firstName, lastName);

	inFromTextFile.close();
	outToTextFile.close();

}