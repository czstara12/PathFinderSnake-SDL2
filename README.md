# PathFinderSnake 寻路蛇

使用了SDL图形库 wsad操控方向

正在开发(练习)的功能 自动寻路蛇

这是一个使用SDL2制作的经典小游戏 贪吃蛇 添加了自动寻路功能
构建环境:CMAKE

## 食用方法

```shell
git clone https://github.com/czstara12/PathFinderSnake-SDL2.git  --recurse-submodules
cd PathFinderSnake-SDL2
mkdir build
cd build
cmake ..
cmake --build .
```

生成的程序在build目录或者build\Debug目录下 直接运行即可

乏了 以后在搞寻路功能吧

修改长和宽请修改snake.h中的(长宽包括四周的边框 比如下面的代码中 蛇的活动空间只有中间的28*28)

```c
#define WIDTH 30
#define HEIGHT 30//长宽
```



# 以下内容过期

具体实现方法 搜索一条能到达食物的最短路径
模拟走一遍 并判断吃到食物后是否有一条路通往蛇尾 如果有 将当前搜索到的方向返回
如果搜索不到吃食物的路径或者吃了食物就没有一条路径能通向蛇尾 那么选择一条通往蛇尾的最远方向

## 具体算法

寻路算法入口:
计算是否只有一个可能的前进方向 如果是直接返回
进行广度优先搜索
如果有路
-模拟
如果没有搜索到直接路径或者当前路径是一个"陷阱"
-代价寻路

模拟:
拷贝地图
在拷贝地图上直接应用搜索到的路径或者应用搜索到的方向并重新搜索直到吃到食物
寻路到蛇尾并返回结果

代价寻路:
复制寻路地图
从蛇尾开始构建代价地图
选择代价最高的方向

