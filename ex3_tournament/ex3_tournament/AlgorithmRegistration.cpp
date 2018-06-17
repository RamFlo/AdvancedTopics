#include "AlgorithmRegistration.h"
#include "TournamentManager_203537246.h"
//registers a new player algorithm
AlgorithmRegistration::AlgorithmRegistration(std::string id, std::function<std::unique_ptr<PlayerAlgorithm>()> factoryMethod)
{
	TournamentManager_203537246::getTournamentManager().registerAlgorithm(id, factoryMethod);
}
