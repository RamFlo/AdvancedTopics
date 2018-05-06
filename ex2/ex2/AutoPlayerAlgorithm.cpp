#include "AutoPlayerAlgorithm.h"

AutoPlayerAlgorithm::AutoPlayerAlgorithm(int player)
{
	this->knowBoard = make_unique<GameBoard>();
	this->player = player;
	this->myPieceCount["myFlags"] = 0;
	this->myPieceCount["myJokers"] = 0;
	this->myPieceCount["myRocks"] = 0;
	this->myPieceCount["myScissors"] = 0;
	this->myPieceCount["myPapers"] = 0;
	this->myPieceCount["myBombs"] = 0;
	/*this->myPieceCount["opponentFlags"] = 0;
	this->myPieceCount["opponentJokers"] = 0;
	this->myPieceCount["player2Rocks"] = 0;
	this->myPieceCount["player2Scissors"] = 0;
	this->myPieceCount["player2Papers"] = 0;
	this->myPieceCount["player2Bombs"] = 0;*/
}

char AutoPlayerAlgorithm::checkPiecesPositioned() {
	if (this->myPieceCount["myFlags"] < NUM_OF_F)
		return 'F';
	else if (this->myPieceCount["myJokers"] < NUM_OF_J)
		return 'J';
	else if (this->myPieceCount["myRocks"] < NUM_OF_R)
		return 'R';
	else if (this->myPieceCount["myScissors"] < NUM_OF_S)
		return 'S';
	else if (this->myPieceCount["myPapers"] < NUM_OF_P)
		return 'P';
	else if (this->myPieceCount["myBombs"] < NUM_OF_B)
		return 'B';
	return '#';
}

void AutoPlayerAlgorithm::updateMyPieceCount(char pieceType,int incOrDec) {
	switch (pieceType) {
	case 'F':
		this->myPieceCount["myFlags"] += incOrDec;
		break;
	case 'J':
		this->myPieceCount["myJokers"] += incOrDec;
		break;
	case 'R':
		this->myPieceCount["myRocks"] += incOrDec;
		break;
	case 'S':
		this->myPieceCount["myScissors"] += incOrDec;
		break;
	case 'P':
		this->myPieceCount["myPapers"] += incOrDec;
		break;
	case 'B':
		this->myPieceCount["myBombs"] += incOrDec;
		break;
	}
}


bool AutoPlayerAlgorithm::isAutoPlayerSquareEmpty(const Point& piecePos) {
	return (this->knowBoard->getPlayer(piecePos)==0);
}

void AutoPlayerAlgorithm::getInitialPositions(int player, std::vector<unique_ptr<PiecePosition>>& vectorToFill)
{
	int curPiecePosX, curPiecePosY;
	char pieceToPosition, curTypeIfJoker = 'B';
	//bool isFirstFlagPositioning = true;
	srand(time(NULL)+this->player);
	while ((pieceToPosition = checkPiecesPositioned())!='#') {
		curPiecePosX = rand() % M + 1;
		curPiecePosY = rand() % N + 1;
		if (!isAutoPlayerSquareEmpty(MyPoint(curPiecePosX, curPiecePosY)))
			continue;
		if (pieceToPosition == 'J') {
			vectorToFill.push_back(make_unique<GamePiece>(pieceToPosition, curPiecePosX, curPiecePosY, curTypeIfJoker, player));
			this->knowBoard->setGamePieceOnBoard(GamePiece(pieceToPosition, curPiecePosX, curPiecePosY, curTypeIfJoker, player), player);

		}
		else {
			vectorToFill.push_back(make_unique<GamePiece>(pieceToPosition, curPiecePosX, curPiecePosY, '#', player));
			this->knowBoard->setGamePieceOnBoard(GamePiece(pieceToPosition, curPiecePosX, curPiecePosY, curTypeIfJoker, player), player);
		}
		this->updateMyPieceCount(pieceToPosition, 1);
	}

}

void AutoPlayerAlgorithm::notifyOnInitialBoard(const Board & b, const std::vector<unique_ptr<FightInfo>>& fights)
{
	int i,col,row;
	//update knowBoard according to fights
	for (i = 0; i < fights.size(); i++) {
		if (fights[i]->getWinner() != this->player) {
			if (fights[i]->getWinner()==0)
				this->knowBoard->setGamePieceOnBoard(GamePiece('\0', fights[i]->getPosition().getX(), fights[i]->getPosition().getY(), '\0', 0), 0);
			else
				this->knowBoard->setGamePieceOnBoard(GamePiece(fights[i]->getPiece(fights[i]->getWinner()), fights[i]->getPosition().getX(), fights[i]->getPosition().getY(), '#', fights[i]->getWinner()), fights[i]->getWinner());
			this->updateMyPieceCount(fights[i]->getPiece(this->player), -1);
		}
	}
	//update knowBoard according to given board
	for (col = 1; col < M; col++) {
		for (row = 1; row < N; row++) {
			if (isAutoPlayerSquareEmpty(MyPoint(col, row)) && b.getPlayer(MyPoint(col, row)) != 0)
				this->knowBoard->setGamePieceOnBoard(GamePiece(UNKNOWN_PIECE, col, row, '#', b.getPlayer(MyPoint(col, row))), b.getPlayer(MyPoint(col, row)));
		}
	}
}

void AutoPlayerAlgorithm::notifyOnOpponentMove(const Move & move)
{
	char opponentPiece;
	int srcCol, srcRow, dstCol, dstRow,opponentNum;
	if (isAutoPlayerSquareEmpty(move.getTo())) {
		opponentPiece = this->knowBoard->getGamePiece(move.getFrom()).getPiece();
		srcCol = move.getFrom().getX();
		srcRow = move.getFrom().getY();
		dstCol = move.getTo().getX();
		dstRow = move.getTo().getY();
		opponentNum = this->knowBoard->getPlayer(move.getFrom());
		this->knowBoard->setGamePieceOnBoard(GamePiece(opponentPiece, dstCol, dstRow, '#', opponentNum), opponentNum);
		this->knowBoard->setGamePieceOnBoard(GamePiece('\0', srcCol, srcRow, '\0', 0), 0);
	}
}

void AutoPlayerAlgorithm::notifyFightResult(const FightInfo & fightInfo)
{
	int srcCol = fightInfo.getPosition().getX();
	int srcRow = fightInfo.getPosition().getY();
	if (fightInfo.getWinner() != this->player) {
		if (fightInfo.getWinner() == 0) 
			this->knowBoard->setGamePieceOnBoard(GamePiece('\0', srcCol, srcRow, '\0', 0), 0);
		else {
			this->knowBoard->setGamePieceOnBoard(GamePiece(fightInfo.getPiece(fightInfo.getWinner()), srcCol, srcRow, '#', fightInfo.getWinner()), 0);
			this->updateMyPieceCount(fightInfo.getPiece(this->player), -1);
		}	
	}
}

bool AutoPlayerAlgorithm::doesPiece1BeatPiece2(char p1, char p2) {
	if (p1 =='B' || p2 == 'B' || p1 == p2)
		return true;
	if (p1 == 'F')
		return false;
	if (p2 == 'F') {
		return true;
	}
	else if (p1 == 'S') {
		if (p2 == 'R')
			return false;
		else if (p2 == 'P')
			return true;
	}
	else if (p2 == 'S') {
		if (p1 == 'R')
			return true;
		else if (p1 == 'P')
			return false;
	}
	else if (p1 == 'R')
		return false;
	else if (p2 == 'R')
		return true;
	return false;
}



void AutoPlayerAlgorithm::findNearbyBeatablePiece(const Point & myPiecePosition,MyPoint& pointToFill) {
	int col = myPiecePosition.getX(), row = myPiecePosition.getY(),dstPointPlayerNum;
	char myPiece = this->knowBoard->getGamePiece(myPiecePosition).getPiece(),opponentPiece;
	if (col + 1 <= M) {
		opponentPiece = this->knowBoard->getGamePiece(MyPoint(col + 1, row)).getPiece();
		dstPointPlayerNum = this->knowBoard->getGamePiece(MyPoint(col + 1, row)).getPlayer();
		if (dstPointPlayerNum != this->player && doesPiece1BeatPiece2(myPiece, opponentPiece)) {
			pointToFill.setX(col + 1);
			pointToFill.setY(row);
			return;
		}
	}
	if (col - 1 >= 1) {
		opponentPiece = this->knowBoard->getGamePiece(MyPoint(col - 1, row)).getPiece();
		dstPointPlayerNum = this->knowBoard->getGamePiece(MyPoint(col + 1, row)).getPlayer();
		if (dstPointPlayerNum != this->player && doesPiece1BeatPiece2(myPiece, opponentPiece)) {
			pointToFill.setX(col - 1);
			pointToFill.setY(row);
			return;
		}
	}
	if (row + 1 <= N) {
		opponentPiece = this->knowBoard->getGamePiece(MyPoint(col, row+1)).getPiece();
		dstPointPlayerNum = this->knowBoard->getGamePiece(MyPoint(col + 1, row)).getPlayer();
		if (dstPointPlayerNum != this->player && doesPiece1BeatPiece2(myPiece, opponentPiece)) {
			pointToFill.setX(col);
			pointToFill.setY(row+1);
			return;
		}
	}
	if (row - 1 >= 1) {
		opponentPiece = this->knowBoard->getGamePiece(MyPoint(col, row-1)).getPiece();
		dstPointPlayerNum = this->knowBoard->getGamePiece(MyPoint(col + 1, row)).getPlayer();
		if (dstPointPlayerNum != this->player && doesPiece1BeatPiece2(myPiece, opponentPiece)) {
			pointToFill.setX(col);
			pointToFill.setY(row-1);
			return;
		}
	}
}

bool AutoPlayerAlgorithm::isMoveablePiece(const Point & myPiecePosition) {
	char actualPieceType = this->knowBoard->getGamePiece(myPiecePosition).getPiece();
	if (actualPieceType == 'J')
		actualPieceType = this->knowBoard->getGamePiece(myPiecePosition).getJokerRep();
	return (actualPieceType == 'R' || actualPieceType == 'P' || actualPieceType == 'S');
}

void AutoPlayerAlgorithm::findLegalMove(const Point & myPiecePosition, MyPoint& pointToFill) {
	int col = myPiecePosition.getX(), row = myPiecePosition.getY();
	char myPiece = this->knowBoard->getGamePiece(myPiecePosition).getPiece(), opponentPiece;
	if (col + 1 <= M && this->knowBoard->getGamePiece(MyPoint(col + 1, row)).getPlayer() != this->player) {
		pointToFill.setX(col + 1);
		pointToFill.setY(row);
		return;
	}
	if (col - 1 >= 1 && this->knowBoard->getGamePiece(MyPoint(col - 1, row)).getPlayer() != this->player) {
		pointToFill.setX(col - 1);
		pointToFill.setY(row);
		return;
	}
	if (row + 1 <= N && this->knowBoard->getGamePiece(MyPoint(col, row + 1)).getPlayer() != this->player) {
		pointToFill.setX(col);
		pointToFill.setY(row + 1);
		return;
	}
	if (row - 1 >= 1 && this->knowBoard->getGamePiece(MyPoint(col, row - 1)).getPlayer() != this->player) {
		pointToFill.setX(col);
		pointToFill.setY(row - 1);
		return;
	}
}

unique_ptr<Move> AutoPlayerAlgorithm::getMove()
{
	int col, row, randIndexInPosVector;
	vector<MyPoint> myPiecesPositions;
	MyPoint pointToMoveTo(-1, -1);
	for (col = 1; col <= M; col++) {
		for (row = 1; row <= N; row++) {
			if (this->knowBoard->getPlayer(MyPoint(col, row)) == this->player && this->isMoveablePiece(MyPoint(col, row))) {
				myPiecesPositions.push_back(MyPoint(col, row));
				findNearbyBeatablePiece(MyPoint(col, row), pointToMoveTo);
				if (pointToMoveTo.getX() > 10)
					int b = 3;
				if (pointToMoveTo.getX() != -1)
					return make_unique<GameMove>(col, row, pointToMoveTo.getX(), pointToMoveTo.getY());
			}
		}
	}
	srand(time(NULL) + 2*this->player);
	randIndexInPosVector = rand() % myPiecesPositions.size();
	while (pointToMoveTo.getX() == -1) {
		randIndexInPosVector = rand() % myPiecesPositions.size();
		findLegalMove(myPiecesPositions[randIndexInPosVector], pointToMoveTo);
	}
	if (pointToMoveTo.getX() > 10)
		int b = 3;
	return make_unique<GameMove>(col, row, pointToMoveTo.getX(), pointToMoveTo.getY());
}

unique_ptr<JokerChange> AutoPlayerAlgorithm::getJokerChange()
{
	return nullptr;
}
