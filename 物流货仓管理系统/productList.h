#pragma once

#include "product.h"

// 产品列表
class ProductList{
public:
	enum ESelect                        //定义枚举类型，说明操作链表的方式
	{
		SELECT_ALL = -1,			 // 全选，表示对链表的所有节点进行操作
		SELECT_FIRST = 1,			 // 仅选择满足条件的第一个节点进行操作
	};
	enum ECondition                    //对于系统中的查询要求，将使用本枚举类作为查询条件
	{
		ON_NONE = 0,
		ON_EQUAL = 0x01,           //查找相同内容
		ON_LESS = 0x02,           //查找小于条件值的内容
		ON_GREATER = 0x03            //查找大于条件值的内容
	};
private:
	Product* m_product;							// Product指针，指向产品信息
	ProductList* m_pProductNext;				// 指向后继节点
private:
	static ProductList* s_pProductHead;			// 静态数据成员，链表头指针
	static ProductList* s_pProductTail;			// 静态数据成员，链表尾指针
public:
	static void DeleteProductList(ProductList*& p);//删除链表
	static const Product* GetProduct(ProductList*& p);//获取产品信息
	static bool IsSame(const Product* pro1, const Product& pro2);//比较两个产品
	static ProductList *GetListHead();//获取链表头指针
public:
	ProductList();								// 构造函数
	~ProductList();								// 析构函数
private:
	// 内部接口
	void Swap(ProductList* ptr1, ProductList* ptr2); //交换节点中的产品信息
	//按属性完成产品信息比较
	int CompareByEType(EType t, const ProductList* ptr1, const ProductList* ptr2);
	//判断指定产品信息是否存在于链表中
	ProductList* IsSameProduct(const Product& pro) const;
	//获取当前节点的前驱
	ProductList* GetFrontProduct(const ProductList* product);
	//判断指定产品信息在链表中是否存在
	ProductList* IsProductExist(const ProductList* product, int num);
public:
	void AddProduct(const Product* ptr = nullptr);	// 添加产品
	// 在指定产品后插入新产品信息
	void InsertProduct(const ProductList* product, int num = SELECT_FIRST);
	// 出货
	void SellProduct(const ProductList* product, int num = SELECT_FIRST);
	// 删除产品信息原始列表中某产品信息
	void DeleteProduct(const ProductList* product, int num = SELECT_FIRST);
	// 查询产品
	ProductList* SearchProduct(EType t, ECondition c, std::string str) const;
	void ShowAllProduct(ProductList *head = s_pProductHead) const;	// 显示所有产品
	// 排序并显示
	void SortProductByEType(EType type);
	// 编辑指定产品的信息
	void EditProduct(const ProductList* product, int num = SELECT_FIRST);
	// 显示指定产品的信息
	void ShowProduct(const ProductList* product, int num = SELECT_FIRST);
};






#pragma region

#define COMPARE_BY(ptr1, ptr2, member) \
do \
{ \
if (ptr1->m_product->member < ptr2->m_product->member) \
	return -1; \
	else if (ptr1->m_product->member == ptr2->m_product->member) \
	return 0; \
	else \
	return 1; \
} \
while (0)

#define COMPARE_WITH(ptr, member, val, res) \
do \
{ \
if (ptr->m_product->member < val) \
	res = ECondition::ON_LESS; \
	else if (ptr->m_product->member == val) \
	res = ECondition::ON_EQUAL; \
	else \
	res = ECondition::ON_GREATER; \
} \
while (0)

#define OUTPUT_HEAD(out) \
do \
{ \
	out << "型号" << "\t\t" \
	<< "名称" << "\t\t" \
	<< "品牌" << "\t\t" \
	<< "单价" << "\t\t" \
	<< "数量" << endl; \
	out << "--------------------------------------------------------------------" << endl;\
} \
while (0)

#define INPUT_PRODUCT(in, pro) \
in >> pro.sSerial \
	>> pro.sName \
	>> pro.sBrand \
	>> pro.iPrice \
	>> pro.iCount

#define OUTPUT_PRODUCT(out, ptr) \
out << ptr->sSerial << "\t\t" \
	<< ptr->sName << "\t" \
	<< ptr->sBrand << "\t\t" \
	<< ptr->iPrice << "\t\t" \
	<< ptr->iCount << endl

#define COPY_PRODUCT(ptr, pro) \
do \
{ \
	ptr->sSerial = pro.sSerial; \
	ptr->sName = pro.sName; \
	ptr->sBrand = pro.sBrand; \
	ptr->iPrice = pro.iPrice; \
	ptr->iCount = pro.iCount; \
} while (0)

#pragma endregion
