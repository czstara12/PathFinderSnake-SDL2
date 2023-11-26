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
	struct gameInfo game = {0};
	drawClass window = {0};
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);																																 // 初始化SDL
	window.window = SDL_CreateWindow("snake.by starstory", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH * PIXELPERUNIT, HEIGHT * PIXELPERUNIT, SDL_WINDOW_SHOWN); // 创建SDL窗口
	window.renderer = SDL_CreateRenderer(window.window, -1, SDL_RENDERER_ACCELERATED);																						 // 刷子绑定窗口
	SDL_SetRenderDrawColor(window.renderer, 255, 255, 255, 255);
	SDL_RenderClear(window.renderer);
	SDL_RenderPresent(window.renderer); // 清屏

	gameInit(&game);
	while (1)
	{
		if (clock() - game.lastLoopTime > CLOCKS_PER_SEC * 1 / 1) ///< 1S
		{
			game.lastLoopTime = clock();
			gameLoop(&game);
		}
		display1(&window, &game);
		gameEvent1(&game, &window);
	}
	// MessageBoxA(NULL, "game over", "game over", MB_OK);
	SDL_Quit();
	return 0;
}