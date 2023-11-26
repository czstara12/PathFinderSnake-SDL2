#include "stack.h"

int stackinit(stack *init)
{
	init->size = defaultStackSize;
	init->base = init->top = (stackType *)malloc(sizeof(stackType) * init->size);
	init->launth = 0;
	return 0;
}
void push(stack *ps, stackType data)
{
	if (ps->launth == ps->size)
	{
		ps->size *= 2;
		stackType *tmp;
		if ((tmp = (stackType *)malloc(sizeof(stackType) * ps->size)) == NULL)
		{
			exit(1);
			return;
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
stackType pop(stack *ps)
{
	ps->top--;
	return *(ps->top);
}