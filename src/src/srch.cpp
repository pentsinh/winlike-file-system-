// #include <stdio.h>
// #include <stdlib.h>
// #include <graphics.h>
// #include <dos.h>
// #include <conio.h>
// #include <bios.h>
// #include <string.h>
#include "include.h"

// 搜索
int srch_input(char target[16], struct file_info *info, void *buffer)
{
    static char pre_target[16]; // 上一次循环的target
    int result = getbuffer_keybd(target, 16);
    if (result == 2) // 如果按下回车
    {
        int position = 0;
        info_init(info);
        loading(buffer);
        srch("C:\\PROJECT", target, &position, info, 0); // 这里只能进行小范围搜索，大范围搜索会出现遗漏甚至找不到的情况
        // srch("C:\\", target, &position, info, 0);
        // srch("C:\\BORLANDC", target, &position, info, 0);
        return 2;
    }
    if (result == 1) // 如果用户输入了
        return 1;
    else
        return 0;
}

// 启动搜索！！！参数：搜索路径，目标，将要存入info的位置，用于存放信息的info数组,递归深度
void srch(char *path, char *target, int *position, struct file_info *info, int depth)
{
    DIR *dir;
    struct dirent *entry;

    dir = opendir(path);
    // printf("preparing to srch %s\n", path);
    if (!dir)
    {
        perror("Failed to open directory");
        return; // 如果打开目录失败，停止读取
    }
    // printf("start srch %s\n", path);

    while ((entry = readdir(dir)) != NULL)
    {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        // printf("checking %s : ", entry->d_name);

        char *file_path = get_file_path(path, entry->d_name);

        // printf("%s\n", file_path);

        if (!file_path)
        {
            closedir(dir);
            free(file_path);
            return;
        }

        if (get_file_type(file_path) == 2)
        {
            if (strcmp(entry->d_name, target) == 0 && (*position) < 10)
            {
                // printf("find %s\n", path);
                get_file_info(path, entry->d_name, info + (*position));
                (*position)++;
            }
            if (depth < 7) // 限制递归深度
                srch(file_path, target, position, info, depth + 1);
        }
        else
        {
            if (strcmp(entry->d_name, target) == 0 && (*position) < 10)
            {
                // printf("find %s\n", path);
                get_file_info(path, entry->d_name, info + (*position));
                (*position)++;
            }
        }

        free(file_path);
    }
    // printf("srch %s OK\n", path);

    closedir(dir);
}

void srch_output(char path[1024], struct file_info *info, struct My_filenode *root, char *target)
{
    cleardevice();
    setcolor(WHITE);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    clearRectangle(120, 70, 640, 480, BLACK);
    load_main(info, 1);
    load_all(path, info, root, target, 1);
}
