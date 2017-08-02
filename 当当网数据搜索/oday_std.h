#ifndef ODAY_STD_H
#define ODAY_STD_H

/* 数据类型 */
typedef enum Data_Type data_type;
enum Data_Type{
	CHAR,			// 字符型
	INT,			// 整数型
	SHORT,			// 短整型
	LONG,			// 长整型
	LONG_LONG,		// 长整型
	POINTER,		// 地址型
	STRING,			// 字符串
};

/* 布尔型常量 */
typedef enum Boolen boolen;
enum Boolen{ TRUE = 1, FALSE = 0 };

/* 多类型联合体 */
typedef union Naked_Type_Constraints naked_type_constraints;
union Naked_Type_Constraints{
	char char_data;
	short short_data;
	int int_data;
	long long_data;
	long long long_long_data;
	void *pointer_data;
};

#endif