//T3
/*#include <stdio.h>
void main()
{
	int i = 1, sum = 0;
	while (i <= 100)
	{
		sum += i;
		i++;
	}
	printf("%d", sum);
}*/

//T8
/*int length(int x)
{
	int y = 1;
	while (x > 9)
	{
		x /= 10;
		y++;
	}
	return y;
}

int trans(int x)
{
	int y = 0;
	do
	{
		y = y * 10 + x % 10;
		x /= 10;
	} while (x > 0);
	return y;
}
void print(int x)
{
	if (x > 9)
	{
		print(x / 10);
	}
	printf("%d\t", x % 10);
}

#include <stdio.h>
void main()
{
	int num = 0;
	printf("please key in a number\n");
	scanf("%d", &num);
	if (num > 0 && num < 100000)
	{
		printf("%d\n", length(num));
		printf("\n");
		print(num);
		printf("\n");
		num = trans(num);
		print(num);


	}
	else
		printf("error\n");
}*/

//T10
/*#include <stdio.h>
int three(int i)
{
	if (i % 3 == 0)
		return 1;
	else
		return 0;
}

int five(int i)
{
	int n = 0;
	while (i > 0)
	{
		if (i % 5 == 0 && i % 10 != 0)
		{
			n++;
			break;
		}
		else
			i /= 10;
		return n;
	}
}

void main()
{
	int i;
	for (i = 1; i < 1000; i++)
	{
		if (three(i) && five(i))
			printf("%d\n", i);
	}
}*/

//extra
/*#include <stdio.h>
void grade(int x)
{
	if (x >= 0 && x <= 100)
	{
		switch (x / 10)
		{
		case 10:
		case 9:printf("A\n"); break;
		case 8:
			if (x >= 85)
			{
				printf("A\n");
			}
			else
			{
				printf("B\n");
			}
			break;
		case 7:printf("B\n"); break;
		case 6:printf("C\n"); break;
		case 5:
		case 4:
		case 3:
		case 2:
		case 1:
		case 0:printf("D\n"); break;
		}
	}
	else
		printf("error\n");
}
void main()
{
	int pswd = 0, time = 0, score = 0;
	for(time=1;time<4;time++)
	{
		scanf("%d", &pswd);
		if (pswd == 1234)
		{
			printf("Right!\nkey in the score\n");
			scanf("%d", &score);
			grade(score);
			break;
		}
		else
		{
			if (time == 3)
			{
				printf("error!\n");
				break;
			}
			else
				printf("try again!\n");
		}
	}
}*/