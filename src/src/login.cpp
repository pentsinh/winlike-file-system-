// #include <graphics.h>
// #include <dos.h>
// #include <conio.h>
// #include <bios.h>
// #include <string.h>
// #include <stdio.h>

#include "include.h"

#define MAX_LENGTH 10
#define PASSWORD "123456"

int is_right = 0;								// 是否允许登陆
char password[MAX_LENGTH + 1] = "__________\0"; // 存放用户输入的密码
int i = -1;										// 表示当前输入的密码在password中的位置,采用先移位再录入，所以i初始化为-1

// 登陆界面的绘制，调用其他登陆相关函数
int login()
{

	int is_entering = 0; // 是否正在输入

	union REGS regs; // 用于读取键盘缓冲区

	user();

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
		{
			is_entering = 1;
			clear_keyboard_buffer();
			// char ch;
			// while (ch = getchar() != EOF && ch != '\0')
			// {
			// 	// 清空误触输入的字符
			// }
		}
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

// 欢迎界面
void user()
{
	cleardevice();
	setbkcolor(BLUE);
	setcolor(YELLOW); // 设置文本颜色为黄色
	// settextstyle(DEFAULT_FONT, HORIZ_DIR, 2); // 设置文本样式
	rectangle(10, 10, 630, 470);
	puthz(308, 228, "登陆", 24, 0, WHITE);

	while (!kbhit()) // 循环，直到按下键盘键
		newmouse(&MouseX, &MouseY, &press);
	clrmous(MouseX, MouseY);
	cleardevice();
}

void welcome()
{
	cleardevice();
	setbkcolor(BLUE);
	setcolor(WHITE);
	settextstyle(DEFAULT_FONT, HORIZ_DIR, 4);
	outtextxy(50, 50, ":P Coming Soon");
	puthz(50, 100, "正在构建目录树", 24, 2, WHITE);
	puthz(50, 150, "这会需要一些时间", 24, 2, WHITE);
	puthz(50, 200, "请耐心等候", 24, 2, WHITE);
	puthz(50, 250, "如果时间过长请重新启动", 24, 2, WHITE);
	settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
	outtextxy(500, 470, "by lxb & pentsinh");
	// delay(3000);
}

// 获取键盘输入
static void getbuffer_keybd(char *password)
{
	union REGS regs; // 用于读取键盘缓冲区
	// char ch;//这次输入的字符
	if (bioskey(1) == 0)
	{
		// printf("%d\n", bioskey(1));
		return;
	}
	else if (i < MAX_LENGTH)
	{
		regs.h.ah = 0x00;
		int86(0x16, &regs, &regs); // 获取16位寄存器的后八位ASCII码
		// ch = regs.h.al;
		if (regs.h.al == 0x08) // 退格
		{
			password[i] = '_';
			if (i != -1)
				i -= 1;
		}
		else if (regs.h.al == 0x0D) // 回车
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
		is_right -= 1; // 用于统计失败的次数
		strcpy(password, "__________\0");
		i = -1;
	}
}

// 清空键盘缓冲区
void clear_keyboard_buffer()
{
	union REGS regs;
	while (bioskey(1)) // 检查键盘缓冲区是否为空
	{
		regs.h.ah = 0x00;
		int86(0x16, &regs, &regs); // 读取并丢弃键盘缓冲区中的字符
	}
}

// 计算三点圆弧，原版算法来自github
void radius_3pts(float x1, float y1, float x2, float y2, float x3, float y3, int *circle)
{
	float a, b, c, d, e, f, r, x, y;
	a = 2 * (x2 - x1);
	b = 2 * (y2 - y1);
	c = x2 * x2 + y2 * y2 - x1 * x1 - y1 * y1;
	d = 2 * (x3 - x2);
	e = 2 * (y3 - y2);
	f = x3 * x3 + y3 * y3 - x2 * x2 - y2 * y2;
	x = (b * f - e * c) / (b * d - e * a);
	y = (d * c - a * f) / (b * d - e * a);
	r = sqrt((x - x1) * (x - x1) + (y - y1) * (y - y1));
	circle[0] = (int)x;
	circle[1] = (int)y;
	circle[2] = (int)r;
	circle[3] = (int)(atan2(y - y2, x2 - x) / M_PI * 180); // 注意BC的y轴是向下的
	circle[4] = (int)(atan2(y - y1, x1 - x) / M_PI * 180);
}

void power_on()
{
	draw_windows(315, 130, 5);
	setcolor(WHITE);
	settextstyle(DEFAULT_FONT, HORIZ_DIR, 6);
	outtextxy(140, 300, "Windows");
	settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
	outtextxy(135, 275, "HUST AIA");
	setcolor(RED);
	settextstyle(DEFAULT_FONT, HORIZ_DIR, 4);
	outtextxy(455, 285, "xb");
	delay(3000);
	cleardevice();
}

void draw_windows(int x, int y, int size)
{

	draw_window(x, y, size, RED);
	draw_window(x + size * 16, y + size * 2, size, GREEN);
	draw_window(x - size * 4, y + size * 14, size, BLUE);
	draw_window(x + size * 12, y + size * 16, size, YELLOW);
}
void draw_window(int x, int y, int size, int color)
{
	int circle[5] = {0}; // 0:x , 1:y , 2:r , 3:stangle , 4:endangle
	setcolor(WHITE);
	line(x, y, x - size * 3, y + size * 11); //-15,+55     345，135
	line(x + size * 13, y + size, x + size * 10, y + size * 12);
	if (color == RED || color == BLUE)
	{
		radius_3pts(x, y, x + size * 13, y + size, x + size * 6, y - size, circle);
		arc(circle[0], circle[1], circle[3], circle[4], circle[2]);
		radius_3pts(x - size * 3, y + size * 11, x + size * 10, y + size * 12, x + size * 3, y + size * 10, circle);
		arc(circle[0], circle[1], circle[3], circle[4], circle[2]);
		setfillstyle(SOLID_FILL, color);
		floodfill((x + x + size * 10) / 2, (y + y + size * 12) / 2, WHITE);
	}
	else if (color == GREEN || color == YELLOW)
	{
		radius_3pts(x + size * 13, y + size, x, y, x + size * 6, y + size, circle);
		circle[0] -= size / 2; // 强制类型转换修正
		arc(circle[0], circle[1], circle[3], circle[4], circle[2]);
		radius_3pts(x + size * 10, y + size * 12, x - size * 3, y + size * 11, x + size * 3, y + size * 12, circle);
		circle[0] -= size / 2; // 强制类型转换修正
		arc(circle[0], circle[1], circle[3], circle[4], circle[2]);
		setfillstyle(SOLID_FILL, color);
		floodfill((x + x + size * 10) / 2, (y + y + size * 12) / 2, WHITE);
	}
}