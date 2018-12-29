#include "snake.h"
#include <stdlib.h>
#include <time.h>
#include <SDL.h>
#include <Windows.h>

int main(int argc, char* args[]) {
	initialize();
	while (gamewithai());
	//MessageBox(NULL, "game over", "game over", MB_OK);
	SDL_Quit();
	return 0;
}