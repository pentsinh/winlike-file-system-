#define TEST

#ifndef TEST
#include <stdio.h>
#include <graphics.h>
#include <dos.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <dirent.h>
#include <direct.h>
#include "include.h"

// int mode = 0x11;

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
	// dir = opendir(path);
	read_dir(path, info);
	// closedir(dir);
	if (now_history == 0 && strcmp(path, history[now_history]) != 0)
		new_history();
}

int main()
{
	struct file_info info[10]; // ����ļ���Ϣ
	int gd = DETECT, gm;	   // ͼ��������ͼ��ģʽ
	char out_put_mode = 0;	   // ���Ӵ���ʾģʽ��0Ϊһ��ģʽ��1Ϊ����ģʽ
	char srch_tar[16];		   // ����Ŀ��
	int result;				   // ������ź�������ֵ����ֹ��ε���
	// tree_make(&tree, 0);	   // Ŀ¼����ʼ����
	root = (struct My_filenode *)malloc(sizeof(struct My_filenode));
	tree_make(root, 0);
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
		// buffer = NULL;
		// tree_make(&tree, 0); // Ŀ¼����ʼ����
		load_init(info); // �����ʼ��
		spinOnce(info);	 // ˢ��info
		load_all(info);	 // ��ʾ

		while (1)
		{
			spinOnce(info);

			if (mouse_press(10, 10, 30, 30) == 1) //|| mouse_press(10, 10, 30, 30) == 4)//������<-����Ŀ¼����
			{
				undo_dir();
				spinOnce(info);
				clrmous(MouseX, MouseY);
				cleardevice();
				load_all(info);
			}
			else if (mouse_press(30, 10, 50, 30) == 1) // || mouse_press(30, 10, 50, 30) == 4)//������->������Ŀ¼����
			{
				anti_undo_dir();
				spinOnce(info);
				clrmous(MouseX, MouseY);
				cleardevice();
				load_all(info);
			}
			else if (mouse_press(50, 10, 70, 30) == 1) //|| mouse_press(50, 10, 70, 30) == 4)//������������һ��Ŀ¼
			{
				back();
				spinOnce(info);
				clrmous(MouseX, MouseY);
				cleardevice();
				load_all(info);
			}
			else if (mouse_press(70, 10, 90, 30) == 1) //|| mouse_press(70, 10, 90, 30) == 4)//������ˢ��
			{
				spinOnce(info);
				clrmous(MouseX, MouseY);
				cleardevice();
				load_all(info);
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
					load_all(info);
				}
				else if (result == 1) // ѡ��
				{
					clrmous(MouseX, MouseY);
					cleardevice();
					spinOnce(info);
					delay(200);
					load_all(info);
				}
				else if (result == 0)
				{
					clrmous(MouseX, MouseY);
					cleardevice();
					delay(200);
					load_all(info);
				}
			}
			// ����
			// else if (mouse_press(540, 10, 630, 30) == 1)
			// {
			// 	out_put_mode = 1;
			// 	// srch_input(srch_tar);
			// }
			// else if (mouse_press_out(540, 10, 630, 30) == 1)
			// {
			// 	out_put_mode = 0;
			// }

			// ����Ŀ¼��
			else if (mouse_press(10, 70, 100, 470) == 1)
			{

				if (chdir(get_file_path_left(root, MouseX, MouseY)) != NULL)
				{
					getcwd(path, sizeof(path));
					spinOnce(info);
					cleardevice();
					load_all(info);
				}
				if (unfold(root, MouseX, MouseY) != 0)
				{
					cleardevice();
					load_all(info);
				}
			}
		}
	}

	closegraph();
	return 0;
}

#endif