#include "kf.h"

KaiFang::KaiFang(string path)
{
	filepath = path;
	dwFileSize = 0;
	hFileMap = nullptr;
	pvFile = nullptr;
	fileline = 0;
	pfilestart = nullptr;
	pfileend = nullptr;
	pos = nullptr;
}

KaiFang::~KaiFang()
{
	delete []pos;
}

bool KaiFang::myFileMap()
{
	LPCTSTR pszPathName = filepath.c_str();//只接受C语言类型的字符串

	HANDLE hFile = CreateFile(pszPathName, GENERIC_WRITE | GENERIC_READ, 0, NULL
		, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hFile == INVALID_HANDLE_VALUE)
	{
		cout << "文件不存在" << endl;
		return FALSE;
	}

	dwFileSize = GetFileSize(hFile, NULL);//获得文件的大小
	cout << "文件大小：" << dwFileSize << "字节"<<endl;

	HANDLE hFileMap = CreateFileMapping(hFile, NULL, PAGE_READWRITE, 0,
		dwFileSize + sizeof(char), NULL);//建立文件映射

	if (hFileMap == NULL){
		CloseHandle(hFile);//建立文件映射失败，关闭文件
		return FALSE;
	}

	SYSTEM_INFO sinf;
	GetSystemInfo(&sinf);
	DWORD dwAllocationGranularity = sinf.dwAllocationGranularity;
	//cout << "分配最小单位为" << dwAllocationGranularity << endl;
	//获取最小的映射单位：65536

	PVOID pvFile = MapViewOfFile(hFileMap, FILE_MAP_WRITE, 0, 0, 0);

	if (pvFile == NULL){
		CloseHandle(hFileMap);
		CloseHandle(hFile);
		cout << "内存映射失败，请重试" << endl;
		return FALSE;
	}

	cout << "内存映射成功" << endl;

	PSTR pchAnsi = (PSTR)pvFile;

	pfilestart = (char *)pchAnsi;//转换指针,设置文件头

	pfileend = pfilestart + dwFileSize;//设置文件尾

	pos = new int[n];//开辟文件偏移指针数组
	for (int i = 0; i < n; i++)
		pos[i] = 0;

	int line = 0;//行数
	int ipos = 0;//文件偏移指针的元素位置
	int index = 0;

	char *p = pfilestart;
	while (index < dwFileSize)//全文扫描，记录线程搜索起始地址
	{
		if (p[index++] == '\n')
		{
			line++;//找到换行符，则行数加1
			if ((line % 65535) == 0)//判断当前行数是否能被65535整除，
			{
				pos[++ipos] = index;//如果能，则记录当前的文件偏移指针
			}
		}
	}

	fileline = line;//记录文件的行数
	//cout << "文件的行数为：" << line << endl;
	//cout << "扫描完成" << endl;
	cout << "===========加载完成==========" << endl;
	return true;
}


bool  KaiFang::SearchInFile(string &strfind)
{

	FindNode fd[n];
	thread *pth[n] = { 0 };

	int i = 0;
	char *pst = pfilestart;

	cout << "============搜索中============" << endl;
	for (i = 0; i < n - 1; i++)
	{
		fd[i].key = strfind;
		fd[i].len = 65535;
		fd[i].pstart = pst + pos[i];
		fd[i].end = 0;
		fd[i].count = 0;
		pth[i] = new thread(&KaiFang::FindInFile,this, &fd[i]);
		pth[i]->join();
	}

	//处理残余的数据
	fd[i].key = strfind;
	fd[i].len = fileline - 65535 * (n - 1);
	fd[i].pstart = pst + pos[i];
	fd[i].end = 0;
	fd[i].count = 0;
	pth[i] = new thread(&KaiFang::FindInFile, this, &fd[i]);
	pth[i]->join();

	int finish = 0;
	int total = 0;

	while (1){
		Sleep(10);//定时检测结束标志

		for (int i = 0; i < n; i++)
		{
			finish += fd[i].end;
			total += fd[i].count;
		}
		if (finish == n)
		{
			cout << "查找完成" << endl;
			cout << "共找到" << total << "条记录" << endl;
			break;
		}
	}

	//cout << "game over" << endl;

	return true;
}

void KaiFang::FindInFile(fnode *fd)
{
	char *pstart = fd->pstart;
	char *p = fd->pstart;
	int length = fd->len;
	int line = 0;
	string str;
	while (line < length) //读取指定的长度
	{
		str += *p;
		if (*p++ == '\n')
			line++;
	}

	int pos = 0;
	int count = 0;

	while ((pos = str.find(fd->key, pos)) != -1)
	{
		int pe = pos;
		while (pos != 0 && str[pos--] != '\n');
		while (str[pe++] != '\n');
		while (pos < pe - 2)
		{
			cout << str[pos];
			pos++;
		}
		count++;
		cout << endl;
		pos = pe;
	}

	fd->end = 1;//设置线程结束标志
	fd->count = count;//统计结果
}