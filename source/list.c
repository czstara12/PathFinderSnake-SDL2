/**
 * @file list.c
 * @brief 链表的源文件
 * @details 链表的源文件，包含链表的函数的实现
 */
#include "list.h"

/**
 * @brief 插入一个数据到链表中
 * @param instert 要插入的位置
 * @param data 要插入的数据
 * @return 返回插入的节点
 */
listNode *instertListNode(listNode *instert, listType data)
{
	listNode *newListNode; // 新节点指针
	if (instert == NULL)
	{
		return NULL; // 传入的指针为空 必须传入一个链表的节点
	}
	if ((newListNode = (listNode *)malloc(sizeof(listNode))) == NULL)
	{
		return NULL; // 申请内存失败
	}
	newListNode->next = instert->next; // 新节点的下一个节点为插入位置的下一个节点
	newListNode->data = data;		   // 新节点的数据为传入的数据
	instert->next = newListNode;	   // 更新插入位置的下一个节点为新节点
	return newListNode;
}

/**
 * @brief 删除一个节点
 * @param prevNode 要删除的节点的前一个节点
 * @return 返回前一个节点
 */
listNode *deleteNextListNode(listNode *prevNode)
{
	if (prevNode == NULL)
		return NULL; // 节点不存在
	if (prevNode->next == NULL)
		return NULL;						 // 要删除的节点不存在
	listNode *nodeToDelete = prevNode->next; // 保存要删除的节点的指针
	prevNode->next = nodeToDelete->next;	 // 更新要删除的节点的前一个节点的下一个节点为要删除的节点的下一个节点
	free(nodeToDelete);						 // 释放要删除的节点
	return prevNode;
}

/**
 * @brief 初始化链表
 * @param listToInit 要初始化的链表
 * @return 返回初始化的链表
 */
list *initList(list *listToInit)
{
	listToInit->count = 0;
	if ((listToInit->head = listToInit->last = (listNode *)malloc(sizeof(listNode))) == NULL)
	{
		return NULL; // 申请内存失败
	}
	listToInit->last->next = NULL;
	return listToInit;
}
/**
 * @brief 插入一个数据到链表中
 * @param listToInstert 要插入的链表
 * @param nodeToInstert 要插入的位置
 * @param data 要插入的数据
 * @return 返回插入的链表
 * @details 插入一个数据到链表中
 */
list *instertList(list *listToInstert, listNode *nodeToInstert, listType data)
{
	if (nodeToInstert == NULL)
	{
		return NULL; // 传入的指针为空 必须传入一个链表的节点
	}
	if (listToInstert == NULL)
	{
		return NULL; // 传入的指针为空 必须传入一个链表
	}
	if (instertListNode(nodeToInstert, data) == NULL)
		return NULL;
	if (nodeToInstert->next->next == NULL)
	{
		listToInstert->last = nodeToInstert->next;
	}
	listToInstert->count++;
	return listToInstert;
}

/**
 * @brief 插入到链表尾
 * @param listToInstert 要插入的链表
 * @param data 要插入的数据
 * @return 返回插入的链表
 */
list *instertListToBack(list *listToInstert, listType data)
{
	return instertList(listToInstert, listToInstert->last, data);
}

/**
 * @brief 插入到链表头
 * @param listToInstert 要插入的链表
 * @param data 要插入的数据
 * @return 返回插入的链表
 */
list *instertListToFront(list *listToInstert, listType data)
{
	return instertList(listToInstert, listToInstert->head, data);
}

/**
 * @brief 删除下一个节点
 * @param listToDelete 要删除的链表
 * @param nodeToDelete 要删除的节点
 * @return 返回删除的链表
 */
list *deleteListNextNode(list *listToDelete, listNode *prevNodeToDelete)
{
	if (prevNodeToDelete == NULL)
	{
		return NULL; // 传入的指针为空 必须传入一个链表的节点
	}
	if (prevNodeToDelete->next == NULL)
	{
		return NULL; // 下一个节点为空 必须传入一个链表的节点
	}
	if (listToDelete == NULL)
	{
		return NULL; // 传入的指针为空 必须传入一个链表
	}
	if (deleteNextListNode(prevNodeToDelete) == NULL)
		return NULL;
	if (prevNodeToDelete->next == NULL)
	{
		listToDelete->last = prevNodeToDelete;
	}
	listToDelete->count--;
	return listToDelete;
}
/**
 * @brief 删除链表第一个节点
 * @param listToDelete 要删除的链表
 * @return 返回删除的链表
 */
list *deleteListFront(list *listToDelete)
{
	return deleteListNextNode(listToDelete, listToDelete->head);
}

/**
 * @brief 销毁链表
 * @param listToDelete 要删除的链表
 */
void destroyList(list *listToDelete)
{
	if (listToDelete == NULL)
		return;
	while (listToDelete->count > 0)
		deleteListFront(listToDelete);
	free(listToDelete->head);
}
