#include <functional>
#include <memory>
#include <iostream>
#include <map>
#include <list> 
#include <vector>
#include <string> 
#include <dlfcn.h> 
#include <stdio.h> 
#include <unistd.h> 
#include <stdlib.h>
#include <string.h>
#include <thread>
#include <mutex> 
#include "GameManager.h"

#include "PlayerAlgorithm.h"

#ifndef __TOURNAMENT_MANAGER_H_
#define __TOURNAMENT_MANAGER_H_

#define BUF_SIZE 1024
#define NUM_OF_PLAYER_MATCHES 30

using namespace std;

class TournamentManager {
	static TournamentManager theTournamentManager;
	std::map<std::string, std::function<std::unique_ptr<PlayerAlgorithm>()>> id2factory;
	map<string, int> playersGames;
	map<string, int> playersPoints;
	list<void *> dl_list; // list to hold handles for dynamic libs 
	map<pair<string, string>, int> matchesCountMap;
	int numOfThreads;
	pair<string, string> chooseTwoPlayersForFightUntilEqualShare();
	string chooseFightingPartner(string firstPlayer, int numOfMatchesPerPlayer);
	pair<string, string> chooseTwoPlayersForFightAfterEqualShare();
	void threadFuncThatDoesFights();
	string choosePlayerWithMissingFights(int neededFights);
	void addPointsToPlayersAfterFight(int winner, string firstPlayer, string secondPlayer, int numOfFirstPlayerMatch, int numOfSecondPlayerMatch);
	mutex matchCountLock;
	mutex pointCountLock;
	// private ctor
	TournamentManager() {}
public:
	static TournamentManager& getTournamentManager();
	void registerAlgorithm(std::string id, std::function<std::unique_ptr<PlayerAlgorithm>()> factoryMethod);
	void run();
	bool getAllDLs(string path);
	void setNumOfThreads(int numOfT);
	void printScoreList();
};
#endif