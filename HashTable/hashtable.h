#ifndef __HASH_TABLE_H_
#define __HASH_TABLE_H_

#include "common.h"

#define SLOT_CAPACITY   10

/* 双向链表 */
typedef DoubleLinkNode hashNode;

typedef struct hashTable
{
    int slotNums;
    hashNode *slotKeyId;
    DoubleLinkList *slotValueList;
} HashTable;

/* 哈希表的初始化 */
int hashTableInit(HashTable** pHashtable);

/* 哈希表 插入<key, value> */
int hashTableInsert(HashTable *pHashtable, int key, int value);

/* 哈希表 删除指定key. */
int hashTableDelAppointKey(HashTable *pHashtable, int key);

/* 哈希表 根据key获取value. */
int hashTableGetAppointKeyValue(HashTable *pHashtable, int key);

#endif //__HASH_TABLE_H_