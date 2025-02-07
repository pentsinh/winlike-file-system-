#include <stdio.h>
#include <dirent.h>
#include <direct.h>
#include <sys/stat.h>

#include "include.h"

#ifndef FA_DIREC
#define FA_DIREC 0x10
#endif

#ifndef FA_ARCH
#define FA_ARCH 0x20
#endif

char* get_file_type(struct  ffblk* entry)//获取文件类型
{
    
    const char* dot;//指向文件后缀名前面的“.”
    switch (entry->ff_attrib)
    {
        case FA_DIREC:
            return "文件夹";
        case FA_ARCH:
        {
            strcpy(dot, strrchr(entry->ff_name, '.'));
            if (dot && !strcmp(dot, ".txt")) 
            {
                return "文本文档";
            }
            else if (dot && !strcmp(dot, ".c")) 
            {
                return "C Source";
            }
            else 
            {
                return "未知类型";
            }
        }        
        default:
            return "未知类型";            
    }
}