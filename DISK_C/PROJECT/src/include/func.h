#ifndef _FUNC_H_
#define _FUNC_H_
#include "include.h"

enum
{
    NEWFILE = 0, // 新建
    CUT_PASTE,   // 剪切粘贴
    COPY_PASTE,  // 复制粘贴
    RENAME,      // 重命名
    DELETE,      // 删除
};

struct pro_history
{
    int num;           // 序号
    int process;       // 新建、粘贴、重命名、删除
    char src[128];    // 对象1
    char tar[128];    // 对象2
    char bin_path[64]; // 回收站路径
};

int func(struct file_info *info, char *source_path, int *sort_mode, int *UpOrDown, char **sort_menu_p, int *pic_flag,
         struct pro_history *history); // 处理文件操作功能
int build(struct file_info *info, int x, int y);
int copy(struct file_info *info, char *source_path);
int paste(char *source_path, int *flag);
int del(struct file_info *info, struct pro_history *history); // 删除文件或文件夹
int cut(struct file_info *file, int *flag, char *source_path);
int frename(struct file_info *info, struct pro_history *history, int pic_flag); // 重命名文件或文件夹

void new_history(struct pro_history *history, int process, char tar[128], char src[128]);                // 更新目录操作历史
void undo_pro(struct pro_history *history);                                                                // 撤销操作
void history_reset(struct pro_history *history, int num, char src[128], char tar[128], char bin_path[64]); // 初始化操作历史
void history_init(struct pro_history *history);                                                              // 初始化操作历史

#endif
