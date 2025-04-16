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
    union REGS regs;    // 用于读取键盘缓冲区
    static int num = 0; // 正在输入的位置在target中的位置

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