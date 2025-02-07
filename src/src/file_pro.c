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

char* get_file_type(struct  ffblk* entry)//��ȡ�ļ�����
{
    
    const char* dot;//ָ���ļ���׺��ǰ��ġ�.��
    switch (entry->ff_attrib)
    {
        case FA_DIREC:
            return "�ļ���";
        case FA_ARCH:
        {
            strcpy(dot, strrchr(entry->ff_name, '.'));
            if (dot && !strcmp(dot, ".txt")) 
            {
                return "�ı��ĵ�";
            }
            else if (dot && !strcmp(dot, ".c")) 
            {
                return "C Source";
            }
            else 
            {
                return "δ֪����";
            }
        }        
        default:
            return "δ֪����";            
    }
}