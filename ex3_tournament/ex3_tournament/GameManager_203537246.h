#ifndef __GAME_MANAGER_203537246_H_
#define __GAME_MANAGER_203537246_H_

//--------------------------
// GameManager Class
//--------------------------

// @author Amir Kirsh, TAU - Advanced Topics in Programming - 2018 Semester B

//--------------------------
#include <memory>
#include <string>
#include <vector>
#include "PlayerAlgorithm.h"
#include "GameBoard_203537246.h"
#include "GameFightInfo_203537246.h"

//--------------------------
// GameManager class
//--------------------------

// @authors Guy Keller, Ram Shimon TAU - Advanced Topics in Programming - 2018 Semester B

//--------------------------
#include <map>
#include <string>
using namespace std;
//--------------------------
class GameManager_203537246 {
	unique_ptr<PlayerAlgorithm> player1Algorithm, player2Algorithm;
	unique_ptr<GameBoard_203537246> gBoard,p1InitialBoard, p2InitialBoard;
	bool isPlayerSquareEmptyDuringPositioning(int player, const Point & piecePos);
	bool handlePositioningLine(PiecePosition & curPiece, int player);
	bool isEnoughFlags(int player);
	bool initializeBoardFromPositionsVector(vector<unique_ptr<PiecePosition>>& playerPositions, int player);
	int fightBetweenTwoPiecesAndUpdatePieceCount(char p1Piece, char p2Piece, char p1ActualPiece, char p2ActualPiece);
	bool updatePieceCount(int player, char curPiece, int incOrDec);
	string reason;
	int winner;
	void fight(vector<unique_ptr<FightInfo>>& fightsVecToFill, Point& pos);
	void mergeTwoBoards(vector<unique_ptr<FightInfo>>& fightsVecToFill);
	bool checkWinnerAccordingToFlags();
	bool isThereLegalMove(const Point & myPiecePosition);
	bool playerHasLegalMove(int player);
	int getOtherPlayer(int player);
	bool isMovingPiece(const GamePiece_203537246 & piece);
	bool isLegalMove(int player, const Point & fromPoint, const Point & toPoint);
	bool checkIfPlayerHasNoFlags(int player);
	bool isLegalJokerChange(const JokerChange & curJokerChange, int player);
	map<string, int> pieceCountMap;
public:
	GameManager_203537246(unique_ptr<PlayerAlgorithm> p1, unique_ptr<PlayerAlgorithm> p2);
	bool initializeGameBoard();
	void playGame();
	int getWinner();
	//void createOutputFile();
	//~GameManager() {}
};

#endif