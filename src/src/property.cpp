#include "include.h"
// 显示文件（夹）属性
void property(char *path, struct file_info *info)
{
    struct file_info ppt;  // 存放将要显示的文件（夹）的属性
    int size;              // 记录图像的大小
    void *property_buffer; // 暂存被遮挡的图像

    if (path == NULL && info != NULL) // 如果传入的为info
    {
        ppt = *info;
    }
    else if (path != NULL && info == NULL) // 如果传入的为path
    {
        // get_file_info()
        return;
    }
    else
    {
        perror("ERROR");
        return; // 如果传入参数不符合NOTICE
    }

    clrmous(MouseX, MouseY);

    int x1 = 210, y1 = 30, x2 = 420, y2 = 450;

    // 保存遮挡图片
    size = imagesize(x1, y1, x2, y2);
    property_buffer = malloc(size);
    if (property_buffer != NULL)
        getimage(x1, y1, x2, y2, property_buffer);
    else
    {
        perror("ERROR IN REMEMBERING");
        // delay(3000);
        // exit(1);
        // return;
    }
    // 绘制弹窗
    setcolor(BLACK);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
    rectangle(x1, y1, x2, y2);
    setfillstyle(SOLID_FILL, WHITE);
    bar(x1 + 1, y1 + 1, x2 - 1, y2 - 1);
    // 退出框
    rectangle(x2 - 2 - 20, y1 + 2, x2, y1 + 20);
    line(x2 - 1 - 20, y1 + 1, x2 - 1, y1 + 1 + 20);
    line(x2 - 1 - 20, y1 + 1 + 20, x2 - 1, y1 + 1);
    // 标题
    int len = strlen(ppt.name); // 名称长度
    outtextxy(x1 + 30, y1 + 5, ppt.name);
    // puthz(x1 + 30 + len * 5, y1 + 5, "属性", 12, 2, BLACK);
    //  这里可以放一张图片
    outtextxy(x1 + 60, y1 + 50, ppt.name);
    line(x1 + 10, y1 + 80, x2 - 10, y1 + 80);
    // 类型
    // puthz(x1 + 10, y1 + 120, "类型", 12, 2, BLACK);
    // 位置
    // puthz(x1 + 10, y1 + 160, "位置", 12, 2, BLACK);
    outtextxy(x1 + 60, y1 + 160, ppt.path);
    // 大小
    // puthz(x1 + 10, y1 + 200, "大小", 12, 2, BLACK);
    outtextxy(x1 + 60, y1 + 200, ppt.size);
    // 包含
    // puthz(x1 + 10, y1 + 240, "包含", 12, 2, BLACK);
    char *sons;
    unsigned char flag = ppt.flag;
    if (get_bit(flag, 0) * 1 + get_bit(flag, 1) * 2 + get_bit(flag, 2) * 2 * 2 + get_bit(flag, 3) * 2 * 2 * 2 == 2) // 是文件夹
        itoa(ppt.sons, sons, 10);
    else
        sons = "N\\A"; // 非文件夹
    outtextxy(x1 + 60, y1 + 240, sons);
    len = strlen(sons);
    // puthz(x1 + 30 + len * 10, y1 + 240, "个项目", 12, 2, BLACK);
    //  修改日期
    // puthz(x1 + 10, y1 + 280, "修改日期", 12, 2, BLACK);
    outtextxy(x1 + 60, y1 + 280, ppt.time);
    // 确定
    rectangle(x2 - 50, y2 - 25, x2 - 5, y2 - 5);
    // puthz(x2 - 45, y2 - 25, "确定", 12, 2, BLACK);

    while (1)
    {
        newmouse(&MouseX, &MouseY, &press);
        if (MouseX > x2 - 2 - 20 && MouseY > y1 + 2 && MouseX < x2 && MouseY < y1 + 20)
        {
            clrmous(MouseX, MouseY);
            setfillstyle(SOLID_FILL, RED);
            bar(x2 - 1 - 20, y1 + 1, x2 - 1, y1 + 1 + 20);
            line(x2 - 1 - 20, y1 + 1, x2 - 1, y1 + 1 + 20);
            line(x2 - 1 - 20, y1 + 1 + 20, x2 - 1, y1 + 1);
            while (1)
            {
                newmouse(&MouseX, &MouseY, &press);
                // result = mouse_press(610, 0, 640, 30);
                int flag = 0; // 是否在框内，不调用mouse_press因为它的return=0也可以是按下鼠标未弹起

                if (MouseX > x2 - 2 - 20 && MouseY > y1 + 2 && MouseX < x2 && MouseY < y1 + 20 && press == 1)
                {
                    clrmous(MouseX, MouseY);
                    return;
                }
                if (MouseX > x2 - 2 - 20 && MouseY > y1 + 2 && MouseX < x2 && MouseY < y1 + 20)
                    flag = 1;
                if (flag == 0)
                {
                    clrmous(MouseX, MouseY);
                    setfillstyle(SOLID_FILL, WHITE);
                    bar(x2 - 1 - 20, y1 + 1, x2 - 1, y1 + 1 + 20);
                    rectangle(x2 - 2 - 20, y1 + 2, x2, y1 + 20);
                    line(x2 - 1 - 20, y1 + 1, x2 - 1, y1 + 1 + 20);
                    line(x2 - 1 - 20, y1 + 1 + 20, x2 - 1, y1 + 1);
                    break;
                }
            }
        }
    }
}