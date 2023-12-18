#include <stdio.h>
#include "dynamicArray.h"
#include <string.h>

#define BUFFER_SIZE 20
#define DEFAULT_NUM 3

typedef struct stuInfo
{
    int age;
    char sex;
} stuInfo; 

int main()
{
    dynamicArray array;
    /* 初始化 */
    dynamicArrayInit(&array, BUFFER_SIZE);
#if 0
    /* 模块化 */
    {
        /* 插入数据 */
        // dynamicArrayInsertData(&array, 3);
        for (int idx = 1; idx <= DEFAULT_NUM; idx++)
        {
            dynamicArrayInsertData(&array, idx);
        }
    }

    /* 模块化 */
    {
        /* 获取动态数组的大小 */
        int size = 0;
        dynamicArrayGetSize(&array, &size);
        printf("size:%d\n", size);
    }

    {
        /* 获取动态数组的大小 */
        int size = 0;
        dynamicArrayGetSize(&array, &size);
        int val = 0;
        for (int idx = 0; idx < size; idx++)
        {
            dynamicArrayGetAppointPosVal(&array, idx, &val);
            printf("val:%d\t", val);
        }    
        printf("\n");
    }

    {
        int size = 0;
        /* 删除最后位置的元素 */
        dynamicArrayDeleteData(&array);

        /* 获取动态数组的大小 */
        dynamicArrayGetSize(&array, &size);
        printf("size:%d\n", size);

        int val = 0;
        for (int idx = 0; idx < size; idx++)
        {
            dynamicArrayGetAppointPosVal(&array, idx, &val);
            printf("val:%d\t", val);
        }    
        printf("\n");
    }

    {
        int size = 0;
        /* 删除指定位置的元素 */
        int pos = 1;
        dynamicArrayDeleteAppointPosData(&array, pos);

        /* 获取动态数组的大小 */
        dynamicArrayGetSize(&array, &size);
        printf("size:%d\n", size);

        int val = 0;
        for (int idx = 0; idx < size; idx++)
        {
            dynamicArrayGetAppointPosVal(&array, idx, &val);
            printf("val:%d\t", val);
        }    
        printf("\n");
    }
#elif 0
    int buffer[DEFAULT_NUM] = {1, 2, 3};
    for (int idx = 0; idx < DEFAULT_NUM; idx++)
    {
        dynamicArrayInsertData(&array, (void *)&buffer[idx]);
    }
    
    int size = 0;
    dynamicArrayGetSize(&array, &size);
    printf("size:%d\n", size);

    int *val = NULL;
    for (int idx = 0; idx < DEFAULT_NUM; idx++)
    {
        dynamicArrayGetAppointPosVal(&array, idx, (void *)&val);
        printf("val:%d\n", *val);
    }
#elif 1
    int idx = 0;
    for (idx; idx < DEFAULT_NUM; idx++)
    {
        dynamicArrayInsertData(&array, (void *)&idx);
    }
    
    int size = 0;
    dynamicArrayGetSize(&array, &size);
    printf("size:%d\n", size);

    int *val = NULL;
    for (int idx = 0; idx < DEFAULT_NUM; idx++)
    {
        dynamicArrayGetAppointPosVal(&array, idx, (void *)&val);
        printf("val:%d\n", *val);
    }
#else
    stuInfo stu1, stu2, stu3;
    memset(&stu1, 0, sizeof(stu1));
    memset(&stu2, 0, sizeof(stu2));
    memset(&stu3, 0, sizeof(stu3));

    stu1.age = 10;
    stu1.sex = 'm';

    stu2.age = 20;
    stu2.sex = 'f';

    stu3.age = 30;
    stu3.sex = 'm';

    stuInfo buffer[DEFAULT_NUM] = {stu1, stu2, stu3};
    for (int idx = 0; idx < DEFAULT_NUM; idx++)
    {
        dynamicArrayInsertData(&array, (void *)&buffer[idx]);
    }

    int size = 0;
    dynamicArrayGetSize(&array, &size);
    printf("size:%d\n", size);

    stuInfo *info = NULL;
    for (int idx = 0; idx < DEFAULT_NUM; idx++)
    {
        dynamicArrayGetAppointPosVal(&array, idx, (void *)&info);
        printf("info.age:%d\tinfo.sex:%c\n", info->age, info->sex);
    }

#endif

    return 0;
}