#include <graphics.h>
#include <dos.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "include.h" 

extern char path[1024];
extern char history[HISTORY_LENGTH][1024];

void spinOnce()//更新状态检测函数
{
	newmouse(&MouseX, &MouseY, &press);
	getcwd(path, sizeof(path));
	if (strcmp(path, history[0]) != 0)
		new_history();
}

int main()
{
    int gd = DETECT, gm;  // 图形驱动和图形模式    
	initgraph(&gd, &gm, "C:\\BORLANDC\\BGI");// 初始化图形模式
	mouseinit();

	if (!login())	//登陆失败
		return;		
	else	//登陆成功
	{
		MouseS = 0;
		cleardevice();
		load_init();
		while (1)
		{
			spinOnce();

			if (mouse_press(10, 10, 30, 30) == 1 || mouse_press(10, 10, 30, 30) == 4)//如果点击<-撤销目录操作
			{
				undo_dir();
				load_all();
			}
			else if (mouse_press(30, 10, 50, 30) == 1 || mouse_press(30, 10, 50, 30) == 4)//如果点击->反撤销目录操作
			{
				anti_undo_dir();
				load_all();
			}
			else if (mouse_press(50, 10, 70, 30) == 1 || mouse_press(50, 10, 70, 30) == 4)//如果点击返回上一级目录
			{
				chdir("..");
				getcwd(path, sizeof(path));
				load_all();
			}
			else if (mouse_press(70, 10, 90, 30) == 1 || mouse_press(70, 10, 90, 30) == 4)//如果点击刷新
				load_all();
			
		}
	}

	closegraph();
	return 0;
}