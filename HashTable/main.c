#include "hashtable.h"
#include <stdio.h>
#include <stdlib.h>


int main()
{
    HashTable *hash = NULL;

    /* 哈希表的初始化 */
    hashTableInit(&hash);


    /* 哈希表 插入<key, value> */
    hashTableInsert(hash, 11, 666);
    hashTableInsert(hash, 81, 777);
    hashTableInsert(hash, 101, 999);

    int value = 0;
    hashTableGetAppointKeyValue(hash, 11, &value);
    printf("value:%d\n", value);

    hashTableGetAppointKeyValue(hash, 81, &value);
    printf("value:%d\n", value);

    hashTableGetAppointKeyValue(hash, 101, &value);
    printf("value:%d\n", value);
}