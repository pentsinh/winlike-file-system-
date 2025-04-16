//#define TEST

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

extern void *buffer; // 缓存

struct menu
{
	char *option;
	struct menu *next;
	struct menu *son_menu_head;
};

void spinOnce(char path[1024], struct file_info *info, int mode, char history[HISTORY_LENGTH][1024], int now_history, int sort_mode, int UpOrDown) // 更新状态检测函数
{
	newmouse(&MouseX, &MouseY, &press);
	if (mode == 0)
	{
		getcwd(path, sizeof(path) * 1024);
		// read_dir(path, info);
	}
	// printf("%s [%d]%s\n", path, now_history, history[now_history]);
	sort(info, sort_mode, UpOrDown);

	if (now_history == 0 && strcmp(path, history[now_history]) != 0)
	{
		new_history(history, path);
	}

	// for (int i = 0; i < HISTORY_LENGTH; i++)
	// 	printf("[%d]%s    ", i, history[i]);
	// printf("\n");
}

int main()
{
	int gd = DETECT, gm; // 图形驱动和图形模式

	struct My_filenode *root;				  // 目录树的根
	char path[1024];						  // 当前路径
	char history[HISTORY_LENGTH][1024] = {0}; // 操作历史
	int now_history = 0;					  // 当前在路径在history中的位置，服务撤销操作
	struct file_info info[10];				  // 存放文件信息

	int i; // 循环变量

	int sort_mode = 0; // 排序方法
	int UpOrDown = 1;  // 升序/降序

	char mode = 0;			 // 主视窗显示模式，0为一般模式，1为搜索模式
	char mode_shift = _0to0; // 模式切换
	char srch_tar[16];		 // 搜索目标

	int choose_mode = 0; // 点击选择模式

	int result; // 用来存放函数返回值，防止多次调用

	root = (struct My_filenode *)malloc(sizeof(struct My_filenode));

	initgraph(&gd, &gm, "C:\\BORLANDC\\BGI"); // 初始化图形模式
	power_on();
	welcome();

	tree_make(root, 0); // 目录树开始构建
	// printf("Ready to start!\n");

	buffer = NULL;

	mouseinit();

	if (!login()) // 登陆失败
		return 0;
	else // 登陆成功
	{
		MouseS = 0;
		cleardevice();
		clrmous(MouseX, MouseY);
		load_init(path, info, history); // 界面初始化
		read_dir(path, info);

		spinOnce(path, info, mode, history, now_history, sort_mode, UpOrDown); // 刷新info
		load_all(path, info, root, srch_tar, mode);							   // 显示

		// 排序菜单初始化
		char sort_menu[6][16] = {"名称", "修改时间", "类型", "大小", "递增", "递减"};
		char **sort_menu_p = (char **)malloc(6 * sizeof(char *));
		for (i = 0; i < 6; i++)
		{
			sort_menu_p[i] = (char *)malloc(16 * sizeof(char));
			strcpy(sort_menu_p[i], sort_menu[i]);
		}

		// 右键菜单初始化
		char RB_menu[4][16] = {"排序方式", "撤销", "新建", "属性"};
		char **RB_menu_p = (char **)malloc(4 * sizeof(char *));
		for (i = 0; i < 4; i++)
		{
			RB_menu_p[i] = (char *)malloc(16 * sizeof(char));
			strcpy(RB_menu_p[i], RB_menu[i]);
		}

		while (1)
		{
			// spinOnce(path, info, mode, history, now_history, sort_mode, UpOrDown);
			newmouse(&MouseX, &MouseY, &press);

			if (mouse_press(10, 10, 30, 30) == 1) //|| mouse_press(10, 10, 30, 30) == 4)//如果点击<-撤销目录操作
			{
				result = undo_dir(history, &now_history);
				spinOnce(path, info, mode, history, now_history, sort_mode, UpOrDown);
				if (result == 1)
					read_dir(path, info);
				clrmous(MouseX, MouseY);
				cleardevice();
				load_all(path, info, root, srch_tar, mode);
			}
			else if (mouse_press(30, 10, 50, 30) == 1) // || mouse_press(30, 10, 50, 30) == 4)//如果点击->反撤销目录操作
			{
				result = anti_undo_dir(history, &now_history);
				spinOnce(path, info, mode, history, now_history, sort_mode, UpOrDown);
				if (result == 1)
					read_dir(path, info);
				clrmous(MouseX, MouseY);
				cleardevice();
				load_all(path, info, root, srch_tar, mode);
			}
			else if (mouse_press(50, 10, 70, 30) == 1) //|| mouse_press(50, 10, 70, 30) == 4)//如果点击返回上一级目录
			{
				result = back(path, history, &now_history);
				spinOnce(path, info, mode, history, now_history, sort_mode, UpOrDown);
				if (result == 1)
					read_dir(path, info);
				clrmous(MouseX, MouseY);
				cleardevice();
				load_all(path, info, root, srch_tar, mode);
			}
			else if (mouse_press(70, 10, 90, 30) == 1) //|| mouse_press(70, 10, 90, 30) == 4)//如果点击刷新
			{
				spinOnce(path, info, mode, history, now_history, sort_mode, UpOrDown);
				read_dir(path, info);
				clrmous(MouseX, MouseY);
				cleardevice();
				if (mode == 0)
					strcpy(srch_tar, "");
				load_all(path, info, root, srch_tar, mode);
			}
			else if (mouse_press(10, 40, 180, 65) == 1) //|| mouse_press(10, 40, 500, 65) == 4)//如果点击上方功能区域
			{

				func();
				spinOnce(path, info, mode, history, now_history, sort_mode, UpOrDown);
				clrmous(MouseX, MouseY);
				cleardevice();
				load_all(path, info, root, srch_tar, mode);
			}
			else if (mouse_press(180, 42, 260, 60) == 1) // 如果排序下拉菜单
			{
				result = drop_down_menu(180, 60, 100, 40, 6, 16, sort_menu_p, WHITE, BLACK, 0, 0);
				if (result >= 0 && result <= 3)
					sort_mode = result;
				else if (result == 4)
					UpOrDown = 1;
				else if (result == 5)
					UpOrDown = -1;
				if (result != -1)
				{
					spinOnce(path, info, mode, history, now_history, sort_mode, UpOrDown);
					clrmous(MouseX, MouseY);
					cleardevice();
					load_all(path, info, root, srch_tar, mode);
					delay(200);
				}
			}

			else if (mouse_press(120, 70, 640, 480) == 1) // || mouse_press(120, 70, 640, 480) == 4)//如果点击文件（夹）区域
			{
				result = change_dir(info, MouseX, MouseY);
				if (result == 2) //|| change_dir(info, MouseX, MouseY) == 0)//进入或无效点击
				{
					clrmous(MouseX, MouseY);
					cleardevice();
					spinOnce(path, info, mode, history, now_history, sort_mode, UpOrDown);
					read_dir(path, info);
					load_all(path, info, root, srch_tar, mode);
				}
				else if (result == 1) // 选中
				{
					spinOnce(path, info, mode, history, now_history, sort_mode, UpOrDown);
					cleardevice();
					load_all(path, info, root, srch_tar, mode);
				}
				else if (result == 0) // 点击空白
				{
					cleardevice();
					for (int j = 0; j < INFO_LENGTH; j++)
						set_bit(&(info + j)->flag, 7, 0); // 这里暂且这样写，等你写多选优化
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

					// getcwd(path, sizeof(path));
					spinOnce(path, info, mode, history, now_history, sort_mode, UpOrDown);
					read_dir(path, info);
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

			// 结束
			else if (mouse_press(620, 0, 640, 20) == 2)
				end();

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
			if (mouse_press_out(540, 10, 620, 30) == 1)
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
			if (mouse_press(120, 70, 640, 480) == 3)
			{
				int tmp_x = MouseX, tmp_y = MouseY; // 记录右击时的鼠标位置

				delay(200);
				result = 0;

				result = drop_down_menu(MouseX, MouseY, 75, 25, 4, 12, RB_menu_p, WHITE, BLACK, 0, 1);

				if (result == 0) // 排序方式
				{
					int result_0 = -1;
					result_0 = drop_down_menu(tmp_x + 75, tmp_y, 75, 25, 6, 12, sort_menu_p, WHITE, BLACK, 0, 0);
					if (result_0 >= 0 && result_0 <= 3)
						sort_mode = result_0;
					else if (result_0 == 4)
						UpOrDown = 1;
					else if (result_0 == 5)
						UpOrDown = -1;
					if (result_0 != -1)
					{
						spinOnce(path, info, mode, history, now_history, sort_mode, UpOrDown);
						clrmous(MouseX, MouseY);
						cleardevice();
						load_all(path, info, root, srch_tar, mode);
						delay(200);
					}
					else
					{
						clrmous(MouseX, MouseY);
						cleardevice();
						load_all(path, info, root, srch_tar, mode);
					}
				}
				else if (result == 1) // 撤销
				{
				}
				else if (result == 2) // 新建
				{
				}
				else if (result == 3) // 属性
				{
					if (get_file_num(tmp_x, tmp_y, info) != -1)
						set_bit(&(info + get_file_num(tmp_x, tmp_y, info) - 1)->flag, 7, 1);

					if (is_selected(info) != 0)
						property(NULL, info + is_selected(info) - 1);
					else
						property(path, NULL);
					cleardevice();
					load_all(path, info, root, srch_tar, mode);
				}
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