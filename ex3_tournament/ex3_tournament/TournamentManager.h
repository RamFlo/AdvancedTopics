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

#include "PlayerAlgorithm.h"

#ifndef __TOURNAMENT_MANAGER_H_
#define __TOURNAMENT_MANAGER_H_

#define BUF_SIZE 1024

using namespace std;

class TournamentManager {
	static TournamentManager theTournamentManager;
	std::map<std::string, std::function<std::unique_ptr<PlayerAlgorithm>()>> id2factory;
	map<string, pair<int, int>> playersStats; //pair: #player's games, #player's points
	list<void *> dl_list; // list to hold handles for dynamic libs 
	// private ctor
	TournamentManager() {}
public:
	static TournamentManager& getTournamentManager();
	void registerAlgorithm(std::string id, std::function<std::unique_ptr<PlayerAlgorithm>()> factoryMethod);
	void run() const;
	void getAllDLs(string path);
};
#endif