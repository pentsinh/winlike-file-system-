#include <stdio.h>
int length(char*);
void copy(char*, char*);
void connect(char*, char*);
void main()
{
	char* s1[100], * s2[100];
	int k;
	printf("enter s1\n");
	gets(s1);
	printf("enter s2\n");
	gets(s2);
	printf("choose a func (1/2/3)\n");
	scanf("%d", &k);
	switch (k)
	{
	case 1:printf("length of s1 = %d", length(s1)); break;
	case 2: 
	{
		copy(s1, s2);
		puts(s1);
		break;
	}
	case 3: 
	{
		connect(s1, s2);
		puts(s1);
		break;
	}
	default:
		break;
	}
	
	
}

int length(char*s1)
{
	int n = 0;
	while (*(s1 + n) != '\0')	
		n++;	
	return n;//这里的长度不包括\0
}

void copy(char* s1, char* s2)
{
	int n = 0;
	do
	{
		*(s1 + n) = *(s2 + n);
		n++;
	} while (*(s2 + n) != '\0');
}

void connect(char* s1, char* s2)
{
	int n, i;	
	n = length(s1) + 1;
	i = 0;
	do
	{
		*(s1 + n) = *(s2 + i);
	} while (*(s2 + i) != '\0');
}
