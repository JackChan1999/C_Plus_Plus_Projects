#include "menu.h"
#include <iostream>

using namespace std;

static const int MAX_LEN = 80;

#define OUTPUT_CONTENT(content) \
do \
{ \
	int len = strlen(content); \
	if (len > 0) \
			{ \
		len = (MAX_LEN - len) / 2; \
		cout << "#"; \
		for (auto i = 1; i < len; i++) \
			cout << " "; \
		cout << content; \
		for (auto i = 1; i < len; i++) \
			cout << " "; \
		cout << "#"; \
	} \
	else \
	{ \
		for (auto i = 0; i < 80; i++) \
			cout << "#"; \
	} \
} \
while (0)

void Menu::MainMenu()
{
	OUTPUT_CONTENT("");
	OUTPUT_CONTENT("欢迎使用物流管理系统");
	OUTPUT_CONTENT("1.开始营业");
	OUTPUT_CONTENT("2.退    出");
	OUTPUT_CONTENT("");
}

void Menu::SubMenu()
{
	OUTPUT_CONTENT("");
	OUTPUT_CONTENT("***物流管理系统***");
	OUTPUT_CONTENT("1.显示产品列表");
	OUTPUT_CONTENT("2.按条件查询");
	OUTPUT_CONTENT("3.按条件排序");
	OUTPUT_CONTENT("4.进      货");
	OUTPUT_CONTENT("5.出      货");
	OUTPUT_CONTENT("6.修      改");
	OUTPUT_CONTENT("7.插      入");
	OUTPUT_CONTENT("8.存      盘");
	OUTPUT_CONTENT("9.退      出");
	OUTPUT_CONTENT("");
}


