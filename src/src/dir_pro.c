#include <stdio.h>
#include <dirent.h>
#include <direct.h> 
#include <string.h>
#include <graphics.h>
#include "include.h"

char history[HISTORY_LENGTH][1024] = { 0 };//目录操作记录
char path[1024];
int now_history = 0;//当前在路径在history中的位置，服务撤销操作

void read_dir(DIR* dir, struct dirent* entry, struct file_info* info)//读取当前目录下文件
{
	int j = 0;
	dir=opendir(path);	
	memset(info, 0, sizeof(struct file_info) * 10);
	while ((entry = readdir(dir)) != NULL)
	{
		//newmouse(&MouseX, &MouseY, &press);
		if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
			continue;
		info[j].num = j;
		get_file_info(entry->d_name, &info[j]);
		j++;

		if (j == 10)//***********暂时只读取10个，后面做翻页功能时优化
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

void new_history()//更新目录操作历史
{	
	int i;	
	for (i = HISTORY_LENGTH; i > 1; i--)
		strcpy(history[i - 1], history[i - 2]);
	strcpy(history[0], path);
}


int change_dir(struct file_info* info, int x, int y)//更改目录.返回1选中，返回2确认
{
	int i, j;
	static int is_chosen = 0;//是否处于选中状态
	char target[1024];
	//查找鼠标点击的区域的文件序号
	for (j = 0; j < 10; j++)
		if (y > 95 + j * 20 && y < 95 + j * 20 + 20)
		{
			i = j;
			break;
		}
	if ((info + i)->name == 0)//如果点击空白
		return 0;
	else if ((info + i)->name != 0 && is_chosen == 0)
	{
		is_chosen = 1;
		setcolor(YELLOW);
		rectangle(120, 95 + i, 640, 95 + i + 20);
		return 1;
	}
	else if ((info + i)->name != 0 && strcmp((info + i)->type, "Fold") == 0 && is_chosen == 1)
	{
		is_chosen = 0;
		/*strcpy(target, path);
		strcpy(target, "\\");
		strcpy(target, (info + i)->name);*/
		strcpy(target, ".");
		strcpy(target, "\\");
		strcpy(target, (info + i)->name);
		chdir(target);
	}
	else
		return 0;
}