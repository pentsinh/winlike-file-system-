#ifndef _INDEX_H_
#define _INDEX_H_
//目录树结构体
struct dir_tree {
	char name[13];//名称
	char path[1024];//当前文件夹路径，包含名称
	struct dir_tree* branch[10];//树枝（子目录）
	int is_branch_on;//子目录是否可见
};

void tree_make(struct dir_tree* tree);//构建目录树

#endif // !_INDEX_H_


