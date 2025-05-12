#include <stdio.h>
void main()
{
	char c;
	printf("Input print_char : ");
	scanf_s("%c", &c);
	printf("%4c\t%c\n", c, c);
	printf("%2c\t%c\t%3c\t%c\n", c, c, c, c);
	printf("%c\t%c\t%5c\t%c\n", c, c, c, c);
	printf("%c\t%c\t%5c\t%c\n", c, c, c, c);
	printf("%2c\t%5c\n", c, c);
	printf("%3c\t%5c\n", c, c);
	printf("%2c\t%5c\n", c, c);
	printf("%c\t%c\t%5c\t%c\n", c, c, c, c);
	printf("%c\t%c\t%5c\t%c\n", c, c, c, c);
	printf("%2c\t%c\t%3c\t%c\n", c, c, c, c);
	printf("%4c\t%c\n", c, c);
}
//#include <stdio.h>
//void main()
//{
//	int a = 1, b = 1;
//	a += b += 1;
//	{
//		int a = 10, b = 10;
//		a += b += 10;
//		printf("b=%d\t", b);
//	}
//	a *= a *= b * 10;
//	printf("a=%2d\n", a);
//}
//#include<stdio.h>
//void main()
//{
//	int a = 1, b = 2, c = 3;
//	++a;
//	b += ++c;
//	{
//		int b = 4, c = 5;
//		c = b * c;
//		a += b += c;
//		printf("a1=%d,b1=%d\n", a, b, c);
//	}
//	printf("a2=%d,b2=%d\n", a, b, c);
//}