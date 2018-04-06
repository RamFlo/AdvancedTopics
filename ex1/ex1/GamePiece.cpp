#include "GamePiece.h"
GamePiece::GamePiece(char type, char curType,int playerNum) : pieceType(type), curPieceType(curType) ,player(playerNum) {}
GamePiece::GamePiece() : pieceType('\0'), curPieceType('\0') {}
void GamePiece:: curTypeSetter(char newType) {
	this->curPieceType = newType;
}


