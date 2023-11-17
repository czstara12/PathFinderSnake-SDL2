#pragma once
#ifndef SNAKE_H
#define SNAKE_H

// #include "AI.h"
#include <time.h>
#include <SDL.h>
#include <Windows.h>
#include "AI.h"
#include "public.h"

void display();              // 显示
int moveSnake(int x, int y); // 蛇的移动
void newfood();              // 刷新食物
int initialize();
int gameLoop();
int gamewithai();
void displayt();

#endif