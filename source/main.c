/*
 * @Date: 2023-11-17 22:18:37
 * @LastEditors: starstory czstara12@gmail.com
 * @LastEditTime: 2023-11-25 23:08:17
 * @FilePath: \PathFinderSnake-SDL2\source\main.c
 */
/**
 * @file main.c
 * @author starstory (czstara12@gmail.com)
 * @brief
 * @version 0.1
 * @date 2023-11-18
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "main.h"

// TODO: 将此部分抽出到独立文件
#define PIXELPERUNIT 30
#define ZOOM_OUT 15

typedef struct drawClass
{
	SDL_Renderer *renderer; // 渲染器
	SDL_Rect rect;			// 矩形对象
	SDL_Event event;		// 事件
	SDL_Window *window;		// 窗口
} drawClass;

void display1(drawClass *window, gameInfo *pGame)
{
	SDL_SetRenderDrawColor(window->renderer, 255, 255, 255, 255);
	SDL_RenderClear(window->renderer);
	for (int a = 0; a < HEIGHT; a++)
	{
		for (int b = 0; b < WIDTH; b++)
		{
			if (pGame->grid[a][b] == SPACE)
				continue;
			window->rect.x = b * PIXELPERUNIT + PIXELPERUNIT / ZOOM_OUT;
			window->rect.y = a * PIXELPERUNIT + PIXELPERUNIT / ZOOM_OUT;
			window->rect.w = PIXELPERUNIT - PIXELPERUNIT / ZOOM_OUT * 2;
			window->rect.h = PIXELPERUNIT - PIXELPERUNIT / ZOOM_OUT * 2;
			switch (pGame->grid[a][b])
			{
			case WALL:
				SDL_SetRenderDrawColor(window->renderer, 0, 0, 0, 255);
				window->rect.x = b * PIXELPERUNIT;
				window->rect.y = a * PIXELPERUNIT;
				window->rect.w = PIXELPERUNIT;
				window->rect.h = PIXELPERUNIT;
				break;
			case FOOD:
				SDL_SetRenderDrawColor(window->renderer, 255, 0, 0, 255);
				break;
			case HEAD:
				SDL_SetRenderDrawColor(window->renderer, 0, 255, 0, 255);
				break;
			case UP:
				SDL_SetRenderDrawColor(window->renderer, 0, 0, 255, 255);
				window->rect.y = a * PIXELPERUNIT - PIXELPERUNIT / ZOOM_OUT;
				window->rect.h = PIXELPERUNIT;
				break;
			case DOWN:
				SDL_SetRenderDrawColor(window->renderer, 0, 0, 255, 255);
				window->rect.h = PIXELPERUNIT;
				break;
			case LEFT:
				SDL_SetRenderDrawColor(window->renderer, 0, 0, 255, 255);
				window->rect.x = b * PIXELPERUNIT - PIXELPERUNIT / ZOOM_OUT;
				window->rect.w = PIXELPERUNIT;
				break;
			case RIGHT:
				SDL_SetRenderDrawColor(window->renderer, 0, 0, 255, 255);
				window->rect.w = PIXELPERUNIT;
				break;
			}
			SDL_RenderFillRect(window->renderer, &window->rect);
		}
	}
	SDL_RenderPresent(window->renderer);
}

void gameEvent1(gameInfo *pGame, drawClass *window)
{
	while (SDL_PollEvent(&window->event))
		switch (window->event.type)
		{
		case SDL_KEYDOWN:
			switch (window->event.key.keysym.sym)
			{
			case SDLK_w:
				if (pGame->pSnakeHead[UP] == DOWN)
					break;
				else
					pGame->headDirection = UP;
				break;
			case SDLK_a:
				if (pGame->pSnakeHead[LEFT] == RIGHT)
					break;
				else
					pGame->headDirection = LEFT;
				break;
			case SDLK_s:
				if (pGame->pSnakeHead[DOWN] == UP)
					break;
				else
					pGame->headDirection = DOWN;
				break;
			case SDLK_d:
				if (pGame->pSnakeHead[RIGHT] == LEFT)
					break;
				else
					pGame->headDirection = RIGHT;
				break;
			case 'q':
				exit(0);
				break;
			}
			gameLoop(pGame);
			break;
		case SDL_QUIT:
			exit(0);
			break;
		}
}

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