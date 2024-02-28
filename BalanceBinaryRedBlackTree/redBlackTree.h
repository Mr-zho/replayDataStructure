#ifndef __BINARY_SEARCH_TREE_H_
#define __BINARY_SEARCH_TREE_H_

#include "common.h"
// #define ELEMENTTYPE int

typedef struct RedBlackTreeNode
{
    ELEMENTTYPE data;
    struct RedBlackTreeNode *left;        /* 左子树 */
    struct RedBlackTreeNode *right;       /* 右子树 */
    #if 1
    struct RedBlackTreeNode *parent;      /* 父结点 */
    #endif
} RedBlackTreeNode;

typedef struct RedBlackTree
{   
    /* 根结点 */
    RedBlackTreeNode * root;
    /* 树的结点个数 */
    int size;

    /* 钩子🪝函数比较器 放到结构体内部. */
    int (*compareFunc)(ELEMENTTYPE val1, ELEMENTTYPE val2);

    /* 钩子🪝函数 包装器实现自定义打印函数接口. */
    int (*printFunc)(ELEMENTTYPE val);

#if 0
    /* 把队列的属性 放到树里面 */
    DoubleLinkListQueue *pQueue;
#endif

} RedBlackTree;

/* 二叉搜索树的初始化 */
int RedBlackTreeInit(RedBlackTree **pBstree, int (*compareFunc)(ELEMENTTYPE val1, ELEMENTTYPE val2), int (*printFunc)(ELEMENTTYPE val));

/* 二叉搜索树的插入 */
int RedBlackTreeInsert(RedBlackTree *pBstree, ELEMENTTYPE val);

/* 二叉搜索树是否包含指定的元素 */
int RedBlackTreeIsContainAppointVal(RedBlackTree *pBstree, ELEMENTTYPE val);

/* 二叉搜索树的前序遍历 */
int RedBlackTreePreOrderTravel(RedBlackTree *pBstree);

/* 二叉搜索树的中序遍历 */
int RedBlackTreeInOrderTravel(RedBlackTree *pBstree);

/* 二叉搜索树的后序遍历 */
int RedBlackTreePostOrderTravel(RedBlackTree *pBstree);

/* 二叉搜索树的层序遍历 */
int RedBlackTreeLevelOrderTravel(RedBlackTree *pBstree);

/* 获取二叉搜索树的结点个数 */
int RedBlackTreeGetNodeSize(RedBlackTree *pBstree, int *pSize);

/* 获取二叉搜索树的高度 */
int RedBlackTreeGetHeight(RedBlackTree *pBstree, int *pHeight);

/* 二叉搜索树的删除 */
int RedBlackTreeDelete(RedBlackTree *pBstree, ELEMENTTYPE val);

/* 二叉搜索树的销毁 */
int RedBlackTreeDestroy(RedBlackTree *pBstree);

/* 判断二叉搜索树是否是完全二叉树 */
int RedBlackTreeIsComplete(RedBlackTree *pBSTree);

#endif  //__BINARY_SEARCH_TREE_H_