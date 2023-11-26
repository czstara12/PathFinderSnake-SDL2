/**
 * @file queue.c
 * @brief 队列的源文件
 * @details 队列的源文件，包含队列的函数的实现
 */

#include "queue.h"

/**
 * @brief 初始化队列
 * @param q 要初始化的队列
 * @return 返回初始化的队列
 */
queue *initQueue(queue *q)
{
	if (q == NULL)
		return NULL;

	if ((q->head = q->back = (listNode *)malloc(sizeof(listNode))) == NULL)
	{
		return NULL; // 在此返回错误信息 申请内存失败
	}

	q->count = 0;
	q->back->next = NULL;
	return q;
}

/**
 * @brief 插入一个数据到队列中
 * @param q 要插入的队列
 * @param data 要插入的数据
 * @return 返回插入的队列
 */
queue *pushQueue(queue *q, queueType data)
{
	if (q == NULL)
		return NULL;

	if (instertListNode(q->back, data) == NULL)
		return NULL; // 在此返回错误信息 申请内存失败
	q->back = q->back->next;
	q->count++;
	return q;
}

/**
 * @brief 从队列中取出一个数据
 * @param q 要取出数据的队列
 * @param data 用于保存取出的数据
 * @return 返回取出数据的队列
 */
queue *popQueue(queue *q, queueType *data)
{
	if (q == NULL)
		return NULL;
	if (q->count == 0)
		return NULL;
	*data = q->head->next->data;
	deleteNextListNode(q->head);
	q->count--;
	return q;
}

/**
 * @brief 快速从队列中取出一个数据
 * @param q 要取出数据的队列
 * @return 返回要取出的数据
 */
queueType quickPopQueue(queue *q)
{
	if (q == NULL)
		return 0;
	if (q->count == 0)
		return 0;
	queueType data = q->head->next->data;
	deleteNextListNode(q->head);
	q->count--;
	return data;
}

/**
 * @brief 销毁队列
 * @param q 要销毁的队列
 */
void destroyqueue(queue *q)
{
	if (q == NULL)
		return;
	queueType data;
	while (q->count > 0)
		popQueue(q, &data);
	free(q->head);
}