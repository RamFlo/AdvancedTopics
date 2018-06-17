#include "TournamentManager_203537246.h"
#include "AlgorithmRegistration.h"
#include <algorithm>
#include <iostream>

TournamentManager_203537246 & TournamentManager_203537246::getTournamentManager()
{
	return theTournamentManager_203537246;
}
//registers a new algorithm, given its ID and PlayerAlgorithm
void TournamentManager_203537246::registerAlgorithm(std::string id, std::function<std::unique_ptr<PlayerAlgorithm>()> factoryMethod)
{
	if (playersGames.find(id) != playersGames.end())
	{
		cout << "ID number: " << id << " is already registered!" << endl;
		return;
	}
	id2factory[id] = factoryMethod;
	playersGames[id] = 0;
	playersPoints[id] = 0;
	for (auto& pair : id2factory) {
		string curPartnerName = pair.first;
		matchesCountMap[make_pair(id, curPartnerName)] = 0;
		matchesCountMap[make_pair(curPartnerName, id)] = 0;
	}

}

//Finds and returns a player that has not finished all of his fights
string TournamentManager_203537246::choosePlayerWithMissingFights(int neededFights) {
	//std::thread::id this_id = std::this_thread::get_id(); //remove line
	for (auto& pair : playersGames) {
		if (pair.second < neededFights)
			return pair.first;
	}
	return "";
}

//Given a player who still has missing fights, returns a fighting partner with whom he has fought less fights than he equally should
string TournamentManager_203537246::chooseFightingPartner(string firstPlayer, int numOfMatchesPerPlayer) {
	//std::thread::id this_id = std::this_thread::get_id(); //remove line
	string curPartnerName;
	for (auto& pair : playersGames) {
		curPartnerName = pair.first;
		if (matchesCountMap[make_pair(firstPlayer, curPartnerName)] < numOfMatchesPerPlayer && curPartnerName != firstPlayer)
			return curPartnerName;
	}
	return "";
}

//uses the two functions above to return two IDs, of the two players who should be the next fight in the tournament
pair<string, string> TournamentManager_203537246::chooseTwoPlayersForFight(bool beforeEqualShare) {
	int numOfPlayers = dl_list.size();
	int numOfMatchesPerPlayer = NUM_OF_PLAYER_MATCHES / (numOfPlayers - 1);
	string firstPlayer = beforeEqualShare ? (choosePlayerWithMissingFights(numOfMatchesPerPlayer * (numOfPlayers - 1))) : (choosePlayerWithMissingFights(NUM_OF_PLAYER_MATCHES));
	if (firstPlayer == "")
		return make_pair("", "");
	string secondPlayer = beforeEqualShare ? (chooseFightingPartner(firstPlayer, numOfMatchesPerPlayer)) : (chooseFightingPartner(firstPlayer, NUM_OF_PLAYER_MATCHES / (numOfPlayers - 1) + 1));
	if (secondPlayer == "") //should never happen
		return make_pair("", "");
	matchesCountMap[make_pair(firstPlayer, secondPlayer)]++;
	matchesCountMap[make_pair(secondPlayer, firstPlayer)]++;
	playersGames[firstPlayer]++;
	playersGames[secondPlayer]++;
	return make_pair(firstPlayer, secondPlayer);
}

//adds points to each player after a fight, according to the winner
void TournamentManager_203537246::addPointsToPlayersAfterFight(int winner, string firstPlayer, string secondPlayer, int numOfFirstPlayerMatch, int numOfSecondPlayerMatch) {
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

//Repeatedly chooses two players and conducts a fight between them, until there are no more fights to be held
void TournamentManager_203537246::doFights(bool beforeEqualShare) {
	pair<string, string> curFightPlayers;
	int winner;
	int numOfFirstPlayerMatch = 0;
	int numOfSecondPlayerMatch = 0;
	while (true) {
		matchCountLock.lock();
		curFightPlayers = chooseTwoPlayersForFight(beforeEqualShare);
		if (curFightPlayers.first == "") {
			matchCountLock.unlock();
			break;
		}
		numOfFirstPlayerMatch = playersGames[curFightPlayers.first];
		numOfFirstPlayerMatch = playersGames[curFightPlayers.second];
		matchCountLock.unlock();
		GameManager_203537246 gm((id2factory.find(curFightPlayers.first))->second(), (id2factory.find(curFightPlayers.second))->second());
		if (gm.initializeGameBoard()) {
			gm.playGame();
		}
		winner = gm.getWinner();
		pointCountLock.lock();
		addPointsToPlayersAfterFight(winner, curFightPlayers.first, curFightPlayers.second, numOfFirstPlayerMatch, numOfSecondPlayerMatch);
		pointCountLock.unlock();
	}
}

//conducts fights until all players fight the maximal equal number of fights against each other.
//Then, completes each players fight quota against other players.
void TournamentManager_203537246::threadFuncThatDoesFights() {
	doFights(true);
	doFights(false);
}

//runs the tournament
void TournamentManager_203537246::run()
{
	int i = 0;
	list<void *>::iterator dl_itr;
	vector<thread> allThreadsVec;
	for (i = 0; i < numOfThreads - 1; i++)
		allThreadsVec.emplace_back(&TournamentManager_203537246::threadFuncThatDoesFights, this);
	threadFuncThatDoesFights();
	for (auto& t : allThreadsVec)
		t.join();

	id2factory.clear();
	for (dl_itr = dl_list.begin(); dl_itr != dl_list.end(); dl_itr++)
		dlclose(*dl_itr);
}

//gets all the dls, and by doing so gets all the player algorithms
bool TournamentManager_203537246::getAllDLs(string path)
{
	FILE *dl;   // handle to read directory 
	string cmd_str = "ls " + path + "/*.so";
	const char *command_str = cmd_str.c_str();  // command string to get dynamic lib names
	char in_buf[BUF_SIZE];
	char curDLName[BUF_SIZE]; //name of the current dl
	void *dlib;
	dl = popen(command_str, "r");
	if (!dl) {
		pclose(dl);
		return false;
	}
		
	while (fgets(in_buf, BUF_SIZE, dl)) {
		// trim off the whitespace 
		char *ws = strpbrk(in_buf, " \t\n");
		if (ws) *ws = '\0';
		// append ./ to the front of the lib name
		sprintf(curDLName, "%s", in_buf);
		dlib = dlopen(curDLName, RTLD_NOW);
		if (dlib == NULL) {
			cerr << dlerror() << endl;
			pclose(dl);
			exit(-1);
		}
		// add the handle to our list
		dl_list.insert(dl_list.end(), dlib);
	}
	if (dl_list.size() == 0)
	{
		cout << "no *.so files found." << endl;
		pclose(dl);
		return false;
	}
	pclose(dl);
	return true;
}

//sets the num of thread
void TournamentManager_203537246::setNumOfThreads(int numOfT)
{
	numOfThreads = numOfT;
}

//compares the amount of points two players have
bool compareTwoPlayersScores(pair<string, int> p1Pair, pair<string, int> p2Pair) {
	return (p1Pair.second > p2Pair.second);
}

//prints the list of players from most points won to least points won
void TournamentManager_203537246::printScoreList() {
	int i = 0;
	vector<pair<string, int>> scoresVec;
	for (auto& pair : playersPoints)
		scoresVec.push_back(pair);
	sort(scoresVec.begin(), scoresVec.end(), compareTwoPlayersScores);
	for (i = 0; i < (int)scoresVec.size(); i++)
		cout << scoresVec[i].first << " " << scoresVec[i].second << endl;
	
	//extended print
	//cout << endl << "playersGames:" << endl;
	//for (auto& pair : playersGames)
	//	cout << "Player: "<< pair.first << ", Games: " << pair.second << endl;

	//cout << endl << "matchesCountMap:" << endl;
	//for(auto& pair: matchesCountMap)
	//	cout << "First Player: " << pair.first.first << ", Second Player: " << pair.first.second << ", Matches: " << pair.second << endl;
	//extended print
}


//define the static variable
TournamentManager_203537246 TournamentManager_203537246::theTournamentManager_203537246;