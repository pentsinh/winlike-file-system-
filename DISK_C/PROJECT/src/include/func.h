#ifndef _FUNC_H_
#define _FUNC_H_
#include "include.h"
int func(struct file_info *info, char *source_path, int *sort_mode, int *UpOrDown, char **sort_menu_p);
void build(struct file_info *info, int x, int y);
int copy(struct file_info *info, char *source_path);
int paste(char *source_path, int *flag);
void del(struct file_info *info);
int cut(struct file_info *file, int *flag, char *source_path);
void frename(struct file_info *info);

#endif
