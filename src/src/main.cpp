// #define TEST

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

// int mode_shift = 0x11;

extern void *buffer; // 缓存
// extern struct dir_tree tree;			   // 目录树，用于加载左栏，以及通过左栏快速定位

void spinOnce(char path[1024], struct file_info *info, int mode, char history[HISTORY_LENGTH][1024], int now_history) // 更新状态检测函数
{
	newmouse(&MouseX, &MouseY, &press);
	if (mode == 0)
	{
		getcwd(path, sizeof(path));
		read_dir(path, info);
	}
	if (now_history == 0 && strcmp(path, history[now_history]) != 0)
		new_history(history, path);
}

int main()
{
	struct My_filenode *root;			// 目录树的根
	char path[1024];					// 当前路径
	char history[HISTORY_LENGTH][1024]; // 操作历史
	int now_history;					// 当前在路径在history中的位置，服务撤销操作
	struct file_info info[10];			// 存放文件信息
	int gd = DETECT, gm;				// 图形驱动和图形模式
	char mode = 0;						// 主视窗显示模式，0为一般模式，1为搜索模式
	char mode_shift = _0to0;			// 模式切换
	char srch_tar[16];					// 搜索目标
	int result;							// 用来存放函数返回值，防止多次调用
	root = (struct My_filenode *)malloc(sizeof(struct My_filenode));
	tree_make(root, 0); // 目录树开始构建
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
		load_init(path, info, history); // 界面初始化

		spinOnce(path, info, mode, history, now_history); // 刷新info
		load_all(path, info, root, srch_tar, mode);		  // 显示

		while (1)
		{
			spinOnce(path, info, mode, history, now_history);

			if (mouse_press(10, 10, 30, 30) == 1) //|| mouse_press(10, 10, 30, 30) == 4)//如果点击<-撤销目录操作
			{
				undo_dir(history, now_history);
				spinOnce(path, info, mode, history, now_history);
				clrmous(MouseX, MouseY);
				cleardevice();
				load_all(path, info, root, srch_tar, mode);
			}
			else if (mouse_press(30, 10, 50, 30) == 1) // || mouse_press(30, 10, 50, 30) == 4)//如果点击->反撤销目录操作
			{
				anti_undo_dir(history, now_history);
				spinOnce(path, info, mode, history, now_history);
				clrmous(MouseX, MouseY);
				cleardevice();
				load_all(path, info, root, srch_tar, mode);
			}
			else if (mouse_press(50, 10, 70, 30) == 1) //|| mouse_press(50, 10, 70, 30) == 4)//如果点击返回上一级目录
			{
				back(path, history, now_history);
				spinOnce(path, info, mode, history, now_history);
				clrmous(MouseX, MouseY);
				cleardevice();
				load_all(path, info, root, srch_tar, mode);
			}
			else if (mouse_press(70, 10, 90, 30) == 1) //|| mouse_press(70, 10, 90, 30) == 4)//如果点击刷新
			{
				spinOnce(path, info, mode, history, now_history);
				clrmous(MouseX, MouseY);
				cleardevice();
				if (mode == 0)
					strcpy(srch_tar, "");
				load_all(path, info, root, srch_tar, mode);
			}

			else if (mouse_press(120, 70, 640, 480) == 1) // || mouse_press(120, 70, 640, 480) == 4)//如果点击文件（夹）区域
			{
				result = change_dir(info, MouseX, MouseY);
				if (result == 2) //|| change_dir(info, MouseX, MouseY) == 0)//进入或无效点击
				{
					clrmous(MouseX, MouseY);
					cleardevice();
					spinOnce(path, info, mode, history, now_history);
					delay(200);
					load_all(path, info, root, srch_tar, mode);
				}
				else if (result == 1) // 选中
				{
					clrmous(MouseX, MouseY);
					cleardevice();
					spinOnce(path, info, mode, history, now_history);
					delay(200);
					load_all(path, info, root, srch_tar, mode);
				}
				else if (result == 0)
				{
					clrmous(MouseX, MouseY);
					cleardevice();
					delay(200);
					load_all(path, info, root, srch_tar, mode);
				}
			}

			// 左栏目录树
			else if (mouse_press(10, 70, 100, 470) == 1)
			{
				if (chdir(get_file_path_left(root, MouseX, MouseY)) != -1)
				{
					mode_shift = _1to0;
					mode = 0;

					getcwd(path, sizeof(path));
					spinOnce(path, info, mode, history, now_history);
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

			// 搜索
			// 模式切换判别
			// if (mouse_press(540, 10, 630, 30) == 1)
			if (MouseX > 540 && MouseX < 630 && MouseY > 10 && MouseY < 30 && press == 1) // 哪个效果好用哪个
			{
				if (mode_shift == _0to0 || mode_shift == _1to0)
				{
					mode_shift = _0to1;
					mode = 1;
				}
				else // if (mode_shift == _0to1 || mode_shift == _1to1)
					mode_shift = _1to1;
			}
			if (mouse_press_out(540, 10, 630, 30) == 1)
			{
				if (mode_shift == _0to1 || mode_shift == _1to1)
				{
					mode_shift = _1to0;
					mode = 1;
				}
				else if (mode_shift == _0to0 || mode_shift == _1to0)
					mode_shift = _0to0;
			}

			// 右键处理
			if (mouse_press(120, 70, 640, 480) == 2)
			{
			}

			// 模式切换处理
			if (mode_shift == _0to1) // 从一般模式到搜索模式
			{
				mode = 1;
				clrmous(MouseX, MouseY);
				load_top(path, srch_tar, mode);
				mode_shift = _1to1;
			}
			else if (mode_shift == _1to0) // 从搜索模式到一般模式，并且搜索目标为空
			{
				mode = 0;
				load_top(path, srch_tar, mode);
				mode_shift = _0to0;
			}

			if (mode_shift == _1to1 || mode_shift == _0to1) // 如果处于搜索模式
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