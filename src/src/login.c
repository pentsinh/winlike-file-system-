#include <graphics.h>
#include <dos.h>
#include <conio.h>
#include <string.h>
//#include <stdlib.h>
//#include <time.h>
#include "include.h"

#define MAX_LENGTH 10
#define PASSWORD "123456"

int is_right = 0;//是否允许登陆
char password[MAX_LENGTH + 1] = "__________\0";//存放用户输入的密码
int i = -1;//表示当前输入的密码在password中的位置,采用先移位再录入，所以i初始化为-1

//登陆界面的绘制，调用其他登陆相关函数
int login()
{
	
	int is_entering = 0;//是否正在输入
	
	union REGS regs;	 //用于读取键盘缓冲区

	welcome();

	setbkcolor(BLUE);
	setcolor(YELLOW); // 设置文本颜色为黄色
	settextstyle(DEFAULT_FONT, HORIZ_DIR, 2); 

	puthz(308, 200, "用户", 24, 10, WHITE);
	rectangle(280, 220, 360, 260);

	while (1)
	{
		newmouse(&MouseX, &MouseY, &press);
		outtextxy(280, 220, password);

		if (mouse_press(280, 220, 360, 260) == 1)
			is_entering = 1;
		if (mouse_press(0, 0, 640, 220) == 1 || mouse_press(0, 220, 280, 260) == 1 || mouse_press(360, 220, 640, 260) == 1 || mouse_press(0, 260, 640, 480) == 1)
			is_entering = 0;
		if (is_entering == 1)
		{
			if (mouse_press(280, 220, 360, 260) != 0)
				MouseS = 2;
			else
				MouseS = 0;
			getbuffer_keybd(password);

			if (is_right == 1)
				return 1;
			else if (is_right == -3)
				return 0;

		}

	}
}


//欢迎界面
void welcome()
{
	setbkcolor(BLUE);
	setcolor(YELLOW); // 设置文本颜色为黄色
	//settextstyle(DEFAULT_FONT, HORIZ_DIR, 2); // 设置文本样式
	rectangle(10, 10, 630, 470);
	puthz(308, 228, "登陆", 24, 0, WHITE);

	while (!kbhit())// 循环，直到按下键盘键
		newmouse(&MouseX, &MouseY, &press);
	cleardevice();
}

//获取键盘输入
void getbuffer_keybd(char* password)
{	
	union REGS regs;	 //用于读取键盘缓冲区
	//char ch;//这次输入的字符
	if (bioskey(1) == 0) 
	{
		return;
	}
	else if (i < MAX_LENGTH)
	{
		regs.h.ah = 0x00;
		int86(0x16, &regs, &regs);//获取16位寄存器的后八位ASCII码
		//ch = regs.h.al;
		if (regs.h.al == 0x08)//退格
		{
			password[i] = '_';
			if (i != -1)
				i -= 1;
			
			

		}
		else if (regs.h.al == 0x0D)//回车
		{
			i = i + 1;
			password[i] = '\0';
			judge(password);
		}
		else if (i < MAX_LENGTH - 1)
		{
			i = i + 1;
			password[i] = regs.h.al;

		}

		cleardevice();
		puthz(308, 200, "用户", 24, 10, WHITE);
		rectangle(280, 220, 360, 260);
	}
}

void judge(char password[MAX_LENGTH])
{
	if (strcmp(password, PASSWORD) == 0)
		is_right = 1;
	else
	{
		is_right -= 1;//用于统计失败的次数
		strcpy(password, "__________\0");
		i = -1;
	}

}