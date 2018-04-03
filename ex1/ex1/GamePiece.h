#ifndef GAMEPIECE_H_
class GamePiece {
public:
	char pieceType, curPieceType;
	GamePiece(char type, char curType);
	GamePiece();
	void curTypeSetter(char newType);
};
#endif // !GAMEPIECE_H_

