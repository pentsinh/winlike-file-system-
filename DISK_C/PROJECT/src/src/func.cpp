#include "include.h"

int build(struct file_info *info, int x, int y) //-1失败；0成功
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
		return -1;
	}

	// 获取当前工作目录
	char *result = getcwd(buffer, sizeof(buffer));
	if (result = NULL)
	{
		perror("fail to get current path");
		return -1;
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
		// if (strlen(file_type_strings[type_index]) > 0)
		// {
		// 	strcat(name, file_type_strings[type_index]);
		// }
	}

	// 整合完整路径
	now_path = get_file_path(buffer, name);
	if (now_path == NULL)
	{
		fprintf(stderr, "fail to build full path\n");
		return -1;
	}

	// 如果新建的是文件夹
	if (type_index == 0)
	{
		if (mkdir(now_path) != 0)
		{
			perror("fail to new dir");
			free(now_path);
			return -1;
		}
		else
		{
			free(now_path);
			return 0;
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
			return -1;
		}
		else
		{
			free(now_path);
			fclose(file);
			return 1;
		}
	}
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

int frename(struct file_info *info, struct pro_history history[5], int pic_flag) //-1失败；0成功
{
	settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
	char new_name[13] = {0};
	char old_name[13] = {0}; // 记录旧名字
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
		return -1;

	// char bd[10] = {0};
	int board = 0; // 记录键盘操作
	int result = 0;
	// strcpy(new_name, (info + wc_select)->name);
	// wc_select += 1;
	suffix = file_type_strings[get_file_type((info + wc_select)->name)];
	strcpy(old_name, (info + wc_select)->name); // 记录旧名字

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
					new_history(history, RENAME, get_file_path(getcwd(NULL, 0), old_name), get_file_path(getcwd(NULL, 0), new_name));
					return 0;
				}
				else
				{
					warn("重命名失败");
					return -1;
				}
			}
			else
			{
				warn("名称为空！");
				setcolor(WHITE);
				outtextxy(140, 95 + wc_select * 20, (info + wc_select)->name);
				return -1;
			}
		}
	}
}

int del(struct file_info *info, struct pro_history history[5]) //-1失败；0成功
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
		return -1;
	}
	// 整合完整路径
	now_path = get_file_path(buffer, (info + wc_select)->name);
	if (now_path == NULL)
	{
		fprintf(stderr, "fail to build full path\n");
		return -1;
	}

	// 真正删除文件
	if (c_p(now_path, "C:\\PROJECT\\DEVEL\\BIN\\BIN_0") != -1 && rm_dir(now_path) == 1)
	{
		new_history(history, DELETE, "", now_path); // 记录删除操作
		free(now_path);								// 释放动态分配的内存
		// printf("success to rm dir\n");
		return 0;
	}
	else
	{
		return -1;
		// printf("fail to rm dir\n");
	}
}

int copy(struct file_info *info, char *source_path) //-1失败；0成功
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

int paste(char *source_path, int *flag) //-1失败；1成功
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

int cut(struct file_info *info, int *flag, char *source_path) //-1失败；1成功
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
	return 1;
}

int check(int x, int y, int *pic_flag)
{
	char *choices[] =
		{
			"小图标",
			"大图标"};
	int choice_index; // 记录类型索引
	press = 0;
	delay(200);
	choice_index = drop_down_menu(x, y, 80, 25, 2, 12, choices, WHITE, DARKGRAY, 0, 0);

	if (choice_index != -1)
		*pic_flag = choice_index;
	return 0;
}

int func(struct file_info *info, char *source_path, int *sort_mode, int *UpOrDown, char **sort_menu_p, int *pic_flag)
{
	// 设置选中状态
	int F = 0;							 // 根据大F的值判断是哪个功能被选中了
	int exit_flag = 0;					 // 退出循环标志
	struct pro_history history[5] = {0}; // 操作历史
	for (int i = 0; i < 5; i++)			 // 初始化操作历史
	{
		char bin_path[64] = "C:\\PROJECT\\DEVEL\\BIN\\BIN_"; // 回收站路径
		char buffer[64] = {0};
		strcat(bin_path, itoa(i + 1, buffer, 10)); // 拼接回收站路径
		history[i].num = i + 1;
		history[i].process = -1; // 初始化为-1
		strcpy(history[i].src, "");
		strcpy(history[i].tar, "");
		strcpy(history[i].bin_path, bin_path); // 初始化回收站路径
	}

	setcolor(YELLOW);
	static int result = -1; // 防止多次调用
	static int if_cut = 0;	// 判断之前是否进行的剪切工作，以确认粘贴后是否要进行删除工作

	while (detect_m(0, 37, 365, 62) == 1) // 鼠标在功能栏
	{

		newmouse(&MouseX, &MouseY, &press);
		highlight_detector();

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
		int result_1 = build(info, 12, 70);
		if (result_1 == 0) // 文件夹
		{
			new_history(history, NEWFILE, get_file_path(getcwd(NULL, 0), "NEWFOLD"), "");
			break;
		}
		else if (result_1 == 1)
		{
			new_history(history, NEWFILE, get_file_path(getcwd(NULL, 0), "NEWFILE"), "");
			break;
		}
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
				if (if_cut == 1)
					new_history(history, CUT_PASTE, get_file_path(getcwd(NULL, 0), path_to_name(source_path)), source_path);
				else
					new_history(history, COPY_PASTE, get_file_path(getcwd(NULL, 0), path_to_name(source_path)), source_path);
				// printf("Copy and paste succeeded\n");
			}
			free(source_path);
		}
		if_cut = 0; // 重置剪切标志
		result = -1;
		break;
	}
	case 5:
	{
		frename(info, history, *pic_flag);
		break;
	}
	case 6: // 删除
	{
		del(info, history);
		break;
	}
	case 7: // 排序
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
	case 8: // 查看
	{
		check(280, 70, pic_flag);
		break;
	}
	default:
		break;
	}

	return F;
}

void new_history(struct pro_history history[5], int process, char tar[1024], char src[1024]) // 更新目录操作历史
{
	int i;
	rm_dir("C:\\PROJECT\\DEVEL\\BIN\\BIN_5"); // 删除回收站的最后一个文件

	// 将历史记录向后移动
	for (i = 4; i > 0; i--)
	{
		history[i].num = i + 1; // 更新序号
		strcpy(history[i].tar, history[i - 1].tar);
		history[i].process = history[i - 1].process;
		strcpy(history[i].src, history[i - 1].src);
	}
	strcpy(history[0].tar, tar);
	history[0].process = process;
	strcpy(history[0].src, src);

	rename("C:\\PROJECT\\DEVEL\\BIN\\BIN_0", "C:\\PROJECT\\DEVEL\\BIN\\BIN_1");
	strcpy(history[0].bin_path, "C:\\PROJECT\\DEVEL\\BIN\\BIN_1");
	mkdir("C:\\PROJECT\\DEVEL\\BIN\\BIN_0"); // 创建新的回收站文件夹
}

void undo_pro(struct pro_history history[5]) // 撤销操作
{
	if (history[0].process == -1) // 如果没有操作记录
	{
		warn("没有可撤销的操作");
		return;
	}
	char *bin_path = history[0].bin_path;
	char *src_path = history[0].src;
	char *tar_path = history[0].tar;

	switch (history[0].process)
	{
	case NEWFILE:
		rm_dir(tar_path); // 删除新建的文件或文件夹
		break;
	case CUT_PASTE:
		c_p(get_file_path(tar_path, path_to_name(src_path)), get_father_path(src_path)); // 将剪切的文件或文件夹粘贴到目标路径
		rm_dir(get_file_path(tar_path, path_to_name(src_path)));
		break;
	case COPY_PASTE:
		rm_dir(get_file_path(tar_path, path_to_name(src_path)));
		break;
	case RENAME:
		rename(src_path, tar_path); // 恢复重命名之前的文件或文件夹
	case DELETE:
		c_p(get_file_path(bin_path, path_to_name(src_path)), get_father_path(src_path)); // 将删除的文件或文件夹恢复到目标路径
		rm_dir(get_file_path(bin_path, path_to_name(src_path)));
		break;
	default:
		break;
	}

	history_reset(history[0], 0, "", "", ""); // 清除操作记录
	for (int i = 1; i < 5; i++)				  // 将后面的操作记录向前移动
	{
		history[i - 1].process = history[i].process;
		strcpy(history[i - 1].src, history[i].src);
		strcpy(history[i - 1].tar, history[i].tar);
	}
}

void history_reset(struct pro_history *history, int num, char src[1024], char tar[1024], char bin_path[64]) // 初始化操作历史
{
	history->num = num;
	history->process = -1;
	strcpy(history->src, src);
	strcpy(history->tar, tar);
}
