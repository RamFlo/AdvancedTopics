#include "GameManager.h"

GameManager::GameManager(string gameMode)
{
	if (gameMode == "auto-vs-file") {
		//this->player1Algorithm = make_unique<AutoPlayerAlgorithm>();
		this->player2Algorithm = make_unique<FilePlayerAlgorithm>(2);
	}
	else if (gameMode == "file-vs-auto") {
		this->player1Algorithm = make_unique<FilePlayerAlgorithm>(1);
		//this->player2Algorithm = make_unique<AutoPlayerAlgorithm>();
	}
	else if (gameMode == "auto-vs-auto") {
		//this->player1Algorithm = make_unique<AutoPlayerAlgorithm>();
		//this->player2Algorithm = make_unique<AutoPlayerAlgorithm>();
	}
	else {
		this->player1Algorithm = make_unique<FilePlayerAlgorithm>(1);
		this->player2Algorithm = make_unique<FilePlayerAlgorithm>(2);
	}
	this->pieceCountMap["player1Flags"] = 0;
	this->pieceCountMap["player1Jokers"] = 0;
	this->pieceCountMap["player1Rocks"] = 0;
	this->pieceCountMap["player1Scissors"] = 0;
	this->pieceCountMap["player1Papers"] = 0;
	this->pieceCountMap["player1Bombs"] = 0;
	this->pieceCountMap["player2Flags"] = 0;
	this->pieceCountMap["player2Jokers"] = 0;
	this->pieceCountMap["player2Rocks"] = 0;
	this->pieceCountMap["player2Scissors"] = 0;
	this->pieceCountMap["player2Papers"] = 0;
	this->pieceCountMap["player2Bombs"] = 0;
	this->winner = 0;
	this->reason = "";
}

bool GameManager::updatePieceCount(int player, PiecePosition & curPiece, int incOrDec) {
	if (player == 1) {
		switch (curPiece.getPiece())
		{
		case 'J':
			this->pieceCountMap["player1Jokers"] += incOrDec;
			return (this->pieceCountMap["player1Jokers"] <= NUM_OF_J);
			break;
		case 'R':
			this->pieceCountMap["player1Rocks"] += incOrDec;
			return (this->pieceCountMap["player1Rocks"] <= NUM_OF_R);
			break;
		case 'P':
			this->pieceCountMap["player1Papers"] += incOrDec;
			return (this->pieceCountMap["player1Papers"] <= NUM_OF_P);
			break;
		case 'S':
			this->pieceCountMap["player1Scissors"] += incOrDec;
			return (this->pieceCountMap["player1Scissors"] <= NUM_OF_S);
			break;
		case 'B':
			this->pieceCountMap["player1Bombs"] += incOrDec;
			return (this->pieceCountMap["player1Bombs"] <= NUM_OF_B);
			break;
		case 'F':
			this->pieceCountMap["player1Flags"] += incOrDec;
			return (this->pieceCountMap["player1Flags"] <= NUM_OF_F);
			break;
		}
	}
	else {
		switch (curPiece.getPiece())
		{
		case 'J':
			this->pieceCountMap["player2Jokers"] += incOrDec;
			return (this->pieceCountMap["player2Jokers"] <= NUM_OF_J);
			break;
		case 'R':
			this->pieceCountMap["player2Rocks"] += incOrDec;
			return (this->pieceCountMap["player2Rocks"] <= NUM_OF_R);
			break;
		case 'P':
			this->pieceCountMap["player2Papers"] += incOrDec;
			return (this->pieceCountMap["player2Papers"] <= NUM_OF_P);
			break;
		case 'S':
			this->pieceCountMap["player2Scissors"] += incOrDec;
			return (this->pieceCountMap["player2Scissors"] <= NUM_OF_S);
			break;
		case 'B':
			this->pieceCountMap["player2Bombs"] += incOrDec;
			return (this->pieceCountMap["player2Bombs"] <= NUM_OF_B);
			break;
		case 'F':
			this->pieceCountMap["player2Flags"] += incOrDec;
			return (this->pieceCountMap["player2Flags"] <= NUM_OF_F);
			break;
		}
	}
	return false;
}

bool GameManager::isPlayerSquareEmptyDuringPositioning(int player, const Point& piecePos) {
	if (player == 1)
		return (this->p1InitialBoard->getPlayer(piecePos) == 0);
	return (this->p2InitialBoard->getPlayer(piecePos) == 0);
}

bool  GameManager::handlePositioningLine(PiecePosition & curPiece, int player) {
	if (curPiece.getPosition().getX() < 0)
		return false;
	if (!isPlayerSquareEmptyDuringPositioning(player, curPiece.getPosition())) {
		//cout << "Bad format: square is not empty for piece on line " << curLineNum << endl;
		return false;
	}
	if (player == 1)
		this->p1InitialBoard->setGamePieceOnBoard(curPiece, 1); //putting the piece on the player's board
	else
		this->p2InitialBoard->setGamePieceOnBoard(curPiece, 2); //putting the piece on the player's board
	if (!updatePieceCount(player, curPiece, 1)) { //checking there aren't too many instances of the current piece
		//cout << "Bad format: too many instances of " << curPiece->pieceType << " on line " << curLineNum << endl;
		return false;
	}
	return true;
}

bool GameManager::isEnoughFlags(int player) {
	if (player == 1)
		return this->pieceCountMap["player1Flags"] == NUM_OF_F;
	return this->pieceCountMap["player2Flags"] == NUM_OF_F;
}

bool GameManager::initializeBoardFromPositionsVector(vector<unique_ptr<PiecePosition>>& playerPositions, int player) {
	int i = 0;
	for (i = 0; i < playerPositions.size(); i++) {
		if (!this->handlePositioningLine(*(playerPositions[i]), player))
			return false;
	}
	if (!isEnoughFlags(player)) { //checking the player has enough flags (finished the while loop, positioning finished
		//cout << "Bad format: missing flags - flags are not positioned according to their number " << endl;
		return false;
	}
	return true;
}

// Simulates a fight between 2 pieces - returns a pointer to the winner
void GameManager::fight(vector<unique_ptr<FightInfo>>& fightsVecToFill, Point& pos) { //given two pieces determines which piece wins
	char p1, p2;
	unique_ptr<FightInfo> curFightInfoPtr;
	int winner = 0;
	if (this->p1InitialBoard->getPlayer(pos) == 0) {
		if (this->p2InitialBoard->getPlayer(pos) != 0)
			this->gBoard->setGamePieceOnBoard(p2InitialBoard->getGamePiece(pos),2);
	}
	else if (this->p2InitialBoard->getPlayer(pos) == 0)
		this->gBoard->setGamePieceOnBoard(p1InitialBoard->getGamePiece(pos), 1);
	else {
		p1 = this->p1InitialBoard->getGamePiece(pos).getPiece();
		p2 = this->p2InitialBoard->getGamePiece(pos).getPiece();
		if (p1 == 'J')
			p1 = this->p1InitialBoard->getGamePiece(pos).getJokerRep();
		if (p2 == 'J')
			p2 = this->p1InitialBoard->getGamePiece(pos).getJokerRep();
		if (p1 == 'B' || p2 == 'B' || (p1 == p2)) {
			updatePieceCount(1, p1InitialBoard->getGamePiece(pos), -1);
			updatePieceCount(2, p2InitialBoard->getGamePiece(pos), -1);
		}
		else if (p1 == 'F') {
			updatePieceCount(1, p1InitialBoard->getGamePiece(pos), -1);
			winner = 2;
		}
		else if (p2 == 'F') {
			updatePieceCount(2, p2InitialBoard->getGamePiece(pos), -1);
			winner = 1;
		}
		else if (p1 == 'S') {
			if (p2 == 'R') {
				updatePieceCount(1, p1InitialBoard->getGamePiece(pos), -1);
				winner = 2;
			}
			else if (p2 == 'P') {
				updatePieceCount(2, p2InitialBoard->getGamePiece(pos), -1);
				winner = 1;
			}
		}
		else if (p2 == 'S') {
			if (p1 == 'R') {
				updatePieceCount(2, p2InitialBoard->getGamePiece(pos), -1);
				winner = 1;
			}
			else if (p1 == 'P') {
				updatePieceCount(1, p1InitialBoard->getGamePiece(pos), -1);
				winner = 2;
			}
		}
		else if (p1 == 'R') {
			updatePieceCount(1, p1InitialBoard->getGamePiece(pos), -1);
			winner = 2;
		}
		else if (p2 == 'R') {
			updatePieceCount(2, p2InitialBoard->getGamePiece(pos), -1);
			winner = 1;
		}
	}
	//curFightInfoPtr = make_unique<GameFightInfo>(pos, p1, p2, winner);
	fightsVecToFill.push_back(make_unique<GameFightInfo>(pos, p1, p2, winner));
}

void GameManager::mergeTwoBoards(vector<unique_ptr<FightInfo>>& fightsVecToFill) {
	int col = 1, row = 1;
	for (row = 1; row <= N; row++) {
		for (col = 1; col <= M; col++) {
			MyPoint fightPos(col, row);
			fight(fightsVecToFill, fightPos);
		}	
	}
}


bool GameManager::initializeGameBoard()
{
	bool validPositioning = true;
	int i = 0;
	vector<unique_ptr<PiecePosition>> player1Positions, player2Positions;
	this->player1Algorithm->getInitialPositions(1, player1Positions);
	this->player2Algorithm->getInitialPositions(2, player2Positions);
	if (!this->initializeBoardFromPositionsVector(player1Positions, 1)) {
		this->winner = 2;
		this->reason= "Bad Positioning for player 1";
		validPositioning = false;
	}
	if (!this->initializeBoardFromPositionsVector(player2Positions, 2)) {
		if (this->winner == 0) {
			this->winner = 1;
			this->reason = "Bad Positioning for player 2";
			validPositioning = false;
		}
		else {
			this->winner = 0;
			this->reason = "Bad Positioning for both players";
			validPositioning = false;
		}
	}
	if (!validPositioning)
		return false;
	vector<unique_ptr<FightInfo>> fightsVec;
	this->mergeTwoBoards(fightsVec);
	this->player1Algorithm->notifyOnInitialBoard(*(this->gBoard), fightsVec);
	this->player2Algorithm->notifyOnInitialBoard(*(this->gBoard), fightsVec);
	return true;
}
