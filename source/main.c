/**
 * @file main.c
 * @author starstory (czstara12@gmail.com)
 * @brief 包含主函数
 * @version 0.1
 * @date 2023-11-18
 *
 * @copyright MIT 2023
 *
 */
#include "main.h"

/**
 * @brief 主函数
 *
 * @param argc
 * @param args
 * @return int
 */
int main(int argc, char *args[])
{
	gameInfo game = {0};
	drawClass window = {0};
	drawInit(&window);
	gameInit(&game);
	while (1)
	{
		if (clock() - game.lastLoopTime > CLOCKS_PER_SEC * 1 / 100) ///< 1S
		{
			game.lastLoopTime = clock();
			gameLoop(&game);
			SDL_GameDisplay(&window, &game);

			plan(&game);
			if (game.headDirection == 0)
			{
				while (1)
				{
					SDL_GameDisplay(&window, &game);
					SDL_GameEvent(&window, &game);
				}
			}
		}
		SDL_GameEvent(&window, &game);
	}
	// MessageBoxA(NULL, "game over", "game over", MB_OK);
	SDL_Quit();
	return 0;
}
