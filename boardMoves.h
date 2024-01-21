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
void moveUp(size_t** board, size_t dimension)
{
	for (size_t col = 0; col < dimension; col++)
	{
		size_t toMove = 0;
		for (size_t row = 0; row < dimension; row++)
		{
			if (board[row][col] == 0)
			{
				continue;
			}

			board[toMove][col] = board[row][col];
			if (row != toMove)
			{
				board[row][col] = 0;
			}
			toMove++;
		}
	}
}

void moveDown(size_t** board, size_t dimension)
{
	for (size_t col = 0; col < dimension; col++)
	{
		size_t toMove = dimension - 1;
		for (int row = dimension - 1; row >= 0; row--)
		{
			if (board[row][col] == 0)
			{
				continue;
			}

			board[toMove][col] = board[row][col];
			if (row != toMove)
			{
				board[row][col] = 0;
			}
			toMove--;
		}
	}
}

void moveRight(size_t** board, size_t dimension)
{
	for (size_t row = 0; row < dimension; row++)
	{
		size_t toMove = dimension - 1;
		for (int col = dimension - 1; col >= 0; col--)
		{
			if (board[row][col] == 0)
			{
				continue;
			}

			board[row][toMove] = board[row][col];
			if (col != toMove)
			{
				board[row][col] = 0;
			}
			toMove--;
		}
	}
}

void moveLeft(size_t** board, size_t dimension)
{
	for (size_t row = 0; row < dimension; row++)
	{
		size_t toMove = 0;
		for (size_t col = 0; col < dimension; col++)
		{
			if (board[row][col] == 0)
			{
				continue;
			}

			board[row][toMove] = board[row][col];
			if (col != toMove)
			{
				board[row][col] = 0;
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
				if (board[row][col] == board[row + 1][col] ||
					board[row][col] == 0)
				{
					board[row][col] += board[row + 1][col];
					board[row + 1][col] = 0;
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
				if (board[row][col] == board[row - 1][col]||board[row][col] == 0)
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
				if (board[row][col] == board[row][col + 1] || board[row][col] == 0)
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
				if (board[row][col] == board[row][col - 1] || board[row][col] == 0)
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