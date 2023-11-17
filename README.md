# PathFinderSnake 寻路蛇

使用了SDL图形库 wsad操控方向

正在开发(练习)的功能 自动蛇 (AI)

这是一个使用SDL2制作的经典小游戏 贪吃蛇 添加了自动寻路(ai)功能
构建环境:VS2017

切换手动/AI模式请把main.cpp中 gamewithai()换成game() 并把//MessageBox(NULL, "game over", "game over", MB_OK);前面的"//"去掉

```c
int main(int argc, char* args[]) {
	initialize();
	while (gamewithai());//此处切换AI/手动模式
	//MessageBox(NULL, "game over", "game over", MB_OK);//此处开关游戏结束弹窗
	SDL_Quit();
	return 0;
}
```

修改长和宽请修改snake.h中的(长宽包括四周的边框 比如下面的代码中 舍得活动空间只有中间的28*28)

```c
#define WIDTH 30
#define HEIGHT 30//长宽
```

两项
蛇的储存结构 二维数组 -2表示墙 -1表示食物 0表示啥都没有 其他正数表示蛇的节数
每次前进在前进的方向上的位置赋值为蛇的长度+1 然后遍历二维数组 将所有蛇身的数字-1 -2,-1,0保持不变
如下

```c
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
```

snake.cpp中display()函数处可以修改配色
AI.cpp可以修改ai逻辑
代码写的可能不好看 ai运行到最后会剩下几个格 求大佬指点更强的寻路算法

自动寻路使用广度优先算法(自己百度广度优先算法是什么 我讲不清)
具体实现方法 搜索一条能到达食物的最短路径
模拟走一遍 并判断吃到食物后是否有一条路通往蛇尾 如果有 将当前搜索到的路径方向返回
如果搜索不到吃食物的路径或者吃了食物就没有一条路径能通向蛇尾 那么搜索一条通往蛇尾的最远路径 并返回(求大佬指点搜索最远路径的更好的方法)
