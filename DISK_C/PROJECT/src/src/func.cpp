#include "include.h"

void build(struct file_info *info, int x, int y)
{
	char *file_type_strings[] =
		{

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

		};
	char *now_path = NULL;
	char buffer[1024] = {0}, name[13]; // buffer用于储存新的路径，name是新建文件名
	// 画出可选选项框
	int type_index; // 记录类型索引
	press = 0;
	delay(200);
	type_index = drop_down_menu(x, y, 90, 15, 13, 1, file_type_strings, WHITE, DARKGRAY, 1, 0);

	if (type_index == -1 || type_index > 12)
	{
		return;
	}

	// 获取当前工作目录
	char *result = getcwd(buffer, sizeof(buffer));
	if (result = NULL)
	{
		perror("fail to get current path");
		return;
	}
	// 构建文件名
	if (type_index != 0)
	{
		// 文件类型：添加扩展名
		strcpy(name, "NEWFILE");
		if (strlen(file_type_strings[type_index]) > 0)
		{
			strcat(name, ".");
			strcat(name, file_type_strings[type_index]);
		}
	}
	else if (type_index != -1)
	{
		// 目录类型
		strcpy(name, "NEWDIR");
		if (strlen(file_type_strings[type_index]) > 0)
		{
			strcat(name, file_type_strings[type_index]);
		}
	}

	// 整合完整路径
	now_path = get_file_path(buffer, name);
	if (now_path == NULL)
	{
		fprintf(stderr, "fail to build full path\n");
		return;
	}

	// 如果新建的是文件夹
	if (type_index == 0)
	{
		if (mkdir(now_path) != 0)
		{
			perror("fail to new dir");
			free(now_path);
			return;
		}
	}
	// 如果新建的是文件
	else if (type_index != -1)
	{
		FILE *file = fopen(now_path, "w");
		if (file == NULL)
		{
			printf("fail to new file: %s\n", now_path);
			perror("fail to new file");
			free(now_path);
			return;
		}
		fclose(file);
	}
	free(now_path);
}

// void frename(struct file_info *info)
// {
// 	settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
// 	char new_name[13] = {0};
// 	int wc_select;
// 	char *suffix; // 后缀
// 	char *file_type_strings[] =
// 		{
// 			"FOLD",
// 			"TXT",
// 			"C",
// 			"CPP",
// 			"H",
// 			"OBJ",
// 			"EXE",
// 			"JPG",
// 			"PNG",
// 			"DOC",
// 			"XLS",
// 			"PPT",
// 			"PDF",
// 		};
// 	wc_select = is_selected(info) - 1; // 记录哪个文件被选中了
// 	if (wc_select == -1)
// 		return;
// 	// char bd[10] = {0};
// 	int board = 0; // 记录键盘操作
// 	int result = 0;
// 	suffix = file_type_strings[get_file_type((info + wc_select)->name)];
// 	setcolor(RED);
// 	outtextxy(120, 95 + wc_select * 20, (info + wc_select)->name); // 选中的文件名字先变为红色标亮
// 	clear_keyboard_buffer();
// 	// 主循环
// 	while (1)
// 	{
// 		newmouse(&MouseX, &MouseY, &press);
// 		int i = mouse_press_out(120, 95 + wc_select * 20, 200, 115 + wc_select * 20); // 判断是否点击了别的区域
// 		if (i == 1)
// 		{
// 			setcolor(WHITE);
// 			outtextxy(120, 95 + wc_select * 20, (info + wc_select)->name);
// 			return;
// 		}
// 		board = getbuffer_keybd(new_name, 10);
// 		// 如果选中点击重命名后输入删除，则名字部分覆盖等待输入新名字
// 		if (board == 1)
// 		{
// 			bar(120, 95 + wc_select * 20, 200, 115 + wc_select * 20);
// 			outtextxy(120, 95 + wc_select * 20, new_name);
// 			while (1)
// 			{
// 				newmouse(&MouseX, &MouseY, &press);
// 				// 获取键盘输入 (是否要设置延迟等待输入完全？)
// 				result = getbuffer_keybd(new_name, 13);
// 				if (result == 1)
// 				{
// 					bar(120, 95 + wc_select * 20, 200, 115 + wc_select * 20);
// 					outtextxy(120, 95 + wc_select * 20, new_name);
// 				}
// 				else if (result == 2)
// 				{
// 					// 删除后，输入新名字后按下回车
// 					if (strlen(new_name) > 0)
// 					{
// 						// 执行重命名操作
// 						rename((info + wc_select)->name, new_name);
// 						strcpy((info + wc_select)->name, new_name);
// 						strcat((info + wc_select)->name, ".");
// 						strcat((info + wc_select)->name, suffix);
// 						setcolor(WHITE);
// 						outtextxy(120, 95 + wc_select * 20, (info + wc_select)->name);
// 						return;
// 					}
// 					// 删除后，如果没有输入就按下回车，则显示原来的名字
// 					else
// 					{
// 						setcolor(WHITE);
// 						outtextxy(120, 95 + wc_select * 20, (info + wc_select)->name);
// 						return;
// 					}
// 				}
// 				//  删除后没有检测到输入 则保持原界面
// 				else if (result == 0)
// 				{
// 					delay(3);
// 					continue;
// 				}
// 			}
// 		}
// 		// 如果选中点击重命名后没有输入，则保持原界面
// 		else if (board == 0)
// 		{
// 			delay(3);
// 			continue;
// 		}
// 		// 如果选中点击重命名后输入回车则显示旧名字
// 		else if (board == 2)
// 		{
// 			outtextxy(120, 95 + wc_select * 20, (info + wc_select)->name);
// 			return;
// 		}
// 	}
// }

void frename(struct file_info *info)
{
	settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
	char new_name[13] = {0};
	int wc_select;
	char *suffix; // 后缀
	char *file_type_strings[] =
		{
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

	wc_select = is_selected(info) - 1; // 记录哪个文件被选中了
	if (wc_select == -1)
		return;

	// char bd[10] = {0};
	int board = 0; // 记录键盘操作
	int result = 0;
	// strcpy(new_name, (info + wc_select)->name);
	// wc_select += 1;
	suffix = file_type_strings[get_file_type((info + wc_select)->name)];

	setcolor(RED);
	outtextxy(140, 95 + wc_select * 20, (info + wc_select)->name); // 选中的文件名字先变为红色标亮
	clear_keyboard_buffer();

	// 主循环
	while (1)
	{
		newmouse(&MouseX, &MouseY, &press);
		result = getbuffer_keybd(new_name, 8);

		if (result == 1) // 如果有输入
		{
			setfillstyle(SOLID_FILL, BLACK);
			bar(140, 92 + wc_select * 20, 200, 108 + wc_select * 20);
			setcolor(RED);
			outtextxy(140, 95 + wc_select * 20, new_name);
		}
		else if (mouse_press_out(140, 95 + wc_select * 20, 200, 115 + wc_select * 20) || result == 2) // 点击框外或者回车
		{
			// 输入新名字后按下回车
			if (strlen(new_name) > 0)
			{
				// 执行重命名操作

				// strcpy((info + wc_select)->name, new_name);
				if (get_file_type((info + wc_select)->name) != 2) // 文件夹
				{
					strcat(new_name, ".");
					strcat(new_name, suffix);
				}

				if (rename((info + wc_select)->name, new_name) == 0) // 成功
				{
					setcolor(WHITE);
					outtextxy(140, 95 + wc_select * 20, (info + wc_select)->name);
				}
				else
					warn("重命名失败");
				return;
			}
			else
			{
				warn("名称为空！");
				setcolor(WHITE);
				outtextxy(140, 95 + wc_select * 20, (info + wc_select)->name);
				return;
			}
		}
	}
}

void del(struct file_info *info)
{
	// printf("removing");
	int wc_select = is_selected(info) - 1; // 记录哪个文件被选中了
	char *now_path = NULL;
	char buffer[1024] = {0}; // buffer用于储存新的路径，name是新建文件名
	press = 0;
	// 获取当前工作目录
	char *result = getcwd(buffer, sizeof(buffer));
	if (result == NULL)
	{
		perror("fail to get current path");
		return;
	}
	// 整合完整路径
	now_path = get_file_path(buffer, (info + wc_select)->name);
	if (now_path == NULL)
	{
		fprintf(stderr, "fail to build full path\n");
		return;
	}

	// 真正删除文件
	if (rm_dir(now_path) == 1)
	{
		printf("success to rm dir\n");
	}
	else
	{
		printf("fail to rm dir\n");
	}
}

int copy(struct file_info *info, char *source_path)
{
	if (info == NULL)
	{
		fprintf(stderr, "Invalid parameters\n");
		return -1;
	}
	int wc_select = is_selected(info) - 1; // 记录哪个文件被选中了
	char buffer[1024] = {0};			   // buffer用于储存新的路径，name是新建文件名
	press = 0;
	// 获取当前工作目录
	char *result = getcwd(buffer, sizeof(buffer));
	if (result == NULL)
	{
		perror("fail to get current path");
		return -1;
	}
	// 整合完整路径
	strcpy(source_path, get_file_path(buffer, (info + wc_select)->name));
	if (*source_path == NULL)
	{
		fprintf(stderr, "fail to build full path\n");
		return -1;
	}
	else
	{
		// fprintf(stderr, "copy have done");
		printf("%s", source_path);
		return 0;
	}
}

int paste(char *source_path, int *flag)
{
	printf("src path=%s", source_path);
	if (source_path == NULL)
	{
		fprintf(stderr, "Invalid parameter\n");
		return -1;
	}
	char dest_father_path[1024] = {0}; // 目标所在文件夹绝对路径
	if (getcwd(dest_father_path, sizeof(dest_father_path)) == NULL)
	{
		perror("Failed to get current path");
		return -1;
	}

	if (c_p(source_path, dest_father_path) == -1)
	{
		fprintf(stderr, "Failed to copy file\n");
		return -1;
	}
	else
	{
		// fprintf(stderr, "succeed to copy file\n");
		//  如果之前是剪切操作，则粘贴后还需删除原文件
		if (*flag == 1)
		{
			if (rm_dir(source_path) != 1)
			{
				fprintf(stderr, "Failed to remove source after cut\n");
				return -1;
			}
			*flag = 0;
		}
		return 1;
	}
}

int cut(struct file_info *info, int *flag, char *source_path)
{
	if (copy(info, source_path) != 0) // 当点击剪切图标，先调用复制函数
	{
		// printf("failed to cut");
		return -1;
	}
	int wc_select = is_selected(info) - 1; // 记录哪个文件被选中了
	setcolor(DARKGRAY);
	outtextxy(140, 95 + wc_select * 20, (info + wc_select)->name); // 选中的文件名字先变为灰色

	*flag = 1;
	return 0;
}

int func(struct file_info *info, char *source_path, int *sort_mode, int *UpOrDown, char **sort_menu_p)
{
	// 设置选中状态
	int F = 0;		   // 根据大F的值判断是哪个功能被选中了
	int exit_flag = 0; // 退出循环标志

	setcolor(YELLOW);
	static int result = -1; // 防止多次调用
	static int if_cut = 0;	// 判断之前是否进行的剪切工作，以确认粘贴后是否要进行删除工作

	while (detect_m(0, 37, 365, 62) == 1) // 鼠标在功能栏
	{

		newmouse(&MouseX, &MouseY, &press);
		highlight_detector(NULL, NULL);

		if (mouse_press(5, 37, 60, 62) == 1)
		{
			F = 1; // 选中新建
		}
		else if (mouse_press(60, 37, 85, 62) == 1)
		{
			F = 2; // 选中剪切
		}
		else if (mouse_press(85, 37, 110, 62) == 1)
		{
			F = 3; // 选中复制
		}
		else if (mouse_press(110, 37, 135, 62) == 1)
		{
			F = 4; // 选中粘贴
		}
		else if (mouse_press(135, 37, 165, 62) == 1)
		{
			F = 5; // 选中重命名
		}
		else if (mouse_press(165, 37, 190, 62) == 1)
		{
			F = 6; // 选中删除
		}
		else if (mouse_press(190, 37, 275, 62) == 1)
		{
			F = 7; // 选中排序
		}
		else if (mouse_press(275, 37, 365, 62) == 1)
		{
			F = 8; // 选中查看
		}
		if (F != 0)
		{
			clrmous(MouseX, MouseY);
			break;
		}
	}

	// 如果选中“新建”
	switch (F)
	{
	case 1:
	{
		build(info, 12, 70);
		break;
	}
	case 2: // 剪切
	{
		// printf("cut have done");
		result = cut(info, &if_cut, source_path);
		break;
	}
	case 3: // 复制
	{
		// printf("3");
		result = copy(info, source_path);
		// printf("after copy src=%s", source_path);
		break;
	}
	case 4: // 粘贴
	{
		// printf("4\n");
		if (result == 0)
		{
			// printf("before paste src=%s", source_path);
			if (paste(source_path, &if_cut) != -1)
			{
				// printf("Copy and paste succeeded\n");
			}
			free(source_path);
		}
		result = -1;
		break;
	}
	case 5:
	{
		frename(info);
		break;
	}
	case 6: // 删除
	{
		del(info);
		break;
	}
	case 7:
	{
		result = drop_down_menu(195, 60, 80, 25, 6, 12, sort_menu_p, WHITE, DARKGRAY, 0, 0);
		if (result >= 0 && result <= 3)
			*sort_mode = result;
		else if (result == 4)
			*UpOrDown = 1;
		else if (result == 5)
			*UpOrDown = -1;
		sort(info, *sort_mode, *UpOrDown);
		break;
	}
		// case 7:
		// {
		// 	check();
		// 	break;
		// }

	default:
		break;
	}

	return F;
}
