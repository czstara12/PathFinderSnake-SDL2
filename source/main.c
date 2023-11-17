#include "snake.h"
#include <Windows.h>
#include <SDL.h>

int main(int argc, char *args[])
{
	initialize();
	while (gamewithai())
		;
	MessageBoxA(NULL, "game over", "game over", MB_OK);
	SDL_Quit();
	return 0;
}