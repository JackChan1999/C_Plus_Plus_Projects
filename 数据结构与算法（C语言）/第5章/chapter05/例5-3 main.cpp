#include "Mat.h"

int main()
{
	ElemType a[ROW][COL] = { { 1, 0, 0, 2 }, { 0, 0, 1, 0 }, { 0, 0, 0, 1 } };
	MatNode *mat;
	cmatCreate(mat, a);
	cmatPrint(mat);
	return 0;
}