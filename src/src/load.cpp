/********加载页面********/

// 把界面划分为
// top顶栏：调整级别，当前路径
// head上栏：各种功能按钮
// left左栏：文件结构
// main主栏：操作板

// #include <graphics.h>
// #include <conio.h>
// #include <dos.h>
// #include <stdio.h>
// #include <string.h>
// #include <time.h>
// #include <dirent.h>
// #include <direct.h>
// #include <sys/stat.h> // 文件状态
#include <IMAGE.h>
#include "include.h"

// extern char path[1024]; // 当前路径
// extern char history[HISTORY_LENGTH][1024];
extern char chosen_name[13]; // 被选中的文件名
// extern struct dir_tree tree;	 // 目录树，用于加载左栏，以及通过左栏快速定位
// extern struct My_filenode *root; //

void load_init(char path[1024], struct file_info *info, char history[HISTORY_LENGTH][1024]) // 界面初始化
{
	setbkcolor(BLACK);
	chdir("C:\\PROJECT");
	if (getcwd(path, sizeof(path) * 1024) == NULL) // 获取当前路径
	{
		perror("Can't get current dir");
		return;
	}
	strcpy(history[0], path); // 路径操作历史开始记录
							  // 加载界面
							  // load_all(info);
}

void load_all(char path[1024], struct file_info *info, struct My_filenode *root, char *target, int mode) // 加载界面
{
	load_top(path, target, mode);
	line(1, 35, 640, 35);
	load_head(mode);
	line(1, 65, 640, 65);
	load_left(root);
	floodfill(121, 71, BLACK);
	line(105, 65, 105, 480);
	load_main(info, mode);
}

void load_top(char path[1024], char *target, int mode) //(10,10)(630,30)
{
	setcolor(WHITE);
	settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
	// 操作
	puthz(10, 10, "左", 16, 0, WHITE); // 前期这些符号就不去画了
	puthz(30, 10, "右", 16, 0, WHITE);
	puthz(50, 10, "上", 16, 0, WHITE);
	outtextxy(70, 10, "@");

	// 路径
	settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
	rectangle(90, 10, 500, 30);
	outtextxy(92, 15, path);

	// 搜索
	// rectangle(540, 10, 620, 30);
	// puthz(542, 12, "搜索", 16, 2, WHITE);
	if (mode == 1) // 搜索模式
	{
		setfillstyle(SOLID_FILL, BLACK);
		bar(540, 10, 620, 30);
		rectangle(540, 10, 620, 30);
		outtextxy(542, 12, target);
	}
	else if (mode == 0 && strcmp(target, "") == 0) // 一般模式，并且搜索目标为空
	{
		clrmous(MouseX, MouseY);
		setfillstyle(SOLID_FILL, BLACK);
		bar(540, 10, 620, 30);
		rectangle(540, 10, 620, 30);
		puthz(542, 12, "搜索", 16, 2, WHITE);
	}
	else if (mode == 0 && strcmp(target, "") != 0) // 处于一般模式时，搜索目标不为空
	{
		setfillstyle(SOLID_FILL, BLACK);
		bar(540, 10, 620, 30);
		setcolor(WHITE);
		settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
		outtextxy(542, 12, target);
	}

	// 退出小叉叉
	line(620, 0, 640, 20);
	line(640, 0, 620, 20);
}

// void load_head() //(10,40)(630,60)
// {
// 	setcolor(WHITE);
// 	puthz(12, 42, "新建", 16, 2, WHITE);
// 	puthz(55, 42, "剪", 16, 2, WHITE);
// 	puthz(75, 42, "复", 16, 2, WHITE);
// 	puthz(95, 42, "粘", 16, 2, WHITE);
// 	puthz(115, 42, "共", 16, 2, WHITE);
// 	puthz(135, 42, "删", 16, 2, WHITE);
// 	puthz(155, 42, "排序", 16, 2, WHITE);
// 	puthz(195, 42, "查看", 16, 2, WHITE);
// 	puthz(235, 42, "…", 16, 2, WHITE);
// }

void load_head(int mode) //(10,40)(630,60)
{
	setcolor(WHITE);
	// 新建
	bmp_convert("C:\\PROJECT\\src\\Images\\BMP\\build.bmp", "C:\\PROJECT\\src\\Images\\DBM\\build.dbm");
	show_dbm(12, 42, "C:\\PROJECT\\src\\Images\\DBM\\build.dbm", 0);
	// 剪切
	bmp_convert("C:\\PROJECT\\src\\Images\\BMP\\cut.bmp", "C:\\PROJECT\\src\\Images\\DBM\\cut.dbm");
	show_dbm(65, 42, "C:\\PROJECT\\src\\Images\\DBM\\cut.dbm", 0);
	// 复制
	bmp_convert("C:\\PROJECT\\src\\Images\\BMP\\todo.bmp", "C:\\PROJECT\\src\\Images\\DBM\\todo.dbm");
	show_dbm(90, 42, "C:\\PROJECT\\src\\Images\\DBM\\todo.dbm", 0);
	// 粘贴
	bmp_convert("C:\\PROJECT\\src\\Images\\BMP\\paste.bmp", "C:\\PROJECT\\src\\Images\\DBM\\paste.dbm");
	show_dbm(115, 42, "C:\\PROJECT\\src\\Images\\DBM\\paste.dbm", 0);
	// 删除
	bmp_convert("C:\\PROJECT\\src\\Images\\BMP\\delete.bmp", "C:\\PROJECT\\src\\Images\\DBM\\delete.dbm");
	show_dbm(150, 42, "C:\\PROJECT\\src\\Images\\DBM\\delete.dbm", 0);
	// 排序
	bmp_convert("C:\\PROJECT\\src\\Images\\BMP\\sort.bmp", "C:\\PROJECT\\src\\Images\\DBM\\sort.dbm");
	show_dbm(180, 42, "C:\\PROJECT\\src\\Images\\DBM\\sort.dbm", 0);
	// 查看
	bmp_convert("C:\\PROJECT\\src\\Images\\BMP\\check.bmp", "C:\\PROJECT\\src\\Images\\DBM\\check.dbm");
	show_dbm(280, 42, "C:\\PROJECT\\src\\Images\\DBM\\check.dbm", 0);
	// 重命名
	bmp_convert("C:\\PROJECT\\src\\Images\\BMP\\rename.bmp", "C:\\PROJECT\\src\\Images\\DBM\\rename.dbm");
	show_dbm(400, 42, "C:\\PROJECT\\src\\Images\\DBM\\rename.dbm", 0);
}

void load_left(struct My_filenode *root) //(10,70)(100,470)
{
	// int i;			// 循环变量
	int layer = 0;	// 目录的层数，设c盘问第0层
	int pen_x = 10; // 画笔位置
	int pen_y = 70;
	struct My_filenode *p;
	setcolor(WHITE);
	settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
	// outtextxy(pen_x, pen_y, ">");
	// outtextxy(pen_x + 10, pen_y, root->name);
	if (get_bit(root->flag, 4) == 1 && root->son_list_head != NULL) // 如果目录展开
	{

		load_left_assist(root->son_list_head, layer, pen_x + 10, &pen_y);
	}
}
void load_left_assist(struct My_filenode *head, int layer, int pen_x, int *pen_y) //(加载左栏辅助函数)加载出传入地址的所有子目录和后面的同级目录
{

	*pen_y += 10;
	outtextxy(pen_x, *pen_y, ">");
	outtextxy(pen_x + 10, *pen_y, head->name);
	if (get_bit(head->flag, 4) == 1 && head->son_list_head != NULL && layer < 2) // 如果子目录可见
	{
		load_left_assist(head->son_list_head, layer + 1, pen_x + 10, pen_y);
	}

	if (head->next != NULL) // 加载后面的目录
	{
		load_left_assist(head->next, layer, pen_x, pen_y);
	}
}

void load_main(struct file_info *info, int mode) //(120,70)(640,480)
{
	int i; // 像素
	int j; // 文件序号
	int k; // 循环变量
	char *file_type_strings[] = {
		"THIS_PC",
		"C_DISK",
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
		"OTHER",
	};
	settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);

	puthz(120, 70, "名称", 16, 2, WHITE);
	line(320, 70, 320, 90);

	puthz(240, 70, "修改日期", 16, 2, WHITE);
	line(400, 70, 400, 90);

	puthz(400, 70, "类型", 16, 2, WHITE);
	line(540, 70, 540, 90);

	puthz(540, 70, "大小", 16, 2, WHITE);

	// 为了开发方便，开发阶段将格子画出来
	for (i = 90; i < 640; i += 20)
		line(120, i, 640, i);

	for (j = 0, i = 95; j < INFO_LENGTH && strcmp((info + j)->name, "") != 0; j++, i += 20)
	{
		setcolor(WHITE);
		settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
		outtextxy(120, i, (info + j)->name); // 名称

		outtextxy(240, i, (info + j)->time); // 修改日期

		// 类型
		unsigned char flag, flag_4;
		flag = (info + j)->flag;
		flag_4 = get_bit(flag, 0) * 1 + get_bit(flag, 1) * 2 + get_bit(flag, 2) * 2 * 2 + get_bit(flag, 3) * 2 * 2 * 2;
		for (k = 0; k < 16; k++)
		{ // 取前4位

			if (flag_4 == k) // 此电脑
				outtextxy(400, i, file_type_strings[k]);
		}
		outtextxy(540, i, (info + j)->size); // 大小

		// if (strcmp(chosen_name, (info + j)->name) == 0 && (info + j)->name != 0)
		if (get_bit((info + j)->flag, 7) == 1)
		{
			setcolor(YELLOW);
			rectangle(120, 90 + j * 20, 640, 90 + j * 20 + 20);
		}
	}
}

void clearRectangle(int x1, int y1, int x2, int y2, unsigned char color) // 清空指定矩形区域
{
	setfillstyle(SOLID_FILL, color);
	bar(x1, y1, x2, y2);
}

// 下拉菜单，原版来自杨征坷学长，此为中文版，点击选项后收起，点击外部收起，菜单增加了x方向的出画面判断（优化掉了一半代码）（改变了x,y的含义），取消record参数，增加son_menu参数
int drop_down_menu(int x, int y, int wide, int h, int n, int lettersize, char **msgs, int lightcolor, int darkcolor, int language, int son_menu)
{
	int i;					 // 循环变量
	int size;				 // 记录图像的大小
	void *drop_down_buffer;	 // 暂存被下拉菜单遮挡的图像
	int flag = n + 1;		 // 记录当前高亮的选项索引
	int place = 0;			 // 标记当前的状态
	int num[10] = {0};		 // 记录每个选项的高亮状态
	int selected_index = -1; // 用于存储选中的选项索引
	clrmous(MouseX, MouseY);
	//  mouseinit();

	// 调整菜单位置，使之位于屏幕内
	if (y + n * h > 470)
		y = y - n * h;
	if (x + wide > 630)
		x = x - wide;

	size = imagesize(x, y, x + wide, y + n * h + 5);
	drop_down_buffer = malloc(size);
	if (drop_down_buffer != NULL)
		getimage(x, y, x + wide, y + n * h + 5, drop_down_buffer);
	else
	{
		// perror("ERROR IN REMEMBERING");
		// delay(3000);
		// exit(1);
	}
	setfillstyle(SOLID_FILL, lightcolor);
	bar(x, y, x + wide, y + n * h);
	setfillstyle(SOLID_FILL, darkcolor);
	bar(x, y, x + 5, y + n * h);
	bar(x + wide - 5, y, x + wide, y + n * h);
	for (i = 0; i <= n; i++)
	{
		bar(x, y + i * h, x + wide, y + i * h + 5);
	}
	if (language == 1)
		settextstyle(DEFAULT_FONT, HORIZ_DIR, lettersize);
	for (i = 0; i < n; i++)
	{
		if (language == 0)
			puthz(x + 10, y + i * h + 10, msgs[i], lettersize, 2, DARKGRAY);
		else if (language == 1)
			outtextxy(x + 10, y + i * h + 10, msgs[i]);
	}

	while (1)
	{
		place = 0;
		newmouse(&MouseX, &MouseY, &press);

		for (i = 0; i < n; i++)
		{
			int result = mouse_press(x, y + i * h, x + wide, y + (i + 1) * h); // 防止多次调用
			if (result == 2)
			{
				if (flag != i)
				{
					MouseS = 1;
					flag = i;
					num[i] = 1;
					// clrmous(MouseX, MouseY);
					if (language == 1)
					{
						setcolor(CYAN);
						settextstyle(DEFAULT_FONT, HORIZ_DIR, lettersize);
						outtextxy(x + 10, y + i * h + 10, msgs[i]);
					}
					else if (language == 0)
						puthz(x + 10, y + i * h + 10, msgs[i], lettersize, 2, CYAN);
				}
				place = 1;
			}
			else if (result == 1)
			{
				// strcpy(record, msgs[i]);
				selected_index = i; // 记录选中的选项索引
				clrmous(MouseX, MouseY);
				if (son_menu == 0)
					putimage(x, y, drop_down_buffer, COPY_PUT);
				free(drop_down_buffer);
				place = 2;
				break;
			}

			if (flag != i && num[i] == 1)
			{
				if (language == 1)
				{
					setcolor(DARKGRAY);
					settextstyle(DEFAULT_FONT, HORIZ_DIR, lettersize);
					outtextxy(x + 10, y + i * h + 10, msgs[i]);
				}
				else if (language == 0)
					puthz(x + 10, y + i * h + 10, msgs[i], lettersize, 2, DARKGRAY);
			}
		}
		if (mouse_press_out(x, y, x + wide, y + n * h + 5))
		{
			selected_index = -1;
			clrmous(MouseX, MouseY);
			putimage(x, y, drop_down_buffer, COPY_PUT);
			free(drop_down_buffer);
			return -1;
		}
		if (place == 0)
		{
			MouseS = 0;
			flag = n + 1;
		}
		else if (place == 2)
		{
			break;
		}
	}
	MouseS = 0;
	return selected_index; // 返回选中的选项索引
}