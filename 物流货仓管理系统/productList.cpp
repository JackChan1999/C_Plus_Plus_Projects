#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "productList.h"

using namespace std;

ProductList* ProductList::s_pProductHead = nullptr;
ProductList* ProductList::s_pProductTail = nullptr;

void ProductList::DeleteProductList(ProductList*& p)
{
	auto pTmp = p, pList = p;
	auto& pHead = p;
	while (pTmp && pTmp->m_pProductNext)
	{
		pTmp = pTmp->m_pProductNext;
		if (pList == s_pProductHead)
			delete p->m_product;
		delete p;
		p = pTmp;
	}
	delete pTmp;
	pHead = nullptr;
}

const Product* ProductList::GetProduct(ProductList*& p)
{
	if (!p->m_product)
		return nullptr;

	const auto ptr = p->m_product;
	p = p->m_pProductNext;
	return ptr;
}

bool ProductList::IsSame(const Product* pro1, const Product& pro2)
{
	if (pro1->sSerial == pro2.sSerial
		&& pro1->sName == pro2.sName
		&& pro1->sBrand == pro2.sBrand)
		return true;

	return false;
}

ProductList::ProductList() :m_product(nullptr), m_pProductNext(nullptr)
{
	//s_pProducHead和s_pProductTail两个静态数据成员是产品信息链表的头指针、尾指针
	//链表刚创建时，只存在一个节点，内容无效，头尾指针均指向该节点
	if (!(s_pProductHead || s_pProductTail))
	{
		s_pProductHead = this;
		s_pProductTail = this;
	}
}


ProductList::~ProductList()
{
	//cout << "productlist destructor!" << endl;
	//s_pProductTail = nullptr;
}

void ProductList::Swap(ProductList* ptr1, ProductList* ptr2)
{
	Product *tmp;
	tmp = ptr1->m_product;
	ptr1->m_product = ptr2->m_product;
	ptr2->m_product = tmp;
}

int ProductList::CompareByEType(EType t, const ProductList* ptr1, const ProductList* ptr2)
{
	switch (t)
	{
	case TYPE_SERIAL:
		COMPARE_BY(ptr1, ptr2, sSerial);
	case TYPE_NAME:
		COMPARE_BY(ptr1, ptr2, sName);
	case TYPE_BRAND:
		COMPARE_BY(ptr1, ptr2, sBrand);
	case TYPE_PRICE:
		COMPARE_BY(ptr1, ptr2, iPrice);
	case TYPE_COUNT:
		COMPARE_BY(ptr1, ptr2, iCount);
	}
	return 0;
}

ProductList* ProductList::IsSameProduct(const Product& pro) const
{
	auto p = s_pProductHead;

	while (p->m_product)
	{
		if (IsSame(p->m_product, pro))
			return p;
		p = p->m_pProductNext;
	}

	return nullptr;
}

ProductList* ProductList::GetFrontProduct(const ProductList* product)
{
	if (!product)
	{
		cout << "Invalid param: product == nullptr!\n";
		return nullptr;
	}

	auto pThis = s_pProductHead;
	while (pThis->m_pProductNext)
	{
		if (pThis->m_pProductNext->m_product == product->m_product)
			break;
		pThis = pThis->m_pProductNext;
	}

	if (!pThis->m_pProductNext)
		return nullptr;
	return pThis;
}

ProductList* ProductList::IsProductExist(const ProductList* product, int num)
{
	if (!product)
	{
		cout << "Invalid param: product == nullptr!\n";
		return nullptr;
	}

	if (num < 1)
	{
		cout << "Invalid count: num == " << num << ", num < 1\n";
		return nullptr;
	}

	auto pThis = s_pProductHead;
	while (pThis)
	{
		if (pThis->m_product == product->m_product)
			break;
		pThis = pThis->m_pProductNext;
	}

	return pThis;
}

//函数参数为待插入的产品对象地址，ptr值有两种：
//1、若产品信息从product.txt文件获得，则ptr为非nullptr值
//2、若产品信息需要用户输入，ptr值为nullptr
void ProductList::AddProduct(const Product* ptr)
{
	Product pro;
	if (!ptr){                              //ptr为nullptr时，需要用户输入产品信息
		cout << "请按以下格式输入产品信息：\n";
		OUTPUT_HEAD(cout);
		INPUT_PRODUCT(cin, pro);        //从键盘获取产品信息，存入pro中
	}
	else{
		pro = *ptr;                       //将待插节点的有效内容存入pro中
	}
	//将待插节点的产品型号、名称、品牌同链表现有节点进行比较
	//若存在内容相同的节点，用p记录链表节点地址，否则p为nullptr
	auto p = IsSameProduct(pro);
	if (p)
	{
		cout << "您输入的产品名称在系统中已存在，现将信息进行合并！" << endl;
		cout << "\n原有信息如下：" << endl;
		OUTPUT_HEAD(cout);
		OUTPUT_PRODUCT(cout, p->m_product);
		//若链表中存在与待插节点信息相同节点，将待插节点的价格、数量与现有链表节点相应内容合并
		int total = p->m_product->iPrice * p->m_product->iCount + pro.iPrice * pro.iCount;
		p->m_product->iCount += pro.iCount;
		p->m_product->iPrice = total / p->m_product->iCount;

		cout << "合并后，信息如下：" << endl;
		OUTPUT_PRODUCT(cout, p->m_product);
		cout << endl;
		return;
	}
	//若链表已存在，在链表尾部插入新节点
	if (s_pProductTail)
	{
		//让尾指针的m_product保存新产品对象地址
		s_pProductTail->m_product = new Product(pro);
		//创建新的尾节点
		s_pProductTail->m_pProductNext = new ProductList();
		//尾指针指向新创建的尾节点
		s_pProductTail = s_pProductTail->m_pProductNext;
	}
}


//在链表中product节点后插入num个新节点
void ProductList::InsertProduct(const ProductList* product, int num)
{
	//在链表中寻找插入位置，比如product为产品型号值等于“PRO001”的节点指针
	//则本函数将在该节点后插入num个新节点。 pThis指针记录插入位置
	ProductList* pThis = IsProductExist(product, num);
	if (!pThis)                             //若插入位置不存在，则结束操作
		return;

	int i = 0;
	Product pro;
	//pThis后将插入新节点，pNext记录当前pThis的后继节点
	auto pNext = pThis->m_pProductNext;
	while (i++ < num)                     //插入num个新节点
	{
		cout << "输入新产品内容：" << endl;
		OUTPUT_HEAD(cout);
		INPUT_PRODUCT(cin, pro);
		//若输入的产品型号、名称、品牌与链表中某节点相同，则认为是同一个产品，只修改产品数量
		auto p = IsSameProduct(pro);
		if (p)
		{
			p->m_product->iCount += pro.iCount;
			continue;
		}
		//输入的是新产品信息，则建立新节点，插入合适的位置
		pThis->m_pProductNext = new ProductList();
		pThis = pThis->m_pProductNext;
		pThis->m_product = new Product(pro);
		pThis->m_pProductNext = pNext;
	}
	return;
}



void ProductList::SellProduct(const ProductList* product, int num)
{
	//在链表中寻找待出货的产品节点，查找结果记录在p中
	auto p = IsProductExist(product, ESelect::SELECT_FIRST);
	//若p为非nullptr，则找到要出货的产品节点
	if (p)
	{
		//显示要出货的产品信息
		cout << "要出货的产品信息：" << endl;
		OUTPUT_HEAD(cout);
		OUTPUT_PRODUCT(cout, p->m_product);
		//根据出货数量，减少节点中相应的产品数量值
		p->m_product->iCount -= num;
		//若出货量大于等于库存量，则删除链表中对应节点
		if (p->m_product->iCount <= 0){
			cout << "**********出货量为：" << p->m_product->iCount + num
				<< ", 该货物已出清！**********" << endl;
			DeleteProduct(p);
		}
	}
}


//参数product指明待删节点
//numm默认值为SELECT_FIRST（1），表示删除链表中匹配的第一个节点，即当前节点
void ProductList::DeleteProduct(const ProductList* product, int num)
{
	int i = 0;
	auto p = product;
	ProductList* pThis;
	ProductList* pNext;
	ProductList* pFront;
	//若待删节点是链表的首节点，则销毁首节点，并修改s_pProductHead
	if (product == s_pProductHead){
		delete product->m_product;
		s_pProductHead = s_pProductHead->m_pProductNext;
		delete product;
		return;
	}
	while (i++ < num)
	{
		if (!p->m_product)
		{
			cout << "Warning: param product == nullptr!\n";
			return;
		}
		//寻找待删节点的前驱
		pFront = GetFrontProduct(p);
		//确定待删节点
		pThis = IsProductExist(p, num);
		if (!pThis)
		{
			cout << "Warning: param pThis == nullptr!\n";
			return;
		}
		//将待删节点的前驱和后继相连，删除指定节点
		p = p->m_pProductNext;
		pNext = pThis->m_pProductNext;
		delete pThis->m_product;
		delete pThis;
		if (pFront)
			pFront->m_pProductNext = pThis = pNext;
	}
	return;
}


//参数说明：
//EType t:表示产品属性编号，例如，若想按照产品型号进行查询，则t为0，按名称查，t为1
//ECondition c:表示查询条件，例如，若查询条件为“相等”，则c为1
//std::string str：表示具体的产品属性值
//当t为0， c为1， str为PRO001时，表示查询产品型号等于“PRO001”的节点信息
ProductList* ProductList::SearchProduct(EType t, ECondition c, std::string str) const
{
	int val;
	ECondition res;
	const char* s = str.c_str();
	auto p = s_pProductHead;            //用p记录待查询的链表头指针
	//pList为查询结果链表的头节点地址
	//若从产品信息链表中查找到符合条件的节点，则依次插入pList指向的链表中
	auto pList = new ProductList();
	auto pHead = pList;
	sscanf(s, "%d", &val);
	//查找产品信息链表
	while (p->m_product)
	{
		//确定查找条件
		switch (t)
		{
		case TYPE_SERIAL:
			//按产品型号进行查询，在res中记录查询比较条件
			//若当前节点中的产品型号值小于str指定的查询值则查询条件res被设定为ON_LESS
			//若相等则res被设定为ON_EQUAL，若大于则res被设置为ON_GREATER
			COMPARE_WITH(p, sSerial, str, res);
			break;
		case TYPE_NAME:
			COMPARE_WITH(p, sName, str, res);
			break;
		case TYPE_BRAND:
			COMPARE_WITH(p, sBrand, str, res);
			break;
		case TYPE_PRICE:
			COMPARE_WITH(p, iPrice, val, res);
			break;
		case TYPE_COUNT:
			COMPARE_WITH(p, iCount, val, res);
			break;
		}
		//比较查询条件与本节点产品属性值的关系，若匹配说明查询成功
		//将查询到的产品信息存入pList指向的链表中
		if (c == res)
		{
			pList->m_product = p->m_product;
			pList->m_pProductNext = new ProductList();
			pList = pList->m_pProductNext;
		}
		p = p->m_pProductNext;
	}
	//若查找到有效信息则返回查询结果链表头指针，否则返回nullptr
	return pHead->m_product ? pHead : nullptr;
}



void ProductList::ShowAllProduct(ProductList *head) const
{
	OUTPUT_HEAD(cout);                                //显示产品属性名称
	auto p = head;
	//循环访问链表节点，完成信息显示
	while (p->m_product)
	{
		OUTPUT_PRODUCT(cout, p->m_product);
		p = p->m_pProductNext;
	}
}



//按指定属性完成链表升序排列
void ProductList::SortProductByEType(EType type)
{
	auto p = s_pProductHead;                   //让p记录头节点地址
	//若链表只有一个节点，直接显示该节点信息,无需排序
	if (!p->m_pProductNext)
	{
		ShowAllProduct();
		return;
	}

	ProductList* pTmp;
	//按照选择排序思想，对链表节点进行升序排序
	for (auto i = p; i->m_pProductNext->m_product;)
	{
		//i节点位置为链表中最前位置，最前位置应该存放属性值最小的节点信息
		pTmp = i;
		//从i节点之后的节点中寻找属性值最小的节点，并将节点地址记录在pTmp指针中
		auto j = i->m_pProductNext;
		while (j->m_product)
		{
			if (CompareByEType(type, pTmp, j) > 0)
				pTmp = j;
			j = j->m_pProductNext;
		}
		//若属性值最小的节点（由pTmp指向）没有出现在链表最前位置i上，则交换产品信息
		Swap(i, pTmp);
		i = i->m_pProductNext;
	}
}

//参数为一个链表头指针，该链表描述满足修改条件的所有产品， num始终为真，表示修改该节点信息
void ProductList::EditProduct(const ProductList* product, int num)
{
	Product pro;
	auto p = product;
	ProductList *pSame;
	ProductList* pThis;
	//通过循环，操作每个需要进行修改的节点
	while (p->m_product)
	{
		//判断产品信息链表中是否存在待修改的节点信息，若存在则进行修改
		pThis = IsProductExist(p, ProductList::ESelect::SELECT_FIRST);
		if (pThis)
		{
			//修改前先显示目前信息
			cout << "该物品原有信息如下：\n";
			OUTPUT_PRODUCT(cout, pThis->m_product);
			//输入新信息
			cout << "请输入修改后的信息：\n";
			INPUT_PRODUCT(cin, pro);
			//在现有产品信息链表中查找新输入的信息是否存在
			pSame = IsSameProduct(pro);
			//修改本节点，或者若新输入的信息与产品信息链表中现有信息均不相同，
			//则将新信息复制到待修改节点中。
			if (!pSame || pSame->m_product == p->m_product){
				COPY_PRODUCT(pThis->m_product, pro);
			}
			//若新输入的信息与链表中除本节点外的某个节点相同，则删除本节点，
			//并将新信息与原有信息合并
			else
			{
				DeleteProduct(pThis);
				pSame->m_product->iCount += pro.iCount;
			}
			cout << "修改成功，请按回车键继续修改。\n";
			cin.get();
			cin.get();
		}
		else
			break;
		p = p->m_pProductNext;
	}
	cout << "修改完毕！\n";
}


void ProductList::ShowProduct(const ProductList* product, int num)
{
	OUTPUT_HEAD(cout);

	int i = 0;
	auto p = product;
	auto pThis = s_pProductHead;
	while (i++ < num)
	{
		pThis = IsProductExist(p, num);
		if (pThis)
			OUTPUT_PRODUCT(cout, pThis->m_product);
		p = p->m_pProductNext;
	}
}
ProductList *ProductList::GetListHead()
{
	return s_pProductHead;
}