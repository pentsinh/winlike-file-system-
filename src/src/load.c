/********����ҳ��********/

//�ѽ��滮��Ϊ
//top�������������𣬵�ǰ·��
//head���������ֹ��ܰ�ť
//left�������ļ��ṹ
//main������������

#include <graphics.h>
#include <conio.h>
#include <dos.h>
#include <stdio.h>
#include <time.h>
#include <dirent.h>
#include <direct.h> 
#include <sys/stat.h> // �ļ�״̬
#include "include.h"

extern char path[1024];//��ǰ·��
extern char history[HISTORY_LENGTH][1024];
void load_init(struct file_info* info)//�����ʼ��
{
	setbkcolor(BLACK);
	chdir("C:\\PROJECT");
	if (getcwd(path, sizeof(path)) == NULL)//��ȡ��ǰ·��
	{
		perror("�޷���ȡ��ǰ·��");
		return ;
	}
	strcpy(history[0], path);//·��������ʷ��ʼ��¼
	//���ؽ���
	load_all(info);
}

void load_all(struct file_info* info)//���ؽ���
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
	//����
	puthz(10, 10, "��", 16, 0, WHITE);		//ǰ����Щ���žͲ�ȥ����
	puthz(30, 10, "��", 16, 0, WHITE);
	puthz(50, 10, "��", 16, 0, WHITE);
	outtextxy(70, 10, "@");

	//·��
	settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
	rectangle(90, 10, 500, 30);
	outtextxy(92, 15, path);

	//����
	rectangle(540, 10, 630, 30);
	puthz(542, 12, "����", 16, 2, WHITE);

}


void load_head()//(10,40)(630,60)
{
	setcolor(WHITE);
	puthz(12, 42, "�½�", 16, 2, WHITE);
	puthz(55, 42, "��", 16, 2, WHITE);
	puthz(75, 42, "��", 16, 2, WHITE);
	puthz(95, 42, "ճ", 16, 2, WHITE);
	puthz(115, 42, "��", 16, 2, WHITE);
	puthz(135, 42, "ɾ", 16, 2, WHITE);
	puthz(155, 42, "����", 16, 2, WHITE);
	puthz(195, 42, "�鿴", 16, 2, WHITE);
	puthz(235, 42, "��", 16, 2, WHITE);
	

}


void load_left()//(10,50)(100,470)
{

}


void load_main(struct file_info *info)//(120,70)(640,480)
{
	int i;
	int j;

	puthz(120, 70, "����", 16, 2, WHITE);
	line(320, 70, 320, 90);

	puthz(240, 70, "�޸�����", 16, 2, WHITE);
	line(400, 70, 400, 90);

	puthz(400, 70, "����", 16, 2, WHITE);
	line(540, 70, 540, 90);

	puthz(540, 70, "��С", 16, 2, WHITE);

	//Ϊ�˿������㣬�����׶ν����ӻ�����
	for (i = 90; i < 640; i += 20)
		line(120, i, 640, i);

	for (j = 0, i = 95; j < 10; j++, i += 20)
	{
		outtextxy(120, i, (info+j)->name);//����
		outtextxy(240, i, (info+j)->time);//�޸�����		
		//puthz(480, i, info.type, 16, 1, WHITE);//����
		outtextxy(400, i, (info + j)->type);//����
		outtextxy(540, i, (info + j)->size);//��С
	}
}


