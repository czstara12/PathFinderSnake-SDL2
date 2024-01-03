/**
 * @file pathFinder.c
 * @author starstory
 * @brief
 * @version 0.1
 * @date 2023-11-26
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "pathFinder.h"

int sim(gameInfo *pGame)
{
	gameInfo game;
	memcpy(&game, pGame, sizeof(gameInfo));
	gameLoop(pGame);
	int result = depthFirstSearch(pGame, pGame->pSnakeHead, pGame->pSnakeTail);
	memcpy(pGame, &game, sizeof(gameInfo));
	return result;
}

void plan(gameInfo *pGame)
{
	pGame->headDirection = bFirstSearch(pGame, pGame->pSnakeHead, pGame->pFood);

	if (pGame->headDirection == 0 || sim(pGame) == 0)
		pGame->headDirection = depthFirstSearch(pGame, pGame->pSnakeHead, pGame->pSnakeTail);

	// 首先直接搜索路径(算法1)

	// 模拟移动一步 然后搜索到蛇尾的路径(算法2)

	// 判断第二次寻路是否成功 如果成功则直接使用第一步的结果

	// 如果失败则直接搜索到蛇尾的路径(算法2)
}
