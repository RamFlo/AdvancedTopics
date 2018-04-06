#ifndef GAMEPIECE_H_
class GamePiece {
public:
	char pieceType, curPieceType;
	int player;
	GamePiece(char type, char curType, int playerNum);
	GamePiece();
	void curTypeSetter(char newType);
};
#endif // !GAMEPIECE_H_

