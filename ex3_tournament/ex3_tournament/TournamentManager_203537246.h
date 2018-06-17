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
#include "GameManager_203537246.h"

#include "PlayerAlgorithm.h"

#ifndef __TOURNAMENT_MANAGER_H_
#define __TOURNAMENT_MANAGER_H_

#define BUF_SIZE 1024
#define NUM_OF_PLAYER_MATCHES 30

using namespace std;

class TournamentManager_203537246 {
	static TournamentManager_203537246 theTournamentManager_203537246;
	std::map<std::string, std::function<std::unique_ptr<PlayerAlgorithm>()>> id2factory;
	map<string, int> playersGames;
	map<string, int> playersPoints;
	list<void *> dl_list; // list to hold handles for dynamic libs 
	map<pair<string, string>, int> matchesCountMap;
	int numOfThreads;
	string chooseFightingPartner(string firstPlayer, int numOfMatchesPerPlayer);
	pair<string, string> chooseTwoPlayersForFight(bool beforeEqualShare);
	void threadFuncThatDoesFights();
	string choosePlayerWithMissingFights(int neededFights);
	void addPointsToPlayersAfterFight(int winner, string firstPlayer, string secondPlayer, int numOfFirstPlayerMatch, int numOfSecondPlayerMatch);
	void doFights(bool beforeEqualShare);
	mutex matchCountLock;
	mutex pointCountLock;
	// private ctor
	TournamentManager_203537246() {}
public:
	static TournamentManager_203537246& getTournamentManager();
	void registerAlgorithm(std::string id, std::function<std::unique_ptr<PlayerAlgorithm>()> factoryMethod);
	void run();
	bool getAllDLs(string path);
	void setNumOfThreads(int numOfT);
	void printScoreList();
};
#endif