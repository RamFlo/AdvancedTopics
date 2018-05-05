#ifndef __FILE_PLAYER_PARSER_H_
#define __FILE_PLAYER_PARSER_H_

//--------------------------
// FilePlayerParser class
//--------------------------

// @authors Guy Keller, Ram Shimon TAU - Advanced Topics in Programming - 2018 Semester B

//--------------------------
#include <vector>
#include <memory>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include "PiecePosition.h"
#include "GamePiece.h"
#include "AllGameParameters.h"
#include "GameJokerChange.h"
#include "GameMove.h"

using std::unique_ptr;
using namespace std;
//--------------------------

class FilePlayerParser {
public:
	void parseInitialPositions(int player, std::vector<unique_ptr<PiecePosition>>& vectorToFill);
	void parseAllPlayerMoves(int player, std::vector<unique_ptr<Move>>& moveVectorToFill, std::vector<unique_ptr<JokerChange>>& jokerVectorToFill);
	//~FilePlayerParser() {}
};

#endif