#ifndef __GAME_MANAGER_H_
#define __GAME_MANAGER_H_

//--------------------------
// GameManager Class
//--------------------------

// @author Amir Kirsh, TAU - Advanced Topics in Programming - 2018 Semester B

//--------------------------
#include <memory>
#include <string>
#include <vector>
#include "PlayerAlgorithm.h"
#include "FilePlayerAlgorithm.h"
#include "GameBoard.h"
#include "GameFightInfo.h"

//--------------------------
#include <map>
#include <string>
using namespace std;
//--------------------------
class GameManager {
	unique_ptr<PlayerAlgorithm> player1Algorithm, player2Algorithm;
	unique_ptr<GameBoard> gBoard,p1InitialBoard, p2InitialBoard;
	bool isPlayerSquareEmptyDuringPositioning(int player, const Point & piecePos);
	bool handlePositioningLine(PiecePosition & curPiece, int player);
	bool isEnoughFlags(int player);
	bool initializeBoardFromPositionsVector(vector<unique_ptr<PiecePosition>>& playerPositions, int player);
	bool updatePieceCount(int player, PiecePosition & curPiece, int incOrDec);
	string reason;
	int winner;
	void fight(vector<unique_ptr<FightInfo>>& fightsVecToFill, Point& pos);
	void mergeTwoBoards(vector<unique_ptr<FightInfo>>& fightsVecToFill);
	map<string, int> pieceCountMap;
public:
	GameManager(string gameMode);
	bool initializeGameBoard();
	~GameManager() {}
};

#endif