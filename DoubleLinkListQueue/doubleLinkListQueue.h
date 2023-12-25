#ifndef __DoubleLinkList_QUEUE_H_
#define __DoubleLinkList_QUEUE_H_


/* 队列初始化 */
int doubleLinkListQueueInit();

/* 队列入队 */
int doubleLinkListQueuePush();

/* 队头元素 */
int doubleLinkListQueueTop();

/* 队尾元素 */
int doubleLinkListQueueRear();

/* 队列出队 */
int doubleLinkListQueuePop();

/* 队列大小 */
int doubleLinkListQueueGetSize();

/* 队列是否为空 */
int doubleLinkListQueueIsEmpty();

/* 队列销毁*/
int doubleLinkListQueueDestroy();

#endif // __DoubleLinkList_QUEUE_H_