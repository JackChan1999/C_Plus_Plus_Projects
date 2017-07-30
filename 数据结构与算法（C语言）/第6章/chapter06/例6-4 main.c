#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct BitNode
{
	char data;
	struct BitNode* lchild, *rchild;
}BitNode;

//中序遍历
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

//#号法创建二叉树
BitNode* BitNode_Create()
{
	BitNode* temp = NULL;
	char ch;
	scanf("%c", &ch);
	if (ch == '#') //如果输入#号，则返回NULL
	{
		temp = NULL;
		return temp;
	}
	else
	{
		temp = (BitNode*)malloc(sizeof(BitNode)); //为结点分配空间
		if (temp == NULL)
			return NULL;
		temp->data = ch;
		temp->lchild = NULL;
		temp->rchild = NULL;
		//创建结点的左右子树
		temp->lchild = BitNode_Create();
		temp->rchild = BitNode_Create();
		return temp;
	}
}

//释放树:先释放左子树，再释放右子树，最后释放根结点
void BitNode_Free(BitNode* T)
{
	if (T == NULL)
		return;
	if (T->lchild != NULL)
	{
		BitNode_Free(T->lchild); //释放左子树
		T->lchild = NULL;
	}
	if (T->rchild != NULL)
	{
		BitNode_Free(T->rchild); //释放右子树
		T->rchild = NULL;
	}
	free(T);
}

int main()
{
	BitNode* T = NULL;
	printf("请输入树的结点元素值：\n");
	T = BitNode_Create(); //创建树

	inOrder(T); //中序遍历此树
	printf("\n");
	BitNode_Free(T);
	printf("二叉树释放成功！\n");

	system("pause");
	return 0;
}
