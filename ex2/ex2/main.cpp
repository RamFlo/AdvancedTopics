#include "GameManager.h"

/*
The game's main function. Initialized the game manager according to the supplied argument and commences the game. Finallly, prints the game's output.
*/
int main(int argc, char* argv[]) {
	if (argc < 2 || (string(argv[1]) != "auto-vs-file" && string(argv[1]) != "file-vs-auto" && string(argv[1]) != "auto-vs-auto" && string(argv[1]) != "file-vs-file")) {
		cout << "Please call this program with one of the following arguments: auto-vs-file, file-vs-auto, auto-vs-auto, file-vs-file" << endl;
		return 0;
	}
	GameManager gm(argv[1]);
	srand(time(NULL));
	if (!gm.initializeGameBoard()) {
		gm.createOutputFile();
		return 0;
	}
	gm.playGame();
	gm.createOutputFile();
	return 0;
}