#include <stdio.h>
#include "doubleLinkList.h"
#include <string.h>

#define BUFFER_SIZE    3


typedef struct stuInfo
{
    int age;
    char sex;
} stuInfo; 


/* 自定义打印 */
int printStruct(void *arg)
{
    stuInfo *info = (stuInfo*)arg;
    printf("age:%d\t, sex:%c\n", info->age, info->sex);
}

int printBasicData(void *arg)
{
    int data = *(int *)arg;
    printf("data:%d\n", data);
}
int main()
{
#if 0
    /* strcpy第一个参数是传出参数 并返回值也是直线dst的地址的. */
    char buffer[BUFFER_SIZE] = {0};
    char *ptr = strcpy(buffer, "zhangsan");
    printf("buffer:%s\n", buffer);
    printf("ptr:%s\n", ptr);
#endif

#if 0
    /* snmp */
    /* 华润电力 */
#endif

    LinkList *list = NULL;
    /* 初始化链表 */
    LinkListInit(&list);

#if 1
    int buffer[BUFFER_SIZE] = {1, 2, 3};
    /* 插入数据 */
    for (int idx = 0; idx < BUFFER_SIZE; idx++)
    {
        LinkListHeadInsert(list, (void *)&buffer[idx]);
    }
    
    /* 获取链表的长度 */
    int size = 0;
    LinkListGetLength(list, &size);
    printf("size:%d\n", size);

    LinkListForeach(list, printBasicData);
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

    stuInfo buffer[BUFFER_SIZE] = {stu1, stu2, stu3};

    for (int idx = 0; idx < BUFFER_SIZE; idx++)
    {
        LinkListHeadInsert(list, (void *)&buffer[idx]);
    }
    
    /* 获取链表的长度 */
    int size = 0;
    LinkListGetLength(list, &size);
    printf("size:%d\n", size);

    /* 遍历 */
    LinkListForeach(list, printStruct);
#endif
    return 0;
}