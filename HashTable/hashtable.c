#include <stdio.h>
#include "hashtable.h"
#include <stdlib.h>
#include "doubleLinkList.h"
#include <error.h>

#define DEFAULT_SLOT_NUMS   10

/* 哈希表的初始化 */
int hashTableInit(HashTable** pHashtable)
{
    int ret = 0;

    HashTable * hash = (HashTable *)malloc(sizeof(HashTable) * 1);
    if (hash == NULL)
    {
        perror("malloc error");
        return MALLOC_ERROR;
    }
    memset(hash, 0, sizeof(HashTable) * 1);
    hash->slotNums = DEFAULT_SLOT_NUMS;


    hash->slotKeyId = (hashNode *)malloc(sizeof(hashNode) * (hash->slotNums));
    if (hash->slotKeyId == NULL)
    {
        perror("malloc error");
        return MALLOC_ERROR;
    }
    memset(hash->slotKeyId, 0, sizeof(hashNode) * (hash->slotNums));

    /* 为哈希表的value初始化。哈希表的value是链表的虚拟头结点 */
    DoubleLinkListInit(&hash->slotValueList);

    
    /* 指针解引用 */
    *pHashtable = hash;
    return ret;
}


/* 计算外部传过来的key 转化为哈希表内部维护的slotKeyId. */
static int calHashValue(HashTable *pHashtable, int key, int *slotKeyId)
{
    int ret = 0;
    if (slotKeyId)
    {
        *slotKeyId = key % (pHashtable->slotNums);
    }
    return ret;
}

/* 哈希表 插入<key, value> */
int hashTableInsert(HashTable *pHashtable, int key, int value)
{
    int ret = 0;

    /* 将外部传过来的key 转化为我哈希表对应的slotId */

    return ret;
}

/* 哈希表 删除指定key. */
int hashTableDelAppointKey(HashTable *pHashtable, int key)
{
    int ret = 0;

    return ret;
}

/* 哈希表 根据key获取value. */
int hashTableGetAppointKeyValue(HashTable *pHashtable, int key)
{
    int ret = 0;

    return ret;
}