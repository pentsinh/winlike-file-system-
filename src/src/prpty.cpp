#include "include.h"
// ��ʾ�ļ����У�����
void property(char *path, struct file_info *info)
{
    struct file_info ppt;  // ��Ž�Ҫ��ʾ���ļ����У�������
    int size;              // ��¼ͼ��Ĵ�С
    void *property_buffer; // �ݴ汻�ڵ���ͼ��
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

    if (path == NULL && info != NULL) // ��������Ϊinfo
    {
        ppt = *info;
    }
    else if (path != NULL && info == NULL) // ��������Ϊpath
    {
        char *father_path = get_father_path(path);
        get_file_info(father_path, path_to_name(path), &ppt);
    }
    else
    {
        perror("ERROR");
        return; // ����������������NOTICE
    }

    clrmous(MouseX, MouseY);

    int x1 = 210, y1 = 30, x2 = 520, y2 = 450;
    int type = get_file_type(ppt.name);

    // ���Ƶ���
    setcolor(BLACK);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
    rectangle(x1, y1, x2, y2);
    setfillstyle(SOLID_FILL, WHITE);
    bar(x1 + 1, y1 + 1, x2 - 1, y2 - 1);
    // �˳���
    rectangle(x2 - 2 - 20, y1 + 2, x2, y1 + 20);
    line(x2 - 1 - 20, y1 + 1, x2 - 1, y1 + 1 + 20);
    line(x2 - 1 - 20, y1 + 1 + 20, x2 - 1, y1 + 1);
    // ����
    int len = strlen(ppt.name); // ���Ƴ���
    outtextxy(x1 + 30, y1 + 5, ppt.name);
    puthz(x1 + 30 + len * 8, y1 + 5, "����", 12, 2, BLACK);
    //  ������Է�һ��ͼƬ
    // setcolor(RED);
    // rectangle(x1 + 10, y1 + 15, x1 + 60, y1 + 65); // 50*50
    switch (type)
    {
    case 2:
    {
        draw_file(x1 + 10, y1 + 15, 1);
        break;
    }
    case 3:
    {
        draw_txt(x1 + 10, y1 + 15, 1);
        break;
    }
    case 4:
    {
        draw_c(x1 + 10, y1 + 15, 1);
        break;
    }
    case 5:
    {
        draw_cpp(x1 + 10, y1 + 15, 1);
        break;
    }
    case 6:
    {
        draw_h(x1 + 10, y1 + 15, 1);
        break;
    }
    case 7:
    {
        draw_obj(x1 + 10, y1 + 15, 1);
        break;
    }
    case 8:
    {
        draw_exe(x1 + 10, y1 + 15, 1);
        break;
    }
    case 9:
    {
        draw_jpg(x1 + 10, y1 + 15, 1);
        break;
    }
    case 10:
    {
        draw_png(x1 + 10, y1 + 15, 1);
        break;
    }
    case 11:
    {
        draw_doc(x1 + 10, y1 + 15, 1);
        break;
    }
    case 12:
    {
        draw_xls(x1 + 10, y1 + 15, 1);
        break;
    }
    case 13:
    {
        draw_ppt(x1 + 10, y1 + 15, 1);
        break;
    }
    case 14:
    {
        draw_pdf(x1 + 10, y1 + 15, 1);
        break;
    }
    }
    setcolor(BLACK);
    outtextxy(x1 + 70, y1 + 50, ppt.name);
    line(x1 + 10, y1 + 80, x2 - 10, y1 + 80);
    // ����
    puthz(x1 + 10, y1 + 120, "����", 12, 2, BLACK);
    outtextxy(x1 + 70, y1 + 120, file_type_strings[type]);

    // λ��
    puthz(x1 + 10, y1 + 160, "λ��", 12, 2, BLACK);
    outtextxy(x1 + 70, y1 + 160, ppt.path);
    // ��С
    puthz(x1 + 10, y1 + 200, "��С", 12, 2, BLACK);
    outtextxy(x1 + 70, y1 + 200, ppt.size);
    // ����
    puthz(x1 + 10, y1 + 240, "����", 12, 2, BLACK);
    char *sons;
    unsigned char flag = ppt.flag;
    if (get_bit(flag, 0) * 1 + get_bit(flag, 1) * 2 + get_bit(flag, 2) * 2 * 2 + get_bit(flag, 3) * 2 * 2 * 2 == 2) // ���ļ���
        itoa(ppt.sons, sons, 10);
    else
        sons = "N\\A"; // ���ļ���
    outtextxy(x1 + 70, y1 + 240, sons);
    len = strlen(sons);
    puthz(x1 + 30 + 100, y1 + 240, "����Ŀ", 12, 2, BLACK);
    //  �޸�����
    puthz(x1 + 10, y1 + 280, "�޸�����", 12, 2, BLACK);
    outtextxy(x1 + 70, y1 + 280, ppt.time);
    // ȷ��
    rectangle(x2 - 50, y2 - 25, x2 - 5, y2 - 5);
    puthz(x2 - 45, y2 - 25, "ȷ��", 16, 2, BLACK);
    // puthz(45, 25, "ȷ��", 16, 2, YELLOW);

    int flag_1 = 0; // �˳�
    int flag_2 = 0; // ȷ��
    while (1)
    {
        newmouse(&MouseX, &MouseY, &press);

        if (detect_m(x2 - 2 - 20, y1 + 2, x2, y1 + 20) == 1 && flag_1 == 0)
        {
            clrmous(MouseX, MouseY);
            highlight(x2 - 2 - 20, y1 + 2, x2, y1 + 20, WHITE, RED);
            flag_1 = 1;
        }
        else if (detect_m(x2 - 2 - 20, y1 + 2, x2, y1 + 20) == 0 && flag_1 == 1)
        {
            clrmous(MouseX, MouseY);
            highlight(x2 - 2 - 20, y1 + 2, x2, y1 + 20, RED, WHITE);
            flag_1 = 0;
        }

        if (detect_m(x2 - 50, y2 - 25, x2 - 5, y2 - 5) == 1 && flag_2 == 0)
        {
            clrmous(MouseX, MouseY);
            highlight(x2 - 50, y2 - 25, x2 - 5, y2 - 5, WHITE, LIGHTGRAY);
            flag_2 = 1;
        }
        else if (detect_m(x2 - 50, y2 - 25, x2 - 5, y2 - 5) == 0 && flag_2 == 1)
        {
            clrmous(MouseX, MouseY);
            highlight(x2 - 50, y2 - 25, x2 - 5, y2 - 5, LIGHTGRAY, WHITE);
            flag_2 = 0;
        }
        if (mouse_press(x2 - 2 - 20, y1 + 2, x2, y1 + 20) == 1 || mouse_press(x2 - 50, y2 - 25, x2 - 5, y2 - 5) == 1)
        {
            clrmous(MouseX, MouseY);
            return;
        }
    }
}
