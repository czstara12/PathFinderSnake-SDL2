/**
 * @file draw.c
 * @author starstory
 * @brief 绘图和事件函数
 * @version 0.1
 * @date 2023-11-26
 *
 * @copyright MIT 2023
 *
 */
#include "draw.h"

void drawInit(drawClass *pWindow)
{
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);                                                                                                                                 // 初始化SDL
    pWindow->window = SDL_CreateWindow("snake.by starstory", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH * PIXELPERUNIT, HEIGHT * PIXELPERUNIT, SDL_WINDOW_SHOWN); // 创建SDL窗口
    pWindow->renderer = SDL_CreateRenderer(pWindow->window, -1, SDL_RENDERER_ACCELERATED);                                                                                     // 渲染器绑定窗口
    SDL_SetRenderDrawColor(pWindow->renderer, 255, 255, 255, 255);
    SDL_RenderClear(pWindow->renderer);
    SDL_RenderPresent(pWindow->renderer); // 清屏
}

/**
 * @brief 图形绘制函数
 *
 * @param pWindow
 * @param pGame
 */
void SDL_GameDisplay(drawClass *pWindow, gameInfo *pGame)
{
    SDL_SetRenderDrawColor(pWindow->renderer, 255, 255, 255, 255);
    SDL_RenderClear(pWindow->renderer);
    for (int a = 0; a < HEIGHT; a++)
    {
        for (int b = 0; b < WIDTH; b++)
        {
            if (pGame->grid[a][b] == SPACE)
                continue;
            pWindow->rect.x = b * PIXELPERUNIT + PIXELPERUNIT / ZOOM_OUT;
            pWindow->rect.y = a * PIXELPERUNIT + PIXELPERUNIT / ZOOM_OUT;
            pWindow->rect.w = PIXELPERUNIT - PIXELPERUNIT / ZOOM_OUT * 2;
            pWindow->rect.h = PIXELPERUNIT - PIXELPERUNIT / ZOOM_OUT * 2;
            switch (pGame->grid[a][b])
            {
            case WALL:
                SDL_SetRenderDrawColor(pWindow->renderer, 0, 0, 0, 255);
                pWindow->rect.x = b * PIXELPERUNIT;
                pWindow->rect.y = a * PIXELPERUNIT;
                pWindow->rect.w = PIXELPERUNIT;
                pWindow->rect.h = PIXELPERUNIT;
                break;
            case FOOD:
                SDL_SetRenderDrawColor(pWindow->renderer, 255, 0, 0, 255);
                break;
            case HEAD:
                SDL_SetRenderDrawColor(pWindow->renderer, 0, 255, 0, 255);
                break;
            case UP:
                SDL_SetRenderDrawColor(pWindow->renderer, 0, 0, 255, 255);
                pWindow->rect.y = a * PIXELPERUNIT - PIXELPERUNIT / ZOOM_OUT;
                pWindow->rect.h = PIXELPERUNIT;
                break;
            case DOWN:
                SDL_SetRenderDrawColor(pWindow->renderer, 0, 0, 255, 255);
                pWindow->rect.h = PIXELPERUNIT;
                break;
            case LEFT:
                SDL_SetRenderDrawColor(pWindow->renderer, 0, 0, 255, 255);
                pWindow->rect.x = b * PIXELPERUNIT - PIXELPERUNIT / ZOOM_OUT;
                pWindow->rect.w = PIXELPERUNIT;
                break;
            case RIGHT:
                SDL_SetRenderDrawColor(pWindow->renderer, 0, 0, 255, 255);
                pWindow->rect.w = PIXELPERUNIT;
                break;
            }
            SDL_RenderFillRect(pWindow->renderer, &pWindow->rect);
        }
    }
    SDL_RenderPresent(pWindow->renderer);
}

/**
 * @brief 游戏事件处理
 *
 * @param pGame
 * @param pWindow
 */
void SDL_GameEvent(drawClass *pWindow, gameInfo *pGame)
{
    while (SDL_PollEvent(&pWindow->event))
        switch (pWindow->event.type)
        {
        case SDL_KEYDOWN:
            switch (pWindow->event.key.keysym.sym)
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
            SDL_GameDisplay(pWindow, pGame);
            break;
        case SDL_QUIT:
            exit(0);
            break;
        }
}
