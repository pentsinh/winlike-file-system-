#ifndef _INDEX_H_
#define _INDEX_H_
// 目录树结构体
struct dir_tree
{
	char name[13];				 // 名称
	char path[1024];			 // 当前文件夹路径，包含名称
	struct dir_tree *branch[10]; // 树枝（子目录）
	int is_branch_on;			 // 子目录是否可见
};

struct My_filenode
{
	unsigned char flag;
	char name[13];
	struct My_filenode *next;
	struct My_filenode *father;		   // 同一条链用同一个父节点（为了做返回上一级功能）
	struct My_filenode *son_list_head; // 一个父节点拥有子链的头节点地址
};

// void tree_make(struct dir_tree* tree,int depth);//构建目录树
void tree_make(struct My_filenode *node, int depth);			  // 目录树构建
char *get_node_path(struct My_filenode *node);					  // 获取节点绝对路径
char *get_file_path(struct My_filenode *node, char *filename);	  // 获取某目录下某文件（夹）的绝对路径
char *get_file_path_left(struct My_filenode *node, int x, int y); // 从左栏直接点击文件夹，获取文件夹绝对路径
#endif															  // !_INDEX_H_
