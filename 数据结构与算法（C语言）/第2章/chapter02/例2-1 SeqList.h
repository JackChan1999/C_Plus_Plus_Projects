#ifndef _SEQLIST_H_
#define  _SEQLIST_H_

typedef void SeqList;
typedef void SeqListNode;

SeqList* SeqList_Create(int capacity); //创建顺序表
void SeqList_Destory(SeqList* list);  //销毁顺序表
void SeqList_Clear(SeqList* list);  //清空线性表
int SeqList_Length(SeqList* list);  //获取顺序表长度
int SeqList_Capacity(SeqList* list); //获取顺序表容量
int SeqList_Insert(SeqList* list, SeqListNode* node, int pos); //在pos位置插入元素
SeqList* SeqList_Get(SeqList* list, int pos); //获取pos位置上的元素
SeqList* SeqList_Delete(SeqList* list, int pos);  //删除pos位置的元素

#endif
