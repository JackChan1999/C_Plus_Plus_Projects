#pragma once

// type declaration
typedef struct Food
{
	int x;
	int y;
	enum EMap foodKind;
}Food;

Food food;		// 食物

// 创建食物
Food FoodCreate();
// 食物被吃掉
void FoodRelease();