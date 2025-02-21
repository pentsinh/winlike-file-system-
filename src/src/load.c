/********加载页面********/

//把界面划分为
//top顶栏：调整级别，当前路径
//head上栏：各种功能按钮
//left左栏：文件结构
//main主栏：操作板

#include <graphics.h>
#include <conio.h>
#include <dos.h>
#include <stdio.h>
#include <time.h>
#include <dirent.h>
#include <direct.h> 
#include <sys/stat.h> // 文件状态
#include "include.h"

extern char path[1024];//当前路径
extern char history[HISTORY_LENGTH][1024];
void load_init(struct file_info* info)//界面初始化
{
	setbkcolor(BLACK);
	chdir("C:\\PROJECT");
	if (getcwd(path, sizeof(path)) == NULL)//获取当前路径
	{
		perror("无法获取当前路径");
		return ;
	}
	strcpy(history[0], path);//路径操作历史开始记录
	//加载界面
	load_all(info);
}

void load_all(struct file_info* info)//加载界面
{
	load_top();
	line(1, 35, 640, 35);
	load_head();
	line(1, 65, 640, 65);
	load_left();
	line(105, 65, 105, 480);
	load_main(info);
}

void load_top()//(10,10)(630,30)
{
	setcolor(WHITE); 
	settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
	//操作
	puthz(10, 10, "左", 16, 0, WHITE);		//前期这些符号就不去画了
	puthz(30, 10, "右", 16, 0, WHITE);
	puthz(50, 10, "上", 16, 0, WHITE);
	outtextxy(70, 10, "@");

	//路径
	settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
	rectangle(90, 10, 500, 30);
	outtextxy(92, 15, path);

	//搜索
	rectangle(540, 10, 630, 30);
	puthz(542, 12, "搜索", 16, 2, WHITE);

}


void load_head()//(10,40)(630,60)
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


void load_left()//(10,50)(100,470)
{

}


void load_main(struct file_info *info)//(120,70)(640,480)
{
	int i;
	int j;

	puthz(120, 70, "名称", 16, 2, WHITE);
	line(320, 70, 320, 90);

	puthz(240, 70, "修改日期", 16, 2, WHITE);
	line(400, 70, 400, 90);

	puthz(400, 70, "类型", 16, 2, WHITE);
	line(540, 70, 540, 90);

	puthz(540, 70, "大小", 16, 2, WHITE);

	//为了开发方便，开发阶段将格子画出来
	for (i = 90; i < 640; i += 20)
		line(120, i, 640, i);

	for (j = 0, i = 95; j < 10; j++, i += 20)
	{
		outtextxy(120, i, (info+j)->name);//名称
		outtextxy(240, i, (info+j)->time);//修改日期		
		//puthz(480, i, info.type, 16, 1, WHITE);//类型
		outtextxy(400, i, (info + j)->type);//类型
		outtextxy(540, i, (info + j)->size);//大小
	}
}


