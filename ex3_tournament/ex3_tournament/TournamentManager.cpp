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
	playersStats[id] = make_pair(0, 0);
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