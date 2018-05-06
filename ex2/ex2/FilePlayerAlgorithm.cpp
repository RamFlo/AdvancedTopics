#include "FilePlayerAlgorithm.h"

FilePlayerAlgorithm::FilePlayerAlgorithm(int player)
{
	this->fillMovesAndJokerVectors(player);
}

void FilePlayerAlgorithm::fillMovesAndJokerVectors(int player) {
	unique_ptr<FilePlayerParser> movesParser = make_unique<FilePlayerParser>();
	movesParser->parseAllPlayerMoves(player, this->movesVector, this->jokerChangeVector);
}

void FilePlayerAlgorithm::getInitialPositions(int player, std::vector<unique_ptr<PiecePosition>>& vectorToFill)
{
	unique_ptr<FilePlayerParser> commandParser = make_unique<FilePlayerParser>();
	commandParser->parseInitialPositions(player, vectorToFill);
}

void FilePlayerAlgorithm::notifyOnInitialBoard(const Board & b, const std::vector<unique_ptr<FightInfo>>& fights) {} //Empty

void FilePlayerAlgorithm::notifyOnOpponentMove(const Move & move) {} //Empty

void FilePlayerAlgorithm::notifyFightResult(const FightInfo & fightInfo) {} //Empty

unique_ptr<Move> FilePlayerAlgorithm::getMove()
{
	if (curMoveNum < this->movesVector.size())
		return make_unique<GameMove>(this->movesVector[curMoveNum]->getFrom().getX(), this->movesVector[curMoveNum]->getFrom().getY(), this->movesVector[curMoveNum]->getTo().getX(), this->movesVector[curMoveNum]->getTo().getY());
	return make_unique<GameMove>(-1,-1,-1,-1);
}

unique_ptr<JokerChange> FilePlayerAlgorithm::getJokerChange()
{
	int curJokerChangeNum = curMoveNum;
	this->curMoveNum++;
	if (curJokerChangeNum < this->jokerChangeVector.size() && this->jokerChangeVector[curJokerChangeNum]!=nullptr)
		return make_unique<GameJokerChange>(this->jokerChangeVector[curJokerChangeNum]->getJokerChangePosition().getX(), this->jokerChangeVector[curJokerChangeNum]->getJokerChangePosition().getY(), this->jokerChangeVector[curJokerChangeNum]->getJokerNewRep());
	return nullptr;
	
}
