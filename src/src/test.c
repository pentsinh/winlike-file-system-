#include <graphics.h>
#include <dos.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "include.h"
extern time_t press_time[10];


//�������˫�����

//int main()
//{
//	char chart_left[10][10] = { 0 };//
//	char chart_right[10][10] = { 0 };
//	int i;
//	int flag = 0;
//	int gd = DETECT, gm;  // ͼ��������ͼ��ģʽ    
//	initgraph(&gd, &gm, "C:\\BORLANDC\\BGI");// ��ʼ��ͼ��ģʽ
//	mouseinit();
//
//	setbkcolor(BLUE);
//	setcolor(YELLOW); // �����ı���ɫΪ��ɫ
//	settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
//
//	puthz(308, 200, "�û�", 24, 10, WHITE);
//	
//	rectangle(280, 220, 360, 260);
//	while (1)
//	{
//		newmouse(&MouseX, &MouseY, &press);
//		itoa(mouse_press(280, 220, 360, 260), chart_right[0], 10);//0��λ
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
//			puthz(308, 200, "�û�", 24, 10, WHITE);
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
//	int gd = DETECT, gm;  // ͼ��������ͼ��ģʽ    
//	initgraph(&gd, &gm, "C:\\BORLANDC\\BGI");// ��ʼ��ͼ��ģʽ
//	mouseinit();
//
//	setbkcolor(BLUE);
//	setcolor(RED); // �����ı���ɫΪ��ɫ
//	settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
//
//	puthz(308, 200, "�û�", 24, 10, WHITE);
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
//	int gd = DETECT, gm;  // ͼ��������ͼ��ģʽ    
//	initgraph(&gd, &gm, "C:\\BORLANDC\\BGI");// ��ʼ��ͼ��ģʽ
//	mouseinit();
//
//	setbkcolor(BLUE);
//	setcolor(RED); // �����ı���ɫΪ��ɫ
//	settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
//
//	puthz(308, 200, "�û�", 24, 10, WHITE);
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
	int gd = DETECT, gm;  // ͼ��������ͼ��ģʽ    
	initgraph(&gd, &gm, "C:\\BORLANDC\\BGI");// ��ʼ��ͼ��ģʽ
	mouseinit();

	setbkcolor(BLUE);
	setcolor(RED); // �����ı���ɫΪ��ɫ
	settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);

	node:
	puthz(308, 200, "�û�", 24, 10, WHITE);

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


//����ʱ��
//int main() {
//    // ��ȡ��ǰʱ��
//    time_t rawtime;
//    struct tm* timeinfo;
//    char buffer[80];
//    time(&rawtime);
//    timeinfo = localtime(&rawtime);  // ��ʱ��ת��Ϊ����ʱ��
//
//    // ��ӡ��ʽ�����ʱ��
//    printf("��ǰʱ��: %s", asctime(timeinfo));  // ʹ�� asctime ������ʱ��ת��Ϊ�ַ���
//
//    // ����ʹ�� strftime �����Զ��������ʽ
//    
//    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo);
//    printf("��ǰʱ��: %s\n", buffer);
//
//    return 0;
//}