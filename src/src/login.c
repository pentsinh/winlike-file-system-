#include <graphics.h>
#include <dos.h>
#include <conio.h>
#include <string.h>
//#include <stdlib.h>
//#include <time.h>
#include "include.h"

#define MAX_LENGTH 10
#define PASSWORD "123456"

int is_right = 0;//�Ƿ������½
char password[MAX_LENGTH + 1] = "__________\0";//����û����������
int i = -1;//��ʾ��ǰ�����������password�е�λ��,��������λ��¼�룬����i��ʼ��Ϊ-1

//��½����Ļ��ƣ�����������½��غ���
int login()
{
	
	int is_entering = 0;//�Ƿ���������
	
	union REGS regs;	 //���ڶ�ȡ���̻�����

	welcome();

	setbkcolor(BLUE);
	setcolor(YELLOW); // �����ı���ɫΪ��ɫ
	settextstyle(DEFAULT_FONT, HORIZ_DIR, 2); 

	puthz(308, 200, "�û�", 24, 10, WHITE);
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


//��ӭ����
void welcome()
{
	setbkcolor(BLUE);
	setcolor(YELLOW); // �����ı���ɫΪ��ɫ
	//settextstyle(DEFAULT_FONT, HORIZ_DIR, 2); // �����ı���ʽ
	rectangle(10, 10, 630, 470);
	puthz(308, 228, "��½", 24, 0, WHITE);

	while (!kbhit())// ѭ����ֱ�����¼��̼�
		newmouse(&MouseX, &MouseY, &press);
	cleardevice();
}

//��ȡ��������
void getbuffer_keybd(char* password)
{	
	union REGS regs;	 //���ڶ�ȡ���̻�����
	//char ch;//���������ַ�
	if (bioskey(1) == 0) 
	{
		return;
	}
	else if (i < MAX_LENGTH)
	{
		regs.h.ah = 0x00;
		int86(0x16, &regs, &regs);//��ȡ16λ�Ĵ����ĺ��λASCII��
		//ch = regs.h.al;
		if (regs.h.al == 0x08)//�˸�
		{
			password[i] = '_';
			if (i != -1)
				i -= 1;
			
			

		}
		else if (regs.h.al == 0x0D)//�س�
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
		puthz(308, 200, "�û�", 24, 10, WHITE);
		rectangle(280, 220, 360, 260);
	}
}

void judge(char password[MAX_LENGTH])
{
	if (strcmp(password, PASSWORD) == 0)
		is_right = 1;
	else
	{
		is_right -= 1;//����ͳ��ʧ�ܵĴ���
		strcpy(password, "__________\0");
		i = -1;
	}

}