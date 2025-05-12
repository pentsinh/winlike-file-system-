/* print string as uppercase */
#include <stdio.h>
#define SIZE 80
void putupper(char ch);
int main()
{
	char str[SIZE];
	int i;

	gets(str);

	for (i = 0; str[i] != '\0'; i++)
	{
		putupper(str[i]);
	}
	return 0;
}
void putupper(char ch)
{
	char cc;

	cc = (ch > 'a' && ch < 'z') ? ch + 'A' - 'a' : ch;
	putchar(cc);
}