#pragma once

enum EMap
{
	MAP_ROAD = 1,
	MAP_BODY,
	MAP_HEAD,
	MAP_FOOD_NORMAL,
	MAP_OBSTACLE,
	MAP_FOOD_ACCELERATE,
	MAP_FOOD_SHORTEN
};

enum EGameStatus //游戏状态
{
	GAME_LOOP,
	GAME_VICTORY,
	GAME_FAILURE
};

int width, height;					 // 地图的长和宽
volatile enum EGameStatus status;	 // 游戏状态
int map[MAX_LENGTH][MAX_LENGTH];	 // 地图最大容量为 32 * 32
int mapTemp[MAX_LENGTH][MAX_LENGTH]; // 地图最大容量为 32 * 32
int selectNum;						 // 所选关卡

// 地图预处理
void PreviewMap();
// 载入地图
void LoadMap(int scene);
// 地图显示（多线程）
void DisplayMap();
