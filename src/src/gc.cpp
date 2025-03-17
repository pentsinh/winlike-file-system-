#include "gc.h"
#include <stdio.h>
#include <string.h>

// 定义一个节点结构体，用于管理内存块
typedef struct node
{
    struct node *next;
    int used;    // 标记该节点是否已被使用
    void *data;  // 指向数据的指针
    size_t size; // 数据的大小
} node;

// 全局变量，用于管理空闲节点链表
static node *head = NULL;
static node *next_free = NULL;

// 查找空闲节点
static node *find_idle_node()
{
    for (next_free = head; next_free && next_free->used; next_free = next_free->next)
    {
    }
    if (!next_free)
    {
        // 如果找不到空闲节点，则触发垃圾回收
        gc_collect();
        for (next_free = head->next; next_free && next_free->used; next_free = next_free->next)
        {
        }
    }
    if (!next_free)
    {
        printf("Allocation Failed! OutOfMemory...\n");
        abort();
    }
    return next_free;
}

// 分配新对象
void *gc_malloc(size_t size)
{
    node *_node = next_free;
    if (!next_free || next_free->used)
    {
        find_idle_node();
    }

    _node->used = 1;
    _node->size = size;
    next_free = next_free->next;

    // 分配内存
    _node->data = malloc(size);
    if (!_node->data)
    {
        printf("Memory allocation failed!\n");
        abort();
    }

    return _node->data;
}

// 标记对象
static void mark(node *cur)
{
    if (!cur || cur->used)
    {
        return;
    }
    cur->used = 1;
    // 这里可以递归标记对象引用的其他对象
}

// 垃圾回收函数
void gc_collect()
{
    node *cur;
    // 标记阶段：从根对象开始标记所有可达对象
    for (cur = head; cur; cur = cur->next)
    {
        mark(cur);
    }

    // 清除阶段：回收未标记的对象
    for (cur = head; cur; cur = cur->next)
    {
        if (!cur->used)
        {
            // 如果对象未被标记，则回收该对象
            free(cur->data);
            cur->data = NULL;
            cur->size = 0;
        }
        else
        {
            // 如果对象被标记，则清除标记
            cur->used = 0;
        }
    }
}