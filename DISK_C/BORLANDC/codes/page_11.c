#include <stdio.h>
static int main()
{
	int c, nl, nw, nc, inword;
	nl = nw = nc = 0;
	while ((c = getchar()) != EOF)
	{
		nc++;
		if (c == '\n')
			nl++;
		if (c == ' ' || c == '\t' || c == '\n')
			inword = 0;
		else if (inword == 0)
		{
			inword = 1;
			nw++;

		}
	}
	printf("nl=%d,nw=%d,nc=%d", nl, nw, nc);
	return 0;
}