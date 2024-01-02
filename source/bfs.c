#include "bfs.h"

// 方向的辅助数组
static const char directions[4] = {UP, LEFT, DOWN, RIGHT};

// 返回第一步的方向 用UP, LEFT, DOWN, RIGHT的值表示
int bFirstSearch(gameInfo *info, char *start, char *end)
{
    // 初始化队列
    queue pathStack;
    initQueue(&pathStack);

    // 用来记录每个节点的前一个节点
    char previous[HEIGHT][WIDTH] = {0};

    // 从蛇头开始
    pushQueue(&pathStack, (queueType)start);
    previous[0][start - info->grid[0]] = HEAD;

    while (pathStack.count > 0)
    {
        char *current = (char *)quickPopQueue(&pathStack);

        // 检查是否到达食物
        if (current == end)
        {
            // 追踪回蛇头，找到第一步的方向
            while (current + previous[0][current - info->grid[0]] != start)
            {
                current += previous[0][current - info->grid[0]];
            }
            destroyqueue(&pathStack);
            return -previous[0][current - info->grid[0]];
        }

        // 探索四个方向
        for (int i = 0; i < 4; i++)
        {
            if (previous[0][current - info->grid[0] + directions[i]] == 0 &&
                (current[directions[i]] == SPACE || current[directions[i]] == FOOD))
            {
                pushQueue(&pathStack, (queueType)&current[directions[i]]);
                previous[0][current - info->grid[0] + directions[i]] = -directions[i];
            }
        }
    }

    // 没有找到路径
    destroyqueue(&pathStack);
    return 0;
}
