#pragma once
#ifndef SNAKE_H
#define SNAKE_H
#include <stdlib.h>
#include <time.h>
#include <SDL.h>

#define WIDTH 25
#define HEIGHT 25//长宽

enum Direction { d_up, d_down, d_left, d_right ,d_error}; // 方向

void display();                 // 显示
int move(int x, int y);//蛇的移动
void newfood();//刷新食物
int initialize();
int game();
int gamewithai();

#endif