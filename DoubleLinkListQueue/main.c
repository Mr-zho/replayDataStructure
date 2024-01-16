#include "doubleLinkListQueue.h"
#include <stdio.h>

#define BUFFER_SIZE 5

int main()
{
    DoubleLinkListQueue *queue = NULL;
    doubleLinkListQueueInit(&queue);

    int buffer[BUFFER_SIZE] = {111, 222, 333, 444, 555};

    for (int idx = 0; idx < 1; idx++)
    {
        doubleLinkListQueuePush(queue, (void *)&buffer[idx]);
    }

    int size = 0;
    doubleLinkListQueueGetSize(queue, &size);
    printf("size:%d\n", size);

    int *topVal = NULL;
    doubleLinkListQueueTop(queue, (void **)&topVal);
    printf("topVal:%d\n", *topVal);

#if 0
    int buffer[BUFFER_SIZE] = {111, 222, 333, 444, 555};

    for (int idx = 0; idx < BUFFER_SIZE; idx++)
    {
        doubleLinkListQueuePush(queue, (void *)&buffer[idx]);
    }

    int size = 0;
    doubleLinkListQueueGetSize(queue, &size);
    printf("size:%d\n", size);

    int * val = NULL;
    while (!doubleLinkListQueueIsEmpty(queue))
    {
        doubleLinkListQueueTop(queue, (void **)&val);
        printf("val:%d\n", *val);
        doubleLinkListQueuePop(queue);
    }

    /* 销毁队列 */
    doubleLinkListQueueDestroy(queue);
#endif
    return 0;
}