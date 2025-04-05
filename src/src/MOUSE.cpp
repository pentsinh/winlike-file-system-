#include <conio.h>
#include <graphics.h>
#include <dos.h>
#include <process.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mouse.h"

/**************************
MOUSE.c
UPDATER: dengshuumin/pentsinh
FUNCTION: mouse action
ABSTRACT:
		A.mread
		B.newmouse
VERSION: 3.3
2025.3.9
在mread函数中更新了鼠标状态的全局变量；
完善了鼠标的点击过程（从弹起到按下到弹起）；
增加了鼠标框外点击检测;
为鼠标添加了双击状态（返回 4 ）,双击检测不稳定(完全不可用)
***************************/
int MouseX;
int MouseY;
int MouseS;
int press;
void *buffer;
union REGS regs;
int flag = 0;

time_t last_click_time = 0; // 记录上次点击时间
int click_count = 0;		// 点击次数计数器
// int is_mouse_down = 0;		// 鼠标按下状态
// int click_flag = 0;

void mouseinit() // 初始化
{
	int retcode;
	int xmin, xmax, ymin, ymax, x_max = 625, y_max = 480;
	int size;

	xmin = 2;
	xmax = x_max - 1;
	ymin = 8;
	ymax = y_max - 2;
	regs.x.ax = 0;
	int86(51, &regs, &regs);
	retcode = regs.x.ax;
	if (retcode == 0)
	{
		printf("Mouse or Mouse Driver Obsent,Please Install!");
		delay(5000);
	}
	else
	{
		regs.x.ax = 7;
		regs.x.cx = xmin;
		regs.x.dx = xmax;
		int86(51, &regs, &regs);
		regs.x.ax = 8;
		regs.x.cx = ymin;
		regs.x.dx = ymax;
		int86(51, &regs, &regs);
	}
	MouseS = 0;
	// 初始化定时器中断
	// init_timer_interrupt();
	//
	// MouseX=320,MouseY=240;
	// save_bk_mou(320,240);
	// mouse(MouseX,MouseY);
	// flag=1;
}

/*****************************
FUNCTION: mouse
DESCRIPTION: 画不同形态的鼠标
INPUT: x,y
RETURN: 无
******************************/
void mouse(int x, int y)
{

	switch (MouseS)
	{
	case 1: // 手势鼠标
	{
		setcolor(WHITE);
		setlinestyle(0, 0, 1);
		line(x - 1, y + 9, x - 1, y + 8);
		line(x, y + 7, x, y + 11);
		line(x + 1, y + 6, x + 1, y + 13);
		line(x + 2, y + 8, x + 2, y + 14);
		line(x + 3, y - 1, x + 3, y + 15);
		arc(x + 4, y - 1, 0, 180, 1);
		line(x + 4, y - 2, x + 4, y + 15);
		line(x + 5, y - 1, x + 5, y + 16);
		arc(x + 6, y + 3, 0, 180, 1);
		line(x + 6, y + 2, x + 6, y + 16);
		line(x + 7, y + 3, x + 7, y + 17);
		arc(x + 8, y + 5, 0, 180, 1);
		line(x + 8, y + 4, x + 8, y + 17);
		line(x + 9, y + 5, x + 9, y + 16);
		arc(x + 10, y + 7, 0, 180, 1);
		line(x + 10, y + 6, x + 10, y + 16);
		line(x + 11, y + 7, x + 11, y + 13);

		setcolor(DARKGRAY);
		line(x - 1, y + 9, x - 1, y + 8);
		line(x - 1, y + 8, x + 1, y + 6);
		line(x + 1, y + 6, x + 3, y + 10);
		line(x + 3, y + 10, x + 3, y - 1);
		arc(x + 4, y - 1, 0, 180, 1);
		line(x + 5, y - 1, x + 5, y + 5);
		arc(x + 6, y + 3, 0, 180, 1);
		line(x + 7, y + 3, x + 7, y + 7);
		arc(x + 8, y + 5, 0, 180, 1);
		line(x + 9, y + 5, x + 9, y + 9);
		arc(x + 10, y + 7, 0, 180, 1);
		line(x + 11, y + 7, x + 11, y + 13);
		arc(x + 7, y + 13, -90, 0, 4);
		line(x + 7, y + 17, x + 3, y + 15);
		line(x + 3, y + 15, x + 1, y + 13);
		line(x + 1, y + 13, x - 1, y + 9);
	}
	break;
	case 2: // 光标
	{
		setcolor(DARKGRAY);
		setlinestyle(0, 0, 1);
		line(x + 1, y - 1, x + 9, y - 1);
		line(x + 1, y + 15, x + 9, y + 15);
		line(x + 5, y - 1, x + 5, y + 15);
	}
	break;
	case 3: // 十字
	{
		setcolor(WHITE);
		setlinestyle(0, 0, 1);
		line(x - 1, y + 7, x + 11, y + 7);
		line(x + 5, y - 1, x + 5, y + 15);
	}
	break;
	default: // 默认鼠标
	{
		setlinestyle(0, 0, 1);
		setcolor(WHITE);
		line(x, y, x, y + 13);
		line(x + 1, y + 1, x + 1, y + 12);
		line(x + 2, y + 2, x + 2, y + 11);
		line(x + 3, y + 3, x + 3, y + 10);
		line(x + 4, y + 4, x + 4, y + 12);
		line(x + 5, y + 5, x + 5, y + 9);
		line(x + 5, y + 11, x + 5, y + 14);
		line(x + 6, y + 6, x + 6, y + 9);
		line(x + 6, y + 13, x + 6, y + 15);
		line(x + 7, y + 7, x + 7, y + 9);
		line(x + 8, y + 8, x + 8, y + 9);
		line(x + 9, y + 9, x + 9, y + 9);
		setcolor(DARKGRAY);
		line(x - 1, y - 1, x - 1, y + 14);
		line(x - 1, y + 14, x + 3, y + 11);
		line(x + 3, y + 11, x + 3, y + 12);
		line(x + 3, y + 12, x + 4, y + 13);
		line(x + 4, y + 13, x + 4, y + 14);
		line(x + 4, y + 14, x + 7, y + 17);
		line(x + 7, y + 17, x + 7, y + 13);
		line(x + 7, y + 13, x + 6, y + 12);
		line(x + 6, y + 12, x + 6, y + 11);
		line(x + 6, y + 11, x + 5, y + 10);
		line(x + 5, y + 10, x + 11, y + 10);
		line(x + 11, y + 10, x - 1, y - 2);
	}
	break;
	}
}

/*void mou_pos(int *nx,int *ny,int*nbuttons)//更改鼠标位置
{
	int x0=*nx,y0=*ny;

	mread(nx,ny,nbuttons);
	clrmous(x0,y0);
	save_bk_mou(*nx,*ny);
	drawmous(*nx,*ny);
}

void mread(int *nx,int *ny,int*nbuttons)//改坐标不画
{
	int x0=*nx,y0=*ny,buttons0=*nbuttons;
	int xnew,ynew,buttonsnew;

	do{
	regs.x.ax=3;
	int86(51,&regs,&regs);
	buttonsnew=regs.x.bx;
	delay(10);
	regs.x.ax=3;
	int86(51,&regs,&regs);
	if(regs.x.bx==buttonsnew)
		*nbuttons=regs.x.bx;
	else
		*nbuttons=buttons0;
	xnew=regs.x.cx;
	ynew=regs.x.dx;
	}while(xnew==x0&&ynew==y0&&*nbuttons==0);
	*nx=xnew;
	*ny=ynew;
}
*/

/***************************************
FUNCTION: mread
DESCRIPTION: 获取新的寄存器信息
INPUT: nx,ny,nbuttons
RETURN: 无
****************************************/
void mread(int *nx, int *ny, int *nbuttons)
{
	regs.x.ax = 3; // 获取鼠标状态（位置和按钮状态）
	int86(51, &regs, &regs);
	*nx = regs.x.cx; // 获取x坐标
	MouseX = regs.x.cx;
	*ny = regs.x.dx; // 获取y坐标
	MouseY = regs.x.dx;
	*nbuttons = regs.x.bx; // 获取鼠标按钮状态
	press = regs.x.bx;
}

/*******************************************
FUNCTION: newmouse
DESCRIPTION: 鼠标状态发生变化则更新鼠标
INPUT: nx,ny,nbuttons
RETURN: 无
********************************************/
void newmouse(int *nx, int *ny, int *nbuttons)
{
	int xn, yn, buttonsn;
	int x0 = *nx, y0 = *ny, buttons0 = *nbuttons;
	mread(&xn, &yn, &buttonsn);
	*nx = xn;
	*ny = yn;
	*nbuttons = buttonsn;
	press = buttonsn;
	// if(buttons0 == *nbuttons)
	//	*nbuttons = 0;    //使得能连续按键
	if (xn == x0 && yn == y0 && buttonsn == buttons0)
		return;		 // 鼠标状态不变则直接返回S
	clrmous(x0, y0); // 说明鼠标状态发生了改变
	save_bk_mou(*nx, *ny);
	drawmous(*nx, *ny);
}

void save_bk_mou(int nx, int ny) // 存鼠标背景
{
	int size;

	size = imagesize(nx - 1, ny - 2, nx + 11, ny + 17);
	buffer = malloc(size);
	if (buffer != NULL)
		getimage(nx - 1, ny - 2, nx + 11, ny + 17, buffer);
	else
		printf("Error");
}

void clrmous(int nx, int ny) // 清除鼠标
{
	if (flag == 1)
	{
		setwritemode(XOR_PUT);
		mouse(nx, ny);
		putimage(nx - 1, ny - 2, buffer, COPY_PUT);
		free(buffer);
		flag = 0;
		setwritemode(COPY_PUT);
	}
}
void drawmous(int nx, int ny)
{
	if (flag == 0)
	{
		setwritemode(COPY_PUT);
		mouse(nx, ny);
		flag = 1;
	}
}

// 如果在框外点击，返回1；否则返回0######适用于640*480######
int mouse_press_out(int x1, int y1, int x2, int y2) // 如果在框外左键，返回1；在框外右键，返回2；否则返回0
{
	if (press == 1)
	{
		if (MouseX > x1 && MouseX < x2 && MouseY > y1 && MouseY < y2)
			return 0;
		else
			return 1;
	}
	else if (press == 2)
	{
		if (MouseX > x1 && MouseX < x2 && MouseY > y1 && MouseY < y2)
			return 0;
		else
			return 2;
	}
	else
		return 0;
}

// 辅助函数：检测完整的点击过程（从释放状态到按下状态再到释放状态）
int detect_complete_click(int press, time_t current_press_time)
{
	static int initial_press_detected = 0; // 标记是否检测到初始按下
	time_t elapsed_ticks;
	// int pid;

	if (press == 1) // 鼠标左键被按下
	{
		if (!initial_press_detected)
		{
			initial_press_detected = 1;			  // 标记初始按下
			last_click_time = current_press_time; // 更新最后点击时间
			return 0;							  // 返回0表示正在按下，等待释放
		}
	}
	else if (press == 0) // 鼠标左键被释放
	{
		if (initial_press_detected)
		{
			initial_press_detected = 0; // 重置标记
			elapsed_ticks = current_press_time - last_click_time;

			if (elapsed_ticks < 12) //
			{
				click_count++;
				if (click_count == 2)
				{
					click_count = 0;	 // 重置点击计数器
					last_click_time = 0; // 重置最后点击时间
					// click_flag = 0;
					return 4; // 返回双击标识
				}
			}
			else
			{
				// 如果超过双击时间间隔，视为单击
				click_count = 1;					  // 重置为单击
				last_click_time = current_press_time; // 更新最后点击时间
				// click_flag = 1;

				return 1; // 返回单击标识
			}
		}
	}

	return 0; // 默认返回值
}

// 检测右键完整点击
int detect_complete_click_R(int press)
{
	static int initial_press_detected_R = 0; // 标记是否检测到初始按下
	printf("%d ", initial_press_detected_R);
	if (press == 2) // 鼠标右键被按下
	{
		if (!initial_press_detected_R)
		{
			initial_press_detected_R = 1; // 标记初始按下
			return 11;					  // 返回0表示正在按下，等待释放
		}
	}
	else if (press == 0) // 鼠标右键被释放
	{
		if (initial_press_detected_R)
		{
			initial_press_detected_R = 0; // 重置标记
			return 3;					  // 返回单击标识
		}
	}

	return 12; // 默认返回值
}

int mouse_press(int x1, int y1, int x2, int y2) //
{
	time_t current_press_time = clock(); // 当前点击时间
	int result;
	// 检查鼠标位置是否在指定框内
	if (MouseX > x1 && MouseX < x2 && MouseY > y1 && MouseY < y2)
	{
		// result = detect_complete_click_R(press);
		// printf("%d/%d ", result, press);
		if (press == 2) // 右键点击
		// if (result == 3)
		{
			click_count = 0;	 // 重置点击计数器
			last_click_time = 0; // 重置最后点击时间
			return 3;			 // 返回右键点击标识
		}

		// 调用辅助函数检测完整的点击过程
		result = detect_complete_click(press, current_press_time);

		if (result != 0) // 如果有点击事件发生
		{
			return result;
		}

		else
			return 2;
	}
	else
	{
		// 如果不在框中，重置状态
		// is_mouse_down = 0;
		click_count = 0;
		last_click_time = 0;
		return 0; // 不在框中
	}

	return 0; // 默认返回值
}
