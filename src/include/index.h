#ifndef _INDEX_H_
#define _INDEX_H_
#include "include.h"
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
	// char *time; // 修改日期
	// char *size; // 大小
	struct My_filenode *next;
	struct My_filenode *father;		   // 同一条链用同一个父节点（为了做返回上一级功能）
	struct My_filenode *son_list_head; // 一个父节点拥有子链的头节点地址
};

/************************************************
 *FUNCTION:目录树构建
 *INPUT:目录树的根，递归限制深度
 *RETURN:无
 *************************************************/
void tree_make(struct My_filenode *node, int depth);

/************************************************
 *FUNCTION:获取节点绝对路径
 *INPUT:目标节点
 *RETURN:绝对路径
 *************************************************/
char *get_node_path(struct My_filenode *node);

/************************************************
 *FUNCTION: 获取某目录下某文件（夹）的绝对路径
 *INPUT:目录节点，目录下的文件名
 *RETURN:绝对路径
 *************************************************/
char *get_file_path_node(struct My_filenode *node, char *filename);

/************************************************
 *FUNCTION:从左栏直接点击文件夹，获取文件路径#####基于左栏最多展开三级目录的前提#####
 *INPUT:目录树的根，鼠标X，鼠标Y
 *RETURN:文件夹绝对路径
 *************************************************/
char *get_file_path_left(struct My_filenode *node, int x, int y);

/************************************************
 *FUNCTION:计算可见子目录数量
 *INPUT:目录节点
 *RETURN:可见子目录数量
 *************************************************/
int count_son_visible(struct My_filenode *node);

/************************************************
 *FUNCTION:计算可见子目录及其可见子目录数量
 *INPUT:目录节点
 *RETURN:可见子目录及其可见子目录数量
 *************************************************/
int count_son_son_visible(struct My_filenode *node);

/************************************************
 *FUNCTION:点击>展开目录
 *INPUT:目录树的根，鼠标X，鼠标Y
 *RETURN:返回1：展开；返回2：收起
 *************************************************/
int unfold(struct My_filenode *node, int x, int y);

/************************************************
 *FUNCTION:折叠传入节点的所有子目录
 *INPUT:目录节点
 *RETURN:无
 *************************************************/
void fold_sonlist(struct My_filenode *node);

#endif // !_INDEX_H_
