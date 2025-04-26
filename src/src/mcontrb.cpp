#include "include.h"

extern time_t last_click_time; // 记录上次点击时间
extern int click_count;        // 点击次数计数器
// 辅助函数：检测完整的点击过程（从释放状态到按下状态再到释放状态）
int detect_complete_click(int press, time_t current_press_time)
{
    static int initial_press_detected = 0; // 标记是否检测到初始按下
    time_t elapsed_ticks;
    // int pid;

    if (press == 1) // 鼠标左键被按下
    {
        if (!initial_press_detected)
        {
            initial_press_detected = 1;           // 标记初始按下
            last_click_time = current_press_time; // 更新最后点击时间
            return 0;                             // 返回0表示正在按下，等待释放
        }
    }
    else if (press == 0) // 鼠标左键被释放
    {
        if (initial_press_detected)
        {
            initial_press_detected = 0; // 重置标记
            elapsed_ticks = current_press_time - last_click_time;

            if (elapsed_ticks < 12) //
            {
                click_count++;
                if (click_count == 2)
                {
                    click_count = 0;     // 重置点击计数器
                    last_click_time = 0; // 重置最后点击时间
                    // click_flag = 0;
                    return 4; // 返回双击标识
                }
            }
            else
            {
                // 如果超过双击时间间隔，视为单击
                click_count = 1;                      // 重置为单击
                last_click_time = current_press_time; // 更新最后点击时间
                // click_flag = 1;

                return 1; // 返回单击标识
            }
        }
    }

    return 0; // 默认返回值
}

int detect_m(int x1, int y1, int x2, int y2) // 检测鼠标是否在框内
{
    if (MouseX > x1 && MouseX < x2 && MouseY > y1 && MouseY < y2)
        return 1;
    else
        return 0;
}

// 如果在框外点击，返回1；否则返回0######适用于640*480######
int mouse_press_out(int x1, int y1, int x2, int y2) // 如果在框外左键，返回1；在框外右键，返回2；否则返回0
{
    if (press == 1)
    {
        if (MouseX > x1 && MouseX < x2 && MouseY > y1 && MouseY < y2)
            return 0;
        else
            return 1;
    }
    else if (press == 2)
    {
        if (MouseX > x1 && MouseX < x2 && MouseY > y1 && MouseY < y2)
            return 0;
        else
            return 2;
    }
    else
        return 0;
}