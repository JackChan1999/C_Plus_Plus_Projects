#include "gList.h"

//求广义表的长度
int LSLength(LSNode *ls)
{
	if (ls == NULL)
		return 0;
	int n = 0;
	if (ls->tag == 0)			//为单元素时返回0
		return 1;
	ls = ls->value.Lists;		//gls指向广义表的第一个元素
	while (ls != NULL)
	{
		n++;					//累加元素个数
		ls = ls->link;
	}
	return n;
}

//求广义表的深度
int LSDepth(LSNode *ls)
{
	if (ls->tag == 0)					//为单元素时返回0
		return 0;
	int max = 0, dep;
	LSNode *gls = ls->value.Lists;		//gls指向第一个元素 
	if (gls == NULL)					//空表返回1
		return 1;
	while (gls != NULL)				   //不为空遍历表中的每一个元素
	{
		if (gls->tag == 1)			  //元素为子表的情况
		{
			dep = LSDepth(gls);		 //递归调用求出子表的深度
			if (dep > max)		//max为同一层所求过的子表中深度的最大值
				max = dep;
		}
		gls = gls->link;		//使gls指向下一个元素
	}
	return (max + 1);			//返回表的深度
}

//输出广义表ls
void LSDis(LSNode *ls)
{
	if (ls->tag == 0)
		printf("%c", ls->value.data);	//输出原子值
	else
	{
		printf("(");
		if (ls->value.Lists == NULL)
			printf("");
		else
			LSDis(ls->value.Lists);		//递归输出子表
		printf(")");
	}
	if (ls->link != NULL)
	{
		printf(",");
		LSDis(ls->link);
	}
}
//广义表创建
void LSCreate(LSNode** ls, int flag)
{
	char ch;
	ch = getchar();
	if (ch == ')')
		*ls = NULL;
	else if (ch == '(')							//当前字符为左括号时
	{
		*ls = (LSNode*)malloc(sizeof(LSNode));	//创建一个新结点
		(*ls)->tag = 1;						//新结点作为表头结点
		LSCreate(&((*ls)->value.Lists), flag + 1);	//递归构造子表并链接到表头结点
	}
	else if (ch == '\n')
	{
		(*ls)->link = NULL;
		return;
	}
	else
	{
		*ls = (LSNode*)malloc(sizeof(LSNode));	//创建一个新结点
		(*ls)->tag = 0;						//是单元素
		(*ls)->value.data = ch;				//新结点作为单元素结点
	}
	if (flag == 0)
	{
		(*ls)->link = NULL;
		printf("%d\n", flag);
		return;
	}
	ch = getchar();								//取下一个字符	
	if ((*ls) == NULL);								//串未结束，继续构造兄弟结点
	else if (ch == ',')							//当前字符为","
		LSCreate(&((*ls)->link), flag);			//递归构造兄弟结点	
	else									//没有兄弟了，将兄弟指针置为NULL
		(*ls)->link = NULL;
	printf("%d-", flag);
	return;									//返回
}
