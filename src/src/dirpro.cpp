#include "include.h"
void read_dir(char *target, struct file_info *info, int *page) // ��ȡָ��Ŀ¼���ļ�
{
	DIR *dir;
	struct dirent *entry;
	int i = 0; // ѭ������
	int j = 0;
	int now_page = *page;
	dir = opendir(target);
	if (!dir)
	{
		perror("Failed to open directory");
		// printf("%s", target);
		return; // �����Ŀ¼ʧ�ܣ�ֹͣ��ȡ
	}
	// memset(info, 0, sizeof(struct file_info) * 10);
	info_init(info);
	while ((entry = readdir(dir)) != NULL)
	{
		// newmouse(&MouseX, &MouseY, &press);
		if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
			continue;

		if (j >= now_page * INFO_LENGTH) // ÿҳ����10��
		{
			info[j - now_page * INFO_LENGTH].num = j - now_page * INFO_LENGTH + 1;
			// printf("%s", target);
			get_file_info(target, entry->d_name, &info[j - now_page * INFO_LENGTH]);
		}
		if (j >= (now_page + 1) * INFO_LENGTH) //***********��ʱֻ��ȡ10��
		{
			if (get_info_num(info) == 0 && now_page >= 1)
			{
				*page = now_page - 1;
			}
			break;
		}
		j++;
	}
	closedir(dir);
}

int undo_dir(char history[HISTORY_LENGTH][1024], int *now_history)
{

	int now = *now_history;

	if (strcmp(history[now + 1], "\0") == 0)
		return 0;

	else if (now < HISTORY_LENGTH - 1 && strcmp(history[now + 1], "\0") != 0)
		(*now_history) = now + 1;
	// printf("entering [%d]%s\n", *now_history, history[*now_history]);
	chdir(history[now + 1]);
	return 1;
}

int anti_undo_dir(char history[HISTORY_LENGTH][1024], int *now_history)
{
	int now = *now_history;
	if (now == 0)
		return 0;
	else if (now > 0)
		(*now_history) = now - 1;
	// printf("entering [%d]%s\n", *now_history, history[*now_history]);
	chdir(history[now - 1]);
	return 1;
}

int back(char path[1024], char history[HISTORY_LENGTH][1024], int *now_history)
{
	if (strcmp(path, "C:\\") == 0)
		return 0;
	int i;

	chdir("..");
	getcwd(path, sizeof(path) * 1024);
	if (*now_history != 0)
	{
		for (i = 0; i < *now_history && i + *now_history < HISTORY_LENGTH; i++)
			strcpy(history[i], history[i + *now_history]);
		for (i = 0; i < *now_history && i + *now_history < HISTORY_LENGTH; i++)
			strcpy(history[HISTORY_LENGTH - 1 - i], "\0");
		*now_history = 0;
	}
	return 1;
}

void new_history(char history[HISTORY_LENGTH][1024], char path[1024]) // ����Ŀ¼������ʷ***������BORLANDC�������ض��ļ���ʱ��bug***
{
	int i;
	// printf("path=%s", path);
	for (i = HISTORY_LENGTH; i > 1; i--)
		strcpy(history[i - 1], history[i - 2]);
	if (strcmp(path, history[1]) != 0)
		strcpy(history[0], path);
}

int change_dir(struct file_info *info, int x, int y) // ����Ŀ¼.����1ѡ�У�����2ȷ��
{
	int i = 0;		   // Ŀ���ļ����-1
	int j;			   // ѭ������
	int file_num;	   // Ŀ���ļ����
	char target[1024]; // Ŀ���ļ�����·��

	static time_t last_click_time = 0; // ��¼�ϴε��ʱ��
	time_t current_click_time = clock();
	time_t elapsed_ticks = current_click_time - last_click_time;

	// �����������������ļ����
	file_num = get_file_num(x, y, info);
	i = file_num - 1;

	if (file_num == -1) // �����Ч
	{
		for (j = 0; j < INFO_LENGTH; j++) // �����ļ���ѡ��
			set_bit(&(info + j)->flag, 7, 0);
		return 0;
	}

	else if (strcmp((info + i)->name, "") != 0 && get_bit((info + i)->flag, 7) == 1 && get_bit((info + i)->flag, 0) == 0 && get_bit((info + i)->flag, 1) == 1 && get_bit((info + i)->flag, 2) == 0 && get_bit((info + i)->flag, 3) == 0 && elapsed_ticks > 1 && elapsed_ticks < 12 && last_click_time != -1) // �����������ļ��У�����
	{
		last_click_time = -1;
		set_bit(&(info + i)->flag, 7, 0);
		// strcpy(target, ".");
		// strcat(target, "\\");
		// strcat(target, (info + i)->name);
		// chdir(target);
		chdir((info + i)->path);
		return 2;
	}
	else if (strcmp((info + i)->name, "") != 0 && get_bit((info + i)->flag, 7) == 0) // ������һ�Σ�ѡ�У�����ȴ�������ѡ�Ż�
	{
		last_click_time = current_click_time;
		if (is_selected(info) != 0)
			unselect_all(info);
		set_bit(&(info + i)->flag, 7, 1);

		return 1;
	}
	else
		return 0;
}

// �ֶ�����
int keyin_dir(char path[1024], int length)
{
	int result = 0;
	char nowpath[1024];
	strcpy(nowpath, path);
	clrmous(MouseX, MouseY);
	highlight(90, 10, 500, 30, BLACK, DARKGRAY);

	while (1)
	{
		newmouse(&MouseX, &MouseY, &press);
		// blbl(95, 15, path, 1, WHITE, BLACK);
		result = getbuffer_keybd(path, length);
		if (result == 1) // ������
		{
			clearRectangle(90, 10, 500, 30, DARKGRAY);
			setcolor(WHITE);
			settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
			rectangle(90, 10, 500, 30);
			outtextxy(92, 15, path);
		}
		else if (result == 2 || mouse_press_out(90, 10, 500, 30) == 1)
		{
			if (strcmp(path, "\0") == 0)
				strcpy(path, nowpath);
			if (chdir(path) == -1)
			{
				strcpy(path, nowpath);
				chdir(nowpath);
			}
			return 1;
		}
	}
}
