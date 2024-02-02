#ifndef __DoubleLinkList_H_
#define __DoubleLinkList_H_
#include "common.h"

/* 链表初始化 */
int DoubleLinkListInit(DoubleLinkList **pList);

/* 链表头插 */
int DoubleLinkListHeadInsert(DoubleLinkList * pList, ELEMENTTYPE val);

/* 链表尾插 */
int DoubleLinkListTailInsert(DoubleLinkList * pList, ELEMENTTYPE val);

/* 链表指定位置插入 */
int DoubleLinkListAppointPosInsert(DoubleLinkList * pList, int pos, ELEMENTTYPE val);

/* 链表头删 */
int DoubleLinkListHeadDel(DoubleLinkList * pList);

/* 链表尾删 */
int DoubleLinkListTailDel(DoubleLinkList * pList);

/* 链表指定位置删 */
int DoubleLinkListDelAppointPos(DoubleLinkList * pList, int pos);

/* 链表删除指定的数据 */
int DoubleLinkListDelAppointData(DoubleLinkList * pList, ELEMENTTYPE val, int (*compareFunc)(ELEMENTTYPE, ELEMENTTYPE));

/* 获取链表的长度 */
int DoubleLinkListGetLength(DoubleLinkList * pList, int *pSize);

/* 链表的销毁 */
int DoubleLinkListDestroy(DoubleLinkList * pList);

/* 链表遍历接口 */
int DoubleLinkListForeach(DoubleLinkList * pList, int (*printFunc)(ELEMENTTYPE));

/* 双向链表逆序打印 */
int DoubleLinkListReverseForeach(DoubleLinkList * pList, int (*printFunc)(ELEMENTTYPE));

/* 获取链表 头位置值 */
int DoubleLinkListGetHeadVal(DoubleLinkList * pList, ELEMENTTYPE *pVal);

/* 获取链表 尾位置值 */
int DoubleLinkListGetTailVal(DoubleLinkList * pList, ELEMENTTYPE *pVal);

/* 获取链表 指定位置的值 */
int DoubleLinkListGetAppointPosVal(DoubleLinkList * pList, int pos, ELEMENTTYPE *pVal);

/* 根据结点找到对应的值 */
DoubleLinkNode * DoubleLinkListAppointKeyValGetNode(DoubleLinkList * pList, ELEMENTTYPE val, int (*compareFunc)(ELEMENTTYPE, ELEMENTTYPE));
#endif