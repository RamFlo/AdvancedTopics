#ifndef MAINAUX_H_
#define MAINAUX_H_
#define N 10
#define M 10
#define NUM_OF_R 2 
#define NUM_OF_P 5 
#define NUM_OF_S 1 
#define NUM_OF_B 2 
#define NUM_OF_J 2 
#define NUM_OF_F 1 
#define FAILURE_CHAR 'T'
#include "GameBoard.h"

bool doPiecePositioning(GameBoard* board, string fileName, int player);
void mergeBoardsToFinalBoard(GameBoard* board);
#endif // !MAINAUX_H_

