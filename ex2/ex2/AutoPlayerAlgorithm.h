#ifndef __AUTO_PLAYER_ALGORITHM_H_
#define __AUTO_PLAYER_ALGORITHM_H_

//--------------------------
// AutoPlayerAlgorithm class
//--------------------------

// @authors Guy Keller, Ram Shimon TAU - Advanced Topics in Programming - 2018 Semester B

//--------------------------
#include "PlayerAlgorithm.h"
#include "AllGameParameters.h"
#include "GameBoard.h"
#include "GameMove.h"
#include <map>
#include <cstdlib>
#include <ctime>
using namespace std;
//--------------------------

class AutoPlayerAlgorithm :public PlayerAlgorithm {
	int player;
	unique_ptr<GameBoard> knowBoard;
	map<string, int> myPieceCount;
	bool isAutoPlayerSquareEmpty(const Point & piecePos);
	char checkPiecesPositioned();
	void updateMyPieceCount(char pieceType, int incOrDec);
	void findNearbyBeatablePiece(const Point & myPiecePosition, MyPoint& pointToFill);
	bool isMoveablePiece(const Point & myPiecePosition);
	void findLegalMove(const Point & myPiecePosition, MyPoint & pointToFill);
public:
	AutoPlayerAlgorithm(int player);
	void getInitialPositions(int player, std::vector<unique_ptr<PiecePosition>>& vectorToFill) override;
	void notifyOnInitialBoard(const Board& b, const std::vector<unique_ptr<FightInfo>>& fights) override;
	void notifyOnOpponentMove(const Move& move) override; // called only on opponent’s move
	void notifyFightResult(const FightInfo& fightInfo) override; // called only if there was a fight
	bool doesPiece1BeatPiece2(char p1, char p2);
	unique_ptr<Move> getMove() override;
	unique_ptr<JokerChange> getJokerChange() override; // nullptr if no change is requested
	~AutoPlayerAlgorithm() {}
};

#endif