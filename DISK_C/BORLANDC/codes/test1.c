//��6��
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
//��7��
//#include <stdio.h>
//void main()
//{
//	double x = 0;
//	printf("������x��ֵ");
//	scanf_s("%lf", &x);
//	if (x < 1)
//		printf("%lf", x);
//	else
//		if (1 <= x < 10)
//			printf("%lf", 2 * x - 1);
//		else
//			printf("%lf", 3 * x - 11);
//}
//��8��
#include <stdio.h>
void main()
{
	int num = 0, a = 1;//a���ڱ�ʾλ��
	printf("������һ��������5λ��������");
	scanf_s("%d", &num);
	if (0 < num < 100000)
	{
		while (num / 10 > 0)
		{
			num = num / 10;
			a++;
		}
		printf("λ����%d", a);
	}
	else
	{
		printf("error!");
	}
}