/**
*
* Solution to course project 4
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2023/2024
*
* @author Aylin Mollaahmed
* @idnumber 3MI0600281
* @compiler VC
*
* functions for validation 
*
*/
#pragma once
#include "constants.h";
bool isDimensionSizeValid(int dimension) {
	return (dimension <= 10 && dimension >= 4);
}
bool isPlayerChoiceForNumberValid(int number) {
	return(number <= 3 && number >= 1);
}
bool isIndexValid(unsigned rowOrCol, unsigned dimension) {
	return rowOrCol <= dimension - 1 && rowOrCol >= 0;
}
bool isDirectionValid(char direction) {
	return direction == MOVE_DOWN || direction == MOVE_RIGHT || direction == MOVE_LEFT || direction == MOVE_UP;
}