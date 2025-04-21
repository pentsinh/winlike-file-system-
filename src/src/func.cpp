// ʵ������һ���½�������ճ���ȹ��ܺ���
#include <graphics.h>
#include <dos.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <dirent.h>
#include <mouse.h>

// #include <direct.h>
// #include <sys/stat.h> // �ļ�״̬
#include "include.h"

// char source_path[1024]; // ���ڸ���ճ���ı���

void build(struct file_info *info)
{
	char *file_type_strings[] =
		{

			"FOLD",
			"TXT",
			"C",
			"CPP",
			"H",
			"OBJ",
			"EXE",
			"JPG",
			"PNG",
			"DOC",
			"XLS",
			"PPT",
			"PDF",

		};
	char *now_path = NULL;
	char buffer[1024] = {0}, name[13]; // buffer���ڴ����µ�·����name���½��ļ���
	// ������ѡѡ���
	int type_index; // ��¼��������
	press = 0;
	delay(200);
	type_index = drop_down_menu(12, 70, 90, 20, 13, 1, file_type_strings, WHITE, DARKGRAY, 1, 0);

	if (type_index == -1 || type_index >= 12)
	{
		return;
	}

	// ��ȡ��ǰ����Ŀ¼
	char *result = getcwd(buffer, sizeof(buffer));
	if (result = NULL)
	{
		perror("fail to get current path");
		return;
	}
	// �����ļ���
	if (type_index != 0)
	{
		// �ļ����ͣ������չ��
		strcpy(name, "newfile");
		if (strlen(file_type_strings[type_index]) > 0)
		{
			strcat(name, ".");
			strcat(name, file_type_strings[type_index]);
		}
	}
	else if (type_index != -1)
	{
		// Ŀ¼����
		strcpy(name, "newdir");
		if (strlen(file_type_strings[type_index]) > 0)
		{
			strcat(name, file_type_strings[type_index]);
		}
	}

	// ��������·��
	now_path = get_file_path(buffer, name);
	if (now_path == NULL)
	{
		fprintf(stderr, "fail to build full path\n");
		return;
	}

	// ����½������ļ���
	if (type_index == 0)
	{
		if (mkdir(now_path) != 0)
		{
			perror("fail to new dir");
			free(now_path);
			return;
		}
		// printf("success to new dir: %s\n", now_path);
	}
	// ����½������ļ�
	else if (type_index != -1)
	{
		FILE *file = fopen(now_path, "w");
		if (file == NULL)
		{
			printf("fail to new file: %s\n", now_path);
			perror("fail to new file");
			free(now_path);
			return;
		}
		fclose(file);
		// printf("success to new file: %s\n", now_path);
	}
	free(now_path);
}

void rename(struct file_info *info)
{
	settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
	char new_name[13] = {0};
	int wc_select;
	wc_select = is_selected(info) - 1; // ��¼�ĸ��ļ���ѡ����
	if (wc_select == -1)
		return;
	clear_keyboard_buffer();
	char bd[10] = {0};
	int board = 0; // ��¼���̲���
	// char *new_name = (char *)malloc(sizeof(char) * 13); // �洢���ļ���

	int result = 0;

	setcolor(RED);
	outtextxy(120, 95 + wc_select * 20, (info + wc_select)->name); // ѡ�е��ļ������ȱ�Ϊ��ɫ����

	// ��ѭ��
	while (1)
	{
		newmouse(&MouseX, &MouseY, &press);
		int i = mouse_press_out(120, 95 + wc_select * 20, 200, 115 + wc_select * 20); // �ж��Ƿ����˱������

		if (i == 1)
		{
			setcolor(WHITE);
			outtextxy(120, 95 + wc_select * 20, (info + wc_select)->name);
			return;
		}

		board = getbuffer_keybd(new_name, 10);

		// ���ѡ�е��������������ɾ���������ֲ��ָ��ǵȴ�����������
		if (board == 1)
		{
			bar(120, 95 + wc_select * 20, 200, 115 + wc_select * 20);
			outtextxy(120, 95 + wc_select * 20, new_name);
			while (1)
			{

				newmouse(&MouseX, &MouseY, &press);
				// ��ȡ�������� (�Ƿ�Ҫ�����ӳٵȴ�������ȫ��)
				result = getbuffer_keybd(new_name, 13);

				if (result == 1)
				{

					bar(120, 95 + wc_select * 20, 200, 115 + wc_select * 20);
					outtextxy(120, 95 + wc_select * 20, new_name);
				}

				// ɾ�����⵽�س���
				else if (result == 2)
				{
					// ɾ�������������ֺ��»س�
					if (strlen(new_name) > 0)
					{
						// ִ������������
						rename((info + wc_select)->name, new_name);
						strcpy((info + wc_select)->name, new_name);
						setcolor(WHITE);
						outtextxy(120, 95 + wc_select * 20, new_name);
						return;
					}
					// ɾ�������û������Ͱ��»س�������ʾԭ��������
					else
					{

						setcolor(WHITE);
						outtextxy(120, 95 + wc_select * 20, (info + wc_select)->name);
						return;
					}
				}
				// delay(5);
				//  ɾ����û�м�⵽���� �򱣳�ԭ����
				else if (result == 0)
				{
					delay(3);
					continue;
				}
			}
		}

		// ���ѡ�е����������û�����룬�򱣳�ԭ����
		else if (board == 0)
		{
			delay(3);
			continue;
		}
		// ���ѡ�е��������������س�����ʾ������
		else if (board == 2)
		{
			outtextxy(120, 95 + wc_select * 20, (info + wc_select)->name);
			return;
		}
	}
}

void del(struct file_info *info)
{
	// printf("removing");
	int wc_select = is_selected(info) - 1; // ��¼�ĸ��ļ���ѡ����
	char *now_path = NULL;
	char buffer[1024] = {0}; // buffer���ڴ����µ�·����name���½��ļ���
	press = 0;
	// ��ȡ��ǰ����Ŀ¼
	char *result = getcwd(buffer, sizeof(buffer));
	if (result == NULL)
	{
		perror("fail to get current path");
		return;
	}
	// ��������·��
	now_path = get_file_path(buffer, (info + wc_select)->name);
	if (now_path == NULL)
	{
		fprintf(stderr, "fail to build full path\n");
		return;
	}

	// ����ɾ���ļ�
	if (rm_dir(now_path) == 1)
	{
		printf("Ŀ¼ɾ���ɹ�\n");
	}
	else
	{
		printf("Ŀ¼ɾ��ʧ��\n");
	}
}

int copy(struct file_info *info, char *source_path)
{
	if (info == NULL)
	{
		fprintf(stderr, "Invalid parameters\n");
		return -1;
	}
	int wc_select = is_selected(info) - 1; // ��¼�ĸ��ļ���ѡ����
	char buffer[1024] = {0};			   // buffer���ڴ����µ�·����name���½��ļ���
	press = 0;
	// ��ȡ��ǰ����Ŀ¼
	char *result = getcwd(buffer, sizeof(buffer));
	if (result == NULL)
	{
		perror("fail to get current path");
		return -1;
	}
	// ��������·��
	strcpy(source_path, get_file_path(buffer, (info + wc_select)->name));
	if (*source_path == NULL)
	{
		fprintf(stderr, "fail to build full path\n");
		return -1;
	}
	else
	{
		fprintf(stderr, "copy have done");
		printf("%s", source_path);
		return 0;
	}
}

int paste(char *source_path, int *flag)
{
	printf("src path=%s", source_path);
	if (source_path == NULL)
	{
		fprintf(stderr, "Invalid parameter\n");
		return -1;
	}
	char dest_father_path[1024] = {0}; // Ŀ�������ļ��о���·��
	if (getcwd(dest_father_path, sizeof(dest_father_path)) == NULL)
	{
		perror("Failed to get current path");
		return -1;
	}

	if (c_p(source_path, dest_father_path) == -1)
	{
		fprintf(stderr, "Failed to copy file\n");
		return -1;
	}
	else
	{
		fprintf(stderr, "succeed to copy file\n");
		// ���֮ǰ�Ǽ��в�������ճ������ɾ��ԭ�ļ�
		if (*flag == 1)
		{
			if (rm_dir(source_path) != 1)
			{
				fprintf(stderr, "Failed to remove source after cut\n");
				return -1;
			}
			*flag = 0;
		}
		return 1;
	}
}

int cut(struct file_info *info, int *flag, char *source_path)
{
	if (copy(info, source_path) != 0) // ���������ͼ�꣬�ȵ��ø��ƺ���
	{
		printf("����δ�ɹ�");
		return -1;
	}
	int wc_select = is_selected(info) - 1; // ��¼�ĸ��ļ���ѡ����
	setcolor(DARKGRAY);
	outtextxy(120, 95 + wc_select * 20, (info + wc_select)->name); // ѡ�е��ļ������ȱ�Ϊ��ɫ

	*flag = 1;
	return 0;
}

int func(struct file_info *info, char *source_path, int *sort_mode, int *UpOrDown, char **sort_menu_p)
{
	// ����ѡ��״̬
	int F = 0; // ���ݴ�F��ֵ�ж����ĸ����ܱ�ѡ����
	// int click_type;
	int exit_flag = 0; // �˳�ѭ����־

	setcolor(YELLOW);
	static int result = -1; // ��ֹ��ε���
	static int if_cut = 0;	// �ж�֮ǰ�Ƿ���еļ��й�������ȷ��ճ�����Ƿ�Ҫ����ɾ������

	while (detect_mouse(0, 37, 365, 62) == 1) // ����ڹ�����
	{

		newmouse(&MouseX, &MouseY, &press);
		highlight_detector(NULL, NULL);

		// rectangle(5, 37, 60, 62);
		// rectangle(60, 37, 85, 62);
		// rectangle(85, 37, 110, 62);
		// rectangle(110, 37, 135, 62);
		// rectangle(135, 37, 165, 62);
		// rectangle(165, 37, 190, 62);
		// rectangle(190, 37, 275, 62);
		// rectangle(275, 37, 365, 62);

		if (mouse_press(5, 37, 60, 62) == 1)
		{
			F = 1; // ѡ���½�
		}
		else if (mouse_press(60, 37, 85, 62))
		{
			F = 2; // ѡ�м���
		}
		else if (mouse_press(85, 37, 110, 62))
		{
			F = 3; // ѡ�и���
		}
		else if (mouse_press(110, 37, 135, 62))
		{
			F = 4; // ѡ��ճ��
		}
		else if (mouse_press(135, 37, 165, 62))
		{
			F = 5; // ѡ��������
		}
		else if (mouse_press(165, 37, 190, 62))
		{
			F = 6; // ѡ��ɾ��
		}
		else if (mouse_press(190, 37, 275, 62))
		{
			F = 7; // ѡ������
		}
		else if (mouse_press(275, 37, 365, 62))
		{
			F = 8; // ѡ�в鿴
		}
		if (F != 0)
		{
			clrmous(MouseX, MouseY);
			break;
		}
	}

	// ���ѡ�С��½���
	switch (F)
	{
	case 1:
	{
		build(info);
		break;
	}
	case 2: // ����
	{
		// printf("cut have done");
		result = cut(info, &if_cut, source_path);
		break;
	}
	case 3: // ����
	{
		// printf("3");
		result = copy(info, source_path);
		printf("after copy src=%s", source_path);
		break;
	}
	case 4: // ճ��
	{
		// printf("4\n");
		if (result == 0)
		{
			// paste(source_path);
			//  if (copy(info, source_path) == 0)//ע���ε���

			// printf("before paste src=%s", source_path);
			if (paste(source_path, &if_cut) != -1)
			{
				printf("Copy and paste succeeded\n");
			}
			free(source_path);
		}
		result = -1;
		break;
	}
	case 5:
	{
		rename(info);
		break;
	}
	case 6: // ɾ��
	{
		del(info);
		break;
	}
	case 7:
	{
		result = drop_down_menu(195, 60, 80, 25, 6, 12, sort_menu_p, WHITE, DARKGRAY, 0, 0);
		if (result >= 0 && result <= 3)
			*sort_mode = result;
		else if (result == 4)
			*UpOrDown = 1;
		else if (result == 5)
			*UpOrDown = -1;
		// if (result != -1)
		// {
		// 	spinOnce(path, info, mode, history, now_history, sort_mode, UpOrDown);
		// 	clrmous(MouseX, MouseY);
		// 	cleardevice();
		// 	load_all(path, info, root, srch_tar, mode);
		// 	delay(200);
		// }
		sort(info, *sort_mode, *UpOrDown);
		break;
	}
		// case 7:
		// {
		// 	check();
		// 	break;
		// }

	default:
		break;
	}

	return F;
}
