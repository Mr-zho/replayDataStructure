#include "hashtable.h"
#include <stdio.h>
#include <stdlib.h>


/* 自定义比较器 */
int compareFunc(void *val1, void *val2)
{
    hashNode *key1 = (hashNode *)val1;
    hashNode *key2 = (hashNode *)val2;

    return key1->real_key - key2->real_key;
}


int main()
{
    HashTable *hash = NULL;

    int slotNums = 10;
    /* 哈希表的初始化 */
    hashTableInit(&hash, slotNums, compareFunc);

    /* 哈希表 插入<key, value> */
    hashTableInsert(hash, 11, 666);
    hashTableInsert(hash, 81, 777);
    hashTableInsert(hash, 101, 999);

    

    int value = 0;
    int ret = hashTableGetAppointKeyValue(hash, 11, &value);
    if (ret == -1)
    {
        printf("not fount...\n");
    }
    else
    {
        printf("value:%d\n", value);
    }

    ret = hashTableGetAppointKeyValue(hash, 81, &value);
    if (ret == -1)
    {
        printf("not fount...\n");
    }
    else
    {
        printf("value:%d\n", value);
    }

    ret = hashTableGetAppointKeyValue(hash, 101, &value);
    if (ret == -1)
    {
        printf("not fount...\n");
    }
    else
    {
        printf("value:%d\n", value);
    }


    hashTableDelAppointKey(hash, 101);

    ret = hashTableGetAppointKeyValue(hash, 101, &value);
    if (ret == -1)
    {
        printf("not fount...\n");
    }
    else
    {
        printf("value:%d\n", value);
    }
}