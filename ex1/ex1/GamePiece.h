#ifndef GAMEPIECE_H_
class GamePiece {
	char pieceType, curPieceType;
public:
	GamePiece(char type, char curType);
	GamePiece();
	void curTypeSetter(char newType);
};
#endif // !GAMEPIECE_H_

