#pragma once
#include <malloc.h>
#include <stdlib.h>
#include <assert.h>

#define defaultStackSize 16
typedef void *stackType;
typedef struct
{
	stackType *base; ///< 栈首
	stackType *top;	 ///< 栈尾(超尾位置)
	int launth;		 ///< 栈长度
	int size;		 ///< 栈可容纳的长度
} stack;

int stackinit(stack *init);
void push(stack *ps, stackType data);
stackType pop(stack *ps);
void stackdestroy(stack *ps);
