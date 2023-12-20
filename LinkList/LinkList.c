#include "LinkList.h"
#include <stdlib.h>
#include <string.h>

/* 状态码 */
enum STATUS_CODE
{
    ON_SUCCESS,
    NULL_PTR,
    MALLOC_ERROR,
    INVALID_ACCESS,
};

/* 链表初始化 */
int LinkListInit(LinkList **pList)
{
    int ret = 0;
    LinkList *list = (LinkList *)malloc(sizeof(LinkList) * 1);
    if (list == NULL)
    {
        return MALLOC_ERROR;
    }
    /* 清空脏数据 */
    memset(list, 0, sizeof(LinkList) * 1);

    list->head = (LinkNode *)malloc(sizeof(LinkNode) * 1);
    if (list->head == NULL)
    {
        return MALLOC_ERROR;
    }
    /* 清空脏数据 */
    memset(list->head, 0, sizeof(LinkNode) * 1);
    list->head->data = 0;
    list->head->next = NULL;

    /* 链表的长度为0 */
    list->len = 0;

    /* 二级指针 */
    *pList = list;
    return ret;
}

/* 链表头插 */
int LinkListHeadInsert(LinkList * pList, ELEMENTTYPE val)
{
    return LinkListAppointPosInsert(pList, 0, val);
}

/* 链表尾插 */
int LinkListTailInsert(LinkList * pList, ELEMENTTYPE val)
{
    /* todo... */
    return LinkListAppointPosInsert(pList, pList->len, val);
}

/* 链表指定位置插入 */
int LinkListAppointPosInsert(LinkList * pList, int pos, ELEMENTTYPE val)
{
    int ret = 0;
    if (pList == NULL)
    {
        return NULL_PTR;
    }
    
    if (pos < 0 || pos > pList->len)
    {
        return INVALID_ACCESS;
    }

    /* 封装结点 */
    LinkNode * newNode = (LinkNode *)malloc(sizeof(LinkNode) * 1);
    if (newNode == NULL)
    {
        return MALLOC_ERROR;
    }
    /* 清除脏数据 */
    memset(newNode, 0, sizeof(LinkNode) * 1);
#if 1
    newNode->data = 0;
    newNode->next = NULL;
#endif
    /* 赋值 */
    newNode->data = val;

#if 1
    /* 从虚拟头结点开始遍历 */
    LinkNode * travelNode = pList->head;
#else
    LinkNode * travelNode = pList->head->next;
#endif
    while (pos)
    {
        travelNode = travelNode->next;
        pos--;
    }
    /* 修改结点指向 */
    newNode->next = travelNode->next;
    travelNode->next = newNode;

    /* 更新链表的长度 */
    (pList->len)++;
    return ret;
}

/* 链表头删 */
int LinkListHeadDel(LinkList * pList)
{
    
}

/* 链表尾删 */
int LinkListTailDel(LinkList * pList)
{
    
}

/* 链表指定位置删 */
int LinkListDelAppointPos(LinkList * pList, int pos)
{
    
}

/* 链表删除指定的数据 */
int LinkListDelAppointData(LinkList * pList, ELEMENTTYPE val)
{
    
}

/* 获取链表的长度 */
int LinkListGetLength(LinkList * pList, int *pSize)
{
    int ret = 0;
    if (pList == NULL)
    {
        return NULL_PTR;
    }

    if (pSize)
    {
        *pSize = pList->len;
    }
    return ret;
}

/* 链表的销毁 */
int LinkListDestroy(LinkList * pList)
{
    
}

/* 链表遍历接口 */
int LinkListForeach(LinkList * pList)
{
    
}