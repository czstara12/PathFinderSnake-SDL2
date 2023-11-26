#pragma once
/**
 * @file list.h
 * @brief 链表的头文件
 * @details 链表的头文件，包含链表的结构体和函数的声明
 */

#include <malloc.h>

/**
 * @brief 链表的数据类型
 * @details 链表的数据类型，可以根据需要修改
 */
typedef void *listType;

/**
 * @brief 链表的节点
 * @details 链表的节点，包含下一个节点的指针和数据
 */
typedef struct listNode
{
	struct listNode *next; ///< 下一个
	listType data;
} listNode;

/**
 * @brief 链表
 * @details 链表，包含头节点和尾节点的指针，以及链表的长度
 */
typedef struct list
{
	listNode *head;
	listNode *last;
	int count;
} list;

listNode *instertListNode(listNode *instert, listType data);
listNode *deleteNextListNode(listNode *prevNode);
list *initList(list *listToInit);
list *instertList(list *listToInstert, listNode *nodeToInstert, listType data);
list *instertListToBack(list *listToInstert, listType data);
list *instertListToFront(list *listToInstert, listType data);
list *deleteListNextNode(list *listToDelete, listNode *prevNodeToDelete);
list *deleteListFront(list *listToDelete);
void destroyList(list *listToDelete);
