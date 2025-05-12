// #define TEST

#ifndef TEST
#include "include.h"

// extern void *buffer; // ����

struct menu
{
	char *option;
	struct menu *next;
	struct menu *son_menu_head;
};

void spinOnce(char path[1024], struct file_info *info, int mode, char history[HISTORY_LENGTH][1024], int now_history, int sort_mode, int UpOrDown, char preference[3][1024]) // ����״̬��⺯��
{
	newmouse(&MouseX, &MouseY, &press);
	if (mode == 0)
	{
		getcwd(path, sizeof(path) * 1024);
		// read_dir(path, info);
	}
	sort(info, sort_mode, UpOrDown);

	if (now_history == 0 && strcmp(path, history[now_history]) != 0)
	{
		new_history(history, path);
		get_preference(history, preference);
	}
}

int main()
{
	int gd = DETECT, gm; // ͼ��������ͼ��ģʽ

	struct My_filenode *root;				  // Ŀ¼���ĸ�
	char path[1024];						  // ��ǰ·��
	char history[HISTORY_LENGTH][1024] = {0}; // ������ʷ
	int now_history = 0;					  // ��ǰ��·����history�е�λ�ã�����������
	struct file_info info[10];				  // ����ļ���Ϣ
	int page = 0;							  // ҳ�룬��0��ʼ

	char preference[3][1024] = {0};

	int i; // ѭ������

	char src_path[1024]; // copy�ļ�Դ·��
	int sort_mode = 0;	 // ���򷽷�
	int UpOrDown = 1;	 // ����/����

	char mode = 0;			 // ���Ӵ���ʾģʽ��0Ϊһ��ģʽ��1Ϊ����ģʽ
	char mode_shift = _0to0; // ģʽ�л�
	char srch_tar[16] = {0}; // ����Ŀ��

	int choose_mode = 0; // ���ѡ��ģʽ

	int result; // ������ź�������ֵ����ֹ��ε���

	void *img_buffer; // ͼƬ����

	root = (struct My_filenode *)malloc(sizeof(struct My_filenode));

	initgraph(&gd, &gm, "C:\\BORLANDC\\BGI"); // ��ʼ��ͼ��ģʽ
	power_on();
	welcome();

	tree_make(root, 0); // Ŀ¼����ʼ����
	// printf("Ready to start!\n");

	// buffer = NULL;

	mouseinit();

	if (!login()) // ��½ʧ��
		return 0;
	else // ��½�ɹ�
	{
		MouseS = 0;
		clrmous(MouseX, MouseY);
		cleardevice();

		load_init(path, info, history); // �����ʼ��
		read_dir(path, info, &page);

		spinOnce(path, info, mode, history, now_history, sort_mode, UpOrDown, preference); // ˢ��info
		load_all(path, info, root, srch_tar, mode, preference, page);					   // ��ʾ

		// ����˵���ʼ��
		char sort_menu[6][16] = {"����", "�޸�ʱ��", "����", "��С", "����", "�ݼ�"};
		char **sort_menu_p = (char **)malloc(6 * sizeof(char *));
		for (i = 0; i < 6; i++)
		{
			sort_menu_p[i] = (char *)malloc(16 * sizeof(char));
			strcpy(sort_menu_p[i], sort_menu[i]);
		}

		// �Ҽ��˵���ʼ��
		char RB_menu[4][16] = {
			"����ʽ",
			//"����",
			"�½�",
			"����"};
		char **RB_menu_p = (char **)malloc(4 * sizeof(char *));
		for (i = 0; i < 4; i++)
		{
			RB_menu_p[i] = (char *)malloc(16 * sizeof(char));
			strcpy(RB_menu_p[i], RB_menu[i]);
		}

		char new_menu[13][8] = {
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
		char **new_menu_p = (char **)malloc(13 * sizeof(char *));
		for (i = 0; i < 13; i++)
		{
			new_menu_p[i] = (char *)malloc(16 * sizeof(char));
			strcpy(new_menu_p[i], new_menu[i]);
		}

		while (1)
		{
			// spinOnce(path, info, mode, history, now_history, sort_mode, UpOrDown);
			newmouse(&MouseX, &MouseY, &press);
			highlight_detector(info, root);
			// printf("%d", page);

			if (mouse_press(5, 5, 25, 25) == 1) //|| mouse_press(10, 10, 30, 30) == 4)//������<-����Ŀ¼����
			{
				result = undo_dir(history, &now_history);
				spinOnce(path, info, mode, history, now_history, sort_mode, UpOrDown, preference);
				if (result == 1)
					read_dir(path, info, &page);
				spinOnce(path, info, mode, history, now_history, sort_mode, UpOrDown, preference);
				clrmous(MouseX, MouseY);
				cleardevice();
				load_all(path, info, root, srch_tar, mode, preference, page);
			}
			else if (mouse_press(25, 5, 45, 25) == 1) // || mouse_press(30, 10, 50, 30) == 4)//������->������Ŀ¼����
			{
				result = anti_undo_dir(history, &now_history);
				spinOnce(path, info, mode, history, now_history, sort_mode, UpOrDown, preference);
				if (result == 1)
					read_dir(path, info, &page);
				spinOnce(path, info, mode, history, now_history, sort_mode, UpOrDown, preference);
				clrmous(MouseX, MouseY);
				cleardevice();
				load_all(path, info, root, srch_tar, mode, preference, page);
			}
			else if (mouse_press(45, 5, 65, 25) == 1) //|| mouse_press(50, 10, 70, 30) == 4)//������������һ��Ŀ¼
			{
				result = back(path, history, &now_history);
				spinOnce(path, info, mode, history, now_history, sort_mode, UpOrDown, preference);
				if (result == 1)
					read_dir(path, info, &page);
				spinOnce(path, info, mode, history, now_history, sort_mode, UpOrDown, preference);
				clrmous(MouseX, MouseY);
				cleardevice();
				load_all(path, info, root, srch_tar, mode, preference, page);
			}
			else if (mouse_press(65, 5, 85, 25) == 1) //|| mouse_press(70, 10, 90, 30) == 4)//������ˢ��
			{
				spinOnce(path, info, mode, history, now_history, sort_mode, UpOrDown, preference); // ����path
				read_dir(path, info, &page);
				spinOnce(path, info, mode, history, now_history, sort_mode, UpOrDown, preference); // ����
				clrmous(MouseX, MouseY);
				cleardevice();
				if (mode == 0)
					strcpy(srch_tar, "");
				load_all(path, info, root, srch_tar, mode, preference, page);
			}
			else if (mouse_press(90, 10, 500, 30) == 1) // �������·��
			{
				keyin_dir(path, 40);
				page = 0;
				read_dir(path, info, &page);
				spinOnce(path, info, mode, history, now_history, sort_mode, UpOrDown, preference);
				clrmous(MouseX, MouseY);
				cleardevice();
				if (mode == 0)
					strcpy(srch_tar, "");
				load_all(path, info, root, srch_tar, mode, preference, page);
			}
			else if (detect_m(0, 37, 365, 62) == 1) //|| mouse_press(10, 40, 500, 65) == 4)//�������Ϸ���������
			{

				if (func(info, src_path, &sort_mode, &UpOrDown, sort_menu_p) != 0)
				{
					read_dir(path, info, &page);
					spinOnce(path, info, mode, history, now_history, sort_mode, UpOrDown, preference);
					clrmous(MouseX, MouseY);
					cleardevice();
					load_all(path, info, root, srch_tar, mode, preference, page);
				}
			}

			else if (mouse_press(120, 70, 640, 440) == 1) // || mouse_press(120, 70, 640, 480) == 4)//�������ļ����У�����
			{
				result = change_dir(info, MouseX, MouseY);
				if (result == 2) //|| change_dir(info, MouseX, MouseY) == 0)//�������Ч���
				{
					page = 0;
					clrmous(MouseX, MouseY);
					cleardevice();
					spinOnce(path, info, mode, history, now_history, sort_mode, UpOrDown, preference);
					read_dir(path, info, &page);
					spinOnce(path, info, mode, history, now_history, sort_mode, UpOrDown, preference);
					load_all(path, info, root, srch_tar, mode, preference, page);
				}
				else if (result == 1) // ѡ��
				{
					clrmous(MouseX, MouseY);
					spinOnce(path, info, mode, history, now_history, sort_mode, UpOrDown, preference);
					cleardevice();
					load_all(path, info, root, srch_tar, mode, preference, page);
				}
				else if (result == 0) // ����հ�
				{
					cleardevice();
					for (int j = 0; j < INFO_LENGTH; j++)
						set_bit(&(info + j)->flag, 7, 0); // ������������д������д��ѡ�Ż�
					load_all(path, info, root, srch_tar, mode, preference, page);
				}
			}
			// ��ҳ
			else if (mouse_press(550, 440, 570, 460) == 1)
			{
				if (page > 0)
					page -= 1;
				clrmous(MouseX, MouseY);
				cleardevice();
				read_dir(path, info, &page);
				spinOnce(path, info, mode, history, now_history, sort_mode, UpOrDown, preference);
				load_all(path, info, root, srch_tar, mode, preference, page);
			}
			else if (mouse_press(580, 440, 600, 460) == 1)
			{
				page += 1;
				clrmous(MouseX, MouseY);
				cleardevice();
				read_dir(path, info, &page);
				spinOnce(path, info, mode, history, now_history, sort_mode, UpOrDown, preference);
				load_all(path, info, root, srch_tar, mode, preference, page);
			}

			// ����Ŀ¼��
			else if (mouse_press(10, 70, 100, 400) == 1)
			{
				if (chdir(get_file_path_left(root, MouseX, MouseY)) != -1)
				{
					mode_shift = _1to0;
					mode = 0;

					page = 0;
					spinOnce(path, info, mode, history, now_history, sort_mode, UpOrDown, preference);
					read_dir(path, info, &page);
					spinOnce(path, info, mode, history, now_history, sort_mode, UpOrDown, preference);
					clrmous(MouseX, MouseY);
					cleardevice();
					load_all(path, info, root, srch_tar, mode, preference, page);
					// clearRectangle(10, 10, 630, 30, BLACK);
					// load_top(path, srch_tar, mode);
					// clearRectangle(120, 70, 640, 480, BLACK);
					// load_main(info, mode);
				}

				if (unfold(root, MouseX, MouseY) != 0)
				{
					clrmous(MouseX, MouseY);
					clearRectangle(10, 70, 100, 400, BLACK);
					load_left(root, preference);
				}
			}
			else if (mouse_press(10, 430, 80, 460) == 1) // ��������
			{
				for (i = 0; i < 3; i++)
				{
					if (detect_m(10, 430 + i * 10, 80, 440 + i * 10) == 1 && strcmp(preference[i], "\0") != 0)
					{
						page = 0;
						chdir(preference[i]);
						spinOnce(path, info, mode, history, now_history, sort_mode, UpOrDown, preference);
						read_dir(path, info, &page);
						spinOnce(path, info, mode, history, now_history, sort_mode, UpOrDown, preference);
						clrmous(MouseX, MouseY);
						cleardevice();
						load_all(path, info, root, srch_tar, mode, preference, page);
					}
				}
			}

			// ����
			else if (mouse_press(620, 0, 640, 20) == 2)
				end();

			// ����
			// ģʽ�л��б�
			// if (mouse_press(540, 10, 630, 30) == 1)
			if (MouseX > 540 && MouseX < 630 && MouseY > 10 && MouseY < 30 && press == 1) // �ĸ�Ч�������ĸ�
			{
				if (mode_shift == _0to0 || mode_shift == _1to0)
				{
					mode_shift = _0to1;
					mode = 1;
				}
				else // if (mode_shift == _0to1 || mode_shift == _1to1)
					mode_shift = _1to1;
			}
			if (mouse_press_out(540, 10, 620, 30) == 1)
			{
				if (mode_shift == _0to1 || mode_shift == _1to1)
				{
					mode_shift = _1to0;
					mode = 1;
				}
				else if (mode_shift == _0to0 || mode_shift == _1to0)
					mode_shift = _0to0;
			}

			// �Ҽ�����
			if (mouse_press(120, 70, 640, 480) == 3)
			{
				int tmp_x = MouseX, tmp_y = MouseY; // ��¼�һ�ʱ�����λ��

				delay(200);
				result = 0;

				// result = drop_down_menu(MouseX, MouseY, 75, 25, 4, 12, RB_menu_p, WHITE, DARKGRAY, 0, 1);
				result = drop_down_menu(MouseX, MouseY, 75, 25, 3, 12, RB_menu_p, WHITE, DARKGRAY, 0, 1);

				if (result == 0) // ����ʽ
				{
					int result_0 = -1;
					result_0 = drop_down_menu(tmp_x + 75, tmp_y, 75, 25, 6, 12, sort_menu_p, WHITE, DARKGRAY, 0, 0);
					if (result_0 >= 0 && result_0 <= 3)
						sort_mode = result_0;
					else if (result_0 == 4)
						UpOrDown = 1;
					else if (result_0 == 5)
						UpOrDown = -1;
					if (result_0 != -1)
					{
						spinOnce(path, info, mode, history, now_history, sort_mode, UpOrDown, preference);
						clrmous(MouseX, MouseY);
						cleardevice();
						load_all(path, info, root, srch_tar, mode, preference, page);
						delay(200);
					}
					else
					{
						clrmous(MouseX, MouseY);
						cleardevice();
						load_all(path, info, root, srch_tar, mode, preference, page);
					}
				}
				// else if (result == 1) // ����
				// {
				// }
				else if (result == 1) // �½�
				{
					build(info, tmp_x + 75, tmp_y);
					clrmous(MouseX, MouseY);
					cleardevice();
					read_dir(path, info, &page);
					spinOnce(path, info, mode, history, now_history, sort_mode, UpOrDown, preference);
					load_all(path, info, root, srch_tar, mode, preference, page);
				}
				else if (result == 2) // ����
				{
					if (get_file_num(tmp_x, tmp_y, info) != -1)
						set_bit(&(info + get_file_num(tmp_x, tmp_y, info) - 1)->flag, 7, 1);
					if (is_selected(info) != 0)
						property(NULL, info + is_selected(info) - 1);
					else
						property(path, NULL);
					cleardevice();
					load_all(path, info, root, srch_tar, mode, preference, page);
				}
			}

			// ģʽ�л�����
			if (mode_shift == _0to1) // ��һ��ģʽ������ģʽ
			{
				mode = 1;
				clrmous(MouseX, MouseY);
				load_top(path, srch_tar, mode);
				mode_shift = _1to1;
			}
			else if (mode_shift == _1to0) // ������ģʽ��һ��ģʽ����������Ŀ��Ϊ��
			{
				mode = 0;
				load_top(path, srch_tar, mode);
				mode_shift = _0to0;
			}

			if (mode_shift == _1to1 || mode_shift == _0to1) // �����������ģʽ
			{
				blbl(542, 12, srch_tar, 2, WHITE, BLACK); // ��������˸

				result = srch_input(srch_tar, info, img_buffer);
				if (result == 1)
				{
					load_top(path, srch_tar, mode);
				}
				else if (result == 2)
				{
					loading_ok(img_buffer);
					// strcpy(srch_tar, "");
					mode_shift = _0to1;
					srch_output(path, info, root, srch_tar);
					clearRectangle(1, 430, 240, 470, BLACK);
					load_main(info, 1, 0);
				}
			}
		}
	}

	closegraph();
	return 0;
}

#endif