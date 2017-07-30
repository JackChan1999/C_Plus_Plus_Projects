#include "global.h"
#include "random.h"
#include <stdlib.h>
#include <time.h>

static BOOL bIsInit = FALSE;	// 限定本文件内使用
//初始化随机数系统，以时间为种子
void InitRandomSystem()
{
	if (!bIsInit)
	{
		time_t t;
		bIsInit = TRUE;
		srand((unsigned)time(&t));
	}
}
//获取一个随机数
int GetRandomNumber(int leftVal, int rightVal)
{
	return rand() % (rightVal - leftVal + 1) + leftVal;
}
