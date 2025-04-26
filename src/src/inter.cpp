#include "include.h"

// 清空键盘缓冲区
void clear_keyboard_buffer()
{
    union REGS regs;
    while (bioskey(1)) // 检查键盘缓冲区是否为空
    {
        regs.h.ah = 0x00;
        int86(0x16, &regs, &regs); // 读取并丢弃键盘缓冲区中的字符
    }
}

// 显示键盘输入内容
void out_keybd(char *text, int max, int x, int y, int lettersize, int bkcolor, int lettercolor)
{
    char box[1024];
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
    line(x, y, x - size * 3, y + size * 11); //-15,+55     345，135
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
        circle[0] -= size / 2; // 强制类型转换修正
        arc(circle[0], circle[1], circle[3], circle[4], circle[2]);
        radius_3pts(x + size * 10, y + size * 12, x - size * 3, y + size * 11, x + size * 3, y + size * 12, circle);
        circle[0] -= size / 2; // 强制类型转换修正
        arc(circle[0], circle[1], circle[3], circle[4], circle[2]);
        setfillstyle(SOLID_FILL, color);
        floodfill((x + x + size * 10) / 2, (y + y + size * 12) / 2, WHITE);
    }
}

// 获取键盘输入，返回2表示输入完毕，返回1表示正在输入，返回0表示无效输入（未输入）
int getbuffer_keybd(char *target, int max)
{
    union REGS regs;          // 用于读取键盘缓冲区
    int num = strlen(target); // 正在输入的位置在target中的位置
                              // printf("%d", num);
    if (bioskey(1) == 0)
    {
        return 0;
    }
    else if (num < max)
    {
        regs.h.ah = 0x00;
        int86(0x16, &regs, &regs); // 获取16位寄存器的后八位ASCII码
        char ch = regs.h.al;

        if (regs.h.al == 0x08) // 退格
        {
            if (num != 0)
                num -= 1;
            target[num] = '\0';
            return 1;
        }
        else if (num < max - 1 && regs.h.al != 0x0D) // 最大长度为16-1
        {

            target[num] = regs.h.al;
            num = num + 1;
            target[num] = '\0';
            return 1;
        }
        else if (num < max && ch == 0x0D) // 只有回车才可以占据最后一个位置
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

// 计算三点圆弧，原版算法来自github
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
    circle[3] = (int)(atan2(y - y2, x2 - x) / M_PI * 180); // 注意BC的y轴是向下的
    circle[4] = (int)(atan2(y - y1, x1 - x) / M_PI * 180);
}

// 在文本末尾光标blinblin闪烁
void blbl(int x, int y, char *str, int size, int lightcolor, int darkcolor)
{

    static time_t blbl_lasttime = 0;
    time_t blbl_nowtime = clock();
    static int flag = 0; // 当前颜色
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

// 高亮,不包括边框
void highlight(int x1, int y1, int x2, int y2, int darkcolor, int lightcolor)
{
    int i, j; // 循环变量

    if (x2 - x1 < 2 || y2 - y1 < 2) // 不需要高亮
        return;

    for (i = x1 + 1; i < x2; i++)
        for (j = y1 + 1; j < y2; j++)
            if (getpixel(i, j) == darkcolor)
                putpixel(i, j, lightcolor);
}

// 高亮侦测（不想大改main了，就水了这么个函数）
void highlight_detector(struct file_info *info, struct My_filenode *root)
{
#define CAPACITY 32
    static int flag[CAPACITY] = {0}; // 高亮标签1:高亮;0:取消高亮
    int i;                           // 循环变量

    int pos[CAPACITY][4] = {
        {5, 5, 25, 25},       // 0左箭头
        {25, 5, 45, 25},      // 1右箭头
        {45, 5, 65, 25},      // 2上箭头
        {65, 5, 85, 25},      // 3刷新
        {5, 37, 60, 62},      // 4新建
        {60, 37, 85, 62},     // 5剪切
        {85, 37, 110, 62},    // 6复制
        {110, 37, 135, 62},   // 7粘贴
        {135, 37, 165, 62},   // 8重命名
        {165, 37, 190, 62},   // 9删除
        {190, 37, 275, 62},   // 10排序
        {550, 440, 570, 460}, // 11上一页
        {580, 440, 600, 460}  // 12下一页
        //{275, 37, 365, 62}  // 13查看

    };
    int len = 13; // 功能数量
    for (i = 0; i < len; i++)
    {
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

    // 文件夹区域采用不同的高亮方式,大区域putpixel流畅度低
    if (info != NULL)
    {
        for (i = 0; i < get_info_num(info); i++)
        {
            pos[len + i][0] = 120;
            pos[len + i][1] = 90 + i * 20;
            pos[len + i][2] = 630;
            pos[len + i][3] = 90 + i * 20 + 20;
        }
        for (i = len; i < len + get_info_num(info); i++)
        {
            if (detect_m(pos[i][0], pos[i][1], pos[i][2], pos[i][3]) == 1 && flag[i] == 0)
            {
                clrmous(MouseX, MouseY);
                clearRectangle(pos[i][0], pos[i][1] + 1, pos[i][2], pos[i][3] - 1, DARKGRAY);
                load_file_info(pos[i][0], pos[i][1] + 5, info + i - len);
                flag[i] = 1;
            }
            else if (detect_m(pos[i][0], pos[i][1], pos[i][2], pos[i][3]) == 0 && flag[i] == 1)
            {
                clrmous(MouseX, MouseY);
                clearRectangle(pos[i][0], pos[i][1] + 1, pos[i][2], pos[i][3] - 1, BLACK);
                load_file_info(pos[i][0], pos[i][1] + 5, info + i - len);
                flag[i] = 0;
            }
        }
    }
    // else if (root != NULL)
    // {
    //     return;
    // }
}

// 警告中文
void warn(char *str)
{
    int size;     // 图像大小
    void *buffer; // 缓存
    int flag = 0; // 高亮标志
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
    setcolor(BLACK); // 420，200,400,220
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

// 比较函数，用于qsort排序时按值从大到小排序
int compare(const void *a, const void *b)
{
    int val1 = ((int *)a)[0];
    int val2 = ((int *)b)[0];
    return val2 - val1; // 按值从大到小排序
}

// 函数实现
void findTopIndices(int *arr1, int len1, int *arr2, int len2)
{
    if (len2 > len1)
    {
        printf("Error: len2 cannot be larger than len1\n");
        return;
    }

    // 创建一个临时数组来存储索引
    int *temp = (int *)malloc(len1 * sizeof(int));
    for (int i = 0; i < len1; i++)
    {
        temp[i] = i; // 存储原数组的索引
    }

    // 按照arr1中的值对索引进行排序（从大到小）
    qsort(temp, len1, sizeof(int), compare);

    // 将最大的len2个索引存入arr2
    for (i = 0; i < len2; i++)
    {
        arr2[i] = temp[i];
    }

    // 释放临时数组
    free(temp);
}

int check(char *str) // 检查排除非法字符
{
    int i = 0;
    int result = 0; // 返回值
    while (str[i] != '\0' && i < 1024)
    {
        if ((str[i] >= '0' && str[i] <= '9') || (str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= 'a' && str[i] <= 'z') || str[i] == '~' || str[i] == '\\' || str[i] == ':' || str[i] == ' ')
            result = 1;
        else
        {
            result = 0;
            break;
        }
        i++;
    }
    return result;
}

// 获取偏好
void get_preference(char history[HISTORY_LENGTH][1024], char preference[3][1024])
{
    char tmp[1024];                  // 暂存路径
    int count[HISTORY_LENGTH] = {0}; // 每个路径在history里面出现次数的平方
    int max_pos[HISTORY_LENGTH];     // 最大值在count中的位置，从大到小
    int i, j;                        // 循环变脸
    // 统计每个路径在history里面出现次数的平方
    for (i = 0; i < HISTORY_LENGTH; i++)
    {
        strcpy(tmp, history[i]);
        for (j = 0; j < HISTORY_LENGTH; j++)
            if (strcmp(tmp, history[j]))
                count[i] += 1;
    }
    // 只有某个路径出现三次及以上preference才可以记录
    for (i = 0; i < HISTORY_LENGTH; i++)
    {
        if (count[i] >= 9)
            break;
    }
    if (i == HISTORY_LENGTH)
        return;
    // 开始构建preference
    // int tmp = 0; // 比较中间值
    // 找最大
    int k = 0; // prefenence中的位置
    findTopIndices(count, HISTORY_LENGTH, max_pos, HISTORY_LENGTH);
    for (i = 0; i < HISTORY_LENGTH; i++)
    {
        for (j = 0; j < k; j++)
            if (strcmp(preference[j], history[max_pos[i]]) == 0) // 如果已经记录在preference
                goto node;
        if (check(history[max_pos[i]]) == 1)
        {
            strcpy(preference[k], history[max_pos[i]]);
            k++;
        }
    node:
    }
}