#include <stdio.h>
#include <time.h>
#include <stdlib.h>
extern click_flag;
void reseter()//子进程函数
{
	delay(600);
	if (click_flag == 1)
		click_flag = 0;
	exit(0);
}