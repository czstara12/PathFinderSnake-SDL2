#include "dfs.h"

// 方向的辅助数组
static const char directions[4] = {UP, LEFT, DOWN, RIGHT};

// 返回第一步的方向 用UP, LEFT, DOWN, RIGHT的值表示
int depthFirstSearch(gameInfo *info, char *start, char *end)
{
    // 初始化栈
    stack pathStack;
    stackinit(&pathStack);

    // 用来记录每个节点的前一个节点
    char previous[HEIGHT][WIDTH] = {0};

    // 从蛇头开始
    push(&pathStack, (stackType)start);
    previous[0][start - info->grid[0]] = HEAD;

    while (pathStack.launth > 0)
    {
        char *current = (char *)pop(&pathStack);

        // 检查是否到达终点
        if (current == end)
        {
            // 追踪回蛇头，找到第一步的方向
            while (current + previous[0][current - info->grid[0]] != start)
            {
                current += previous[0][current - info->grid[0]];
            }
            stackdestroy(&pathStack);
            return -previous[0][current - info->grid[0]];
        }

        // 探索四个方向
        for (int i = 0; i < 4; i++)
        {
            if (previous[0][current - info->grid[0] + directions[i]] == 0 &&
                (current[directions[i]] == SPACE ||
                 current[directions[i]] == FOOD ||
                 &current[directions[i]] == info->pSnakeTail))
            {
                push(&pathStack, (stackType)&current[directions[i]]);
                previous[0][current - info->grid[0] + directions[i]] = -directions[i];
            }
        }
    }

    // 没有找到路径
    stackdestroy(&pathStack);
    return 0;
}
