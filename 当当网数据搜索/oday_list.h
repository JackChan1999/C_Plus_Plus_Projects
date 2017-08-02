#ifndef ODAY_LIST_H
#define ODAY_LIST_H

#include "oday_std.h"

/* 链接方式 */
typedef enum Link_Type link_type;
enum Link_Type{
	SINGLE,									// 单项链表
	BOTH,									// 双向链表
	SINGLE_LOOP,							// 单循环链表
	BOTH_LOOP,								// 双循环链表
};

/* 单链表节点 */
typedef struct Oday_Single_List_Node oday_single_list_node;
struct Oday_Single_List_Node{
	naked_type_constraints data;			// 链表键值
	oday_single_list_node *next;			// 链表后继
};

/* 双链表节点 */
typedef struct Oday_Both_List_Node oday_both_list_node;
struct Oday_Both_List_Node{
	naked_type_constraints data;			// 链表键值
	oday_both_list_node *prior;				// 链表前驱
	oday_both_list_node *next;				// 链表后继
};

/* 链表节点 */
typedef union Oday_List_Node oday_list_node;
union Oday_List_Node{
	oday_single_list_node *single;			// 单项链表
	oday_both_list_node *both;				// 双向链表
}; 

/* 单链表 */
typedef struct Oday_List_Headle* oday_list_headle;
struct Oday_List_Headle{
	data_type data_type;					// 哈希表类型
	link_type link_type;					// 链接方式
	unsigned int length;					// 链表总长度
	oday_list_node head;					// 链表头结点
	oday_list_node tail;					// 链表尾结点
	oday_list_node nonius;					// 链表指针
};

oday_list_headle oday_list_create(data_type data_type, link_type link_type);

/**
* 在链表头部压入一个元素
* @param list			链表句柄
* @param value			元素值
*/
void oday_list_stick(oday_list_headle list, void *value);

/**
* 从链表头部弹出一个元素
* @param list			链表句柄
* @param value			链表值
*/
boolen oday_list_shift(oday_list_headle list, void *value);

/**
* 在链表尾部压入一个元素
* @param list			链表句柄
* @param value			元素值
*/
void oday_list_push(oday_list_headle list, void *value);

/**
* 从链表尾部弹出一个元素
* @param list			链表句柄
* @param value			链表值
*/
boolen oday_lish_pop(oday_list_headle list, void *value);

/* 读取一个链表节点内容 */
void *oday_list_get(oday_list_headle list);

/* 将链表指针复位（定位到链表开头） */
void oday_list_rewind(oday_list_headle list);

/* 移动链表指针 */
void *oday_list_next(oday_list_headle list);

#endif