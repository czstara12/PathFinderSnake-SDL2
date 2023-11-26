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

/**
 * @brief 图形绘制函数
 *
 * @param window
 * @param pGame
 */
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

/**
 * @brief 游戏事件处理
 *
 * @param pGame
 * @param window
 */
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
