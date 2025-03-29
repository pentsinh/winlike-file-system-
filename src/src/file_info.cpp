// BC的DIRENT.H里面struct dirent成员只有一个：名字，而readdir只能跟他用；
// 为了获取更全面的文件信息，使用DIR.H里面的struct ffblk，
// 以上两个不兼容，所以在下面写的获取文件信息的函数里面不再使用struct dirent

// 读取文件类型时存在bug，在遇到特定文件类型时卡死;通过排查问题可能在get_file_type_plus里

// #include <stdio.h>
// #include <dirent.h>
// #include <string.h>
// #include <stdlib.h>
// #include <direct.h>
// #include <time.h>
// #include <sys/stat.h>

#include "include.h"
// #include "bit_pro.h"
#ifndef FA_DIREC
#define FA_DIREC 0x10
#endif

#ifndef FA_ARCH
#define FA_ARCH 0x20
#endif

// extern enum file;

void get_file_info(char *half_path, char *name, struct file_info *info) // 获取文件信息
{
    struct stat file_stat;
    char full_path[FILENAME_MAX] = {0}; // 存放完整路径
    struct tm *local_time;              // 将 time_t 转换为本地时间的 struct tm
    char formatted_time[20];            // 用于存储格式化后的字符串

    // 构造完整路径
    // snprintf(full_path, sizeof(full_path), "./%s", name);//然鹅并不完整，等待后面做搜索时优化

    strcpy(full_path, half_path);
    strcat(full_path, "\\");
    strcat(full_path, name);
    // printf("%s\n", full_path);

    // 获取文件状态信息
    if (stat(full_path, &file_stat) == -1)
    {
        // printf("error\n");
        perror("stat");
        return;
    }

    // 获取文件名
    // info->name = (char *)realloc(info->name, strlen(name) * sizeof(char));
    strcpy(info->name, name);

    // 获取文件绝对路径
    char *file_path = get_file_path(half_path, name);
    if (file_path != NULL)
    {
        strcpy(info->path, file_path);
        free(file_path); // 释放动态分配的内存
    }
    else
        strcpy(info->path, "unknown"); // 处理内存分配失败的情况

    // 获取文件类型
    // strcpy(info->type, get_file_type(full_path));
    info->flag = get_file_type(full_path);

    // 获取文件大小
    ltoa(file_stat.st_size, info->size, 10);
    // info->size = (char *)realloc(info->size, strlen(info->size) * sizeof(char) + sizeof("byte"));
    strcat(info->size, " byte");

    // 获取最后修改时间
    local_time = localtime(&file_stat.st_mtime);
    strftime(formatted_time, sizeof(formatted_time), "%Y/%m/%d %H:%M", local_time); // 格式化时间
                                                                                    // info->time = (char *)realloc(info->time, strlen(formatted_time) * sizeof(char));
    strcpy(info->time, formatted_time);
    //  strcpy(info->time, ltoa((long)file_stat.st_mtime,formatted_time,10));

    // gc_collect();
}

// unsigned char get_file_type(char *filename) // 获取文件类型，此处传入绝对路径
// {
//     struct ffblk ffblk; // 文件信息，采用DIR.H中的结构体
//     int done = findfirst(filename, &ffblk, FA_DIREC | FA_ARCH);

//     if (ffblk.ff_attrib & FA_DIREC)
//     {
//         if (strchr(filename, '.') != NULL) // 这里是为了处理.ovl文件
//             return 15;
//         else
//             return 2; // 目录
//     }
//     else if (ffblk.ff_attrib & FA_ARCH)
//     {
//         return get_file_type_plus(filename);
//         // return "文件";
//     }
//     return 15; // 未知类型
// }

unsigned char get_file_type(char *filename) // 获取文件类型，此处传入绝对路径
{
    struct ffblk ffblk; // 文件信息，采用DIR.H中的结构体
    int done = findfirst(filename, &ffblk, FA_DIREC | FA_ARCH);

    if (done == 0) // 如果找到文件
    {
        if (ffblk.ff_attrib & FA_DIREC)
        {
            if (strchr(filename, '.') != NULL) // 这里是为了处理.ovl文件
                return 15;
            else
                return 2; // 目录
        }
        else if (ffblk.ff_attrib & FA_ARCH)
        {
            return get_file_type_plus(filename);
        }
    }
    return 15; // 未知类型
}

unsigned char get_file_type_plus(char *filename) // 进一步获取文件类型
{
    int i;
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
    char *dot = strrchr(filename, '.'); // 指向文件后缀名前面的“.”
    if (dot)
    {
        // 判断文件类型
        for (i = 0; i < 16; i++)
            if (!strcmp(dot + 1, file_type_strings[i]))
                return i;
    }
    else
        return 15;
}

// char *get_file_path(char *father_path, char *name) // 获取文件绝对路径
// {
//     size_t path_len = strlen(father_path);
//     if (path_len > 0 && father_path[path_len - 1] != '\\')
//     {
//         // 如果节点路径不以反斜杠结尾，则添加反斜杠
//         char *path = (char *)malloc(path_len + strlen(name) + 2);
//         if (path == NULL)
//         {
//             return NULL;
//         }
//         sprintf(path, "%s\\%s", father_path, name);
//         return path;
//     }
//     else
//     {
//         // 如果节点路径以反斜杠结尾，则直接拼接文件名
//         char *path = (char *)malloc(path_len + strlen(name) + 1);
//         if (path == NULL)
//         {
//             return NULL;
//         }
//         sprintf(path, "%s%s", path, name);
//         return path;
//     }
// }

char *get_file_path(char *father_path, char *name)
{
    size_t path_len = strlen(father_path);
    size_t name_len = strlen(name);
    char *path = NULL;

    // 根据是否需要添加反斜杠来分配内存
    if (path_len > 0 && father_path[path_len - 1] != '\\')
    {
        path = (char *)malloc(path_len + name_len + 2); // +2 是为了容纳反斜杠和字符串结束符
        if (path == NULL)
        {
            return NULL; // 内存分配失败
        }
        sprintf(path, "%s\\%s", father_path, name); // 拼接路径
    }
    else
    {
        path = (char *)malloc(path_len + name_len + 1); // +1 是为了容纳字符串结束符
        if (path == NULL)
        {
            return NULL; // 内存分配失败
        }
        sprintf(path, "%s%s", father_path, name); // 拼接路径
    }

    return path;
}