// snake.cpp: 定义控制台应用程序的入口点。
#include "snake.h"

short map[HEIGHT][WIDTH] = { 0 }; // 地图
short size;                     // 蛇的长度
Direction dire, diren; // 方向
short x, y;                     // 蛇头位置
clock_t mark;                   // 时间标记
SDL_Renderer *ren;//刷子
SDL_Rect rec;//框子
bool end = false;
bool quit = false;
SDL_Event event;//事件
SDL_Window * window;
int banai = 0;//防止死循环

int initialize()
{
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);//初始化SDL
	window = SDL_CreateWindow("snake.by starstory", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, HEIGHT * 20, WIDTH * 20 , SDL_WINDOW_SHOWN);//创建SDL窗口
	srand((unsigned)time(NULL));//初始化随机数
	mark = clock();//标记时间
	for (int i = 0; i < WIDTH; i++) {
		map[0][i] = -2;
		map[HEIGHT - 1][i] = -2;
	}
	for (int i = 0; i < HEIGHT; i++) {
		map[i][0] = -2;
		map[i][WIDTH - 1] = -2;
	}//占用地图边界
	ren = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);//刷子绑定窗口
	SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
	SDL_RenderClear(ren);
	SDL_RenderPresent(ren);//清屏
	size = 3;
	x = 3;
	y = 3;
	map[3][3] = 3;
	map[3][2] = 2;
	map[3][1] = 1;
	dire = d_right;
	diren = d_right;
	newfood();//初始化一个食物
	return 0;
}
int gamewithai()
{
	if ((dire = ai(map, size, x, y, 0)) == d_error)
	{
		MessageBox(NULL, "没路了", "error", MB_OK);
		return 0;
	}
	if (banai > (WIDTH-2)*(HEIGHT-2)*4)
	{
		MessageBox(NULL, "死循环", "error", MB_OK);
		return 0;
	}
	switch (dire) {
	case d_up:
		if (move(x, y - 1) == 1)
			y = y - 1;
		else
			end = true;
		break;
	case d_down:
		if (move(x, y + 1) == 1)
			y = y + 1;
		else
			end = true;
		break;
	case d_left:
		if (move(x - 1, y) == 1)
			x = x - 1;
		else
			end = true;
		break;
	case d_right:
		if (move(x + 1, y) == 1)
			x = x + 1;
		else
			end = true;
		break;
	}
	if (end)return 0;
	display();
	
	
	if (quit)
		return 0;
	//SDL_Delay(10);
	while (SDL_PollEvent(&event))
		switch (event.type)
		{
		case SDL_QUIT:
			quit = true;
			break;
		}
	if (quit)
		return 0;
	return 1;
}

int game()
{
	if (clock() - mark > CLOCKS_PER_SEC * 2 /9) {
		mark = clock();
		switch (dire) {
		case d_up:
			if (move(x, y - 1) == 1)
				y = y - 1;
			else
				end = true;
			break;
		case d_down:
			if (move(x, y + 1) == 1)
				y = y + 1;
			else
				end = true;
			break;
		case d_left:
			if (move(x - 1, y) == 1)
				x = x - 1;
			else
				end = true;
			break;
		case d_right:
			if (move(x + 1, y) == 1)
				x = x + 1;
			else
				end = true;
			break;
		}
		if (end)return 0;
		display();
	}
	while (SDL_PollEvent(&event))
		switch (event.type)
		{
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym) {
			case SDLK_w: if (diren == d_up || diren == d_down)
				break;
						 else
				dire = d_up;
				break;
			case SDLK_a: if (diren == d_left || diren == d_right)
				break;
						 else
				dire = d_left;
				break;
			case SDLK_s: if (diren == d_up || diren == d_down)
				break;
						 else
				dire = d_down;
				break;
			case SDLK_d: if (diren == d_left || diren == d_right)
				break;
						 else
				dire = d_right;
				break;
			}
			break;
		case SDL_QUIT:
			quit = true;
			break;
		}
	if (quit)
		return 0;
	return 1;
}

int move(int x, int y) {//蛇头向前进一个格
	diren = dire;
	if (map[y][x] == 0|| map[y][x] == 1) {
		map[y][x] = size + 1;
		banai++;
		for (int a = 0; a < HEIGHT; a++)
			for (int b = 0; b < HEIGHT; b++)
				map[a][b] = (map[a][b] > 0 ? map[a][b] - 1 : map[a][b]);
	}
	else if (map[y][x] == -1) {
		size++;
		map[y][x] = size;
		banai = 0;
		newfood();
	}
	else return 0;
	return 1;
}

void display() {
	SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
	SDL_RenderClear(ren);
	for (int a = 0; a < HEIGHT; a++) {
		for (int b = 0; b < WIDTH; b++) {
			switch (map[a][b])
			{
			case 0:
				break;
			case -1:
				rec.x = b * 20 + 2;
				rec.y = a * 20 + 2;
				rec.h = rec.w = 16;
				SDL_SetRenderDrawColor(ren, 255, 0, 0, 255);
				SDL_RenderFillRect(ren, &rec);
				break;
			case -2:
				rec.x = b * 20;
				rec.y = a * 20;
				rec.h = rec.w = 20;
				SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
				SDL_RenderFillRect(ren, &rec);
				break;
			default:
				rec.x = b * 20 + 2;
				rec.y = a * 20 + 2;
				rec.h = rec.w = 16;
				if(size!=map[a][b])
					SDL_SetRenderDrawColor(ren, 0, 255, 0, 255);
				else
					SDL_SetRenderDrawColor(ren, 0, 0, 255, 255);
				SDL_RenderFillRect(ren, &rec);
				if (a < 1 || b < 1)
				{
					std::cerr << "错误" << __FILE__ << __LINE__ << __FUNCTION__ << std::endl;
					exit(-1);
				}
				if (abs(map[a - 1][b] - map[a][b]) == 1 && map[a - 1][b] != 0) {
					rec.x = b * 20 + 2;
					rec.y = a * 20;
					rec.w = 16;
					rec.h = 2;
					SDL_SetRenderDrawColor(ren, 0, 255, 0, 255);
					SDL_RenderFillRect(ren, &rec);
				}
				if (abs(map[a + 1][b] - map[a][b]) == 1 && map[a + 1][b] != 0) {
					rec.x = b * 20 + 2;
					rec.y = a * 20 + 18;
					rec.w = 16;
					rec.h = 2;
					SDL_SetRenderDrawColor(ren, 0, 255, 0, 255);
					SDL_RenderFillRect(ren, &rec);
				}
				if (abs(map[a][b + 1] - map[a][b]) == 1 && map[a][b + 1] != 0) {
					rec.x = b * 20 + 18;
					rec.y = a * 20 + 2;
					rec.w = 2;
					rec.h = 16;
					SDL_SetRenderDrawColor(ren, 0, 255, 0, 255);
					SDL_RenderFillRect(ren, &rec);
				}
				if (abs(map[a][b - 1] - map[a][b]) == 1 && map[a][b - 1] != 0) {
					rec.x = b * 20;
					rec.y = a * 20 + 2;
					rec.w = 2;
					rec.h = 16;
					SDL_SetRenderDrawColor(ren, 0, 255, 0, 255);
					SDL_RenderFillRect(ren, &rec);
				}
				break;
			}
		}
	}
	rec.x = x * 20 + 2;
	rec.y = y * 20 + 2;
	rec.h = rec.w = 16;
	SDL_SetRenderDrawColor(ren, 0, 0, 255, 255);
	SDL_RenderFillRect(ren, &rec);
	SDL_RenderPresent(ren);
}
void displayt()
{
	system("cls");
	for (int a = 0; a < HEIGHT; a++) {
		for (int b = 0; b < WIDTH; b++) {
			std::cout.width(4);
			std::cout << map[a][b];
		}
		std::cout << std::endl << std::endl;
	}
	Sleep(10);
}
void newfood() {//随机一个新的食物
	int r = rand() % ((WIDTH - 2) * (HEIGHT - 2) - size);
	short *p;
	p = map[0];

	while (r >= 0) {
		if (*p == 0)
			r--;
		p++;
	}
	p--;//上方循环在r=0时p多自增了一次
	*p = -1;
}
