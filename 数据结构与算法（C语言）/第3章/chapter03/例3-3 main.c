#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "linkstack.h"

char buffer[256] = { 0 }; //临时缓冲区，从栈中弹出的元素可以先存放在这里
void Put(char ch)
{
	static int index = 0;
	buffer[index++] = ch; //将字符存入进来，然后索引index后移
}

//优先级比较函数
int Priority(char ch)
{
	int ret = 0;
	switch (ch)
	{
	case '+':
	case '-':
		ret = 1;
		break;
	case '*':
	case '/':
		ret = 2;
		break;
	default:
		break;
	}
	return ret;
}

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

//判断字符是否是左括号
int isLeft(char ch)
{
	return (ch == '(');
}

//判断字符是否是右括号
int isRight(char ch)
{
	return (ch == ')');
}

//函数功能：中缀转后缀表达式
//函数返回值：正确返回0；错误返回-1
int  Transform(const char* str)
{
//在转换字符串时，先创建一个栈
LinkStack lstack = Create(); //创建栈

//创建完栈之后，就遍历字符串中的字符，数字输出，运算符入栈...
int i = 0;
while (str[i] != '\0')
{
	//判断是否是数字
	if (isNumber(str[i])) //如果是数字，就直接输出
	{
		Put(str[i]);  //存入到buffer中
	}
	//判断是否是运算符
	else if (isOperator(str[i])) 
	{
		//如果是运算符，则先判断栈是否为空
		if (!IsEmpty(lstack)) //如果栈不为空
		{
			//要比较此符号与栈顶符号的优先级
			while (!IsEmpty(lstack) && Priority(*((char*)getTop(lstack))) 
                                                          >= Priority(str[i]))
			{ //如果栈顶符号优先级高，就将栈顶符号弹出并输出，直到栈顶符号的优先级
			  //小于此符号或者栈已弹空
				Put(Pop(lstack)->data); //将弹出的栈顶符号存入到buffer中
			}
		}
		Push(lstack, str[i]); //如果栈为空，符号直接入栈
	}
	//如果是左括号，直接入栈
	else if (isLeft(str[i]))
	{
		Push(lstack, str[i]);
	}
	//如果是右括号
	else if (isRight(str[i]))
	{
		//判断栈顶是不是左括号，如果不是，就弹出，直到匹配到左括号
		while (!isLeft(*((char*)getTop(lstack)))) 
		{	
				//弹出栈顶符号并存入到buffer中
				Put(Pop(lstack)->data);
				if (IsEmpty(lstack)) //如果弹出元素后，栈已经空了，就匹配错误
				{
					printf("没有匹配到左括号！\n");
					return -1; //如果栈已为空，结束程序
				}
			}

			Pop(lstack); //while循环结束，就匹配到了左括号，将左括号弹出，注意不保存
		}
		else
		{
			printf("有不能识别字符！\n");
			return -1;
		}
		i++;
	}
	
	//遍历结束后
	if (str[i] == '\0')
	{
		//遍历结束后，将栈中所有符号依次弹出
		while (!IsEmpty(lstack))
		{
			if (getTop(lstack)->data == '(') //如果栈中还有“(“，证明缺少右括号
			{
				printf("有没有匹配的“（”，缺少“）”\n");
				return -1;
			}
			Put(Pop(lstack)->data);
		}
	}
	else
	{
		printf("遍历没有完成！\n");
	}
	return 1;
}

int main()
{
	char str[1024] = {0};//"1325+*+";
	printf("请输入四则运算表达式：\n");
	scanf("%s", str);
	
	if(Transform(str) == -1)
		printf("遍历中出现错误，无法完成转换！\n"); //转换
	else
		printf("转化后的表达式是： %s\n",buffer);
	system("pause");
	return 0;
}
