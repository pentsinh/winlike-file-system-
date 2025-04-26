#include "include.h"
void read_dir(char *target, struct file_info *info, int *page) // 读取指定目录下文件
{
	DIR *dir;
	struct dirent *entry;
	int i = 0; // 循环变量
	int j = 0;
	int now_page = *page;
	dir = opendir(target);
	if (!dir)
	{
		perror("Failed to open directory");
		// printf("%s", target);
		return; // 如果打开目录失败，停止读取
	}
	// memset(info, 0, sizeof(struct file_info) * 10);
	info_init(info);
	while ((entry = readdir(dir)) != NULL)
	{
		// newmouse(&MouseX, &MouseY, &press);
		if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
			continue;

		if (j >= now_page * INFO_LENGTH) // 每页存在10个
		{
			info[j - now_page * INFO_LENGTH].num = j - now_page * INFO_LENGTH + 1;
			// printf("%s", target);
			get_file_info(target, entry->d_name, &info[j - now_page * INFO_LENGTH]);
		}
		if (j >= (now_page + 1) * INFO_LENGTH) //***********暂时只读取10个
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

void new_history(char history[HISTORY_LENGTH][1024], char path[1024]) // 更新目录操作历史***在遇到BORLANDC及里面特定文件夹时会bug***
{
	int i;
	// printf("path=%s", path);
	for (i = HISTORY_LENGTH; i > 1; i--)
		strcpy(history[i - 1], history[i - 2]);
	if (strcmp(path, history[1]) != 0)
		strcpy(history[0], path);
}

int change_dir(struct file_info *info, int x, int y) // 更改目录.返回1选中，返回2确认
{
	int i = 0;		   // 目标文件标号-1
	int j;			   // 循环变量
	int file_num;	   // 目标文件标号
	char target[1024]; // 目标文件绝对路径

	static time_t last_click_time = 0; // 记录上次点击时间
	time_t current_click_time = clock();
	time_t elapsed_ticks = current_click_time - last_click_time;

	// 查找鼠标点击的区域的文件序号
	file_num = get_file_num(x, y, info);
	i = file_num - 1;

	if (file_num == -1) // 点击无效
	{
		for (j = 0; j < INFO_LENGTH; j++) // 所有文件不选中
			set_bit(&(info + j)->flag, 7, 0);
		return 0;
	}

	else if (strcmp((info + i)->name, "") != 0 && get_bit((info + i)->flag, 7) == 1 && get_bit((info + i)->flag, 0) == 0 && get_bit((info + i)->flag, 1) == 1 && get_bit((info + i)->flag, 2) == 0 && get_bit((info + i)->flag, 3) == 0 && elapsed_ticks > 1 && elapsed_ticks < 12 && last_click_time != -1) // 如果点击两次文件夹，进入
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
	else if (strcmp((info + i)->name, "") != 0 && get_bit((info + i)->flag, 7) == 0) // 如果点击一次，选中，这里等待你做多选优化
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

// 手动输入
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
		if (result == 1) // 有输入
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
