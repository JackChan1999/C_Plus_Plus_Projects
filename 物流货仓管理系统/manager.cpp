#include "manager.h"
#include "productList.h"
#include <iostream>

using namespace std;

Manager::Manager(std::string fileName, std::string logFile)
: m_strRecordFile(fileName)//初始化为存放产品信息的文件名称product.txt
, m_strLogFileName(logFile)//初始化为日志文件名称info.log
, m_productHead(new ProductList())//初始化为ProductList对象地址
{
	// 打开日志文件
	m_foutLogFile.open(m_strLogFileName, ios_base::out | ios_base::app);
	m_foutLogFile.clear();
	m_foutLogFile.seekp(0, ios_base::beg);
	Logout("成功打开日志文件，开始营业");               //向日志文件保存相应操作信息
	system("pause");
	system("cls");
}


Manager::~Manager()
{
	m_foutLogFile.close();
	cout << "manager destructor!" << endl;
	
	ProductList::DeleteProductList(m_productHead);
	system("pause");
}


void Manager::ReadRecord()
{
	// 打开并载入产品信息记录文件（product.txt）
	m_finRecord.open(m_strRecordFile, ios_base::in);
	m_finRecord.clear();
	m_finRecord.seekg(0, ios_base::beg);

	//在日志文件中记录用户执行的操作
	OUTPUT_HEAD(m_foutLogFile);
	Product pro;
	//读取产品信息文件，将每条记录作为节点，插入链表
	while (INPUT_PRODUCT(m_finRecord, pro))
		m_productHead->AddProduct(&pro);         //向链表中插入新节点
	m_finRecord.close();                            //关闭产品信息文件
}


void Manager::UpdateRecord()
{
	auto str = m_strRecordFile + ".bak";//构造一个名称为“product.txt.bak”的字符串
	BackupRecord(str);                      //向名为“product.txt.bak”的文件存入链表信息
	remove(m_strRecordFile.c_str());     //删除原有的product.txt文件
	//将product.txt.bak更名为product.txt
	rename(str.c_str(), m_strRecordFile.c_str());
}


//函数参数指出文件名称
void Manager::BackupRecord(std::string file)
{
	Logout("正在创建副本");              //在日志文件中记录用户操作
	ofstream fout(file);
	auto p = m_productHead;           //p保存链表头指针
	auto ptr = ProductList::GetProduct(p);//获取链表首节点
	while (ptr)
	{
		OUTPUT_PRODUCT(fout, ptr);//将节点对应的产品信息存入文件
		ptr = ProductList::GetProduct(p);//获取下一个节点
	}
	fout.close();                      //关闭文件
	Logout("副本创建成功");
	system("pause");
}


void Manager::LogoutInfo()
{
	cout << __DATE__ << ", " << __TIME__ << ": ";
	m_foutLogFile << __DATE__ << ", " << __TIME__ << ": ";
}

void Manager::Logout(std::string content, bool bHasInfo)
{
	if (bHasInfo)
		LogoutInfo();

	cout << content << endl;
	m_foutLogFile << content << endl;
}

//参数说明：
//1、sChoice：用户输入的功能选项
//2、iExtra：操作条件
//3、iKeyword：属性选项
//4、sExtra：与iKeyword匹配的属性值
//例如四个参数为：2, 3（iExtra：表示查询条件， 3表示“大于”）, 
//3（iKeyword：表示属性编号， 3表示“产品价格”）, 20（sExtra），则表示用户要执行查询操作，
//则执行的操作为：查询价格高于20元的产品
void Manager::InventoryManager(std::string sChoice, int iExtra, int iKeyword, std::string sExtra)
{
	//获取产品信息链表头指针
	m_productHead = ProductList::GetListHead();
	if (sChoice == "1")             //功能1：产品信息显示
	{
		Logout("显示产品列表");
		//产品信息已保存在链表中，显示链表节点信息
		m_productHead->ShowAllProduct();
		Logout("显示完成");
	}
	else if (sChoice == "2")       //功能2：产品信息查询
	{
		Logout("按条件查询");        //在日志文件中记录用户操作
		//查找满足条件的节点信息，并将这些节点构成一个查询结果链表
		auto p = m_productHead->SearchProduct(static_cast<EType>(iKeyword), static_cast<ProductList::ECondition>(iExtra), sExtra);
		//若p为nullptr，表示未查找到满足条件的记录
		if (!p){
			cout << "************您查询的信息在系统中不存在*************" << endl;
			return;
		}
		//若查找到相应记录，显示查询结果
		p->ShowAllProduct(p);
		Logout("查询完成");
		ProductList::DeleteProductList(p);//删除查询结果链表
	}
	else if (sChoice == "3")        //功能3：产品信息排序
	{
		Logout("按条件排序");         //在日志文件中记录用户操作
		//通过SortProductByEType()函数按指定属性完成链表排序
		m_productHead->SortProductByEType(static_cast<EType>(iKeyword));
		//显示排序结果
		m_productHead->ShowAllProduct();
		Logout("排序完成");
	}
	else if (sChoice == "4")        //功能4：进货
	{
		Logout("进货");
		//按进货品种，完成进货操作，即向链表插入若干新节点
		for (auto i = 0; i < iExtra; i++){
			cout << "请输入第" << i + 1 << "个品种信息(共" << iExtra << "个）：" << endl;
			m_productHead->AddProduct();
		}
		Logout("进货完成");
	}
	else if (sChoice == "5")       //功能5：出货
	{
		Logout("按条件出货");
		//寻找待出货的节点信息，用p记录
		auto p = m_productHead->SearchProduct(static_cast<EType>(iKeyword), ProductList::ECondition::ON_EQUAL, sExtra);
		//若没找到待出货的产品节点，则给出用户提示
		if (!p){
			cout << "该货物不存在！" << endl;
			return;
		}
		//调用SellProduct()函数完成出货操作
		m_productHead->SellProduct(p, iExtra);
		Logout("出货完成");
		//销毁p指向的空间
		ProductList::DeleteProductList(p);
	}
	else if (sChoice == "6")           //功能6：修改产品信息
	{
		Logout("修改");
		//寻找待修改的节点信息，可以修改多个产品信息，将待修改的多个产品信息构成链表，由p指向
		auto p = m_productHead->SearchProduct(static_cast<EType>(iKeyword), static_cast<ProductList::ECondition>(iExtra), sExtra);
		if (!p){
			cout << "************要修改的信息不存在*************" << endl;
			return;
		}
		//通过EditProduct()函数完成信息修改
		m_productHead->EditProduct(p, ProductList::ESelect::SELECT_FIRST);
		Logout("修改完成");
		//销毁p指向的链表
		ProductList::DeleteProductList(p);
	}
	else if (sChoice == "7")           //功能7：在指定位置插入新信息
	{
		Logout("按条件插入");
		//寻找插入位置
		auto p = m_productHead->SearchProduct(static_cast<EType>(iKeyword), ProductList::ECondition::ON_EQUAL, sExtra);
		if (!p){
			cout << "没有找到插入位置！" << endl;
			return;
		}
		//在指定位置后插入新节点
		m_productHead->InsertProduct(p, iExtra);
		Logout("插入完成");
	}
	else if (sChoice == "8")         //功能8：信息保存
	{
		Logout("存盘");
		UpdateRecord();
		Logout("存盘完成");
	}
	else if (sChoice == "9")         //功能9：退出系统
	{
		Logout("谢谢使用!");
		system("pause");
		return;
	}
}



