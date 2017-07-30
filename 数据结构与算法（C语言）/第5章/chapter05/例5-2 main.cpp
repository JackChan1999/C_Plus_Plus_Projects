#include "Matrix.h"
int main()
{
	//创建矩阵
	TSMatrix M = NewMatrix(6, 7);
	TSMatrix N;
	//向矩阵中插入数据
	InsertElem(&M, 1, 2, 11);
	InsertElem(&M, 1, 3, 21);
	InsertElem(&M, 2, 4, 2);
	InsertElem(&M, 3, 1, 92);
	InsertElem(&M, 3, 6, 85);
	InsertElem(&M, 4, 3, 12);
	InsertElem(&M, 5, 2, 26);
	InsertElem(&M, 6, 5, 10);
	//打印矩阵
	printf("\nM:");
	sMatrixPrint(&M);
	//打印使用方案a转置的矩阵
	sMatrixTranspose(&M, &N);
	printf("\nN(Transpose of M)——a:");
	sMatrixPrint(&N);
	//打印使用方案b转置的矩阵
	sMatrixFastTranspose(&M, &N);
	printf("\nN(Transpose of M)——b:");
	sMatrixPrint(&N);
	return 0;
}
