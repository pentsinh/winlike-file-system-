// #include <stdio.h>
// #include <stdlib.h>
// #include <dirent.h>
// #include <direct.h>
// #include <string.h>
// #include <graphics.h>
#include "include.h"

// char history[HISTORY_LENGTH][1024] = {0}; // 目录操作记录
// char path[1024];						  // 当前路径
// int now_history = 0;					  // 当前在路径在history中的位置，服务撤销操作
char chosen_name[13] = {-1}; // 被选中的文件名

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
	// memset(info, 0, sizeof(struct file_info) * 10);
	info_init(info);
	while ((entry = readdir(dir)) != NULL)
	{
		// newmouse(&MouseX, &MouseY, &press);
		if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
			continue;
		info[j].num = j;
		// printf("%s", target);
		get_file_info(target, entry->d_name, &info[j]);
		j++;

		if (j >= INFO_LENGTH) //***********暂时只读取10个
			break;
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
	chdir(history[*now_history]);
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
	chdir(history[*now_history]);
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

void new_history(char history[HISTORY_LENGTH][1024], char path[1024]) // 更新目录操作历史
{
	int i;
	for (i = HISTORY_LENGTH; i > 1; i--)
		strcpy(history[i - 1], history[i - 2]);
	strcpy(history[0], path);
}

// int change_dir(struct file_info *info, int x, int y) // 更改目录.返回1选中，返回2确认
// {
// 	int i, j;
// 	// static int is_chosen = 0;//是否处于选中状态
// 	// static char chosen_name[13];//记录选中的文件
// 	char target[1024];
// 	// 查找鼠标点击的区域的文件序号
// 	for (j = 0; j < INFO; j++)
// 		if (y > 90 + j * 20 && y < 90 + j * 20 + 20)
// 		{
// 			i = j;
// 			break;
// 		}

// 	if ((info + i)->name == 0 || strcmp((info + i)->name, "") == 0) // 如果点击空白
// 	{
// 		strcpy(chosen_name, 0);
// 		return 0;
// 	}

// 	else if ((info + i)->name != 0 && (info + i)->flag == 2 && strcmp(chosen_name, (info + i)->name) == 0) // 如果点击两次，进入
// 	{
// 		strcpy(chosen_name, 0);
// 		strcpy(target, ".");
// 		strcat(target, "\\");
// 		strcat(target, (info + i)->name);
// 		chdir(target);
// 		return 2;
// 	}
// 	else if ((info + i)->name != 0 && strcmp(chosen_name, (info + i)->name) != 0) // 如果点击一次，选中
// 	{
// 		strcpy(chosen_name, (info + i)->name);
// 		// setcolor(YELLOW);
// 		// rectangle(120, 90 + i * 20, 640, 90 + i * 20 + 20);
// 		return 1;
// 	}

// 	else
// 	{
// 		strcpy(chosen_name, 0);
// 		return 0;
// 	}
// }

int change_dir(struct file_info *info, int x, int y) // 更改目录.返回1选中，返回2确认
{
	int i = 0; // 目标文件标号
	int j;	   // 循环变量

	char target[1024];
	// 查找鼠标点击的区域的文件序号
	for (j = 0; j < INFO_LENGTH; j++)
		if (y > 90 + j * 20 && y < 90 + j * 20 + 20)
		{
			i = j;
			break;
		}

	if ((info + i)->name == 0 || strcmp((info + i)->name, "") == 0) // 如果点击空白
	{
		for (j = 0; j < INFO_LENGTH; j++) // 所有文件不选中
			set_bit(&(info + j)->flag, 7, 0);
	}

	else if (strcmp((info + i)->name, "") != 0 && get_bit((info + i)->flag, 7) == 1 && get_bit((info + i)->flag, 0) == 0 && get_bit((info + i)->flag, 1) == 1 && get_bit((info + i)->flag, 2) == 0 && get_bit((info + i)->flag, 3) == 0) // 如果点击两次文件夹，进入
	{
		set_bit(&(info + i)->flag, 7, 0);
		strcpy(target, ".");
		strcat(target, "\\");
		strcat(target, (info + i)->name);
		chdir(target);
		return 2;
	}
	else if (strcmp((info + i)->name, "") != 0 && get_bit((info + i)->flag, 7) == 0) // 如果点击一次，选中
	{
		// strcpy(chosen_name, (info + i)->name);
		set_bit(&(info + i)->flag, 7, 1);
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
