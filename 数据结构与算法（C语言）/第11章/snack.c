#include <malloc.h>
#include <windows.h>
#include "global.h"
#include "snack.h"
#include "food.h"
#include "map.h"

Snack* SnackInit()
{
	direction = SNACK_RIGHT;
	snackLength = INIT_SNACK_LEN;
	int cnt = INIT_SNACK_LEN ;//计算蛇身长度for循环的边界
	SnakeStutas = SnakeNormal;
	//蛇头创建
	pHeader = pTail = (Snack *)malloc(sizeof(Snack));
	pTail->x = cnt;
	pTail->y = 1;

	//蛇身创建
	while (cnt-- > 1)
	{
		pTail->pNext = (Snack *)malloc(sizeof(Snack));
		pTail = pTail->pNext;
		pTail->x = cnt;
		pTail->y = 1;
	}
	pTail->pNext = NULL;
	return pHeader;
}


void SnackMove()
{
	BOOL result;
	Snack *pSnack = NULL;
	int x = pHeader->x, y = pHeader->y, newX = x, newY = y;
	switch (direction)
	{
	case SNACK_UP:
		result = SnackJudge(x, y - 1);
		if (result == TRUE)
			newY = y - 1;
		break;
	case SNACK_LEFT:
		result = SnackJudge(x - 1, y);
		if (result == TRUE)
			newX = x - 1;
		break;
	case SNACK_DOWN:
		result = SnackJudge(x, y + 1);
		if (result == TRUE)
			newY = y + 1;
		break;
	case SNACK_RIGHT:
		result = SnackJudge(x + 1, y);
		if (result == TRUE)
			newX = x + 1;
		break;
	}
	if (result == TRUE)
	{
		Snack *pTemp = pHeader;
		pTail->pNext = pHeader;
		map[pTail->x][pTail->y] = MAP_ROAD;
		while (pTemp->pNext != pTail)
			pTemp = pTemp->pNext;
		pTemp->pNext = NULL;
		pHeader = pTail;
		pHeader->x = newX;
		pHeader->y = newY;
		map[pTail->x][pTail->y] = MAP_ROAD;
		pTail = pTemp;
	}
	else if (result == FALSE)
		status = GAME_FAILURE;
}

// 链表蛇事件判定
static BOOL SnackJudge(int x, int y)
{
	Snack *pSnack = pHeader;
	if (x >= width || x <= 0 || y >= height || y <= 0)
		return FALSE;
	switch (map[x][y])
	{
		case MAP_ROAD:
			return TRUE;
		case MAP_BODY:
			while (pSnack && (pSnack->x != x || pSnack->y != y))
				pSnack = pSnack->pNext;
			if (!pSnack || pSnack == pTail)
				return TRUE;
			return FALSE;
		case MAP_FOOD_NORMAL:
			SnackNormalFn();
			FoodRelease();
			return OTHER;
			break;
		case MAP_FOOD_SHORTEN:
			SnackShorten();
			FoodRelease();
			return OTHER;
			break;
		case MAP_FOOD_ACCELERATE:
			SnackAccelerate();
			FoodRelease();
			return OTHER;
			break;
		case MAP_OBSTACLE:
		default:
			return FALSE;
	}
}

// 头插法链表增长
Snack* SnackInsert()
{
	Snack *pSnack = (Snack *)malloc(sizeof(Snack));
	pSnack->x = food.x;
	pSnack->y = food.y;
	pSnack->pNext = pHeader;
	pHeader = pSnack;
	if (++snackLength == VICTORE_SNACK_LEN)
		status = GAME_VICTORY;
	
	return pHeader;
}

void  SnackNormalFn()
{
	SnackInsert();
	SnakeStutas = SnakeNormal;
}

Snack * SnackShorten()
{
	if (snackLength <= 2)
	{
		status = GAME_FAILURE;
		return pHeader;
	}
	Snack *pTempHeader = pHeader;
	Snack *pTempTail = pTail;
	Snack * pTempBehTail = pTail;

	while ((pTempHeader->pNext)->pNext != pTempTail)
	{
		pTempHeader = pTempHeader->pNext;
	}
	pTail = pTempHeader;
	pTempBehTail = pTempHeader->pNext;
	pTail->pNext = NULL;

	pTempBehTail->x = food.x;
	pTempBehTail->y = food.y;
	pTempBehTail->pNext = pHeader;
	pHeader = pTempBehTail;

	free(pTempTail);
	snackLength--;

	SnakeStutas = SnakeShorten;
	return pHeader;
}

void SnackAccelerate()
{
	SnackInsert();
	SnakeStutas = SnakeAccelerate;
}

// 某个具体关卡中的游戏结束
void SnackDestroy()
{
	Snack *pSnack = pHeader;
	while (pHeader)
	{
		pHeader = pHeader->pNext;
		free(pSnack);
		pSnack = NULL;
	}
	pTail = NULL;
}
