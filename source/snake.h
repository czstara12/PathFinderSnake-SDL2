#pragma once
/**
 * @file snake.h
 * @brief 贪吃蛇游戏头文件
 * @details 定义了贪吃蛇游戏的相关数据结构和函数声明
 */

#ifndef SNAKE_H
#define SNAKE_H

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <assert.h>

#define WIDTH 32
#define HEIGHT 32

/**
 * @brief 方向枚举
 * @details 用于标记蛇节的方向
 */
enum
{
	UP = -WIDTH,  ///< 上
	LEFT = -1,	  ///< 左
	SPACE = 0,	  ///< 空格
	RIGHT = 1,	  ///< 右
	DOWN = WIDTH, ///< 下
	FOOD,		  ///< 食物
	WALL,		  ///< 墙
	HEAD		  ///< 蛇头
};

/**
 * @brief 游戏信息结构体
 * @details 用于存储游戏的相关信息
 */
typedef struct gameInfo
{
	char grid[HEIGHT][WIDTH];			   ///< 地图
	short snakeLength;					   ///< 蛇的长度
	clock_t lastLoopTime;				   ///< 标记时间
	char *pSnakeHead, *pSnakeTail, *pFood; ///< 蛇头和蛇尾
	char headDirection;					   ///< 蛇头方向
} gameInfo;

int gameInit(struct gameInfo *game);
int gameLoop(struct gameInfo *game);
void newfood(struct gameInfo *pGame);
void gameEventFromTerminal(struct gameInfo *pGame);
void displayOnTerminal(struct gameInfo *pGame);
#endif