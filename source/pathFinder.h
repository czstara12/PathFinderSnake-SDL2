/**
 * @file pathFinder.h
 * @author starstory
 * @brief
 * @version 0.1
 * @date 2023-11-26
 *
 * @copyright Copyright (c) 2023
 *
 */
#pragma once
#ifndef AI_H
#define AI_H

#include "snake.h"

typedef struct node
{
    struct node *parent;
    int x, y;
    float cost;
} node;

#endif // !AI_H