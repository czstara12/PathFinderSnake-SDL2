#include "snake.h"
#include <stdlib.h>
#include <time.h>
#include <SDL.h>

int main(int argc, char* args[]) {
	initialize();
	while (game());
	SDL_Quit();
	return 0;
}