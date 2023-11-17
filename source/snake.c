// snake.cpp: 定义控制台应用程序的入口点。
#include "snake.h"

short grid[HEIGHT][WIDTH] = {0};				// 地图
short snakeLength;								// 蛇的长度
Direction dire, diren;							// 方向
short snakeHeadPosition_x, snakeHeadPosition_y; // 蛇头位置
clock_t lastLoopTime;							// 时间标记
SDL_Renderer *renderer;							// 刷子
SDL_Rect rect;									// 框子
BOOL end = FALSE;
BOOL quit = FALSE;
SDL_Event event; // 事件
SDL_Window *window;
int stepsSinceLastFood = 0; // 防止死循环

int initialize()
{
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);																									  // 初始化SDL
	window = SDL_CreateWindow("snake.by starstory", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, HEIGHT * 20, WIDTH * 20, SDL_WINDOW_SHOWN); // 创建SDL窗口
	srand((unsigned)time(NULL));																												  // 初始化随机数
	clock_t lastLoopTime = clock();																												  // 标记时间
	for (int i = 0; i < WIDTH; i++)
	{
		grid[0][i] = -2;
		grid[HEIGHT - 1][i] = -2;
	}
	for (int i = 0; i < HEIGHT; i++)
	{
		grid[i][0] = -2;
		grid[i][WIDTH - 1] = -2;
	}																	 // 占用地图边界
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED); // 刷子绑定窗口
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer); // 清屏
	snakeLength = 3;
	snakeHeadPosition_x = 3;
	snakeHeadPosition_y = 3;
	grid[3][3] = 3;
	grid[3][2] = 2;
	grid[3][1] = 1;
	dire = d_right;
	diren = d_right;
	newfood(); // 初始化一个食物
	return 0;
}
int gamewithai()
{
	if ((dire = ai(grid, snakeLength, snakeHeadPosition_x, snakeHeadPosition_y, 0)) == d_error)
	{
		MessageBoxA(NULL, "没路了", "error", MB_OK);
		return 0;
	}
	if (stepsSinceLastFood > (WIDTH - 2) * (HEIGHT - 2) * 4)
	{
		MessageBoxA(NULL, "死循环", "error", MB_OK);
		return 0;
	}
	switch (dire)
	{
	case d_up:
		if (moveSnake(snakeHeadPosition_x, snakeHeadPosition_y - 1) == 1)
			snakeHeadPosition_y = snakeHeadPosition_y - 1;
		else
			end = TRUE;
		break;
	case d_down:
		if (moveSnake(snakeHeadPosition_x, snakeHeadPosition_y + 1) == 1)
			snakeHeadPosition_y = snakeHeadPosition_y + 1;
		else
			end = TRUE;
		break;
	case d_left:
		if (moveSnake(snakeHeadPosition_x - 1, snakeHeadPosition_y) == 1)
			snakeHeadPosition_x = snakeHeadPosition_x - 1;
		else
			end = TRUE;
		break;
	case d_right:
		if (moveSnake(snakeHeadPosition_x + 1, snakeHeadPosition_y) == 1)
			snakeHeadPosition_x = snakeHeadPosition_x + 1;
		else
			end = TRUE;
		break;
	}
	if (end)
		return 0;
	display();

	if (quit)
		return 0;
	// SDL_Delay(10);
	while (SDL_PollEvent(&event))
		switch (event.type)
		{
		case SDL_QUIT:
			quit = TRUE;
			break;
		}
	if (quit)
		return 0;
	return 1;
}

int gameLoop()
{
	if (clock() - lastLoopTime > CLOCKS_PER_SEC * 2 / 9)
	{
		lastLoopTime = clock();
		switch (dire)
		{
		case d_up:
			if (moveSnake(snakeHeadPosition_x, snakeHeadPosition_y - 1) == 1)
				snakeHeadPosition_y = snakeHeadPosition_y - 1;
			else
				end = TRUE;
			break;
		case d_down:
			if (moveSnake(snakeHeadPosition_x, snakeHeadPosition_y + 1) == 1)
				snakeHeadPosition_y = snakeHeadPosition_y + 1;
			else
				end = TRUE;
			break;
		case d_left:
			if (moveSnake(snakeHeadPosition_x - 1, snakeHeadPosition_y) == 1)
				snakeHeadPosition_x = snakeHeadPosition_x - 1;
			else
				end = TRUE;
			break;
		case d_right:
			if (moveSnake(snakeHeadPosition_x + 1, snakeHeadPosition_y) == 1)
				snakeHeadPosition_x = snakeHeadPosition_x + 1;
			else
				end = TRUE;
			break;
		}
		if (end)
			return 0;
		display();
	}
	while (SDL_PollEvent(&event))
		switch (event.type)
		{
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym)
			{
			case SDLK_w:
				if (diren == d_up || diren == d_down)
					break;
				else
					dire = d_up;
				break;
			case SDLK_a:
				if (diren == d_left || diren == d_right)
					break;
				else
					dire = d_left;
				break;
			case SDLK_s:
				if (diren == d_up || diren == d_down)
					break;
				else
					dire = d_down;
				break;
			case SDLK_d:
				if (diren == d_left || diren == d_right)
					break;
				else
					dire = d_right;
				break;
			}
			break;
		case SDL_QUIT:
			quit = TRUE;
			break;
		}
	if (quit)
		return 0;
	return 1;
}

int moveSnake(int x, int y)
{ // 蛇头向前进一个格
	diren = dire;
	if (grid[y][x] == 0 || grid[y][x] == 1)
	{
		grid[y][x] = snakeLength + 1;
		stepsSinceLastFood++;
		for (int a = 0; a < HEIGHT; a++)
			for (int b = 0; b < HEIGHT; b++)
				grid[a][b] = (grid[a][b] > 0 ? grid[a][b] - 1 : grid[a][b]);
	}
	else if (grid[y][x] == -1)
	{
		snakeLength++;
		grid[y][x] = snakeLength;
		stepsSinceLastFood = 0;
		newfood();
	}
	else
		return 0;
	return 1;
}

void display()
{
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderClear(renderer);
	for (int a = 0; a < HEIGHT; a++)
	{
		for (int b = 0; b < WIDTH; b++)
		{
			switch (grid[a][b])
			{
			case 0:
				break;
			case -1:
				rect.x = b * 20 + 2;
				rect.y = a * 20 + 2;
				rect.h = rect.w = 16;
				SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
				SDL_RenderFillRect(renderer, &rect);
				break;
			case -2:
				rect.x = b * 20;
				rect.y = a * 20;
				rect.h = rect.w = 20;
				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
				SDL_RenderFillRect(renderer, &rect);
				break;
			default:
				rect.x = b * 20 + 2;
				rect.y = a * 20 + 2;
				rect.h = rect.w = 16;
				if (snakeLength != grid[a][b])
					SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
				else
					SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
				SDL_RenderFillRect(renderer, &rect);
				if (a < 1 || b < 1)
				{
					// std::cerr << "错误" << __FILE__ << __LINE__ << __FUNCTION__ << std::endl;
					exit(-1);
				}
				if (abs(grid[a - 1][b] - grid[a][b]) == 1 && grid[a - 1][b] != 0)
				{
					rect.x = b * 20 + 2;
					rect.y = a * 20;
					rect.w = 16;
					rect.h = 2;
					SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
					SDL_RenderFillRect(renderer, &rect);
				}
				if (abs(grid[a + 1][b] - grid[a][b]) == 1 && grid[a + 1][b] != 0)
				{
					rect.x = b * 20 + 2;
					rect.y = a * 20 + 18;
					rect.w = 16;
					rect.h = 2;
					SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
					SDL_RenderFillRect(renderer, &rect);
				}
				if (abs(grid[a][b + 1] - grid[a][b]) == 1 && grid[a][b + 1] != 0)
				{
					rect.x = b * 20 + 18;
					rect.y = a * 20 + 2;
					rect.w = 2;
					rect.h = 16;
					SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
					SDL_RenderFillRect(renderer, &rect);
				}
				if (abs(grid[a][b - 1] - grid[a][b]) == 1 && grid[a][b - 1] != 0)
				{
					rect.x = b * 20;
					rect.y = a * 20 + 2;
					rect.w = 2;
					rect.h = 16;
					SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
					SDL_RenderFillRect(renderer, &rect);
				}
				break;
			}
		}
	}
	rect.x = snakeHeadPosition_x * 20 + 2;
	rect.y = snakeHeadPosition_y * 20 + 2;
	rect.h = rect.w = 16;
	SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
	SDL_RenderFillRect(renderer, &rect);
	SDL_RenderPresent(renderer);
}
void displayt()
{
	system("cls");
	for (int a = 0; a < HEIGHT; a++)
	{
		for (int b = 0; b < WIDTH; b++)
		{
			// std::cout.width(4);
			// std::cout << grid[a][b];
		}
		// std::cout << std::endl << std::endl;
	}
	Sleep(10);
}
void newfood()
{ // 随机一个新的食物
	int r = rand() % ((WIDTH - 2) * (HEIGHT - 2) - snakeLength);
	short *p;
	p = grid[0];

	while (r >= 0)
	{
		if (*p == 0)
			r--;
		p++;
	}
	p--; // 上方循环在r=0时p多自增了一次
	*p = -1;
}
