//蛇
#pragma once

enum EDirection
{
	
	SNACK_UP,		// W
	SNACK_LEFT,		// A
	SNACK_DOWN,	// S
	SNACK_RIGHT	// D
};
// type declaration
typedef struct Snack
{
	int x;
	int y;
	struct Snack *pNext;
}Snack;

enum ESnakeStutas //蛇吃了食物后的状态
{
	SnakeNormal = 1,
	SnakeShorten,
	SnakeAccelerate
};
int snackLength;					// 蛇的长度
Snack *pHeader, *pTail;				// 蛇头、蛇尾
enum EDirection direction;	        // 蛇的移动方向
enum ESnakeStutas SnakeStutas;		//蛇吃了食物后的状态

// 初始化蛇
Snack* SnackInit();
// 链表蛇移动（多线程）
void SnackMove();
// 头插法链表增长
Snack* SnackInsert();
// 某个具体关卡中的游戏结束
void SnackDestroy();

void  SnackNormalFn();//吃了正常食物
Snack*  SnackShorten();//吃了有毒食物，蛇缩短
void SnackAccelerate();//吃了致幻食物，蛇加速移动
