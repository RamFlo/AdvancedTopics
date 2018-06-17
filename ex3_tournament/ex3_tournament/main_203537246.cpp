#include "TournamentManager_203537246.h"
#include <string>
#include <iostream>
using namespace std;


string path = ".";
int numOfThreads = 4;

int parseThreadsNum(const char* threadsNum) {
	size_t numOfConvertedChars = 0;
	int tNum;
	const string tNumString(threadsNum);
	tNum = stoi(tNumString, &numOfConvertedChars);
	if (numOfConvertedChars != tNumString.length() || tNum < 1)
		return -1;
	return tNum;
}

int parseForwards(const char* forward)
{
	if (strcmp(forward, "-threads") == 0)
		return 1;
	if (strcmp(forward, "-path") == 0)
		return 2;
	return -1;
}

bool parseArgumentsPair(const char* forward, const char* arg) {
	int forwardCheck = -1;
	forwardCheck = parseForwards(forward);
	if (forwardCheck == 1) {
		if ((numOfThreads = parseThreadsNum(arg)) == -1) {
			cout << "Bad number of threads supplied. Please enter a positive integer." << endl;
			return false;
		}
	}
	else if (forwardCheck == 2) {
		string s(arg);
		path = s;
	}
	else {
		cout << "valid optional arguments: -threads <num_threads> -path <location_of_algorithms>" << endl;
		return false;
	}
	return true;
}

int main(int argc, char* argv[])
{
	if (argc == 3) {
		if (!parseArgumentsPair(argv[1], argv[2]))
			return 0;
	}
	else if (argc == 5) {
		if (!parseArgumentsPair(argv[1], argv[2]) || !parseArgumentsPair(argv[3], argv[4]) || parseForwards(argv[1]) == parseForwards(argv[3]))
			return 0;
	}
	else if (argc != 1) {
		cout << "Invalid number of arguments supplied. valid optional arguments: -threads <num_threads> -path <location_of_algorithms>" << endl;
		return 0;
	}
	if (!TournamentManager_203537246::getTournamentManager().getAllDLs(path))
	{
		cout << "Invlid *.so files' path supplied." << endl;
		return 0;
	}
	TournamentManager_203537246::getTournamentManager().setNumOfThreads(numOfThreads);
	TournamentManager_203537246::getTournamentManager().run();
	TournamentManager_203537246::getTournamentManager().printScoreList();
	return 0;
}