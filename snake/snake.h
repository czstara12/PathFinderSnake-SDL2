#pragma once
#ifndef SNAKE_H
#define SNAKE_H
#include <stdlib.h>
#include <time.h>
#include <SDL.h>

#define WIDTH 25
#define HEIGHT 25//����

enum Direction { d_up, d_down, d_left, d_right ,d_error}; // ����

void display();                 // ��ʾ
int move(int x, int y);//�ߵ��ƶ�
void newfood();//ˢ��ʳ��
int initialize();
int game();
int gamewithai();

#endif