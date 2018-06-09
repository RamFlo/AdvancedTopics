#include "TournamentManager.h"
#include "AlgorithmRegistration.h"
#include <algorithm>
#include <iostream>

TournamentManager & TournamentManager::getTournamentManager()
{
	return theTournamentManager;
}

void TournamentManager::registerAlgorithm(std::string id, std::function<std::unique_ptr<PlayerAlgorithm>()> factoryMethod)
{
	// TODO: should warn if id is already registered
	id2factory[id] = factoryMethod;
	playersGames[id] = 0;
	playersPoints[id] = 0;
	for (auto& pair : id2factory) {
		string curPartnerName = pair.first;
		matchesCountMap[make_pair(id, curPartnerName)] = 0;
		matchesCountMap[make_pair(curPartnerName, id)] = 0;
	}

}

string TournamentManager::choosePlayerWithMissingFights(int neededFights) {
	for (auto& pair : id2factory) {
		string curPlayerName = pair.first;
		if (playersGames[curPlayerName] < neededFights)
			return curPlayerName;
	}
	return "";
}

string TournamentManager::chooseFightingPartner(string firstPlayer, int numOfMatchesPerPlayer) {
	for (auto& pair : id2factory) {
		string curPartnerName = pair.first;
		if (matchesCountMap[make_pair(firstPlayer, curPartnerName)] < numOfMatchesPerPlayer && curPartnerName != firstPlayer)
			return curPartnerName;
	}
	return "";
}

pair<string, string> TournamentManager::chooseTwoPlayersForFightUntilEqualShare() {
	int numOfPlayers = dl_list.size();
	int numOfMatchesPerPlayer = NUM_OF_PLAYER_MATCHES / (numOfPlayers - 1);
	string firstPlayer = choosePlayerWithMissingFights(numOfMatchesPerPlayer * numOfPlayers);
	if (firstPlayer == "") 
		return make_pair("", "");
	string secondPlayer = chooseFightingPartner(firstPlayer, numOfMatchesPerPlayer);
	if (secondPlayer == "") //should never happen
		return make_pair("", "");
	matchesCountMap[make_pair(firstPlayer, secondPlayer)]++;
	matchesCountMap[make_pair(secondPlayer, firstPlayer)]++;
	playersGames[firstPlayer]++;
	playersGames[secondPlayer]++;
	return make_pair(firstPlayer, secondPlayer);
}

pair<string, string> TournamentManager::chooseTwoPlayersForFightAfterEqualShare() {
	int numOfPlayers = dl_list.size();
	string firstPlayer = choosePlayerWithMissingFights(NUM_OF_PLAYER_MATCHES);
	if (firstPlayer == "")
		return make_pair("", "");
	string secondPlayer = chooseFightingPartner(firstPlayer, NUM_OF_PLAYER_MATCHES / (numOfPlayers - 1) + 1);
	if (secondPlayer == "") //should never happen
		return make_pair("", "");
	matchesCountMap[make_pair(firstPlayer, secondPlayer)]++;
	matchesCountMap[make_pair(secondPlayer, firstPlayer)]++;
	playersGames[firstPlayer]++;
	playersGames[secondPlayer]++;
	return make_pair(firstPlayer, secondPlayer);
}

void TournamentManager::addPointsToPlayersAfterFight(int winner, string firstPlayer, string secondPlayer, int numOfFirstPlayerMatch, int numOfSecondPlayerMatch) {
	int player1Doubler = numOfFirstPlayerMatch <= 30 ? 1 : 0;
	int player2Doubler = numOfSecondPlayerMatch <= 30 ? 1 : 0;
	if (winner == 0) {
		playersPoints[firstPlayer] += player1Doubler * 1;
		playersPoints[secondPlayer] += player2Doubler * 1;
	}
	else if (winner == 1)
		playersPoints[firstPlayer] += player1Doubler * 3;
	else
		playersPoints[secondPlayer] += player2Doubler * 3;
}

void TournamentManager::threadFuncThatDoesFights() {
	pair<string, string> curFightPlayers;
	std::thread::id this_id = std::this_thread::get_id(); //remove line
	int winner;
	int numOfFirstPlayerMatch = 0;
	int numOfSecondPlayerMatch = 0;
	cout << "thread: "<< this_id << " threadFuncThatDoesFights() print 0" << endl;
	while (true) {
		cout << "thread: " << this_id << " threadFuncThatDoesFights() print 1" << endl;
		matchCountLock.lock();
		cout << "thread: " << this_id << " threadFuncThatDoesFights() print 2" << endl;
		curFightPlayers = chooseTwoPlayersForFightUntilEqualShare();
		cout << "thread: " << this_id << " threadFuncThatDoesFights() print 3" << endl;
		if (curFightPlayers.first == "") {
			matchCountLock.unlock();
			break;
		}
		numOfFirstPlayerMatch = playersGames[curFightPlayers.first];
		numOfFirstPlayerMatch = playersGames[curFightPlayers.second];
		cout << "thread: " << this_id << " threadFuncThatDoesFights() print 4" << endl;
		matchCountLock.unlock();
		GameManager gm((id2factory.find(curFightPlayers.first))->second(), (id2factory.find(curFightPlayers.second))->second());
		cout << "thread: " << this_id << " threadFuncThatDoesFights() print 5" << endl;
		if (gm.initializeGameBoard()) {
			gm.playGame();
		}
		cout << "thread: " << this_id << " threadFuncThatDoesFights() print 6" << endl;
		winner = gm.getWinner();
		pointCountLock.lock();
		cout << "thread: " << this_id << " threadFuncThatDoesFights() print 7" << endl;
		addPointsToPlayersAfterFight(winner, curFightPlayers.first, curFightPlayers.second, numOfFirstPlayerMatch, numOfSecondPlayerMatch);
		cout << "thread: " << this_id << " threadFuncThatDoesFights() print 8" << endl;
		pointCountLock.unlock();
		cout << "thread: " << this_id << " threadFuncThatDoesFights() print 9" << endl << endl;
	}
	cout << "thread: " << this_id << " finished! " << endl;
}

void TournamentManager::run()
{
	int i = 0;
	list<void *>::iterator dl_itr;
	vector<thread> allThreadsVec;
	cout << "run 1" << endl;
	for (i = 0; i < numOfThreads - 1; i++)
		allThreadsVec.emplace_back(&TournamentManager::threadFuncThatDoesFights, this);
	cout << "run 2" << endl;
	threadFuncThatDoesFights();
	cout << "run 3" << endl;
	for (auto& t : allThreadsVec) {
		cout << "run 4" << endl;
		t.join();
		cout << "run 5" << endl;
	}

	//for (unsigned int j = 0; j<allThreadsVec.size(); ++j)
	//{
	//	cout << "run 4" << endl;
	//	if (allThreadsVec[j].joinable())
	//		allThreadsVec.at(j).join();
	//	cout << "run 5" << endl;
	//}
	
	cout << "run 6" << endl;
	id2factory.clear();
	for (dl_itr = dl_list.begin(); dl_itr != dl_list.end(); dl_itr++)
		dlclose(*dl_itr);
}

bool TournamentManager::getAllDLs(string path)
{
	FILE *dl;   // handle to read directory 
	const char *command_str = ("ls "+path+"/*.so").c_str();  // command string to get dynamic lib names
	char in_buf[BUF_SIZE];
	char curDLName[BUF_SIZE]; //name of the current dl
	void *dlib;
	dl = popen(command_str, "r");
	if (!dl)
		return false;
	while (fgets(in_buf, BUF_SIZE, dl)) {
		// trim off the whitespace 
		char *ws = strpbrk(in_buf, " \t\n");
		if (ws) *ws = '\0';
		// append ./ to the front of the lib name
		sprintf(curDLName, "./%s", in_buf);
		dlib = dlopen(curDLName, RTLD_NOW);
		if (dlib == NULL) {
			cerr << dlerror() << endl;
			exit(-1);
		}
		// add the handle to our list
		dl_list.insert(dl_list.end(), dlib);
	}
	if (dl_list.size() == 0)
		return false;
	return true;
}

void TournamentManager::setNumOfThreads(int numOfT)
{
	numOfThreads = numOfT;
}

bool compareTwoPlayersScores(pair<string, int> p1Pair, pair<string, int> p2Pair) {
	return (p1Pair.second > p2Pair.second);
}

void TournamentManager::printScoreList() {
	int i = 0;
	vector<pair<string, int>> scoresVec;
	for (auto& pair : playersPoints)
		scoresVec.push_back(pair);
	sort(scoresVec.begin(), scoresVec.end(), compareTwoPlayersScores);
	for (i = 0; i < (int)scoresVec.size(); i++)
		cout << scoresVec[i].first << " " << scoresVec[i].second << endl;
	

	//extended print
	cout << endl << "playersGames:" << endl;
	for (auto& pair : playersGames)
		cout << "Player: "<< pair.first << ", Games: " << pair.second << endl;

	cout << endl << "matchesCountMap:" << endl;
	for(auto& pair: matchesCountMap)
		cout << "First Player: " << pair.first.first << ", Second Player: " << pair.first.second << ", Matches: " << pair.second << endl;
	//extended print
}


//define the static variable
TournamentManager TournamentManager::theTournamentManager;