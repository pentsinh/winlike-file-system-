//第6题
//#include <stdio.h>
//void main()
//{
//	int i, a = 8, b = 1, sum = 0;
//	for (i = 0; i < 10; i++)
//	{
//		sum += a;
//		b += 3;
//		a += b;
//	}
//	printf("%d", sum);
//}
//第7题
//#include <stdio.h>
//void main()
//{
//	double x = 0;
//	printf("请输入x的值");
//	scanf_s("%lf", &x);
//	if (x < 1)
//		printf("%lf", x);
//	else
//		if (1 <= x < 10)
//			printf("%lf", 2 * x - 1);
//		else
//			printf("%lf", 3 * x - 11);
//}
//第8题
#include <stdio.h>
void main()
{
	int num = 0, a = 1;//a用于表示位数
	printf("请输入一个不多于5位的正整数");
	scanf_s("%d", &num);
	if (0 < num < 100000)
	{
		while (num / 10 > 0)
		{
			num = num / 10;
			a++;
		}
		printf("位数是%d", a);
	}
	else
	{
		printf("error!");
	}
}