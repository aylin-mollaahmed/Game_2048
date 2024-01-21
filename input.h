#pragma once
#include"validation.h";
using namespace std;
#include <iostream>

unsigned inputDimensionSize() {
	int dimension;
	cin >> dimension;
	while (!isDimensionSizeValid(dimension)) {
		cout << "Invalid number, try again!" << endl;
		cout << "Enter dimension you want to play in: ";
		cin >> dimension;
	}
	return dimension;
}
unsigned inputPlayerChoice() {
	cout << "-> ";
	int number;
	cin >> number;

	while (!isPlayerChoiceForNumberValid(number))
	{
		cout << "Invalid number, try again!" << endl;
		cout << "-> ";
		cin >> number;
	}
	cout << "OK! :)" << endl << endl;

	return number;
}
char* inputStr()
{
	char* input = new char[BUFFER_SIZE];
	cin >> input;
	return input;
}
char inputDirectionChoice() {
	char direction;
	cin >> direction;
	while (!isDirectionValid(direction)) {
		cout << "Invalid direction!" << endl;
		cout << endl << "Enter direction: ";
		cin >> direction;
	}
	return direction;
}