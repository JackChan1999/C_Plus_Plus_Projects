#pragma once

#include <string>

#define OFFSET_OF(__TYPE__, __MEMBER__) \
(size_t)(&((static_cast<__TYPE__*>(0))->__MEMBER__))

enum EType
{
	TYPE_SERIAL,              //产品型号
	TYPE_NAME,                //产品名称
	TYPE_BRAND,               //产品品牌
	TYPE_PRICE,               //产品价格
	TYPE_COUNT                //产品数量
};


// 产品
struct Product
{
	std::string sSerial;	// 产品型号
	std::string sName;		// 产品名称
	std::string sBrand;		// 产品品牌
	int iPrice;				// 产品价格
	int iCount;				// 产品数量
};

