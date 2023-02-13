// CSLabs.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <string>
#include <fstream>

int main()
{
	//added new fatures!
		const int characterArraySize = 80;
	char firstLine[characterArraySize];
	char secondLine[characterArraySize];

	std::ifstream inFromTextFile;
	std::ofstream outToTextFile;

	inFromTextFile.open("inputfile.txt");
	if (!inFromTextFile)
	{
		printf("Can't open inputfile.txt successfully. I will create it for you!\n");

		outToTextFile.open("inputfile.txt");

		outToTextFile << "firstLine: paul" << std::endl;
		outToTextFile << "secondLine: hutchinson" << std::endl;

		outToTextFile.close();
		inFromTextFile.open("inputfile.txt");
	}

	outToTextFile.open("outputfile.txt");
	if (!outToTextFile)
	{
		printf("Can't open outputfile.txt successfully.\n");

		return 1;
	}

	printf("input line 1: ");
	std::cin.getline(firstLine, sizeof firstLine);
	outToTextFile << "firstLine: "<< firstLine << std::endl;
	inFromTextFile.getline(firstLine, sizeof firstLine);

	printf("\ninput line 2: ");
	std::cin.getline(secondLine, sizeof secondLine);
	outToTextFile << "secondLine: " << secondLine << std::endl;
	inFromTextFile.getline(secondLine, sizeof secondLine);

	printf("\nread from inputfile.txt: \n%s \n%s\n\n", firstLine, secondLine);

	inFromTextFile.close();
	outToTextFile.close();
}