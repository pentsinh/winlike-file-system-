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
typedef enum
{
	FILE_TYPE_TEXT = 0,
	FILE_TYPE_DATA,
	FILE_TYPE_DIRECTORY,
	FILE_TYPE_COUNT // ���ڼ��߽�
} FileType;
void build()
{
	char *now_path = NULL;
	char buffer[1024] = {0}, name[13]; // buffer���ڴ����µ�·����name���½��ļ���
	// ������ѡѡ���
	int type_index; // ��¼��������
	press = 0;
	delay(200);
	type_index = drop_down_menu(12, 70, 90, 20, 16, 1, file_type_strings, YELLOW, BLACK, 1, 0);

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

void func()
{
	// ����ѡ��״̬
	int F = 0; // ���ݴ�F��ֵ�ж����ĸ����ܱ�ѡ����
	int click_type;
	int exit_flag = 0; // �˳�ѭ����־
	while (!exit_flag)
	{

		newmouse(&MouseX, &MouseY, &press);
		click_type = mouse_press(10, 42, 500, 65);
		// printf("click_type: %d\n", click_type); // ���click_type��ֵ

		// if (click_type == 1)
		// if (mouse_press(10, 42, 500, 65) == 1)
		if (press == 1)
		{

			// exit(1);
			//  printf("MouseX: %d, MouseY: %d\n", MouseX, MouseY); // ������������
			// if (MouseX >= 12 && MouseX <= 55 && MouseY >= 42 && MouseY <= 65)
			if (detect_mouse(12, 55, 42, 65) == 1)
			{
				F = 1; // ѡ���½�
			}
			// else if (MouseX >= 65 && MouseX <= 80 && MouseY >= 42 && MouseY <= 65)
			else if (detect_mouse(65, 80, 42, 65))
			{
				F = 2; // ѡ�м���
			}
			// else if (MouseX >= 90 && MouseX <= 105 && MouseY >= 42 && MouseY <= 65)
			else if (detect_mouse(90, 105, 42, 65))
			{
				F = 3; // ѡ�и���
			}
			else if (detect_mouse(115, 40, 42, 65))
			{
				F = 4; // ѡ��ճ��
			}
			else if (detect_mouse(150, 170, 42, 65))
			{
				F = 5; // ѡ��ɾ��
			}
			else if (detect_mouse(180, 270, 42, 65))
			{
				F = 6; // ѡ������
			}
			else if (detect_mouse(280, 390, 42, 65))
			{
				F = 7; // ѡ�в鿴
			}
			else if (detect_mouse(400, 450, 42, 65))
			{
				F = 8; // ѡ��������
			}
			else
			{
				exit_flag = 1;
			}
		}
		/*/int if_build,if_cut,if_paste,if_copy,if_delete,if_sort,if_check,if_rename;
		if_build=mouse_press(12,42,55,65);
		if_cut=mouse_press(65,42,80,65);
		if_paste=mouse_press(90,42,105,65);
		if_copy=mouse_press(115,42,140,65);
		if_delete=mouse_press(150,42,170,65);
		if_sort=mouse_press(180,42,270,65);
		if_check=mouse_press(280,42,390,65);
		if_rename=mouse_press(400,42,450,65);*/
		// ���ѡ�С��½���
		switch (F)
		{
		case 1:
		{
			build();
			break;
		}
			// case 2:
			// {
			// 	cut();
			// 	break;
			// }
			// case 3:
			// {
			// 	past();
			// 	break;
			// }
			// case 4:
			// {
			// 	copy();
			// 	break;
			// }
			// case 5:
			// {
			// 	del();
			// 	break;
			// }
			// case 6:
			// {
			// 	sort();
			// 	break;
			// }
			// case 7:
			// {
			// 	check();
			// 	break;
			// }
			// case 8:
			// {
			// 	rename();
			// 	break;
			// }

		default:
			break;
		}
	}
}
