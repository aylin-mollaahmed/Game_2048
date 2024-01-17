#include <iostream>
#include <fstream>
#include "constants.h"
#include "validation.h"
using namespace std;

void printEnteringMenu() {
	cout << "Hello, are you ready to play?" << endl << endl;
	cout << "Please choose from the menu." << endl << endl;
	std::cout << "1. Start game" << endl;
	std::cout << "2. Leaderboard" << endl;
	std::cout << "3. Quit" << endl << endl;
}
//input functions
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
void strCpy(const char* source, char* dest)
{
	if (!source || !dest)
		return;
	while (*source)
	{
		*dest = *source;
		dest++;
		source++;
	}
	*dest = '\0';
}
int strCmp(const char* first, const char* second)
{
 if (!first || !second)
	return 0; 

 while ((*first) && (*second) && ((*first) == (*second))) 
{
	first++;
	second++;
}

 return (*first - *second);
}
size_t strLen(const char* str)
{
	if(!str)
		return 0;

	unsigned result = 0;
	while (*str) 
	{
		result++;
		str++;
	}
	return result;
}
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
			if (strCmp(names[i], name) == 0)
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
		strCpy(names[count], name);
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
		std::cout << "---------" << std::endl << std::endl;
	}
	else
	{
		std::cout << "No leaderboard for the current dimension selected." <<
			std::endl << std::endl;
	}

	delete[] fileName;
}
size_t** createMatrix(size_t n)
{
	size_t** matrix = new size_t * [n] {};

	for (size_t i = 0; i < n; i++)
		matrix[i] = new size_t[n]{ 0 };

	return matrix;
}
bool hasSameNeighbours(size_t** board, size_t dimension) {
	for (size_t i = 0; i < dimension; i++)
	{
		for (size_t j = 0; j < dimension; j++)
		{
			if ((j + 1 < dimension && board[i][j] == board[i][j + 1]) ||
				(i + 1 < dimension && board[i][j] == board[i + 1][j]))
			{
				return true;
			}
		}
	}

	return false;
}
bool hasEmptySpace(size_t** board, size_t dimension)
{
	for (size_t row = 0; row < dimension; row++)
	{
		for (size_t col = 0; col < dimension; col++)
		{
			if (board[row][col] == 0)
			{
				return true;
			}
		}
	}

	return false;
}
bool isMovePossible(size_t** board, size_t dimension)
{
	return hasEmptySpace(board, dimension) || hasSameNeighbours(board, dimension);
}
void generateRandom(size_t** board, size_t dimension, size_t& currentScore)
{
	srand(time(0));
	size_t row, col;

	row = rand() % dimension;
	col = rand() % dimension;

	while (board[row][col] != 0) {
		row = rand() % dimension;
		col = rand() % dimension;
	}


	if (currentScore < SCORE_EARLY_STAGE)
	{
		size_t optionsEarlyStage[] = { 2,2,2,2,2,4,4,4 };
		board[row][col] = optionsEarlyStage[rand() % 8];
		currentScore += board[row][col];
	}
	else if (currentScore < SCORE_MIDDLE_STAGE)
	{
		size_t optionsMiddleStage[] = { 2,2,2,4,4,4,8,8 };
		board[row][col] = optionsMiddleStage[rand() % 8];
		currentScore += board[row][col];
	}
	else
	{
		size_t optionsLatestStage[] = { 2,2,4,4,4,4,8,8,8 };
		board[row][col] = optionsLatestStage[rand() % 8];
		currentScore += board[row][col];
	}

}
void printBoard(size_t** board, size_t rows)
{
	for (size_t i = 0; i < rows; i++)
	{
		for (size_t j = 0; j < rows; j++)
		{
			cout << board[i][j] << " ";
		}
		cout << endl;
	}
}
void moveUp(size_t** matrix, size_t n)
{
	for (size_t col = 0; col < n; col++)
	{
		size_t toMove = 0;
		for (size_t row = 0; row < n; row++)
		{
			if (matrix[row][col] == 0)
			{
				continue;
			}
			matrix[toMove][col] = matrix[row][col];
			if (row != toMove)
			{
				matrix[row][col] = 0;
			}
			toMove++;

		}
	}
}
void moveDown(size_t** matrix, size_t n)
{
	for (size_t col = 0; col < n; col++)
	{
		size_t toMove = n - 1;
		for (int row = n - 1; row >= 0; row--)
		{
			if (matrix[row][col] == 0)
			{
				continue;
			}

			matrix[toMove][col] = matrix[row][col];
			if (row != toMove)
			{
				matrix[row][col] = 0;
			}
			toMove--;

		}
	}
}
void moveRight(size_t** matrix, size_t n)
{
	for (size_t row = 0; row < n; row++)
	{
		size_t toMove = n - 1;
		for (int col = n - 1; col >= 0; col--)
		{
			if (matrix[row][col] == 0)
			{
				continue;
			}

			matrix[row][toMove] = matrix[row][col];
			if (col != toMove)
			{
				matrix[row][col] = 0;
			}
			toMove--;

		}
	}
}
void moveLeft(size_t** matrix, size_t n)
{
	for (size_t row = 0; row < n; row++)
	{
		size_t toMove = 0;
		for (size_t col = 0; col < n; col++)
		{
			if (matrix[row][col] == 0)
			{
				continue;
			}

			matrix[row][toMove] = matrix[row][col];
			if (col != toMove)
			{
				matrix[row][col] = 0;
			}
			toMove++;

		}
	}
}
void move(size_t** board, size_t dimension, char direction) {
	switch (direction)
	{
	case MOVE_UP:
		moveUp(board, dimension);
		for (size_t row = 0; row < dimension - 1; row++)
		{
			for (size_t col = 0; col < dimension; col++)
			{
				if (board[row][col] == board[row + 1][col])
				{
					board[row][col] += board[row + 1][col];
				}
			}
		}
		moveUp(board, dimension);
		break;
	case MOVE_DOWN:
		moveDown(board, dimension);
		for (int row = dimension - 1; row > 0; row--)
		{
			for (size_t col = 0; col < dimension; col++)
			{
				if (board[row][col] == board[row - 1][col])
				{
					board[row][col] += board[row - 1][col];
					board[row - 1][col] = 0;
				}
			}
		}
		moveDown(board, dimension);
		break;
	case MOVE_LEFT:
		moveLeft(board, dimension);
		for (size_t col = 0; col < dimension - 1; col++)
		{
			for (size_t row = 0; row < dimension; row++)
			{
				if (board[row][col] == board[row][col + 1])
				{
					board[row][col] += board[row][col + 1];
					board[row][col + 1] = 0;
				}
			}
		}
		moveLeft(board, dimension);
		break;
	case MOVE_RIGHT:
		moveRight(board, dimension);
		for (int col = dimension - 1; col > 0; col--)
		{
			for (size_t row = 0; row < dimension; row++)
			{
				if (board[row][col] == board[row][col - 1])
				{
					board[row][col] += board[row][col - 1];
					board[row][col - 1] = 0;
				}
			}
		}
		moveRight(board, dimension);
		break;

	}
}
void freeMatrix(size_t** m, size_t n)
{
	for (size_t i = 0; i < n; i++)
	{
		delete[] m[i];
	}

	delete[] m;
}
void play() {
	cout << "Enter your nickname: ";
	char* nickname = inputStr();
	cout << "Enter dimension you want to play in: ";
	unsigned dimension = inputDimensionSize();
	cout << endl;
	size_t** board = createMatrix(dimension);
	size_t score = 0;
	while (isMovePossible(board, dimension)) {
		if (hasEmptySpace(board, dimension))
		{
			generateRandom(board, dimension, score);
		}
		cout << "Current score: " << score << endl << endl;
		printBoard(board, dimension);
		cout << endl << "Enter direction: ";
		char direction = inputDirectionChoice();
		move(board, dimension, direction);

	}
	cout << "Game finished! Your final score is: " << score << endl << endl;
	updateLeaderboard(dimension, nickname, score);
	freeMatrix(board, dimension);
	delete[]nickname;
}
void startGame() {
	while (true) {
		printEnteringMenu();

		unsigned playerChoiceNumber = inputPlayerChoice();
		switch (playerChoiceNumber)
		{

		case 1:

			play();
			break;

		case 2:

			leaderboardMenu();
			break;

		case 3:

			cout << "Come to play again!:)" << endl;
			return;


		}
	}
}
int main() {

	startGame();
}
	
	
	
	
	
	
	