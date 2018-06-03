#include "TournamentManager.h"
#include "AlgorithmRegistration.h"

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
	int numOfMatchesPerPlayer = NUM_OF_PLAYER_MATCHES / numOfPlayers;
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
	string secondPlayer = chooseFightingPartner(firstPlayer, NUM_OF_PLAYER_MATCHES / numOfPlayers + 1);
	if (secondPlayer == "") //should never happen
		return make_pair("", "");
	matchesCountMap[make_pair(firstPlayer, secondPlayer)]++;
	matchesCountMap[make_pair(secondPlayer, firstPlayer)]++;
	playersGames[firstPlayer]++;
	playersGames[secondPlayer]++;
	return make_pair(firstPlayer, secondPlayer);
}

void TournamentManager::addPointsToPlayersAfterFight(int winner, string firstPlayer, string secondPlayer, int numOfFirstPlayerMatch, int numOfSecondPlayerMatch) {
	if (winner == 0) {
		if ()
		playersPoints[firstPlayer]++;
		playersPoints[secondPlayer]++;
	}
}

void TournamentManager::threadFuncThatDoesFights() {
	pair<string, string> curFightPlayers;
	int winner;
	int numOfFirstPlayerMatch = 0;
	int numOfSecondPlayerMatch = 0;
	while (true) {
		matchCountLock.lock();
		curFightPlayers = chooseTwoPlayersForFightUntilEqualShare();
		if (curFightPlayers.first == "") {
			matchCountLock.unlock();
			break;
		}
		numOfFirstPlayerMatch = playersGames[curFightPlayers.first];
		numOfFirstPlayerMatch = playersGames[curFightPlayers.second];
		matchCountLock.unlock();
		GameManager gm((id2factory.find(curFightPlayers.first))->second(), (id2factory.find(curFightPlayers.second))->second());
		if (gm.initializeGameBoard()) {
			gm.playGame();
		}
		winner = gm.getWinner();
		pointCountLock.lock();
	}

}

void TournamentManager::run() const
{
	//unique_ptr<PlayerAlgorithm> p3 = (id2factory.find("3"))->second();

/*
	for (auto& pair : id2factory) {
		const auto& id = pair.first;
		std::cout << id << ": ";
		const auto& factoryMethod = pair.second;
		factoryMethod()->foo();
	}*/
	
}

void TournamentManager::getAllDLs(string path)
{
	FILE *dl;   // handle to read directory 
	const char *command_str = ("ls "+path+"/*.so").c_str();  // command string to get dynamic lib names
	char in_buf[BUF_SIZE];
	char curDLName[BUF_SIZE]; //name of the current dl
	void *dlib;
	dl = popen(command_str, "r");
	if (!dl) {
		perror("popen");
		exit(-1);
	}
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
}


//define the static variable
TournamentManager TournamentManager::theTournamentManager;