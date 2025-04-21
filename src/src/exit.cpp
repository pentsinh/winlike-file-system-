#include "include.h"

void end()
{
    clrmous(MouseX, MouseY);
    int result;
    setfillstyle(SOLID_FILL, RED);
    bar(620, 0, 640, 20);
    line(620, 0, 640, 20);
    line(640, 0, 620, 20);
    while (1)
    {
        newmouse(&MouseX, &MouseY, &press);
        result = mouse_press(610, 0, 640, 30);
        int flag = 0; // 是否在框内，不调用mouse_press因为它的return=0也可以是按下鼠标未弹起

        // char MX[8], MY[8];
        // itoa(MouseX, MX, 10);
        // itoa(MouseY, MY, 10);
        // clearRectangle(0, 0, 80, 20, BLACK);
        // settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
        // outtextxy(0, 0, MX);
        // outtextxy(40, 0, MY);

        if (press == 1)
            printf("%d", result);

        // if (result == 1)
        // if (mouse_press(620, 0, 640, 20) == 1)
        if (MouseX > 620 && MouseX < 640 && MouseY > 0 && MouseY < 20 && press == 1)
        {
            cleardevice();
            end_img();
            chdir("C:\\PROJECT\\devel");
            closegraph();
        }
        if (MouseX > 620 && MouseX < 640 && MouseY > 0 && MouseY < 20)
            flag = 1;
        if (flag == 0)
        {
            clrmous(MouseX, MouseY);
            setfillstyle(SOLID_FILL, BLACK);
            bar(620, 0, 640, 20);
            line(620, 0, 640, 20);
            line(640, 0, 620, 20);
            break;
        }
        // newmouse(&MouseX, &MouseY, &press);
    }
}

void end_img()
{
    draw_windows(315, 130, 5);
    setcolor(WHITE);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 6);
    outtextxy(140, 300, "Windos");
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    outtextxy(135, 275, "HUST AIA");
    setcolor(RED);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 4);
    outtextxy(455, 285, "xb");
    delay(3000);
}