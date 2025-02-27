#include <graphics.h>
#include <dos.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <dirent.h>
#include <direct.h> 
#include "include.h" 

extern char path[1024];//当前路径
extern char history[HISTORY_LENGTH][1024];//操作历史
extern int now_history;//当前在路径在history中的位置，服务撤销操作
extern void* buffer;//缓存
extern struct dir_tree tree;//目录树，用于加载左栏，以及通过左栏快速定位

void spinOnce(DIR* dir, struct dirent* entry, struct file_info* info)//更新状态检测函数
{	
	newmouse(&MouseX, &MouseY, &press);
	getcwd(path, sizeof(path));
	read_dir(dir, entry, info);
	if (now_history == 0 && strcmp(path, history[now_history]) != 0)
		new_history();	
}


int main()
{
	DIR* dir;//= opendir(".");//指向当前目录（.）的目录流
	struct dirent* entry;//指向目录中的一个条目（文件或文件夹）
	struct file_info info[10];//存放文件信息
    int gd = DETECT, gm;  // 图形驱动和图形模式    
	int result;//用来存放函数返回值，防止多次调用
	initgraph(&gd, &gm, "C:\\BORLANDC\\BGI");// 初始化图形模式
	mouseinit();

	if (!login())	//登陆失败
		return;		
	else	//登陆成功
	{
		MouseS = 0;
		cleardevice();
		clrmous(MouseX, MouseY);
		//buffer = NULL;
		//tree_make(&tree);//目录树开始构建
		load_init(info);//界面初始化
		spinOnce(dir, entry, info);//刷新info
		load_all(info);//显示

		while (1)
		{
			spinOnce(dir, entry, info);

			if (mouse_press(10, 10, 30, 30) == 1)//|| mouse_press(10, 10, 30, 30) == 4)//如果点击<-撤销目录操作
			{
				undo_dir();
				spinOnce(dir, entry, info);
				clrmous(MouseX, MouseY);
				cleardevice();
				load_all(info);
			}
			else if (mouse_press(30, 10, 50, 30) == 1)// || mouse_press(30, 10, 50, 30) == 4)//如果点击->反撤销目录操作
			{
				anti_undo_dir();
				spinOnce(dir, entry, info);
				clrmous(MouseX, MouseY);
				cleardevice();
				load_all(info);
			}
			else if (mouse_press(50, 10, 70, 30) == 1)//|| mouse_press(50, 10, 70, 30) == 4)//如果点击返回上一级目录
			{
				back();
				spinOnce(dir, entry, info);
				clrmous(MouseX, MouseY);
				cleardevice();
				load_all(info);
			}
			else if (mouse_press(70, 10, 90, 30) == 1)//|| mouse_press(70, 10, 90, 30) == 4)//如果点击刷新
			{
				spinOnce(dir, entry, info);
				clrmous(MouseX, MouseY);
				cleardevice();
				load_all(info);
			}

			else if (mouse_press(120, 70, 640, 480) == 1)// || mouse_press(120, 70, 640, 480) == 4)//如果点击文件（夹）区域
			{
				result = change_dir(info, MouseX, MouseY);
				if (result == 2)//|| change_dir(info, MouseX, MouseY) == 0)//进入或无效点击
				{
					clrmous(MouseX, MouseY);
					cleardevice();
					spinOnce(dir, entry, info);
					delay(200);
					load_all(info);
				}
				else if (result == 1)//选中
				{
					clrmous(MouseX, MouseY);
					cleardevice();
					spinOnce(dir, entry, info);
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

		}
	}

	closegraph();
	return 0;
}