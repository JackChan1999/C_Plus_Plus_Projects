#pragma once

#include <fstream>
#include "productList.h"

// 管理
class Manager{
private:
	std::ifstream m_finRecord;			// 操作库存文件的对象
	std::ofstream m_foutLogFile;		// 操作日志文件的对象
	std::string m_strRecordFile;		// 库存文件名
	std::string m_strLogFileName;		// 日志文件名
	ProductList* m_productHead;			// 产品链表头
public:
	//声明带参数默认值的构造函数，日志文件名默认为”info.log”
	Manager(std::string fileName, std::string logFile = "info.log");
	~Manager();
public:
	void ReadRecord();                   //实现产品信息文件读取，每条记录对应一个链表节点
	void UpdateRecord();                 //文件内容更新
	void BackupRecord(std::string file);//实现“存盘”操作
	void LogoutInfo();                   //向日志文件写入信息
	void Logout(std::string content, bool bHasInfo = true);
	//系统功能入口函数
	void InventoryManager(std::string sChoice, int iExtra = ProductList::ECondition::ON_NONE, int iKeyword = -1, std::string sExtra = nullptr);
};
