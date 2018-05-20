#include "GameManager.h"

int main() {
	int i = 0;
	GameManager gm("file-vs-file");
	srand(time(NULL));
	if (!gm.initializeGameBoard()) {
		gm.createOutputFile();
		return 0;
	}
	gm.playGame();
	gm.createOutputFile();
	return 0;
}