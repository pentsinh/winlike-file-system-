#define TEST
#ifdef TEST
#include <graphics.h>
#include <dos.h>
#include <conio.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <bios.h>
#include "include.h"
// extern time_t press_time[10];

// �������˫�����

// int main()
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
// }

// int main()
// {
// 	char chart_left[10][10] = {0}; //
// 	char chart_right[10][10] = {0};
// 	int i;
// 	int flag = 0;
// 	int gd = DETECT, gm;					  // ͼ��������ͼ��ģʽ
// 	initgraph(&gd, &gm, "C:\\BORLANDC\\BGI"); // ��ʼ��ͼ��ģʽ
// 	mouseinit();
// 	setbkcolor(BLUE);
// 	setcolor(RED); // �����ı���ɫΪ��ɫ
// 	settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
// 	puthz(308, 200, "�û�", 24, 10, WHITE);
// 	rectangle(280, 220, 360, 260);
// 	while (1)
// 	{
// 		newmouse(&MouseX, &MouseY, &press);
// 		if (mouse_press(280, 220, 360, 260) == 4 && flag == 0)
// 		{
// 			setbkcolor(YELLOW);
// 			flag = 1;
// 		}
// 		else if (mouse_press(280, 220, 360, 260) == 4 && flag == 1)
// 		{
// 			setbkcolor(BLUE);
// 			flag = 0;
// 		}
// 	}
// 	return 1;
// }

// int main()
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
// }

// ���Ե��
// extern last_press_time;
// extern last_click_time;
// void main()
//{
//	int last_press = 0;
//	char box[10] = { 0 };
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
//	node:
//	puthz(308, 200, "�û�", 24, 10, WHITE);
//
//	rectangle(280, 220, 360, 260);
//	rectangle(380, 320, 460, 360);
//
//	while (1)
//	{
//		newmouse(&MouseX, &MouseY, &press);
//		last_press = mouse_press(280, 220, 360, 260);
//		if (last_press != 3 && last_press != 2 && last_press != 0)
//		{
//			outtextxy(30, 30, ltoa((long)last_click_time, box, 10));
//			outtextxy(10, 10, itoa(last_press, box, 10));
//		}
//		else if(last_press==3)
//		{
//			cleardevice();
//			goto node;
//		}
//		if (mouse_press(380, 320, 460, 360) == 1)
//		{
//			cleardevice();
//			goto node;
//		}
//		//if (mouse_press(280, 220, 360, 260) == 1)
//		//	flag = 1;
//		//if (mouse_press(280, 220, 360, 260) == 2 && flag == 1)
//		//	break;
//	}
// }

// ����ʱ��
// int main() {
//     // ��ȡ��ǰʱ��
//     time_t rawtime;
//     struct tm* timeinfo;
//     char buffer[80];
//     time(&rawtime);
//     timeinfo = localtime(&rawtime);  // ��ʱ��ת��Ϊ����ʱ��
//
//     // ��ӡ��ʽ�����ʱ��
//     printf("��ǰʱ��: %s", asctime(timeinfo));  // ʹ�� asctime ������ʱ��ת��Ϊ�ַ���
//
//     // ����ʹ�� strftime �����Զ��������ʽ
//
//     strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo);
//     printf("��ǰʱ��: %s\n", buffer);
//
//     return 0;
// }

// void main()
//{
//	char str[13];
//	memset(str, 0, sizeof(char[13]));
//	printf("%s,%d", str, strlen(str));
//	printf("\n");
//	if (str == 0)
//		printf("str==0");
//	else
//		printf("%d", (int)str);
//	printf("\n");
//	if (strcmp(str, "") == 0)
//		printf("strcmp(str,\"\")==0");
//	printf("\n");
// }

// #include <graphics.h>
// #include <dos.h>
// #include <conio.h>
// #include <string.h>
// #include <stdlib.h>
// #include <time.h>
// #include <dirent.h>
// #include <direct.h>
// #include "include.h"
//
// extern char path[1024];//��ǰ·��
// extern char history[HISTORY_LENGTH][1024];//������ʷ
// extern int now_history;//��ǰ��·����history�е�λ�ã�����������
// extern void* buffer;//����
// extern struct dir_tree tree;//Ŀ¼�������ڼ����������Լ�ͨ���������ٶ�λ
//
////void spinOnce(DIR* dir, struct dirent* entry, struct file_info* info)//����״̬��⺯��
////{
////	newmouse(&MouseX, &MouseY, &press);
////	getcwd(path, sizeof(path));
////	dir = opendir(path);
////	read_dir(dir, entry, info);
////	closedir(dir);
////	if (now_history == 0 && strcmp(path, history[now_history]) != 0)
////		new_history();
////}

// int main()
//{
//
//	struct file_info info[10];//����ļ���Ϣ
//	int gd = DETECT, gm;  // ͼ��������ͼ��ģʽ
//	int result;//������ź�������ֵ����ֹ��ε���
//	initgraph(&gd, &gm, "C:\\BORLANDC\\BGI");// ��ʼ��ͼ��ģʽ
//	mouseinit();
//
//	//if (!login())	//��½ʧ��
//	//	return;
//	//else	//��½�ɹ�
//	//{
//		MouseS = 0;
//		cleardevice();
//		clrmous(MouseX, MouseY);
//		//buffer = NULL;
//		tree_make(&tree);//Ŀ¼����ʼ����
//		load_init(info);//�����ʼ��
//		//spinOnce(dir, entry, info);//ˢ��info
//		load_all(info);//��ʾ
//		setcolor(YELLOW);
//		outtextxy(100, 0, tree.name);
//		outtextxy(200, 0, tree.path);
//		if (tree.branch[0])
//		{
//			outtextxy(100, 100, tree.branch[0]->name);
//			outtextxy(200, 100, tree.branch[0]->path);
//		}
//		if (tree.branch[1])
//		{
//			outtextxy(100, 200, tree.branch[1]->name);
//			outtextxy(200, 200, tree.branch[1]->path);
//		}
//		if (tree.branch[2])
//		{
//			outtextxy(100, 300, tree.branch[2]->name);
//			outtextxy(200, 300, tree.branch[2]->path);
//		}
//	//	while (1)
//	//	{
//	//		spinOnce(dir, entry, info);
//
//	//		if (mouse_press(10, 10, 30, 30) == 1)//|| mouse_press(10, 10, 30, 30) == 4)//������<-����Ŀ¼����
//	//		{
//	//			undo_dir();
//	//			spinOnce(dir, entry, info);
//	//			clrmous(MouseX, MouseY);
//	//			cleardevice();
//	//			load_all(info);
//	//		}
//	//		else if (mouse_press(30, 10, 50, 30) == 1)// || mouse_press(30, 10, 50, 30) == 4)//������->������Ŀ¼����
//	//		{
//	//			anti_undo_dir();
//	//			spinOnce(dir, entry, info);
//	//			clrmous(MouseX, MouseY);
//	//			cleardevice();
//	//			load_all(info);
//	//		}
//	//		else if (mouse_press(50, 10, 70, 30) == 1)//|| mouse_press(50, 10, 70, 30) == 4)//������������һ��Ŀ¼
//	//		{
//	//			back();
//	//			spinOnce(dir, entry, info);
//	//			clrmous(MouseX, MouseY);
//	//			cleardevice();
//	//			load_all(info);
//	//		}
//	//		else if (mouse_press(70, 10, 90, 30) == 1)//|| mouse_press(70, 10, 90, 30) == 4)//������ˢ��
//	//		{
//	//			spinOnce(dir, entry, info);
//	//			clrmous(MouseX, MouseY);
//	//			cleardevice();
//	//			load_all(info);
//	//		}
//
//	//		else if (mouse_press(120, 70, 640, 480) == 1)// || mouse_press(120, 70, 640, 480) == 4)//�������ļ����У�����
//	//		{
//	//			result = change_dir(info, MouseX, MouseY);
//	//			if (result == 2)//|| change_dir(info, MouseX, MouseY) == 0)//�������Ч���
//	//			{
//	//				clrmous(MouseX, MouseY);
//	//				cleardevice();
//	//				spinOnce(dir, entry, info);
//	//				delay(200);
//	//				load_all(info);
//	//			}
//	//			else if (result == 1)//ѡ��
//	//			{
//	//				clrmous(MouseX, MouseY);
//	//				cleardevice();
//	//				spinOnce(dir, entry, info);
//	//				delay(200);
//	//				load_all(info);
//	//			}
//	//			else if (result == 0)
//	//			{
//	//				clrmous(MouseX, MouseY);
//	//				cleardevice();
//	//				delay(200);
//	//				load_all(info);
//	//			}
//	//		}
//
//	//	}
//	//}
//				 while(1);
//	closegraph();
//	return 0;
// }

// Ŀ¼������+��������
struct My_filenode *root;
int main()
{
	int gd = DETECT, gm; // ͼ��������ͼ��ģʽ
	int result;			 // ������ź�������ֵ����ֹ��ε���
	int mode = 0;		 // 1Ϊ����
	root = (struct My_filenode *)malloc(sizeof(struct My_filenode));
	tree_make(root, 0);
	printf("Finished!\n");
	initgraph(&gd, &gm, "C:\\BORLANDC\\BGI"); // ��ʼ��ͼ��ģʽ
	mouseinit();
	setbkcolor(BLACK);
	setcolor(WHITE);
	settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
	rectangle(270, 230, 370, 250);
	puthz(270, 230, "����", 16, 2, WHITE);
	while (1)
	{
		newmouse(&MouseX, &MouseY, &press);

		// ����
		if (mouse_press(270, 230, 370, 250) == 1)
		{
			mode = 1;
		}
		else if (mouse_press_out(270, 230, 370, 250) == 1)
		{
			mode = 0;
		}
		if (mode == 1)
		{
			// srch_input(srch_tar);
		}
	}

	return 0;
}

// ���԰�λ����
//
// int main()
// {
// 	unsigned char num = 0b10101100; // ʾ����ʼֵ
// 	printf("Original value: %02X\n", num);
// 	printBinary(num);
// 	set_bit(&num, 3, 1); // ����3λ����Ϊ1
// 	printf("After setting bit 3 to 1: %02X\n", num);
// 	printBinary(num);
// 	set_bit(&num, 3, 0); // ����5λ����Ϊ0
// 	printf("After setting bit 3 to 0: %02X\n", num);
// 	printBinary(num);
// 	return 0;
// }

#endif