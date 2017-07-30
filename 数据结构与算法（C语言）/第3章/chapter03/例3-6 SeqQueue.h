#ifndef _SQQUEUE_H
#define _SQQUEUE_H

#define MAXSIZE 50
typedef struct Queue* SeqQueue;
struct Queue
{
	int front; // 队头
	int rear; // 队尾
	int data[MAXSIZE]; // 数据
};

SeqQueue Create(); // 初始化操作，建立一个空队列Sq
int getLength(SeqQueue Sq); // 返回队列Sq的元素个数(长度）
int IsEmpty(SeqQueue Sq); // 判断队列是否为空
void Insert(SeqQueue Sq, int val);// 入队
int Del(SeqQueue Sq);// 出队
int GetHead(SeqQueue Sq);// 获取队头元素
void Clear(SeqQueue Sq);// 将队列Sq清空
void Destory(SeqQueue Sq); //销毁队列

#endif	//_SQQUEUE_H
