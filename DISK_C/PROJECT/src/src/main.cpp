// #define TEST

#ifndef TEST
#include "include.h"

// extern void *buffer; // 缓存

struct menu
{
	char *option;
	struct menu *next;
	struct menu *son_menu_head;
};

void spinOnce(char path[1024], struct file_info *info, int mode, char history[HISTORY_LENGTH][1024], int now_history, int sort_mode, int UpOrDown, char preference[3][1024]) // 更新状态检测函数
{
	newmouse(&MouseX, &MouseY, &press);
	if (mode == 0)
	{
		getcwd(path, sizeof(path) * 1024);
		// read_dir(path, info);
	}
	sort(info, sort_mode, UpOrDown);

	if (now_history == 0 && strcmp(path, history[now_history]) != 0)
	{
		new_history(history, path);
		get_preference(history, preference);
	}
}

int main()
{
	int gd = DETECT, gm; // 图形驱动和图形模式

	struct My_filenode *root;				  // 目录树的根
	char path[1024];						  // 当前路径
	char history[HISTORY_LENGTH][1024] = {0}; // 操作历史
	int now_history = 0;					  // 当前在路径在history中的位置，服务撤销操作
	struct file_info info[10];				  // 存放文件信息
	int page = 0;							  // 页码，从0开始

	char preference[3][1024] = {0};

	int i; // 循环变量

	char src_path[1024]; // copy文件源路径
	int sort_mode = 0;	 // 排序方法
	int UpOrDown = 1;	 // 升序/降序

	char mode = 0;			 // 主视窗显示模式，0为一般模式，1为搜索模式
	char mode_shift = _0to0; // 模式切换
	char srch_tar[16] = {0}; // 搜索目标

	int choose_mode = 0; // 点击选择模式

	int result; // 用来存放函数返回值，防止多次调用

	void *img_buffer; // 图片缓存

	root = (struct My_filenode *)malloc(sizeof(struct My_filenode));

	initgraph(&gd, &gm, "C:\\BORLANDC\\BGI"); // 初始化图形模式
	power_on();
	welcome();

	tree_make(root, 0); // 目录树开始构建
	// printf("Ready to start!\n");

	// buffer = NULL;

	mouseinit();

	if (!login()) // 登陆失败
		return 0;
	else // 登陆成功
	{
		MouseS = 0;
		clrmous(MouseX, MouseY);
		cleardevice();

		load_init(path, info, history); // 界面初始化
		read_dir(path, info, &page);

		spinOnce(path, info, mode, history, now_history, sort_mode, UpOrDown, preference); // 刷新info
		load_all(path, info, root, srch_tar, mode, preference, page);					   // 显示

		// 排序菜单初始化
		char sort_menu[6][16] = {"名称", "修改时间", "类型", "大小", "递增", "递减"};
		char **sort_menu_p = (char **)malloc(6 * sizeof(char *));
		for (i = 0; i < 6; i++)
		{
			sort_menu_p[i] = (char *)malloc(16 * sizeof(char));
			strcpy(sort_menu_p[i], sort_menu[i]);
		}

		// 右键菜单初始化
		char RB_menu[4][16] = {
			"排序方式",
			//"撤销",
			"新建",
			"属性"};
		char **RB_menu_p = (char **)malloc(4 * sizeof(char *));
		for (i = 0; i < 4; i++)
		{
			RB_menu_p[i] = (char *)malloc(16 * sizeof(char));
			strcpy(RB_menu_p[i], RB_menu[i]);
		}

		char new_menu[13][8] = {
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
		char **new_menu_p = (char **)malloc(13 * sizeof(char *));
		for (i = 0; i < 13; i++)
		{
			new_menu_p[i] = (char *)malloc(16 * sizeof(char));
			strcpy(new_menu_p[i], new_menu[i]);
		}

		while (1)
		{
			// spinOnce(path, info, mode, history, now_history, sort_mode, UpOrDown);
			newmouse(&MouseX, &MouseY, &press);
			highlight_detector(info, root);
			// printf("%d", page);

			if (mouse_press(5, 5, 25, 25) == 1) //|| mouse_press(10, 10, 30, 30) == 4)//如果点击<-撤销目录操作
			{
				result = undo_dir(history, &now_history);
				spinOnce(path, info, mode, history, now_history, sort_mode, UpOrDown, preference);
				if (result == 1)
					read_dir(path, info, &page);
				spinOnce(path, info, mode, history, now_history, sort_mode, UpOrDown, preference);
				clrmous(MouseX, MouseY);
				cleardevice();
				load_all(path, info, root, srch_tar, mode, preference, page);
			}
			else if (mouse_press(25, 5, 45, 25) == 1) // || mouse_press(30, 10, 50, 30) == 4)//如果点击->反撤销目录操作
			{
				result = anti_undo_dir(history, &now_history);
				spinOnce(path, info, mode, history, now_history, sort_mode, UpOrDown, preference);
				if (result == 1)
					read_dir(path, info, &page);
				spinOnce(path, info, mode, history, now_history, sort_mode, UpOrDown, preference);
				clrmous(MouseX, MouseY);
				cleardevice();
				load_all(path, info, root, srch_tar, mode, preference, page);
			}
			else if (mouse_press(45, 5, 65, 25) == 1) //|| mouse_press(50, 10, 70, 30) == 4)//如果点击返回上一级目录
			{
				result = back(path, history, &now_history);
				spinOnce(path, info, mode, history, now_history, sort_mode, UpOrDown, preference);
				if (result == 1)
					read_dir(path, info, &page);
				spinOnce(path, info, mode, history, now_history, sort_mode, UpOrDown, preference);
				clrmous(MouseX, MouseY);
				cleardevice();
				load_all(path, info, root, srch_tar, mode, preference, page);
			}
			else if (mouse_press(65, 5, 85, 25) == 1) //|| mouse_press(70, 10, 90, 30) == 4)//如果点击刷新
			{
				spinOnce(path, info, mode, history, now_history, sort_mode, UpOrDown, preference); // 更新path
				read_dir(path, info, &page);
				spinOnce(path, info, mode, history, now_history, sort_mode, UpOrDown, preference); // 排序
				clrmous(MouseX, MouseY);
				cleardevice();
				if (mode == 0)
					strcpy(srch_tar, "");
				load_all(path, info, root, srch_tar, mode, preference, page);
			}
			else if (mouse_press(90, 10, 500, 30) == 1) // 点击键入路径
			{
				keyin_dir(path, 40);
				page = 0;
				read_dir(path, info, &page);
				spinOnce(path, info, mode, history, now_history, sort_mode, UpOrDown, preference);
				clrmous(MouseX, MouseY);
				cleardevice();
				if (mode == 0)
					strcpy(srch_tar, "");
				load_all(path, info, root, srch_tar, mode, preference, page);
			}
			else if (detect_m(0, 37, 365, 62) == 1) //|| mouse_press(10, 40, 500, 65) == 4)//如果点击上方功能区域
			{

				if (func(info, src_path, &sort_mode, &UpOrDown, sort_menu_p) != 0)
				{
					read_dir(path, info, &page);
					spinOnce(path, info, mode, history, now_history, sort_mode, UpOrDown, preference);
					clrmous(MouseX, MouseY);
					cleardevice();
					load_all(path, info, root, srch_tar, mode, preference, page);
				}
			}

			else if (mouse_press(120, 70, 640, 440) == 1) // || mouse_press(120, 70, 640, 480) == 4)//如果点击文件（夹）区域
			{
				result = change_dir(info, MouseX, MouseY);
				if (result == 2) //|| change_dir(info, MouseX, MouseY) == 0)//进入或无效点击
				{
					page = 0;
					clrmous(MouseX, MouseY);
					cleardevice();
					spinOnce(path, info, mode, history, now_history, sort_mode, UpOrDown, preference);
					read_dir(path, info, &page);
					spinOnce(path, info, mode, history, now_history, sort_mode, UpOrDown, preference);
					load_all(path, info, root, srch_tar, mode, preference, page);
				}
				else if (result == 1) // 选中
				{
					clrmous(MouseX, MouseY);
					spinOnce(path, info, mode, history, now_history, sort_mode, UpOrDown, preference);
					cleardevice();
					load_all(path, info, root, srch_tar, mode, preference, page);
				}
				else if (result == 0) // 点击空白
				{
					cleardevice();
					for (int j = 0; j < INFO_LENGTH; j++)
						set_bit(&(info + j)->flag, 7, 0); // 这里暂且这样写，等你写多选优化
					load_all(path, info, root, srch_tar, mode, preference, page);
				}
			}
			// 翻页
			else if (mouse_press(550, 440, 570, 460) == 1)
			{
				if (page > 0)
					page -= 1;
				clrmous(MouseX, MouseY);
				cleardevice();
				read_dir(path, info, &page);
				spinOnce(path, info, mode, history, now_history, sort_mode, UpOrDown, preference);
				load_all(path, info, root, srch_tar, mode, preference, page);
			}
			else if (mouse_press(580, 440, 600, 460) == 1)
			{
				page += 1;
				clrmous(MouseX, MouseY);
				cleardevice();
				read_dir(path, info, &page);
				spinOnce(path, info, mode, history, now_history, sort_mode, UpOrDown, preference);
				load_all(path, info, root, srch_tar, mode, preference, page);
			}

			// 左栏目录树
			else if (mouse_press(10, 70, 100, 400) == 1)
			{
				if (chdir(get_file_path_left(root, MouseX, MouseY)) != -1)
				{
					mode_shift = _1to0;
					mode = 0;

					page = 0;
					spinOnce(path, info, mode, history, now_history, sort_mode, UpOrDown, preference);
					read_dir(path, info, &page);
					spinOnce(path, info, mode, history, now_history, sort_mode, UpOrDown, preference);
					clrmous(MouseX, MouseY);
					cleardevice();
					load_all(path, info, root, srch_tar, mode, preference, page);
					// clearRectangle(10, 10, 630, 30, BLACK);
					// load_top(path, srch_tar, mode);
					// clearRectangle(120, 70, 640, 480, BLACK);
					// load_main(info, mode);
				}

				if (unfold(root, MouseX, MouseY) != 0)
				{
					clrmous(MouseX, MouseY);
					clearRectangle(10, 70, 100, 400, BLACK);
					load_left(root, preference);
				}
			}
			else if (mouse_press(10, 430, 80, 460) == 1) // 点击最近打开
			{
				for (i = 0; i < 3; i++)
				{
					if (detect_m(10, 430 + i * 10, 80, 440 + i * 10) == 1 && strcmp(preference[i], "\0") != 0)
					{
						page = 0;
						chdir(preference[i]);
						spinOnce(path, info, mode, history, now_history, sort_mode, UpOrDown, preference);
						read_dir(path, info, &page);
						spinOnce(path, info, mode, history, now_history, sort_mode, UpOrDown, preference);
						clrmous(MouseX, MouseY);
						cleardevice();
						load_all(path, info, root, srch_tar, mode, preference, page);
					}
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

				// result = drop_down_menu(MouseX, MouseY, 75, 25, 4, 12, RB_menu_p, WHITE, DARKGRAY, 0, 1);
				result = drop_down_menu(MouseX, MouseY, 75, 25, 3, 12, RB_menu_p, WHITE, DARKGRAY, 0, 1);

				if (result == 0) // 排序方式
				{
					int result_0 = -1;
					result_0 = drop_down_menu(tmp_x + 75, tmp_y, 75, 25, 6, 12, sort_menu_p, WHITE, DARKGRAY, 0, 0);
					if (result_0 >= 0 && result_0 <= 3)
						sort_mode = result_0;
					else if (result_0 == 4)
						UpOrDown = 1;
					else if (result_0 == 5)
						UpOrDown = -1;
					if (result_0 != -1)
					{
						spinOnce(path, info, mode, history, now_history, sort_mode, UpOrDown, preference);
						clrmous(MouseX, MouseY);
						cleardevice();
						load_all(path, info, root, srch_tar, mode, preference, page);
						delay(200);
					}
					else
					{
						clrmous(MouseX, MouseY);
						cleardevice();
						load_all(path, info, root, srch_tar, mode, preference, page);
					}
				}
				// else if (result == 1) // 撤销
				// {
				// }
				else if (result == 1) // 新建
				{
					build(info, tmp_x + 75, tmp_y);
					clrmous(MouseX, MouseY);
					cleardevice();
					read_dir(path, info, &page);
					spinOnce(path, info, mode, history, now_history, sort_mode, UpOrDown, preference);
					load_all(path, info, root, srch_tar, mode, preference, page);
				}
				else if (result == 2) // 属性
				{
					if (get_file_num(tmp_x, tmp_y, info) != -1)
						set_bit(&(info + get_file_num(tmp_x, tmp_y, info) - 1)->flag, 7, 1);
					if (is_selected(info) != 0)
						property(NULL, info + is_selected(info) - 1);
					else
						property(path, NULL);
					cleardevice();
					load_all(path, info, root, srch_tar, mode, preference, page);
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
				blbl(542, 12, srch_tar, 2, WHITE, BLACK); // 输入光标闪烁

				result = srch_input(srch_tar, info, img_buffer);
				if (result == 1)
				{
					load_top(path, srch_tar, mode);
				}
				else if (result == 2)
				{
					loading_ok(img_buffer);
					// strcpy(srch_tar, "");
					mode_shift = _0to1;
					srch_output(path, info, root, srch_tar);
					clearRectangle(1, 430, 240, 470, BLACK);
					load_main(info, 1, 0);
				}
			}
		}
	}

	closegraph();
	return 0;
}

#endif