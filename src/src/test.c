#include <graphics.h>
#include <dos.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "include.h"
extern time_t press_time[10];


//测试鼠标双击检测

//int main()
//{
//	char chart_left[10][10] = { 0 };//
//	char chart_right[10][10] = { 0 };
//	int i;
//	int flag = 0;
//	int gd = DETECT, gm;  // 图形驱动和图形模式    
//	initgraph(&gd, &gm, "C:\\BORLANDC\\BGI");// 初始化图形模式
//	mouseinit();
//
//	setbkcolor(BLUE);
//	setcolor(YELLOW); // 设置文本颜色为黄色
//	settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
//
//	puthz(308, 200, "用户", 24, 10, WHITE);
//	
//	rectangle(280, 220, 360, 260);
//	while (1)
//	{
//		newmouse(&MouseX, &MouseY, &press);
//		itoa(mouse_press(280, 220, 360, 260), chart_right[0], 10);//0号位
//		if (strcmp(chart_right[0], "4") == 0 && flag == 0)
//		{
//			setbkcolor(YELLOW);
//			flag = 1;
//		}
//		else if (strcmp(chart_right[0], "4") == 0 && flag == 1)
//		{
//			setbkcolor(BLUE);
//			flag = 0;
//		}
//		
//		if (strcmp(chart_right[0], "0") != 0 && strcmp(chart_right[0], "2") != 0)
//		{
//			cleardevice();
//			puthz(308, 200, "用户", 24, 10, WHITE);
//			rectangle(280, 220, 360, 260);
//
//			/*for (i = 1; i < 10; i++)
//			{
//				strcpy(chart[10 - i], chart[9 - i]);
//			}
//			ltoa(clock(), chart[0], 10);*/						
//				for (i = 0; i < 10; i++)
//					ltoa(press_time[i], chart_left[i], 10);
//			if (strcmp(chart_right[0], chart_right[1]) != 0)
//			{
//				for (i = 1; i < 10; i++)
//				{
//					strcpy(chart_right[10 - i], chart_right[9 - i]);
//				}
//			}
//			for (i = 0; i < 10; i++)
//			{
//				outtextxy(10, i * 48, chart_left[i]);
//				outtextxy(540, i * 48, chart_right[i]);
//			}
//
//		}
//
//	}
//	return 1;
//		
//}


//int main()
//{
//	char chart_left[10][10] = { 0 };//
//	char chart_right[10][10] = { 0 };
//	int i;
//	int flag = 0;
//	int gd = DETECT, gm;  // 图形驱动和图形模式    
//	initgraph(&gd, &gm, "C:\\BORLANDC\\BGI");// 初始化图形模式
//	mouseinit();
//
//	setbkcolor(BLUE);
//	setcolor(RED); // 设置文本颜色为黄色
//	settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
//
//	puthz(308, 200, "用户", 24, 10, WHITE);
//
//	rectangle(280, 220, 360, 260);
//	while (1)
//	{
//		newmouse(&MouseX, &MouseY, &press);
//		if (mouse_press(280, 220, 360, 260) == 4 && flag == 0)
//		{
//			setbkcolor(YELLOW);
//			flag = 1;
//		}
//		else if (mouse_press(280, 220, 360, 260) == 4 && flag == 1)
//		{
//			setbkcolor(BLUE);
//			flag = 0;
//		}
//	}
//	return 1;
//}


//int main()
//{
//	int last_press = 0;
//
//	char chart_left[10][10] = { 0 };//
//	char chart_right[10][10] = { 0 };
//	int i;
//	int flag = 0;
//	int gd = DETECT, gm;  // 图形驱动和图形模式    
//	initgraph(&gd, &gm, "C:\\BORLANDC\\BGI");// 初始化图形模式
//	mouseinit();
//
//	setbkcolor(BLUE);
//	setcolor(RED); // 设置文本颜色为黄色
//	settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
//
//	puthz(308, 200, "用户", 24, 10, WHITE);
//
//	rectangle(280, 220, 360, 260);
//	while (1)
//	{
//		last_press = press;
//		newmouse(&MouseX, &MouseY, &press);
//		if (last_press != press)
//		{
//			outtextxy(1, i * 10, "2");
//			i++;
//			//break;
//		}
//		/*if (last_press != press && flag == 0)
//		{
//			outtextxy(1, i * 10, "1");
//			i++;
//			setbkcolor(YELLOW);
//			flag = 1;
//		}
//		else if (last_press != press && flag == 1)
//		{
//			outtextxy(1, i * 10, "2");
//			i++;
//			setbkcolor(BLUE);
//			flag = 0;
//		}*/
//
//	}
//	return 1;
//}
extern last_press_time;
extern last_click_time;
void main()
{
	int last_press = 0;
	char box[10] = { 0 };

	char chart_left[10][10] = { 0 };//
	char chart_right[10][10] = { 0 };
	int i;
	int flag = 0;
	int gd = DETECT, gm;  // 图形驱动和图形模式    
	initgraph(&gd, &gm, "C:\\BORLANDC\\BGI");// 初始化图形模式
	mouseinit();

	setbkcolor(BLUE);
	setcolor(RED); // 设置文本颜色为黄色
	settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);

	node:
	puthz(308, 200, "用户", 24, 10, WHITE);

	rectangle(280, 220, 360, 260);
	rectangle(380, 320, 460, 360);

	while (1)
	{
		newmouse(&MouseX, &MouseY, &press);
		last_press = mouse_press(280, 220, 360, 260);
		if (last_press != 3 && last_press != 2 && last_press != 0)
		{
			outtextxy(30, 30, ltoa((long)last_click_time, box, 10));
			outtextxy(10, 10, itoa(last_press, box, 10));
		}
		else if(last_press==3)
		{
			cleardevice();
			goto node;
		}
		if (mouse_press(380, 320, 460, 360) == 1)
		{
			cleardevice();
			goto node;
		}
		//if (mouse_press(280, 220, 360, 260) == 1)
		//	flag = 1;
		//if (mouse_press(280, 220, 360, 260) == 2 && flag == 1)
		//	break;
	}
}


//测试时间
//int main() {
//    // 获取当前时间
//    time_t rawtime;
//    struct tm* timeinfo;
//    char buffer[80];
//    time(&rawtime);
//    timeinfo = localtime(&rawtime);  // 将时间转换为本地时间
//
//    // 打印格式化后的时间
//    printf("当前时间: %s", asctime(timeinfo));  // 使用 asctime 函数将时间转换为字符串
//
//    // 或者使用 strftime 函数自定义输出格式
//    
//    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo);
//    printf("当前时间: %s\n", buffer);
//
//    return 0;
//}