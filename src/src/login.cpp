// #include <graphics.h>
// #include <dos.h>
// #include <conio.h>
// #include <bios.h>
// #include <string.h>
// #include <stdio.h>

#include "include.h"

#define MAX_LENGTH 10
#define PASSWORD "123456"

int is_right = 0;					  // �Ƿ������½
char password[MAX_LENGTH + 1] = "\0"; // ����û����������
int i = -1;							  // ��ʾ��ǰ�����������password�е�λ��,��������λ��¼�룬����i��ʼ��Ϊ-1

// ��½����Ļ��ƣ�����������½��غ���
int login()
{

	int is_entering = 0; // �Ƿ���������

	union REGS regs; // ���ڶ�ȡ���̻�����

	user();

	setbkcolor(BLUE);
	setcolor(YELLOW); // �����ı���ɫΪ��ɫ
	settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);

	puthz(308, 200, "�û�", 12, 10, WHITE);
	rectangle(260, 220, 380, 240);

	while (1)
	{
		newmouse(&MouseX, &MouseY, &press);
		// outtextxy(280, 220, password);

		if (mouse_press(280, 220, 360, 260) == 1)
		{
			is_entering = 1;
			clear_keyboard_buffer();
		}
		if (mouse_press(0, 0, 640, 220) == 1 || mouse_press(0, 220, 280, 260) == 1 || mouse_press(360, 220, 640, 260) == 1 || mouse_press(0, 260, 640, 480) == 1)
			is_entering = 0;
		if (is_entering == 1)
		{
			if (mouse_press(280, 220, 360, 260) != 0)
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
				out_keybd(password, 10, 262, 222, 1, BLUE, WHITE);
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

// ��ӭ����
void user()
{
	cleardevice();
	setbkcolor(BLUE);
	setcolor(YELLOW); // �����ı���ɫΪ��ɫ
	// settextstyle(DEFAULT_FONT, HORIZ_DIR, 2); // �����ı���ʽ
	rectangle(10, 10, 630, 470);
	puthz(308, 228, "��½", 24, 0, WHITE);

	while (!kbhit()) // ѭ����ֱ�����¼��̼�
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
	puthz(50, 100, "���ڹ���Ŀ¼��", 24, 2, WHITE);
	puthz(50, 150, "�����ҪһЩʱ��", 24, 2, WHITE);
	puthz(50, 200, "�����ĵȺ�", 24, 2, WHITE);
	puthz(50, 250, "���ʱ���������������", 24, 2, WHITE);
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
		is_right -= 1; // ����ͳ��ʧ�ܵĴ���
		strcpy(password, "\0");
		i = -1;
	}
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
