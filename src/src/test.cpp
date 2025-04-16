//#define TEST
#ifdef TEST
#include "include.h"
//   extern time_t press_time[10];

// 测试鼠标双击检测

// int main()
//{
//	char chart_left[10][10] = { 0 };//
//	char chart_right[10][10] = { 0 };
//	int i;
//	int flag = 0;
//	int gd = DETECT, gm;  // 图形驱动和图形模式
//	initgraph(&gd, &gm, "C:\\BORLANDC\\BGI");// 初始化图形模式
//	mouseinit();
//
//	setbkcolor(BLUE);
//	setcolor(YELLOW); // 设置文本颜色为黄色
//	settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
//
//	puthz(308, 200, "用户", 24, 10, WHITE);
//
//	rectangle(280, 220, 360, 260);
//	while (1)
//	{
//		newmouse(&MouseX, &MouseY, &press);
//		itoa(mouse_press(280, 220, 360, 260), chart_right[0], 10);//0号位
//		if (strcmp(chart_right[0], "4") == 0 && flag == 0)
//		{
//			setbkcolor(YELLOW);
//			flag = 1;
//		}
//		else if (strcmp(chart_right[0], "4") == 0 && flag == 1)
//		{
//			setbkcolor(BLUE);
//			flag = 0;
//		}
//
//		if (strcmp(chart_right[0], "0") != 0 && strcmp(chart_right[0], "2") != 0)
//		{
//			cleardevice();
//			puthz(308, 200, "用户", 24, 10, WHITE);
//			rectangle(280, 220, 360, 260);
//
//			/*for (i = 1; i < 10; i++)
//			{
//				strcpy(chart[10 - i], chart[9 - i]);
//			}
//			ltoa(clock(), chart[0], 10);*/
//				for (i = 0; i < 10; i++)
//					ltoa(press_time[i], chart_left[i], 10);
//			if (strcmp(chart_right[0], chart_right[1]) != 0)
//			{
//				for (i = 1; i < 10; i++)
//				{
//					strcpy(chart_right[10 - i], chart_right[9 - i]);
//				}
//			}
//			for (i = 0; i < 10; i++)
//			{
//				outtextxy(10, i * 48, chart_left[i]);
//				outtextxy(540, i * 48, chart_right[i]);
//			}
//
//		}
//
//	}
//	return 1;
//
// }

// int main()
// {
// 	char chart_left[10][10] = {0}; //
// 	char chart_right[10][10] = {0};
// 	int i;
// 	int flag = 0;
// 	int gd = DETECT, gm;					  // 图形驱动和图形模式
// 	initgraph(&gd, &gm, "C:\\BORLANDC\\BGI"); // 初始化图形模式
// 	mouseinit();
// 	setbkcolor(BLUE);
// 	setcolor(RED); // 设置文本颜色为黄色
// 	settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
// 	puthz(308, 200, "用户", 24, 10, WHITE);
// 	rectangle(280, 220, 360, 260);
// 	while (1)
// 	{
// 		newmouse(&MouseX, &MouseY, &press);
// 		if (mouse_press(280, 220, 360, 260) == 4 && flag == 0)
// 		{
// 			setbkcolor(YELLOW);
// 			flag = 1;
// 		}
// 		else if (mouse_press(280, 220, 360, 260) == 4 && flag == 1)
// 		{
// 			setbkcolor(BLUE);
// 			flag = 0;
// 		}
// 	}
// 	return 1;
// }

// int main()
//{
//	int last_press = 0;
//
//	char chart_left[10][10] = { 0 };//
//	char chart_right[10][10] = { 0 };
//	int i;
//	int flag = 0;
//	int gd = DETECT, gm;  // 图形驱动和图形模式
//	initgraph(&gd, &gm, "C:\\BORLANDC\\BGI");// 初始化图形模式
//	mouseinit();
//
//	setbkcolor(BLUE);
//	setcolor(RED); // 设置文本颜色为黄色
//	settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
//
//	puthz(308, 200, "用户", 24, 10, WHITE);
//
//	rectangle(280, 220, 360, 260);
//	while (1)
//	{
//		last_press = press;
//		newmouse(&MouseX, &MouseY, &press);
//		if (last_press != press)
//		{
//			outtextxy(1, i * 10, "2");
//			i++;
//			//break;
//		}
//		/*if (last_press != press && flag == 0)
//		{
//			outtextxy(1, i * 10, "1");
//			i++;
//			setbkcolor(YELLOW);
//			flag = 1;
//		}
//		else if (last_press != press && flag == 1)
//		{
//			outtextxy(1, i * 10, "2");
//			i++;
//			setbkcolor(BLUE);
//			flag = 0;
//		}*/
//
//	}
//	return 1;
// }

// 测试点击
// extern last_press_time;
// extern last_click_time;
// void main()
//{
//	int last_press = 0;
//	char box[10] = { 0 };
//
//	char chart_left[10][10] = { 0 };//
//	char chart_right[10][10] = { 0 };
//	int i;
//	int flag = 0;
//	int gd = DETECT, gm;  // 图形驱动和图形模式
//	initgraph(&gd, &gm, "C:\\BORLANDC\\BGI");// 初始化图形模式
//	mouseinit();
//
//	setbkcolor(BLUE);
//	setcolor(RED); // 设置文本颜色为黄色
//	settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
//
//	node:
//	puthz(308, 200, "用户", 24, 10, WHITE);
//
//	rectangle(280, 220, 360, 260);
//	rectangle(380, 320, 460, 360);
//
//	while (1)
//	{
//		newmouse(&MouseX, &MouseY, &press);
//		last_press = mouse_press(280, 220, 360, 260);
//		if (last_press != 3 && last_press != 2 && last_press != 0)
//		{
//			outtextxy(30, 30, ltoa((long)last_click_time, box, 10));
//			outtextxy(10, 10, itoa(last_press, box, 10));
//		}
//		else if(last_press==3)
//		{
//			cleardevice();
//			goto node;
//		}
//		if (mouse_press(380, 320, 460, 360) == 1)
//		{
//			cleardevice();
//			goto node;
//		}
//		//if (mouse_press(280, 220, 360, 260) == 1)
//		//	flag = 1;
//		//if (mouse_press(280, 220, 360, 260) == 2 && flag == 1)
//		//	break;
//	}
// }

// 测试时间
// int main() {
//     // 获取当前时间
//     time_t rawtime;
//     struct tm* timeinfo;
//     char buffer[80];
//     time(&rawtime);
//     timeinfo = localtime(&rawtime);  // 将时间转换为本地时间
//
//     // 打印格式化后的时间
//     printf("当前时间: %s", asctime(timeinfo));  // 使用 asctime 函数将时间转换为字符串
//
//     // 或者使用 strftime 函数自定义输出格式
//
//     strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo);
//     printf("当前时间: %s\n", buffer);
//
//     return 0;
// }

// void main()
//{
//	char str[13];
//	memset(str, 0, sizeof(char[13]));
//	printf("%s,%d", str, strlen(str));
//	printf("\n");
//	if (str == 0)
//		printf("str==0");
//	else
//		printf("%d", (int)str);
//	printf("\n");
//	if (strcmp(str, "") == 0)
//		printf("strcmp(str,\"\")==0");
//	printf("\n");
// }

// #include <graphics.h>
// #include <dos.h>
// #include <conio.h>
// #include <string.h>
// #include <stdlib.h>
// #include <time.h>
// #include <dirent.h>
// #include <direct.h>
// #include "include.h"
//
// extern char path[1024];//当前路径
// extern char history[HISTORY_LENGTH][1024];//操作历史
// extern int now_history;//当前在路径在history中的位置，服务撤销操作
// extern void* buffer;//缓存
// extern struct dir_tree tree;//目录树，用于加载左栏，以及通过左栏快速定位
//
////void spinOnce(DIR* dir, struct dirent* entry, struct file_info* info)//更新状态检测函数
////{
////	newmouse(&MouseX, &MouseY, &press);
////	getcwd(path, sizeof(path));
////	dir = opendir(path);
////	read_dir(dir, entry, info);
////	closedir(dir);
////	if (now_history == 0 && strcmp(path, history[now_history]) != 0)
////		new_history();
////}

// int main()
//{
//
//	struct file_info info[10];//存放文件信息
//	int gd = DETECT, gm;  // 图形驱动和图形模式
//	int result;//用来存放函数返回值，防止多次调用
//	initgraph(&gd, &gm, "C:\\BORLANDC\\BGI");// 初始化图形模式
//	mouseinit();
//
//	//if (!login())	//登陆失败
//	//	return;
//	//else	//登陆成功
//	//{
//		MouseS = 0;
//		cleardevice();
//		clrmous(MouseX, MouseY);
//		//buffer = NULL;
//		tree_make(&tree);//目录树开始构建
//		load_init(info);//界面初始化
//		//spinOnce(dir, entry, info);//刷新info
//		load_all(info);//显示
//		setcolor(YELLOW);
//		outtextxy(100, 0, tree.name);
//		outtextxy(200, 0, tree.path);
//		if (tree.branch[0])
//		{
//			outtextxy(100, 100, tree.branch[0]->name);
//			outtextxy(200, 100, tree.branch[0]->path);
//		}
//		if (tree.branch[1])
//		{
//			outtextxy(100, 200, tree.branch[1]->name);
//			outtextxy(200, 200, tree.branch[1]->path);
//		}
//		if (tree.branch[2])
//		{
//			outtextxy(100, 300, tree.branch[2]->name);
//			outtextxy(200, 300, tree.branch[2]->path);
//		}
//	//	while (1)
//	//	{
//	//		spinOnce(dir, entry, info);
//
//	//		if (mouse_press(10, 10, 30, 30) == 1)//|| mouse_press(10, 10, 30, 30) == 4)//如果点击<-撤销目录操作
//	//		{
//	//			undo_dir();
//	//			spinOnce(dir, entry, info);
//	//			clrmous(MouseX, MouseY);
//	//			cleardevice();
//	//			load_all(info);
//	//		}
//	//		else if (mouse_press(30, 10, 50, 30) == 1)// || mouse_press(30, 10, 50, 30) == 4)//如果点击->反撤销目录操作
//	//		{
//	//			anti_undo_dir();
//	//			spinOnce(dir, entry, info);
//	//			clrmous(MouseX, MouseY);
//	//			cleardevice();
//	//			load_all(info);
//	//		}
//	//		else if (mouse_press(50, 10, 70, 30) == 1)//|| mouse_press(50, 10, 70, 30) == 4)//如果点击返回上一级目录
//	//		{
//	//			back();
//	//			spinOnce(dir, entry, info);
//	//			clrmous(MouseX, MouseY);
//	//			cleardevice();
//	//			load_all(info);
//	//		}
//	//		else if (mouse_press(70, 10, 90, 30) == 1)//|| mouse_press(70, 10, 90, 30) == 4)//如果点击刷新
//	//		{
//	//			spinOnce(dir, entry, info);
//	//			clrmous(MouseX, MouseY);
//	//			cleardevice();
//	//			load_all(info);
//	//		}
//
//	//		else if (mouse_press(120, 70, 640, 480) == 1)// || mouse_press(120, 70, 640, 480) == 4)//如果点击文件（夹）区域
//	//		{
//	//			result = change_dir(info, MouseX, MouseY);
//	//			if (result == 2)//|| change_dir(info, MouseX, MouseY) == 0)//进入或无效点击
//	//			{
//	//				clrmous(MouseX, MouseY);
//	//				cleardevice();
//	//				spinOnce(dir, entry, info);
//	//				delay(200);
//	//				load_all(info);
//	//			}
//	//			else if (result == 1)//选中
//	//			{
//	//				clrmous(MouseX, MouseY);
//	//				cleardevice();
//	//				spinOnce(dir, entry, info);
//	//				delay(200);
//	//				load_all(info);
//	//			}
//	//			else if (result == 0)
//	//			{
//	//				clrmous(MouseX, MouseY);
//	//				cleardevice();
//	//				delay(200);
//	//				load_all(info);
//	//			}
//	//		}
//
//	//	}
//	//}
//				 while(1);
//	closegraph();
//	return 0;
// }

// 目录树测试+搜索测试
// struct My_filenode *root;
// int main()
// {
// 	enum // 模式切换,0为一般，1为搜索
// 	{
// 		_0to0 = 1,
// 		_0to1 = 2,
// 		_1to0 = 3,
// 		_1to1 = 4
// 	};
// 	struct file_info info[10]; // 存放文件信息
// 	int gd = DETECT, gm; // 图形驱动和图形模式
// 	int result;			 // 用来存放函数返回值，防止多次调用
// 	int mode = _0to0;
// 	char srch_tar[16] = ""; // 搜索目标
// 	char box[10];
// 	root = (struct My_filenode *)malloc(sizeof(struct My_filenode));
// 	tree_make(root, 0);
// 	printf("Finished!\n");
// 	while (!kbhit()) // 循环，直到按下键盘键
// 		;
// 	clear_keyboard_buffer();
// 	initgraph(&gd, &gm, "C:\\BORLANDC\\BGI"); // 初始化图形模式
// 	mouseinit();
// 	setbkcolor(BLACK);
// 	setcolor(WHITE);
// 	settextstyle(DEFAULT_FONT, HORIZ_DIR, 10);
// 	rectangle(270, 230, 370, 250);
// 	puthz(270, 230, "搜索", 16, 2, WHITE);
// 	rectangle(10, 10, 630, 470);
// 	while (1)
// 	{
// 		// printf("%d", mode);
// 		newmouse(&MouseX, &MouseY, &press);
//		// 右键刷新
// 		if (mouse_press_out(540, 10, 630, 30) == 2)
// 		{
// 			cleardevice();
// 			outtextxy(10, 10, itoa(mode, box, 10));
// 			rectangle(540, 10, 630, 30);
// 			puthz(542, 12, "搜索", 16, 2, WHITE);
// 		}
// 		// 搜索
// 		// if (mouse_press(540, 10, 630, 30) == 1)
// 		if (MouseX > 540 && MouseX < 630 && MouseY > 10 && MouseY < 30 && press == 1) // 哪个效果好用哪个
// 		{
// 			if (mode == _0to0 || mode == _1to0)
// 				mode = _0to1;
// 			else // if (mode == _0to1 || mode == _1to1)
// 				mode = _1to1;
// 		}
// 		if (mouse_press_out(540, 10, 630, 30) == 1)
// 		{
// 			if (mode == _0to1 || mode == _1to1)
// 				mode = _1to0;
// 			else if (mode == _0to0 || mode == _1to0)
// 				mode = _0to0;
// 		}
// 		if (mode == _0to1) // 从一般模式到搜索模式
// 		{
// 			clrmous(MouseX, MouseY);
// 			clear_keyboard_buffer();
// 			//  newmouse(&MouseX, &MouseY, &press);
// 			setfillstyle(SOLID_FILL, BLACK);
// 			bar(540, 10, 630, 30);
// 			rectangle(540, 10, 630, 30);
// 			outtextxy(542, 12, srch_tar);
// 			mode = _1to1;
// 		}
// 		else if (mode == _1to0 && strcmp(srch_tar, "") == 0) // 从搜索模式到一般模式，并且搜索目标为空
// 		{
// 			clrmous(MouseX, MouseY);
// 			setfillstyle(SOLID_FILL, BLACK);
// 			bar(540, 10, 630, 30);
// 			rectangle(540, 10, 630, 30);
// 			puthz(542, 12, "搜索", 16, 2, WHITE);
// 			mode = _0to0;
// 		}
// 		else if ((mode == _0to0 || mode == _1to0) && strcmp(srch_tar, "") != 0) // 处于一般模式时，搜索目标不为空
// 		{
// 			setcolor(WHITE);
// 			settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
// 			outtextxy(542, 12, srch_tar);
// 		}
// 		if (mode == _1to1 || mode == _0to1) // 如果处于搜索模式
// 		{
// 			result = srch_input(srch_tar, info);
// 			if (result == 1)
// 			{
// 				cleardevice();
// 				setcolor(WHITE);
// 				settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
// 				rectangle(540, 10, 630, 30);
// 				outtextxy(542, 12, srch_tar);
// 			}
// 			else if (result == 2)
// 				srch_output(info);
// 		}
// 	}
// 	return 0;
// }

// 测试按位操作
//
// int main()
// {
// 	unsigned char num = 0b10101100; // 示例初始值
// 	printf("Original value: %02X\n", num);
// 	printBinary(num);
// 	set_bit(&num, 3, 1); // 将第3位设置为1
// 	printf("After setting bit 3 to 1: %02X\n", num);
// 	printBinary(num);
// 	set_bit(&num, 3, 0); // 将第5位设置为0
// 	printf("After setting bit 3 to 0: %02X\n", num);
// 	printBinary(num);
// 	return 0;
// }

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

extern void *buffer;		// 缓存
time_t last_click_time = 0; // 记录上次点击时间
time_t current_click_time = 0;
time_t elapsed_ticks;
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

	tree_make(root, 0); // 目录树开始构建

	buffer = NULL;

	mouseinit();

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
	int counter = 0;
	while (1)
	{
		// spinOnce(path, info, mode, history, now_history, sort_mode, UpOrDown);
		newmouse(&MouseX, &MouseY, &press);

		if (mouse_press(70, 10, 90, 30) == 1)
		{

			current_click_time = clock();
			elapsed_ticks = current_click_time - last_click_time;
			last_click_time = current_click_time;
			counter++;
		}
		// if (mouse_press(70, 10, 90, 30) == 1) //|| mouse_press(70, 10, 90, 30) == 4)//如果点击刷新
		if (elapsed_ticks > 1 && elapsed_ticks < 12 && current_click_time != 0 && counter >= 2)
		{
			elapsed_ticks = 0;
			counter = 0;

			spinOnce(path, info, mode, history, now_history, sort_mode, UpOrDown);
			read_dir(path, info);
			clrmous(MouseX, MouseY);
			cleardevice();
			if (mode == 0)
				strcpy(srch_tar, "");
			load_all(path, info, root, srch_tar, mode);
		}
		else if (detect_mouse(10, 40, 500, 65) == 4) //|| mouse_press(10, 40, 500, 65) == 4)//如果点击上方功能区域
		{

			func();
			spinOnce(path, info, mode, history, now_history, sort_mode, UpOrDown);
			clrmous(MouseX, MouseY);
			cleardevice();
			load_all(path, info, root, srch_tar, mode);
		}

		// 结束
		else if (mouse_press(620, 0, 640, 20) == 2)
			end();
	}
	closegraph();
	return 0;
}
#endif