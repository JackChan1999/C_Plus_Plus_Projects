#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef void SeqList;
typedef void SeqListNode;

typedef struct _tag_SeqList  //头结点，记录表的信息
{
	int capacity;  //表容量
	int length;    //表长度
	int * node;    //node[capacity]，为指针数组
}TSeqList;

//创建顺序表
SeqList* SeqList_Create(int capacity) //返回值为SeqList*类型，即顺序表的地址
{
	int ret;
	TSeqList *temp = NULL;
	temp = (TSeqList*)malloc(sizeof(TSeqList));  //为头结点分配空间
	if (temp == NULL)
	{
		ret = 1;
		printf("func SeqList_Create() error:%d\n", ret);
		return NULL;
	}
	memset(temp, 0, sizeof(TSeqList));
	temp->capacity = capacity;
	temp->length = 0;
	temp->node = (int*)malloc(sizeof(void*)*capacity); //分配一个指针数组
	if (temp->node == NULL)
	{
		ret = 2;
		printf("func SeqList_Create() error:%d\n", ret);
		return NULL;
	}
	return temp;  //将分配好的顺序表的地址扔出去
}

//求顺序表容量
int SeqList_Capacity(SeqList* list) //参数为顺序表地址
{
	TSeqList *temp = NULL;
	if (list == NULL) //作健壮性判断
	{
		return;
	}
	temp = (TSeqList *)list;
	return temp->capacity;
}

//获取顺序表长度
int SeqList_Length(SeqList* list)
{
	TSeqList *temp = NULL;
	if (list == NULL)
	{
		return;
	}
	temp = (TSeqList *)list;
	return temp->length;
}

//插入元素
int SeqList_Insert(SeqList* list, SeqListNode* node, int pos)
{                     //参数为顺序表地址，要插入的元素地址，插入位置
	int i;
	TSeqList *temp = NULL;
	//先作健壮性判断
	if (list == NULL || node == NULL) //如果顺序表为空，或者结点为空
	{
		return -1;
	}
	temp = (TSeqList *)list;
	//如果顺序表已满
	if (temp->length >= temp->capacity)
	{
		return -2;
	}

	//容错
	if (pos > temp->length) //如果给出的pos在长度后，即中间有空余，
		pos = temp->length; //就修正到最后一个元素后面

	for (i = temp->length; i > pos; i--)  //将插入位置的元素依次后移动
	{
		temp->node[i] = temp->node[i - 1];
	}
	temp->node[i] = (int)node; //然后在空出的位置插入新元素结点
	temp->length++; //插入成功后，长度加1
	return 0;
}

//删除元素
SeqList* SeqList_Delete(SeqList* list, int pos)
{
	int i;
	//先作健壮性判断
	TSeqList * tlist = NULL;
	SeqListNode * temp = NULL;
	tlist = (TSeqList *)list;
	if (list == NULL || pos < 0 || pos >= tlist->capacity)
	{
		printf("SeqList_Delete() error\n");
		return NULL;
	}
	temp = (SeqListNode *)tlist->node[pos]; //要删除的元素

	for (i = pos + 1; i < tlist->length; i++) //将删除元素位置后的所有元素向前移动
	{
		tlist->node[i - 1] = tlist->node[i];
	}

	tlist->length--; //删除元素后，长度要减
	return temp;
}

SeqList* SeqList_Get(SeqList* list, int pos)
{
	//先作健壮性判断
	TSeqList * tlist = NULL;
	SeqListNode * temp = NULL;
	tlist = (TSeqList *)list;
	if (list == NULL || pos < 0 || pos >= tlist->capacity)
	{
		printf("SeqList_Get() error\n");
		return NULL;
	}
	temp = (SeqListNode *)tlist->node[pos]; //将表中pos位置的结点指针赋给temp
	return temp;
}

//清空顺序表
void SeqList_Clear(SeqList* list)
{
	TSeqList *temp = NULL;
	if (list == NULL)
	{
		return;
	}
	temp = (TSeqList *)list;
	temp->length = 0;
	memset(temp->node, 0, (temp->capacity * sizeof(void*))); //将顺序表全部归0
	return;
}
//销毁顺序表
void SeqList_Destory(SeqList* list)
{
	TSeqList* temp = NULL;
	if (list == NULL)  //如果参数顺序表为空
	{
		return;
	}
	temp = (TSeqList *)list;
	if (temp->node != NULL)
	{
		free(temp->node); //先释放头结点中的指针数组
	}
	free(temp); //再释放头结点
	return;
}
