/********����ҳ��********/

// �ѽ��滮��Ϊ
// top�������������𣬵�ǰ·��
// head���������ֹ��ܰ�ť
// left�������ļ��ṹ
// main������������

// #include <graphics.h>
// #include <conio.h>
// #include <dos.h>
// #include <stdio.h>
// #include <string.h>
// #include <time.h>
// #include <dirent.h>
// #include <direct.h>
// #include <sys/stat.h> // �ļ�״̬
#include <IMAGE.h>
#include "include.h"

extern char path[1024]; // ��ǰ·��
extern char history[HISTORY_LENGTH][1024];
extern char chosen_name[13];	 // ��ѡ�е��ļ���
extern struct dir_tree tree;	 // Ŀ¼�������ڼ����������Լ�ͨ���������ٶ�λ
extern struct My_filenode *root; //

void load_init(struct file_info *info) // �����ʼ��
{
	setbkcolor(BLACK);
	chdir("C:\\PROJECT");
	if (getcwd(path, sizeof(path)) == NULL) // ��ȡ��ǰ·��
	{
		perror("�޷���ȡ��ǰ·��");
		return;
	}
	strcpy(history[0], path); // ·��������ʷ��ʼ��¼
							  // ���ؽ���
							  // load_all(info);
}

void load_all(struct file_info *info, char *target, int mode) // ���ؽ���
{
	load_top(target, mode);
	line(1, 35, 640, 35);
	load_head(mode);
	line(1, 65, 640, 65);
	load_left();
	floodfill(121, 71, BLACK);
	line(105, 65, 105, 480);
	load_main(info, mode);
}

void load_top(char *target, int mode) //(10,10)(630,30)
{
	setcolor(WHITE);
	settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
	// ����
	puthz(10, 10, "��", 16, 0, WHITE); // ǰ����Щ���žͲ�ȥ����
	puthz(30, 10, "��", 16, 0, WHITE);
	puthz(50, 10, "��", 16, 0, WHITE);
	outtextxy(70, 10, "@");

	// ·��
	settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
	rectangle(90, 10, 500, 30);
	outtextxy(92, 15, path);

	// ����
	// rectangle(540, 10, 630, 30);
	// puthz(542, 12, "����", 16, 2, WHITE);
	if (mode == 1) // ����ģʽ
	{
		setfillstyle(SOLID_FILL, BLACK);
		bar(540, 10, 630, 30);
		rectangle(540, 10, 630, 30);
		outtextxy(542, 12, target);
	}
	else if (mode == 0 && strcmp(target, "") == 0) // һ��ģʽ����������Ŀ��Ϊ��
	{
		clrmous(MouseX, MouseY);
		setfillstyle(SOLID_FILL, BLACK);
		bar(540, 10, 630, 30);
		rectangle(540, 10, 630, 30);
		puthz(542, 12, "����", 16, 2, WHITE);
	}
	else if (mode == 0 && strcmp(target, "") != 0) // ����һ��ģʽʱ������Ŀ�겻Ϊ��
	{
		setfillstyle(SOLID_FILL, BLACK);
		bar(540, 10, 630, 30);
		setcolor(WHITE);
		settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
		outtextxy(542, 12, target);
	}
}

// void load_head() //(10,40)(630,60)
// {
// 	setcolor(WHITE);
// 	puthz(12, 42, "�½�", 16, 2, WHITE);
// 	puthz(55, 42, "��", 16, 2, WHITE);
// 	puthz(75, 42, "��", 16, 2, WHITE);
// 	puthz(95, 42, "ճ", 16, 2, WHITE);
// 	puthz(115, 42, "��", 16, 2, WHITE);
// 	puthz(135, 42, "ɾ", 16, 2, WHITE);
// 	puthz(155, 42, "����", 16, 2, WHITE);
// 	puthz(195, 42, "�鿴", 16, 2, WHITE);
// 	puthz(235, 42, "��", 16, 2, WHITE);
// }

void load_head(int mode) //(10,40)(630,60)
{
	setcolor(WHITE);
	// �½�
	bmp_convert("C:\\PROJECT\\src\\Images\\BMP\\build.bmp", "C:\\PROJECT\\src\\Images\\DBM\\build.dbm");
	show_dbm(12, 42, "C:\\PROJECT\\src\\Images\\DBM\\build.dbm", 0);
	// ����
	bmp_convert("C:\\PROJECT\\src\\Images\\BMP\\cut.bmp", "C:\\PROJECT\\src\\Images\\DBM\\cut.dbm");
	show_dbm(65, 42, "C:\\PROJECT\\src\\Images\\DBM\\cut.dbm", 0);
	// ����
	bmp_convert("C:\\PROJECT\\src\\Images\\BMP\\todo.bmp", "C:\\PROJECT\\src\\Images\\DBM\\todo.dbm");
	show_dbm(90, 42, "C:\\PROJECT\\src\\Images\\DBM\\todo.dbm", 0);
	// ճ��
	bmp_convert("C:\\PROJECT\\src\\Images\\BMP\\paste.bmp", "C:\\PROJECT\\src\\Images\\DBM\\paste.dbm");
	show_dbm(115, 42, "C:\\PROJECT\\src\\Images\\DBM\\paste.dbm", 0);
	// ɾ��
	bmp_convert("C:\\PROJECT\\src\\Images\\BMP\\delete.bmp", "C:\\PROJECT\\src\\Images\\DBM\\delete.dbm");
	show_dbm(150, 42, "C:\\PROJECT\\src\\Images\\DBM\\delete.dbm", 0);
	// ����
	bmp_convert("C:\\PROJECT\\src\\Images\\BMP\\sort.bmp", "C:\\PROJECT\\src\\Images\\DBM\\sort.dbm");
	show_dbm(180, 42, "C:\\PROJECT\\src\\Images\\DBM\\sort.dbm", 0);
	// �鿴
	bmp_convert("C:\\PROJECT\\src\\Images\\BMP\\check.bmp", "C:\\PROJECT\\src\\Images\\DBM\\check.dbm");
	show_dbm(280, 42, "C:\\PROJECT\\src\\Images\\DBM\\check.dbm", 0);
	// ������
	bmp_convert("C:\\PROJECT\\src\\Images\\BMP\\rename.bmp", "C:\\PROJECT\\src\\Images\\DBM\\rename.dbm");
	show_dbm(400, 42, "C:\\PROJECT\\src\\Images\\DBM\\rename.dbm", 0);
}

// void load_left() //(10,70)(100,470)
// {
// 	int i;			// ѭ������
// 	int layer = 0;	// Ŀ¼�Ĳ�������c���ʵ�0��
// 	int pen_x = 10; // ����λ��
// 	int pen_y = 70;
// 	setcolor(WHITE);
// 	settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
// 	outtextxy(pen_x, pen_y, ">");
// 	pen_x += 10;
// 	// if (strcmp(tree.name, "") == 0)
// 	// 	exit(0);
// 	outtextxy(pen_x, pen_y, tree.name);
// 	// printf("%s:%d,%d\n", tree.name, pen_x, pen_y);
// 	if (tree.is_branch_on != 0) // �����Ŀ¼�ɼ�
// 		for (i = 0; tree.branch[i] != NULL; i++)
// 			load_left_assist(tree.branch[i], layer, pen_x, &pen_y);
// }
// void load_left_assist(struct dir_tree *p, int layer, int pen_x, int *pen_y) //(����������������)���س������ַ��������Ŀ¼
// {
// 	int i; // ѭ������
// 	layer++;
// 	*pen_y += 10;
// 	outtextxy(pen_x, *pen_y, ">");
// 	pen_x += 10;
// 	outtextxy(pen_x, *pen_y, p->name);
// 	// printf("%s:%d,%d\n", p->name, pen_x, *pen_y);
// 	if (p->is_branch_on != 0 && layer < 2) // �����Ŀ¼�ɼ�
// 		for (i = 0; p->branch[i] != NULL; i++)
// 			load_left_assist(p->branch[i], layer, pen_x, pen_y);
// }

void load_left() //(10,70)(100,470)
{
	// int i;			// ѭ������
	int layer = 0;	// Ŀ¼�Ĳ�������c���ʵ�0��
	int pen_x = 10; // ����λ��
	int pen_y = 70;
	struct My_filenode *p;
	setcolor(WHITE);
	settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
	// outtextxy(pen_x, pen_y, ">");
	// outtextxy(pen_x + 10, pen_y, root->name);
	if (get_bit(root->flag, 4) == 1 && root->son_list_head != NULL) // ���Ŀ¼չ��
	{

		load_left_assist(root->son_list_head, layer, pen_x + 10, &pen_y);
	}
}
void load_left_assist(struct My_filenode *head, int layer, int pen_x, int *pen_y) //(����������������)���س������ַ��������Ŀ¼�ͺ����ͬ��Ŀ¼
{

	*pen_y += 10;
	outtextxy(pen_x, *pen_y, ">");
	outtextxy(pen_x + 10, *pen_y, head->name);
	if (get_bit(head->flag, 4) == 1 && head->son_list_head != NULL && layer < 2) // �����Ŀ¼�ɼ�
	{
		load_left_assist(head->son_list_head, layer + 1, pen_x + 10, pen_y);
	}

	if (head->next != NULL) // ���غ����Ŀ¼
	{
		load_left_assist(head->next, layer, pen_x, pen_y);
	}
}

void load_main(struct file_info *info, int mode) //(120,70)(640,480)
{
	int i; // ����
	int j; // �ļ����
	int k; // ѭ������
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

	puthz(120, 70, "����", 16, 2, WHITE);
	line(320, 70, 320, 90);

	puthz(240, 70, "�޸�����", 16, 2, WHITE);
	line(400, 70, 400, 90);

	puthz(400, 70, "����", 16, 2, WHITE);
	line(540, 70, 540, 90);

	puthz(540, 70, "��С", 16, 2, WHITE);

	// Ϊ�˿������㣬�����׶ν����ӻ�����
	for (i = 90; i < 640; i += 20)
		line(120, i, 640, i);

	for (j = 0, i = 95; j < 10 && strcmp((info + j)->name, "") != 0; j++, i += 20)
	{
		setcolor(WHITE);
		outtextxy(120, i, (info + j)->name); // ����
		outtextxy(240, i, (info + j)->time); // �޸�����
		// puthz(480, i, info.type, 16, 1, WHITE);//����
		for (k = 0; k < 16; k++)
			if ((info + j)->flag == k) // �˵���
				outtextxy(400, i, file_type_strings[k]);

		outtextxy(540, i, (info + j)->size); // ��С
		if (strcmp(chosen_name, (info + j)->name) == 0 && (info + j)->name != 0)
		{
			setcolor(YELLOW);
			rectangle(120, 90 + j * 20, 640, 90 + j * 20 + 20);
		}
	}
}

void clearRectangle(int x1, int y1, int x2, int y2, unsigned char color) // ���ָ����������
{
	setfillstyle(SOLID_FILL, color);
	bar(x1, y1, x2, y2);
}
