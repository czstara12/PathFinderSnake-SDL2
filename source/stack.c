#include "stack.h"

/**
 * @brief 初始化
 *
 * @param init
 * @return int
 */
int stackinit(stack *init)
{
	init->size = defaultStackSize;
	init->base = init->top = (stackType *)malloc(sizeof(stackType) * init->size);
	init->launth = 0;
	return 0;
}

/**
 * @brief 压栈
 *
 * @param ps
 * @param data
 */
void push(stack *ps, stackType data)
{
	if (ps->launth == ps->size)
	{
		ps->size *= 2;
		stackType *tmp;
		if ((tmp = (stackType *)malloc(sizeof(stackType) * ps->size)) == NULL)
		{
			assert(0);
		}
		stackType *a = ps->base;
		stackType *b = tmp;
		while (a != ps->top)
		{
			*b = *a;
			a++;
			b++;
		}
		free(ps->base);
		ps->base = tmp;
		ps->top = b;
	}
	*(ps->top) = data;
	ps->top++;
	ps->launth++;
}

/**
 * @brief 弹出
 *
 * @param ps
 * @return stackType
 */
stackType pop(stack *ps)
{
	if (ps->launth == 0)
	{
		return NULL;
	}
	ps->top--;
	ps->launth--;
	return *(ps->top);
}

/**
 * @brief 销毁队列
 *
 */
void stackdestroy(stack *ps)
{
	free(ps->base);
	ps->base = ps->top = NULL;
	ps->launth = 0;
}
