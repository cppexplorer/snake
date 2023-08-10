#define _CRT_SECURE_NO_WARNINGS
#include "snake.h"

//主程序
int main(void)
{
	CONSOLE_CURSOR_INFO cci;
	cci.dwSize = sizeof cci;
	cci.bVisible = FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cci);
	//播种随机种子
	srand(time(NULL));
	drawWall();
	initSnake();
	initFood();
	initUI();

	playgame();
	
	//打印分数和排行榜
	EndGame();

	system("cls");
	WriteToRank();
	ReadRank();
	printf("输入0清空历史记录，输入其他字符结束游戏\n");
	
	char ch =0;
	scanf(" %c", &ch);
	if (ch == '0') {
		FILE* pf = fopen("rank.txt", "w");
		fclose(pf);
	}
	putchar(ch);
	system("pause");
	return EXIT_SUCCESS;
}

void eatfood() {
	//if (snake.body[0].x == food.x && snake.body[0].y == food.y) {
	snake.size++;
	initFood();
	score += 10;
	//accelerate();
}

void playgame() {
	char key = 'd';
	
	while (!IsDead()) {
		
		COORD coord = { 0 };
		coord.X = lastX;
		coord.Y = lastY;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
		putchar(' ');

		initUI();
		
		get_input(&key);

		//蛇头吃食物
		if (((food.x == snake.body[0].x) && (food.y == snake.body[0].y))) {

			//食物消失
			initFood();

			//身体增长
			snake.size++;

			//加分
			score += 100;
		}

		lastX = snake.body[snake.size - 1].x;
		lastY = snake.body[snake.size - 1].y;
		

		//蛇移动
		for (size_t i = snake.size - 1; i > 0; i--)
		{
			snake.body[i].x = snake.body[i - 1].x;
			snake.body[i].y = snake.body[i - 1].y;

		}
		
		snake.body[0].x += kx;
		snake.body[0].y += ky;


		int speed = snake.size - 2;

		if (100 - speed * 3 > 50) {
			Sleep(100-speed*3);

		}
		//system("cls");

	}
	return;
}

int IsDead() {
	int a = ((snake.body[0].x < 0) || (snake.body[0].x > WIDTH));
	for (int i = 1; i < snake.size; i++) {
		if ((snake.body[0].x == snake.body[i].x) && (snake.body[0].y == snake.body[i].y)) {
			a = 1;
		}
	}
	if ((snake.body[0].y < 0) || (snake.body[0].y > HEIGHT)) {
		a = 1;
	}

	return a;
}

void get_input(char* key) {
	//接受输入

	if (_kbhit()) {
		*key = _getch();
	}

	switch (*key) {
	case'w':
		if (ky != 1) {
			kx = 0; ky = -1;
		}
		break;
	case'a':
		if (kx != 1) {
			kx = -1; ky = 0;
		}
		break;
	case's':
		if (ky != -1) {
			kx = 0; ky = 1;
		}
		break;
	case'd':
		if (kx != -1) {
			kx = 1; ky = 0;
		}
		break;
	default: break;
	}



}

void initUI() {
	
	COORD coord = { 0 };
	//画蛇
	for (size_t i = 0; i < snake.size; i++)
	{
		coord.X = snake.body[i].x;
		coord.Y = snake.body[i].y;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

		if (i) {
			putchar('*');
		}

		else {
			putchar('@');
		}
	}
	DrawFood();

	coord.X = 0;
	coord.Y = HEIGHT + 2;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void DrawFood() {
	COORD coord = { 0 };
	coord.X = food.x;
	coord.Y = food.y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	putchar('#');
}

//定义初始化蛇函数
void initSnake(void) {
	//初始化蛇头
	snake.body[0].x = WIDTH / 2;
	snake.body[0].y = HEIGHT / 2;

	//初始化蛇身（一节身体）
	snake.body[1].x = WIDTH / 2 - 1;;
	snake.body[1].y = HEIGHT / 2;

	//设定蛇的大小
	snake.size = 2;

	return;
}

void initFood(void) {
	while (1) {
		food.x = rand() % WIDTH;
		food.y = rand() % HEIGHT;
		int IsSame = 0;
		for (int i = 0; i < snake.size; i++) {
			if ((food.x == snake.body[i].x) && (food.y == snake.body[i].y)) {
				IsSame = 1;
				break;
			}
		}
		if (!IsSame) {
			break;
		}
	}
	return;
}

void drawWall() {
	for (size_t i = 0; i <= HEIGHT; i++)
	{
		for (size_t j = 0; j <= WIDTH; j++)
		{
			if (j == WIDTH) {
				printf("|");
			}
			else if (i == HEIGHT) {
				printf("_");
			}
			else {
				printf(" ");
			}
		}
		printf("\n");
	}
		
}

void EndGame() {
	COORD coord = { 0 };
	coord.X = 0;
	coord.Y = HEIGHT+1;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	printf("\n游戏结束！您本次得分为%d\n\n", score);
}

void WriteToRank() {

	printf("请输入您的姓名，以保存在排行榜中");

	char str[100] = { 0 };
	scanf("%s", str);

	FILE* fp = fopen("rank.txt", "ab");
	if (fp == NULL) {
		perror("fail to load the rank");
		return;
	}

	fwrite(str, 1, sizeof str, fp);
	fwrite(&score, 1, sizeof (int), fp);

	fclose(fp);
}

void ReadRank() {
	FILE* fp = fopen("rank.txt", "rb");

	if (fp == NULL) {
		perror("fail to load the rank");
		return;
	}

	char str[100] = { 0 };
	int SCORE = 0;
	printf("历史记录：\n");
	while (!feof(fp)) {
		fread(str,1,sizeof str,fp);
		fread(&SCORE, 1, sizeof(int), fp);
		printf("%s得分%d\n", str, SCORE);
	}
	

}