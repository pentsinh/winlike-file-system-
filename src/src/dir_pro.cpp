// #include <stdio.h>
// #include <stdlib.h>
// #include <dirent.h>
// #include <direct.h>
// #include <string.h>
// #include <graphics.h>
#include "include.h"

char history[HISTORY_LENGTH][1024] = {0}; // 目录操作记录
char path[1024];						  // 当前路径
int now_history = 0;					  // 当前在路径在history中的位置，服务撤销操作
char chosen_name[13] = {-1};			  // 被选中的文件名

void read_dir(char *target, struct file_info *info) // 读取指定目录下文件
{
	DIR *dir;
	struct dirent *entry;
	int j = 0;
	dir = opendir(target);
	if (!dir)
	{
		perror("Failed to open directory");
		// printf("%s", target);
		return; // 如果打开目录失败，停止读取
	}
	memset(info, 0, sizeof(struct file_info) * 10);
	while ((entry = readdir(dir)) != NULL)
	{
		// newmouse(&MouseX, &MouseY, &press);
		if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
			continue;
		info[j].num = j;
		get_file_info(target, entry->d_name, &info[j]);
		j++;

		if (j == 10) //***********暂时只读取10个，后面做翻页功能时优化
			break;
	}
	closedir(dir);
}

void undo_dir()
{
	if (now_history < HISTORY_LENGTH - 1 && strcmp(history[now_history + 1], "\0") != 0)
		now_history++;
	chdir(history[now_history]);
}
void anti_undo_dir()
{
	if (now_history > 0)
		now_history--;
	chdir(history[now_history]);
}
void back()
{
	int i;
	chdir("..");
	getcwd(path, sizeof(path));
	if (now_history != 0)
	{
		for (i = 0; i < now_history && i + now_history < HISTORY_LENGTH; i++)
			strcpy(history[i], history[i + now_history]);
		for (i = 0; i < now_history && i + now_history < HISTORY_LENGTH; i++)
			strcpy(history[HISTORY_LENGTH - 1 - i], "\0");
		now_history = 0;
	}
}

void new_history() // 更新目录操作历史
{
	int i;
	for (i = HISTORY_LENGTH; i > 1; i--)
		strcpy(history[i - 1], history[i - 2]);
	strcpy(history[0], path);
}

int change_dir(struct file_info *info, int x, int y) // 更改目录.返回1选中，返回2确认
{
	int i, j;
	// static int is_chosen = 0;//是否处于选中状态
	// static char chosen_name[13];//记录选中的文件
	char target[1024];
	// 查找鼠标点击的区域的文件序号
	for (j = 0; j < 10; j++)
		if (y > 90 + j * 20 && y < 90 + j * 20 + 20)
		{
			i = j;
			break;
		}
	if ((info + i)->name == 0 || strcmp((info + i)->name, "") == 0) // 如果点击空白
	{
		strcpy(chosen_name, 0);
		return 0;
	}
	else if ((info + i)->name != 0 && (info + i)->flag == 2 && strcmp(chosen_name, (info + i)->name) == 0) // 如果点击两次，进入
	{
		strcpy(chosen_name, 0);
		strcpy(target, ".");
		strcat(target, "\\");
		strcat(target, (info + i)->name);
		chdir(target);
		return 2;
	}
	else if ((info + i)->name != 0 && strcmp(chosen_name, (info + i)->name) != 0) // 如果点击一次，选中
	{
		strcpy(chosen_name, (info + i)->name);
		// setcolor(YELLOW);
		// rectangle(120, 90 + i * 20, 640, 90 + i * 20 + 20);
		return 1;
	}

	else
	{
		strcpy(chosen_name, 0);
		return 0;
	}
}
