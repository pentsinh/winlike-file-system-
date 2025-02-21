#include <graphics.h>
#include <dos.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <dirent.h>
#include <direct.h> 
#include "include.h" 

extern char path[1024];
extern char history[HISTORY_LENGTH][1024];
extern int now_history;//��ǰ��·����history�е�λ�ã�����������
extern void* buffer;//����

void spinOnce(DIR* dir, struct dirent* entry, struct file_info* info)//����״̬��⺯��
{
	newmouse(&MouseX, &MouseY, &press);
	getcwd(path, sizeof(path));
	read_dir(dir, entry, info);
	if (now_history == 0 && strcmp(path, history[now_history]) != 0)
		new_history();
}

int main()
{
	DIR* dir;//= opendir(".");//ָ��ǰĿ¼��.����Ŀ¼��
	struct dirent* entry;//ָ��Ŀ¼�е�һ����Ŀ���ļ����ļ��У�
	struct file_info info[10];//����ļ���Ϣ
    int gd = DETECT, gm;  // ͼ��������ͼ��ģʽ    
	initgraph(&gd, &gm, "C:\\BORLANDC\\BGI");// ��ʼ��ͼ��ģʽ
	mouseinit();

	if (!login())	//��½ʧ��
		return;		
	else	//��½�ɹ�
	{
		MouseS = 0;
		cleardevice();
		//buffer = NULL;
		load_init(info);
		spinOnce(dir, entry, info);
		load_all(info);

		while (1)
		{
			spinOnce(dir, entry, info);

			if (mouse_press(10, 10, 30, 30) == 1 || mouse_press(10, 10, 30, 30) == 4)//������<-����Ŀ¼����
			{
				undo_dir();
				spinOnce(dir, entry, info);
				cleardevice();
				load_all(info);
			}
			else if (mouse_press(30, 10, 50, 30) == 1 || mouse_press(30, 10, 50, 30) == 4)//������->������Ŀ¼����
			{
				anti_undo_dir();
				spinOnce(dir, entry, info);
				cleardevice();
				load_all(info);
			}
			else if (mouse_press(50, 10, 70, 30) == 1 || mouse_press(50, 10, 70, 30) == 4)//������������һ��Ŀ¼
			{
				back();
				spinOnce(dir, entry, info);
				cleardevice();
				load_all(info);
			}
			else if (mouse_press(70, 10, 90, 30) == 1 || mouse_press(70, 10, 90, 30) == 4)//������ˢ��
			{
				spinOnce(dir, entry, info);
				cleardevice();
				load_all(info);
			}
			
			else if (mouse_press(120, 70, 640, 480) == 1 || mouse_press(120, 70, 640, 480) == 4)//�������ļ����У�����
			{
				if (change_dir(info, MouseX, MouseY) == 2 || change_dir(info, MouseX, MouseY) == 0)
				{
					cleardevice();
					spinOnce(dir, entry, info);					
					load_all(info);
				}
				else if (change_dir(info, MouseX, MouseY) == 1)
				{
					spinOnce(dir, entry, info);
					load_all(info);
				}				

			}
			
		}
	}

	closegraph();
	return 0;
}