#include "include.h"

int build(struct file_info *info, int x, int y) //-1ʧ�ܣ�0�ɹ�
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
	type_index = drop_down_menu(x, y, 90, 15, 13, 1, file_type_strings, WHITE, DARKGRAY, 1, 0);

	if (type_index == -1 || type_index > 12)
	{
		return -1;
	}

	// ��ȡ��ǰ����Ŀ¼
	char *result = getcwd(buffer, sizeof(buffer));
	if (result = NULL)
	{
		perror("fail to get current path");
		return -1;
	}
	// �����ļ���
	if (type_index != 0)
	{
		// �ļ����ͣ������չ��
		strcpy(name, "NEWFILE");
		if (strlen(file_type_strings[type_index]) > 0)
		{
			strcat(name, ".");
			strcat(name, file_type_strings[type_index]);
		}
	}
	else if (type_index != -1)
	{
		// Ŀ¼����
		strcpy(name, "NEWDIR");
		// if (strlen(file_type_strings[type_index]) > 0)
		// {
		// 	strcat(name, file_type_strings[type_index]);
		// }
	}

	// ��������·��
	now_path = get_file_path(buffer, name);
	if (now_path == NULL)
	{
		fprintf(stderr, "fail to build full path\n");
		return -1;
	}

	// ����½������ļ���
	if (type_index == 0)
	{
		if (mkdir(now_path) != 0)
		{
			perror("fail to new dir");
			free(now_path);
			return -1;
		}
		else
		{
			free(now_path);
			return 0;
		}
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
			return -1;
		}
		else
		{
			free(now_path);
			fclose(file);
			return 1;
		}
	}
}

// void frename(struct file_info *info)
// {
// 	settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
// 	char new_name[13] = {0};
// 	int wc_select;
// 	char *suffix; // ��׺
// 	char *file_type_strings[] =
// 		{
// 			"FOLD",
// 			"TXT",
// 			"C",
// 			"CPP",
// 			"H",
// 			"OBJ",
// 			"EXE",
// 			"JPG",
// 			"PNG",
// 			"DOC",
// 			"XLS",
// 			"PPT",
// 			"PDF",
// 		};
// 	wc_select = is_selected(info) - 1; // ��¼�ĸ��ļ���ѡ����
// 	if (wc_select == -1)
// 		return;
// 	// char bd[10] = {0};
// 	int board = 0; // ��¼���̲���
// 	int result = 0;
// 	suffix = file_type_strings[get_file_type((info + wc_select)->name)];
// 	setcolor(RED);
// 	outtextxy(120, 95 + wc_select * 20, (info + wc_select)->name); // ѡ�е��ļ������ȱ�Ϊ��ɫ����
// 	clear_keyboard_buffer();
// 	// ��ѭ��
// 	while (1)
// 	{
// 		newmouse(&MouseX, &MouseY, &press);
// 		int i = mouse_press_out(120, 95 + wc_select * 20, 200, 115 + wc_select * 20); // �ж��Ƿ����˱������
// 		if (i == 1)
// 		{
// 			setcolor(WHITE);
// 			outtextxy(120, 95 + wc_select * 20, (info + wc_select)->name);
// 			return;
// 		}
// 		board = getbuffer_keybd(new_name, 10);
// 		// ���ѡ�е��������������ɾ���������ֲ��ָ��ǵȴ�����������
// 		if (board == 1)
// 		{
// 			bar(120, 95 + wc_select * 20, 200, 115 + wc_select * 20);
// 			outtextxy(120, 95 + wc_select * 20, new_name);
// 			while (1)
// 			{
// 				newmouse(&MouseX, &MouseY, &press);
// 				// ��ȡ�������� (�Ƿ�Ҫ�����ӳٵȴ�������ȫ��)
// 				result = getbuffer_keybd(new_name, 13);
// 				if (result == 1)
// 				{
// 					bar(120, 95 + wc_select * 20, 200, 115 + wc_select * 20);
// 					outtextxy(120, 95 + wc_select * 20, new_name);
// 				}
// 				else if (result == 2)
// 				{
// 					// ɾ�������������ֺ��»س�
// 					if (strlen(new_name) > 0)
// 					{
// 						// ִ������������
// 						rename((info + wc_select)->name, new_name);
// 						strcpy((info + wc_select)->name, new_name);
// 						strcat((info + wc_select)->name, ".");
// 						strcat((info + wc_select)->name, suffix);
// 						setcolor(WHITE);
// 						outtextxy(120, 95 + wc_select * 20, (info + wc_select)->name);
// 						return;
// 					}
// 					// ɾ�������û������Ͱ��»س�������ʾԭ��������
// 					else
// 					{
// 						setcolor(WHITE);
// 						outtextxy(120, 95 + wc_select * 20, (info + wc_select)->name);
// 						return;
// 					}
// 				}
// 				//  ɾ����û�м�⵽���� �򱣳�ԭ����
// 				else if (result == 0)
// 				{
// 					delay(3);
// 					continue;
// 				}
// 			}
// 		}
// 		// ���ѡ�е����������û�����룬�򱣳�ԭ����
// 		else if (board == 0)
// 		{
// 			delay(3);
// 			continue;
// 		}
// 		// ���ѡ�е��������������س�����ʾ������
// 		else if (board == 2)
// 		{
// 			outtextxy(120, 95 + wc_select * 20, (info + wc_select)->name);
// 			return;
// 		}
// 	}
// }

int frename(struct file_info *info, struct pro_history history[5], int pic_flag) //-1ʧ�ܣ�0�ɹ�
{
	settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
	char new_name[13] = {0};
	char old_name[13] = {0}; // ��¼������
	int wc_select;
	char *suffix; // ��׺
	char *file_type_strings[] =
		{
			"THIS_PC",
			"C_DISK",
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
			"OTHER",
		};

	wc_select = is_selected(info) - 1; // ��¼�ĸ��ļ���ѡ����
	if (wc_select == -1)
		return -1;

	// char bd[10] = {0};
	int board = 0; // ��¼���̲���
	int result = 0;
	// strcpy(new_name, (info + wc_select)->name);
	// wc_select += 1;
	suffix = file_type_strings[get_file_type((info + wc_select)->name)];
	strcpy(old_name, (info + wc_select)->name); // ��¼������

	setcolor(RED);
	outtextxy(140, 95 + wc_select * 20, (info + wc_select)->name); // ѡ�е��ļ������ȱ�Ϊ��ɫ����
	clear_keyboard_buffer();

	// ��ѭ��
	while (1)
	{
		newmouse(&MouseX, &MouseY, &press);
		result = getbuffer_keybd(new_name, 8);

		if (result == 1) // ���������
		{
			setfillstyle(SOLID_FILL, BLACK);
			bar(140, 92 + wc_select * 20, 200, 108 + wc_select * 20);
			setcolor(RED);
			outtextxy(140, 95 + wc_select * 20, new_name);
		}
		else if (mouse_press_out(140, 95 + wc_select * 20, 200, 115 + wc_select * 20) || result == 2) // ���������߻س�
		{
			// ���������ֺ��»س�
			if (strlen(new_name) > 0)
			{
				// ִ������������

				// strcpy((info + wc_select)->name, new_name);
				if (get_file_type((info + wc_select)->name) != 2) // �ļ���
				{
					strcat(new_name, ".");
					strcat(new_name, suffix);
				}

				if (rename((info + wc_select)->name, new_name) == 0) // �ɹ�
				{
					setcolor(WHITE);
					outtextxy(140, 95 + wc_select * 20, (info + wc_select)->name);
					new_history(history, RENAME, get_file_path(getcwd(NULL, 0), old_name), get_file_path(getcwd(NULL, 0), new_name));
					return 0;
				}
				else
				{
					warn("������ʧ��");
					return -1;
				}
			}
			else
			{
				warn("����Ϊ�գ�");
				setcolor(WHITE);
				outtextxy(140, 95 + wc_select * 20, (info + wc_select)->name);
				return -1;
			}
		}
	}
}

int del(struct file_info *info, struct pro_history history[5]) //-1ʧ�ܣ�0�ɹ�
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
		return -1;
	}
	// ��������·��
	now_path = get_file_path(buffer, (info + wc_select)->name);
	if (now_path == NULL)
	{
		fprintf(stderr, "fail to build full path\n");
		return -1;
	}

	// ����ɾ���ļ�
	if (c_p(now_path, "C:\\PROJECT\\DEVEL\\BIN\\BIN_0") != -1 && rm_dir(now_path) == 1)
	{
		new_history(history, DELETE, "", now_path); // ��¼ɾ������
		free(now_path);								// �ͷŶ�̬������ڴ�
		// printf("success to rm dir\n");
		return 0;
	}
	else
	{
		return -1;
		// printf("fail to rm dir\n");
	}
}

int copy(struct file_info *info, char *source_path) //-1ʧ�ܣ�0�ɹ�
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
		// fprintf(stderr, "copy have done");
		printf("%s", source_path);
		return 0;
	}
}

int paste(char *source_path, int *flag) //-1ʧ�ܣ�1�ɹ�
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
		// fprintf(stderr, "succeed to copy file\n");
		//  ���֮ǰ�Ǽ��в�������ճ������ɾ��ԭ�ļ�
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

int cut(struct file_info *info, int *flag, char *source_path) //-1ʧ�ܣ�1�ɹ�
{
	if (copy(info, source_path) != 0) // ���������ͼ�꣬�ȵ��ø��ƺ���
	{
		// printf("failed to cut");
		return -1;
	}
	int wc_select = is_selected(info) - 1; // ��¼�ĸ��ļ���ѡ����
	setcolor(DARKGRAY);
	outtextxy(140, 95 + wc_select * 20, (info + wc_select)->name); // ѡ�е��ļ������ȱ�Ϊ��ɫ

	*flag = 1;
	return 1;
}

int check(int x, int y, int *pic_flag)
{
	char *choices[] =
		{
			"Сͼ��",
			"��ͼ��"};
	int choice_index; // ��¼��������
	press = 0;
	delay(200);
	choice_index = drop_down_menu(x, y, 80, 25, 2, 12, choices, WHITE, DARKGRAY, 0, 0);

	if (choice_index != -1)
		*pic_flag = choice_index;
	return 0;
}

int func(struct file_info *info, char *source_path, int *sort_mode, int *UpOrDown, char **sort_menu_p, int *pic_flag)
{
	// ����ѡ��״̬
	int F = 0;							 // ���ݴ�F��ֵ�ж����ĸ����ܱ�ѡ����
	int exit_flag = 0;					 // �˳�ѭ����־
	struct pro_history history[5] = {0}; // ������ʷ
	for (int i = 0; i < 5; i++)			 // ��ʼ��������ʷ
	{
		char bin_path[64] = "C:\\PROJECT\\DEVEL\\BIN\\BIN_"; // ����վ·��
		char buffer[64] = {0};
		strcat(bin_path, itoa(i + 1, buffer, 10)); // ƴ�ӻ���վ·��
		history[i].num = i + 1;
		history[i].process = -1; // ��ʼ��Ϊ-1
		strcpy(history[i].src, "");
		strcpy(history[i].tar, "");
		strcpy(history[i].bin_path, bin_path); // ��ʼ������վ·��
	}

	setcolor(YELLOW);
	static int result = -1; // ��ֹ��ε���
	static int if_cut = 0;	// �ж�֮ǰ�Ƿ���еļ��й�������ȷ��ճ�����Ƿ�Ҫ����ɾ������

	while (detect_m(0, 37, 365, 62) == 1) // ����ڹ�����
	{

		newmouse(&MouseX, &MouseY, &press);
		highlight_detector();

		if (mouse_press(5, 37, 60, 62) == 1)
		{
			F = 1; // ѡ���½�
		}
		else if (mouse_press(60, 37, 85, 62) == 1)
		{
			F = 2; // ѡ�м���
		}
		else if (mouse_press(85, 37, 110, 62) == 1)
		{
			F = 3; // ѡ�и���
		}
		else if (mouse_press(110, 37, 135, 62) == 1)
		{
			F = 4; // ѡ��ճ��
		}
		else if (mouse_press(135, 37, 165, 62) == 1)
		{
			F = 5; // ѡ��������
		}
		else if (mouse_press(165, 37, 190, 62) == 1)
		{
			F = 6; // ѡ��ɾ��
		}
		else if (mouse_press(190, 37, 275, 62) == 1)
		{
			F = 7; // ѡ������
		}
		else if (mouse_press(275, 37, 365, 62) == 1)
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
		int result_1 = build(info, 12, 70);
		if (result_1 == 0) // �ļ���
		{
			new_history(history, NEWFILE, get_file_path(getcwd(NULL, 0), "NEWFOLD"), "");
			break;
		}
		else if (result_1 == 1)
		{
			new_history(history, NEWFILE, get_file_path(getcwd(NULL, 0), "NEWFILE"), "");
			break;
		}
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
		// printf("after copy src=%s", source_path);
		break;
	}
	case 4: // ճ��
	{
		// printf("4\n");
		if (result == 0)
		{
			// printf("before paste src=%s", source_path);
			if (paste(source_path, &if_cut) != -1)
			{
				if (if_cut == 1)
					new_history(history, CUT_PASTE, get_file_path(getcwd(NULL, 0), path_to_name(source_path)), source_path);
				else
					new_history(history, COPY_PASTE, get_file_path(getcwd(NULL, 0), path_to_name(source_path)), source_path);
				// printf("Copy and paste succeeded\n");
			}
			free(source_path);
		}
		if_cut = 0; // ���ü��б�־
		result = -1;
		break;
	}
	case 5:
	{
		frename(info, history, *pic_flag);
		break;
	}
	case 6: // ɾ��
	{
		del(info, history);
		break;
	}
	case 7: // ����
	{
		result = drop_down_menu(195, 60, 80, 25, 6, 12, sort_menu_p, WHITE, DARKGRAY, 0, 0);
		if (result >= 0 && result <= 3)
			*sort_mode = result;
		else if (result == 4)
			*UpOrDown = 1;
		else if (result == 5)
			*UpOrDown = -1;
		sort(info, *sort_mode, *UpOrDown);
		break;
	}
	case 8: // �鿴
	{
		check(280, 70, pic_flag);
		break;
	}
	default:
		break;
	}

	return F;
}

void new_history(struct pro_history history[5], int process, char tar[1024], char src[1024]) // ����Ŀ¼������ʷ
{
	int i;
	rm_dir("C:\\PROJECT\\DEVEL\\BIN\\BIN_5"); // ɾ������վ�����һ���ļ�

	// ����ʷ��¼����ƶ�
	for (i = 4; i > 0; i--)
	{
		history[i].num = i + 1; // �������
		strcpy(history[i].tar, history[i - 1].tar);
		history[i].process = history[i - 1].process;
		strcpy(history[i].src, history[i - 1].src);
	}
	strcpy(history[0].tar, tar);
	history[0].process = process;
	strcpy(history[0].src, src);

	rename("C:\\PROJECT\\DEVEL\\BIN\\BIN_0", "C:\\PROJECT\\DEVEL\\BIN\\BIN_1");
	strcpy(history[0].bin_path, "C:\\PROJECT\\DEVEL\\BIN\\BIN_1");
	mkdir("C:\\PROJECT\\DEVEL\\BIN\\BIN_0"); // �����µĻ���վ�ļ���
}

void undo_pro(struct pro_history history[5]) // ��������
{
	if (history[0].process == -1) // ���û�в�����¼
	{
		warn("û�пɳ����Ĳ���");
		return;
	}
	char *bin_path = history[0].bin_path;
	char *src_path = history[0].src;
	char *tar_path = history[0].tar;

	switch (history[0].process)
	{
	case NEWFILE:
		rm_dir(tar_path); // ɾ���½����ļ����ļ���
		break;
	case CUT_PASTE:
		c_p(get_file_path(tar_path, path_to_name(src_path)), get_father_path(src_path)); // �����е��ļ����ļ���ճ����Ŀ��·��
		rm_dir(get_file_path(tar_path, path_to_name(src_path)));
		break;
	case COPY_PASTE:
		rm_dir(get_file_path(tar_path, path_to_name(src_path)));
		break;
	case RENAME:
		rename(src_path, tar_path); // �ָ�������֮ǰ���ļ����ļ���
	case DELETE:
		c_p(get_file_path(bin_path, path_to_name(src_path)), get_father_path(src_path)); // ��ɾ�����ļ����ļ��лָ���Ŀ��·��
		rm_dir(get_file_path(bin_path, path_to_name(src_path)));
		break;
	default:
		break;
	}

	history_reset(history[0], 0, "", "", ""); // ���������¼
	for (int i = 1; i < 5; i++)				  // ������Ĳ�����¼��ǰ�ƶ�
	{
		history[i - 1].process = history[i].process;
		strcpy(history[i - 1].src, history[i].src);
		strcpy(history[i - 1].tar, history[i].tar);
	}
}

void history_reset(struct pro_history *history, int num, char src[1024], char tar[1024], char bin_path[64]) // ��ʼ��������ʷ
{
	history->num = num;
	history->process = -1;
	strcpy(history->src, src);
	strcpy(history->tar, tar);
}
