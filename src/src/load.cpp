/********加载页面********/

// 把界面划分为
// top顶栏：调整级别，当前路径
// head上栏：各种功能按钮
// left左栏：文件结构
// main主栏：操作板

#include <graphics.h>
#include <conio.h>
#include <dos.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <dirent.h>
#include <direct.h>
#include <sys/stat.h> // 文件状态
#include "include.h"

extern char path[1024]; // 当前路径
extern char history[HISTORY_LENGTH][1024];
extern char chosen_name[13];	 // 被选中的文件名
extern struct dir_tree tree;	 // 目录树，用于加载左栏，以及通过左栏快速定位
extern struct My_filenode *root; //

void load_init(struct file_info *info) // 界面初始化
{
	setbkcolor(BLACK);
	chdir("C:\\PROJECT");
	if (getcwd(path, sizeof(path)) == NULL) // 获取当前路径
	{
		perror("无法获取当前路径");
		return;
	}
	strcpy(history[0], path); // 路径操作历史开始记录
							  // 加载界面
							  // load_all(info);
}

void load_all(struct file_info *info) // 加载界面
{
	load_top();
	line(1, 35, 640, 35);
	load_head();
	line(1, 65, 640, 65);
	load_left();
	floodfill(121, 71, BLACK);
	line(105, 65, 105, 480);
	load_main(info);
}

void load_top() //(10,10)(630,30)
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
	rectangle(540, 10, 630, 30);
	puthz(542, 12, "搜索", 16, 2, WHITE);
}

void load_head() //(10,40)(630,60)
{
	setcolor(WHITE);
	puthz(12, 42, "新建", 16, 2, WHITE);
	puthz(55, 42, "剪", 16, 2, WHITE);
	puthz(75, 42, "复", 16, 2, WHITE);
	puthz(95, 42, "粘", 16, 2, WHITE);
	puthz(115, 42, "共", 16, 2, WHITE);
	puthz(135, 42, "删", 16, 2, WHITE);
	puthz(155, 42, "排序", 16, 2, WHITE);
	puthz(195, 42, "查看", 16, 2, WHITE);
	puthz(235, 42, "…", 16, 2, WHITE);
}

// void load_left() //(10,70)(100,470)
// {
// 	int i;			// 循环变量
// 	int layer = 0;	// 目录的层数，设c盘问第0层
// 	int pen_x = 10; // 画笔位置
// 	int pen_y = 70;
// 	setcolor(WHITE);
// 	settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
// 	outtextxy(pen_x, pen_y, ">");
// 	pen_x += 10;
// 	// if (strcmp(tree.name, "") == 0)
// 	// 	exit(0);
// 	outtextxy(pen_x, pen_y, tree.name);
// 	// printf("%s:%d,%d\n", tree.name, pen_x, pen_y);
// 	if (tree.is_branch_on != 0) // 如果子目录可见
// 		for (i = 0; tree.branch[i] != NULL; i++)
// 			load_left_assist(tree.branch[i], layer, pen_x, &pen_y);
// }
// void load_left_assist(struct dir_tree *p, int layer, int pen_x, int *pen_y) //(加载左栏辅助函数)加载出传入地址的所有子目录
// {
// 	int i; // 循环变量
// 	layer++;
// 	*pen_y += 10;
// 	outtextxy(pen_x, *pen_y, ">");
// 	pen_x += 10;
// 	outtextxy(pen_x, *pen_y, p->name);
// 	// printf("%s:%d,%d\n", p->name, pen_x, *pen_y);
// 	if (p->is_branch_on != 0 && layer < 2) // 如果子目录可见
// 		for (i = 0; p->branch[i] != NULL; i++)
// 			load_left_assist(p->branch[i], layer, pen_x, pen_y);
// }

void load_left() //(10,70)(100,470)
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

void load_main(struct file_info *info) //(120,70)(640,480)
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

	for (j = 0, i = 95; j < 10 && strcmp((info + j)->name, "") != 0; j++, i += 20)
	{
		setcolor(WHITE);
		outtextxy(120, i, (info + j)->name); // 名称
		outtextxy(240, i, (info + j)->time); // 修改日期
		// puthz(480, i, info.type, 16, 1, WHITE);//类型
		for (k = 0; k < 16; k++)
			if ((info + j)->flag == k) // 此电脑
				outtextxy(400, i, file_type_strings[k]);

		outtextxy(540, i, (info + j)->size); // 大小
		if (strcmp(chosen_name, (info + j)->name) == 0 && (info + j)->name != 0)
		{
			setcolor(YELLOW);
			rectangle(120, 90 + j * 20, 640, 90 + j * 20 + 20);
		}
	}
}
