//BC��DIRENT.H����struct dirent��Աֻ��һ�������֣���readdirֻ�ܸ����ã�
//Ϊ�˻�ȡ��ȫ����ļ���Ϣ��ʹ��DIR.H�����struct ffblk��
//�������������ݣ�����������д�Ļ�ȡ�ļ���Ϣ�ĺ������治��ʹ��struct dirent

//��ȡ�ļ�����ʱ����bug���������ض��ļ�����ʱ����;ͨ���Ų����������get_file_type_plus��
//�ļ�����޸�ʱ����ô�㣿


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



void get_file_info(char* name, struct file_info* info)//��ȡ�ļ���Ϣ
{
    struct stat file_stat;
    char full_path[FILENAME_MAX] = { 0 };//�������·��    
    struct tm* local_time; // �� time_t ת��Ϊ����ʱ��� struct tm   
    char formatted_time[20]; // ���ڴ洢��ʽ������ַ���


    // ��������·��
    //snprintf(full_path, sizeof(full_path), "./%s", name);//Ȼ�첢���������ȴ�����������ʱ�Ż�
    strcpy(full_path, "./");
    strcat(full_path, name);

    // ��ȡ�ļ�״̬��Ϣ
    if (stat(full_path, &file_stat) == -1)
    {
        perror("stat");
        return;
    }

    // ��ȡ�ļ���
    strcpy(info->name, name);

    // ��ȡ�ļ�����
    strcpy(info->type, get_file_type(info->name));

    // ��ȡ�ļ���С
    ltoa(file_stat.st_size, info->size, 10);
    strcat(info->size, " byte");

    // ��ȡ����޸�ʱ��
    local_time = localtime(&file_stat.st_mtime);
    strftime(formatted_time, sizeof(formatted_time), "%Y/%m/%d %H:%M", local_time); // ��ʽ��ʱ��
    strcpy(info->time, formatted_time);
	//strcpy(info->time, ltoa((long)file_stat.st_mtime,formatted_time,10));

}


char* get_file_type(char* filename)//��ȡ�ļ�����
{
    struct ffblk ffblk;//�ļ���Ϣ������DIR.H�еĽṹ��
    int done = findfirst(filename, &ffblk, FA_DIREC | FA_ARCH);

    if (ffblk.ff_attrib & FA_DIREC)
    {
        return "Fold"; // Ŀ¼
    }
    else if (ffblk.ff_attrib & FA_ARCH) 
    {
        return get_file_type_plus(filename); 
        //return "�ļ�";
    }
    return "Unknown"; // δ֪����
}


char* get_file_type_plus(char* filename)//��һ����ȡ�ļ�����
{
    char* dot = strrchr(filename, '.');//ָ���ļ���׺��ǰ��ġ�.��    
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