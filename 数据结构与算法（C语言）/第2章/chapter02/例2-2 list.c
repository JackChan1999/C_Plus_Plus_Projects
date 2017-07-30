#include <stdio.h>
#include <stdlib.h>

struct Header  //头结点
{
	int length; //记录链表大小
	struct Node* next; //指向第一个结点的指针
};
struct Node  //结点
{
	int data; //数据域
	struct Node* next;  //指向下一个结点的指针
};

typedef struct Header pHead; //将struct Header重命名为pHead
typedef struct Node  List;  //将struct Node重命名为List

//创建链表
pHead * createList()//pHead是struct Header的别名，是头结点类型
{
	pHead* ph = (pHead*)malloc(sizeof(pHead)); //为头结点分配内存
	ph->length = 0; //为头结点初始化
	ph->next = NULL;
	return ph; //将头结点地址返回
}
//获取链表大小
int Size(pHead* ph)
{
	if (ph == NULL)
	{
		printf("参数传入有误！");
		return 0;
	}

	return ph->length;
}
//插入
int Insert(pHead* ph, int pos, int val) //在某一个位置插入某一个元素，插入成功返回1；
{
	//先作健壮性判断
	if (ph == NULL || pos < 0 || pos > ph->length)
	{
		printf("参数传入有误！");
		return 0;
	}
	//在向链表中插入元素时，先要找到这个位置
	List* pval = (List*)malloc(sizeof(List)); //先分配一块内存来存储要插入的数据
	pval->data = val;

	List *pCur = ph->next; //当前指针指向头结点后的第一个结点
	if (pos == 0) //插入在第一个位置
	{
		ph->next = pval; //指针断开连接过程
		pval->next = pCur;
	}
	else
	{
		for (int i = 1; i < pos; i++) //找到要插入的位置
		{
			pCur = pCur->next;
		}

		pval->next = pCur->next; //指针断开再连接过程
		pCur->next = pval;
	}

	ph->length++; //增加一个元素，长度要加1
	return 1;
}
//查找
List* find(pHead* ph, int val)  //查找某个元素
{
	//先作健壮性判断
	if (ph == NULL)
	{
		printf("参数传入有误！");
		return NULL;
	}

	//遍历链表来查找元素
	List *pTmp = ph->next;
	do
	{
		if (pTmp->data == val)
		{
			return pTmp;
		}
		pTmp = pTmp->next;
	} while (pTmp->next != NULL); //循环条件是直到链表结尾

	printf("没有值为%d的元素!", val);
	return NULL;
}

//删除
List* Delete(pHead* ph, int val)  //删除值为val的元素，删除成功，返回删除的元素
{
	//先作健壮性判断
	if (ph == NULL)
	{
		printf("链表传入错误！");
		return NULL;
	}

	//找到val值所在结点
	List* pval = find(ph, val);
	if (pval == NULL)
	{
		printf("没有值为%d的元素!", val);
		return NULL;
	}

	//遍历链表去找到要删除结点，并找出其前驱及后继结点
	List *pRe = ph->next;  //当前结点
	List *pCur = NULL;
	if (pRe->data == val)  //如果删除的是第一个结点
	{
		ph->next = pRe->next;
		ph->length--;
		return pRe;
	}
	else //如果删除的是其他结点
	{
		for (int i = 0; i < ph->length; i++)  //遍历链表
		{
			pCur = pRe->next;
			if (pCur->data == val) //找到要删除的元素
			{
				pRe->next = pCur->next; //将被删除元素的上下两个结点连接起来
				ph->length--; //长度减1
				return pCur;  //将被删除的元素结点返回
			}
			pRe = pRe->next;
		}
	}
}

//销毁链表
void Destory(pHead* ph)
{
	List *pCur = ph->next;
	List *pTmp;
	if (ph == NULL)
		printf("参数传入有误！");

	while (pCur->next != NULL)
	{
		pTmp = pCur->next;
		free(pCur); //将结点释放
		pCur = pTmp;
	}
	ph->length = 0; //回到初始化状态
	ph->next = NULL;
}

//遍历链表
void print(pHead *ph)
{
	if (ph == NULL)
	{
		printf("参数传入有误！");
	}
	List *pTmp = ph->next;
	while (pTmp != NULL)
	{
		printf("%d  ", pTmp->data);
		pTmp = pTmp->next;
	}
	printf("\n");
}



