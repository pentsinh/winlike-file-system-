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

char path[1024];//��ǰ·��
extern char history[HISTORY_LENGTH][1024];
void load_init()//�����ʼ��
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
	load_all();
}

void load_all()//���ؽ���
{
	cleardevice();
	load_top();
	line(1, 35, 640, 35);
	load_head();
	line(1, 65, 640, 65);
	load_left();
	line(105, 65, 105, 480);
	load_main();
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


void load_main()//(120,70)(640,480)
{
	int i;

	DIR* dir = opendir(".");//ָ��ǰĿ¼��.����Ŀ¼��
	struct dirent* entry;//ָ��Ŀ¼�е�һ����Ŀ���ļ����ļ��У�
	struct stat statbuf;//�洢�ļ����ļ��е�Ԫ������Ϣ�����С���޸�ʱ�䡢Ȩ�޵�
	char time_str[20];//���ڴ洢��ʽ�����ʱ���ַ���
	char* type = get_file_type(statbuf.st_mode);//�洢�ļ����͵��������硰�ļ�������Ŀ¼���ȣ���

	puthz(120, 70, "����", 16, 2, WHITE);
	line(320, 70, 320, 90);

	puthz(320, 70, "�޸�����", 16, 2, WHITE);
	line(480, 70, 480, 90);

	puthz(480, 70, "����", 16, 2, WHITE);
	line(580,70,580,90);

	puthz(580, 70, "��С", 16, 2, WHITE);

	//Ϊ�˿������㣬�����׶ν����ӻ�����
	for (i = 90; i < 640; i += 20)
		line(120, i, 640, i);


	while ((entry = readdir(dir))) 
	{
		if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
			continue;

		
		if (lstat(entry->d_name, &statbuf) == -1)
		{
			//perror("��ȡ�ļ���Ϣʧ��");
			continue;
		}

		// ��ʽ��ʱ��
		
		strftime(time_str, sizeof(time_str), "%Y.%m.%d %H:%M:%S",localtime(&statbuf.st_mtime));

		// ��ȡ�ļ�����
		

		// �����Ϣ
		/*printf("%-25s %-20s %-15s %8ld�ֽ�\n",
			entry->d_name,
			time_str,
			type,
			statbuf.st_size);*/
		outtextxy(120, i, entry->d_name);
		outtextxy(320, i, entry->d_name);
		puthz(480, i, type, 16, 1, WHITE);
		outtextxy(120, i, entry->d_name);

	}

	closedir(dir);



}


