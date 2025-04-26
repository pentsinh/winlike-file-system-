

#include "include.h"
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

    strcpy(full_path, half_path);
    if (strcmp(half_path, "C:\\") != 0)
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
    info->flag = get_file_type(full_path);

    // ��ȡ�ļ���С
    ltoa(file_stat.st_size, info->size, 10);
    strcat(info->size, " byte");

    // ��ȡ����޸�ʱ��
    local_time = localtime(&file_stat.st_mtime);
    strftime(formatted_time, sizeof(formatted_time), "%Y/%m/%d %H:%M", local_time); // ��ʽ��ʱ��
    strcpy(info->time, formatted_time);

    // ��ȡ������Ŀ����
    if (info->flag == 2) // Ŀ¼
        info->sons = count_sons(info->path);
    else
        info->sons = -1;
}

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
        return 15;
    }
    else
        return 15;
}

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

// info����ʼ��
void info_init(struct file_info *info)
{
    for (int i = 0; i < INFO_LENGTH; i++)
    {
        (info + i)->num = 0;
        strcpy((info + i)->name, "");
        (info + i)->flag = 0;
        strcpy((info + i)->path, "");
        strcpy((info + i)->size, "");
        strcpy((info + i)->time, "");
    }
}

// ��ʽ��ʱ��ת��Ϊʱ���
time_t formatted_tm_to_stamp(char *formatted_time)
{
    struct tm tm = {0};

    // ʹ�� sscanf �����ַ���
    if (sscanf(formatted_time, "%d/%d/%d %d:%d", &tm.tm_year, &tm.tm_mon, &tm.tm_mday, &tm.tm_hour, &tm.tm_min) == 5)
    {
        // ������ݺ��·�
        tm.tm_year -= 1900; // �����Ҫ��ȥ 1900
        tm.tm_mon -= 1;     // �·���Ҫ��ȥ 1

        // ת��Ϊʱ���
        return mktime(&tm);
    }
}

// ��ȡ��Чinfo����
int get_info_num(struct file_info *info)
{
    int num = 0;
    int i = 0; // ѭ������

    while (strcmp((info + i)->name, "") != 0 && num < INFO_LENGTH)
    {
        num++;
        i++;
    }
    return num;
}

// ��ȡ���λ�õ��ļ����
int get_file_num(int x, int y, struct file_info *info)
{
    int num; // info������Ч�ļ�����
    int j;   // ѭ������
    num = get_info_num(info);
    // �����������������ļ����
    for (j = 0; j < num; j++)
        if (y > 90 + j * 20 && y < 90 + j * 20 + 20)
            return j + 1;

    return -1;
}

//  �ж�info�����Ƿ����Ѿ�ѡ�е��ļ�
int is_selected(struct file_info *info)
{
    int i; // ѭ������
    for (i = 0; i < INFO_LENGTH; i++)
        if (get_bit((info + i)->flag, 7) == 1)
            return (info + i)->num;
    return 0;
}

// ���������Ŀ����
int count_sons(char *path)
{
    DIR *dir;
    struct dirent *entry;
    int num = 0; // ����
    int j = 0;   // ѭ������
    dir = opendir(path);
    if (!dir)
    {
        perror("Failed to open directory");
        return -1; // �����Ŀ¼ʧ�ܣ�ֹͣ��ȡ
    }
    while ((entry = readdir(dir)) != NULL)
    {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;
        if (strcmp(entry->d_name, "\0") != 0)
            num++;
        j++;
        if (j >= INFO_LENGTH) //***********��ʱֻ��ȡ10��
            break;
    }
    closedir(dir);
    return num;
}

// ���㴫���ļ�����Ŀ¼
char *get_father_path(char *path)
{
    if (strchr(path, '\\') == NULL)
        return path;
    else
    {
        int flag = 0;           // ѭ���˳���־
        int len = strlen(path); // path����
        int i = len - 1;        // Ѱ��������
        char tmp[1024];
        strcpy(tmp, path);
        do
        {
            if (tmp[i] == '\\')
                flag = 1;
            tmp[i] = '\0';
            i = i - 1;
        } while (flag != 1);
        return tmp;
    }
}

// �Ӿ���·����ȡ�ļ���
char *path_to_name(char *path)
{
    if (strcmp(path, "C:\\") == 0)
        return path;
    char *name;
    if (strchr(path, '\\') == NULL)
        return path;
    else
    {
        name = strchr(path, '\\') + 1;
        return path_to_name(name);
    }
}

// ȫѡ
void select_all(struct file_info *info)
{
    if (info == NULL)
        return;
    else
        for (int i = 0; i < get_info_num(info); i++)
            set_bit(&(info + i)->flag, 7, 1);
}

// ȫ��ѡ
void unselect_all(struct file_info *info)
{
    if (info == NULL)
        return;
    else
        for (int i = 0; i < get_info_num(info); i++)
            set_bit(&(info + i)->flag, 7, 0);
}

// ������ѡ��
void select_name(struct file_info *info, char *name)
{
    for (int i = 0; i < get_info_num(info); i++)
    {
        if (strcmp(name, (info + i)->name) == 0)
        {
            set_bit(&(info + i)->flag, 7, 1);
            return;
        }
    }
}