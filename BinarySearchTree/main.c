#include <stdio.h>
#include "binarySearchTree.h"


#define BUFFER_SIZE 10

/* 测试二叉搜索树 */
int compareBasicDataFunc(void * arg1, void *arg2)
{
    int val1 = *(int *)arg1;
    int val2 = *(int *)arg2;

    return val1 - val2;
}

/* 打印基础数据 */
int printBasicData(void *arg)
{
    int ret = 0;
    int val = *(int *)arg;
    printf("val:%d\t", val);

    return ret;
}

int main()
{
    BinarySearchTree * BST;
    binarySearchTreeInit(&BST, compareBasicDataFunc, printBasicData);

    int buffer[BUFFER_SIZE] = {56, 28, 75, 73, 77, 13, 7, 26, 100, 12};

    for (int idx = 0; idx < BUFFER_SIZE; idx++)
    {   
        binarySearchTreeInsert(BST, (void *)&buffer[idx]);
    }
    /* 获取二叉搜索树的结点个数 */
    int size = 0;
    binarySearchTreeGetNodeSize(BST, &size);
    printf("size:%d\n", size);

    /* 获取二叉搜索树的高度 */
    int height = 0;
    binarySearchTreeGetHeight(BST, &height);
    printf("height:%d\n", height);


    /* 中序遍历 */
    binarySearchTreeInOrderTravel(BST);
    printf("\n");


    /* 层序遍历 */
    binarySearchTreeLevelOrderTravel(BST);
    printf("\n");


    /* 删除 度为2. 值为56 */
    int delVal = 56;
    binarySearchTreeDelete(BST, &delVal);

    /* 获取二叉搜索树的结点个数 */
    size = 0;
    binarySearchTreeGetNodeSize(BST, &size);
    printf("size:%d\n", size);

    /* 获取二叉搜索树的高度 */
    height = 0;
    binarySearchTreeGetHeight(BST, &height);
    printf("height:%d\n", height);

    /* 层序遍历 */
    binarySearchTreeLevelOrderTravel(BST);
    printf("\n");




    /* 删除 度为1. 值为56 */
    delVal = 7;
    binarySearchTreeDelete(BST, &delVal);

    /* 获取二叉搜索树的结点个数 */
    size = 0;
    binarySearchTreeGetNodeSize(BST, &size);
    printf("size:%d\n", size);

    /* 获取二叉搜索树的高度 */
    height = 0;
    binarySearchTreeGetHeight(BST, &height);
    printf("height:%d\n", height);

    /* 层序遍历 */
    binarySearchTreeLevelOrderTravel(BST);
    printf("\n");


    /* 删除 度为0. 值为12 */
    delVal = 12;
    binarySearchTreeDelete(BST, &delVal);

    /* 获取二叉搜索树的结点个数 */
    size = 0;
    binarySearchTreeGetNodeSize(BST, &size);
    printf("size:%d\n", size);

    /* 获取二叉搜索树的高度 */
    height = 0;
    binarySearchTreeGetHeight(BST, &height);
    printf("height:%d\n", height);

    /* 层序遍历 */
    binarySearchTreeLevelOrderTravel(BST);
    printf("\n");



    return 0;
}