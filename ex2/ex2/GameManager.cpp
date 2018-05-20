#include "GameManager.h"

GameManager::GameManager(string gameMode)
{

	if (gameMode == "auto-vs-file") {
		this->player1Algorithm = make_unique<AutoPlayerAlgorithm>(1);
		this->player2Algorithm = make_unique<FilePlayerAlgorithm>(2);
	}
	else if (gameMode == "file-vs-auto") {
		this->player1Algorithm = make_unique<FilePlayerAlgorithm>(1);
		this->player2Algorithm = make_unique<AutoPlayerAlgorithm>(2);
	}
	else if (gameMode == "auto-vs-auto") {
		this->player1Algorithm = make_unique<AutoPlayerAlgorithm>(1);
		this->player2Algorithm = make_unique<AutoPlayerAlgorithm>(2);
	}
	else {
		this->player1Algorithm = make_unique<FilePlayerAlgorithm>(1);
		this->player2Algorithm = make_unique<FilePlayerAlgorithm>(2);
	}
	this->p1InitialBoard = make_unique<GameBoard>();
	this->p2InitialBoard = make_unique<GameBoard>();
	this->gBoard = make_unique<GameBoard>();
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

bool GameManager::updatePieceCount(int player, char curPiece, int incOrDec) {
	if (player == 1) {
		switch (curPiece)
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
		switch (curPiece)
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
	if (!updatePieceCount(player, curPiece.getPiece(), 1)) { //checking there aren't too many instances of the current piece
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
	for (i = 0; i < (int)playerPositions.size(); i++) {
		if (!this->handlePositioningLine(*(playerPositions[i]), player))
			return false;
	}
	if (!isEnoughFlags(player)) { //checking the player has enough flags (finished the while loop, positioning finished
		//cout << "Bad format: missing flags - flags are not positioned according to their number " << endl;
		return false;
	}
	return true;
}

int GameManager::fightBetweenTwoPiecesAndUpdatePieceCount(char p1Piece, char p2Piece,char p1ActualPiece, char p2ActualPiece) {
	int fightWinner = 0;
	if (p1Piece == 'B' || p2Piece == 'B' || (p1Piece == p2Piece)) {
		updatePieceCount(1, p1ActualPiece, -1);
		updatePieceCount(2, p2ActualPiece, -1);
	}
	else if (p1Piece == 'F') {
		updatePieceCount(1, p1ActualPiece, -1);
		fightWinner = 2;
	}
	else if (p2Piece == 'F') {
		updatePieceCount(2, p2ActualPiece, -1);
		fightWinner = 1;
	}
	else if (p1Piece == 'S') {
		if (p2Piece == 'R') {
			updatePieceCount(1, p1ActualPiece, -1);
			fightWinner = 2;
		}
		else if (p2Piece == 'P') {
			updatePieceCount(2, p2ActualPiece, -1);
			fightWinner = 1;
		}
	}
	else if (p2Piece == 'S') {
		if (p1Piece == 'R') {
			updatePieceCount(2, p2ActualPiece, -1);
			fightWinner = 1;
		}
		else if (p1Piece == 'P') {
			updatePieceCount(1, p1ActualPiece, -1);
			fightWinner = 2;
		}
	}
	else if (p1Piece == 'R') {
		updatePieceCount(1, p1ActualPiece, -1);
		fightWinner = 2;
	}
	else if (p2Piece == 'R') {
		updatePieceCount(2, p2ActualPiece, -1);
		fightWinner = 1;
	}
	return fightWinner;
}

// Simulates a fight between 2 pieces - returns a pointer to the winner
void GameManager::fight(vector<unique_ptr<FightInfo>>& fightsVecToFill, Point& pos) { //given two pieces determines which piece wins
	char p1, p2;
	unique_ptr<FightInfo> curFightInfoPtr;
	int fightWinner = 0;
	bool shouldUpdateFightsVector = true;
	if (this->p1InitialBoard->getPlayer(pos) == 0) {
		shouldUpdateFightsVector = false;
		if (this->p2InitialBoard->getPlayer(pos) != 0)
			fightWinner = 2;
	}
	else if (this->p2InitialBoard->getPlayer(pos) == 0) {
		shouldUpdateFightsVector = false;
		fightWinner = 1;
	}
	else {
		p1 = this->p1InitialBoard->getGamePiece(pos).getPiece();
		p2 = this->p2InitialBoard->getGamePiece(pos).getPiece();
		if (p1 == 'J')
			p1 = this->p1InitialBoard->getGamePiece(pos).getJokerRep();
		if (p2 == 'J')
			p2 = this->p1InitialBoard->getGamePiece(pos).getJokerRep();
		fightWinner = fightBetweenTwoPiecesAndUpdatePieceCount(p1, p2, p1InitialBoard->getGamePiece(pos).getPiece(), p2InitialBoard->getGamePiece(pos).getPiece());
	}
	/*if (p1 == 'B' || p2 == 'B' || (p1 == p2)) {
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
}*/
	//curFightInfoPtr = make_unique<GameFightInfo>(pos, p1, p2, 56);
	if (shouldUpdateFightsVector)
		fightsVecToFill.push_back(make_unique<GameFightInfo>(pos, p1, p2, fightWinner));
	if (fightWinner == 1)
		this->gBoard->setGamePieceOnBoard(p1InitialBoard->getGamePiece(pos), 1);
	else if (fightWinner == 2)
		this->gBoard->setGamePieceOnBoard(p2InitialBoard->getGamePiece(pos), 2);
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

bool GameManager::checkWinnerAccordingToFlags() {
	if (this->pieceCountMap["player1Flags"] == 0) {
		this->winner = 2;
		this->reason = "All flags of the opponent are captured";
		return true;
	}
	else if (this->pieceCountMap["player2Flags"] == 0) {
		this->winner = 1;
		this->reason = "All flags of the opponent are captured";
		return true;
	}
	return false;
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
	if (this->pieceCountMap["player1Flags"] == 0 && this->pieceCountMap["player2Flags"] == 0) {
		this->winner = 0;
		this->reason = "A tie - all flags are eaten by both players in the position files";
		return false;
	}
	else if (this->checkWinnerAccordingToFlags())
		return false;
	this->player1Algorithm->notifyOnInitialBoard(*(this->gBoard), fightsVec);
	this->player2Algorithm->notifyOnInitialBoard(*(this->gBoard), fightsVec);
	return true;
}

bool GameManager::isThereLegalMove(const Point & myPiecePosition) {
	int col = myPiecePosition.getX(), row = myPiecePosition.getY();
	char myPiece = this->gBoard->getGamePiece(myPiecePosition).getPiece();
	if (!isMovingPiece(this->gBoard->getGamePiece(myPiecePosition)))
		return false;
	if (col + 1 <= M && this->gBoard->getGamePiece(MyPoint(col + 1, row)).getPlayer() != this->gBoard->getPlayer(myPiecePosition))
		return true;
	if (col - 1 >= 1 && this->gBoard->getGamePiece(MyPoint(col - 1, row)).getPlayer() != this->gBoard->getPlayer(myPiecePosition))
		return true;
	if (row + 1 <= N && this->gBoard->getGamePiece(MyPoint(col, row + 1)).getPlayer() != this->gBoard->getPlayer(myPiecePosition))
		return true;
	if (row - 1 >= 1 && this->gBoard->getGamePiece(MyPoint(col, row - 1)).getPlayer() != this->gBoard->getPlayer(myPiecePosition))
		return true;
	return false;
}

bool GameManager::playerHasLegalMove(int player) {
	int col, row;
	for (col = 1; col <= M; col++) {
		for (row = 1; row <= N; row++) {
			if (this->gBoard->getPlayer(MyPoint(col, row)) == player && isThereLegalMove(MyPoint(col, row)))
				return true;
		}
	}
	return false;
}

int GameManager::getOtherPlayer(int player) {
	if (player == 1)
		return 2;
	else
		return 1;
}

bool GameManager::isMovingPiece(const GamePiece & piece) {
	char pieceType = piece.getPiece();
	if (pieceType == 'J')
		pieceType = piece.getJokerRep();
	if (pieceType == 'R' || pieceType == 'S' || pieceType == 'P')
		return true;
	return false;
}

bool GameManager::isLegalMove(int player, const Point & fromPoint, const Point & toPoint) {
	int xDiff, yDiff;
	if (fromPoint.getX() > M || fromPoint.getX() < 1 || fromPoint.getY() > N || fromPoint.getY() < 1 || toPoint.getX() > M || toPoint.getX() < 1 || toPoint.getY() > N || toPoint.getY() < 1)
		return false;
	if (this->gBoard->getPlayer(fromPoint) != player)
		return false;
	if (this->gBoard->getPlayer(toPoint) == player)
		return false;
	if (!isMovingPiece(this->gBoard->getGamePiece(fromPoint)))
		return false;
	xDiff = abs(fromPoint.getX() - toPoint.getX());
	yDiff= abs(fromPoint.getY() - toPoint.getY());
	if (!((xDiff == 1 && yDiff == 0) || (xDiff == 0 && yDiff == 1)))
		return false;
	return true;
}

bool GameManager::checkIfPlayerHasNoFlags(int player) {
	return this->pieceCountMap["player" + to_string(player) + "Flags"] == 0;
}

bool GameManager::isLegalJokerChange(const JokerChange & curJokerChange, int player) {
	if (curJokerChange.getJokerChangePosition().getX() > M || curJokerChange.getJokerChangePosition().getX() < 1 || curJokerChange.getJokerChangePosition().getY() > N || curJokerChange.getJokerChangePosition().getY() < 1 )
		return false;
	if (curJokerChange.getJokerNewRep() != 'R' && curJokerChange.getJokerNewRep() != 'P' && curJokerChange.getJokerNewRep() != 'S' && curJokerChange.getJokerNewRep() != 'B')
		return false;
	if (this->gBoard->getGamePiece(curJokerChange.getJokerChangePosition()).getPlayer() != player)
		return false;
	if (this->gBoard->getGamePiece(curJokerChange.getJokerChangePosition()).getPiece() != 'J')
		return false;
	return true;
}

void GameManager::playGame() {
	int turnsWithoutFight = 0, curPlayer = 1, curFightWinner, moveNum = 0;
	char movingPieceType, movingPieceCurType, curPlayerPiece,opponentPiece;
	unique_ptr<Move> curMove;
	unique_ptr<JokerChange> curJokerChange;
	//this->createOutputFile();
	while (turnsWithoutFight < MAX_TURNS_WITHOUT_FIGHT) {
		moveNum++;
		turnsWithoutFight++;
		if (!playerHasLegalMove(curPlayer)) {
			this->reason = "All moving PIECEs of the opponent are eaten";
			this->winner = this->getOtherPlayer(curPlayer);
			return;
		}
		if (curPlayer == 1)
			curMove = this->player1Algorithm->getMove();
		else
			curMove = this->player2Algorithm->getMove();
		//printf("Print A: player %d: move %c from: <%d, %d> to: <%d, %d>\n", curPlayer, this->gBoard->getGamePiece(curMove->getFrom()).getPiece(), curMove->getFrom().getX(), curMove->getFrom().getY(), curMove->getTo().getX(), curMove->getTo().getY());
		if (!isLegalMove(curPlayer, curMove->getFrom(), curMove->getTo())) {
			this->reason = "Bad Moves input for player " + to_string(curPlayer);
			this->winner = this->getOtherPlayer(curPlayer);
			return;
		}
		if (curPlayer == 1)
			this->player2Algorithm->notifyOnOpponentMove(*(curMove));
		else
			this->player1Algorithm->notifyOnOpponentMove(*(curMove));
		movingPieceType = this->gBoard->getGamePiece(curMove->getFrom()).getPiece();
		movingPieceCurType = this->gBoard->getGamePiece(curMove->getFrom()).getJokerRep();
		//printf("Print B: player %d: move %c from: <%d, %d> to: <%d, %d>\n\n", curPlayer, movingPieceType, curMove->getFrom().getX(), curMove->getFrom().getY(), curMove->getTo().getX(), curMove->getTo().getY());
		if (this->gBoard->getPlayer(curMove->getTo()) == 0)
			this->gBoard->setGamePieceOnBoard(GamePiece(movingPieceType, curMove->getTo().getX(), curMove->getTo().getY(), movingPieceCurType, curPlayer), curPlayer);
		else {//handle fight
			turnsWithoutFight = 0;
			curPlayerPiece = movingPieceType;
			opponentPiece = this->gBoard->getGamePiece(curMove->getTo()).getPiece();
			if (curPlayerPiece == 'J')
				curPlayerPiece = movingPieceCurType;
			if (opponentPiece == 'J')
				opponentPiece = this->gBoard->getGamePiece(curMove->getTo()).getJokerRep();
			if (curPlayer == 1) {
				curFightWinner = fightBetweenTwoPiecesAndUpdatePieceCount(curPlayerPiece, opponentPiece, this->gBoard->getGamePiece(curMove->getTo()).getPiece(), movingPieceType);
				//curFightWinner = fightBetweenTwoPiecesAndUpdatePieceCount(curPlayerPiece, opponentPiece, movingPieceType, this->gBoard->getGamePiece(curMove->getTo()).getPiece());
			}
				
			else {
				curFightWinner = fightBetweenTwoPiecesAndUpdatePieceCount(opponentPiece, curPlayerPiece, this->gBoard->getGamePiece(curMove->getTo()).getPiece(), movingPieceType);
				//curFightWinner = fightBetweenTwoPiecesAndUpdatePieceCount(opponentPiece, curPlayerPiece, movingPieceType, this->gBoard->getGamePiece(curMove->getTo()).getPiece());
			}
			if (curPlayer == 1) {
				GameFightInfo curFightInfo(curMove->getTo(), curPlayerPiece, opponentPiece, curFightWinner);
				this->player1Algorithm->notifyFightResult(curFightInfo);
				this->player2Algorithm->notifyFightResult(curFightInfo);
			}	
			else {
				GameFightInfo curFightInfo(curMove->getTo(), opponentPiece, curPlayerPiece, curFightWinner);
				this->player1Algorithm->notifyFightResult(curFightInfo);
				this->player2Algorithm->notifyFightResult(curFightInfo);
			}
			if (curFightWinner == curPlayer)
				this->gBoard->setGamePieceOnBoard(GamePiece(movingPieceType, curMove->getTo().getX(), curMove->getTo().getY(), movingPieceCurType, curPlayer), curPlayer);
			else if (curFightWinner == 0)
				this->gBoard->setGamePieceOnBoard(GamePiece('\0', curMove->getTo().getX(), curMove->getTo().getY(), '\0', 0), 0); //if both pieces tied, empty destination square
		}
		this->gBoard->setGamePieceOnBoard(GamePiece('\0', curMove->getFrom().getX(), curMove->getFrom().getY(), '\0', 0), 0); //empty source point of move
		if (checkIfPlayerHasNoFlags(this->getOtherPlayer(curPlayer))) {
			this->winner = curPlayer;
			this->reason = "All flags of the opponent are captured";
			return;
		}
		if (curPlayer == 1)
			curJokerChange = this->player1Algorithm->getJokerChange();
		else
			curJokerChange = this->player2Algorithm->getJokerChange();
		if (curJokerChange != nullptr) {
			if (!isLegalJokerChange(*(curJokerChange), curPlayer)) {
				this->reason = "Bad Joker Change input for player " + to_string(curPlayer);
				this->winner = this->getOtherPlayer(curPlayer);
				return;
			}
			this->gBoard->setGamePieceOnBoard(GamePiece('J', curJokerChange->getJokerChangePosition().getX(), curJokerChange->getJokerChangePosition().getY(), curJokerChange->getJokerNewRep(), curPlayer), curPlayer);
		}
		/*if (turnsWithoutFight >= 90) {
			this->createOutputFile();
		}*/
		//this->createOutputFile();
		//if (this->winner != 0)
		//	int b = 3;
	
		curPlayer = this->getOtherPlayer(curPlayer);
	}
	//exited while loop - 100 turns without fight
	this->reason = "A tie - " + to_string(MAX_TURNS_WITHOUT_FIGHT) + " turns without a fight";
	this->winner = 0;
}

void GameManager::createOutputFile() {
	char curLetter = '\0';
	ofstream fout;
	int col, row;
	fout.open("rps.output");
	if (fout.fail())
		cout << "Could not create output file" << endl;
	else {
		fout << "Winner: " << this->winner << endl;
		fout << "Reason: " << this->reason << endl;
		fout << endl;

		for (row = 1; row <= N; row++) {
			for (col = 1; col <= M; col++) {
				if (this->gBoard->getPlayer(MyPoint(col,row))!=0) {
					if (this->gBoard->getPlayer(MyPoint(col, row)) == 1)
						curLetter = this->gBoard->getGamePiece(MyPoint(col,row)).getPiece();
					else
						curLetter = tolower(this->gBoard->getGamePiece(MyPoint(col, row)).getPiece());
					fout << curLetter;
				}
				else
					fout << " ";
			}
			fout << endl;
		}
		fout.close();
	}
}