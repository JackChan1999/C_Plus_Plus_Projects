#include <stdio.h>
#include <stdlib.h>
#include "linkstack.h"

//寻找遍历起始结点
BitNode*  GoFarLeft(BitNode* T, LinkStack ls)
{
	if (T == NULL)
		return NULL;
	while (T->lchild != NULL) //左子树不为空，就一直往下寻找
	{
		Push(ls, T);
		T = T->lchild;
	}
	return T;
}

//非递归中序遍历函数
void MyOrder(BitNode* T)
{
	LinkStack ls = Create(); //创建栈
	BitNode* t = GoFarLeft(T, ls);//寻找遍历起始结点
	while (t != NULL)
	{
		printf("%c", t->data); //打印起始结点的值
		//若结点有右子树，重复步骤（1）
		if (t->rchild != NULL)
			t = GoFarLeft(t->rchild, ls); //寻找右子树中的起始结点
		else if (!IsEmpty(ls)) //如果栈不为空
		{
			t = getTop(ls)->data; //回退到栈顶元素结点
			Pop(ls); //栈顶元素弹出
		}
		else
			t = NULL;
	}
}
int main()
{
	BitNode nodeA, nodeB, nodeD, nodeF, nodeI, nodeL; //创建6个结点
	//将结点都初始，这样可以保证没有孩子的结点相应指针批向空
	memset(&nodeA, 0, sizeof(BitNode));
	memset(&nodeB, 0, sizeof(BitNode));
	memset(&nodeD, 0, sizeof(BitNode));
	memset(&nodeF, 0, sizeof(BitNode));
	memset(&nodeI, 0, sizeof(BitNode));
	memset(&nodeL, 0, sizeof(BitNode));
	//给结点赋值
	nodeA.data = 'A';
	nodeB.data = 'B';
	nodeD.data = 'D';
	nodeF.data = 'F';
	nodeI.data = 'I';
	nodeL.data = 'L';
	//存储结点之间的逻辑关系
	nodeA.lchild = &nodeB; //A结点左孩子是B
	nodeA.rchild = &nodeD; //A结点的右孩子是D
	nodeB.rchild = &nodeF; //B结点的右孩子是F
	nodeF.lchild = &nodeL; //F结点的左孩子是L
	nodeD.lchild = &nodeI; //D结点的左孩子是I

	printf("二叉树构建成功！\n");

	printf("非递归中序遍历：");
	MyOrder(&nodeA);

	printf("\n");
	system("pause");
	return 0;
}
