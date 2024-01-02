/**
 * @file snake.c
 * @brief 贪吃蛇游戏
 * @details 用C语言实现的贪吃蛇游戏
 * @mainpage 贪吃蛇游戏
 */

#include "snake.h"

/**
 * @brief 游戏初始化
 * @param pGame 游戏信息
 * @return 0
 */
int gameInit(struct gameInfo *pGame)
{
	// 初始化地图
	for (int i = 0; i < HEIGHT; i++)
		for (int j = 0; j < WIDTH; j++)
		{
			pGame->grid[i][j] = SPACE;
		}
	for (int i = 0; i < WIDTH; i++)
	{
		pGame->grid[0][i] = WALL;
		pGame->grid[HEIGHT - 1][i] = WALL;
	}
	for (int i = 0; i < HEIGHT; i++)
	{
		pGame->grid[i][0] = WALL;
		pGame->grid[i][WIDTH - 1] = WALL;
	}

	// 初始化蛇
	pGame->snakeLength = 3;
	pGame->grid[3][3] = HEAD;
	pGame->grid[3][2] = RIGHT;
	pGame->grid[3][1] = RIGHT;
	pGame->pSnakeHead = &pGame->grid[3][3];
	pGame->pSnakeTail = &pGame->grid[3][1];
	pGame->headDirection = RIGHT;

	pGame->lastLoopTime = clock();

	srand((unsigned)time(NULL)); // 初始化随机数
	newfood(pGame);				 // 初始化一个食物
	return 0;
}

/**
 * @brief 随机一个新的食物
 * @param pGame 游戏信息
 * @return 0
 */
void newfood(struct gameInfo *pGame)
{
	int r = rand() % ((WIDTH - 2) * (HEIGHT - 2) - pGame->snakeLength);
	char *p = pGame->grid[0];
	while (1)
	{
		if (*p == SPACE)
		{
			if (r == 0)
			{
				*p = FOOD;
				pGame->pFood = p;
				break;
			}
			else
				r--;
		}
		p++;
	}
}

/**
 * @brief 在终端中绘制
 * @param pGame 游戏信息
 */
void displayOnTerminal(struct gameInfo *pGame)
{
	system("cls");
	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			switch (pGame->grid[i][j])
			{
			case SPACE:
				printf("  ");
				break;
			case WALL:
				printf(" #");
				break;
			case FOOD:
				printf(" *");
				break;
			case HEAD:
				printf(" @");
				break;
			case LEFT:
				printf(" <");
				break;
			case RIGHT:
				printf(" >");
				break;
			case UP:
				printf(" A");
				break;
			case DOWN:
				printf(" V");
				break;
			default:
				printf(" ?");
				break;
			}
		}
		printf("\n");
	}
	printf("score:%d\n", pGame->snakeLength - 3);
}

/**
 * @brief 游戏主循环
 * @param pGame 游戏信息
 * @return 0
 */
int gameLoop(struct gameInfo *pGame)
{
	// 游戏逻辑判断
	switch (*(pGame->pSnakeHead + pGame->headDirection))
	{
	case FOOD:
		pGame->snakeLength++;
		*(pGame->pSnakeHead + pGame->headDirection) = HEAD;
		*pGame->pSnakeHead = pGame->headDirection;
		pGame->pSnakeHead = pGame->pSnakeHead + pGame->headDirection;
		newfood(pGame);
		break;
	case SPACE:
		*(pGame->pSnakeHead + pGame->headDirection) = HEAD;
		*pGame->pSnakeHead = pGame->headDirection;
		pGame->pSnakeHead = pGame->pSnakeHead + pGame->headDirection;
		char temp = *(pGame->pSnakeTail);
		*(pGame->pSnakeTail) = SPACE;
		pGame->pSnakeTail = pGame->pSnakeTail + temp;
		break;
	case WALL:
	case LEFT:
	case RIGHT:
	case UP:
	case DOWN:
		if (*(pGame->pSnakeHead + pGame->headDirection) == *(pGame->pSnakeTail))
		{
			*(pGame->pSnakeHead + pGame->headDirection) = HEAD;
			*pGame->pSnakeHead = pGame->headDirection;
			pGame->pSnakeTail = pGame->pSnakeTail + *(pGame->pSnakeTail);
			pGame->pSnakeHead = pGame->pSnakeHead + pGame->headDirection;
			break;
		}
		// TODO:游戏终止
		break;
	case HEAD: // 这不可能
		assert(0);
		break;
	}
	return 0;
}

/**
 * @brief 获取输入
 * @param pGame 游戏信息
 */
void gameEventFromTerminal(struct gameInfo *pGame)
{
	// 获取输入
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'w':
			if (pGame->pSnakeHead[UP] == DOWN)
				break;
			else
				pGame->headDirection = UP;
			break;
		case 'a':
			if (pGame->pSnakeHead[LEFT] == RIGHT)
				break;
			else
				pGame->headDirection = LEFT;
			break;
		case 's':
			if (pGame->pSnakeHead[DOWN] == UP)
				break;
			else
				pGame->headDirection = DOWN;
			break;
		case 'd':
			if (pGame->pSnakeHead[RIGHT] == LEFT)
				break;
			else
				pGame->headDirection = RIGHT;
			break;
		case 'q':
			// TODO: 退出游戏
			break;
		}

		gameLoop(pGame);
		// pGame->lastLoopTime = clock();
	}
}
