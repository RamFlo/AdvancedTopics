#include "GamePiece.h"
GamePiece::GamePiece(char type, char curType) : pieceType(type), curPieceType(curType) {}
GamePiece::GamePiece() : pieceType('\0'), curPieceType('\0') {}
void GamePiece:: curTypeSetter(char newType) {
	this->curPieceType = newType;
}


