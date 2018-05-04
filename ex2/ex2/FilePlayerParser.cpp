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

void parseStringIntoVector(vector<string>* myVec, string str) {
	string buf; // Have a buffer string
	stringstream ss(str); // Insert the string into a stream
	while (ss >> buf)
		myVec->push_back(buf);
}

void FilePlayerParser::parseInitialPositions(int player, std::vector<unique_ptr<PiecePosition>>& vectorToFill)
{
	string curLine, token, fileName = "player" + to_string(player) + ".rps_board";
	//GamePiece* curPiece = NULL;
	vector<string> myWordVec;
	int curLineNum = 0, curCol = 0, curRow = 0;
	ifstream fin(fileName);
	istringstream iss;
	if (fin.fail()) //checking if we could open the file
		return;
	while (getline(fin, curLine)) { //returns false when reaching EOF
		if (fin.bad()) {
			fin.close();
			return false;
		}
		myWordVec.clear();
		curLineNum++;
		parseStringIntoVector(&myWordVec, curLine);
		if (!checkPositioningCommandVectorIsValid(&myWordVec, curLineNum) || !handlePositioningLine(board, &myWordVec, curLineNum, player)) {
			handlePositioningError(board, player, curLineNum);
			fin.close();
			return true;
		}
	}
	if (!isEnoughFlags(board, player)) { //checking the player has enough flags (finished the while loop, positioning finished
		cout << "Bad format: missing flags - flags are not positioned according to their number " << endl;
		handlePositioningError(board, player, curLineNum);
		fin.close();
		return true;
	}
	fin.close();
	return true;
}
