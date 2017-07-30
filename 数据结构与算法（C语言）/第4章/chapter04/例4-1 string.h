#ifndef _STRING_H_
#define _STRING_H_

typedef struct string
{
	char * str;
	int length;
}String;

void strAssign(String* s, char* p); //将p串的值赋值给s
int strLength(String* s); //求串的长度
int strEqual(String* s, String* t);//判断两个串是否相等
int strCompete(String* s, String* t); //比较两串大小
void strConnect(String* s, String* t); //连接两个字符串
void strCopy(String* s, String* t); //将串t复制到串s中
void Insert(String *s, int pos, char* p); //在pos位置插入串p
void Delete(String* s, int pos, int len); //删除pos位置及后面长度为len的串

void print(String* s); //打印串

#endif
