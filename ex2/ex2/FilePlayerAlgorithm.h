#ifndef __FILE_PLAYER_ALGORITHM_H_
#define __FILE_PLAYER_ALGORITHM_H_

//--------------------------
// FilePlayerAlgorithm class
//--------------------------

// @authors Guy Keller, Ram Shimon TAU - Advanced Topics in Programming - 2018 Semester B

//--------------------------
#include "PlayerAlgorithm.h"
#include "FilePlayerParser.h"

using namespace std;
//--------------------------

class FilePlayerAlgorithm:public PlayerAlgorithm {
	vector<unique_ptr<Move>> movesVector;
	vector<unique_ptr<JokerChange>> jokerChangeVector;
	void fillMovesAndJokerVectors(int player);
public:
	FilePlayerAlgorithm(int player);
	void getInitialPositions(int player, std::vector<unique_ptr<PiecePosition>>& vectorToFill) override;
	void notifyOnInitialBoard(const Board& b, const std::vector<unique_ptr<FightInfo>>& fights) override;
	void notifyOnOpponentMove(const Move& move) override; // called only on opponent’s move
	void notifyFightResult(const FightInfo& fightInfo) override; // called only if there was a fight
	unique_ptr<Move> getMove() override;
	unique_ptr<JokerChange> getJokerChange() override; // nullptr if no change is requested
	~FilePlayerAlgorithm() {}
};

#endif