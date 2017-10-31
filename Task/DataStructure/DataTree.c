/*================================================================================
 * 文件描述: 数据二叉树 
 * 文件版本: V1.00
 * 开发人员: wangrq
 * 定版时间:
 * 版本修订:
 * 修订人员:
 *================================================================================*/
#include <stdio.h>
#include "DataTree.h"

//===========================================================
// 函数功能: 释放二叉树节点
//===========================================================
static void DataTreeFreeNode(tagTreeCtrl *ptTreeCtrl, tagTreeNode* pNode)
{
	UINT32 dwErrInfo = 0;
	
#if(CN_DATA_TREE_MODE==0)
    free(pNode);
#else
    //pNode->pRight = NULL;
    //pNode->pLeft  = NULL;
		
	dwErrInfo = DataPoolPut(&ptTreeCtrl->tPoolCtrl, (void *)pNode);	
    if(dwErrInfo)
    {
        printf("DataTreeFreeNode Err: pNode=%p,ErrInfo=%d\n",pNode,dwErrInfo);
    }
#endif

    return;
}

//===========================================================
// 函数功能: 申请二叉树节点
//===========================================================
static tagTreeNode* DataTreeCreatNode(tagTreeCtrl *ptTreeCtrl, void *pData)
{
    tagTreeNode*  pNode;
    UINT32 		  dwIndex = 0, dwErrInfo = 0;
     
#if(CN_DATA_TREE_MODE==0)  
    pNode = (tagTreeNode *)malloc(sizeof(tagTreeNode));
#else
    //dwIndex = *((UINT32*)pData);
    //pNode = (dwIndex < ptTreeCtrl->dwBlk)? &ptTreeCtrl->pRam[dwIndex] : NULL;

   	pNode = (tagTreeNode *)DataPoolGet(&ptTreeCtrl->tPoolCtrl, &dwErrInfo);
   	if(!pNode||dwErrInfo)
   	{
        printf("DataTreeCreatNode Err: pNode=%p,ErrInfo=%d\n",pNode,dwErrInfo);
        return NULL;
    }
#endif

    if(pNode)
    {
        pNode->pRight = NULL;
        pNode->pLeft  = NULL;
        pNode->pData  = pData;
    }
    else
    {
        printf("DataTreeCreatNode Err!\n");
    }
   
    return pNode;
}


//===========================================================
// 函数功能: 查找二叉树节点
//===========================================================
static tagTreeNode* DataTreeSrchNode(tagTreeNode *pTree, void *pData)
{
    tagTreeNode*  pWalk;
    tagTreeNode*  pNode;
    
    pWalk = pTree;
    if(!pWalk)
    {
        return NULL;
    }
    if(pWalk->pData==pData)
    {
        return pWalk;       
    }
    
    pNode = DataTreeSrchNode(pWalk->pRight, pData);
    if(pNode)
    {
        return pNode;       
    }   
    
    pNode = DataTreeSrchNode(pWalk->pLeft, pData);
    if(pNode)
    {
        return pNode;       
    }
        
    return pNode;
}

//===========================================================
// 函数功能: 删除二叉树节点
//===========================================================
static void DataTreeRmvTree(tagTreeCtrl *ptTreeCtrl, tagTreeNode *pTree)
{
    tagTreeNode*  pWalk;
    
    pWalk = pTree;
    if(!pWalk)
    {
        return;
    }
    
    DataTreeRmvTree(ptTreeCtrl, pWalk->pRight);

    DataTreeRmvTree(ptTreeCtrl, pWalk->pLeft);

    DataTreeFreeNode(ptTreeCtrl, pWalk);
    
    ptTreeCtrl->dwNum--;
        
    return ;
}

//===========================================================
// 函数功能: 创建二叉树根节点
//===========================================================
UINT32 DataTreeBuild(tagTreeCtrl *ptTreeCtrl, tagTreeNode *pRam, UINT32 dwBlk)
{
    UINT32	dwErrInfo = 0;
	    
	ptTreeCtrl->pRoot  = NULL; 
	//ptTreeCtrl->pfnCmp = pfnCmp;
	
    ptTreeCtrl->dwNum  = 0;
#if(CN_DATA_TREE_MODE!=0)
    //ptTreeCtrl->pRam  = pRam;           // 静态分配内存区指针 
    ptTreeCtrl->dwBlk = dwBlk;    	    // 静态分配内存块个数 
    
    dwErrInfo = DataPoolCreat(&ptTreeCtrl->tPoolCtrl, (void *)pRam, dwBlk, sizeof(tagTreeNode));	
	if(dwErrInfo)
	{
		printf("DataTreeBuild: ErrInfo=%d\n",dwErrInfo);		
		return dwErrInfo;
	}
#endif

    return 0; 
}

//===========================================================
// 函数功能: 添加二叉树根节点
//===========================================================
UINT32 DataTreeAddRoot(tagTreeCtrl *ptTreeCtrl, void *pData)
{
    tagTreeNode*  pNode;
	
	pNode = DataTreeCreatNode(ptTreeCtrl, pData);
    if(!pNode)
    {
        return 1;
    }
         
    ptTreeCtrl->pRoot = pNode;

    ptTreeCtrl->dwNum++;
    
	return 0;
}

//===========================================================
// 函数功能: 添加二叉树叶子节点
//===========================================================
UINT32 DataTreeAddRight(tagTreeCtrl *ptTreeCtrl, void *pData)
{
    tagTreeNode*  pNode;
    tagTreeNode*  pWalk;    
     
    pNode = DataTreeCreatNode(ptTreeCtrl, pData);
    if(!pNode)
    {
        return 1;
    }
         
    pWalk = ptTreeCtrl->pRoot;
    if(!pWalk)
    {
        return 2;
    }
    
    while(pWalk->pRight)
    {
        pWalk = pWalk->pRight;             
    }
    pWalk->pRight = pNode;
    
    ptTreeCtrl->dwNum++;
    
    return 0;
}


//===========================================================
// 函数功能: 添加二叉树叶子节点
//===========================================================
UINT32 DataTreeAddLeft(tagTreeCtrl *ptTreeCtrl, void *pData)
{
    tagTreeNode*  pNode;
    tagTreeNode*  pWalk;    
     
    pNode = DataTreeCreatNode(ptTreeCtrl, pData);
    if(!pNode)
    {
        return 1;
    }
         
    pWalk = ptTreeCtrl->pRoot;
    if(!pWalk)
    {
        return 2;
    }
    
    while(pWalk->pLeft)
    {
        pWalk = pWalk->pLeft;             
    }
    pWalk->pLeft = pNode;
    
    ptTreeCtrl->dwNum++;
    
    return 0;
}


//===========================================================
// 函数功能: 截断二叉树节点
//===========================================================
UINT32 DataTreePruning(tagTreeCtrl *ptTreeCtrl, void *pData)
{   
    tagTreeNode*  pFree;
    tagTreeNode*  pRoot;

                
    pRoot = ptTreeCtrl->pRoot;
    if(!pRoot)
    {
        return 1;
    }
    
    pFree = DataTreeSrchNode(pRoot, pData);
    if(!pFree)
    {
        return 2;
    }
    
    printf("DataTreeTrunc:%d\n",*((UINT32*)pFree->pData));
    
    DataTreeRmvTree(ptTreeCtrl, pFree->pLeft);
    DataTreeRmvTree(ptTreeCtrl, pFree->pRight);

	pFree->pLeft  = NULL;
	pFree->pRight = NULL;
    
	return 0;
}

//===========================================================
// 函数功能: 删除二叉树
//===========================================================
UINT32 DataTreeDestory(tagTreeCtrl *ptTreeCtrl)
{
    tagTreeNode*  pRoot;    
             
    pRoot = ptTreeCtrl->pRoot;
    if(!pRoot)
    {
        return 1;
    }
	  
    DataTreeRmvTree(ptTreeCtrl, pRoot);
    
    ptTreeCtrl->pRoot = NULL ;
    
    return 0;

}

//===========================================================
// 函数功能: 删除二叉树叶子节点
//===========================================================
UINT32 DataTreeCutLeft(tagTreeCtrl *ptTreeCtrl, void *pData)
{
    tagTreeNode*  pFree;
    tagTreeNode*  pRoot;
    tagTreeNode*  pNode;
    tagTreeNode** ppIndex; 

      
    pRoot = ptTreeCtrl->pRoot;
    if(!pRoot)
    {
        return 1;
    }
    
    pNode = DataTreeSrchNode(pRoot->pLeft, pData);
    if(!pNode)
    {
        return 2;
    }
    
    ppIndex = &ptTreeCtrl->pRoot->pLeft;
    
    while((*ppIndex)!=pNode)
    {
        ppIndex = &(*ppIndex)->pLeft;
    }
    
    *ppIndex = NULL;
    
    while(pNode)
    {
        pFree = pNode;        
        pNode = pNode->pLeft;

        DataTreeFreeNode(ptTreeCtrl, pFree);

        ptTreeCtrl->dwNum--;

    }    
       
    return 0;
}

//===========================================================
// 函数功能: 删除二叉树叶子节点
//===========================================================
UINT32 DataTreeCutRight(tagTreeCtrl *ptTreeCtrl, void *pData)
{
    tagTreeNode*  pFree;
    tagTreeNode*  pRoot;
    tagTreeNode*  pNode;
    tagTreeNode** ppIndex; 

      
    pRoot = ptTreeCtrl->pRoot;
    if(!pRoot)
    {
        return 1;
    }
    
    pNode = DataTreeSrchNode(pRoot->pRight, pData);
    if(!pNode)
    {
        return 2;
    }
    
    ppIndex = &ptTreeCtrl->pRoot->pRight;
    
    while((*ppIndex)!=pNode)
    {
        ppIndex = &(*ppIndex)->pRight;
    }
    
    *ppIndex = NULL;
    
    while(pNode)
    {
        pFree = pNode;        
        pNode = pNode->pRight;

        DataTreeFreeNode(ptTreeCtrl, pFree);

        ptTreeCtrl->dwNum--;

    }    
     
    return 0;
}
//===========================================================
// 函数功能: 查找二叉树节点
//===========================================================
tagTreeNode* DataTreeSrch(tagTreeCtrl *ptTreeCtrl, void *pData)
{
    return DataTreeSrchNode(ptTreeCtrl->pRoot, pData);
}
//===========================================================
// 函数功能: 查找二叉树节点
//===========================================================
tagTreeNode* DataTreeSrchLeft(tagTreeCtrl *ptTreeCtrl, void *pData)
{
	if(!ptTreeCtrl->pRoot)
	{
		return NULL;
	}
	
    return DataTreeSrchNode(ptTreeCtrl->pRoot->pLeft, pData);
}
//===========================================================
// 函数功能: 查找二叉树节点
//===========================================================
tagTreeNode* DataTreeSrchRight(tagTreeCtrl *ptTreeCtrl, void *pData)
{
	if(!ptTreeCtrl->pRoot)
	{
		return NULL;
	}

    return DataTreeSrchNode(ptTreeCtrl->pRoot->pRight, pData);
}
//===========================================================
// 函数功能: 查找二叉树叶子节点 
//===========================================================
tagTreeNode* DataTreeLeftLeaf(tagTreeCtrl *ptTreeCtrl)
{
    tagTreeNode** ppIndex; 
    
    if(!ptTreeCtrl->pRoot)
    {
    	return NULL;
    }
    
    ppIndex = &ptTreeCtrl->pRoot;
    
    while((*ppIndex)->pLeft)
	{
		ppIndex = &(*ppIndex)->pLeft; 
	}
	
    return *ppIndex;
}
//===========================================================
// 函数功能: 查找二叉树叶子节点 
//===========================================================
tagTreeNode* DataTreeRightLeaf(tagTreeCtrl *ptTreeCtrl)
{
    tagTreeNode** ppIndex; 
    
    if(!ptTreeCtrl->pRoot)
    {
    	return NULL;
    }
    
    ppIndex = &ptTreeCtrl->pRoot;
    
    while((*ppIndex)->pRight)
	{
		ppIndex = &(*ppIndex)->pRight; 
	}
	
    return *ppIndex;
}
