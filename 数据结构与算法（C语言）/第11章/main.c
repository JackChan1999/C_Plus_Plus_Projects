#include "global.h"
#include "map.h"
#include "food.h"
#include "snack.h"
#include "random.h"
#include <stdio.h>
#include <conio.h>
#include <process.h>//windows线程头文件
#include <windows.h>//获取键盘输入的头文件

void InitGame(int n)
{
	LoadMap(n); //加载地图
	SnackInit(); //蛇初始化
	PreviewMap();
	FoodCreate(); //创建食物
	PreviewMap(); //预处理地图
	DisplayMap(); //显示地图
}

void MainLoop(void *param)//游戏的子循环，获取键盘输入
{
	char ch;
	while (status == GAME_LOOP)//该线程执行读取用户输入功能
	{
		ch = _getch(); //获取键盘输入
		switch (ch)
		{
		case 'w': 
		case 'W':
			direction = SNACK_UP; //向上移动
			break;
		case 'a':
		case 'A':
			direction = SNACK_LEFT; //向左移动
			break;
		case 's':
		case 'S':
			direction = SNACK_DOWN; //向下移动
			break;
		case 'd':
		case 'D':
			direction = SNACK_RIGHT; //向右移动
			break;
		default: 
			break;
		}
	}
}

void Failure() //闯关失败，打印游戏结束界面
{
	int i, tmp;
	system("cls");
	printf("\n\n\n\n");
	for (i = 0; i < CONSOLE_MAX_WIDTH; i++) //打印第一排“#”符号
		printf("#"); 

	tmp = CONSOLE_MAX_WIDTH - 30;
	for (i = 0; i < tmp / 2; i++)
		printf(" ");
	printf("很抱歉，你失败了！请再次开启游戏\n"); //打印结束提示

	for (i = 0; i < CONSOLE_MAX_WIDTH; i++) //打印第二排“#”符号
		printf("#");
	system("pause");
}

void VictoryFn() //打印胜利过关界面
{
	int i, tmp;
	system("cls");
	printf("\n\n\n\n");
	for (i = 0; i < CONSOLE_MAX_WIDTH; i++)
		printf("#");

	tmp = CONSOLE_MAX_WIDTH - 30;
	for (i = 0; i < tmp / 2; i++)
		printf(" ");
	printf("恭喜您，顺利进入第%d关,继续愉快地玩耍\n", snackLength);

	for (i = 0; i < CONSOLE_MAX_WIDTH; i++)
		printf("#");
	Sleep(500);
}


int main()
{	
	HANDLE hThread;
	hThread = (HANDLE)_beginthread(MainLoop, 0, NULL);//创建一个子线程
	int selectNum = 1;
	InitRandomSystem();//初始化随机数系统
AA:
	InitGame(selectNum);//根据随机选的关卡数初始化游戏
	
	while (status == GAME_LOOP)//状态一直是GAME_LOOP时，一直执行
	{
		switch (SnakeStutas)
		{
		case SnakeShorten:
			Sleep(DELAY_TIME_SHORTEN);//显示完地图后，停顿DELAY_TIME时间
			SnackMove();//蛇正常移动（为了游戏的健壮性）
			break;
		case SnakeNormal:
			Sleep(DELAY_TIME);//显示完地图后，停顿DELAY_TIME时间	
			SnackMove();//蛇正常移动（为了游戏的健壮性）
			break;
		case SnakeAccelerate:
			Sleep(DELAY_TIME_ACCELERATE);//显示完地图后，停顿DELAY_TIME时间
			SnackMove();//蛇正常移动（为了游戏的健壮性）
			break;
		default:
			SnackMove();//蛇正常移动（为了游戏的健壮性）
			break;
		}

		PreviewMap();//预处理地图
		DisplayMap();//显示地图

	}
	
	if (status == GAME_FAILURE)//游戏失败
	{
		Failure();//退出
		SnackDestroy();

	}
	else if (status == GAME_VICTORY)
	{
		VictoryFn();
		status = GAME_LOOP;
		selectNum = selectNum % 3+1;
 		goto AA;
	}
	
}
