#ifndef GAMEPIECE_H_
class GamePiece {
public:
	char pieceType, curPieceType;	//only Joker has a different pieceType and curPieceType
	int player;
	GamePiece(char type, char curType, int playerNum);
	GamePiece();
	void curTypeSetter(char newType);
};
#endif // !GAMEPIECE_H_

