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

extern char path[1024];					   // 当前路径
extern char history[HISTORY_LENGTH][1024]; // 操作历史
extern int now_history;					   // 当前在路径在history中的位置，服务撤销操作
extern void *buffer;					   // 缓存
extern struct dir_tree tree;			   // 目录树，用于加载左栏，以及通过左栏快速定位
struct My_filenode *root;

void spinOnce(struct file_info *info) // 更新状态检测函数
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
	struct file_info info[10]; // 存放文件信息
	int gd = DETECT, gm;	   // 图形驱动和图形模式
	char out_put_mode = 0;	   // 主视窗显示模式，0为一般模式，1为搜索模式
	char srch_tar[16];		   // 搜索目标
	int result;				   // 用来存放函数返回值，防止多次调用
	// tree_make(&tree, 0);	   // 目录树开始构建
	root = (struct My_filenode *)malloc(sizeof(struct My_filenode));
	tree_make(root, 0);
	printf("Ready to start!\n");

	buffer = NULL;
	initgraph(&gd, &gm, "C:\\BORLANDC\\BGI"); // 初始化图形模式
	mouseinit();

	if (!login()) // 登陆失败
		return 0;
	else // 登陆成功
	{
		MouseS = 0;
		cleardevice();
		clrmous(MouseX, MouseY);
		// buffer = NULL;
		// tree_make(&tree, 0); // 目录树开始构建
		load_init(info); // 界面初始化
		spinOnce(info);	 // 刷新info
		load_all(info);	 // 显示

		while (1)
		{
			spinOnce(info);

			if (mouse_press(10, 10, 30, 30) == 1) //|| mouse_press(10, 10, 30, 30) == 4)//如果点击<-撤销目录操作
			{
				undo_dir();
				spinOnce(info);
				clrmous(MouseX, MouseY);
				cleardevice();
				load_all(info);
			}
			else if (mouse_press(30, 10, 50, 30) == 1) // || mouse_press(30, 10, 50, 30) == 4)//如果点击->反撤销目录操作
			{
				anti_undo_dir();
				spinOnce(info);
				clrmous(MouseX, MouseY);
				cleardevice();
				load_all(info);
			}
			else if (mouse_press(50, 10, 70, 30) == 1) //|| mouse_press(50, 10, 70, 30) == 4)//如果点击返回上一级目录
			{
				back();
				spinOnce(info);
				clrmous(MouseX, MouseY);
				cleardevice();
				load_all(info);
			}
			else if (mouse_press(70, 10, 90, 30) == 1) //|| mouse_press(70, 10, 90, 30) == 4)//如果点击刷新
			{
				spinOnce(info);
				clrmous(MouseX, MouseY);
				cleardevice();
				load_all(info);
			}

			else if (mouse_press(120, 70, 640, 480) == 1) // || mouse_press(120, 70, 640, 480) == 4)//如果点击文件（夹）区域
			{
				result = change_dir(info, MouseX, MouseY);
				if (result == 2) //|| change_dir(info, MouseX, MouseY) == 0)//进入或无效点击
				{
					clrmous(MouseX, MouseY);
					cleardevice();
					spinOnce(info);
					delay(200);
					load_all(info);
				}
				else if (result == 1) // 选中
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
			// 搜索
			// else if (mouse_press(540, 10, 630, 30) == 1)
			// {
			// 	out_put_mode = 1;
			// 	// srch_input(srch_tar);
			// }
			// else if (mouse_press_out(540, 10, 630, 30) == 1)
			// {
			// 	out_put_mode = 0;
			// }

			// 左栏目录树
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