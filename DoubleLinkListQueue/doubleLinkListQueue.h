#ifndef __DoubleLinkList_QUEUE_H_
#define __DoubleLinkList_QUEUE_H_

#include "common.h"
typedef DoubleLinkList DoubleLinkListQueue;

/* 队列初始化 */
int doubleLinkListQueueInit(DoubleLinkListQueue **pQueue);

/* 队列入队 */
int doubleLinkListQueuePush(DoubleLinkListQueue *pQueue, ELEMENTTYPE val);

/* 队头元素 */
int doubleLinkListQueueTop(DoubleLinkListQueue *pQueue, ELEMENTTYPE *pVal);

/* 队尾元素 */
int doubleLinkListQueueRear(DoubleLinkListQueue *pQueue, ELEMENTTYPE *pVal);

/* 队列出队 */
int doubleLinkListQueuePop(DoubleLinkListQueue *pQueue);

/* 队列大小 */
int doubleLinkListQueueGetSize(DoubleLinkListQueue *pQueue, int *pSize);

/* 队列是否为空 */
int doubleLinkListQueueIsEmpty(DoubleLinkListQueue *pQueue);

/* 队列销毁*/
int doubleLinkListQueueDestroy(DoubleLinkListQueue *pQueue);

#endif // __DoubleLinkList_QUEUE_H_