#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <windows.h>
#include <string>
#include <thread>

using namespace std;

const int n = 306;

typedef struct FindNode
{
	string key;	//待查找目标
	char *pstart;//起点
	int len;     //搜索范围
	int end;	//查找是否完成结果指针
	int count;  //统计记录条数

}fnode;

class KaiFang{
private:
	string filepath;//文件路径
	DWORD dwFileSize;//文件大小
	HANDLE hFileMap;//映射句柄
	PVOID pvFile;//文件映射授权

	int fileline;//文件行数
	char *pfilestart;//文件起始指针
	char *pfileend;//文件结束指针
	int  *pos;//文件偏移地址
	
public:
	KaiFang(string path);
	~KaiFang();
	bool myFileMap();
	bool SearchInFile(string &strfind);
	void FindInFile(fnode *fd);
};