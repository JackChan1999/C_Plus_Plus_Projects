#include "menu.h"
#include "control.h"
#include <iostream>

using namespace std;
#if 1
#define OUTPUT_INFO(out, content, isNum) \
do \
{ \
	out << "请分别输入：\n一、" << content << "的关键字索引：\n"; \
if (content != "按条件出货")\
	out << "(0.产品型号; 1.产品名称; 2.产品品牌; 3.产品价格; 4.产品数量)\n"; \
	else\
	out << "(0.产品型号; 1.产品名称)\n"; \
if (isNum) \
	out << "二、" << content << "的数目：\n"; \
	else \
	out << "二、" << "比较条件：" \
	<< "(1.相等; 2.小于; 3.大于)\n"; \
	out << "三、" << content << "的对象：\n"; \
} \
while (0)
#endif

#define OUTPUT_ATTRIBUTE_CHOICE(out, content) \
do \
{ \
	out << "请输入：\n" << content << "的关键字索引：\n" \
	<< "(0.产品型号; 1.产品名称; 2.产品品牌; 3.产品价格; 4.产品数量)\n"; \
} \
while (0)

#define OUTPUT_CONDITION_INFO(out, content, isStrAttribute, isNum) \
do \
{ \
if (isNum) \
	out << content << "的数目：\n"; \
	else if (isStrAttribute > 2){\
	out << "请输入比较条件" \
	<< "(1.相等; 2.小于; 3.大于)："; \
	cin >> iExtra; \
}else\
	iExtra = 1;\
	out << "请输入" << content << "的对象："; \
} \
while (0)

Control::Control() :m_manager("product.txt") //初始化m_manager对象
{
	Menu::MainMenu();                           //显示系统主界面
	cout << "请选择：";
	cin >> m_strChoice;                        //读取用户输入
	if (m_strChoice == "2")                   //若用户选择”2”，则退出系统
		exit(EXIT_SUCCESS);
	else if (m_strChoice == "1")             //若选择”1”，则进入系统执行相应功能
	{
		system("pause");
		system("cls");
		//载入产品信息文件（product.txt），创建链表结构，每条记录是一个节点
		m_manager.ReadRecord();
		//执行MainControl()函数，根据用户输入，执行相应功能
		MainControl();
	}
}


Control::~Control()
{

}



void Control::MainControl()
{
	int iExtra = 0;
	int iKeyword = -1;
	std::string sExtra;
	while (true)
	{
		Menu::SubMenu();                            //显示功能选项界面
		cout << "请选择：";
		cin >> m_strChoice;                        //输入功能选项
		if (m_strChoice == "2")                   //选择”2”，进行信息查询
		{
			//输出提示信息，让用户选择属性编号，按指定属性进行查询
			//属性编号由枚举类型EType描述
			OUTPUT_ATTRIBUTE_CHOICE(cout, "按条件查询");
			cin >> iKeyword;                      //获取属性编号
			//输出提示，若用户要求按价格或数量查询信息，则需要向iExtra输入查询条件
			OUTPUT_CONDITION_INFO(cout, "按条件查询", iKeyword, false);
			cin >> sExtra;                        //获取属性内容
			//例如用户输入的查询条件为：产品价格高于10
			//则iKeyword为“产品价格”，iExtra为“大于”, sExtra为10
		}
		else if (m_strChoice == "3")              //选择”3”，进行产品排序
		{
			cout << "请分别输入按条件排序的关键字索引：\n";
			cout << "(0.产品编号; 1.产品名称; 2.产品牌子; 3.产品价格; 4.产品数量)\n";
			cin >> iKeyword;
		}
		else if (m_strChoice == "4")             //选择”4”，实现产品入库
		{
			cout << "请输入进货品种：";             //输入进货品种
			cin >> iExtra;
		}
		else if (m_strChoice == "5")             //选择”5”，实现产品出库
		{
			OUTPUT_INFO(cout, "按条件出货", true);
			cin >> iKeyword >> iExtra >> sExtra;
		}
		else if (m_strChoice == "6")             //选择”6”，实现产品信息修改
		{
			OUTPUT_INFO(cout, "按条件修改", false);
			cin >> iKeyword >> iExtra >> sExtra;
		}
		else if (m_strChoice == "7")             //选择”7”，在指定位置插入新信息
		{
			OUTPUT_INFO(cout, "按条件插入", true);
			cin >> iKeyword >> iExtra >> sExtra;
		}
		//通过Manager类成员函数InventoryManager()实现用户指定功能
		//参数的含义分别为：
		//1、m_strChoice：用户的功能选项
		//2、iKeyword：执行子功能时按哪个产品属性进行操作，
		//              如iKeyword为0，按“产品型号”操作
		//3、iExtra：执行子功能时对iKeyword对应的属性按哪种方法进行操作
		//4、sExtra：根据iKeyword，输入具体的属性内容
		//例如：iKeyword为0（“产品型号”）， iExtra为2（小于）， sExtra为“PRO001”时
		//表示对产品型号值小于“PRO001”的产品执行相应操作
		m_manager.InventoryManager(m_strChoice, iExtra, iKeyword, sExtra);
		if (m_strChoice == "9")
			return;
		system("pause");
		system("cls");
	}
}

