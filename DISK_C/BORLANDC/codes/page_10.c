#include <stdio.h>
int main()
{
	int r, h;
	float v;
	r = h = 0; v = 0;
	scanf("%d%d",&r,&h);
	v = 3.14159 * r * r * h;
	printf("v=%f\n",v);
	return 0;
}