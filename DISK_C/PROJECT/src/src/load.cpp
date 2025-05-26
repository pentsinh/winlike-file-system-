/********加载页面********/
// #define TEST
//  把界面划分为
//  top顶栏：调整级别，当前路径
//  head上栏：各种功能按钮
//  left左栏：文件结构
//  main主栏：操作板
#include "include.h"

void load_init(char path[1024], struct file_info *info, char history[HISTORY_LENGTH][1024]) // 界面初始化
{
	setbkcolor(BLACK);
	chdir("C:\\PROJECT\\DEVEL"); // 进入开发目录	
	mkdir("BIN"); // 创建回收站，RUBBISHBIN太长了。。。
	chdir("C:\\PROJECT\\DEVEL\\BIN");
	mkdir("BIN_0"); // 0为暂存
	mkdir("BIN_1");// 创建回收站子目录
	mkdir("BIN_2");// 创建回收站子目录
	mkdir("BIN_3");// 创建回收站子目录
	mkdir("BIN_4");// 创建回收站子目录
	mkdir("BIN_5");// 创建回收站子目录
	chdir("C:\\PROJECT");
	if (getcwd(path, sizeof(path) * 1024) == NULL) // 获取当前路径
	{
		perror("Can't get current dir");
		return;
	}
	strcpy(history[0], path); // 路径操作历史开始记录
							  // 加载界面
							  // load_all(info);
}

void load_all(char path[1024], struct file_info *info, struct My_filenode *root, char *target, int mode, char preference[3][1024], int page, int pic_flag) // 加载界面
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

	// 操作
	draw_left(10, 10);	  // 10，10，22，22
	draw_right(30, 10);	  // 30，10，42，22
	draw_up(50, 10);	  // 50，10，62，22
	draw_refresh(70, 10); // 70，10，82，22
#ifdef TEST
	setcolor(YELLOW);
	rectangle(5, 5, 25, 25);
	rectangle(25, 5, 45, 25);
	rectangle(45, 5, 65, 25);
	rectangle(65, 5, 85, 25);
#endif

	// 路径
	setcolor(WHITE);
	settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
	rectangle(90, 10, 500, 30);
	outtextxy(92, 15, path);

	// 搜索
	if (mode == 1) // 搜索模式
	{
		setfillstyle(SOLID_FILL, BLACK);
		bar(540, 10, 620, 30);
		rectangle(540, 10, 620, 30);
		setcolor(WHITE);
		settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
		outtextxy(542, 12, target);
	}
	else if (mode == 0 && strcmp(target, "") == 0) // 一般模式，并且搜索目标为空
	{
		clrmous(MouseX, MouseY);
		setfillstyle(SOLID_FILL, BLACK);
		bar(540, 10, 620, 30);
		rectangle(540, 10, 620, 30);
		puthz(542, 12, "搜索", 16, 2, WHITE);
	}
	else if (mode == 0 && strcmp(target, "") != 0) // 处于一般模式时，搜索目标不为空
	{
		setfillstyle(SOLID_FILL, BLACK);
		bar(540, 10, 620, 30);
		setcolor(WHITE);
		settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
		outtextxy(542, 12, target);
	}

	// 退出小叉叉
	line(620, 0, 640, 20);
	line(640, 0, 620, 20);
}

void load_head(int mode) //(10,40)(630,60)
{
	setcolor(WHITE);
	// 新建
	draw_new(10, 42); // 10，42，56，58
	// 剪切
	draw_scissor(65, 42); // 65，42，80，57
	// 复制
	draw_copy(90, 42); // 90，42，106，58
	// 粘贴
	draw_paste(115, 42); // 115，42，131，60
	//  重命名
	draw_rename(140, 42); // 140，42，160，56
	// 删除
	draw_trash(170, 42); // 170, 42，188，60
	// 排序
	draw_sort(195, 42);	 // 195, 42，270，59.5
						 // 查看
	draw_check(280, 42); // 280，42，362.5，57
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
	// int i;			// 循环变量
	int layer = 0; // 目录的层数，设c盘问第0层
	int pen_x = 0; // 画笔位置
	int pen_y = 70;
	struct My_filenode *p;
	setcolor(WHITE);
	settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
	// outtextxy(pen_x, pen_y, ">");
	// outtextxy(pen_x + 10, pen_y, root->name);
	if (get_bit(root->flag, 4) == 1 && root->son_list_head != NULL) // 如果目录展开
	{
		load_left_assist(root->son_list_head, layer, pen_x + 10, &pen_y);
	}
	line(0, 408, 100, 408);
	puthz(25, 410, "最近打开", 12, 2, WHITE);
	for (int i = 0; i < 3; i++)
	{
		if (strcmp(preference[i], "\0") != 0)
			outtextxy(10, 430 + i * 10, path_to_name(preference[i]));
		// outtextxy(10, 430 + i * 10, preference[i]);
	}
}
void load_left_assist(struct My_filenode *head, int layer, int pen_x, int *pen_y) //(加载左栏辅助函数)加载出传入地址的所有子目录和后面的同级目录
{

	*pen_y += 10;
	int y = *pen_y;
	if (y > 400)
		return;
	outtextxy(pen_x, *pen_y, ">");
	outtextxy(pen_x + 10, *pen_y, head->name);
	if (get_bit(head->flag, 4) == 1 && head->son_list_head != NULL && layer < 2) // 如果子目录可见
	{
		load_left_assist(head->son_list_head, layer + 1, pen_x + 10, pen_y);
	}

	if (head->next != NULL) // 加载后面的目录
	{
		load_left_assist(head->next, layer, pen_x, pen_y);
	}
}

void load_main(struct file_info *info, int mode, int page, int pic_flag) //(120,70)(640,480)
{
	int i; // 像素
	int j; // 文件序号
	settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);

	// 为了开发方便，开发阶段将格子画出来
	// for (i = 90; i < 440; i += 20)
	// 	line(120, i, 640, i);

	if (pic_flag == 0) // 小图标
	{
		puthz(120, 70, "名称", 16, 2, WHITE);
		line(320, 70, 320, 90);

		puthz(240, 70, "修改日期", 16, 2, WHITE);
		line(400, 70, 400, 90);

		puthz(400, 70, "类型", 16, 2, WHITE);
		line(540, 70, 540, 90);

		puthz(540, 70, "大小", 16, 2, WHITE);

		for (j = 0, i = 95; j < INFO_LENGTH && strcmp((info + j)->name, "") != 0; j++, i += 20)
		{
			load_file_info(120, i, info + j, pic_flag);
		}
	}
	else if (pic_flag == 1) // 大图标
	{
		for (j = 0, i = 160; j < INFO_LENGTH && strcmp((info + j)->name, "") != 0; j++, i += 100) // 每行4个
		{
			load_file_info(i, 95 + 100 * (j / 4), info + j, pic_flag);
			if ((j + 1) % 4 == 0)
				i = 60;
		}
	}

	// 翻页键
	rectangle(550, 440, 570, 460);
	draw_left(553, 443); // 10，10，22，22
	rectangle(580, 440, 600, 460);
	draw_right(583, 443); // 30，10，42，22
	puthz(550, 462, "当前页", 12, 2, WHITE);
	char str_page[4];
	itoa(page + 1, str_page, 10); // page从0开始，显示时从1开始
	outtextxy(600, 465, str_page);
}

// 加载一条文件
void load_file_info(int x, int y, struct file_info *info, int pic_flag)
{
	int k; // 循环变量
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
		outtextxy(140, y, info->name); // 名称
		outtextxy(240, y, info->time); // 修改日期
	}

	// 类型
	unsigned char flag, flag_4;
	flag = info->flag;
	flag_4 = get_bit(flag, 0) * 1 + get_bit(flag, 1) * 2 + get_bit(flag, 2) * 2 * 2 + get_bit(flag, 3) * 2 * 2 * 2;
	for (k = 0; k < 16 && pic_flag == 0; k++)
	{ // 取前4位

		if (flag_4 == k && flag_4 >= 2) // 此电脑
			outtextxy(400, y, file_type_strings[k]);
	}
	// 显示图标
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
	// 大小
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

void clearRectangle(int x1, int y1, int x2, int y2, unsigned char color) // 清空指定矩形区域
{
	setfillstyle(SOLID_FILL, color);
	bar(x1, y1, x2, y2);
}

// 下拉菜单，原版来自杨征坷学长，此为中文版，点击选项后收起，点击外部收起，菜单增加了x方向的出画面判断（优化掉了一半代码）（改变了x,y的含义），取消record参数，增加son_menu参数
int drop_down_menu(int x, int y, int wide, int h, int n, int lettersize, char **msgs, int lightcolor, int darkcolor, int language, int son_menu)
{
	int i;					   // 循环变量
	int now_mouse_on = n + 1;  // 现在鼠标在哪
	int last_mouse_on = n + 1; // 刚才鼠标在哪里
	int selected_index = -1;   // 用于存储选中的选项索引
	clrmous(MouseX, MouseY);

	// 调整菜单位置，使之位于屏幕内
	if (y + n * h > 470)
		y = y - n * h;
	if (x + wide > 630)
		x = x - wide;

	setfillstyle(SOLID_FILL, darkcolor);
	bar(x, y, x + wide, y + n * h);
	setcolor(lightcolor); // 字体颜色
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
			int result = mouse_press(x, y + i * h, x + wide, y + (i + 1) * h); // 防止多次调用
			if (result == 2)
			{
				now_mouse_on = i;
				if (last_mouse_on != i) // 如果刚才鼠标不在这一条
				{
					MouseS = 1;
					clrmous(MouseX, MouseY);

					// 将这一条高亮
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
			else if (result == 1) // 点击
			{
				selected_index = i; // 记录选中的选项索引
				clrmous(MouseX, MouseY);
				MouseS = 0;
				return selected_index;
			}
		}

		// 将刚才的取消高亮
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

		if (mouse_press_out(x, y, x + wide, y + n * h)) // 如果鼠标点击外面
		{
			selected_index = -1;
			clrmous(MouseX, MouseY);
			MouseS = 0;
			return selected_index;
		}

		if (detect_m(x, y, x + wide, y + n * h) == 0) // 如果鼠标在外面
		{
			now_mouse_on = n + 1;
		}
	}
}

void loading(void *buffer) // 加载中。。。
{
	int size; // 被遮挡的图像的大小
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

void loading_ok(void *buffer) // 加载完成
{
	putimage(220, 200, buffer, COPY_PUT);
	free(buffer);
}

// 画新建46*16
void draw_new(int x, int y)
{
	int size = 8;
	setcolor(WHITE);
	circle(x + size, y + size, size);
	setcolor(LIGHTBLUE);
	line(x + size, y + 1, x + size, y + 2 * size - 1);
	line(x + 1, y + size, x + 2 * size - 1, y + size);
	puthz(x + size * 2 + 5, y + size / 2, "新建", 12, 2, WHITE);
}

// 画剪切剪刀15*15
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

// 画复制16*16
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

// 画粘贴16*18
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

// 画重命名20*14
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

// 画垃圾桶18*18
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

// 画排序75*17.5
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
	puthz(x + size * 7.5, y + size / 2, "排序", 12, 2, WHITE);
	setcolor(WHITE);
	line(x + size * 14.5, y + size * 2, x + size * 15, y + size * 2.5);
	line(x + size * 15.5, y + size * 2, x + size * 15, y + size * 2.5);
}

// 画查看82.5*15
void draw_check(int x, int y)
{
	int size = 5;
	setcolor(WHITE);
	line(x, y, x + size * 5, y);
	line(x, y + size * 1, x + size * 5, y + size * 1);
	line(x, y + size * 2, x + size * 5, y + size * 2);
	line(x, y + size * 3, x + size * 5, y + size * 3);
	puthz(x + size * 7, y + size / 2, "查看", 12, 2, WHITE);
	line(x + size * 15.5, y + size * 1, x + size * 16, y + size * 2);
	line(x + size * 16.5, y + size * 1, x + size * 16, y + size * 2);
}

// 画左箭头12*12
void draw_left(int x, int y)
{
	int size = 3;
	setcolor(WHITE);
	line(x, y + size * 2, x + size * 2, y);
	line(x, y + size * 2, x + size * 4, y + size * 2);
	line(x, y + size * 2, x + size * 2, y + size * 4);
}

// 画右箭头12*12
void draw_right(int x, int y)
{
	int size = 3;
	setcolor(WHITE);
	line(x, y + size * 2, x + size * 4, y + size * 2);
	line(x + size * 2, y, x + size * 4, y + size * 2);
	line(x + size * 4, y + size * 2, x + size * 2, y + size * 4);
}

// 画上箭头12*12
void draw_up(int x, int y)
{
	int size = 3;
	setcolor(WHITE);
	line(x + size * 2, y, x + size * 2, y + size * 4);
	line(x + size * 2, y, x, y + size * 2);
	line(x + size * 2, y, x + size * 4, y + size * 2);
}

// 画刷新12*12
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

// 画文件夹
void draw_file(int x, int y, int flag)
{
	int size;
	if (flag == 0) // 小
		size = 1.5;
	else if (flag == 1) // 中
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
	if (flag == 0) // 小
		size = 2.1;
	else if (flag == 1) // 中
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
	if (flag == 0) // 小
		size = 2.1;
	else if (flag == 1) // 中
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
	if (flag == 0) // 小
		size = 2.6;
	else if (flag == 1) // 中
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
	if (flag == 0) // 小
		size = 2.1;
	else if (flag == 1) // 中
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
	if (flag == 0) // 小
		size = 2.1;
	else if (flag == 1) // 中
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
	if (flag == 0) // 小
		size = 2.1;
	else if (flag == 1) // 中
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
	if (flag == 0) // 小
		size = 2.1;
	else if (flag == 1) // 中
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
	if (flag == 0) // 小
		size = 2.1;
	else if (flag == 1) // 中
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
	if (flag == 0) // 小
		size = 2.1;
	else if (flag == 1) // 中
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
	if (flag == 0) // 小
		size = 2.1;
	else if (flag == 1) // 中
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
	if (flag == 0) // 小
		size = 2.1;
	else if (flag == 1) // 中
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

	if (flag == 0) // 小
	{
		bmp_convert("C:\\PROJECT\\src\\Images\\BMP\\obj.bmp", "C:\\PROJECT\\src\\Images\\DBM\\obj.dbm");
		show_dbm(x - 8, y - 18, "C:\\PROJECT\\src\\Images\\DBM\\obj.dbm", 0);
	}

	else if (flag == 1) // 中
	{
		bmp_convert("C:\\PROJECT\\src\\Images\\BMP\\obj2.bmp", "C:\\PROJECT\\src\\Images\\DBM\\obj2.dbm");
		show_dbm(x, y, "C:\\PROJECT\\src\\Images\\DBM\\obj2.dbm", 0);
	}
}

void draw_other(int x, int y, int flag)
{
	int size;
	if (flag == 0) // 小
		size = 2.1;
	else if (flag == 1) // 中
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