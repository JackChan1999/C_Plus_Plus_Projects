#include <stdio.h>
#include <stdlib.h>

typedef struct BitNode
{
	char data;
	struct BitNode* lchild, *rchild;
}BitNode;


//1、先序遍历
void preOrder(BitNode* T)
{
	if (T == NULL)
		return;
	printf("%c", T->data); //打印根节点的值

	//遍历完根节点再遍历左子树
	if (T->lchild != NULL)
		preOrder(T->lchild); //递归调用
	//遍历完左子树再遍历右子树
	if (T->rchild != NULL)
		preOrder(T->rchild);
}

//2、中序遍历
void inOrder(BitNode* T)
{
	if (T == NULL)
		return;
	//先遍历左子树
	if (T->lchild != NULL)
		inOrder(T->lchild); //递归调用

	printf("%c", T->data); //再遍历根节点

	//最后遍历右子树
	if (T->rchild != NULL)
		inOrder(T->rchild);
}

//3、后序遍历
void lastOrder(BitNode* T)
{
	if (T == NULL)
		return;
	//先遍历左子树
	if (T->lchild != NULL)
		lastOrder(T->lchild); //递归调用
	//再遍历右子树
	if (T->rchild != NULL)
		lastOrder(T->rchild);
	printf("%c", T->data); //最后遍历根节点
}

int main()
{
	BitNode nodeA, nodeB, nodeD, nodeF, nodeI, nodeL; //创建6个节点
	//将节点都初始，这样可以保证没有孩子的节点相应指针批向空
	memset(&nodeA, 0, sizeof(BitNode));
	memset(&nodeB, 0, sizeof(BitNode));
	memset(&nodeD, 0, sizeof(BitNode));
	memset(&nodeF, 0, sizeof(BitNode));
	memset(&nodeI, 0, sizeof(BitNode));
	memset(&nodeL, 0, sizeof(BitNode));
	//给节点赋值
	nodeA.data = 'A';
	nodeB.data = 'B';
	nodeD.data = 'D';
	nodeF.data = 'F';
	nodeI.data = 'I';
	nodeL.data = 'L';
	//存储节点之间的逻辑关系
	nodeA.lchild = &nodeB; //A节点左孩子是B
	nodeA.rchild = &nodeD; //A节点的右孩子是D
	nodeB.rchild = &nodeF; //B节点的右孩子是F
	nodeF.lchild = &nodeL; //F节点的左孩子是L
	nodeD.lchild = &nodeI; //D节点的左孩子是I

	printf("二叉树构建成功！\n");

	printf("先序遍历：");
	preOrder(&nodeA);

	printf("\n中序遍历：");
	inOrder(&nodeA);

	printf("\n后序遍历：");
	lastOrder(&nodeA);
	printf("\n");
	system("pause");
	return 0;
}