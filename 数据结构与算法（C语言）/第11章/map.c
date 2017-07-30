#define _CRT_SECURE_NO_WARNINGS
#include "global.h"
#include "snack.h"
#include "food.h"
#include "map.h"
#include <stdio.h>
#include <stdlib.h>

static FILE *fp = NULL;
volatile enum EGameStatus status = GAME_LOOP;

void LoadMap(int scene)
{
	int i, j;
	char str[MAX_LENGTH] = "";

	sprintf(str, "Map\\%d.map", scene);
	fp = fopen(str, "r");
	fscanf(fp, "%d%d", &width, &height);

	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			fscanf(fp, "%d", &map[j][i]);
			mapTemp[j][i] = map[j][i];
		}
	}
	fclose(fp);
	fp = NULL;
}


void PreviewMap()
{
	int i, j;
	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			map[i][j] = mapTemp[i][j];
		}
	}

	Snack *pSnack = pHeader;
	map[pSnack->x][pSnack->y] = MAP_HEAD;
	pSnack = pSnack->pNext;
	while (pSnack)
	{
		map[pSnack->x][pSnack->y] = MAP_BODY;
		pSnack = pSnack->pNext;
	}
	map[food.x][food.y] = food.foodKind;
}

void DisplayMap()
{
	int i, j;

	system("cls");
	printf("                 传智案例\n\n");
	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			if (i==0||j==0)
			{
				printf("回");
				continue;
			}
			switch (map[j][i])
			{
			case MAP_ROAD:
				printf("　");
				break;
			case MAP_BODY:
				printf("□");
				break;
			case MAP_HEAD:
				printf("○");
				break;
			case MAP_FOOD_NORMAL:
				printf("▲");
				break;

			case MAP_FOOD_ACCELERATE:
				printf("◆");
				break;
			case MAP_FOOD_SHORTEN:
				printf("★");
				break;
			case MAP_OBSTACLE:
				printf("╬");
				break;
			}
		}
		printf("回");

		switch (i)
		{
		case 3:
			printf("\t您的得分是：%d", snackLength);
			break;


		case 7:
			printf("\t本关过关蛇长需要10");
			break;
		case 8:
			printf("\t目前蛇长度是：%d", snackLength);
			break;
		case 9:
			printf("\t距过关还需的长度：%d", 10 - snackLength);
			break;

		case 13:
			switch (food.foodKind)
			{
			case MAP_FOOD_NORMAL:
				printf("\t出现的食物为：健康食物！");
				break;
			case MAP_FOOD_ACCELERATE:
				printf("\t出现的食物为：有毒食物！");
				break;
			case MAP_FOOD_SHORTEN:
				printf("\t出现的食物为：致幻食物！");
				break;
			default:
				break;
			}
			break;

		case 14:
			switch (food.foodKind)
			{
			case MAP_FOOD_NORMAL:
				printf("  效果：吃后增长1，健康快乐成长！");
				break;
			case MAP_FOOD_ACCELERATE:
				printf("  效果：吃后增长1，但是蛇速变快！");
				break;
			case MAP_FOOD_SHORTEN:
				printf("  效果：吃后减短1，并且蛇速变慢！");
				break;
			default:
				break;
			}
			break;

		default:
			break;
		}
		
		printf("\n");
	}
	for (j = 0; j <= width; j++)
		printf("回");
	printf("\n");
}
