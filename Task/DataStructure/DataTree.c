/*================================================================================
 * �ļ�����: ���ݶ����� 
 * �ļ��汾: V1.00
 * ������Ա: wangrq
 * ����ʱ��:
 * �汾�޶�:
 * �޶���Ա:
 *================================================================================*/
#include <stdio.h>
#include "DataTree.h"

//===========================================================
// ��������: �ͷŶ������ڵ�
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
// ��������: ����������ڵ�
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
// ��������: ���Ҷ������ڵ�
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
// ��������: ɾ���������ڵ�
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
// ��������: �������������ڵ�
//===========================================================
UINT32 DataTreeBuild(tagTreeCtrl *ptTreeCtrl, tagTreeNode *pRam, UINT32 dwBlk)
{
    UINT32	dwErrInfo = 0;
	    
	ptTreeCtrl->pRoot  = NULL; 
	//ptTreeCtrl->pfnCmp = pfnCmp;
	
    ptTreeCtrl->dwNum  = 0;
#if(CN_DATA_TREE_MODE!=0)
    //ptTreeCtrl->pRam  = pRam;           // ��̬�����ڴ���ָ�� 
    ptTreeCtrl->dwBlk = dwBlk;    	    // ��̬�����ڴ����� 
    
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
// ��������: ��Ӷ��������ڵ�
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
// ��������: ��Ӷ�����Ҷ�ӽڵ�
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
// ��������: ��Ӷ�����Ҷ�ӽڵ�
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
// ��������: �ض϶������ڵ�
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
// ��������: ɾ��������
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
// ��������: ɾ��������Ҷ�ӽڵ�
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
// ��������: ɾ��������Ҷ�ӽڵ�
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
// ��������: ���Ҷ������ڵ�
//===========================================================
tagTreeNode* DataTreeSrch(tagTreeCtrl *ptTreeCtrl, void *pData)
{
    return DataTreeSrchNode(ptTreeCtrl->pRoot, pData);
}
//===========================================================
// ��������: ���Ҷ������ڵ�
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
// ��������: ���Ҷ������ڵ�
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
// ��������: ���Ҷ�����Ҷ�ӽڵ� 
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
// ��������: ���Ҷ�����Ҷ�ӽڵ� 
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
