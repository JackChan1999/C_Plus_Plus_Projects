#include "gList.h"
//测试代码主函数
int main()
{
	LSNode *ls;
	printf("请输入广义表：");
	LSCreate(&ls);
	LSDis(ls);
	int len = LSLength(ls);
	printf("\nlen = %d\n", len);
	int dep = LSDepth(ls);
	printf("dep = %d\n", dep);
	return 0;
}
