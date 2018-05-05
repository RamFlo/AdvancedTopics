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
	//unique_ptr<FilePlayerParser> moveParser = make_unique<FilePlayerParser>();
	return unique_ptr<Move>();
}

unique_ptr<JokerChange> FilePlayerAlgorithm::getJokerChange()
{
	return unique_ptr<JokerChange>();
}
