#ifndef ODAY_HASH_H
#define ODAY_HASH_H

// 引入oday库标准头
#include <stdio.h>
#include "oday_std.h"

/* Hash节点结构体 */
typedef struct Oday_Hash_Node oday_hash_node;
struct Oday_Hash_Node{
	char *key;								// 哈希键名
	naked_type_constraints data;			// 哈希键值
	oday_hash_node *next;					// 下一节点
};

/* Hash表结构体 */
typedef struct Oday_Hash_Table* oday_hash_headle;
typedef struct Oday_Hash_Table oday_hash_table;
typedef struct Oday_Hash_Table{
	unsigned int length;					// 哈希表长度
	data_type type;							// 哈希表类型
	oday_hash_node **data;					// 哈希表节点
	unsigned int(*hash_code)(char *str);	// 哈希code
};

/* Hash表迭代器 */
typedef struct Oday_Hash_Iterator oday_hash_iterator;
struct Oday_Hash_Iterator{
	oday_hash_headle table;					// 哈希表句柄
	oday_hash_node **code;					// 哈希表节点
	oday_hash_node *node;					// 哈希表项目
};

/**
* 创建Hash表
* @param type			表类型
* @param length			表长度
* @param hash_code		散列算法
* @return 创建成功返回Hash表句柄
* @return 创建失败返回NULL
*/
oday_hash_headle oday_hash_create(data_type type, unsigned int length, unsigned int(*hash_code)(char *str));

/**
* 销毁Hash表
*/
void oday_hash_destory(oday_hash_headle hash_table);

/**
* 为Hash表赋值
* @param hash_table		哈希表句柄
* @param key			存放的键名
* @param value			要放的键值
**/
void oday_hash_set(const oday_hash_headle hash_table, const char *key, const void *value);

/**
* 查看一个Hash表中的值
* @param hash_table		哈希表句柄
* @param key			存放的键名
* @return 数据存放的地址,为空表示节点不存在
**/
void *oday_hash_get(const oday_hash_headle hash_table, const char *key);

/**
* 弹出一个Hash键
* @param hash_table		哈希表句柄
* @param key			存放的键名
* @param result			存放结果
**/
void oday_hash_pop(const oday_hash_headle hash_table, const char *key, void *result);

/**
 * 初始化Hash表迭代器
 * @param hash_table	哈希表句柄
 * @param iterator		哈希迭代器
 */
void oday_hash_iterator_init(oday_hash_headle hash_table, oday_hash_iterator *iterator);

/* SDBM Hash 算法 */
unsigned int oday_SDBMHash(char *str);

/* RS Hash 算法 */
unsigned int oday_RSHash(char *str);

/* JS Hash 算法 */
unsigned int oday_JSHash(char *str);

/* P.J.Weinberger Hash 算法 */
unsigned int oday_PJWHash(char *str);

/* ELF Hash 算法 */
unsigned int oday_ELFHash(char *str);

/* BKDR Hash 算法 */
unsigned int oday_BKDRHash(char *str);

/* DJB Hash 算法 */
unsigned int oday_DJBHash(char *str);

/* AP Hash 算法 */
unsigned int oday_APhash(char *str);

#endif