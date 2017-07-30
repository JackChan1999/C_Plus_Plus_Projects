#include "Mat.h"
//创建一个十字链表，并使用数组a初始化
void cmatCreate(MatNode *&hm, ElemType a[ROW][COL])
{
	int i, j;
	//头结点指针
	MatNode *h[Max], *p, *q, *r;
	hm = (MatNode*)malloc(sizeof(MatNode));			//矩阵指针hm
	hm->row = ROW;									//初始化行
	hm->col = COL;									//初始化列
	r = hm;
	for (i = 0; i < Max; i++)
	{
		h[i] = (MatNode*)malloc(sizeof(MatNode));
		h[i]->right = h[i];							//构成循环
		h[i]->down = h[i];
		r->tag.link = h[i];							//将头指针链接起来
		r = h[i];
	}
	r->tag.link = hm;								//将指针重新指向矩阵头结点
	for (i = 0; i < ROW; i++)
	{
		for (j = 0; j < COL; j++)
		{
			if (a[i][j] != 0)						//赋值初始化
			{
				p = (MatNode*)malloc(sizeof(MatNode));
				p->row = i;
				p->col = j;
				p->tag.value = a[i][j];
				q = h[i];
				//插入行链表
				while (q->right != h[i] && q->right->col < j)
					q = q->right;
				p->right = q->right;
				q->right = p;
				q = h[j];
				//插入列链表
				while (q->down != h[j] && q->down->row < i)
					q = q->down;
				p->down = q->down;
				q->down = p;
			}
		}
	}
}

void cmatPrint(MatNode *hm)
{
	MatNode *p, *q;
	printf("行 = %d，列 = %d\n", hm->row, hm->col);
	p = hm->tag.link;
	while (p != hm)
	{
		q = p->right;
		while (p != q)
		{
			printf("(%d,%d,%d)\n", q->row + 1, q->col + 1, q->tag.value);
			q = q->right;
		}
		p = p->tag.link;
	}
}