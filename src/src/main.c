#include <graphics.h>
#include <dos.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "include.h" 

extern char path[1024];
extern char history[HISTORY_LENGTH][1024];

void spinOnce()//����״̬��⺯��
{
	newmouse(&MouseX, &MouseY, &press);
	getcwd(path, sizeof(path));
	if (strcmp(path, history[0]) != 0)
		new_history();
}

int main()
{
    int gd = DETECT, gm;  // ͼ��������ͼ��ģʽ    
	initgraph(&gd, &gm, "C:\\BORLANDC\\BGI");// ��ʼ��ͼ��ģʽ
	mouseinit();

	if (!login())	//��½ʧ��
		return;		
	else	//��½�ɹ�
	{
		MouseS = 0;
		cleardevice();
		load_init();
		while (1)
		{
			spinOnce();

			if (mouse_press(10, 10, 30, 30) == 1 || mouse_press(10, 10, 30, 30) == 4)//������<-����Ŀ¼����
			{
				undo_dir();
				load_all();
			}
			else if (mouse_press(30, 10, 50, 30) == 1 || mouse_press(30, 10, 50, 30) == 4)//������->������Ŀ¼����
			{
				anti_undo_dir();
				load_all();
			}
			else if (mouse_press(50, 10, 70, 30) == 1 || mouse_press(50, 10, 70, 30) == 4)//������������һ��Ŀ¼
			{
				chdir("..");
				getcwd(path, sizeof(path));
				load_all();
			}
			else if (mouse_press(70, 10, 90, 30) == 1 || mouse_press(70, 10, 90, 30) == 4)//������ˢ��
				load_all();
			
		}
	}

	closegraph();
	return 0;
}