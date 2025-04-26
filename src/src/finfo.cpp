

#include "include.h"
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

    strcpy(full_path, half_path);
    if (strcmp(half_path, "C:\\") != 0)
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
    info->flag = get_file_type(full_path);

    // 获取文件大小
    ltoa(file_stat.st_size, info->size, 10);
    strcat(info->size, " byte");

    // 获取最后修改时间
    local_time = localtime(&file_stat.st_mtime);
    strftime(formatted_time, sizeof(formatted_time), "%Y/%m/%d %H:%M", local_time); // 格式化时间
    strcpy(info->time, formatted_time);

    // 获取包含项目数量
    if (info->flag == 2) // 目录
        info->sons = count_sons(info->path);
    else
        info->sons = -1;
}

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

// info链初始化
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

// 格式化时间转换为时间戳
time_t formatted_tm_to_stamp(char *formatted_time)
{
    struct tm tm = {0};

    // 使用 sscanf 解析字符串
    if (sscanf(formatted_time, "%d/%d/%d %d:%d", &tm.tm_year, &tm.tm_mon, &tm.tm_mday, &tm.tm_hour, &tm.tm_min) == 5)
    {
        // 调整年份和月份
        tm.tm_year -= 1900; // 年份需要减去 1900
        tm.tm_mon -= 1;     // 月份需要减去 1

        // 转换为时间戳
        return mktime(&tm);
    }
}

// 获取有效info数量
int get_info_num(struct file_info *info)
{
    int num = 0;
    int i = 0; // 循环变量

    while (strcmp((info + i)->name, "") != 0 && num < INFO_LENGTH)
    {
        num++;
        i++;
    }
    return num;
}

// 获取点击位置的文件标号
int get_file_num(int x, int y, struct file_info *info)
{
    int num; // info链中有效文件数量
    int j;   // 循环变量
    num = get_info_num(info);
    // 查找鼠标点击的区域的文件序号
    for (j = 0; j < num; j++)
        if (y > 90 + j * 20 && y < 90 + j * 20 + 20)
            return j + 1;

    return -1;
}

//  判断info链中是否有已经选中的文件
int is_selected(struct file_info *info)
{
    int i; // 循环变量
    for (i = 0; i < INFO_LENGTH; i++)
        if (get_bit((info + i)->flag, 7) == 1)
            return (info + i)->num;
    return 0;
}

// 计算包含项目数量
int count_sons(char *path)
{
    DIR *dir;
    struct dirent *entry;
    int num = 0; // 数量
    int j = 0;   // 循环变量
    dir = opendir(path);
    if (!dir)
    {
        perror("Failed to open directory");
        return -1; // 如果打开目录失败，停止读取
    }
    while ((entry = readdir(dir)) != NULL)
    {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;
        if (strcmp(entry->d_name, "\0") != 0)
            num++;
        j++;
        if (j >= INFO_LENGTH) //***********暂时只读取10个
            break;
    }
    closedir(dir);
    return num;
}

// 计算传入文件所在目录
char *get_father_path(char *path)
{
    if (strchr(path, '\\') == NULL)
        return path;
    else
    {
        int flag = 0;           // 循环退出标志
        int len = strlen(path); // path长度
        int i = len - 1;        // 寻呼按变量
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

// 从绝对路径获取文件名
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

// 全选
void select_all(struct file_info *info)
{
    if (info == NULL)
        return;
    else
        for (int i = 0; i < get_info_num(info); i++)
            set_bit(&(info + i)->flag, 7, 1);
}

// 全不选
void unselect_all(struct file_info *info)
{
    if (info == NULL)
        return;
    else
        for (int i = 0; i < get_info_num(info); i++)
            set_bit(&(info + i)->flag, 7, 0);
}

// 按名字选中
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