#include "include.h"

// ��ռ��̻�����
void clear_keyboard_buffer()
{
    union REGS regs;
    while (bioskey(1)) // �����̻������Ƿ�Ϊ��
    {
        regs.h.ah = 0x00;
        int86(0x16, &regs, &regs); // ��ȡ���������̻������е��ַ�
    }
}

// ��ʾ������������
void out_keybd(char *text, int max, int x, int y, int lettersize, int bkcolor, int lettercolor)
{
    char box[128];
    strcpy(box, text);
    setfillstyle(SOLID_FILL, bkcolor);
    clrmous(MouseX, MouseY);
    bar(x, y, x + lettersize * 8 * max, y + lettersize * 15);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, lettersize);
    setcolor(lettercolor);
    outtextxy(x, y + lettersize * 5, box);
}

void draw_windows(int x, int y, int size)
{

    draw_window(x, y, size, RED);
    draw_window(x + size * 16, y + size * 2, size, GREEN);
    draw_window(x - size * 4, y + size * 14, size, BLUE);
    draw_window(x + size * 12, y + size * 16, size, YELLOW);
}

void draw_window(int x, int y, int size, int color)
{
    int circle[5] = {0}; // 0:x , 1:y , 2:r , 3:stangle , 4:endangle
    setcolor(WHITE);
    line(x, y, x - size * 3, y + size * 11); //-15,+55     345��135
    line(x + size * 13, y + size, x + size * 10, y + size * 12);
    if (color == RED || color == BLUE)
    {
        radius_3pts(x, y, x + size * 13, y + size, x + size * 6, y - size, circle);
        arc(circle[0], circle[1], circle[3], circle[4], circle[2]);
        radius_3pts(x - size * 3, y + size * 11, x + size * 10, y + size * 12, x + size * 3, y + size * 10, circle);
        arc(circle[0], circle[1], circle[3], circle[4], circle[2]);
        setfillstyle(SOLID_FILL, color);
        floodfill((x + x + size * 10) / 2, (y + y + size * 12) / 2, WHITE);
    }
    else if (color == GREEN || color == YELLOW)
    {
        radius_3pts(x + size * 13, y + size, x, y, x + size * 6, y + size, circle);
        circle[0] -= size / 2; // ǿ������ת������
        arc(circle[0], circle[1], circle[3], circle[4], circle[2]);
        radius_3pts(x + size * 10, y + size * 12, x - size * 3, y + size * 11, x + size * 3, y + size * 12, circle);
        circle[0] -= size / 2; // ǿ������ת������
        arc(circle[0], circle[1], circle[3], circle[4], circle[2]);
        setfillstyle(SOLID_FILL, color);
        floodfill((x + x + size * 10) / 2, (y + y + size * 12) / 2, WHITE);
    }
}

// ��ȡ�������룬����2��ʾ������ϣ�����1��ʾ�������룬����0��ʾ��Ч���루δ���룩
int getbuffer_keybd(char *target, int max)
{
    union REGS regs;          // ���ڶ�ȡ���̻�����
    int num = strlen(target); // ���������λ����target�е�λ��
                              // printf("%d", num);
    if (bioskey(1) == 0)
    {
        return 0;
    }
    else if (num < max)
    {
        regs.h.ah = 0x00;
        int86(0x16, &regs, &regs); // ��ȡ16λ�Ĵ����ĺ��λASCII��
        char ch = regs.h.al;

        if (regs.h.al == 0x08) // �˸�
        {
            if (num != 0)
                num -= 1;
            target[num] = '\0';
            return 1;
        }
        else if (num < max - 1 && regs.h.al != 0x0D) // ��󳤶�Ϊ16-1
        {

            target[num] = regs.h.al;
            num = num + 1;
            target[num] = '\0';
            return 1;
        }
        else if (num < max && ch == 0x0D) // ֻ�лس��ſ���ռ�����һ��λ��
        {

            target[num] = '\0';
            num = 0;
            return 2;
            // num = 0;
        }
    }
    else
        return 0;
}

// ��������Բ����ԭ���㷨����github
void radius_3pts(float x1, float y1, float x2, float y2, float x3, float y3, int *circle)
{
    float a, b, c, d, e, f, r, x, y;
    a = 2 * (x2 - x1);
    b = 2 * (y2 - y1);
    c = x2 * x2 + y2 * y2 - x1 * x1 - y1 * y1;
    d = 2 * (x3 - x2);
    e = 2 * (y3 - y2);
    f = x3 * x3 + y3 * y3 - x2 * x2 - y2 * y2;
    x = (b * f - e * c) / (b * d - e * a);
    y = (d * c - a * f) / (b * d - e * a);
    r = sqrt((x - x1) * (x - x1) + (y - y1) * (y - y1));
    circle[0] = (int)x;
    circle[1] = (int)y;
    circle[2] = (int)r;
    circle[3] = (int)(atan2(y - y2, x2 - x) / M_PI * 180); // ע��BC��y�������µ�
    circle[4] = (int)(atan2(y - y1, x1 - x) / M_PI * 180);
}

// ���ı�ĩβ���blinblin��˸
void blbl(int x, int y, char *str, int size, int lightcolor, int darkcolor)
{

    static time_t blbl_lasttime = 0;
    time_t blbl_nowtime = clock();
    static int flag = 0; // ��ǰ��ɫ
    settextstyle(DEFAULT_FONT, HORIZ_DIR, size);
    if (blbl_nowtime - blbl_lasttime > 2 && flag == 0)
    {
        flag = 1;
        blbl_lasttime = blbl_nowtime;
        setcolor(lightcolor);
        // outtextxy(x + size * strlen(str) * 4, y, "|");
        line(x + size * strlen(str) * 4, y, x + size * strlen(str) * 4, y + size * 8);
    }
    else if (blbl_nowtime - blbl_lasttime > 2 && flag == 1)
    {
        flag = 0;
        blbl_lasttime = blbl_nowtime;
        setcolor(darkcolor);
        // outtextxy(x + size * strlen(str) * 4, y, "|");
        line(x + size * strlen(str) * 4, y, x + size * strlen(str) * 4, y + size * 8);
    }
}

// ����,�������߿�
void highlight(int x1, int y1, int x2, int y2, int darkcolor, int lightcolor)
{
    int i, j; // ѭ������

    if (x2 - x1 < 2 || y2 - y1 < 2) // ����Ҫ����
        return;

    for (i = x1 + 1; i < x2; i++)
        for (j = y1 + 1; j < y2; j++)
            if (getpixel(i, j) == darkcolor)
                putpixel(i, j, lightcolor);
}

// ������⣨������main�ˣ���ˮ����ô��������
void highlight_detector(char src_path[128], struct file_info *info)
{

    static int flag[16] = {0}; // ������ǩ1:����;0:ȡ������
    int i;                     // ѭ������

    int pos[16][4] = {
        {5, 5, 25, 25},       // 0���ͷ
        {25, 5, 45, 25},      // 1�Ҽ�ͷ
        {45, 5, 65, 25},      // 2�ϼ�ͷ
        {65, 5, 85, 25},      // 3ˢ��
        {5, 37, 60, 62},      // 4�½�
        {60, 37, 85, 62},     // 5����
        {85, 37, 110, 62},    // 6����
        {110, 37, 135, 62},   // 7ճ��
        {135, 37, 165, 62},   // 8������
        {165, 37, 190, 62},   // 9ɾ��
        {190, 37, 275, 62},   // 10����
        {550, 440, 570, 460}, // 11��һҳ
        {580, 440, 600, 460}, // 12��һҳ
        {275, 37, 365, 62}    // 13�鿴

    };
    int len = 14; // ��������
    for (i = 0; i < len; i++)
    {
        if (strcmp(src_path, "") == 0 && i == 7) // ���·��Ϊ�գ����С����ơ���������ɾ��������
        {
            pos[i][0] = -1;
            pos[i][1] = -1;
            pos[i][2] = -1;
            pos[i][3] = -1;
        }
        else if (is_selected(info) == 0 && (i == 5 || i == 6 || i == 8 || i == 9)) // ���û��ѡ���ļ������С����ơ���������ɾ��������
        {
            pos[i][0] = -1;
            pos[i][1] = -1;
            pos[i][2] = -1;
            pos[i][3] = -1;
        }
        if (detect_m(pos[i][0], pos[i][1], pos[i][2], pos[i][3]) == 1 && flag[i] == 0)
        {
            clrmous(MouseX, MouseY);
            highlight(pos[i][0], pos[i][1], pos[i][2], pos[i][3], BLACK, DARKGRAY);
            flag[i] = 1;
        }
        else if (detect_m(pos[i][0], pos[i][1], pos[i][2], pos[i][3]) == 0 && flag[i] == 1)
        {
            clrmous(MouseX, MouseY);
            highlight(pos[i][0], pos[i][1], pos[i][2], pos[i][3], DARKGRAY, BLACK);
            flag[i] = 0;
        }
    }
}

void highlight_detector(struct file_info *info, int pic_flag)
{
#define CAPACITY 32
    static int flag[CAPACITY] = {0}; // ������ǩ1:����;0:ȡ������
    int i;                           // ѭ������
    int pos[CAPACITY][4];

    // �ļ���������ò�ͬ�ĸ�����ʽ,������putpixel�����ȵ�
    if (info != NULL)
    {
        for (i = 0; i < get_info_num(info); i++)
        {
            if (pic_flag == 0)
            {
                pos[i][0] = 120;
                pos[i][1] = 90 + i * 20;
                pos[i][2] = 630;
                pos[i][3] = 90 + i * 20 + 20;
            }
            else if (pic_flag == 1)
            {
                pos[i][0] = 160 + (i % 4) * 100;
                pos[i][1] = 90 + (i / 4) * 100;
                pos[i][2] = 160 + (i % 4) * 100 + 100;
                pos[i][3] = 90 + (i / 4) * 100 + 100;
            }
        }
        for (i = 0; i < get_info_num(info); i++)
        {
            if (detect_m(pos[i][0], pos[i][1], pos[i][2], pos[i][3]) == 1 && flag[i] == 0)
            {
                clrmous(MouseX, MouseY);
                clearRectangle(pos[i][0], pos[i][1], pos[i][2], pos[i][3], DARKGRAY);
                load_file_info(pos[i][0], pos[i][1] + 5, info + i, pic_flag);
                flag[i] = 1;
            }
            else if (detect_m(pos[i][0], pos[i][1], pos[i][2], pos[i][3]) == 0 && flag[i] == 1)
            {
                clrmous(MouseX, MouseY);
                clearRectangle(pos[i][0], pos[i][1], pos[i][2], pos[i][3], BLACK);
                load_file_info(pos[i][0], pos[i][1] + 5, info + i, pic_flag);
                flag[i] = 0;
            }
        }
    }
}

// ��������
void warn(char *str)
{
    int size;     // ͼ���С
    void *buffer; // ����
    int flag = 0; // ������־
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
    setcolor(BLACK); // 420��200,400,220
    line(420, 200, 400, 220);
    line(400, 200, 420, 220);
    puthz(240, 240, str, 12, 2, BLACK);
    while (1)
    {
        newmouse(&MouseX, &MouseY, &press);
        if (detect_m(400, 200, 420, 220) == 1 && flag == 0)
        {
            clrmous(MouseX, MouseY);
            highlight(400, 200, 420, 220, LIGHTGRAY, RED);

            flag = 1;
        }
        else if (detect_m(400, 200, 420, 220) == 0 && flag == 1)
        {
            clrmous(MouseX, MouseY);
            highlight(400, 200, 420, 220, RED, LIGHTGRAY);
            flag = 0;
        }

        if (detect_m(400, 200, 420, 220) == 1 && press == 1)
            break;
    }
    putimage(220, 200, buffer, COPY_PUT);
    clrmous(MouseX, MouseY);
    free(buffer);
}

// ����ַ��Ƿ�Ϸ�
int check(char *str)
{
    int i = 0;
    while (str[i] != '\0')
    {
        char c = str[i];
        if (!((c >= '0' && c <= '9') ||
              (c >= 'A' && c <= 'Z') ||
              (c >= 'a' && c <= 'z') ||
              c == '~' || c == '\\' || c == ':' || c == ' '))
        {
            return 0; // �Ƿ��ַ�
        }
        i++;
    }
    return 1;
}

// �ṹ�����ڴ洢·��������ִ���
typedef struct
{
    char path[128];
    int count;
} PathCount;

// �ȽϺ����������ִ�����������
int compare_path_count(const void *a, const void *b)
{
    return ((PathCount *)b)->count - ((PathCount *)a)->count;
}

// ��ȡƫ��
void get_preference(char history[HISTORY_LENGTH][128], char preference[3][128])
{
    PathCount paths[HISTORY_LENGTH];
    int path_count = 0;

    // ��ʼ�� paths ���鲢ͳ�Ƴ��ִ���
    for (int i = 0; i < HISTORY_LENGTH; i++)
    {
        int found = 0;
        for (int j = 0; j < path_count; j++)
        {
            if (strcmp(history[i], paths[j].path) == 0)
            {
                paths[j].count++;
                found = 1;
                break;
            }
        }
        if (!found && strlen(history[i]) > 0)
        {
            strcpy(paths[path_count].path, history[i]);
            paths[path_count].count = 1;
            path_count++;
        }
    }

    // ���ճ��ִ�������
    qsort(paths, path_count, sizeof(PathCount), compare_path_count);

    // ɸѡ���ִ��� >= 3�����ұ�֤���ظ�������check����
    int pref_index = 0;
    for (i = 0; i < path_count && pref_index < 3; i++)
    {
        if ( // paths[i].count >= 3  &&
            check(paths[i].path))
        {
            // ȥ�ؼ��
            int is_dup = 0;
            for (int j = 0; j < pref_index; j++)
            {
                if (strcmp(preference[j], paths[i].path) == 0)
                {
                    is_dup = 1;
                    break;
                }
            }
            if (!is_dup)
            {
                strcpy(preference[pref_index], paths[i].path);
                pref_index++;
            }
        }
    }

    // ������������������ַ���
    while (pref_index < 3)
    {
        preference[pref_index][0] = '\0';
        pref_index++;
    }
}