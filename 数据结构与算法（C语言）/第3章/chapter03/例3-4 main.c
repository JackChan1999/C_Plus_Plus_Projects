#include "linkstack.h" //将栈的头文件包含进来
#include <stdio.h>

//判断字符是否是数字
int isNumber(char ch)
{
	return (ch >= '0' && ch <= '9'); //是数字返回1，否则返回0
}

//判断字符是否是运算符
int isOperator(char ch)
{
	return (ch == '+' || ch == '-' || ch == '*' || ch == '/');
}

//左右两个操作运算
int express(int left, int right, char op)
{
	switch (op)
	{
	case '+':
		return left + right;
	case '-':
		return left - right;
	case '*':
		return left * right;
	case '/':
		return left / right;
	default:
		break;
	}
	return -1;
}

//后缀表达式运算
int Calculate(const char * str)
{
	LinkStack lstack = NULL;
	lstack = Create();

	int i = 0;
	while (str[i]) //遍历字符串
	{
		if (isNumber(str[i])) //如果是数字，直接入栈
			Push(lstack, str[i] - '0'); //在存储时，是按字符的ASCII码存储的，所以要送去‘0’
		else if (isOperator(str[i])) //如果是运算符，就弹出左右操作数
		{
			int left = Pop(lstack)->data;
			int right = Pop(lstack)->data;
			int ret = express(left, right, str[i]); //运算
			Push(lstack, ret); //运算结果入栈
		}
		else
		{
			printf("error!\n");
			break;
		}
		i++;
	}

	if (str[i] == '\0' && getSize(lstack) == 1)
		return *((char*)getTop(lstack));
}

int main()
{
	char *str = "1325+*+";  //正确的后缀表达式
	int num = Calculate(str);
	printf("%d\n", num);

	system("pause");
	return 0;
}
