#include "Matrix.h"

TSMatrix NewMatrix(int m, int n){
	//新建一个三元组表示的稀疏矩阵   
	TSMatrix M;
	M.rows = m;
	M.cols = n;
	M.nums = 0;
	return M;
}
Status InsertElem(TSMatrix *M, int row, int col, ElemType value){
	//在三元组表示的稀疏矩阵M，第 row 行，第 col 列位置插入元素value   
	//插入成功，返回0，否则返回-1   
	int i, t, p;
	if (M->nums >= MAXSIZE){//当前三元组表已满   
		printf("\nError:There is no space in the matrix;\n");
		return 0;
	}
	//数组越界
	if (row>M->rows || col>M->cols || row<1 || col<1){
		printf("\nError:Insert position is beyond the arrange.\n");
		return -1;
	}
	p = 1;//标志新元素应该插入的位置   
	if (M->nums == 0){//插入前矩阵M没有非零元素   
		M->data[p].row = row;
		M->data[p].col = col;
		M->data[p].value = value;
		M->nums++;
		return 0;
	}
	for (t = 1; t <= M->nums; t++)//寻找合适的插入位置  
	{
		//行比当前行大，p++
		if (row > M->data[t].row)
			p++;
		//行相等但是列比当前列大,p++
		if ((row == M->data[t].row) && (col > M->data[t].col))
			p++;
	}
	//插入前，该位置已有数据，则更新数值
	if (row == M->data[t - 1].row && col == M->data[t - 1].col){
		M->data[t - 1].value = value;
		return 0;
	}
	for (i = M->nums; i >= p; i--){//移动p之后的元素   
		M->data[i + 1].row = M->data[i].row;
		M->data[i + 1].col = M->data[i].col;
		M->data[i + 1].value = M->data[i].value;
	}
	//插入新元素   
	M->data[p].row = row;
	M->data[p].col = col;
	M->data[p].value = value;
	M->nums++;
	return 0;
}


Status sMatrixTranspose(const TSMatrix *M, TSMatrix *N){
	//采用三元组表存储表示，求稀疏矩阵M的转置矩阵T   
	int col, p, q;
	N->rows = M->cols;
	N->cols = M->rows;
	N->nums = M->nums;
	if (N->nums){
		q = 1;
		for (col = 1; col <= M->rows; col++)
		for (p = 1; p <= M->nums; p++)
		if (M->data[p].col == col){
			N->data[q].row = M->data[p].col;
			N->data[q].col = M->data[p].row;
			N->data[q].value = M->data[p].value;
			q++;
		}
	}
	return OK;
}

Status sMatrixFastTranspose(const TSMatrix *M, TSMatrix *N)
{
	//矩阵N的成员初始化
	N->rows = M->cols;
	N->cols = M->rows;
	N->nums = M->nums;
	if (N->nums)	//如果矩阵中有非零元素
	{
		int col;		//辅助数组的下标
		int num[COLS + 1] = { 0 }, cpot[COLS + 2] = { 0 };
		int t;
		for (t = 1; t <= M->cols; t++)
			num[M->data[t].col]++;		//求M中每一列中非零元素个数
		cpot[1] = 1;	//第一行的第一个非零元素的位置肯定在1
		for (col = 2; col <= M->nums; col++)
			//第col行的第一个非零元素的位置，
			//等于它前一行的第一个非零元素的位置，加上该行非零元素的个数
			cpot[col] = cpot[col - 1] + num[col - 1];
		int p, q;
		for (p = 1; p <= M->nums; p++)
		{
			col = M->data[p].col;
			q = cpot[col];
			N->data[q].row = M->data[p].col;
			N->data[q].col = M->data[p].row;
			N->data[q].value = M->data[p].value;
			cpot[col]++;
		}
	}
	return 0;
}

void sMatrixPrint(const TSMatrix *M){
	//打印稀疏矩阵所有元素   
	int i, j, p = 1;
	printf("\nsize:%d × %d\n", M->rows, M->cols);
	if (!M->nums){//0矩阵   
		printf("%d\n", 0.0);
		return;
	}
	for (i = 1; i <= M->rows; i++){
		for (j = 1; j <= M->cols; j++){
			if (i == M->data[p].row && j == M->data[p].col){
				printf("%d\t", M->data[p].value);
				p++;
			}
			else{
				printf("%d\t", 0.0);
			}
		}
		printf("\n");
	}
	printf("\n");
}
