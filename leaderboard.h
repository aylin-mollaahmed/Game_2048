/**
*
* Solution to course project # <номер на вариант>
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2023/2024
*
* @author Aylin Mollaahmed
* @idnumber 3MI0600281
* @compiler VC
*
* leadeboard functions
*
*/
#pragma once
#include "constants.h";
#include <fstream>
#include "validation.h"
#include "input.h"
#include "stringFunctions.h"
void swapInteger(size_t& first, size_t& second) {
	size_t temp = first;
	first = second;
	second = temp;
}
void swap(char first[], char second[]) {
	char* temp = new char[strLen(first) + 1];
	strCpy(temp, first);
	strCpy(first, second);
	strCpy(second, temp);
	delete[] temp;
}
void selectionSort(size_t count, size_t scores[], char names[MAX_PLAYERS_LEADERBOARD + 1][BUFFER_SIZE])
{
	for (size_t i = 0; i < count - 1; i++)
	{
		size_t maxInd = i;
		for (size_t j = i + 1; j < count; j++)
		{
			if (scores[j] > scores[maxInd])
			{
				maxInd = j;
			}
		}

		if (maxInd != i)
		{
			swapInteger(scores[i], scores[maxInd]);
			swap(names[i], names[maxInd]);
		}
	}
}
int parseNum(const char* input) {
	size_t iter = 0;
	size_t result = 0;
	while (input[iter] != '\0')
	{
		if (input[iter] < '0' || input[iter]>'9')
		{
			return -1;
		}

		result = result * 10 + input[iter] - DIGIT_TO_CHAR;
		iter++;
	}

	return result;
}

char* getFileName(size_t dimension)
{
	char* fileName = new char[LENGTH_PATH];
	switch (dimension)
	{
	case 4:
		fileName[0] = '4';
		break;
	case 5:
		fileName[0] = '5';
		break;
	case 6:
		fileName[0] = '6';
		break;
	case 7:
		fileName[0] = '7';
		break;
	case 8:
		fileName[0] = '8';
		break;
	case 9:
		fileName[0] = '9';
		break;
	case 10:
		fileName[0] = '10';
		break;
	}
	fileName[1] = '.';
	fileName[2] = 't';
	fileName[3] = 'x';
	fileName[4] = 't';
	fileName[5] = '\0';

	return fileName;

}
void updateLeaderboard(size_t dimension, char* name, size_t score)
{
	size_t count = 0;
	char* fileName = getFileName(dimension);
	ifstream leaderboardFile(fileName);

	char names[MAX_PLAYERS_LEADERBOARD + 1][BUFFER_SIZE];
	size_t scores[MAX_PLAYERS_LEADERBOARD + 1];
	char buffer[BUFFER_SIZE];


	bool shouldAdd = true;

	if (leaderboardFile.is_open())
	{
		leaderboardFile.getline(buffer, BUFFER_SIZE);
		count = parseNum(buffer);
		for (size_t i = 0; i < count; i++)
		{
			leaderboardFile.getline(buffer, BUFFER_SIZE);
			scores[i] = parseNum(buffer);
			leaderboardFile.getline(names[i], BUFFER_SIZE);
			if (strCmp(name, names[i]) == 0)
			{
				shouldAdd = false;
				if (score > scores[i])
				{
					scores[i] = score;
				}
			}
		}

		leaderboardFile.close();
	}

	if (shouldAdd)
	{
		strCpy(name, names[count]);
		scores[count] = score;
		count++;
	}
	selectionSort(count, scores, names);

	if (count > MAX_PLAYERS)
	{
		count = MAX_PLAYERS;
	}

	ofstream leaderboardFileOut(fileName);
	if (leaderboardFileOut.is_open())
	{
		leaderboardFileOut << count << std::endl;
		for (size_t i = 0; i < count; i++)
		{
			leaderboardFileOut << scores[i] << endl;
			leaderboardFileOut << names[i] << endl;
		}

		leaderboardFileOut.close();
	}

	delete[] fileName;
}
void leaderboardMenu()
{
	cout << "Enter dimension you want to see leaderboard in: ";
	int dimension = inputDimensionSize();


	size_t count = 0;
	char* fileName = getFileName(dimension);
	ifstream leaderboardFile(fileName);

	char name[BUFFER_SIZE];
	size_t score;
	char buffer[BUFFER_SIZE];

	if (leaderboardFile.is_open())
	{
		leaderboardFile.getline(buffer, BUFFER_SIZE);
		count = parseNum(buffer);
		for (size_t i = 0; i < count; i++)
		{
			leaderboardFile.getline(buffer, BUFFER_SIZE);
			score = parseNum(buffer);
			leaderboardFile.getline(name, BUFFER_SIZE);
			cout << (i + 1) << ". " << score << " " << name << endl;
		}

		leaderboardFile.close();
		cout << "---------" << std::endl << std::endl;
	}
	else
	{
		cout << "No leaderboard for the current dimension selected." << endl;
			cout << endl << endl;
	}

	delete[] fileName;
}
