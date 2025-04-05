#include "include.h"
// 排序
void sort(struct file_info *info, unsigned char sort_mode, int UpOrDown)
{
    int num; // info的有效数据量
    int i;   // 循环变量
    int j;   // 循环变量

    num = get_info_num(info);
    // printf("num=%d\n", num);
    // printf("UpOrDown=%d\n", UpOrDown);
    switch (sort_mode)
    {
    case 0: // name
    {
        for (i = 0; i < num - 1; i++)
        {
            for (j = 0; j < num - i - 1; j++)
            {
                // 下面利用了strcmp返回值正负的含义（比如，前者更小，strcmp返回负值，此时UpOrDown为负值即逆序，那么交换）
                if (strcmp((info + j)->name, (info + j + 1)->name) * UpOrDown > 0)
                    swp_info((info + j), (info + j + 1));
            }
        }
        break;
    }
    case 1: // date
    {
        for (i = 0; i < num - 1; i++)
        {
            for (j = 0; j < num - i - 1; j++)
            {
                time_t time_1 = formatted_tm_to_stamp((info + j)->time);
                time_t time_2 = formatted_tm_to_stamp((info + j + 1)->time);
                if ((time_1 - time_2) * UpOrDown > 0)
                    swp_info(info + j, info + j + 1);
            }
        }
        break;
    }
    case 2: // type
    {
        for (i = 0; i < num - 1; i++)
        {
            for (j = 0; j < num - i - 1; j++)
            {
                // 这里只记录flag的前四位，并转化为十进制
                unsigned char flag;

                flag = (info + j)->flag;
                int flag_1 = get_bit(flag, 0) * 1 + get_bit(flag, 1) * 2 + get_bit(flag, 2) * 2 * 2 + get_bit(flag, 3) * 2 * 2 * 2;

                flag = (info + j + 1)->flag;
                int flag_2 = get_bit(flag, 0) * 1 + get_bit(flag, 1) * 2 + get_bit(flag, 2) * 2 * 2 + get_bit(flag, 3) * 2 * 2 * 2;

                if ((flag_1 - flag_2) * UpOrDown > 0)
                    swp_info(info + j, info + j + 1);
            }
        }
        break;
    }
    case 3: // size
    {
        for (i = 0; i < num - 1; i++)
        {
            for (j = 0; j < num - i - 1; j++)
            {
                // 先去除" byte"，然后转化为int
                char size[16];

                strcpy(size, (info + j)->size);
                *strchr(size, ' ') = '\0';
                int size_1 = atoi(size);

                strcpy(size, (info + j + 1)->size);
                *strchr(size, ' ') = '\0';
                int size_2 = atoi(size);

                if ((size_1 - size_2) * UpOrDown > 0)
                    swp_info(info + j, info + j + 1);
            }
        }
        break;
    }
    default:
        break;
    }

    // 重新标号
    for (i = 0; i < num; i++)
        (info + i)->num = i + 1;
}

// 交换两个info
void swp_info(struct file_info *info_1, struct file_info *info_2)
{
    if (info_1 == NULL || info_2 == NULL)
        return;
    // printf("swapping [%s][%d] with [%s][%d]\n", info_1->name, info_1->name, info_2->name, info_2->name);
    struct file_info tmp; // 交换中间量
    tmp = *info_1;
    *info_1 = *info_2;
    *info_2 = tmp;
    //  printf("swapped [%s][%d] with [%s][%d]", info_2->name, info_2->name, info_1->name, info_1->name);
}
