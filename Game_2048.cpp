#include <iostream>
#include <fstream>
#include "constants.h"
#include "validation.h"
#include "input.h"
#include "stringFunctions.h"
#include "leaderboard.h"
#include "boardMoves.h"
using namespace std;

void printEnteringMenu() {
	cout << "Hello, are you ready to play?" << endl << endl;
	cout << "Please choose from the menu." << endl << endl;
	cout << "1. Start game" << endl;
	cout << "2. Leaderboard" << endl;
	cout << "3. Quit" << endl << endl;
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
		
		cout << "Current score: " << score << endl << endl;
		printBoard(board, dimension);
		cout << endl << "Enter direction: ";
		char direction = inputDirectionChoice();
		move(board, dimension, direction);
		if (hasEmptySpace(board, dimension))
		{
			generateRandom(board, dimension, score);
		}
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
	
	
	
	
	
	
	