#include <stdio.h>
#include "hashtable.h"
#include <stdlib.h>
#include "doubleLinkList.h"
#include <error.h>
#include <string.h>

#define DEFAULT_SLOT_NUMS   10

/* 函数前置声明 */
/* 比较器 */
static int compareFunc(void *val1, void *val2);

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
    /* 清除脏数据 */
    memset(hash, 0, sizeof(HashTable) * 1);
    hash->slotNums = DEFAULT_SLOT_NUMS;

#if 1
    hash->slotKeyId = (DoubleLinkList *)malloc(sizeof(DoubleLinkList) * (hash->slotNums));
    if (hash->slotKeyId == NULL)
    {
        perror("malloc error");
        return MALLOC_ERROR;
    }
    /* 清除脏数据 */
    memset(hash->slotKeyId, 0, sizeof(DoubleLinkList) * (hash->slotNums));
#endif

    DoubleLinkListInit(&(hash->slotKeyId[0]));

    /* 初始化 */
    for (int idx = 0; idx < hash->slotNums; idx++)
    {
        /* 为哈希表的value初始化。哈希表的value是链表的虚拟头结点 */
        DoubleLinkListInit(&(hash->slotKeyId[idx]));
    }

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
 
/* 新建结点 */
static hashNode * createHashNode(int key, int value)
{
    /* 封装结点 */
    hashNode * newNode = (hashNode *)malloc(sizeof(hashNode) * 1);
    if (newNode == NULL)
    {
        return NULL;
    }
    /* 清除脏数据 */
    memset(newNode, 0, sizeof(hashNode) * 1);

    newNode->real_key = key;
    newNode->value = value;

    /* 返回新结点 */
    return newNode;
}


/* 哈希表 插入<key, value> */
int hashTableInsert(HashTable *pHashtable, int key, int value)
{
    int ret = 0;

    /* 将外部传过来的key 转化为我哈希表对应的slotId */
    int KeyId = 0;
    calHashValue(pHashtable, key, &KeyId);

    /* 创建哈希node */
    hashNode * newNode = createHashNode(key, value);
    if (newNode == NULL)
    {
        perror("create hash node error");
        return MALLOC_ERROR;
    }
    
    /* 将哈希结点插入到链表中. */
    DoubleLinkListTailInsert(&(pHashtable->slotKeyId[KeyId]), newNode);

    return ret;
}

/* 哈希表 删除指定key. */
int hashTableDelAppointKey(HashTable *pHashtable, int key)
{
    int ret = 0;
    /* 将外部传过来的key 转化为我哈希表对应的slotId */
    int KeyId = 0;
    calHashValue(pHashtable, key, &KeyId);



int DoubleLinkListDelAppointData(DoubleLinkList * pList, ELEMENTTYPE val, int (*compareFunc)(ELEMENTTYPE, ELEMENTTYPE));

    return ret;
}


/* 自定义比较器 */
int compareFunc(void *val1, void *val2)
{
    hashNode *key1 = (hashNode *)val1;
    hashNode *key2 = (hashNode *)val2;

    return key1->real_key - key2->real_key;
}

/* 哈希表 根据key获取value. */
int hashTableGetAppointKeyValue(HashTable *pHashtable, int key, int *mapValue)
{
    int ret = 0;

    /* 将外部传过来的key 转化为我哈希表对应的slotId */
    int KeyId = 0;
    calHashValue(pHashtable, key, &KeyId);

    hashNode tmpNode;
    tmpNode.real_key = key;
    DoubleLinkNode * resNode = DoubleLinkListAppointKeyValGetNode(&(pHashtable->slotKeyId[KeyId]), &tmpNode,  compareFunc);
    if (resNode == NULL)
    {
        return -1;
    }

    hashNode * mapNode = (hashNode*)resNode->data;
    if (mapValue)
    {
        *mapValue = mapNode->value;
    }

    return ret;
}