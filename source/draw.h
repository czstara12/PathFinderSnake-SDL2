/**
 * @file draw.h
 * @author starstory
 * @brief 绘图和事件函数需要的头文件和类
 * @version 0.1
 * @date 2023-11-26
 *
 * @copyright MIT 2023
 *
 */
#include "SDL.h"
#include <Windows.h>
#include "snake.h"

#define PIXELPERUNIT 30
#define ZOOM_OUT 15

/**
 * @brief 画图类
 *
 */
typedef struct drawClass
{
    SDL_Renderer *renderer; ///< 渲染器
    SDL_Rect rect;          ///< 矩形对象
    SDL_Event event;        ///< 事件
    SDL_Window *window;     ///< 窗口
} drawClass;

void SDL_GameDisplay(drawClass *window, gameInfo *pGame);
void SDL_GameEvent(drawClass *window, gameInfo *pGame);
void drawInit(drawClass *window);
