#include "kf.h"

int main()
{
	string filepath = "kaifang_noBomb.txt";

	KaiFang kf(filepath);
		
	if (kf.myFileMap())
	{
		string findstr;
		string choice;
		while (1)
		{
			choice.clear();
			cout << "欢迎使用开房查询工具，请选择要查询的方式(exit退出)：1精确查找，0模糊查找：" << endl;
			cin >> choice;
			if (!choice.compare("exit"))
			{
				cout << "谢谢使用" << endl;
				choice.clear();
				break;
			}
			else
			{
				if (choice == "1")
				{
					choice.clear();
					while (findstr.empty())
					{

						cout << "请输入你要查找的内容(exit退出)：" << endl;
						cin >> findstr;
					}
					if (!findstr.compare("exit"))
					{
						cout << "谢谢使用" << endl;
						return 0;
					}
					findstr.push_back(',');
					//cout << "你输入的内容是：" << findstr << endl;

					int starttime = GetTickCount();
					kf.SearchInFile(findstr);
					int endtime = GetTickCount();

					cout << "总耗时" << endtime - starttime << "ms" << endl;
					cout << endl;
					findstr.clear();
				}
				else if (choice == "0")
				{
					choice.clear();
					while (findstr.empty())
					{

						cout << "请输入你要查找的内容(exit退出)：" << endl;
						cin >> findstr;
					}
					if (!choice.compare("exit"))
					{
						cout << "谢谢使用" << endl;
						return 0;
					}
					//cout << "你输入的内容是：" << findstr << endl;

					int starttime = GetTickCount();
					kf.SearchInFile(findstr);
					int endtime = GetTickCount();

					cout << "总耗时" << endtime - starttime << "ms" << endl;
					cout << endl;
					findstr.clear();
				}
				else
				{
					cout << endl;
					cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>输入有误，请重新输入<<<<<<<<<<<<<<<<<<<<<<<" << endl;
					cout << endl;
					choice.clear();
					findstr.clear();
				}			
			}		

		}
				
	}

	system("pause");
	return 0;
}