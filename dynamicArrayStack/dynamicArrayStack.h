#ifndef __DYNAMIC_ARRAY_STACK_H_
#define __DYNAMIC_ARRAY_STACK_H_

/* 栈的初始化 */
int dynamicArrayStackInit();

/* 压栈 */
int dynamicArrayStackPush();

/* 查看栈顶元素 */
int dynamicArrayStackTop();

/* 出栈 */
int dynamicArrayStackPop();

/* 栈是否为空 */
int dynamicArrayStackIsEmpty();

/* 获取栈的大小 */
int dynamicArrayStackSize();

/* 栈的销毁 */
int dynamicArrayStackDestroy();

#endif