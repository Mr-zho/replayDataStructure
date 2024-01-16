#include "balanceBinarySearchTree.h"
#include <stdlib.h>
#include <string.h>
#include "doubleLinkListQueue.h"
#include <math.h>

/* 状态码 */
enum STATUS_CODE
{
    ON_SUCCESS,
    NULL_PTR,
    MALLOC_ERROR,
    INVALID_ACCESS,
};

#define true    1
#define false   0

/* 静态函数前置声明 */

/* 两个值比较大小 */
static int compareFunc(ELEMENTTYPE val1, ELEMENTTYPE val2);
/* 创建结点 */
static AVLTreeNode *createAVLTreeNewNode(ELEMENTTYPE val, AVLTreeNode *parent);
/* 根据指定的值获取二叉搜索树的结点 */
static AVLTreeNode * baseAppointValGetAVLTreeNode(BalanceBinarySearchTree *pBstree, ELEMENTTYPE val);
/* 判断二叉搜索树度为2 */
static int balanceBinarySearchTreeNodeHasTwochildrens(AVLTreeNode *node);
/* 判断二叉搜索树度为1 */
static int balanceBinarySearchTreeNodeHasOnechildren(AVLTreeNode *node);
/* 判断二叉搜索树度为0 */
static int balanceBinarySearchTreeNodeIsLeaf(AVLTreeNode *node);
/* 前序遍历 */
static int preOrderTravel(BalanceBinarySearchTree *pBstree, AVLTreeNode *node);
/* 中序遍历 */
static int inOrderTravel(BalanceBinarySearchTree *pBstree, AVLTreeNode *node);
/* 后序遍历 */
static int postOrderTravel(BalanceBinarySearchTree *pBstree, AVLTreeNode *node);
/* 获取当前结点的前驱结点 */
static AVLTreeNode * bstreeNodePreDecessor(AVLTreeNode *node);
/* 获取当前结点的后继结点 */
static AVLTreeNode * bstreeNodeSuccessor(AVLTreeNode *node);
/* 二叉搜索树删除指定的结点 */
static int balanceBinarySearchTreeDeleteNode(BalanceBinarySearchTree *pBstree, AVLTreeNode *node);
/* 添加结点之后要做的事情 */
static int insertNodeAfter(BalanceBinarySearchTree *pBstree, AVLTreeNode *node);
/* 删除结点之后要做的事情 */
static int removeNodeAfter(BalanceBinarySearchTree *pBstree, AVLTreeNode *node);
/* 计算结点的平衡因子 */
static int AVLTreeNodeBalanceFactor(AVLTreeNode *node);
/* 判断结果是否平衡 */
static int AVLTreeNodeIsBalanced(AVLTreeNode *node);
/* 更新结点的高度. */
static int AVLTreeNodeUpdateHeight(AVLTreeNode *node);
/* AVL树结点调整平衡 */
static int AVLTreeNodeAdjustBalance(BalanceBinarySearchTree *pBstree, AVLTreeNode *node);
/* 获取AVL结点较高的子结点 */
static AVLTreeNode * AVLTreeNodeGetChildTaller(AVLTreeNode *node);
/* 当前结点是父结点的左子树 */
static int AVLTreeCurrentNodeIsLeft(AVLTreeNode *node);
/* 当前结点是父结点的右子树 */
static int AVLTreeCurrentNodeIsRight(AVLTreeNode *node);
/* 左旋 */
static int AVLTreeCurrentNodeRotateLeft(BalanceBinarySearchTree *pBstree, AVLTreeNode *grand);
/* 右旋 */
static int AVLTreeCurrentNodeRotateRight(BalanceBinarySearchTree *pBstree, AVLTreeNode *grand);


/* 二叉搜索树的初始化 */
int balanceBinarySearchTreeInit(BalanceBinarySearchTree **pBstree, int (*compareFunc)(ELEMENTTYPE val1, ELEMENTTYPE val2), int (*printFunc)(ELEMENTTYPE val))
{
    int ret = 0;
    BalanceBinarySearchTree * bstree = (BalanceBinarySearchTree *)malloc(sizeof(BalanceBinarySearchTree) * 1);
    if (bstree == NULL)
    {
        return MALLOC_ERROR;
    }
    /* 清除脏数据 */
    memset(bstree, 0, sizeof(BalanceBinarySearchTree) * 1);
    /* 初始化树 */
    {
        /* 树的根结点置为NULL. */
        bstree->root = NULL;
        /* 树的结点个数为0. */
        bstree->size = 0;

        /* 钩子函数在这边赋值. */
        bstree->compareFunc = compareFunc;
        /* 钩子函数包装器 自定义打印. */
        bstree->printFunc = printFunc;
    }
   
    *pBstree = bstree;
    return ret;
}

/* 当前结点是父结点的左子树 */
static int AVLTreeCurrentNodeIsLeft(AVLTreeNode *node)
{
    return (node->parent != NULL) && (node == node->parent->left);
}

/* 当前结点是父结点的右子树 */
static int AVLTreeCurrentNodeIsRight(AVLTreeNode *node)
{
    return (node->parent != NULL ) && (node == node->parent->right);
}

/* 计算结点的平衡因子 */
/* 左子树 - 右子树 */
static int AVLTreeNodeBalanceFactor(AVLTreeNode *node)
{
    /* 左子树的高度 */
    int leftHeight = node->left == NULL ? 0 : node->left->height;
    /* 右子树的高度 */
    int rightHeight = node->right == NULL ? 0 : node->right->height;

    return leftHeight - rightHeight;
}

/* 判断结果是否平衡 */
static int AVLTreeNodeIsBalanced(AVLTreeNode *node)
{
    #if 0
    return abs(AVLTreeNodeBalanceFactor(node)) <= 1;
    #else
    int nodeFactor = abs(AVLTreeNodeBalanceFactor(node));
    if (nodeFactor <= 1)
    {
        return true;
    }
    else
    {
        return false;
    }
    #endif
}


static int tmpMax(int val1, int val2)
{   
    return val1 - val2 >= 0 ? val1 : val2;
}

/* 更新结点的高度. */
static int AVLTreeNodeUpdateHeight(AVLTreeNode *node)
{
    int ret = 0;
    /* 左子树的高度 */
    int leftHeight = node->left == NULL ? 0 : node->left->height;
    /* 右子树的高度 */
    int rightHeight = node->right == NULL ? 0 : node->right->height;
#if 1
    node->height = 1 + tmpMax(leftHeight, rightHeight);
#else
    return 1 + tmpMax(leftHeight, rightHeight);
#endif
    return ret;
}

/* 判断二叉搜索树度为2 */
static int balanceBinarySearchTreeNodeHasTwochildrens(AVLTreeNode *node)
{
    return (node->left != NULL) && (node->right != NULL);
}

/* 判断二叉搜索树度为1 */
static int balanceBinarySearchTreeNodeHasOnechildren(AVLTreeNode *node)
{
    return ((node->left == NULL) && (node->right != NULL)) || ((node->left != NULL) && (node->right == NULL));
}

/* 判断二叉搜索树度为0 */
static int balanceBinarySearchTreeNodeIsLeaf(AVLTreeNode *node)
{
    return (node->left == NULL) && (node->right == NULL);
}

/* 获取当前结点的前驱结点 */
/* 中序遍历到结点的前一个结点 */
static AVLTreeNode * bstreeNodePreDecessor(AVLTreeNode *node)
{
    if (node->left != NULL)
    {
        /* 前驱结点是在左子树的右子树的右子树... */
        AVLTreeNode *travelNode = node->left;
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
static AVLTreeNode * bstreeNodeSuccessor(AVLTreeNode *node)
{
    if (node->right != NULL)
    {
        /* 后继结点是在右子树的左子树的左子树的左子树... */
        AVLTreeNode *travelNode = node->right;
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


static AVLTreeNode *createAVLTreeNewNode(ELEMENTTYPE val, AVLTreeNode *parent)
{
    /* 分配根结点 */
    AVLTreeNode * newAVLNode = (AVLTreeNode *)malloc(sizeof(AVLTreeNode) * 1);
    if (newAVLNode == NULL)
    {
        return NULL;
    }
    /* 清除脏数据 */
    memset(newAVLNode, 0, sizeof(AVLTreeNode) * 1);
    /* 初始化根结点 */
    {
        newAVLNode->data = 0;
        /* 结点的高度为1. */
        newAVLNode->height = 1;
        newAVLNode->left = NULL;
        newAVLNode->right = NULL;
        newAVLNode->parent = NULL;
    }

    /* 赋值 */
    newAVLNode->data = val;
    newAVLNode->parent = parent;
    return newAVLNode;
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

/* 获取AVL结点较高的子结点 */
static AVLTreeNode * AVLTreeNodeGetChildTaller(AVLTreeNode *node)
{
    /* 左子树高度 */
    int leftHeight = node->left == NULL ? 0 : node->left->height;
    /* 右子树高度 */
    int rightHeight = node->right == NULL ? 0 : node->right->height;
    if (leftHeight > rightHeight)
    {
        return node->left;
    }
    else if (leftHeight < rightHeight)
    {
        return node->right;
    }
    else
    {
        /* leftHeight == rightHeight */
        if (AVLTreeCurrentNodeIsLeft(node))
        {
            return node->left;
        }
        else if (AVLTreeCurrentNodeIsRight(node))
        {
            return node->right;
        }
    }
}

static int AVLTreeNodeRotate(BalanceBinarySearchTree *pBstree, AVLTreeNode *grand, AVLTreeNode *parent, AVLTreeNode *child)
{
    int ret = 0;
    /* p成为新的根结点 */
    parent->parent = grand->parent;   // 3

    if(AVLTreeCurrentNodeIsRight(grand))
    {
        grand->parent->right = parent;      // 4
    }
    else if (AVLTreeCurrentNodeIsLeft(grand))
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
    AVLTreeNodeUpdateHeight(grand);
    AVLTreeNodeUpdateHeight(parent);

    return ret;
}

/* 左旋 : RR */
static int AVLTreeCurrentNodeRotateLeft(BalanceBinarySearchTree *pBstree, AVLTreeNode *grand)
{
    int ret = 0;

    AVLTreeNode * parent = grand->right;
    AVLTreeNode * child = parent->left;

    grand->right = child;        // 1
    parent->left = grand;        // 2

#if 0
    /* p成为新的根结点 */
    parent->parent = grand->parent;   // 3

    if(AVLTreeCurrentNodeIsRight(grand))
    {
        grand->parent->right = parent;      // 4
    }
    else if (AVLTreeCurrentNodeIsLeft(grand))
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
    AVLTreeNodeUpdateHeight(grand);
    AVLTreeNodeUpdateHeight(parent);
#else
    AVLTreeNodeRotate(pBstree, grand, parent, child);
#endif
    return ret;
}

/* 右旋 */
static int AVLTreeCurrentNodeRotateRight(BalanceBinarySearchTree *pBstree, AVLTreeNode *grand)
{
    int ret = 0;
    /* */
    AVLTreeNode *parent = grand->left;
    AVLTreeNode *child = parent->right;

    grand->left = child;                // 1
    parent->right = grand;              // 2

#if 0
    /* p成为新的根结点 */
    parent->parent = grand->parent;     // 3

    if (AVLTreeCurrentNodeIsLeft(grand))
    {
        grand->parent->left = parent;   // 4
    }
    else if (AVLTreeCurrentNodeIsRight(grand))
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
    AVLTreeNodeUpdateHeight(grand);
    AVLTreeNodeUpdateHeight(parent);
#else
    AVLTreeNodeRotate(pBstree, grand, parent, child);
#endif
    return ret;
}

/* AVL树结点调整平衡 */
/* node一定是最低的不平衡结点 */
static int AVLTreeNodeAdjustBalance(BalanceBinarySearchTree *pBstree, AVLTreeNode *node)
{
    /* LL LR RL RR */
    AVLTreeNode *parent = AVLTreeNodeGetChildTaller(node);
    AVLTreeNode *child = AVLTreeNodeGetChildTaller(parent);

    /* L */
    if (AVLTreeCurrentNodeIsLeft(parent))
    {
        if (AVLTreeCurrentNodeIsLeft(child))
        {
            /* LL - 右旋 */
            AVLTreeCurrentNodeRotateRight(pBstree, node);
        }
        else if (AVLTreeCurrentNodeIsRight(child))
        {
            /* LR */
            AVLTreeCurrentNodeRotateLeft(pBstree, parent);
            AVLTreeCurrentNodeRotateRight(pBstree, node);
        }
    }
    else
    {
        /* R */
        if (AVLTreeCurrentNodeIsLeft(child))
        {
            /* RL */
            AVLTreeCurrentNodeRotateRight(pBstree, parent);
            AVLTreeCurrentNodeRotateLeft(pBstree, node);
        }
        else if (AVLTreeCurrentNodeIsRight(child))
        {
            /* RR */
            AVLTreeCurrentNodeRotateLeft(pBstree, node);

        }
    }
}

/* 删除结点之后要做的事情 */
/* node参数是要删除的结点 */
static int removeNodeAfter(BalanceBinarySearchTree *pBstree, AVLTreeNode *node)
{
    int ret = 0;
    /* 时间复杂度是O(logN) */
    while ( (node = node->parent) != NULL)
    {
        /* 程序执行到这里面的时候, 一定不止一个结点. */
        if (AVLTreeNodeIsBalanced(node))
        {
            /* 如果结点是平衡的. 那就更新高度. */
            AVLTreeNodeUpdateHeight(node);
        }
        else
        {
            /* node是最低不平衡结点 */
            /* 调整平衡 */
            AVLTreeNodeAdjustBalance(pBstree, node);
        }
    }
    return ret;
}

/* 添加结点之后的操作. */
/* 新添加的结点一定是叶子结点 */
static int insertNodeAfter(BalanceBinarySearchTree *pBstree, AVLTreeNode *node)
{
    int ret = 0;
    /* todo... */
    while ( (node = node->parent) != NULL)
    {
        /* 程序执行到这里面的时候, 一定不止一个结点. */
        if (AVLTreeNodeIsBalanced(node))
        {
            /* 如果结点是平衡的. 那就更新高度. */
            AVLTreeNodeUpdateHeight(node);
        }
        else
        {
            /* node是最低不平衡结点 */
            /* 调整平衡 */
            AVLTreeNodeAdjustBalance(pBstree, node);
            
            /* 调整完最低的不平衡结点, 上面的不平衡结点就已经平衡. */
            break;
        }
    }
    return ret;
}


/* 二叉搜索树的插入 */
int balanceBinarySearchTreeInsert(BalanceBinarySearchTree *pBstree, ELEMENTTYPE val)
{
    int ret = 0;

    /* 如果是空树. */
    if (pBstree->root == NULL)
    {
        pBstree->root = createAVLTreeNewNode(val, NULL);
        /* 更新树的结点 */
        (pBstree->size)++;
        insertNodeAfter(pBstree, pBstree->root);
        return ret;
    }

    

    /* travelNode 指向根结点 */
    AVLTreeNode * travelNode = pBstree->root;
    AVLTreeNode * parentNode = pBstree->root;

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
    AVLTreeNode * newAVLNode = (AVLTreeNode *)malloc(sizeof(AVLTreeNode) * 1);
    if (newAVLNode == NULL)
    {
        return MALLOC_ERROR;
    }
    memset(newAVLNode, 0, sizeof(AVLTreeNode) * 1);
    {
        newAVLNode->data = 0;
        newAVLNode->left = NULL;
        newAVLNode->right = NULL;
        newAVLNode->parent = NULL;
    }
    /* 新结点赋值 */
    newAVLNode->data = val;
    #else
    AVLTreeNode * newAVLNode = createAVLTreeNewNode(val, parentNode);
    #endif

    /* 挂在左子树 */
    if (cmp < 0)
    {
        parentNode->left = newAVLNode;
    }
    else
    {   
        /* 挂在右子树 */
        parentNode->right = newAVLNode;
    }
    /* 添加之后的调整 */
    insertNodeAfter(pBstree, newAVLNode);

#if 0
    /* 新结点的parent指针赋值 */
    newAVLNode->parent = parentNode;
#endif

    /* 更新树的结点 */
    (pBstree->size)++;
    return ret;
}


/* 前序遍历 */
/* 根结点 左子树 右子树 */
static int preOrderTravel(BalanceBinarySearchTree *pBstree, AVLTreeNode *node)
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
int balanceBinarySearchTreePreOrderTravel(BalanceBinarySearchTree *pBstree)
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
static int inOrderTravel(BalanceBinarySearchTree *pBstree, AVLTreeNode *node)
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
int balanceBinarySearchTreeInOrderTravel(BalanceBinarySearchTree *pBstree)
{
    int ret = 0;
    inOrderTravel(pBstree, pBstree->root);
    return ret;
}

/* 后序遍历 */
/* 左子树 右子树 根结点 */
static int postOrderTravel(BalanceBinarySearchTree *pBstree, AVLTreeNode *node)
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
int balanceBinarySearchTreePostOrderTravel(BalanceBinarySearchTree *pBstree)
{
    int ret = 0;
    postOrderTravel(pBstree, pBstree->root); 
    return ret;
}

/* 二叉搜索树的层序遍历 */
int balanceBinarySearchTreeLevelOrderTravel(BalanceBinarySearchTree *pBstree)
{
    int ret = 0;
    DoubleLinkListQueue * pQueue = NULL;
    doubleLinkListQueueInit(&pQueue);

    /* 1. 根结点入队 */
    doubleLinkListQueuePush(pQueue, pBstree->root);

    /* 2. 判断队列是否为空 */
    AVLTreeNode *nodeVal = NULL;
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
static AVLTreeNode * baseAppointValGetAVLTreeNode(BalanceBinarySearchTree *pBstree, ELEMENTTYPE val)
{
    AVLTreeNode * travelNode = pBstree->root;

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
int balanceBinarySearchTreeIsContainAppointVal(BalanceBinarySearchTree *pBstree, ELEMENTTYPE val)
{
    return baseAppointValGetAVLTreeNode(pBstree, val) == NULL ? 0 : 1;
}


/* 获取二叉搜索树的高度 */
/* 层序遍历的思路. */
int balanceBinarySearchTreeGetHeight(BalanceBinarySearchTree *pBstree, int *pHeight)
{
    if (pBstree == NULL)
    {
        return NULL_PTR;
    }

    int ret;
    /* 判断是否为空树 */
    if (pBstree->root == NULL)
    {
        return 0;
    }
    DoubleLinkListQueue *pQueue = NULL;
    doubleLinkListQueueInit(&pQueue);

    doubleLinkListQueuePush(pQueue, (void *)(pBstree->root));
    /* 树的高度 (根结点入队高度为) */
    int height = 0;
    /* 树每一层的结点数量 */
    int levelSize = 1;

    AVLTreeNode * travelNode = NULL;
    while(!doubleLinkListQueueIsEmpty(pQueue))
    {
        doubleLinkListQueueTop(pQueue, (void **)&travelNode);
        pBstree->printFunc(travelNode->data);
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

static int balanceBinarySearchTreeDeleteNode(BalanceBinarySearchTree *pBstree, AVLTreeNode *node)
{
    int ret = 0;
    if (node == NULL)
    {
        return ret;
    }

    /* 树的结点减一 */
    (pBstree->size)--;
    
    /* 删除度为2的结点 */
    if (balanceBinarySearchTreeNodeHasTwochildrens(node))
    {
        /* 找到前驱结点 */
        AVLTreeNode * preNode = bstreeNodePreDecessor(node);
        node->data = preNode->data;
        node = preNode;
    }

    /* 程序执行到这里. 要删除的结点要么是度为1 要么是度为0. */

    /* 假设node结点是度为1的。它的child要么是左要么是右. */
    /* 假设node结点是度为0的, */
    AVLTreeNode * child = node->left != NULL ? node->left : node->right;

    AVLTreeNode *delNode = NULL;
    if (child)
    {
        /* 度为1 */
        child->parent = node->parent;
        if (node->parent == NULL)
        {
            /* 度为1 且 它是根结点 */
            pBstree->root = child;

            delNode = node;

            /* 删除的结点 */
            removeNodeAfter(pBstree, delNode);
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

            /* 删除的结点 */
            removeNodeAfter(pBstree, delNode);
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

            /* 删除的结点 */
            removeNodeAfter(pBstree, delNode);
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
            if (node == node->parent->left)
            {
                node->parent->left = NULL;
            }
            else if (node == node->parent->right)
            {
                node->parent->right = NULL;
            }

            delNode = node;
            /* 删除的结点 */
            removeNodeAfter(pBstree, delNode);
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
int balanceBinarySearchTreeDelete(BalanceBinarySearchTree *pBstree, ELEMENTTYPE val)
{
    if (pBstree == NULL)
    {
        return NULL_PTR;
    }
    int ret = 0;
    #if 0
    AVLTreeNode * delNode = baseAppointValGetAVLTreeNode(pBstree, val);
    return balanceBinarySearchTreeDeleteNode(pBstree, delNode);
    #else
    return balanceBinarySearchTreeDeleteNode(pBstree, baseAppointValGetAVLTreeNode(pBstree, val));
    #endif
    return ret;
}


/* 二叉搜索树的销毁 */
int balanceBinarySearchTreeDestroy(BalanceBinarySearchTree *pBstree)
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
    AVLTreeNode *travelNode = NULL;
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
int balanceBinarySearchTreeIsComplete(BalanceBinarySearchTree *pBSTree)
{
    int ret = 0;
    

    return ret;
}


/* 获取二叉搜索树的结点个数 */
int balanceBinarySearchTreeGetNodeSize(BalanceBinarySearchTree *pBstree, int *pSize)
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