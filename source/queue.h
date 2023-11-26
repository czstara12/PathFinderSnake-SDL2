#pragma once
/**
 * @file queue.h
 * @brief 队列的头文件
 * @details 队列的头文件，包含队列的结构体和函数的声明
 */

/**
 * @file queue.h
 * @brief 队列的头文件
 * @details 队列的头文件，包含队列的结构体和函数的声明
 */
#include "list.h"

/**
 * @brief 队列的数据类型
 * @details 队列的数据类型，与基础链表的数据类型相同
 */
typedef listType queueType;

/**
 * @brief 队列
 * @details 队列，包含队列的头节点和尾节点的指针，以及队列的长度
 */
typedef struct queue
{
	listNode *head;
	listNode *back;
	int count;
} queue;

queue *initQueue(queue *q);
queue *pushQueue(queue *q, queueType data);
queue *popQueue(queue *q, queueType *data);
void destroyqueue(queue *q);
