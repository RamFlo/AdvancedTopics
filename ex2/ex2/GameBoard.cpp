#include "GameBoard.h"

GamePiece & GameBoard::getGamePiece(const Point & pos) const
{
	return *(this->finalBoard[pos.getY() - 1][pos.getX() - 1]);
}

GameBoard::GameBoard()
{
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++)
			this->finalBoard[i][j] = make_unique<GamePiece>('\0', j+1, i+1, '\0', 0);
	}
}

/*
returns the player residing at position pos on the board.
*/
int GameBoard::getPlayer(const Point & pos) const
{
	return this->getGamePiece(pos).getPlayer();
}

//sets a piece on board accoring to the given piece
void GameBoard::setGamePieceOnBoard(const PiecePosition & piece,int player)
{
	this->finalBoard[piece.getPosition().getY() - 1][piece.getPosition().getX() - 1] = make_unique<GamePiece>(piece.getPiece(), piece.getPosition().getX(), piece.getPosition().getY(),piece.getJokerRep(),player);
}
