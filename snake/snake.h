#pragma once
#ifndef SNAKE_H
#define SNAKE_H

//#include "AI.h"
#include <time.h>
#include <SDL.h>
#include <iostream>
#include <Windows.h>
#include "AI.h"
#include "public.h"

/**
 * @brief 枚举类型，表示每个格子的状态。
 */
enum class GridStatus {
    Empty,      /**< 空格子，没有任何物体。 */
    SnakeBody,  /**< 蛇的身体部分。 */
    Food,       /**< 食物。 */
    Wall,       /**< 墙。 */
    // 添加其他可能的状态...
};


void display();                 // 显示
int moveSnake(int x, int y);//蛇的移动
void newfood();//刷新食物
int initialize();
int gameLoop();
int gamewithai();
void displayt();

#endif