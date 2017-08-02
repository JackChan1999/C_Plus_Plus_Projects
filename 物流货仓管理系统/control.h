#pragma once

#include "manager.h"

class Control{
private:
	Manager m_manager;                              //Manager对象，用于实现系统功能
	std::string m_strChoice;                       //功能选项值
public:
	Control();
	~Control();
	void MainControl();                             //系统功能入口函数
};

