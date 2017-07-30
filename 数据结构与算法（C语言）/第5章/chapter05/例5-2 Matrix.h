#include <stdio.h>   
#include <stdlib.h>

#define OK 1   
#define ERROR 0   
#define TRUE 1   
#define FALSE 0  
#define ROWS 6
#define COLS 7  
#define MAXSIZE 100   

typedef int Status;
typedef int ElemType;
typedef struct{		//三元组结构   
	int row;		//行号  
	int col;		//列号
	ElemType value;//非零元素值   
}Triples;
typedef struct{
	Triples data[MAXSIZE + 1];//非零元三元组表，data[0]不用   
	int rows, cols, nums;//矩阵的行数、列数和非零元素个数   
}TSMatrix;

//新建一个三元组表示的稀疏矩阵   
TSMatrix NewMatrix(int m, int n);
//向使用三元组表示的稀疏矩阵M中插入数据
Status InsertElem(TSMatrix *M, int row, int col, ElemType value);
//矩阵转置，将使用三元组表示的稀疏矩阵M转置，并存入N中
Status sMatrixTranspose(const TSMatrix *M, TSMatrix *N);
//快速转置，将使用三元组表示的稀疏矩阵M转置，并存入N中
Status sMatrixFastTranspose(const TSMatrix *M, TSMatrix *N);
//矩阵打印，将使用三元组表示的稀疏矩阵M打印到屏幕
void sMatrixPrint(const TSMatrix *M);
//矩阵乘法
void mmult(Triples a[], Triples b[], Triples d[]);
