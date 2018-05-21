#include "FilePlayerAlgorithm.h"

FilePlayerAlgorithm::FilePlayerAlgorithm(int player)
{
	this->fillMovesAndJokerVectors(player);
}

/*
fills FilePlayer's moves and joker changes vector, using FilePlayerParser to parse input file.
*/
void FilePlayerAlgorithm::fillMovesAndJokerVectors(int player) {
	unique_ptr<FilePlayerParser> movesParser = make_unique<FilePlayerParser>();
	movesParser->parseAllPlayerMoves(player, this->movesVector, this->jokerChangeVector);
}

/*
fills FilePlayer's position vector using FilePlayerParser to parse the input position file.
*/
void FilePlayerAlgorithm::getInitialPositions(int player, std::vector<unique_ptr<PiecePosition>>& vectorToFill)
{
	unique_ptr<FilePlayerParser> commandParser = make_unique<FilePlayerParser>();
	commandParser->parseInitialPositions(player, vectorToFill);
}

/*
Does nothing.
*/
void FilePlayerAlgorithm::notifyOnInitialBoard(const Board & b, const std::vector<unique_ptr<FightInfo>>& fights) {
	UNUSED(b);
	UNUSED(fights);
}

/*
Does nothing.
*/
void FilePlayerAlgorithm::notifyOnOpponentMove(const Move & move) {
	UNUSED(move);
}

/*
Does nothing.
*/
void FilePlayerAlgorithm::notifyFightResult(const FightInfo & fightInfo) {
	UNUSED(fightInfo);
}

/*
returns the next move from the moves vector. If no such move exists, returns an illegal move.
*/
unique_ptr<Move> FilePlayerAlgorithm::getMove()
{
	if ((unsigned)curMoveNum < this->movesVector.size())
		return make_unique<GameMove>(this->movesVector[curMoveNum]->getFrom().getX(), this->movesVector[curMoveNum]->getFrom().getY(), this->movesVector[curMoveNum]->getTo().getX(), this->movesVector[curMoveNum]->getTo().getY());
	return make_unique<GameMove>(-1,-1,-1,-1);
}

/*
returns the next joker change from the joker changes vector. If no such joker change exists, returns nullptr.
*/
unique_ptr<JokerChange> FilePlayerAlgorithm::getJokerChange()
{
	int curJokerChangeNum = curMoveNum;
	this->curMoveNum++;
	if ((unsigned)curJokerChangeNum < this->jokerChangeVector.size() && this->jokerChangeVector[curJokerChangeNum]!=nullptr)
		return make_unique<GameJokerChange>(this->jokerChangeVector[curJokerChangeNum]->getJokerChangePosition().getX(), this->jokerChangeVector[curJokerChangeNum]->getJokerChangePosition().getY(), this->jokerChangeVector[curJokerChangeNum]->getJokerNewRep());
	return nullptr;
	
}
