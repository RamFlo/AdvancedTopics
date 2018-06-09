#include "AutoPlayerAlgorithm.h"

/*
constructor for AutoPlayerAlgorithm
*/
AutoPlayerAlgorithm::AutoPlayerAlgorithm(int player)
{
	this->knowBoard = make_unique<GameBoard>(); //the board that this player sees.
	this->player = player;
	this->myPieceCount["myFlags"] = 0;
	this->myPieceCount["myJokers"] = 0;
	this->myPieceCount["myRocks"] = 0;
	this->myPieceCount["myScissors"] = 0;
	this->myPieceCount["myPapers"] = 0;
	this->myPieceCount["myBombs"] = 0;
}

/*
returns the next piece to be positioned on the board.
When all pieces were positioned, returns '#'
*/
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

/*
Updates the player's piece count (adds or lowers the corresponding piece to pieceType).
*/
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

/*
returns whether or not a square is empty on self's board.
*/
bool AutoPlayerAlgorithm::isAutoPlayerSquareEmpty(const Point& piecePos) {
	return (this->knowBoard->getPlayer(piecePos)==0);
}

/*
randomly positions the player's pieces on the board, and fills the player's PiecePosition vector accordingly.
*/
void AutoPlayerAlgorithm::getInitialPositions(int player, std::vector<unique_ptr<PiecePosition>>& vectorToFill)
{
	int curPiecePosX, curPiecePosY;
	char pieceToPosition, curTypeIfJoker = 'B';
	while ((pieceToPosition = checkPiecesPositioned())!='#') {
		curPiecePosX = rand() % M + 1;
		curPiecePosY = rand() % N + 1;
		if (!isAutoPlayerSquareEmpty(MyPoint(curPiecePosX, curPiecePosY))) //if the randomly generated square already contains a piece, try again
			continue;
		if (pieceToPosition == 'J') {
			vectorToFill.push_back(make_unique<GamePiece>(pieceToPosition, curPiecePosX, curPiecePosY, curTypeIfJoker, player));
			this->knowBoard->setGamePieceOnBoard(GamePiece(pieceToPosition, curPiecePosX, curPiecePosY, curTypeIfJoker, player), player);

		}
		else {
			vectorToFill.push_back(make_unique<GamePiece>(pieceToPosition, curPiecePosX, curPiecePosY, '#', player));
			this->knowBoard->setGamePieceOnBoard(GamePiece(pieceToPosition, curPiecePosX, curPiecePosY, '#', player), player);
		}
		this->updateMyPieceCount(pieceToPosition, 1);
	}

}

/*
updates self's knowBoard according to the initial board and fights vector supplied by the game manager.
*/
void AutoPlayerAlgorithm::notifyOnInitialBoard(const Board & b, const std::vector<unique_ptr<FightInfo>>& fights)
{
	int i,col,row;
	//update knowBoard according to fights
	for (i = 0; (unsigned)i < fights.size(); i++) {
		if (fights[i]->getWinner() != this->player) {
			if (fights[i]->getWinner()==0)
				this->knowBoard->setGamePieceOnBoard(GamePiece('\0', fights[i]->getPosition().getX(), fights[i]->getPosition().getY(), '\0', 0), 0);
			else
				this->knowBoard->setGamePieceOnBoard(GamePiece(fights[i]->getPiece(fights[i]->getWinner()), fights[i]->getPosition().getX(), fights[i]->getPosition().getY(), '#', fights[i]->getWinner()), fights[i]->getWinner());
			this->updateMyPieceCount(fights[i]->getPiece(this->player), -1);
		}
	}
	//update knowBoard according to given board (put other player's unknown pieces on board)
	for (col = 1; col <= M; col++) {
		for (row = 1; row <= N; row++) {
			if (isAutoPlayerSquareEmpty(MyPoint(col, row)) && b.getPlayer(MyPoint(col, row)) != 0)
				this->knowBoard->setGamePieceOnBoard(GamePiece(UNKNOWN_PIECE, col, row, '#', b.getPlayer(MyPoint(col, row))), b.getPlayer(MyPoint(col, row)));
		}
	}
}

/*
updates self's knowBoard according to the other player's move.
*/
void AutoPlayerAlgorithm::notifyOnOpponentMove(const Move & move)
{
	char opponentPiece;
	int srcCol, srcRow, dstCol, dstRow,opponentNum;
	srcCol = move.getFrom().getX();
	srcRow = move.getFrom().getY();
	opponentNum = this->knowBoard->getPlayer(move.getFrom());
	opponentPiece = this->knowBoard->getGamePiece(move.getFrom()).getPiece();
	this->knowBoard->setGamePieceOnBoard(GamePiece('\0', srcCol, srcRow, '\0', 0), 0);
	if (isAutoPlayerSquareEmpty(move.getTo())) {
		dstCol = move.getTo().getX();
		dstRow = move.getTo().getY();
		this->knowBoard->setGamePieceOnBoard(GamePiece(opponentPiece, dstCol, dstRow, '#', opponentNum), opponentNum);
	}
}

/*
updates self's knowBoard according to a fight that occurred. If this player lost the fight, updates the other player's piece according to the fight's result.
*/
void AutoPlayerAlgorithm::notifyFightResult(const FightInfo & fightInfo)
{
	int fightCol = fightInfo.getPosition().getX();
	int fightRow = fightInfo.getPosition().getY();
	if (fightInfo.getWinner() == 0) {
		this->knowBoard->setGamePieceOnBoard(GamePiece('\0', fightCol, fightRow, '\0', 0), 0);
		this->updateMyPieceCount(fightInfo.getPiece(this->player), -1);
	}
	else {
		this->knowBoard->setGamePieceOnBoard(GamePiece(fightInfo.getPiece(fightInfo.getWinner()), fightCol, fightRow, '#', fightInfo.getWinner()), fightInfo.getWinner());
		if (fightInfo.getWinner() != this->player)
			this->updateMyPieceCount(fightInfo.getPiece(this->player), -1);
	}
}

/*
returns whether or not p1 piece beats p2 piece.
*/
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


/*
fills pointToFill with the position of a piece that is near this player's piece (found on myPiecePosition) that can be beaten.
If no such position exists, does nothing.
*/
void AutoPlayerAlgorithm::findNearbyBeatablePiece(const Point & myPiecePosition,MyPoint& pointToFill) {
	int col = myPiecePosition.getX(), row = myPiecePosition.getY(),dstPointPlayerNum;
	char myPiece = this->knowBoard->getGamePiece(myPiecePosition).getPiece(),opponentPiece;
	if (col + 1 <= M) {
		opponentPiece = this->knowBoard->getGamePiece(MyPoint(col + 1, row)).getPiece();
		dstPointPlayerNum = this->knowBoard->getGamePiece(MyPoint(col + 1, row)).getPlayer();
		if (dstPointPlayerNum != this->player && opponentPiece!='\0' && doesPiece1BeatPiece2(myPiece, opponentPiece)) {
			pointToFill.setX(col + 1);
			pointToFill.setY(row);
			return;
		}
	}
	if (col - 1 >= 1) {
		opponentPiece = this->knowBoard->getGamePiece(MyPoint(col - 1, row)).getPiece();
		dstPointPlayerNum = this->knowBoard->getGamePiece(MyPoint(col - 1, row)).getPlayer();
		if (dstPointPlayerNum != this->player && opponentPiece != '\0' && doesPiece1BeatPiece2(myPiece, opponentPiece)) {
			pointToFill.setX(col - 1);
			pointToFill.setY(row);
			return;
		}
	}
	if (row + 1 <= N) {
		opponentPiece = this->knowBoard->getGamePiece(MyPoint(col, row+1)).getPiece();
		dstPointPlayerNum = this->knowBoard->getGamePiece(MyPoint(col, row+1)).getPlayer();
		if (dstPointPlayerNum != this->player && opponentPiece != '\0' && doesPiece1BeatPiece2(myPiece, opponentPiece)) {
			pointToFill.setX(col);
			pointToFill.setY(row+1);
			return;
		}
	}
	if (row - 1 >= 1) {
		opponentPiece = this->knowBoard->getGamePiece(MyPoint(col, row-1)).getPiece();
		dstPointPlayerNum = this->knowBoard->getGamePiece(MyPoint(col , row-1)).getPlayer();
		if (dstPointPlayerNum != this->player && opponentPiece != '\0' && doesPiece1BeatPiece2(myPiece, opponentPiece)) {
			pointToFill.setX(col);
			pointToFill.setY(row-1);
			return;
		}
	}
}

/*
returns whether or not the piece located at myPiecePosition is a moveable piece.
*/
bool AutoPlayerAlgorithm::isMoveablePiece(const Point & myPiecePosition) {
	char actualPieceType = this->knowBoard->getGamePiece(myPiecePosition).getPiece();
	if (actualPieceType == 'J')
		actualPieceType = this->knowBoard->getGamePiece(myPiecePosition).getJokerRep();
	return (actualPieceType == 'R' || actualPieceType == 'P' || actualPieceType == 'S');
}

/*
fills pointToFill with a random legal move for the piece located at myPiecePosition. If not such move exists, does nothing.
*/
void AutoPlayerAlgorithm::findLegalMove(const Point & myPiecePosition, MyPoint& pointToFill) {
	int col = myPiecePosition.getX(), row = myPiecePosition.getY(), i, randDirectionNum;
	vector<int> myPossibleDirectionsVec;
	bool isNumInVector[4] = { false,false,false,false };
	while (myPossibleDirectionsVec.size() < 4) { //fill a vector with the numbers 0-3 in random order
		randDirectionNum = rand() % 4;
		if (!isNumInVector[randDirectionNum]) {
			myPossibleDirectionsVec.push_back(randDirectionNum);
			isNumInVector[randDirectionNum] = true;
		}
	}
	for (i = 0; i < 4; i++) { //pick a direction according to the randomly generated vector and check if valid move exists in that direction.
		if (myPossibleDirectionsVec[i] == 0 && col + 1 <= M && this->knowBoard->getGamePiece(MyPoint(col + 1, row)).getPlayer() != this->player) {
			pointToFill.setX(col + 1);
			pointToFill.setY(row);
			return;
		}
		if (myPossibleDirectionsVec[i] == 1 && col - 1 >= 1 && this->knowBoard->getGamePiece(MyPoint(col - 1, row)).getPlayer() != this->player) {
			pointToFill.setX(col - 1);
			pointToFill.setY(row);
			return;
		}
		if (myPossibleDirectionsVec[i] == 2 && row + 1 <= N && this->knowBoard->getGamePiece(MyPoint(col, row + 1)).getPlayer() != this->player) {
			pointToFill.setX(col);
			pointToFill.setY(row + 1);
			return;
		}
		if (myPossibleDirectionsVec[i] == 3 && row - 1 >= 1 && this->knowBoard->getGamePiece(MyPoint(col, row - 1)).getPlayer() != this->player) {
			pointToFill.setX(col);
			pointToFill.setY(row - 1);
			return;
		}
	}
	
}

/*
returns unique_ptr<Move> to this player's move.
*/
unique_ptr<Move> AutoPlayerAlgorithm::getMove()
{
	int col, row, randIndexInPosVector;
	char movingPieceType, movingPieceJokerRep;
	vector<MyPoint> myPiecesPositions;
	MyPoint pointToMoveTo(-1, -1);
	for (col = 1; col <= M; col++) { //try to find a move that beats the other player's piece.
		for (row = 1; row <= N; row++) {
			if (this->knowBoard->getPlayer(MyPoint(col, row)) == this->player && this->isMoveablePiece(MyPoint(col, row))) {
				myPiecesPositions.push_back(MyPoint(col, row));
				findNearbyBeatablePiece(MyPoint(col, row), pointToMoveTo);
				if (pointToMoveTo.getX() != -1) {
					movingPieceType = this->knowBoard->getGamePiece(MyPoint(col, row)).getPiece();
					movingPieceJokerRep = this->knowBoard->getGamePiece(MyPoint(col, row)).getJokerRep();
					//assuming that I won, even if I lost, since notify on fight result will correct me: update self's board according to the move found.
					this->knowBoard->setGamePieceOnBoard(GamePiece(movingPieceType, pointToMoveTo.getX(), pointToMoveTo.getY(), movingPieceJokerRep, this->player), this->player);
					this->knowBoard->setGamePieceOnBoard(GamePiece('\0', col, row, '\0', 0), 0);
					return make_unique<GameMove>(col, row, pointToMoveTo.getX(), pointToMoveTo.getY());
				}
			}
		}
	}
	while (pointToMoveTo.getX() == -1) { //if no good move found, randomly picks a piece and moves it in a random direction.
		if (myPiecesPositions.size() == 0)
			printf("myPiecesPositions.size() == 0\n");
		randIndexInPosVector = rand() % myPiecesPositions.size();
		findLegalMove(myPiecesPositions[randIndexInPosVector], pointToMoveTo);
	}
	movingPieceType = this->knowBoard->getGamePiece(myPiecesPositions[randIndexInPosVector]).getPiece();
	movingPieceJokerRep = this->knowBoard->getGamePiece(myPiecesPositions[randIndexInPosVector]).getJokerRep();
	//assuming that I won, even if I lost, since notify on fight result will correct me: update self's board according to the move found.
	this->knowBoard->setGamePieceOnBoard(GamePiece(movingPieceType, pointToMoveTo.getX(), pointToMoveTo.getY(), movingPieceJokerRep, this->player), this->player);
	this->knowBoard->setGamePieceOnBoard(GamePiece('\0', myPiecesPositions[randIndexInPosVector].getX(), myPiecesPositions[randIndexInPosVector].getY(), '\0', 0), 0);
	return make_unique<GameMove>(myPiecesPositions[randIndexInPosVector].getX(), myPiecesPositions[randIndexInPosVector].getY(), pointToMoveTo.getX(), pointToMoveTo.getY());
}

unique_ptr<JokerChange> AutoPlayerAlgorithm::getJokerChange()
{
	return nullptr;
}
