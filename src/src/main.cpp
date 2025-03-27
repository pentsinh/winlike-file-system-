// #define TEST

#ifndef TEST
// #include <stdio.h>
// #include <graphics.h>
// #include <dos.h>
// #include <conio.h>
// #include <string.h>
// #include <stdlib.h>
// #include <time.h>
// #include <dirent.h>
// #include <direct.h>
#include "include.h"

// int mode_shift = 0x11;

extern char path[1024];					   // ��ǰ·��
extern char history[HISTORY_LENGTH][1024]; // ������ʷ
extern int now_history;					   // ��ǰ��·����history�е�λ�ã�����������
extern void *buffer;					   // ����
extern struct dir_tree tree;			   // Ŀ¼�������ڼ����������Լ�ͨ���������ٶ�λ
struct My_filenode *root;

void spinOnce(struct file_info *info) // ����״̬��⺯��
{
	newmouse(&MouseX, &MouseY, &press);
	getcwd(path, sizeof(path));
	read_dir(path, info);
	if (now_history == 0 && strcmp(path, history[now_history]) != 0)
		new_history();
}

int main()
{
	struct file_info info[10]; // ����ļ���Ϣ
	int gd = DETECT, gm;	   // ͼ��������ͼ��ģʽ
	char mode = 0;			   // ���Ӵ���ʾģʽ��0Ϊһ��ģʽ��1Ϊ����ģʽ
	char mode_shift = _0to0;   // ģʽ�л�
	char srch_tar[16];		   // ����Ŀ��
	int result;				   // ������ź�������ֵ����ֹ��ε���
	root = (struct My_filenode *)malloc(sizeof(struct My_filenode));
	tree_make(root, 0); // Ŀ¼����ʼ����
	printf("Ready to start!\n");

	buffer = NULL;
	initgraph(&gd, &gm, "C:\\BORLANDC\\BGI"); // ��ʼ��ͼ��ģʽ
	mouseinit();

	if (!login()) // ��½ʧ��
		return 0;
	else // ��½�ɹ�
	{
		MouseS = 0;
		cleardevice();
		clrmous(MouseX, MouseY);
		load_init(info);				// �����ʼ��
		spinOnce(info);					// ˢ��info
		load_all(info, srch_tar, mode); // ��ʾ

		while (1)
		{
			spinOnce(info);

			if (mouse_press(10, 10, 30, 30) == 1) //|| mouse_press(10, 10, 30, 30) == 4)//������<-����Ŀ¼����
			{
				undo_dir();
				spinOnce(info);
				clrmous(MouseX, MouseY);
				cleardevice();
				load_all(info, srch_tar, mode);
			}
			else if (mouse_press(30, 10, 50, 30) == 1) // || mouse_press(30, 10, 50, 30) == 4)//������->������Ŀ¼����
			{
				anti_undo_dir();
				spinOnce(info);
				clrmous(MouseX, MouseY);
				cleardevice();
				load_all(info, srch_tar, mode);
			}
			else if (mouse_press(50, 10, 70, 30) == 1) //|| mouse_press(50, 10, 70, 30) == 4)//������������һ��Ŀ¼
			{
				back();
				spinOnce(info);
				clrmous(MouseX, MouseY);
				cleardevice();
				load_all(info, srch_tar, mode);
			}
			else if (mouse_press(70, 10, 90, 30) == 1) //|| mouse_press(70, 10, 90, 30) == 4)//������ˢ��
			{
				spinOnce(info);
				clrmous(MouseX, MouseY);
				cleardevice();
				if (mode == 0)
					strcpy(srch_tar, "");
				load_all(info, srch_tar, mode);
			}

			else if (mouse_press(120, 70, 640, 480) == 1) // || mouse_press(120, 70, 640, 480) == 4)//�������ļ����У�����
			{
				result = change_dir(info, MouseX, MouseY);
				if (result == 2) //|| change_dir(info, MouseX, MouseY) == 0)//�������Ч���
				{
					clrmous(MouseX, MouseY);
					cleardevice();
					spinOnce(info);
					delay(200);
					load_all(info, srch_tar, mode);
				}
				else if (result == 1) // ѡ��
				{
					clrmous(MouseX, MouseY);
					cleardevice();
					spinOnce(info);
					delay(200);
					load_all(info, srch_tar, mode);
				}
				else if (result == 0)
				{
					clrmous(MouseX, MouseY);
					cleardevice();
					delay(200);
					load_all(info, srch_tar, mode);
				}
			}

			// ����Ŀ¼��
			else if (mouse_press(10, 70, 100, 470) == 1)
			{

				if (chdir(get_file_path_left(root, MouseX, MouseY)) != NULL)
				{
					getcwd(path, sizeof(path));
					spinOnce(info);
					clrmous(MouseX, MouseY);
					cleardevice();
					load_all(info, srch_tar, mode);
				}
				if (unfold(root, MouseX, MouseY) != 0)
				{
					cleardevice();
					load_all(info, srch_tar, mode);
				}
			}

			// ����
			// ģʽ�л��б�
			// if (mouse_press(540, 10, 630, 30) == 1)
			if (MouseX > 540 && MouseX < 630 && MouseY > 10 && MouseY < 30 && press == 1) // �ĸ�Ч�������ĸ�
			{
				if (mode_shift == _0to0 || mode_shift == _1to0)
				{
					mode_shift = _0to1;
					mode = 1;
				}
				else // if (mode_shift == _0to1 || mode_shift == _1to1)
					mode_shift = _1to1;
			}
			if (mouse_press_out(540, 10, 630, 30) == 1)
			{
				if (mode_shift == _0to1 || mode_shift == _1to1)
				{
					mode_shift = _1to0;
					mode = 1;
				}
				else if (mode_shift == _0to0 || mode_shift == _1to0)
					mode_shift = _0to0;
			}

			if (mode_shift == _0to1) // ��һ��ģʽ������ģʽ
			{
				mode = 1;
				clrmous(MouseX, MouseY);
				load_top(srch_tar, mode);
				mode_shift = _1to1;
			}
			else if (mode_shift == _1to0) // ������ģʽ��һ��ģʽ����������Ŀ��Ϊ��
			{
				mode = 0;
				load_top(srch_tar, mode);
				mode_shift = _0to0;
			}

			if (mode_shift == _1to1 || mode_shift == _0to1) // �����������ģʽ
			{
				result = srch_input(srch_tar, info);
				if (result == 1)
				{
					load_top(srch_tar, mode);
				}
				else if (result == 2)
				{
					// strcpy(srch_tar, "");
					mode_shift = _0to1;
					srch_output(info, srch_tar);
				}
			}
		}
	}

	closegraph();
	return 0;
}

#endif