#include "redBlackTree.h"
#include <stdlib.h>
#include <string.h>
#include "doubleLinkListQueue.h"

/* 状态码 */
enum STATUS_CODE
{
    ON_SUCCESS,
    NULL_PTR,
    MALLOC_ERROR,
    INVALID_ACCESS,
};

/* 静态函数前置声明 */

/* 两个值比较大小 */
static int compareFunc(ELEMENTTYPE val1, ELEMENTTYPE val2);
/* 创建结点 */
static RedBlackTreeNode *createBSTreeNewNode(ELEMENTTYPE val, RedBlackTreeNode *parent);
/* 根据指定的值获取二叉搜索树的结点 */
static RedBlackTreeNode * baseAppointValGetRedBlackTreeNode(RedBlackTree *pBstree, ELEMENTTYPE val);
/* 判断二叉搜索树度为2 */
static int RedBlackTreeNodeHasTwochildrens(RedBlackTreeNode *node);
/* 判断二叉搜索树度为1 */
static int RedBlackTreeNodeHasOnechildren(RedBlackTreeNode *node);
/* 判断二叉搜索树度为0 */
static int RedBlackTreeNodeIsLeaf(RedBlackTreeNode *node);
/* 前序遍历 */
static int preOrderTravel(RedBlackTree *pBstree, RedBlackTreeNode *node);
/* 中序遍历 */
static int inOrderTravel(RedBlackTree *pBstree, RedBlackTreeNode *node);
/* 添加结点之后要做的事情 */
static int insertNodeAfter(RedBlackTree *pBstree, RedBlackTreeNode *node);
/* 后序遍历 */
static int postOrderTravel(RedBlackTree *pBstree, RedBlackTreeNode *node);
/* 获取当前结点的前驱结点 */
static RedBlackTreeNode * RedBlackTreeNodePreDecessor(RedBlackTreeNode *node);
/* 获取当前结点的后继结点 */
static RedBlackTreeNode * RedBlackTreeNodeSuccessor(RedBlackTreeNode *node);
/* 二叉搜索树删除指定的结点 */
static int RedBlackTreeDeleteNode(RedBlackTree *pBstree, RedBlackTreeNode *node);
/* 当前结点是父结点的左子树 */
static int RedBlackTreeNodeIsLeft(RedBlackTreeNode *node);
/* 当前结点是父结点的右子树 */
static int RedBlackTreeNodeIsRight(RedBlackTreeNode *node);
/* 左旋 */
static int RedBlackTreeNodeRotateLeft(RedBlackTree *pBstree, RedBlackTreeNode *grand);
/* 右旋 */
static int RedBlackTreeNodeRotateRight(RedBlackTree *pBstree, RedBlackTreeNode *grand);
/* 染色 */
static RedBlackTreeNode * stainColor(RedBlackTreeNode *node, bool color);
/* 当前结点染成红色 */
static RedBlackTreeNode * stainRedColor(RedBlackTreeNode *node);
/* 查看当前结点的颜色 */
static bool RedBlackTreeNodeColorOf(RedBlackTreeNode *node);
/* 当前结点染成黑色 */
static RedBlackTreeNode * stainBlackColor(RedBlackTreeNode *node);
/* 当前结点是红色结点 */
static bool RedBlackTreeNodeIsRedColor(RedBlackTreeNode *node);
/* 当前结点是黑色结点 */
static bool RedBlackTreeNodeIsBlackColor(RedBlackTreeNode *node);
/* 返回兄弟结点 */
static RedBlackTreeNode * RedBlackTreeNodeGetSiblingNode(RedBlackTreeNode *node);

/* 二叉搜索树的初始化 */
int RedBlackTreeInit(RedBlackTree **pBstree, int (*compareFunc)(ELEMENTTYPE val1, ELEMENTTYPE val2), int (*printFunc)(ELEMENTTYPE val))
{
    int ret = 0;
    RedBlackTree * bstree = (RedBlackTree *)malloc(sizeof(RedBlackTree) * 1);
    if (bstree == NULL)
    {
        return MALLOC_ERROR;
    }
    /* 清除脏数据 */
    memset(bstree, 0, sizeof(RedBlackTree) * 1);
    /* 初始化树 */
    {
        bstree->root = NULL;
        bstree->size = 0;

        /* 钩子函数在这边赋值. */
        bstree->compareFunc = compareFunc;
        /* 钩子函数包装器 自定义打印. */
        bstree->printFunc = printFunc;
    }
    
    *pBstree = bstree;
    return ret;
}

/* 添加结点之后要做的事情 */
static int insertNodeAfter(RedBlackTree *pBstree, RedBlackTreeNode *node)
{
    RedBlackTreeNode * parent = node->parent;

    /* 根结点的的父结点为NULL. */
    if (parent == NULL)
    {
        stainBlackColor(node);
        return ON_SUCCESS;
    }

    // 如果父结点是黑色, 直接返回
    if (RedBlackTreeNodeIsBlackColor(parent))
    {
        return ON_SUCCESS;
    }
    else
    {
        /* 程序执行到这里, 父结点一定是红色 */

        /* 叔父结点 */
        RedBlackTreeNode * uncleNode = RedBlackTreeNodeGetSiblingNode(parent);
        /* 祖父结点 */
        RedBlackTreeNode *grandNode = parent->parent;

        if (RedBlackTreeNodeIsRedColor(uncleNode))
        {
            /* 叔父结点是红色, 就要进行上溢 */
            stainBlackColor(parent);
            stainBlackColor(uncleNode);

            /* 把祖父结点当作是新添加的结点 */
            insertNodeAfter(pBstree, grandNode);

            return ON_SUCCESS;
        }

        /* 程序执行到这里: 叔父结点一定不是红色 todo... */
        /* 需要判断是LL, RR, LR, RL四种情况 */
        if (RedBlackTreeNodeIsLeft(parent))     /* L? */
        {
            
            if (RedBlackTreeNodeIsLeft(node))
            {
                /* LL */
                stainBlackColor(parent);
                stainRedColor(grandNode);

                /* 右旋转 */
                RedBlackTreeNodeRotateRight(pBstree, grandNode);
            }
            else if (RedBlackTreeNodeIsRight(node))
            {
                /* LR */
                stainBlackColor(node);
                stainRedColor(grandNode);

                /* parent左旋转 */
                RedBlackTreeNodeRotateLeft(pBstree, parent);
                /* grand右旋转 */
                RedBlackTreeNodeRotateRight(pBstree, grandNode);
            }
        }
        else if (RedBlackTreeNodeIsRight(parent))   /* R? */
        {
            if (RedBlackTreeNodeIsLeft(node))
            {
                /* RL */
                stainBlackColor(node);
                stainRedColor(grandNode);

                /* parent右旋转 */
                RedBlackTreeNodeRotateRight(pBstree, parent);
                /* grand左旋转 */
                RedBlackTreeNodeRotateLeft(pBstree, grandNode);
            }
            else if (RedBlackTreeNodeIsRight(node))
            {
                /* RR */
                stainBlackColor(parent);
                stainRedColor(grandNode);

                /* 右旋转 */
                RedBlackTreeNodeRotateLeft(pBstree, grandNode);
            }
        }
    }

    return 0;
}

/* 判断二叉搜索树度为2 */
static int RedBlackTreeNodeHasTwochildrens(RedBlackTreeNode *node)
{
    return (node->left != NULL) && (node->right != NULL);
}

/* 判断二叉搜索树度为1 */
static int RedBlackTreeNodeHasOnechildren(RedBlackTreeNode *node)
{
    return ((node->left == NULL) && (node->right != NULL)) || ((node->left != NULL) && (node->right == NULL));
}

/* 判断二叉搜索树度为0 */
static int RedBlackTreeNodeIsLeaf(RedBlackTreeNode *node)
{
    return (node->left == NULL) && (node->right == NULL);
}

/* 当前结点是父结点的左子树 */
static int RedBlackTreeNodeIsLeft(RedBlackTreeNode *node)
{
    return (node->parent != NULL) && (node == node->parent->left);
}

/* 当前结点是父结点的右子树 */
static int RedBlackTreeNodeIsRight(RedBlackTreeNode *node)
{
    return (node->parent != NULL ) && (node == node->parent->right);
}


static int RedBlackTreeNodeRotate(RedBlackTree *pBstree, RedBlackTreeNode *grand, RedBlackTreeNode *parent, RedBlackTreeNode *child)
{
    int ret = 0;
    /* p成为新的根结点 */
    parent->parent = grand->parent;   // 3

    if(RedBlackTreeNodeIsRight(grand))
    {
        grand->parent->right = parent;      // 4
    }
    else if (RedBlackTreeNodeIsLeft(grand))
    {
        grand->parent->left = parent;        // 4
    }
    else
    {
        /* 根结点 */
        pBstree->root = parent;     // 4
    }
    grand->parent = parent;      // 5

    if(child)
    {
        child->parent = grand;   //6
    }

    /* 更新高度 */
    RedBlackTreeNodeUpdateHeight(grand);
    RedBlackTreeNodeUpdateHeight(parent);

    return ret;
}

/* 左旋 : RR */
static int RedBlackTreeNodeRotateLeft(RedBlackTree *pBstree, RedBlackTreeNode *grand)
{
    int ret = 0;

    RedBlackTreeNode * parent = grand->right;
    RedBlackTreeNode * child = parent->left;

    grand->right = child;        // 1
    parent->left = grand;        // 2

#if 0
    /* p成为新的根结点 */
    parent->parent = grand->parent;   // 3

    if(RedBlackTreeNodeIsRight(grand))
    {
        grand->parent->right = parent;      // 4
    }
    else if (RedBlackTreeNodeIsLeft(grand))
    {
        grand->parent->left = parent;        // 4
    }
    else
    {
        /* 根结点 */
        pBstree->root = parent;     // 4
    }
    grand->parent = parent;      // 5

    if(child)
    {
        child->parent = grand;   //6
    }

    /* 更新高度 */
    RedBlackTreeNodeUpdateHeight(grand);
    RedBlackTreeNodeUpdateHeight(parent);
#else
    RedBlackTreeNodeRotate(pBstree, grand, parent, child);
#endif
    return ret;
}

/* 右旋 */
static int RedBlackTreeNodeRotateRight(RedBlackTree *pBstree, RedBlackTreeNode *grand)
{
    int ret = 0;
    /* */
    RedBlackTreeNode *parent = grand->left;
    RedBlackTreeNode *child = parent->right;

    grand->left = child;                // 1
    parent->right = grand;              // 2

#if 0
    /* p成为新的根结点 */
    parent->parent = grand->parent;     // 3

    if (RedBlackTreeNodeIsLeft(grand))
    {
        grand->parent->left = parent;   // 4
    }
    else if (RedBlackTreeNodeIsRight(grand))
    {
        grand->parent->right = parent;  // 4
    }
    else
    {
        /* p 成为树的根结点 */
        pBstree->root = parent;         // 4
    }
    grand->parent = parent;             // 5

    if (child != NULL)
    {
        child->parent = grand;          // 6
    }

    /* 更新高度 */
    /* 先更新低的结点 */
    RedBlackTreeNodeUpdateHeight(grand);
    RedBlackTreeNodeUpdateHeight(parent);
#else
    RedBlackTreeNodeRotate(pBstree, grand, parent, child);
#endif
    return ret;
}


/* 获取当前结点的前驱结点 */
/* 中序遍历到结点的前一个结点 */
static RedBlackTreeNode * RedBlackTreeNodePreDecessor(RedBlackTreeNode *node)
{
    if (node->left != NULL)
    {
        /* 前驱结点是在左子树的右子树的右子树... */
        RedBlackTreeNode *travelNode = node->left;
        while (travelNode->right != NULL)
        {
            travelNode = travelNode->right;
        }
        return travelNode;
    }

    /* 程序执行到这个地方 说明一定没有左子树。 那就需要向父结点找 */
    while(node->parent != NULL && node == node->parent->left)
    {
        node = node->parent;
    }
    /* node->parent == NULL. */
    /* node == node->parent->right. */
    return node->parent;
}

/* 获取当前结点的后继结点 */
static RedBlackTreeNode * RedBlackTreeNodeSuccessor(RedBlackTreeNode *node)
{
    if (node->right != NULL)
    {
        /* 后继结点是在右子树的左子树的左子树的左子树... */
        RedBlackTreeNode *travelNode = node->right;
        while (travelNode->left!= NULL)
        {
            travelNode = travelNode->left;
        }
        return travelNode;
    }

    /* 程序执行到这个地方, 说明一定没有右子树。 那就需要向父结点找 */
    while (node->parent != NULL && node == node->parent->right)
    {
        node = node->parent;
    }
    return node->parent;
}

/* 对指定结点染色 */
static RedBlackTreeNode * stainColor(RedBlackTreeNode *node, bool color)
{
    if (node == NULL)
    {
        return NULL;
    }
    node->color = color;
    return node;
}

/* 当前结点染成红色 */
static RedBlackTreeNode * stainRedColor(RedBlackTreeNode *node)
{
    return stainColor(node, RED);
}

/* 查看当前结点的颜色 */
static bool RedBlackTreeNodeColorOf(RedBlackTreeNode *node)
{
    return (node == NULL) ? BLACK : node->color;
}

/* 当前结点染成黑色 */
static RedBlackTreeNode * stainBlackColor(RedBlackTreeNode *node)
{
    return stainColor(node, BLACK);
}

/* 当前结点是红色结点 */
static bool RedBlackTreeNodeIsRedColor(RedBlackTreeNode *node)
{
    return RedBlackTreeNodeColorOf(node) == RED;
}

/* 当前结点是黑色结点 */
static bool RedBlackTreeNodeIsBlackColor(RedBlackTreeNode *node)
{
    return RedBlackTreeNodeColorOf(node) == BLACK;
}

/* 返回兄弟结点 */
static RedBlackTreeNode * RedBlackTreeNodeGetSiblingNode(RedBlackTreeNode *node)
{
    if (RedBlackTreeNodeIsLeaf(node))
    {
        return node->parent->right;
    }
    else if (RedBlackTreeNodeIsRight(node))
    {
        return node->parent->left;
    }
    else
    {
        /* 根结点无父结点 */
        return NULL;
    }
}

static RedBlackTreeNode *createBSTreeNewNode(ELEMENTTYPE val, RedBlackTreeNode *parent)
{
    /* 分配新结点 */
    RedBlackTreeNode * newBstNode = (RedBlackTreeNode *)malloc(sizeof(RedBlackTreeNode) * 1);
    if (newBstNode == NULL)
    {
        return NULL;
    }
    /* 清除脏数据 */
    memset(newBstNode, 0, sizeof(RedBlackTreeNode) * 1);
    /* 初始化根结点 */
    {
        newBstNode->data = 0;
        /* 为了尽快满足红黑树的性质.  [同时保证从根结点到叶子结点黑色个数相等] */
        newBstNode->color = RED;
        newBstNode->left = NULL;
        newBstNode->right = NULL;
        newBstNode->parent = NULL;
    }

    /* 赋值 */
    newBstNode->data = val;
    newBstNode->parent = parent;
    return newBstNode;
}
#if 0
static int compareFunc(ELEMENTTYPE val1, ELEMENTTYPE val2)
{
    #if 0
    if (val1 < val2)
    {
        return -1;
    }
    else if (val1 > val2)
    {
        return 1;
    }
    else
    {
        return 0;
    }
    #else
    return val1 - val2;
    #endif
}
#endif

/* 二叉搜索树的插入 */
int RedBlackTreeInsert(RedBlackTree *pBstree, ELEMENTTYPE val)
{
    int ret = 0;
    
    /* 空树 */
    if (pBstree->root == NULL)
    {
        /* 更新树的结点 */
        (pBstree->size)++;
        pBstree->root = createBSTreeNewNode(val, NULL);
        /* 添加结点之后要做的事情 */
        insertNodeAfter(pBstree, pBstree->root);
        return ret;
    }

    /* travelNode 指向根结点 */
    RedBlackTreeNode * travelNode = pBstree->root;
    RedBlackTreeNode * parentNode = pBstree->root;

    /* 确定符号: 到底放在左边还是右边 */
    int cmp = 0;
    while (travelNode != NULL)
    {
        /* 标记父结点 */
        parentNode = travelNode;
        cmp = pBstree->compareFunc(val, travelNode->data);
        /* 插入元素 < 遍历到的结点 */
        if (cmp < 0)
        {
            travelNode = travelNode->left;
        }
        else if (cmp > 0)     /* 插入元素 > 遍历到的结点 */
        {
            travelNode = travelNode->right;
        }
        else
        {
            /* 插入元素 = 遍历到的结点 */
            return ret;
        }
    }
    
    
    /* 分配根结点 */
    #if 0
    RedBlackTreeNode * newBstNode = (RedBlackTreeNode *)malloc(sizeof(RedBlackTreeNode) * 1);
    if (newBstNode == NULL)
    {
        return MALLOC_ERROR;
    }
    memset(newBstNode, 0, sizeof(RedBlackTreeNode) * 1);
    {
        newBstNode->data = 0;
        newBstNode->left = NULL;
        newBstNode->right = NULL;
        newBstNode->parent = NULL;
    }
    /* 新结点赋值 */
    newBstNode->data = val;
    #else
    RedBlackTreeNode * newBstNode = createBSTreeNewNode(val, parentNode);
    #endif

    /* 挂在左子树 */
    if (cmp < 0)
    {
        parentNode->left = newBstNode;
    }
    else
    {   
        /* 挂在右子树 */
        parentNode->right = newBstNode;
    }
#if 0
    /* 新结点的parent指针赋值 */
    newBstNode->parent = parentNode;
#endif

    /* 更新树的结点 */
    (pBstree->size)++;
    /* 添加结点之后要做的事情 */
    insertNodeAfter(pBstree, newBstNode);

    return ret;
}


/* 前序遍历 */
/* 根结点 左子树 右子树 */
static int preOrderTravel(RedBlackTree *pBstree, RedBlackTreeNode *node)
{
    int ret = 0;
    if (node == NULL)
    {
        return ret;
    }
    /* 根结点 */
    pBstree->printFunc(node->data);
    /* 左子树 */
    preOrderTravel(pBstree, node->left);
    /* 右子树 */
    preOrderTravel(pBstree, node->right);
}
/* 二叉搜索树的前序遍历 */
int RedBlackTreePreOrderTravel(RedBlackTree *pBstree)
{
    int ret = 0;
    preOrderTravel(pBstree, pBstree->root);
    return ret;
}

/* 斐波那契数列 */
/* 
    # 递归
    f(1) = 1, f(2) = 1
    f(n) = f(n-1) + f(n-2) [n > 2 n是整数]
*/

/* 中序遍历 */
/* 左子树 根结点 右子树 */
static int inOrderTravel(RedBlackTree *pBstree, RedBlackTreeNode *node)
{
    int ret = 0;
    if (node == NULL)
    {
        return ret;
    }
    /* 左子树 */
    inOrderTravel(pBstree, node->left);
    /* 根结点 */
    pBstree->printFunc(node->data);
    /* 右子树 */
    inOrderTravel(pBstree, node->right);
}

/* 二叉搜索树的中序遍历 */
int RedBlackTreeInOrderTravel(RedBlackTree *pBstree)
{
    int ret = 0;
    inOrderTravel(pBstree, pBstree->root);
    return ret;
}

/* 后序遍历 */
/* 左子树 右子树 根结点 */
static int postOrderTravel(RedBlackTree *pBstree, RedBlackTreeNode *node)
{
    int ret = 0;
    if (node == NULL)
    {
        return ret;
    }
    /* 左子树 */
    postOrderTravel(pBstree, node->left);
    /* 右子树 */
    postOrderTravel(pBstree, node->right);
    /* 根结点 */
    pBstree->printFunc(node->data);
}

/* 二叉搜索树的后序遍历 */
int RedBlackTreePostOrderTravel(RedBlackTree *pBstree)
{
    int ret = 0;
    postOrderTravel(pBstree, pBstree->root); 
    return ret;
}

/* 二叉搜索树的层序遍历 */
int RedBlackTreeLevelOrderTravel(RedBlackTree *pBstree)
{
    int ret = 0;
    DoubleLinkListQueue * pQueue = NULL;
    doubleLinkListQueueInit(&pQueue);

    /* 1. 根结点入队 */
    doubleLinkListQueuePush(pQueue, pBstree->root);

    /* 2. 判断队列是否为空 */
    RedBlackTreeNode *nodeVal = NULL;
    while (!doubleLinkListQueueIsEmpty(pQueue))
    {
        doubleLinkListQueueTop(pQueue, (void **)&nodeVal);
        #if 0
        printf ("data:%d\n", nodeVal->data);
        #else
        pBstree->printFunc(nodeVal->data);
        #endif
        doubleLinkListQueuePop(pQueue);

        /* 将左子树入队. */
        if (nodeVal->left != NULL)
        {
            doubleLinkListQueuePush(pQueue, nodeVal->left);
        }

        /* 将右子树入队. */
        if (nodeVal->right != NULL)
        {
            doubleLinkListQueuePush(pQueue, nodeVal->right);
        }
    }

    /* 释放队列 */
    doubleLinkListQueueDestroy(pQueue);
    return ret;
}

/* 根据指定的值获取二叉搜索树的结点 */
static RedBlackTreeNode * baseAppointValGetRedBlackTreeNode(RedBlackTree *pBstree, ELEMENTTYPE val)
{
    RedBlackTreeNode * travelNode = pBstree->root;

    int cmp = 0;
    while (travelNode != NULL)
    {
        /* 比较大小 */
        cmp = pBstree->compareFunc(val, travelNode->data);
        if (cmp < 0)
        {
            travelNode = travelNode->left;
        }
        else if (cmp > 0)
        {
            travelNode = travelNode->right;
        }
        else
        {
            /* 找到了. */
            return travelNode;
        }
    }
    return NULL;
}

/* 二叉搜索树是否包含指定的元素 */
int RedBlackTreeIsContainAppointVal(RedBlackTree *pBstree, ELEMENTTYPE val)
{
    return baseAppointValGetRedBlackTreeNode(pBstree, val) == NULL ? 0 : 1;
}


/* 获取二叉搜索树的高度 */
/* 层序遍历的思路. */
int RedBlackTreeGetHeight(RedBlackTree *pBstree, int *pHeight)
{
    if (pBstree == NULL)
    {
        return NULL_PTR;
    }

    /* 判断是否为空树 */
    if (pBstree->size == 0)
    {
        return 0;
    }
    int ret;
    DoubleLinkListQueue *pQueue = NULL;
    doubleLinkListQueueInit(&pQueue);

    doubleLinkListQueuePush(pQueue, pBstree->root);
    /* 树的高度 (根结点入队高度为) */
    int height = 0;
    /* 树每一层的结点数量 */
    int levelSize = 1;

    RedBlackTreeNode * travelNode = NULL;
    while(!doubleLinkListQueueIsEmpty(pQueue))
    {
        doubleLinkListQueueTop(pQueue, (void **)&travelNode);
        doubleLinkListQueuePop(pQueue);
        levelSize--;

        /* 左子树不为空 */
        if (travelNode->left != NULL)
        {
            doubleLinkListQueuePush(pQueue, travelNode->left);
        }

        /* 右子树不为空 */
        if (travelNode->right != NULL)
        {
            doubleLinkListQueuePush(pQueue, travelNode->right);
        }

        /* 树的当前层结点遍历结束 */
        if (levelSize == 0)
        {
            height++;
            doubleLinkListQueueGetSize(pQueue, &levelSize);
        }
    }
    /* 解引用 */
    *pHeight = height;

    /* 释放队列的空间 */
    doubleLinkListQueueDestroy(pQueue);
    return ret;
}

static int RedBlackTreeDeleteNode(RedBlackTree *pBstree, RedBlackTreeNode *node)
{
    int ret = 0;
    if (node == NULL)
    {
        return ret;
    }

    /* 树的结点减一 */
    (pBstree->size)--;

    if (RedBlackTreeNodeHasTwochildrens(node))
    {
        /* 找到前驱结点 */
        RedBlackTreeNode * preNode = RedBlackTreeNodePreDecessor(node);
        node->data = preNode->data;
        node = preNode;
    }

    /* 程序执行到这里. 要删除的结点要么是度为1 要么是度为0. */

    /* 假设node结点是度为1的。它的child要么是左要么是右. */
    /* 假设node结点是度为0的, */
    RedBlackTreeNode * child = node->left != NULL ? node->left : node->right;

    RedBlackTreeNode *delNode = NULL;
    if (child)
    {
        /* 度为1 */
        child->parent = node->parent;
        if (node->parent == NULL)
        {
            /* 度为1 且 它是根结点 */
            pBstree->root = child;

            delNode = node;
            #if 0
            if (node)
            {   
                free(node);
                node = NULL;
            }
            #endif
        }
        else
        {
            /* 度为1 且 它不是根结点 */
            if (node == node->parent->left)
            {
                node->parent->left = child;
            }
            else if (node == node->parent->right)
            {
                node->parent->right = child;
            }

            delNode = node;
            #if 0
            /* 释放结点 */
            if (node)
            {
                free(node);
                node = NULL;
            }
            #endif
        }
    }
    else
    {
        /* 度为0 */
        if (node->parent == NULL)
        {
            /* 度为0 且是根结点 */
            delNode = node;
            #if 0
            if (node)
            {
                free(node);
                node = NULL;
            }
            #endif
            /* 根结点置为NULL, 否则有bug. */
            pBstree->root = NULL;
        }
        else
        {
            if (node == node->parent->left)
            {
                node->parent->left = NULL;
            }
            else if (node == node->parent->right)
            {
                node->parent->right = NULL;
            }


            delNode = node;
            #if 0
            if (node)
            {
                free(node);
                node = NULL;
            }
            #endif
        }
       
    }

    if (delNode)
    {
        free(delNode);
        delNode = NULL;
    }
    
    return ret;
}

/* 二叉搜索树的删除 */
int RedBlackTreeDelete(RedBlackTree *pBstree, ELEMENTTYPE val)
{
    if (pBstree == NULL)
    {
        return NULL_PTR;
    }
    int ret = 0;
    #if 0
    RedBlackTreeNode * delNode = baseAppointValGetRedBlackTreeNode(pBstree, val);
    return RedBlackTreeDeleteNode(pBstree, delNode);
    #else
    return RedBlackTreeDeleteNode(pBstree, baseAppointValGetRedBlackTreeNode(pBstree, val));
    #endif
    return ret;
}


/* 二叉搜索树的销毁 */
int RedBlackTreeDestroy(RedBlackTree *pBstree)
{
    if (pBstree == NULL)
    {
        return NULL_PTR;
    }

    int ret;
    DoubleLinkListQueue *pQueue = NULL;
    doubleLinkListQueueInit(&pQueue);

    /* 将根结点入队 */
    doubleLinkListQueuePush(pQueue, pBstree->root);
    RedBlackTreeNode *travelNode = NULL;
    while (!doubleLinkListQueueIsEmpty(pQueue))
    {
        doubleLinkListQueueTop(pQueue, (void **)&travelNode);
        doubleLinkListQueuePop(pQueue);

        if (travelNode->left != NULL)
        {
            doubleLinkListQueuePush(pQueue, travelNode->left);
        }

        if (travelNode->right != NULL)
        {
            doubleLinkListQueuePush(pQueue, travelNode->right);
        }

        /* 最后释放 */
        if (travelNode)
        {
            free(travelNode);
            travelNode = NULL;
        }
    }
    /* 释放队列 */
    doubleLinkListQueueDestroy(pQueue);

    /* 释放树 */
    if (pBstree)
    {
        free(pBstree);
        pBstree = NULL;
    }
    return ret;
}


/* 判断二叉搜索树是否是完全二叉树 */
int RedBlackTreeIsComplete(RedBlackTree *pBSTree)
{
    int ret = 0;
    

    return ret;
}


/* 获取二叉搜索树的结点个数 */
int RedBlackTreeGetNodeSize(RedBlackTree *pBstree, int *pSize)
{
    if (pBstree == NULL)
    {
        return 0;
    }

    if (pSize)
    {
       *pSize = pBstree->size;
    }
    
    return pBstree->size;
}