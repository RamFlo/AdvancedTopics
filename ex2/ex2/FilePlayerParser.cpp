#include "FilePlayerParser.h"

//This function checks if a string represents a non-negative integer
bool isLegalNonNegativeNumber(string numString) {
	int i = 0, strSize = numString.length();
	for (i = 0; i < strSize; i++) {
		if (!isdigit(numString[i]))
			return false;
	}
	return true;
}

//checks if a string represents a legal column index
bool isLegalBoardCol(string colIndex) {
	return isLegalNonNegativeNumber(colIndex) && stoi(colIndex) > 0 && stoi(colIndex) <= M;
}
//checks if a string represents a legal row index
bool isLegalBoardRow(string rowIndex) {
	return isLegalNonNegativeNumber(rowIndex) && stoi(rowIndex) > 0 && stoi(rowIndex) <= N;
}

//checks if a string represents a legal piece char
bool isLegalPieceChar(char c) {
	switch (c)
	{
	case 'J':
	case 'R':
	case 'P':
	case 'S':
	case 'B':
	case 'F':
		return true;
		break;
	}
	return false;
}

//checks if a string represents a legal joker curType char (board pieces the joker can become)
bool isLegalJokerTypeChar(char c) {
	switch (c)
	{
	case 'R':
	case 'P':
	case 'S':
	case 'B':
		return true;
		break;
	}
	return false;
}

/*
returns whether or not a position command is valid.
*/
bool checkPositioningCommandVectorIsValid(vector<string>* myVec, int curLineNum, int player) {
	vector<string>& myCommandVec = *myVec;
	if (myCommandVec.size() > 4 || myCommandVec.size() < 3) {
		cout << "Bad format: input size inconsistent with given instructions for player " << player << " on line " << curLineNum << endl;
		return false;
	}
	if (myCommandVec[0].length() != 1 || (myCommandVec.size() == 4 && myCommandVec[3].length() != 1)) {
		cout << "Bad format: input size inconsistent with given instructions for player " << player << " on line " << curLineNum << endl;
		return false;
	}
	if (!isLegalPieceChar(myCommandVec[0][0])) {
		cout << "Bad format: illegal piece character for player " << player << " in line " << curLineNum << endl;
		return false;
	}
	if (!isLegalBoardCol(myCommandVec[1]) || !isLegalBoardRow(myCommandVec[2])) {
		cout << "Bad format: illegal index for player " << player << " on line " << curLineNum << endl;
		return false;
	}
	if (myCommandVec[0][0] == 'J') {
		if (myCommandVec.size() != 4) {
			cout << "Bad format: input size inconsistent with given instructions for player " << player << " on line " << curLineNum << endl;
			return false;
		}
		if (!isLegalJokerTypeChar(myCommandVec[3][0])) {
			cout << "Bad format: illegal piece character for Joker type for player " << player << " in line " << curLineNum << endl;
			return false;
		}
	}
	return true;
}

/*
parses string str into vector myVec (using spaces as delimiter)
*/
void parseStringIntoVector(vector<string>* myVec, string str) {
	string buf; // Have a buffer string
	stringstream ss(str); // Insert the string into a stream
	while (ss >> buf)
		myVec->push_back(buf);
}

/*bool isLegalJokerChangeCommandInVec(vector<string>* myVec, int curLineNum, int player) {
	vector<string> myCommandVec = *myVec;
}*/

/*
returns whether or not a move command is valid (including the joker change)
*/
bool isLegalMoveCommandVec(vector<string>* myVec) {
	vector<string> myCommandVec = *myVec;
	if (myCommandVec.size() != 4 && myCommandVec.size() != 8) {
		//cout << "Bad format: move command length is inconsistent with instructions by player " << player << " on line " << curLineNum << endl;
		return false;
	}
	if (!isLegalBoardRow(myCommandVec[1]) || !isLegalBoardRow(myCommandVec[3]) || !isLegalBoardCol(myCommandVec[0]) || !isLegalBoardCol(myCommandVec[2])) {
		//cout << "Bad format: illegal move index by player " << player << " on line " << curLineNum << endl;
		return false;
	}
	if (myCommandVec.size() == 8) {
		if (myCommandVec[4] != "J:") {
			//cout << "Bad format: illegal move command by player " << player << " on line " << curLineNum << endl;
			return false;
		}
		if (!isLegalBoardRow(myCommandVec[6]) || !isLegalBoardCol(myCommandVec[5])) {
			//cout << "Bad format: illegal move index by player " << player << " on line " << curLineNum << endl;
			return false;
		}
		if (!isLegalJokerTypeChar(myCommandVec[7][0])) {
			//cout << "Bad format: illegal move command joker type by player " << player << " on line " << curLineNum << endl;
			return false;
		}
	}
	return true;
}

void insertInvalidPositionIntoVector(std::vector<unique_ptr<PiecePosition>>& vectorToFill) {
	vectorToFill.push_back(make_unique<GamePiece>('\0', -1, -1, '\0',-1));
}

/*
fills PiecePosition vector with the player's piece positions according to the input file.
*/
void FilePlayerParser::parseInitialPositions(int player, std::vector<unique_ptr<PiecePosition>>& vectorToFill)
{
	string curLine, token, fileName = "player" + to_string(player) + ".rps_board";
	vector<string> myWordVec;
	int curLineNum = 0;
	ifstream fin(fileName);
	if (fin.fail()) { //checking if we could open the file
		insertInvalidPositionIntoVector(vectorToFill);
		return;
	}
	while (getline(fin, curLine)) { //returns false when reaching EOF
		if (fin.bad()) {
			fin.close();
			insertInvalidPositionIntoVector(vectorToFill);
			return;
		}
		myWordVec.clear();
		curLineNum++;
		parseStringIntoVector(&myWordVec, curLine);
		if (!checkPositioningCommandVectorIsValid(&myWordVec, curLineNum,player)){ //if current line is illegal, put an illegal position into the vector and return
			insertInvalidPositionIntoVector(vectorToFill);
			fin.close();
			return;
		}
		if (myWordVec.size()==3)
			vectorToFill.push_back(make_unique<GamePiece>(myWordVec[0][0],stoi(myWordVec[1]), stoi(myWordVec[2]),'#',player ));
		else
			vectorToFill.push_back(make_unique<GamePiece>(myWordVec[0][0], stoi(myWordVec[1]), stoi(myWordVec[2]), myWordVec[3][0],player));
	}
	fin.close();
	return;
}

void insertInvalidMoveIntoVector(std::vector<unique_ptr<Move>>& moveVectorToFill) {
	moveVectorToFill.push_back(make_unique<GameMove>(-1, -1, -1, -1));
}

void insertInvalidJokerIntoVector(std::vector<unique_ptr<JokerChange>>& jokerVectorToFill) {
	jokerVectorToFill.push_back(make_unique<GameJokerChange>(-1, -1, '\0'));
}

/*
fills Move vector with the player's moves according to the input file.
*/
void FilePlayerParser::parseAllPlayerMoves(int player, std::vector<unique_ptr<Move>>& moveVectorToFill, std::vector<unique_ptr<JokerChange>>& jokerVectorToFill) {
	string curLine, token, fileName = "player" + to_string(player) + ".rps_moves";
	vector<string> myWordVec;
	int curLineNum = 0;
	ifstream fin(fileName);
	if (fin.fail()) { //checking if we could open the file
		insertInvalidMoveIntoVector(moveVectorToFill);
		insertInvalidJokerIntoVector(jokerVectorToFill);
		return;
	}
	while (getline(fin, curLine)) { //returns false when reaching EOF
		if (fin.bad()) {
			fin.close();
			insertInvalidMoveIntoVector(moveVectorToFill);
			insertInvalidJokerIntoVector(jokerVectorToFill);
			return;
		}
		myWordVec.clear();
		curLineNum++;
		parseStringIntoVector(&myWordVec, curLine);
		if (!isLegalMoveCommandVec(&myWordVec)) { //if current line is illegal, put an illegal move into the vector and return
			insertInvalidMoveIntoVector(moveVectorToFill);
			insertInvalidJokerIntoVector(jokerVectorToFill);
			fin.close();
			return;
		}
		moveVectorToFill.push_back(make_unique<GameMove>(stoi(myWordVec[0]), stoi(myWordVec[1]), stoi(myWordVec[2]), stoi(myWordVec[3])));
		if (myWordVec.size() == 4)
			jokerVectorToFill.push_back(nullptr);
		else
			jokerVectorToFill.push_back(make_unique<GameJokerChange>(stoi(myWordVec[5]), stoi(myWordVec[6]), myWordVec[7][0]));
	}
	fin.close();
	return;
}