#include "include.h"

#define MAX_LENGTH 10
#define PASSWORD "123456"

int is_right = 0;					// 是否允许登陆
char password[MAX_LENGTH + 1] = ""; // 存放用户输入的密码
int i = -1;							// 表示当前输入的密码在password中的位置,采用先移位再录入，所以i初始化为-1

// 登陆界面的绘制，调用其他登陆相关函数
int login()
{

	int is_entering = 1; // 是否正在输入

	union REGS regs; // 用于读取键盘缓冲区

	user();

	// setbkcolor(BLUE);

	// puthz(308, 200, "用户", 12, 10, WHITE);
	settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
	clearRectangle(280, 268, 360, 292, WHITE);
	setcolor(BLACK);
	rectangle(280, 268, 360, 292);
	clear_keyboard_buffer();

	while (1)
	{
		newmouse(&MouseX, &MouseY, &press);
		// outtextxy(280, 220, password);

		if (detect_m(280, 268, 360, 292) == 1 && press == 1)
		{
			is_entering = 1;
			clear_keyboard_buffer();
		}
		if (mouse_press_out(280, 268, 360, 292) == 1)
			is_entering = 0;
		if (is_entering == 1)
		{
			// printf("1");
			blbl(282, 274, password, 2, BLACK, WHITE);
			if (detect_m(280, 268, 360, 292) == 1)
			{
				MouseS = 2;
				newmouse(&MouseX, &MouseY, &press);
			}
			else
			{
				MouseS = 0;
				newmouse(&MouseX, &MouseY, &press);
			}

			int result = getbuffer_keybd(password, 10);
			if (result == 1)
			{
				out_keybd(password, 10, 282, 274, 1, WHITE, BLACK);
			}
			else if (result == 2)
			{
				judge(password);
			}

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
	setbkcolor(BLACK);
	// setcolor(YELLOW); // 设置文本颜色为黄色
	// rectangle(10, 10, 630, 470);
	// puthz(308, 228, "登陆", 24, 0, WHITE);
	bmp_convert("C:\\PROJECT\\src\\Images\\BMP\\login_1.bmp", "C:\\PROJECT\\src\\Images\\DBM\\login_1.dbm");
	show_dbm(8, 0, "C:\\PROJECT\\src\\Images\\DBM\\login_1.dbm", 0);
	while (!kbhit()) // 循环，直到按下键盘键
		newmouse(&MouseX, &MouseY, &press);
	clrmous(MouseX, MouseY);
	// cleardevice();
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

void judge(char password[MAX_LENGTH])
{
	if (strcmp(password, PASSWORD) == 0)
		is_right = 1;
	else
	{
		is_right -= 1; // 用于统计失败的次数
		strcpy(password, "\0");
		i = -1;
	}
}

void power_on()
{
	draw_windows(315, 130, 5);
	setcolor(WHITE);
	settextstyle(DEFAULT_FONT, HORIZ_DIR, 6);
	outtextxy(140, 300, "Windos");
	settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
	outtextxy(135, 275, "HUST AIA");
	setcolor(RED);
	settextstyle(DEFAULT_FONT, HORIZ_DIR, 4);
	outtextxy(455, 285, "xb");
	delay(3000);
	cleardevice();
}
