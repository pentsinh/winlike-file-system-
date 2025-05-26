/********����ҳ��********/
// #define TEST
//  �ѽ��滮��Ϊ
//  top�������������𣬵�ǰ·��
//  head���������ֹ��ܰ�ť
//  left�������ļ��ṹ
//  main������������
#include "include.h"

void load_init(char path[1024], struct file_info *info, char history[HISTORY_LENGTH][1024]) // �����ʼ��
{
	setbkcolor(BLACK);
	chdir("C:\\PROJECT\\DEVEL"); // ���뿪��Ŀ¼	
	mkdir("BIN"); // ��������վ��RUBBISHBIN̫���ˡ�����
	chdir("C:\\PROJECT\\DEVEL\\BIN");
	mkdir("BIN_0"); // 0Ϊ�ݴ�
	mkdir("BIN_1");// ��������վ��Ŀ¼
	mkdir("BIN_2");// ��������վ��Ŀ¼
	mkdir("BIN_3");// ��������վ��Ŀ¼
	mkdir("BIN_4");// ��������վ��Ŀ¼
	mkdir("BIN_5");// ��������վ��Ŀ¼
	chdir("C:\\PROJECT");
	if (getcwd(path, sizeof(path) * 1024) == NULL) // ��ȡ��ǰ·��
	{
		perror("Can't get current dir");
		return;
	}
	strcpy(history[0], path); // ·��������ʷ��ʼ��¼
							  // ���ؽ���
							  // load_all(info);
}

void load_all(char path[1024], struct file_info *info, struct My_filenode *root, char *target, int mode, char preference[3][1024], int page, int pic_flag) // ���ؽ���
{
	load_top(path, target, mode);
	setcolor(WHITE);
	line(1, 35, 640, 35);
	load_head(mode);
	setcolor(WHITE);
	line(1, 65, 640, 65);
	load_left(root, preference);
	floodfill(121, 71, BLACK);
	setcolor(WHITE);
	line(105, 65, 105, 480);
	load_main(info, mode, page, pic_flag);
}

void load_top(char path[1024], char *target, int mode) //(10,10)(630,30)
{

	// ����
	draw_left(10, 10);	  // 10��10��22��22
	draw_right(30, 10);	  // 30��10��42��22
	draw_up(50, 10);	  // 50��10��62��22
	draw_refresh(70, 10); // 70��10��82��22
#ifdef TEST
	setcolor(YELLOW);
	rectangle(5, 5, 25, 25);
	rectangle(25, 5, 45, 25);
	rectangle(45, 5, 65, 25);
	rectangle(65, 5, 85, 25);
#endif

	// ·��
	setcolor(WHITE);
	settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
	rectangle(90, 10, 500, 30);
	outtextxy(92, 15, path);

	// ����
	if (mode == 1) // ����ģʽ
	{
		setfillstyle(SOLID_FILL, BLACK);
		bar(540, 10, 620, 30);
		rectangle(540, 10, 620, 30);
		setcolor(WHITE);
		settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
		outtextxy(542, 12, target);
	}
	else if (mode == 0 && strcmp(target, "") == 0) // һ��ģʽ����������Ŀ��Ϊ��
	{
		clrmous(MouseX, MouseY);
		setfillstyle(SOLID_FILL, BLACK);
		bar(540, 10, 620, 30);
		rectangle(540, 10, 620, 30);
		puthz(542, 12, "����", 16, 2, WHITE);
	}
	else if (mode == 0 && strcmp(target, "") != 0) // ����һ��ģʽʱ������Ŀ�겻Ϊ��
	{
		setfillstyle(SOLID_FILL, BLACK);
		bar(540, 10, 620, 30);
		setcolor(WHITE);
		settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
		outtextxy(542, 12, target);
	}

	// �˳�С���
	line(620, 0, 640, 20);
	line(640, 0, 620, 20);
}

void load_head(int mode) //(10,40)(630,60)
{
	setcolor(WHITE);
	// �½�
	draw_new(10, 42); // 10��42��56��58
	// ����
	draw_scissor(65, 42); // 65��42��80��57
	// ����
	draw_copy(90, 42); // 90��42��106��58
	// ճ��
	draw_paste(115, 42); // 115��42��131��60
	//  ������
	draw_rename(140, 42); // 140��42��160��56
	// ɾ��
	draw_trash(170, 42); // 170, 42��188��60
	// ����
	draw_sort(195, 42);	 // 195, 42��270��59.5
						 // �鿴
	draw_check(280, 42); // 280��42��362.5��57
#ifdef TEST
	setcolor(YELLOW);
	rectangle(5, 37, 60, 62);
	rectangle(60, 37, 85, 62);
	rectangle(85, 37, 110, 62);
	rectangle(110, 37, 135, 62);
	rectangle(135, 37, 165, 62);
	rectangle(165, 37, 190, 62);
	rectangle(190, 37, 275, 62);
	// rectangle(275, 37, 365, 62);

#endif
}

void load_left(struct My_filenode *root, char preference[3][1024]) //(10,70)(100,470)
{
	// int i;			// ѭ������
	int layer = 0; // Ŀ¼�Ĳ�������c���ʵ�0��
	int pen_x = 0; // ����λ��
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
	line(0, 408, 100, 408);
	puthz(25, 410, "�����", 12, 2, WHITE);
	for (int i = 0; i < 3; i++)
	{
		if (strcmp(preference[i], "\0") != 0)
			outtextxy(10, 430 + i * 10, path_to_name(preference[i]));
		// outtextxy(10, 430 + i * 10, preference[i]);
	}
}
void load_left_assist(struct My_filenode *head, int layer, int pen_x, int *pen_y) //(����������������)���س������ַ��������Ŀ¼�ͺ����ͬ��Ŀ¼
{

	*pen_y += 10;
	int y = *pen_y;
	if (y > 400)
		return;
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

void load_main(struct file_info *info, int mode, int page, int pic_flag) //(120,70)(640,480)
{
	int i; // ����
	int j; // �ļ����
	settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);

	// Ϊ�˿������㣬�����׶ν����ӻ�����
	// for (i = 90; i < 440; i += 20)
	// 	line(120, i, 640, i);

	if (pic_flag == 0) // Сͼ��
	{
		puthz(120, 70, "����", 16, 2, WHITE);
		line(320, 70, 320, 90);

		puthz(240, 70, "�޸�����", 16, 2, WHITE);
		line(400, 70, 400, 90);

		puthz(400, 70, "����", 16, 2, WHITE);
		line(540, 70, 540, 90);

		puthz(540, 70, "��С", 16, 2, WHITE);

		for (j = 0, i = 95; j < INFO_LENGTH && strcmp((info + j)->name, "") != 0; j++, i += 20)
		{
			load_file_info(120, i, info + j, pic_flag);
		}
	}
	else if (pic_flag == 1) // ��ͼ��
	{
		for (j = 0, i = 160; j < INFO_LENGTH && strcmp((info + j)->name, "") != 0; j++, i += 100) // ÿ��4��
		{
			load_file_info(i, 95 + 100 * (j / 4), info + j, pic_flag);
			if ((j + 1) % 4 == 0)
				i = 60;
		}
	}

	// ��ҳ��
	rectangle(550, 440, 570, 460);
	draw_left(553, 443); // 10��10��22��22
	rectangle(580, 440, 600, 460);
	draw_right(583, 443); // 30��10��42��22
	puthz(550, 462, "��ǰҳ", 12, 2, WHITE);
	char str_page[4];
	itoa(page + 1, str_page, 10); // page��0��ʼ����ʾʱ��1��ʼ
	outtextxy(600, 465, str_page);
}

// ����һ���ļ�
void load_file_info(int x, int y, struct file_info *info, int pic_flag)
{
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
	setcolor(WHITE);
	settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
	if (pic_flag == 0)
	{
		outtextxy(140, y, info->name); // ����
		outtextxy(240, y, info->time); // �޸�����
	}

	// ����
	unsigned char flag, flag_4;
	flag = info->flag;
	flag_4 = get_bit(flag, 0) * 1 + get_bit(flag, 1) * 2 + get_bit(flag, 2) * 2 * 2 + get_bit(flag, 3) * 2 * 2 * 2;
	for (k = 0; k < 16 && pic_flag == 0; k++)
	{ // ȡǰ4λ

		if (flag_4 == k && flag_4 >= 2) // �˵���
			outtextxy(400, y, file_type_strings[k]);
	}
	// ��ʾͼ��
	int x1 = x;
	int y1 = y;
	if(pic_flag == 1)
	{
		x1 = x + 20;
		y1 = y + 5;
	}
	switch (flag_4)
	{
	case 2:
	{
		draw_file(x1, y1, pic_flag);
		break;
	}
	case 3:
	{
		draw_txt(x1, y1, pic_flag);
		break;
	}
	case 4:
	{
		draw_c(x1, y1, pic_flag);
		break;
	}
	case 5:
	{
		draw_cpp(x1, y1, pic_flag);
		break;
	}
	case 6:
	{
		draw_h(x1, y1, pic_flag);
		break;
	}
	case 7:
	{
		draw_obj(x1 + 10, y1 + 15, pic_flag);
		break;
	}
	case 8:
	{
		draw_exe(x1, y1, pic_flag);
		break;
	}
	case 9:
	{
		draw_jpg(x1, y1, pic_flag);
		break;
	}
	case 10:
	{
		draw_png(x1, y1, pic_flag);
		break;
	}
	case 11:
	{
		draw_doc(x1, y1, pic_flag);
		break;
	}
	case 12:
	{
		draw_xls(x1, y1, pic_flag);
		break;
	}
	case 13:
	{
		draw_ppt(x1, y1, pic_flag);
		break;
	}
	case 14:
	{
		draw_pdf(x1, y1, pic_flag);
		break;
	}
	case 15:
	{
		draw_other(x1, y1, pic_flag);
		break;
	}
	}

	setcolor(WHITE);
	// ��С
	if (pic_flag == 0)
		outtextxy(540, y, info->size);
	else if(pic_flag == 1)
	{
		outtextxy(x1 + 5, y1 + 60, info->name);
	}			

	// if (strcmp(chosen_name, (info + j)->name) == 0 && (info + j)->name != 0)
	if (get_bit(info->flag, 7) == 1)
	{
		setcolor(YELLOW);
		if (pic_flag == 0)
			rectangle(x, y - 4, 640, y + 14);
	}
}

void clearRectangle(int x1, int y1, int x2, int y2, unsigned char color) // ���ָ����������
{
	setfillstyle(SOLID_FILL, color);
	bar(x1, y1, x2, y2);
}

// �����˵���ԭ������������ѧ������Ϊ���İ棬���ѡ������𣬵���ⲿ���𣬲˵�������x����ĳ������жϣ��Ż�����һ����룩���ı���x,y�ĺ��壩��ȡ��record����������son_menu����
int drop_down_menu(int x, int y, int wide, int h, int n, int lettersize, char **msgs, int lightcolor, int darkcolor, int language, int son_menu)
{
	int i;					   // ѭ������
	int now_mouse_on = n + 1;  // �����������
	int last_mouse_on = n + 1; // �ղ����������
	int selected_index = -1;   // ���ڴ洢ѡ�е�ѡ������
	clrmous(MouseX, MouseY);

	// �����˵�λ�ã�ʹ֮λ����Ļ��
	if (y + n * h > 470)
		y = y - n * h;
	if (x + wide > 630)
		x = x - wide;

	setfillstyle(SOLID_FILL, darkcolor);
	bar(x, y, x + wide, y + n * h);
	setcolor(lightcolor); // ������ɫ
	if (language == 1)
		settextstyle(DEFAULT_FONT, HORIZ_DIR, lettersize);
	for (i = 0; i < n; i++)
	{
		if (language == 0)
			puthz(x + 10, y + i * h + 5, msgs[i], lettersize, 2, lightcolor);
		else if (language == 1)
			outtextxy(x + 10, y + i * h + 5, msgs[i]);
	}

	while (1)
	{
		newmouse(&MouseX, &MouseY, &press);

		for (i = 0; i < n; i++)
		{
			int result = mouse_press(x, y + i * h, x + wide, y + (i + 1) * h); // ��ֹ��ε���
			if (result == 2)
			{
				now_mouse_on = i;
				if (last_mouse_on != i) // ����ղ���겻����һ��
				{
					MouseS = 1;
					clrmous(MouseX, MouseY);

					// ����һ������
					setfillstyle(SOLID_FILL, LIGHTGRAY);
					bar(x, y + i * h, x + wide, y + (i + 1) * h);
					if (language == 1)
					{
						setcolor(lightcolor);
						settextstyle(DEFAULT_FONT, HORIZ_DIR, lettersize);
						outtextxy(x + 10, y + i * h + 5, msgs[i]);
					}
					else if (language == 0)
						puthz(x + 10, y + i * h + 5, msgs[i], lettersize, 2, lightcolor);
				}
			}
			else if (result == 1) // ���
			{
				selected_index = i; // ��¼ѡ�е�ѡ������
				clrmous(MouseX, MouseY);
				MouseS = 0;
				return selected_index;
			}
		}

		// ���ղŵ�ȡ������
		if (now_mouse_on != last_mouse_on && last_mouse_on != n + 1)
		{
			clrmous(MouseX, MouseY);
			setfillstyle(SOLID_FILL, darkcolor);
			bar(x, y + last_mouse_on * h, x + wide, y + (last_mouse_on + 1) * h);
			if (language == 1)
			{
				setcolor(lightcolor);
				settextstyle(DEFAULT_FONT, HORIZ_DIR, lettersize);
				outtextxy(x + 10, y + last_mouse_on * h + 5, msgs[last_mouse_on]);
			}
			else if (language == 0)
				puthz(x + 10, y + last_mouse_on * h + 5, msgs[last_mouse_on], lettersize, 2, lightcolor);
		}
		last_mouse_on = now_mouse_on;

		if (mouse_press_out(x, y, x + wide, y + n * h)) // ������������
		{
			selected_index = -1;
			clrmous(MouseX, MouseY);
			MouseS = 0;
			return selected_index;
		}

		if (detect_m(x, y, x + wide, y + n * h) == 0) // ������������
		{
			now_mouse_on = n + 1;
		}
	}
}

void loading(void *buffer) // �����С�����
{
	int size; // ���ڵ���ͼ��Ĵ�С
	size = imagesize(220, 200, 420, 280);
	buffer = malloc(size);
	if (buffer != NULL)
		getimage(220, 200, 420, 280, buffer);
	else
	{
		// perror("ERROR IN REMEMBERING");
		// delay(3000);
		// exit(1);
	}

	clrmous(MouseX, MouseY);
	setfillstyle(SOLID_FILL, LIGHTGRAY);
	bar(220, 200, 420, 280);
	setcolor(BLACK);
	settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
	outtextxy(240, 240, "loading . . .");
}

void loading_ok(void *buffer) // �������
{
	putimage(220, 200, buffer, COPY_PUT);
	free(buffer);
}

// ���½�46*16
void draw_new(int x, int y)
{
	int size = 8;
	setcolor(WHITE);
	circle(x + size, y + size, size);
	setcolor(LIGHTBLUE);
	line(x + size, y + 1, x + size, y + 2 * size - 1);
	line(x + 1, y + size, x + 2 * size - 1, y + size);
	puthz(x + size * 2 + 5, y + size / 2, "�½�", 12, 2, WHITE);
}

// �����м���15*15
void draw_scissor(int x, int y)
{
	int size = 3;
	setcolor(WHITE);
	line(x + size, y, x + size * 3, y + size * 3);
	line(x + size * 4, y, x + size * 2, y + size * 3);
	setcolor(LIGHTBLUE);
	circle(x + size, y + size * 4, size);
	circle(x + size * 4, y + size * 4, size);
}

// ������16*16
void draw_copy(int x, int y)
{
	int size = 4;
	setcolor(LIGHTBLUE);
	rectangle(x + size * 1.5, y, x + size * 4, y + size * 3);
	setcolor(WHITE);
	line(x, y + size, x + size * 1.5, y + size);
	line(x, y + size, x, y + size * 4);
	line(x, y + size * 4, x + size * 2.5, y + size * 4);
	line(x + size * 2.5, y + size * 4, x + size * 2.5, y + size * 3);
}

// ��ճ��16*18
void draw_paste(int x, int y)
{
	int size = 4;
	setcolor(LIGHTBLUE);
	rectangle(x + size * 2, y + size * 1.5, x + size * 4, y + size * 4.5);
	setcolor(WHITE);
	rectangle(x + size * 1.5, y - size * 0.5, x + size * 2.5, y + size * 0.5);
	line(x, y, x + size * 1.5, y);
	line(x + size * 2.5, y, x + size * 3.5, y);
	line(x, y, x, y + size * 4.5);
	line(x, y + size * 4.5, x + size * 2, y + size * 4.5);
	line(x + size * 3.5, y, x + size * 3.5, y + size * 1.5);
}

// ��������20*14
void draw_rename(int x, int y)
{
	int size = 4;
	setcolor(WHITE);
	rectangle(x, y, x + size * 5, y + size * 3.5);
	setcolor(LIGHTBLUE);
	line(x + size * 2.5, y - size * 1, x + size * 4, y - size * 1);
	line(x + size * 3.25, y - size * 1, x + size * 3.25, y + size * 4);
	line(x + size * 2.5, y + size * 4, x + size * 4, y + size * 4);
	line(x + size * 2, y + size * 1, x + size * 1, y + size * 2.5);
	line(x + size * 2, y + size * 1, x + size * 2.5, y + size * 2.5);
	line(x + size * 1.5, y + size * 2, x + size * 2.5, y + size * 2);
}

// ������Ͱ18*18
void draw_trash(int x, int y)
{
	int size = 4;
	setcolor(WHITE);
	line(x, y + size * 0.5, x + size * 4.5, y + size * 0.5);
	line(x + size * 0.5, y + size * 0.5, x + size * 1, y + size * 4.5);
	line(x + size * 4, y + size * 0.5, x + size * 3.5, y + size * 4.5);
	line(x + size * 1, y + size * 4.5, x + size * 3.5, y + size * 4.5);
	line(x + size * 1.75, y + size * 2, x + size * 1.75, y + size * 3.5);
	line(x + size * 2.75, y + size * 2, x + size * 2.75, y + size * 3.5);
	arc(x + size * 2.25, y + size * 0.5, 0, 180, size * 1);
}

// ������75*17.5
void draw_sort(int x, int y)
{
	int size = 5;
	setcolor(WHITE);
	line(x + size * 1.5, y, x + size * 1.5, y + size * 3.5);
	line(x + size * 1.5, y, x, y + size * 1.5);
	line(x + size * 1.5, y, x + size * 3, y + size * 1.5);
	setcolor(LIGHTBLUE);
	line(x + size * 3.5, y, x + size * 3.5, y + size * 3.5);
	line(x + size * 2, y + size * 2, x + size * 3.5, y + size * 3.5);
	line(x + size * 5, y + size * 2, x + size * 3.5, y + size * 3.5);
	puthz(x + size * 7.5, y + size / 2, "����", 12, 2, WHITE);
	setcolor(WHITE);
	line(x + size * 14.5, y + size * 2, x + size * 15, y + size * 2.5);
	line(x + size * 15.5, y + size * 2, x + size * 15, y + size * 2.5);
}

// ���鿴82.5*15
void draw_check(int x, int y)
{
	int size = 5;
	setcolor(WHITE);
	line(x, y, x + size * 5, y);
	line(x, y + size * 1, x + size * 5, y + size * 1);
	line(x, y + size * 2, x + size * 5, y + size * 2);
	line(x, y + size * 3, x + size * 5, y + size * 3);
	puthz(x + size * 7, y + size / 2, "�鿴", 12, 2, WHITE);
	line(x + size * 15.5, y + size * 1, x + size * 16, y + size * 2);
	line(x + size * 16.5, y + size * 1, x + size * 16, y + size * 2);
}

// �����ͷ12*12
void draw_left(int x, int y)
{
	int size = 3;
	setcolor(WHITE);
	line(x, y + size * 2, x + size * 2, y);
	line(x, y + size * 2, x + size * 4, y + size * 2);
	line(x, y + size * 2, x + size * 2, y + size * 4);
}

// ���Ҽ�ͷ12*12
void draw_right(int x, int y)
{
	int size = 3;
	setcolor(WHITE);
	line(x, y + size * 2, x + size * 4, y + size * 2);
	line(x + size * 2, y, x + size * 4, y + size * 2);
	line(x + size * 4, y + size * 2, x + size * 2, y + size * 4);
}

// ���ϼ�ͷ12*12
void draw_up(int x, int y)
{
	int size = 3;
	setcolor(WHITE);
	line(x + size * 2, y, x + size * 2, y + size * 4);
	line(x + size * 2, y, x, y + size * 2);
	line(x + size * 2, y, x + size * 4, y + size * 2);
}

// ��ˢ��12*12
void draw_refresh(int x, int y)
{
	int size = 3;
	int radius = size * 2;
	double start = 30.0 / 180.0 * M_PI;
	setcolor(WHITE);
	arc(x + radius, y + radius, 30, 360, radius);
	line(x + radius + radius * cos(start), y + radius - radius * sin(start), x + radius + radius * cos(start) - size, y + radius - radius * sin(start));
	line(x + radius + radius * cos(start), y + radius - radius * sin(start), x + radius + radius * cos(start), y + radius - radius * sin(start) - size);
}

// ���ļ���
void draw_file(int x, int y, int flag)
{
	int size;
	if (flag == 0) // С
		size = 1.5;
	else if (flag == 1) // ��
		size = 5;
	setfillstyle(SOLID_FILL, BROWN);
	bar(x, y, x + size * 4, y + size * 1.5);
	setfillstyle(SOLID_FILL, YELLOW);
	bar(x, y + size * 1.5, x + size * 10, y + size * 9);
	setcolor(BROWN);
	line(x, y + size * 1.5, x + size * 10, y + size * 1.5);
	line(x, y + size * 9, x + size * 10, y + size * 9);
}

void draw_txt(int x, int y, int flag)
{
	int size;
	if (flag == 0) // С
		size = 2.1;
	else if (flag == 1) // ��
		size = 7;
	setfillstyle(SOLID_FILL, WHITE);
	bar(x, y, x + size * 4, y + size * 5);
	setcolor(DARKGRAY);
	line(x, y, x + size * 3, y);
	line(x, y, x, y + size * 5);
	line(x, y + size * 5, x + size * 4, y + size * 5);
	line(x + size * 4, y + size * 5, x + size * 4, y + size * 1);
	line(x + size * 3, y, x + size * 4, y + size * 1);
	line(x + size * 3, y, x + size * 3, y + size * 1);
	line(x + size * 3, y + size * 1, x + size * 4, y + size * 1);
	line(x + size * 3, y + size * 1, x + size * 3, y + size * 1);
	line(x + size * 0.5, y + size * 1, x + size * 2, y + size * 1);
	line(x + size * 0.5, y + size * 1.5, x + size * 3, y + size * 1.5);
	line(x + size * 0.5, y + size * 2, x + size * 3, y + size * 2);
	line(x + size * 0.5, y + size * 2.5, x + size * 3, y + size * 2.5);
	line(x + size * 0.5, y + size * 3, x + size * 3, y + size * 3);
	line(x + size * 0.5, y + size * 3.5, x + size * 3, y + size * 3.5);
	line(x + size * 0.5, y + size * 4, x + size * 3, y + size * 4);
	line(x + size * 0.5, y + size * 4.5, x + size * 3, y + size * 4.5);
}
void draw_c(int x, int y, int flag)
{
	int size;
	if (flag == 0) // С
		size = 2.1;
	else if (flag == 1) // ��
		size = 7;
	setfillstyle(SOLID_FILL, WHITE);
	bar(x, y, x + size * 4, y + size * 5);
	setcolor(DARKGRAY);
	line(x, y, x + size * 3, y);
	line(x, y, x, y + size * 5);
	line(x, y + size * 5, x + size * 4, y + size * 5);
	line(x + size * 4, y + size * 5, x + size * 4, y + size * 1);
	line(x + size * 3, y, x + size * 5, y + size * 1);
	line(x + size * 3, y, x + size * 3, y + size * 1);
	line(x + size * 3, y + size * 1, x + size * 3, y + size * 1);
	setfillstyle(SOLID_FILL, BLUE);
	bar(x + size * 1, y + size * 1.4, x + size * 2.6, y + size * 1.8);
	bar(x + size * 0.8, y + size * 1.8, x + size * 1.4, y + size * 3);
	bar(x + size * 1, y + size * 3, x + size * 1.6, y + size * 3.4);
	bar(x + size * 1.4, y + size * 3.2, x + size * 2.4, y + size * 3.6);
	bar(x + size * 2.2, y + size * 1.8, x + size * 2.6, y + size * 2);
	bar(x + size * 2.2, y + size * 3, x + size * 2.6, y + size * 3.4);
}

void draw_cpp(int x, int y, int flag)
{
	int size;
	if (flag == 0) // С
		size = 2.6;
	else if (flag == 1) // ��
		size = 7;
	setfillstyle(SOLID_FILL, WHITE);
	bar(x, y, x + size * 4, y + size * 5);
	setcolor(DARKGRAY);
	line(x, y, x + size * 3, y);
	line(x, y, x, y + size * 5);
	line(x, y + size * 5, x + size * 4, y + size * 5);
	line(x + size * 4, y + size * 5, x + size * 4, y + size * 1);
	line(x + size * 3, y, x + size * 5, y + size * 1);
	line(x + size * 3, y, x + size * 3, y + size * 1);
	line(x + size * 3, y + size * 1, x + size * 3, y + size * 1);
	setcolor(BLUE);
	arc(x + size * 2, y + size * 2, 90, 270, size * 0.8);
	line(x + size * 2.8, y + size * 2, x + size * 3.6, y + size * 2);
	line(x + size * 3.2, y + size * 1.5, x + size * 3.2, y + size * 2.6);
}

void draw_exe(int x, int y, int flag)
{
	int size;
	if (flag == 0) // С
		size = 2.1;
	else if (flag == 1) // ��
		size = 7;
	setfillstyle(SOLID_FILL, WHITE);
	bar(x, y, x + size * 5.8, y + size * 3.6);
	setfillstyle(SOLID_FILL, DARKGRAY);
	bar(x, y, x + size * 5.8, y + size * 0.4);
	setcolor(DARKGRAY);
	line(x, y, x, y + size * 3.6);
	line(x + size * 5.8, y, x + size * 5.8, y + size * 3.6);
	line(x, y + size * 3.6, x + size * 5.8, y + size * 3.6);
	line(x + size * 0.4, y + size * 1, x + size * 1.2, y + size * 1);
	line(x + size * 0.4, y + size * 1.6, x + size * 1.2, y + size * 1.6);
	line(x + size * 0.4, y + size * 2.2, x + size * 1.2, y + size * 2.2);
	line(x + size * 3.6, y + size * 1, x + size * 3.6, y + size * 1);
	line(x + size * 3.6, y + size * 1.6, x + size * 3.6, y + size * 1.6);
	line(x + size * 3.6, y + size * 2.2, x + size * 3.6, y + size * 2.2);
	setfillstyle(SOLID_FILL, BLUE);
	bar(x + size * 1.4, y + size * 0.8, x + size * 3.4, y + size * 3);
}
void draw_jpg(int x, int y, int flag)
{
	int size;
	if (flag == 0) // С
		size = 2.1;
	else if (flag == 1) // ��
		size = 7;
	setfillstyle(SOLID_FILL, WHITE);
	bar(x, y, x + size * 3.2, y + size * 4.4);
	setcolor(BLUE);
	line(x, y, x + size * 2, y);
	line(x + size * 2, y, x + size * 3.2, y + size * 1.2);
	line(x, y, x, y + size * 4.4);
	line(x, y + size * 4.4, x + size * 3.2, y + size * 4.4);
	line(x + size * 3.2, y + size * 1.2, x + size * 3.2, y + size * 4.4);
	setfillstyle(SOLID_FILL, BLUE);
	bar(x - size * 0.8, y + size * 0.8, x + size * 1.6, y + size * 2);
}
void draw_png(int x, int y, int flag)
{
	int size;
	if (flag == 0) // С
		size = 2.1;
	else if (flag == 1) // ��
		size = 7;
	setfillstyle(SOLID_FILL, WHITE);
	bar(x, y, x + size * 3.2, y + size * 4.4);
	setcolor(GREEN);
	line(x, y, x + size * 2, y);
	line(x + size * 2, y, x + size * 3.2, y + size * 1.2);
	line(x, y, x, y + size * 4.4);
	line(x, y + size * 4.4, x + size * 3.2, y + size * 4.4);
	line(x + size * 3.2, y + size * 1.2, x + size * 3.2, y + size * 4.4);
	setfillstyle(SOLID_FILL, GREEN);
	bar(x - size * 0.8, y + size * 0.8, x + size * 1.6, y + size * 2);
}
void draw_doc(int x, int y, int flag)
{
	int size;
	if (flag == 0) // С
		size = 2.1;
	else if (flag == 1) // ��
		size = 7;
	setcolor(DARKGRAY);
	line(x, y, x + size * 2.8, y);
	line(x, y, x, y + size * 4.4);
	line(x, y + size * 4.4, x + size * 3.6, y + size * 4.4);
	line(x + size * 3.6, y + size * 4.4, x + size * 3.6, y + size * 1);
	line(x + size * 3.6, y + size * 1, x + size * 2.8, y);
	setfillstyle(SOLID_FILL, WHITE);
	floodfill(x + size * 1, y + size * 0.4, DARKGRAY);
	setcolor(BLUE);
	line(x - size * 0.6, y + size * 0.8, x + size * 2.2, y + size * 0.8);
	line(x - size * 0.6, y + size * 0.8, x - size * 0.6, y + size * 3.6);
	line(x - size * 0.6, y + size * 3.6, x + size * 2.2, y + size * 3.6);
	line(x + size * 2.2, y + size * 3.6, x + size * 2.2, y + size * 0.8);
	line(x - size * 0.2, y + size * 1.4, x + size * 0.4, y + size * 3);
	line(x + size * 0.4, y + size * 3, x + size * 0.8, y + size * 1.6);
	line(x + size * 0.8, y + size * 1.6, x + size * 1.4, y + size * 3);
	line(x + size * 1.4, y + size * 3, x + size * 1.8, y + size * 1.4);
	setfillstyle(SOLID_FILL, WHITE);
	floodfill(x, y + size * 1.5, BLUE);
}
void draw_xls(int x, int y, int flag)
{
	int size;
	if (flag == 0) // С
		size = 2.1;
	else if (flag == 1) // ��
		size = 7;
	setcolor(DARKGRAY);
	line(x, y, x + size * 2.8, y);
	line(x, y, x, y + size * 4.4);
	line(x, y + size * 4.4, x + size * 3.6, y + size * 4.4);
	line(x + size * 3.6, y + size * 4.4, x + size * 3.6, y + size * 1);
	line(x + size * 3.6, y + size * 1, x + size * 2.8, y);
	setfillstyle(SOLID_FILL, WHITE);
	floodfill(x + size * 1, y + size * 0.4, DARKGRAY);
	setcolor(GREEN);
	line(x - size * 0.6, y + size * 0.8, x + size * 2.2, y + size * 0.8);
	line(x - size * 0.6, y + size * 0.8, x - size * 0.6, y + size * 3.6);
	line(x - size * 0.6, y + size * 3.6, x + size * 2.2, y + size * 3.6);
	line(x + size * 2.2, y + size * 3.6, x + size * 2.2, y + size * 0.8);
	arc(x + size * 0.8, y + size * 1.8, 0, 180, size * 0.6);
	line(x + size * 0.2, y + size * 1.8, x + size * 1.4, y + size * 2.6);
	arc(x + size * 0.8, y + size * 2.6, 180, 360, size * 0.6);
	/*line(x-size*0.2,y+size*1.4,x+size*0.4,y+size*3);
	line(x+size*0.4,y+size*3,x+size*0.8,y+size*1.6);
	line(x+size*0.8,y+size*1.6,x+size*1.4,y+size*3);
	line(x+size*1.4,y+size*3,x+size*1.8,y+size*1.4);*/
	setfillstyle(SOLID_FILL, WHITE);
	floodfill(x, y + size * 1.5, GREEN);
}
void draw_ppt(int x, int y, int flag)
{
	int size;
	if (flag == 0) // С
		size = 2.1;
	else if (flag == 1) // ��
		size = 7;
	setcolor(DARKGRAY);
	line(x, y, x + size * 2.8, y);
	line(x, y, x, y + size * 4.4);
	line(x, y + size * 4.4, x + size * 3.6, y + size * 4.4);
	line(x + size * 3.6, y + size * 4.4, x + size * 3.6, y + size * 1);
	line(x + size * 3.6, y + size * 1, x + size * 2.8, y);
	setfillstyle(SOLID_FILL, WHITE);
	floodfill(x + size * 1, y + size * 0.4, DARKGRAY);
	setcolor(RED);
	line(x - size * 0.6, y + size * 0.8, x + size * 2.2, y + size * 0.8);
	line(x - size * 0.6, y + size * 0.8, x - size * 0.6, y + size * 3.6);
	line(x - size * 0.6, y + size * 3.6, x + size * 2.2, y + size * 3.6);
	line(x + size * 2.2, y + size * 3.6, x + size * 2.2, y + size * 0.8);
	line(x + size * 0.2, y + size * 1.4, x + size * 0.2, y + size * 3);
	arc(x + size * 0.2, y + size * 1.8, -90, 90, size * 0.4);
	setfillstyle(SOLID_FILL, WHITE);
	floodfill(x, y + size * 1.5, RED);
}
void draw_pdf(int x, int y, int flag)
{
	int size;
	if (flag == 0) // С
		size = 2.1;
	else if (flag == 1) // ��
		size = 7;
	setfillstyle(SOLID_FILL, RED);
	bar(x, y, x + size * 4.8, y + size * 4.8);
	setcolor(WHITE);
	line(x + size * 2.2, y + size * 0.8, x + size * 2.2, y + size * 3.2);
	arc(x + size * 2.2, y + size * 1.4, -90, 90, size * 0.6);
	arc(x + size * 2.2, y + size * 2.8, 90, 270, size * 0.4);
}
void draw_h(int x, int y, int flag)
{
	int size;
	if (flag == 0) // С
		size = 2.1;
	else if (flag == 1) // ��
		size = 7;
	setfillstyle(SOLID_FILL, WHITE);
	bar(x, y, x + size * 3.8, y + size * 4.8);
	setcolor(DARKGRAY);
	line(x, y, x + size * 3.8, y);
	line(x + size * 3.8, y, x + size * 3.8, y + size * 4.8);
	line(x + size * 3.8, y + size * 4.8, x, y + size * 4.8);
	line(x, y + size * 4.8, x, y);
	line(x + size * 1, y + size * 1, x + size * 3, y + size * 1);
	line(x + size * 1, y + size * 1.6, x + size * 3, y + size * 1.6);
	setfillstyle(SOLID_FILL, RED);
	bar(x + size * 0.8, y + size * 2.6, x + size * 4.4, y + size * 4.4);
	setcolor(WHITE);
	line(x + size * 2.8, y + size * 3.2, x + size * 2.8, y + size * 4.2);
	line(x + size * 2.8, y + size * 3.6, x + size * 3.6, y + size * 3.6);
	line(x + size * 3.6, y + size * 3.2, x + size * 3.6, y + size * 4.2);
}

void draw_obj(int x, int y, int flag)
{

	if (flag == 0) // С
	{
		bmp_convert("C:\\PROJECT\\src\\Images\\BMP\\obj.bmp", "C:\\PROJECT\\src\\Images\\DBM\\obj.dbm");
		show_dbm(x - 8, y - 18, "C:\\PROJECT\\src\\Images\\DBM\\obj.dbm", 0);
	}

	else if (flag == 1) // ��
	{
		bmp_convert("C:\\PROJECT\\src\\Images\\BMP\\obj2.bmp", "C:\\PROJECT\\src\\Images\\DBM\\obj2.dbm");
		show_dbm(x, y, "C:\\PROJECT\\src\\Images\\DBM\\obj2.dbm", 0);
	}
}

void draw_other(int x, int y, int flag)
{
	int size;
	if (flag == 0) // С
		size = 2.1;
	else if (flag == 1) // ��
		size = 7;
	setfillstyle(SOLID_FILL, WHITE);
	bar(x, y, x + size * 4, y + size * 5);
	setcolor(DARKGRAY);
	line(x, y, x + size * 3, y);
	line(x, y, x, y + size * 5);
	line(x, y + size * 5, x + size * 4, y + size * 5);
	line(x + size * 4, y + size * 5, x + size * 4, y + size * 1);

	line(x + size * 3, y, x + size * 4, y + size * 1);
	line(x + size * 3, y, x + size * 3, y + size * 1);
	line(x + size * 3, y + size * 1, x + size * 4, y + size * 1);
}