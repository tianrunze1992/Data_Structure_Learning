/*================================================================================
 * 文件描述: 充电机分组链表
 * 文件版本: V1.00
 * 开发人员: wangrq
 * 定版时间:
 * 版本修订:
 * 修订人员:
 *================================================================================*/
#include <stdio.h>
#include "EVC_GrpList.h"

const UINT32           g_dwPlugNo[CN_EVC_GRP_NUM] = { 0, 1, 2, 3 };
static tagGrpInfo      g_tGrpInfo[CN_EVC_GRP_NUM];
static tagListNode     g_tGrpListRam[CN_EVC_GRP_NUM];

//===========================================================
// 函数功能: 显示充电机分组链表
//===========================================================
void  EVC_GrpListShow(tagListCtrl* ptGrpCtrl)
{
    tagGrpInfo      *ptGrpInfo;
    tagListCtrl     *ptListCtrl;      // 充电机分组内部链表-记录启动顺序
    tagTreeCtrl     *ptTreeCtrl;      // 充电机分组内部二叉树-记录功率方向
    tagListNode	    *pGrpNode;
		
	pGrpNode = ptGrpCtrl->pHead;
	
	while(pGrpNode)
	{
		ptGrpInfo  = (tagGrpInfo*)pGrpNode->pData;
		ptListCtrl = &ptGrpInfo->tListCtrl;
		ptTreeCtrl = &ptGrpInfo->tTreeCtrl;
		
		printf("++++++++++++++++++++++++++++\n");
		printf("GrpInfo:GrpNo=%d\n",ptGrpInfo->dwGrpNo);
		//DataListShow(ptGrpCtrl);
		DataListShow(ptListCtrl);		
		DataTreeShow(ptTreeCtrl);
		printf("****************************\n");

		pGrpNode = pGrpNode->pNext;
	}
	
	printf("\n\n\n\n\n");
}

//===========================================================
// 函数功能: 构造充电机分组链表
//===========================================================
UINT32 EVC_GrpListBuild(tagListCtrl* ptGrpCtrl)
{
    return DataListBuild(ptGrpCtrl, &g_tGrpListRam[0], CN_EVC_GRP_NUM);
}

//===========================================================
// 函数功能: 分组链表添加节点
//===========================================================
UINT32 EVC_GrpListChk(tagListCtrl* ptGrpCtrl, UINT32 dwGrpNo)
{
    tagGrpInfo      *ptGrpInfo;
    tagListNode	    *pGrpNode;
    tagListCtrl     *ptListCtrl;
 
    // 该节点是否被占用 
	pGrpNode = ptGrpCtrl->pHead;	
	while(pGrpNode)
	{
		ptGrpInfo  = (tagGrpInfo*)pGrpNode->pData;
		ptListCtrl = &ptGrpInfo->tListCtrl;
		
		if(DataListSrch(ptListCtrl, (UINT32 *)&g_dwPlugNo[dwGrpNo]))
		{
			return 1;			
		}
		pGrpNode = pGrpNode->pNext;
	}
	
    return 0;
}

//===========================================================
// 函数功能: 分组链表添加节点
//===========================================================
UINT32 EVC_GrpListAdd(tagListCtrl* ptGrpCtrl, UINT32 dwGrpNo)
{
    UINT32          *pdwGrpNo;
    tagGrpInfo      *ptGrpInfo;
    tagListCtrl     *ptList;      // 充电机分组内部链表-记录启动顺序
    tagTreeCtrl     *ptTree;      // 充电机分组内部二叉树-记录功率方向
    tagListNode	    *pGrpNode;
    tagListCtrl     *ptListCtrl;

    if(dwGrpNo>=CN_EVC_GRP_NUM)
    {
        return 1;
    }
    
    // 该节点是否被占用 
	if(EVC_GrpListChk(ptGrpCtrl, dwGrpNo))
	{
		printf("EVC_GrpListAdd:Err Exist In GrpList!\n");
		return 2;
	}

    // 指针初始化
    pdwGrpNo = (UINT32 *)&g_dwPlugNo[dwGrpNo];
    
    ptGrpInfo = &g_tGrpInfo[dwGrpNo];
    ptList = &ptGrpInfo->tListCtrl;
    ptTree = &ptGrpInfo->tTreeCtrl;

    // 查找该分组节点 
	if(DataListSrch(ptGrpCtrl, ptGrpInfo))
	{
		printf("EVC_GrpListAdd:Err Exist In MstList!\n");
		return 3;		
	}

    // 内部链表、内部二叉树初始化
    DataListBuild(ptList, &ptGrpInfo->tListRam[0], CN_EVC_GRP_NUM);
    DataTreeBuild(ptTree, &ptGrpInfo->tTreeRam[0], CN_EVC_GRP_NUM);

    // 添加内部充电抢号信息
	ptGrpInfo->dwGrpNo = *pdwGrpNo;

    return DataListAdd(ptGrpCtrl, ptGrpInfo);
}

//===========================================================
// 函数功能: 分组链表删除节点
//===========================================================
UINT32 EVC_GrpListDel(tagListCtrl* ptGrpCtrl, UINT32 dwGrpNo)
{
    UINT32          *pdwPlugNo;
    tagGrpInfo      *ptGrpInfo;
    tagListCtrl     *ptList;      // 充电机分组内部链表-记录启动顺序
    tagTreeCtrl     *ptTree;      // 充电机分组内部二叉树-记录功率方向

    if(dwGrpNo>=CN_EVC_GRP_NUM)
    {
        return 1;
    }

    // 指针初始化
    pdwPlugNo = (UINT32 *)&g_dwPlugNo[dwGrpNo];
    ptGrpInfo = &g_tGrpInfo[dwGrpNo];
    ptList = &ptGrpInfo->tListCtrl;
    ptTree = &ptGrpInfo->tTreeCtrl;

	// 查找该分组节点 
	if(!DataListSrch(ptGrpCtrl, ptGrpInfo))
	{
		printf("EVC_GrpListDel:Err Nothing!\n");
		return 2;		
	}

	// 删除内部链表、内部二叉树
    DataListDestory(ptList);
    DataTreeDestory(ptTree);

    return DataListDel(ptGrpCtrl, ptGrpInfo);
}

//===========================================================
// 函数功能: 删除充电机分组链表
//===========================================================
UINT32 EVC_GrpListDestory(tagListCtrl* ptGrpCtrl)
{
    UINT32          dwLoop;
    //UINT32          *pdwPlugNo;
    tagGrpInfo      *ptGrpInfo;
    tagListCtrl     *ptList;      // 充电机分组内部链表-记录启动顺序
    tagTreeCtrl     *ptTree;      // 充电机分组内部二叉树-记录功率方向

    // 指针初始化
    //pdwPlugNo = (UINT32 *)&g_dwPlugNo[0];
    ptGrpInfo = &g_tGrpInfo[0];

    for(dwLoop=0;dwLoop<CN_EVC_GRP_NUM;dwLoop++)
    {
        ptList = &ptGrpInfo->tListCtrl;
        ptTree = &ptGrpInfo->tTreeCtrl;

    	// 删除内部链表、内部二叉树
        DataListDestory(ptList);
        DataTreeDestory(ptTree);

        //pdwPlugNo++;
        ptGrpInfo++;
    }

    return DataListDestory(ptGrpCtrl);
}

//===========================================================
// 函数功能: 分组链表节点升级
//===========================================================
UINT32 EVC_GrpNodeUpgd(tagListCtrl* ptGrpCtrl, tagGrpTrans *ptGrpTrans)
{
    UINT32          dwGrpNo, dwPlugNo, dwTrans, dwLeafNo;
    UINT32          *pdwPlugNo;
    tagGrpInfo      *ptGrpInfo;
    tagListCtrl     *ptList;      // 充电机分组内部链表-记录启动顺序
    tagTreeCtrl     *ptTree;      // 充电机分组内部二叉树-记录功率方向 
	tagTreeNode		*ptLeaf;
    tagListNode	    *pGrpNode;
    tagListCtrl     *ptListCtrl;
    
    dwGrpNo  = ptGrpTrans->dwGrpNo;
    dwPlugNo = ptGrpTrans->dwPlugNo;
    dwTrans  = ptGrpTrans->dwTrans;

    if(dwGrpNo>=CN_EVC_GRP_NUM)
    {
        return 1;
    }
    if(dwPlugNo>=CN_EVC_GRP_NUM)
    {
        return 2;
    }
    // 该节点是否被占用 
	if(EVC_GrpListChk(ptGrpCtrl, dwPlugNo))
	{
		printf("EVC_GrpNodeUpgd:Err Exist In GrpList!\n");
		return 2;
	} 
    
    // 指针初始化
    pdwPlugNo = (UINT32 *)&g_dwPlugNo[dwPlugNo];
    
    ptGrpInfo = &g_tGrpInfo[dwGrpNo];
    ptList = &ptGrpInfo->tListCtrl;
    ptTree = &ptGrpInfo->tTreeCtrl;

	// 查找该分组节点 
	if(!DataListSrch(ptGrpCtrl, ptGrpInfo))
	{
		printf("EVC_GrpNodeUpgd:Err Nothing!\n");
		return 3;		
	}

	// 添加内部二叉树、内部链表节点
	switch(dwTrans)
	{
	    case EN_GRP_LIST_UPGD_NONE:
	    	if(ptTree->pRoot)
	    	{
		    	printf("EVC_GrpNodeUpgd:Err ROOT,none null\n");
		    	return 5;	    		
	    	}
	    	    
	    	if(dwGrpNo==*pdwPlugNo)
	    	{
		        DataTreeAddRoot(ptTree, pdwPlugNo);
	     		DataListAdd(ptList, pdwPlugNo);	    		
	    	}
	    	else
	    	{
	    		printf("EVC_GrpNodeUpgd:Err NONE,%d,%d\n",dwGrpNo,*pdwPlugNo);
	    	}
	        break;
	    case EN_GRP_LIST_UPGD_LEFT:
			ptLeaf = DataTreeLeftLeaf(ptTree);		
   			if(!ptLeaf)
		    {
		    	printf("EVC_GrpNodeUpgd:Err LEFT,null\n");
		    	return 6;
		    }
			
			dwLeafNo = *((UINT32*)ptLeaf->pData);		
	        if((dwLeafNo)==((*pdwPlugNo+1)%ptGrpCtrl->dwBlk))
	    	{
		        DataTreeAddLeft(ptTree, pdwPlugNo);
	        	DataListAdd(ptList, pdwPlugNo);    		
	    	}
	    	else
	    	{
	    		printf("EVC_GrpNodeUpgd:Err LEFT,%d,%d\n",dwLeafNo,*pdwPlugNo);
	    	    return 7;
	    	}	
			break;
	    case EN_GRP_LIST_UPGD_RIGHT:
			ptLeaf = DataTreeRightLeaf(ptTree);
   			if(!ptLeaf)
		    {
		    	printf("EVC_GrpNodeUpgd:Err RIGHT,null\n");
		    	return 8;
		    }
			
			dwLeafNo = *((UINT32*)ptLeaf->pData);		
	        if((*pdwPlugNo)==((dwLeafNo+1)%ptGrpCtrl->dwBlk))
	    	{
		        DataTreeAddRight(ptTree, pdwPlugNo);
	        	DataListAdd(ptList, pdwPlugNo);    		
	    	}
	    	else
	    	{
	    		printf("EVC_GrpNodeUpgd:Err RIGHT,%d,%d\n",dwLeafNo,*pdwPlugNo);
	    	    return 9;
			}
	        break;
	    default:
	        return 10;

	        break;
	}
					
    return 0;
}

//===========================================================
// 函数功能: 分组链表节点降级
//===========================================================
UINT32 EVC_GrpNodeDegd(tagListCtrl* ptGrpCtrl, tagGrpTrans *ptGrpTrans)
{
    UINT32          dwGrpNo, dwPlugNo, dwTrans;
    UINT32          *pdwPlugNo;
    tagGrpInfo      *ptGrpInfo;
    tagListCtrl     *ptList;      // 充电机分组内部链表-记录启动顺序
    tagTreeCtrl     *ptTree;      // 充电机分组内部二叉树-记录功率方向
    tagTreeNode		*pNode, *pFree; 

    dwGrpNo  = ptGrpTrans->dwGrpNo;
    dwPlugNo = ptGrpTrans->dwPlugNo;
    dwTrans  = ptGrpTrans->dwTrans;

    if(dwGrpNo>=CN_EVC_GRP_NUM)
    {
        return 1;
    }
    if(dwPlugNo>=CN_EVC_GRP_NUM)
    {
        return 2;
    }

    // 指针初始化
    pdwPlugNo = (UINT32 *)&g_dwPlugNo[dwPlugNo];
    
    ptGrpInfo = &g_tGrpInfo[dwGrpNo];
    ptList = &ptGrpInfo->tListCtrl;
    ptTree = &ptGrpInfo->tTreeCtrl;

	// 查找该分组节点 
	if(!DataListSrch(ptGrpCtrl, ptGrpInfo))
	{
		printf("EVC_GrpNodeDegd:Srch Err\n");
		return 3;		
	}
    
	// 删除内部二叉树、内部链表节点	  
 	if(pNode = DataTreeSrchLeft(ptTree, pdwPlugNo))
	{
		 while(pNode)
		 {
			 pFree = pNode;
			 pNode = pNode->pLeft;		
			 DataListDel(ptList, pFree->pData);
		 }
		 DataTreeCutLeft(ptTree, pdwPlugNo);
 	 }
	 else if(pNode = DataTreeSrchRight(ptTree, pdwPlugNo))
	 {
		 while(pNode)
		 {
			 pFree = pNode;
			 pNode = pNode->pRight;		
			 DataListDel(ptList, pFree->pData);
		 }
		 DataTreeCutRight(ptTree, pdwPlugNo);
 	 }
	 else if(dwGrpNo==*pdwPlugNo)
	 {
		 DataListDestory(ptList);
	 	 DataTreeDestory(ptTree);	 	 
	 }
	 else
	 {
		  printf("EVC_GrpNodeDegd:Err Nothing\n");
		  return 4;		
 	 }
	 
    return 0;
}
//===========================================================
// 函数功能: 封装分组链表变换事件 
//===========================================================
void EVC_GrpListTrans(tagGrpTrans *pTrans, UINT32 dwGrpNo, UINT32 dwPlugNo, UINT32 dwTrans) 
{
	pTrans->dwGrpNo  = dwGrpNo;
	pTrans->dwPlugNo = dwPlugNo;
	pTrans->dwTrans  = dwTrans;	
}
//===========================================================
// 函数功能: 响应分组链表变换事件 
//===========================================================
void EVC_GrpListResp(tagGrpTrans *ptTrans, tagListCtrl* ptGrpCtrl)
{
	UINT32	dwGrpNo, dwPlugNo, dwTrans;
	
	dwGrpNo  = ptTrans->dwGrpNo;
	dwPlugNo = ptTrans->dwPlugNo;
	dwTrans  = ptTrans->dwTrans;
	
	switch(dwTrans)
	{
		case EN_MST_LIST_ADD:
			EVC_GrpListAdd(ptGrpCtrl, dwGrpNo);
printf("Trans Add:GrpNo=%d,PlugNo=%d\n",dwGrpNo, dwPlugNo);
			break;
		case EN_MST_LIST_DEL:
			EVC_GrpListDel(ptGrpCtrl, dwGrpNo);
printf("Trans Del:GrpNo=%d,PlugNo=%d\n",dwGrpNo, dwPlugNo);			
			break;
		case EN_GRP_LIST_UPGD_NONE:
		case EN_GRP_LIST_UPGD_LEFT:
		case EN_GRP_LIST_UPGD_RIGHT:			
			EVC_GrpNodeUpgd(ptGrpCtrl, ptTrans);
printf("Trans Upgd:GrpNo=%d,PlugNo=%d\n",dwGrpNo, dwPlugNo);			
			break;
		case EN_GRP_LIST_DEGD_NONE:
			EVC_GrpNodeDegd(ptGrpCtrl, ptTrans);
printf("Trans Degd:GrpNo=%d,PlugNo=%d\n",dwGrpNo, dwPlugNo);		
			break;
		default :
			break;		
	}

}
//===========================================================
// 函数功能: 获取MasterList根节点指针 
//===========================================================
tagListNode* EVC_GetMstListHead(tagListCtrl* ptGrpCtrl)
{
	return  ptGrpCtrl->pHead;
}
//===========================================================
// 函数功能: 获取GroupList根节点指针 
//===========================================================
tagListNode* EVC_GetGrpListHead(tagListCtrl* ptGrpCtrl, UINT32 dwGrpNo)
{
    tagGrpInfo      *ptGrpInfo;

    if(dwGrpNo>=CN_EVC_GRP_NUM)
    {
        return NULL;
    }
        
    // 指针初始化   
    ptGrpInfo = &g_tGrpInfo[dwGrpNo];
    
    if(DataListSrch(ptGrpCtrl, ptGrpInfo))
    {
    	return ptGrpInfo->tListCtrl.pHead;  	
    }
    else
    {
        return NULL;    	
    }
}
//===========================================================
// 函数功能: 获取GroupTree根节点指针 
//===========================================================
tagTreeNode* EVC_GetGrpTreeRoot(tagListCtrl* ptGrpCtrl, UINT32 dwGrpNo)
{
    tagGrpInfo      *ptGrpInfo;

    if(dwGrpNo>=CN_EVC_GRP_NUM)
    {
        return NULL;
    }
    
    // 指针初始化   
    ptGrpInfo = &g_tGrpInfo[dwGrpNo];

    if(DataListSrch(ptGrpCtrl, ptGrpInfo))
	{
    	return ptGrpInfo->tTreeCtrl.pRoot;		
	}
	else
	{
        return NULL;		
	}
}

