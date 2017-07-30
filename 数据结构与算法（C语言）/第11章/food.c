#include "global.h"
#include "random.h"
#include "food.h"
#include "map.h"

static BOOL bIsExisted = FALSE;
//确定食物种类
enum EMap FoodKindFn()
{
	int xx = GetRandomNumber(1, 10);
	if (xx > 0 && xx <=8)
	{
		return MAP_FOOD_NORMAL;
	}
	else if (xx == 9)
	{
		return MAP_FOOD_ACCELERATE;
	}
	else
	{
		return MAP_FOOD_SHORTEN;
	}
}

//创建食物
Food FoodCreate()
{
	int x, y;
	BOOL result;
	if (bIsExisted)
		return food;
	do
	{
		result = TRUE;
		x = GetRandomNumber(0, width - 1);
		y = GetRandomNumber(0, height - 1);
		if (map[x][y] != MAP_ROAD || x == 0 || y == 0)
		{
			result = FALSE;
		}
	} while (!result);

	bIsExisted = TRUE;
	food.x = x;
	food.y = y;
	food.foodKind = FoodKindFn();

	return food;
}


//释放食物
void FoodRelease()
{
	if (bIsExisted)
	{
		bIsExisted = FALSE;
		FoodCreate();
	}
}
