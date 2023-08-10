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

//一个身体
typedef struct BODY {
	int x;
	int y;
};

//整个蛇
struct SNAKE {
	struct BODY body[WIDTH * HEIGHT];
	int size;
}snake;

//食物
struct FOOD {
	int x;
	int y;
}food;

//分数
int score = 0;

int kx = 0;int ky = 0;

int lastX = 0; int lastY = 0;
//声明函数
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

