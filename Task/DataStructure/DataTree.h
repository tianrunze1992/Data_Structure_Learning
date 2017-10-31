/*================================================================================
 * 文件描述: 数据二叉树 
 * 文件版本: V1.00
 * 开发人员: wangrq
 * 定版时间:
 * 版本修订:
 * 修订人员:
 *================================================================================*/

#ifndef _DATATREE_H_
#define _DATATREE_H_


//#include "Resource.h"
//#include "InstCell.h"
#include "Macro.h"
#include "DataPool.h"

#ifdef __cplusplus
extern "C" {
#endif

/*================================================================================*/

#define CN_DATA_TREE_MODE	( CN_DATA_LOCATE_MODE )    // 0-动态分配模式 1-静态分配模式

// 定义数据二叉树节点
typedef struct TreeNode
{
    struct TreeNode* pRight;        // 右侧节点指针 
    struct TreeNode* pLeft ;        // 左侧节点指针 

    void             *pData;        // 节点数据指针

}tagTreeNode;

// 数据二叉树控制结构体
typedef struct
{
    tagTreeNode     *pRoot;         // 二叉树根节点指针
    FUNCPTR         pfnCmp;         // 函数指针-比较节点数据 
    
    FUNCPTR         pfnShow;        // 函数指针-显示节点数据     
    UINT32          dwNum;          // 节点个数
#if(CN_DATA_TREE_MODE!=0)
    //tagTreeNode     *pRam;          // 静态分配内存区指针 
    UINT32			dwBlk;    	    // 静态分配内存块个数 

    tagPoolCtrl     tPoolCtrl;		// 静态分配内存池 
#endif

}tagTreeCtrl; 

/*================================================================================
 * 对外声明函数
 *================================================================================*/
extern UINT32 DataTreeBuild(tagTreeCtrl *ptTreeCtrl, tagTreeNode *pRam, UINT32 dwBlk);
extern UINT32 DataTreeDestory(tagTreeCtrl *ptTreeCtrl);

extern UINT32 DataTreeAddRoot(tagTreeCtrl *ptTreeCtrl, void *pData);
extern UINT32 DataTreeAddLeft(tagTreeCtrl *ptTreeCtrl, void *pData);
extern UINT32 DataTreeAddRight(tagTreeCtrl *ptTreeCtrl, void *pData);

extern UINT32 DataTreeCutLeft(tagTreeCtrl *ptTreeCtrl, void *pData); 
extern UINT32 DataTreeCutRight(tagTreeCtrl *ptTreeCtrl, void *pData);

extern tagTreeNode* DataTreeSrch(tagTreeCtrl *ptTreeCtrl, void *pData);
extern tagTreeNode* DataTreeSrchLeft(tagTreeCtrl *ptTreeCtrl, void *pData);
extern tagTreeNode* DataTreeSrchRight(tagTreeCtrl *ptTreeCtrl, void *pData);

extern tagTreeNode* DataTreeLeftLeaf(tagTreeCtrl *ptTreeCtrl);
extern tagTreeNode* DataTreeRightLeaf(tagTreeCtrl *ptTreeCtrl);
/*================================================================================*/


#ifdef __cplusplus
}
#endif

#endif
