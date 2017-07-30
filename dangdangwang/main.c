#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "oday_hash.h"
#include "oday_list.h"
#include <sys/timeb.h>

long long getTime();
unsigned long long load_file(char filename[], char **buffer);
void read_key(char *key, char *source);

int main(){
	oday_hash_headle dangdang_table;
	oday_list_headle list;
	char *buffer = NULL, key[100], *str, input[100] ,*result, temp[1000];
	unsigned long long i = 0, size, start;

	printf("正在载入文件...");

	// 计时开始
	start = getTime();

	if (size = load_file("dangdangwang.txt", &buffer)){
		printf("...载入完成,文件大小：%d,耗时：%udms\n", size, getTime() - start);
	}
	else{
		printf("...载入失败,程序结束\n");
		system("pause");
		return 0;
	}

	dangdang_table = oday_hash_create(POINTER, 100000, oday_BKDRHash);
	list = oday_list_create(POINTER, SINGLE);

	printf("开始解析文件...\n");

	// 计时开始
	start = getTime();

	str = strtok(buffer, "\n");
	read_key(key, strchr(str, ',') + 1);
	oday_hash_set(dangdang_table, key, str);
	while (str = strtok(NULL, "\n")){
		read_key(key, strchr(str, ',') + 1);
		list = (oday_list_headle)oday_hash_get(dangdang_table, key);
		if (list){
			oday_list_stick(list, str);
		}
		else{
			list = oday_list_create(POINTER, SINGLE);
			oday_list_stick(list, str);
			oday_hash_set(dangdang_table, key, list);
		}
		if (i++ > 500000){
			i = 0;
			printf("完成%.2f%%\n", 100.0*(double)(str - buffer) / (double)size);
		}
	}
	printf("完成100.00%%,耗时：%udms\n", 100.0*(double)(str - buffer) / (double)size, getTime() - start);

	printf("请输入需要查询的姓名：");
	while (scanf("%s", input)){

		// 计时开始
		start = getTime();

		if (strcmp(input, "ext") == 0)
			return 0;
		list = (oday_list_headle)oday_hash_get(dangdang_table, input);
		if (list){
			oday_list_rewind(list);
			while (result = (char*)oday_list_next(list)){
			//	printf("耗时：%dms\n%s\n", getTime() - start, result);
				printf("耗时：%dms\n", getTime() - start);
				printf("%s\n", result);
			}
		}
		else
			printf("查找的数据不存在,耗时：%udms!\n",getTime() - start);
		printf("输入需要查询的姓名：");
	}
	oday_hash_destory(dangdang_table);
	system("pause");
}

/* 将文件载入内存 */
unsigned long long load_file(char filename[], char **buffer){
	FILE *dist;						// 词库文件句柄
	unsigned long long size;		// 文件大小

	// 打开目标文件
	dist = fopen(filename, "r");
	if (!dist)
		return 0;

	// 读取文件大小
	fseek(dist, 0, SEEK_END);
	size = (unsigned)ftell(dist);
	rewind(dist);

	// 将文件读入缓冲区
	*buffer = (char*)malloc(sizeof(char)*(size+1));
	fread(*buffer, 1, size, dist);
	return size;
}

void read_key(char *key, char *source){
	while (*source!=',')
		*key++ = *source++;
	*key = 0;
}

long long getTime() {
	struct timeb t;
	ftime(&t);
	return 1000 * t.time + t.millitm;
}