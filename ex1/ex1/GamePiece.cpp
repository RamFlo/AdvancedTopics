class GamePiece {
	char pieceType, curPieceType;
public: 
	GamePiece(char type, char curType) :pieceType(type), curPieceType(curType) {}
	void curTypeSetter(char newType) {
		this->curPieceType = newType;
	}
};