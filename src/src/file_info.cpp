// BC��DIRENT.H����struct dirent��Աֻ��һ�������֣���readdirֻ�ܸ����ã�
// Ϊ�˻�ȡ��ȫ����ļ���Ϣ��ʹ��DIR.H�����struct ffblk��
// �������������ݣ�����������д�Ļ�ȡ�ļ���Ϣ�ĺ������治��ʹ��struct dirent

// ��ȡ�ļ�����ʱ����bug���������ض��ļ�����ʱ����;ͨ���Ų����������get_file_type_plus��

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

void get_file_info(char *half_path, char *name, struct file_info *info) // ��ȡ�ļ���Ϣ
{
    struct stat file_stat;
    char full_path[FILENAME_MAX] = {0}; // �������·��
    struct tm *local_time;              // �� time_t ת��Ϊ����ʱ��� struct tm
    char formatted_time[20];            // ���ڴ洢��ʽ������ַ���

    // ��������·��
    // snprintf(full_path, sizeof(full_path), "./%s", name);//Ȼ�첢���������ȴ�����������ʱ�Ż�

    strcpy(full_path, half_path);
    strcat(full_path, "\\");
    strcat(full_path, name);
    // printf("%s\n", full_path);

    // ��ȡ�ļ�״̬��Ϣ
    if (stat(full_path, &file_stat) == -1)
    {
        // printf("error\n");
        perror("stat");
        return;
    }

    // ��ȡ�ļ���
    // info->name = (char *)realloc(info->name, strlen(name) * sizeof(char));
    strcpy(info->name, name);

    // ��ȡ�ļ�����·��
    char *file_path = get_file_path(half_path, name);
    if (file_path != NULL)
    {
        strcpy(info->path, file_path);
        free(file_path); // �ͷŶ�̬������ڴ�
    }
    else
        strcpy(info->path, "unknown"); // �����ڴ����ʧ�ܵ����

    // ��ȡ�ļ�����
    // strcpy(info->type, get_file_type(full_path));
    info->flag = get_file_type(full_path);

    // ��ȡ�ļ���С
    ltoa(file_stat.st_size, info->size, 10);
    // info->size = (char *)realloc(info->size, strlen(info->size) * sizeof(char) + sizeof("byte"));
    strcat(info->size, " byte");

    // ��ȡ����޸�ʱ��
    local_time = localtime(&file_stat.st_mtime);
    strftime(formatted_time, sizeof(formatted_time), "%Y/%m/%d %H:%M", local_time); // ��ʽ��ʱ��
                                                                                    // info->time = (char *)realloc(info->time, strlen(formatted_time) * sizeof(char));
    strcpy(info->time, formatted_time);
    //  strcpy(info->time, ltoa((long)file_stat.st_mtime,formatted_time,10));

    // gc_collect();
}

// unsigned char get_file_type(char *filename) // ��ȡ�ļ����ͣ��˴��������·��
// {
//     struct ffblk ffblk; // �ļ���Ϣ������DIR.H�еĽṹ��
//     int done = findfirst(filename, &ffblk, FA_DIREC | FA_ARCH);

//     if (ffblk.ff_attrib & FA_DIREC)
//     {
//         if (strchr(filename, '.') != NULL) // ������Ϊ�˴���.ovl�ļ�
//             return 15;
//         else
//             return 2; // Ŀ¼
//     }
//     else if (ffblk.ff_attrib & FA_ARCH)
//     {
//         return get_file_type_plus(filename);
//         // return "�ļ�";
//     }
//     return 15; // δ֪����
// }

unsigned char get_file_type(char *filename) // ��ȡ�ļ����ͣ��˴��������·��
{
    struct ffblk ffblk; // �ļ���Ϣ������DIR.H�еĽṹ��
    int done = findfirst(filename, &ffblk, FA_DIREC | FA_ARCH);

    if (done == 0) // ����ҵ��ļ�
    {
        if (ffblk.ff_attrib & FA_DIREC)
        {
            if (strchr(filename, '.') != NULL) // ������Ϊ�˴���.ovl�ļ�
                return 15;
            else
                return 2; // Ŀ¼
        }
        else if (ffblk.ff_attrib & FA_ARCH)
        {
            return get_file_type_plus(filename);
        }
    }
    return 15; // δ֪����
}

unsigned char get_file_type_plus(char *filename) // ��һ����ȡ�ļ�����
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
    char *dot = strrchr(filename, '.'); // ָ���ļ���׺��ǰ��ġ�.��
    if (dot)
    {
        // �ж��ļ�����
        for (i = 0; i < 16; i++)
            if (!strcmp(dot + 1, file_type_strings[i]))
                return i;
    }
    else
        return 15;
}

// char *get_file_path(char *father_path, char *name) // ��ȡ�ļ�����·��
// {
//     size_t path_len = strlen(father_path);
//     if (path_len > 0 && father_path[path_len - 1] != '\\')
//     {
//         // ����ڵ�·�����Է�б�ܽ�β������ӷ�б��
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
//         // ����ڵ�·���Է�б�ܽ�β����ֱ��ƴ���ļ���
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

    // �����Ƿ���Ҫ��ӷ�б���������ڴ�
    if (path_len > 0 && father_path[path_len - 1] != '\\')
    {
        path = (char *)malloc(path_len + name_len + 2); // +2 ��Ϊ�����ɷ�б�ܺ��ַ���������
        if (path == NULL)
        {
            return NULL; // �ڴ����ʧ��
        }
        sprintf(path, "%s\\%s", father_path, name); // ƴ��·��
    }
    else
    {
        path = (char *)malloc(path_len + name_len + 1); // +1 ��Ϊ�������ַ���������
        if (path == NULL)
        {
            return NULL; // �ڴ����ʧ��
        }
        sprintf(path, "%s%s", father_path, name); // ƴ��·��
    }

    return path;
}