/*================================================================================
 * 文件描述: 数据链表 
 * 文件版本: V1.00
 * 开发人员: wangrq
 * 定版时间:
 * 版本修订:
 * 修订人员:
 *================================================================================*/
#include <stdio.h>
#include "DataList.h"

//===========================================================
// 函数功能: 释放链表节点
//===========================================================
static void DataListFreeNode(tagListCtrl *ptListCtrl, tagListNode* pNode)
{
	UINT32 dwErrInfo = 0;
	
#if(CN_DATA_LIST_MODE==0)
    free(pNode);
#else
    //pNode->pNext = NULL;
		
	dwErrInfo = DataPoolPut(&ptListCtrl->tPoolCtrl, (void *)pNode);	
    if(dwErrInfo)
    {
        printf("DataListFreeNode Err: pNode=%p,ErrInfo=%d\n",pNode,dwErrInfo);
    }
#endif

    return;
}

//===========================================================
// 函数功能: 申请链表节点
//===========================================================
static tagListNode* DataListCreatNode(tagListCtrl *ptListCtrl, void *pData)
{
    tagListNode*  pNode;
    UINT32 		  dwIndex = 0, dwErrInfo = 0;
     
#if(CN_DATA_LIST_MODE==0)  
    pNode = (tagListNode *)malloc(sizeof(tagListNode));
#else
    //dwIndex = *((UINT32*)pData);
    //pNode = (dwIndex < ptListCtrl->dwBlk)? &ptListCtrl->pRam[dwIndex] : NULL;
    
   	pNode = (tagListNode *)DataPoolGet(&ptListCtrl->tPoolCtrl, &dwErrInfo);
   	if(!pNode||dwErrInfo)
   	{
        printf("DataListCreatNode Err: pNode=%p,ErrInfo=%d\n",pNode,dwErrInfo);
        return NULL;
    }
#endif

    if(pNode)
	{
	    pNode->pNext = NULL;
		pNode->pData = pData;
	}
	else
	{
		printf("DataListCreatNode Err!\n");
	}
  
    return pNode;
}

//===========================================================
// 函数功能: 查找链表节点
//===========================================================
static tagListNode* DataListSrchNode(tagListNode *pList, void *pData)
{
    tagListNode*  pWalk;    
         
    pWalk = pList;
    
    while(pWalk)
    {
        if(pWalk->pData==pData)
        {
            break;        
        }
        
        pWalk = pWalk->pNext;             
    }

    return pWalk;
}

//===========================================================
// 函数功能: 创建链表根节点
//===========================================================
UINT32 DataListBuild(tagListCtrl *ptListCtrl, tagListNode *pRam, UINT32 dwBlk)
{    
    UINT32	dwErrInfo = 0;
    
	ptListCtrl->pHead  = NULL; 
	//ptListCtrl->pfnCmp = pfnCmp;
	
    ptListCtrl->dwNum  = 0;
#if(CN_DATA_LIST_MODE!=0)
    //ptListCtrl->pRam  = pRam;           // 静态分配内存区指针 
    ptListCtrl->dwBlk = dwBlk;    	    // 静态分配内存块个数 
    
    dwErrInfo = DataPoolCreat(&ptListCtrl->tPoolCtrl, (void *)pRam, dwBlk, sizeof(tagListNode));	
	if(dwErrInfo)
	{
		printf("DataPoolCreat: ErrInfo=%d\n",dwErrInfo);		
		return dwErrInfo;
	}   
#endif

    return 0; 
}

//===========================================================
// 函数功能: 注册节点数据比较函数 
//===========================================================
UINT32 DataListFnCmp(tagListCtrl *ptListCtrl, FUNCPTR pfnCmp)
{    
	ptListCtrl->pfnCmp = pfnCmp;
    return 0; 
}

//===========================================================
// 函数功能: 注册节点数据显示函数 
//===========================================================
UINT32 DataListFnShow(tagListCtrl *ptListCtrl, FUNCPTR pfnShow)
{    
	ptListCtrl->pfnShow = pfnShow;
    return 0; 
}

//===========================================================
// 函数功能: 添加链表尾节点
//===========================================================
UINT32 DataListAdd(tagListCtrl *ptListCtrl, void *pData)
{
    tagListNode*  pNode;
    tagListNode** ppIndex;    
     
    pNode = DataListCreatNode(ptListCtrl, pData);
    if(!pNode)
    {
        return 1;
    }
      
    ppIndex = &ptListCtrl->pHead;
    while(*ppIndex)
    {
        ppIndex = &(*ppIndex)->pNext;             
    }
    *ppIndex = pNode;

	ptListCtrl->dwNum++;
	
    return 0;
}

//===========================================================
// 函数功能: 删除链表节点
//===========================================================
UINT32 DataListDel(tagListCtrl *ptListCtrl, void *pData)
{
    tagListNode*  pNode;
    tagListNode*  pHead;
    tagListNode** ppIndex; 
    
    pHead = ptListCtrl->pHead;
    if(!pHead)
    {
        return 1;
    }
    
    pNode = DataListSrchNode(pHead, pData);
    if(!pNode)
    {
        return 2;
    }

    ppIndex = &ptListCtrl->pHead;
    
    while((*ppIndex)!=pNode)
    {
        ppIndex = &(*ppIndex)->pNext;
    }
    
    *ppIndex = pNode->pNext;   
     
    DataListFreeNode(ptListCtrl, pNode); 
 
    ptListCtrl->dwNum--;
    
    return 0;
}

//===========================================================
// 函数功能: 截断链表节点-包含参数节点 
//===========================================================
UINT32 DataListCut(tagListCtrl *ptListCtrl, void *pData)
{   
    tagListNode*  pFree;
    tagListNode*  pHead;
    tagListNode*  pNode;
    tagListNode** ppIndex; 
	            
    pHead = ptListCtrl->pHead;
    if(!pHead)
    {
        return 1;
    }
    
    pNode = DataListSrchNode(pHead, pData);
    if(!pNode)
    {
        return 2;
    }

    ppIndex = &ptListCtrl->pHead;
    
    while((*ppIndex)!=pNode)
    {
        ppIndex = &(*ppIndex)->pNext;
    }
    
    *ppIndex = NULL;
    
    while(pNode)
    {
        pFree = pNode;        
        pNode = pNode->pNext;

        DataListFreeNode(ptListCtrl, pFree);

        ptListCtrl->dwNum--;

    }
    
    return 0;
}

//===========================================================
// 函数功能: 删除链表
//===========================================================
UINT32 DataListDestory(tagListCtrl *ptListCtrl)
{
    tagListNode*  pHead;    
             
    pHead = ptListCtrl->pHead;
    if(!pHead)
    {
        return 1;
    }
    
    DataListCut(ptListCtrl, pHead->pData); 
    
    ptListCtrl->pHead = NULL;
    
    return 0;

}

//===========================================================
// 函数功能: 查找链表节点
//===========================================================
tagListNode* DataListSrch(tagListCtrl *ptListCtrl, void *pData)
{        
    return DataListSrchNode(ptListCtrl->pHead, pData);
}
