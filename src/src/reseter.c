#include <stdio.h>
#include <time.h>
#include <stdlib.h>
extern click_flag;
void reseter()//�ӽ��̺���
{
	delay(600);
	if (click_flag == 1)
		click_flag = 0;
	exit(0);
}