#ifndef __RSPPLAYER_204573356_H_
#define __RSPPLAYER_204573356_H_

//--------------------------
// RSPPlayer_204573356 class
//--------------------------

// @authors Guy Keller, Ram Shimon TAU - Advanced Topics in Programming - 2018 Semester B

//--------------------------
#include "PlayerAlgorithm.h"
#include "AllGameParameters.h"
#include "GameBoard_204573356.h"
#include "GameMove_204573356.h"
#include <map>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <random>
using namespace std;
//--------------------------

class RSPPlayer_204573356 :public PlayerAlgorithm {
	int player;
	unique_ptr<GameBoard_204573356> knowBoard;
	map<string, int> myPieceCount;
	bool isAutoPlayerSquareEmpty(const Point & piecePos);
	char checkPiecesPositioned();
	void updateMyPieceCount(char pieceType, int incOrDec);
	void findNearbyBeatablePiece(const Point & myPiecePosition, MyPoint_204573356& pointToFill);
	bool isMoveablePiece(const Point & myPiecePosition);
	void findLegalMove(const Point & myPiecePosition, MyPoint_204573356 & pointToFill);
public:
	RSPPlayer_204573356();
	void getInitialPositions(int player, std::vector<unique_ptr<PiecePosition>>& vectorToFill) override;
	void notifyOnInitialBoard(const Board& b, const std::vector<unique_ptr<FightInfo>>& fights) override;
	void notifyOnOpponentMove(const Move& move) override; // called only on opponent’s move
	void notifyFightResult(const FightInfo& fightInfo) override; // called only if there was a fight
	bool doesPiece1BeatPiece2(char p1, char p2);
	unique_ptr<Move> getMove() override;
	unique_ptr<JokerChange> getJokerChange() override; // nullptr if no change is requested
	~RSPPlayer_204573356() {}
};

#endif