#include <graphics.h>
#include <dos.h>
#include <conio.h>
#include <string.h>
//#include <stdlib.h>
#include <time.h>
#include "include.h"

int main()
{
	int gd = DETECT, gm;  // 图形驱动和图形模式    
	initgraph(&gd, &gm, "C:\\BORLANDC\\BGI");// 初始化图形模式
	mouseinit();

	setbkcolor(BLUE);
	setcolor(YELLOW); // 设置文本颜色为黄色
	settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);

	puthz(308, 200, "用户", 24, 10, WHITE);
	
	rectangle(280, 220, 360, 260);
	while (1)
	{
		newmouse(&MouseX, &MouseY, &press);
		if (mouse_press(280, 220, 360, 260) == 4)
			break;
	}
	return 1;
		
}