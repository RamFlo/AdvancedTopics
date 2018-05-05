#include "GameManager.h"

int main() {
	int i = 0;
	GameManager gm("file-vs-file");
	if (gm.initializeGameBoard())
		i = 1;
}