#include <graphics.h>
#include <dos.h>
#include <conio.h>
#include <string.h>
//#include <stdlib.h>
#include <time.h>
#include "include.h"

int main()
{
	int gd = DETECT, gm;  // ͼ��������ͼ��ģʽ    
	initgraph(&gd, &gm, "C:\\BORLANDC\\BGI");// ��ʼ��ͼ��ģʽ
	mouseinit();

	setbkcolor(BLUE);
	setcolor(YELLOW); // �����ı���ɫΪ��ɫ
	settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);

	puthz(308, 200, "�û�", 24, 10, WHITE);
	
	rectangle(280, 220, 360, 260);
	while (1)
	{
		newmouse(&MouseX, &MouseY, &press);
		if (mouse_press(280, 220, 360, 260) == 4)
			break;
	}
	return 1;
		
}