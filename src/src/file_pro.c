//BC的DIRENT.H里面struct dirent成员只有一个：名字，而readdir只能跟他用；
//为了获取更全面的文件信息，使用DIR.H里面的struct ffblk，
//以上两个不兼容，所以在下面写的获取文件信息的函数里面不再使用struct dirent

//读取文件类型时存在bug，在遇到特定文件类型时卡死;通过排查问题可能在get_file_type_plus里
//文件最后修改时间怎么搞？


#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <direct.h>
#include <time.h>
#include <sys/stat.h>

#include "include.h"

#ifndef FA_DIREC
#define FA_DIREC 0x10
#endif

#ifndef FA_ARCH
#define FA_ARCH 0x20
#endif



void get_file_info(char* name, struct file_info* info)//获取文件信息
{
    struct stat file_stat;
    char full_path[FILENAME_MAX] = { 0 };//存放完整路径    
    struct tm* local_time; // 将 time_t 转换为本地时间的 struct tm   
    char formatted_time[20]; // 用于存储格式化后的字符串


    // 构造完整路径
    //snprintf(full_path, sizeof(full_path), "./%s", name);//然鹅并不完整，等待后面做搜索时优化
    strcpy(full_path, "./");
    strcat(full_path, name);

    // 获取文件状态信息
    if (stat(full_path, &file_stat) == -1)
    {
        perror("stat");
        return;
    }

    // 获取文件名
    strcpy(info->name, name);

    // 获取文件类型
    strcpy(info->type, get_file_type(info->name));

    // 获取文件大小
    ltoa(file_stat.st_size, info->size, 10);
    strcat(info->size, " byte");

    // 获取最后修改时间
    local_time = localtime(&file_stat.st_mtime);
    strftime(formatted_time, sizeof(formatted_time), "%Y/%m/%d %H:%M", local_time); // 格式化时间
    strcpy(info->time, formatted_time);
	//strcpy(info->time, ltoa((long)file_stat.st_mtime,formatted_time,10));

}


char* get_file_type(char* filename)//获取文件类型
{
    struct ffblk ffblk;//文件信息，采用DIR.H中的结构体
    int done = findfirst(filename, &ffblk, FA_DIREC | FA_ARCH);

    if (ffblk.ff_attrib & FA_DIREC)
    {
        return "Fold"; // 目录
    }
    else if (ffblk.ff_attrib & FA_ARCH) 
    {
        return get_file_type_plus(filename); 
        //return "文件";
    }
    return "Unknown"; // 未知类型
}


char* get_file_type_plus(char* filename)//进一步获取文件类型
{
    char* dot = strrchr(filename, '.');//指向文件后缀名前面的“.”    
    if (dot && !strcmp(dot, ".TXT"))
        return "Text File";
    else if (dot && !strcmp(dot, ".C"))
        return "C Source";
    else if (dot && !strcmp(dot, ".PRJ"))
        return "Project File";
    else if (dot && !strcmp(dot, ".MD"))
        return "Markdowm Source";
    else if (dot && !strcmp(dot, ".DSK"))
        return "Disk Image File";
    else    
        return "Unknown";
}