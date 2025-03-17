/*
垃圾回收，回收内存碎片
*/
#ifndef GC_H
#define GC_H

#include <stdlib.h>

// 分配内存
void *gc_malloc(size_t size);

// 触发垃圾回收
void gc_collect();

#endif // GC_H