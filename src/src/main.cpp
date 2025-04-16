//#define TEST

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

extern void *buffer; // ����

struct menu
{
	char *option;
	struct menu *next;
	struct menu *son_menu_head;
};

void spinOnce(char path[1024], struct file_info *info, int mode, char history[HISTORY_LENGTH][1024], int now_history, int sort_mode, int UpOrDown) // ����״̬��⺯��
{
	newmouse(&MouseX, &MouseY, &press);
	if (mode == 0)
	{
		getcwd(path, sizeof(path) * 1024);
		// read_dir(path, info);
	}
	// printf("%s [%d]%s\n", path, now_history, history[now_history]);
	sort(info, sort_mode, UpOrDown);

	if (now_history == 0 && strcmp(path, history[now_history]) != 0)
	{
		new_history(history, path);
	}

	// for (int i = 0; i < HISTORY_LENGTH; i++)
	// 	printf("[%d]%s    ", i, history[i]);
	// printf("\n");
}

int main()
{
	int gd = DETECT, gm; // ͼ��������ͼ��ģʽ

	struct My_filenode *root;				  // Ŀ¼���ĸ�
	char path[1024];						  // ��ǰ·��
	char history[HISTORY_LENGTH][1024] = {0}; // ������ʷ
	int now_history = 0;					  // ��ǰ��·����history�е�λ�ã�����������
	struct file_info info[10];				  // ����ļ���Ϣ

	int i; // ѭ������

	int sort_mode = 0; // ���򷽷�
	int UpOrDown = 1;  // ����/����

	char mode = 0;			 // ���Ӵ���ʾģʽ��0Ϊһ��ģʽ��1Ϊ����ģʽ
	char mode_shift = _0to0; // ģʽ�л�
	char srch_tar[16];		 // ����Ŀ��

	int choose_mode = 0; // ���ѡ��ģʽ

	int result; // ������ź�������ֵ����ֹ��ε���

	root = (struct My_filenode *)malloc(sizeof(struct My_filenode));

	initgraph(&gd, &gm, "C:\\BORLANDC\\BGI"); // ��ʼ��ͼ��ģʽ
	power_on();
	welcome();

	tree_make(root, 0); // Ŀ¼����ʼ����
	// printf("Ready to start!\n");

	buffer = NULL;

	mouseinit();

	if (!login()) // ��½ʧ��
		return 0;
	else // ��½�ɹ�
	{
		MouseS = 0;
		cleardevice();
		clrmous(MouseX, MouseY);
		load_init(path, info, history); // �����ʼ��
		read_dir(path, info);

		spinOnce(path, info, mode, history, now_history, sort_mode, UpOrDown); // ˢ��info
		load_all(path, info, root, srch_tar, mode);							   // ��ʾ

		// ����˵���ʼ��
		char sort_menu[6][16] = {"����", "�޸�ʱ��", "����", "��С", "����", "�ݼ�"};
		char **sort_menu_p = (char **)malloc(6 * sizeof(char *));
		for (i = 0; i < 6; i++)
		{
			sort_menu_p[i] = (char *)malloc(16 * sizeof(char));
			strcpy(sort_menu_p[i], sort_menu[i]);
		}

		// �Ҽ��˵���ʼ��
		char RB_menu[4][16] = {"����ʽ", "����", "�½�", "����"};
		char **RB_menu_p = (char **)malloc(4 * sizeof(char *));
		for (i = 0; i < 4; i++)
		{
			RB_menu_p[i] = (char *)malloc(16 * sizeof(char));
			strcpy(RB_menu_p[i], RB_menu[i]);
		}

		while (1)
		{
			// spinOnce(path, info, mode, history, now_history, sort_mode, UpOrDown);
			newmouse(&MouseX, &MouseY, &press);

			if (mouse_press(10, 10, 30, 30) == 1) //|| mouse_press(10, 10, 30, 30) == 4)//������<-����Ŀ¼����
			{
				result = undo_dir(history, &now_history);
				spinOnce(path, info, mode, history, now_history, sort_mode, UpOrDown);
				if (result == 1)
					read_dir(path, info);
				clrmous(MouseX, MouseY);
				cleardevice();
				load_all(path, info, root, srch_tar, mode);
			}
			else if (mouse_press(30, 10, 50, 30) == 1) // || mouse_press(30, 10, 50, 30) == 4)//������->������Ŀ¼����
			{
				result = anti_undo_dir(history, &now_history);
				spinOnce(path, info, mode, history, now_history, sort_mode, UpOrDown);
				if (result == 1)
					read_dir(path, info);
				clrmous(MouseX, MouseY);
				cleardevice();
				load_all(path, info, root, srch_tar, mode);
			}
			else if (mouse_press(50, 10, 70, 30) == 1) //|| mouse_press(50, 10, 70, 30) == 4)//������������һ��Ŀ¼
			{
				result = back(path, history, &now_history);
				spinOnce(path, info, mode, history, now_history, sort_mode, UpOrDown);
				if (result == 1)
					read_dir(path, info);
				clrmous(MouseX, MouseY);
				cleardevice();
				load_all(path, info, root, srch_tar, mode);
			}
			else if (mouse_press(70, 10, 90, 30) == 1) //|| mouse_press(70, 10, 90, 30) == 4)//������ˢ��
			{
				spinOnce(path, info, mode, history, now_history, sort_mode, UpOrDown);
				read_dir(path, info);
				clrmous(MouseX, MouseY);
				cleardevice();
				if (mode == 0)
					strcpy(srch_tar, "");
				load_all(path, info, root, srch_tar, mode);
			}
			else if (mouse_press(10, 40, 180, 65) == 1) //|| mouse_press(10, 40, 500, 65) == 4)//�������Ϸ���������
			{

				func();
				spinOnce(path, info, mode, history, now_history, sort_mode, UpOrDown);
				clrmous(MouseX, MouseY);
				cleardevice();
				load_all(path, info, root, srch_tar, mode);
			}
			else if (mouse_press(180, 42, 260, 60) == 1) // ������������˵�
			{
				result = drop_down_menu(180, 60, 100, 40, 6, 16, sort_menu_p, WHITE, BLACK, 0, 0);
				if (result >= 0 && result <= 3)
					sort_mode = result;
				else if (result == 4)
					UpOrDown = 1;
				else if (result == 5)
					UpOrDown = -1;
				if (result != -1)
				{
					spinOnce(path, info, mode, history, now_history, sort_mode, UpOrDown);
					clrmous(MouseX, MouseY);
					cleardevice();
					load_all(path, info, root, srch_tar, mode);
					delay(200);
				}
			}

			else if (mouse_press(120, 70, 640, 480) == 1) // || mouse_press(120, 70, 640, 480) == 4)//�������ļ����У�����
			{
				result = change_dir(info, MouseX, MouseY);
				if (result == 2) //|| change_dir(info, MouseX, MouseY) == 0)//�������Ч���
				{
					clrmous(MouseX, MouseY);
					cleardevice();
					spinOnce(path, info, mode, history, now_history, sort_mode, UpOrDown);
					read_dir(path, info);
					load_all(path, info, root, srch_tar, mode);
				}
				else if (result == 1) // ѡ��
				{
					spinOnce(path, info, mode, history, now_history, sort_mode, UpOrDown);
					cleardevice();
					load_all(path, info, root, srch_tar, mode);
				}
				else if (result == 0) // ����հ�
				{
					cleardevice();
					for (int j = 0; j < INFO_LENGTH; j++)
						set_bit(&(info + j)->flag, 7, 0); // ������������д������д��ѡ�Ż�
					load_all(path, info, root, srch_tar, mode);
				}
			}

			// ����Ŀ¼��
			else if (mouse_press(10, 70, 100, 470) == 1)
			{
				if (chdir(get_file_path_left(root, MouseX, MouseY)) != -1)
				{
					mode_shift = _1to0;
					mode = 0;

					// getcwd(path, sizeof(path));
					spinOnce(path, info, mode, history, now_history, sort_mode, UpOrDown);
					read_dir(path, info);
					clrmous(MouseX, MouseY);
					// cleardevice();
					// load_all(path, info, root, srch_tar, mode);
					clearRectangle(10, 10, 630, 30, BLACK);
					load_top(path, srch_tar, mode);
					clearRectangle(120, 70, 640, 480, BLACK);
					load_main(info, mode);
				}

				if (unfold(root, MouseX, MouseY) != 0)
				{
					clearRectangle(10, 70, 100, 470, BLACK);
					load_left(root);
				}
			}

			// ����
			else if (mouse_press(620, 0, 640, 20) == 2)
				end();

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
			if (mouse_press_out(540, 10, 620, 30) == 1)
			{
				if (mode_shift == _0to1 || mode_shift == _1to1)
				{
					mode_shift = _1to0;
					mode = 1;
				}
				else if (mode_shift == _0to0 || mode_shift == _1to0)
					mode_shift = _0to0;
			}

			// �Ҽ�����
			if (mouse_press(120, 70, 640, 480) == 3)
			{
				int tmp_x = MouseX, tmp_y = MouseY; // ��¼�һ�ʱ�����λ��

				delay(200);
				result = 0;

				result = drop_down_menu(MouseX, MouseY, 75, 25, 4, 12, RB_menu_p, WHITE, BLACK, 0, 1);

				if (result == 0) // ����ʽ
				{
					int result_0 = -1;
					result_0 = drop_down_menu(tmp_x + 75, tmp_y, 75, 25, 6, 12, sort_menu_p, WHITE, BLACK, 0, 0);
					if (result_0 >= 0 && result_0 <= 3)
						sort_mode = result_0;
					else if (result_0 == 4)
						UpOrDown = 1;
					else if (result_0 == 5)
						UpOrDown = -1;
					if (result_0 != -1)
					{
						spinOnce(path, info, mode, history, now_history, sort_mode, UpOrDown);
						clrmous(MouseX, MouseY);
						cleardevice();
						load_all(path, info, root, srch_tar, mode);
						delay(200);
					}
					else
					{
						clrmous(MouseX, MouseY);
						cleardevice();
						load_all(path, info, root, srch_tar, mode);
					}
				}
				else if (result == 1) // ����
				{
				}
				else if (result == 2) // �½�
				{
				}
				else if (result == 3) // ����
				{
					if (get_file_num(tmp_x, tmp_y, info) != -1)
						set_bit(&(info + get_file_num(tmp_x, tmp_y, info) - 1)->flag, 7, 1);

					if (is_selected(info) != 0)
						property(NULL, info + is_selected(info) - 1);
					else
						property(path, NULL);
					cleardevice();
					load_all(path, info, root, srch_tar, mode);
				}
			}

			// ģʽ�л�����
			if (mode_shift == _0to1) // ��һ��ģʽ������ģʽ
			{
				mode = 1;
				clrmous(MouseX, MouseY);
				load_top(path, srch_tar, mode);
				mode_shift = _1to1;
			}
			else if (mode_shift == _1to0) // ������ģʽ��һ��ģʽ����������Ŀ��Ϊ��
			{
				mode = 0;
				load_top(path, srch_tar, mode);
				mode_shift = _0to0;
			}

			if (mode_shift == _1to1 || mode_shift == _0to1) // �����������ģʽ
			{
				result = srch_input(srch_tar, info);
				if (result == 1)
				{
					load_top(path, srch_tar, mode);
				}
				else if (result == 2)
				{
					// strcpy(srch_tar, "");
					mode_shift = _0to1;
					srch_output(path, info, root, srch_tar);
				}
			}
		}
	}

	closegraph();
	return 0;
}

#endif