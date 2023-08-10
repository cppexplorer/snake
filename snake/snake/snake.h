#pragma once
#ifndef __SNAKE_H__
#define __SNAKE_H__
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <Windows.h>

#include <conio.h>

#define WIDTH 60
#define HEIGHT 20

//һ������
typedef struct BODY {
	int x;
	int y;
};

//������
struct SNAKE {
	struct BODY body[WIDTH * HEIGHT];
	int size;
}snake;

//ʳ��
struct FOOD {
	int x;
	int y;
}food;

//����
int score = 0;

int kx = 0;int ky = 0;

int lastX = 0; int lastY = 0;
//��������
void initSnake();
void initFood();
void initUI();
void DrawFood();
void eatfood();
void playgame();
int IsDead();
void get_input(char*);
void drawWall();
void EndGame();
void ReadRank();
void WriteToRank();
#endif

