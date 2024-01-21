/**
*
* Solution to course project #4
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2023/2024
*
* @author Aylin Mollaahmed
* @idnumber 3MI0600281
* @compiler VC
*
* functions for moving on the playing board
*
*/



#pragma once
#include "constants.h"
#include <iostream>
size_t** createMatrix(size_t n)
{
	size_t** matrix = new size_t * [n] {};

	for (size_t i = 0; i < n; i++)
		matrix[i] = new size_t[n]{ 0 };

	return matrix;
}
bool isValidIndex(int index, int dimension) {
	return index < dimension;
}
bool hasSameNeighbours(size_t** board, size_t dimension) {
	for (size_t i = 0; i < dimension; i++)
	{
		for (size_t j = 0; j < dimension; j++)
		{
			if ((isValidIndex(j+1,dimension) && board[i][j] == board[i][j + 1]) ||
				(isValidIndex(i+ 1, dimension) < dimension && board[i][j] == board[i + 1][j]))
			{
				return true;
			}
		}
	}

	return false;
}
bool hasEmptyCell(size_t** board, size_t dimension)
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
	return hasEmptyCell (board, dimension) || hasSameNeighbours(board, dimension);
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
void moveUp(size_t** board, size_t dimension)
{
	for (size_t row = 0; row < dimension; row++)
	{

		for (size_t col = 0; col < dimension; col++)
		{
			int index = 1;
			if (board[row][col] != 0)
			{

				while (isIndexValid(row - index, dimension) && board[row - index][col] == 0)
				{
					board[row - index][col] = board[row - index + 1][col];
					board[row - index + 1][col] = 0;
					index++;
				}
			}
		}
	}
}

void moveDown(size_t** board, size_t dimension)
{
	for (int row = dimension - 1; row >= 0; row--)
	{

		for (size_t col = 0; col < dimension; col++)
		{
			int index = 1;
			if (board[row][col] != 0)
			{

				while (isIndexValid(row + index, dimension) && board[row + index][col] == 0)
				{
					board[row + index][col] = board[row + index - 1][col];
					board[row + index - 1][col] = 0;
					index++;
				}
			}
		}
	}
}

void moveRight(size_t** board, size_t dimension)
{
	for (size_t row = 0; row < dimension; row++)
	{

		for (int col = dimension-1; col >=0 ; col--)
		{
			int index = 1;
			if (board[row][col] != 0)
			{

				while (isIndexValid(col + index, dimension) && board[row ][col+ index] == 0)
				{
					board[row ][col+index] = board[row ][col + index - 1];
					board[row][col + index - 1] = 0;
					index++;
				}
			}
		}
	}
}

void moveLeft(size_t** board, size_t dimension)
{
	for (size_t row = 0; row < dimension; row++)
	{

		for (size_t col = 0; col < dimension; col++)
		{
			int index = 1;
			if (board[row][col] != 0)
			{

				while (isIndexValid(col - index, dimension) && board[row][col - index] == 0)
				{
					board[row][col - index] = board[row][col - index + 1];
					board[row][col - index + 1] = 0;
					index++;
				}
			}
		}
	}
}
void checkForSameNumbersAfterMovingUp(size_t** board, size_t dimension) {
	for (int row = 0; row < dimension ; row++)
	{

		for (size_t col = 0; col < dimension; col++)
		{
			if (isIndexValid(row + 1, dimension) && board[row + 1][col] == board[row][col])
			{
				board[row][col] *= 2;
				board[row+1][col] = 0;
			}

		}
	}
}
void checkForSameNumbersAfterMovingDown(size_t** board, size_t dimension) {
	for (int row = dimension-1; row >=0; row--)
	{

		for (size_t col = 0; col < dimension; col++)
		{
			if (isIndexValid(row - 1, dimension) && board[row - 1][col] == board[row][col])
			{
				board[row][col] *= 2;
				board[row -1][col] = 0;
			}

		}
	}
}
void checkForSameNumbersAfterMovingLeft(size_t** board, size_t dimension) {
	for (size_t row = 0; row < dimension; row++)
	{

		for (size_t col = 0; col < dimension; col++)
		{
			if (isIndexValid(col+ 1, dimension) && board[row ][col+1] == board[row][col])
			{
				board[row][col] *= 2;
				board[row][col+1] = 0;
			}

		}
	}
}
void checkForSameNumbersAfterMovingRight(size_t** board, size_t dimension) {
	for (size_t row = 0; row < dimension; row++)
	{

		for (int col = dimension - 1; col >=0 ; col--)
		{
			if (isIndexValid(col - 1, dimension) && board[row][col - 1] == board[row][col])
			{
				board[row][col] *= 2;
				board[row][col - 1] = 0;
			}

		}
	}
}
void move(size_t** board, size_t dimension, char direction) {
	switch (direction)
	{
	case MOVE_UP:
		moveUp(board, dimension);
		checkForSameNumbersAfterMovingUp(board, dimension);
		moveUp(board, dimension);
		break;
	case MOVE_DOWN:
		moveDown(board, dimension);
		checkForSameNumbersAfterMovingDown(board, dimension);
		moveDown(board, dimension);
		break;
	case MOVE_LEFT:
		moveLeft(board, dimension);
		checkForSameNumbersAfterMovingLeft(board, dimension);
		moveLeft(board, dimension);
		break;
	case MOVE_RIGHT:
		moveRight(board, dimension);
		checkForSameNumbersAfterMovingRight(board, dimension);
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
