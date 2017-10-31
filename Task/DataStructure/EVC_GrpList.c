/*================================================================================
 * �ļ�����: ������������
 * �ļ��汾: V1.00
 * ������Ա: wangrq
 * ����ʱ��:
 * �汾�޶�:
 * �޶���Ա:
 *================================================================================*/
#include <stdio.h>
#include "EVC_GrpList.h"

const UINT32           g_dwPlugNo[CN_EVC_GRP_NUM] = { 0, 1, 2, 3 };
static tagGrpInfo      g_tGrpInfo[CN_EVC_GRP_NUM];
static tagListNode     g_tGrpListRam[CN_EVC_GRP_NUM];

//===========================================================
// ��������: ��ʾ������������
//===========================================================
void  EVC_GrpListShow(tagListCtrl* ptGrpCtrl)
{
    tagGrpInfo      *ptGrpInfo;
    tagListCtrl     *ptListCtrl;      // ���������ڲ�����-��¼����˳��
    tagTreeCtrl     *ptTreeCtrl;      // ���������ڲ�������-��¼���ʷ���
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
// ��������: ���������������
//===========================================================
UINT32 EVC_GrpListBuild(tagListCtrl* ptGrpCtrl)
{
    return DataListBuild(ptGrpCtrl, &g_tGrpListRam[0], CN_EVC_GRP_NUM);
}

//===========================================================
// ��������: ����������ӽڵ�
//===========================================================
UINT32 EVC_GrpListChk(tagListCtrl* ptGrpCtrl, UINT32 dwGrpNo)
{
    tagGrpInfo      *ptGrpInfo;
    tagListNode	    *pGrpNode;
    tagListCtrl     *ptListCtrl;
 
    // �ýڵ��Ƿ�ռ�� 
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
// ��������: ����������ӽڵ�
//===========================================================
UINT32 EVC_GrpListAdd(tagListCtrl* ptGrpCtrl, UINT32 dwGrpNo)
{
    UINT32          *pdwGrpNo;
    tagGrpInfo      *ptGrpInfo;
    tagListCtrl     *ptList;      // ���������ڲ�����-��¼����˳��
    tagTreeCtrl     *ptTree;      // ���������ڲ�������-��¼���ʷ���
    tagListNode	    *pGrpNode;
    tagListCtrl     *ptListCtrl;

    if(dwGrpNo>=CN_EVC_GRP_NUM)
    {
        return 1;
    }
    
    // �ýڵ��Ƿ�ռ�� 
	if(EVC_GrpListChk(ptGrpCtrl, dwGrpNo))
	{
		printf("EVC_GrpListAdd:Err Exist In GrpList!\n");
		return 2;
	}

    // ָ���ʼ��
    pdwGrpNo = (UINT32 *)&g_dwPlugNo[dwGrpNo];
    
    ptGrpInfo = &g_tGrpInfo[dwGrpNo];
    ptList = &ptGrpInfo->tListCtrl;
    ptTree = &ptGrpInfo->tTreeCtrl;

    // ���Ҹ÷���ڵ� 
	if(DataListSrch(ptGrpCtrl, ptGrpInfo))
	{
		printf("EVC_GrpListAdd:Err Exist In MstList!\n");
		return 3;		
	}

    // �ڲ������ڲ���������ʼ��
    DataListBuild(ptList, &ptGrpInfo->tListRam[0], CN_EVC_GRP_NUM);
    DataTreeBuild(ptTree, &ptGrpInfo->tTreeRam[0], CN_EVC_GRP_NUM);

    // ����ڲ����������Ϣ
	ptGrpInfo->dwGrpNo = *pdwGrpNo;

    return DataListAdd(ptGrpCtrl, ptGrpInfo);
}

//===========================================================
// ��������: ��������ɾ���ڵ�
//===========================================================
UINT32 EVC_GrpListDel(tagListCtrl* ptGrpCtrl, UINT32 dwGrpNo)
{
    UINT32          *pdwPlugNo;
    tagGrpInfo      *ptGrpInfo;
    tagListCtrl     *ptList;      // ���������ڲ�����-��¼����˳��
    tagTreeCtrl     *ptTree;      // ���������ڲ�������-��¼���ʷ���

    if(dwGrpNo>=CN_EVC_GRP_NUM)
    {
        return 1;
    }

    // ָ���ʼ��
    pdwPlugNo = (UINT32 *)&g_dwPlugNo[dwGrpNo];
    ptGrpInfo = &g_tGrpInfo[dwGrpNo];
    ptList = &ptGrpInfo->tListCtrl;
    ptTree = &ptGrpInfo->tTreeCtrl;

	// ���Ҹ÷���ڵ� 
	if(!DataListSrch(ptGrpCtrl, ptGrpInfo))
	{
		printf("EVC_GrpListDel:Err Nothing!\n");
		return 2;		
	}

	// ɾ���ڲ������ڲ�������
    DataListDestory(ptList);
    DataTreeDestory(ptTree);

    return DataListDel(ptGrpCtrl, ptGrpInfo);
}

//===========================================================
// ��������: ɾ��������������
//===========================================================
UINT32 EVC_GrpListDestory(tagListCtrl* ptGrpCtrl)
{
    UINT32          dwLoop;
    //UINT32          *pdwPlugNo;
    tagGrpInfo      *ptGrpInfo;
    tagListCtrl     *ptList;      // ���������ڲ�����-��¼����˳��
    tagTreeCtrl     *ptTree;      // ���������ڲ�������-��¼���ʷ���

    // ָ���ʼ��
    //pdwPlugNo = (UINT32 *)&g_dwPlugNo[0];
    ptGrpInfo = &g_tGrpInfo[0];

    for(dwLoop=0;dwLoop<CN_EVC_GRP_NUM;dwLoop++)
    {
        ptList = &ptGrpInfo->tListCtrl;
        ptTree = &ptGrpInfo->tTreeCtrl;

    	// ɾ���ڲ������ڲ�������
        DataListDestory(ptList);
        DataTreeDestory(ptTree);

        //pdwPlugNo++;
        ptGrpInfo++;
    }

    return DataListDestory(ptGrpCtrl);
}

//===========================================================
// ��������: ��������ڵ�����
//===========================================================
UINT32 EVC_GrpNodeUpgd(tagListCtrl* ptGrpCtrl, tagGrpTrans *ptGrpTrans)
{
    UINT32          dwGrpNo, dwPlugNo, dwTrans, dwLeafNo;
    UINT32          *pdwPlugNo;
    tagGrpInfo      *ptGrpInfo;
    tagListCtrl     *ptList;      // ���������ڲ�����-��¼����˳��
    tagTreeCtrl     *ptTree;      // ���������ڲ�������-��¼���ʷ��� 
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
    // �ýڵ��Ƿ�ռ�� 
	if(EVC_GrpListChk(ptGrpCtrl, dwPlugNo))
	{
		printf("EVC_GrpNodeUpgd:Err Exist In GrpList!\n");
		return 2;
	} 
    
    // ָ���ʼ��
    pdwPlugNo = (UINT32 *)&g_dwPlugNo[dwPlugNo];
    
    ptGrpInfo = &g_tGrpInfo[dwGrpNo];
    ptList = &ptGrpInfo->tListCtrl;
    ptTree = &ptGrpInfo->tTreeCtrl;

	// ���Ҹ÷���ڵ� 
	if(!DataListSrch(ptGrpCtrl, ptGrpInfo))
	{
		printf("EVC_GrpNodeUpgd:Err Nothing!\n");
		return 3;		
	}

	// ����ڲ����������ڲ�����ڵ�
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
// ��������: ��������ڵ㽵��
//===========================================================
UINT32 EVC_GrpNodeDegd(tagListCtrl* ptGrpCtrl, tagGrpTrans *ptGrpTrans)
{
    UINT32          dwGrpNo, dwPlugNo, dwTrans;
    UINT32          *pdwPlugNo;
    tagGrpInfo      *ptGrpInfo;
    tagListCtrl     *ptList;      // ���������ڲ�����-��¼����˳��
    tagTreeCtrl     *ptTree;      // ���������ڲ�������-��¼���ʷ���
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

    // ָ���ʼ��
    pdwPlugNo = (UINT32 *)&g_dwPlugNo[dwPlugNo];
    
    ptGrpInfo = &g_tGrpInfo[dwGrpNo];
    ptList = &ptGrpInfo->tListCtrl;
    ptTree = &ptGrpInfo->tTreeCtrl;

	// ���Ҹ÷���ڵ� 
	if(!DataListSrch(ptGrpCtrl, ptGrpInfo))
	{
		printf("EVC_GrpNodeDegd:Srch Err\n");
		return 3;		
	}
    
	// ɾ���ڲ����������ڲ�����ڵ�	  
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
// ��������: ��װ��������任�¼� 
//===========================================================
void EVC_GrpListTrans(tagGrpTrans *pTrans, UINT32 dwGrpNo, UINT32 dwPlugNo, UINT32 dwTrans) 
{
	pTrans->dwGrpNo  = dwGrpNo;
	pTrans->dwPlugNo = dwPlugNo;
	pTrans->dwTrans  = dwTrans;	
}
//===========================================================
// ��������: ��Ӧ��������任�¼� 
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
// ��������: ��ȡMasterList���ڵ�ָ�� 
//===========================================================
tagListNode* EVC_GetMstListHead(tagListCtrl* ptGrpCtrl)
{
	return  ptGrpCtrl->pHead;
}
//===========================================================
// ��������: ��ȡGroupList���ڵ�ָ�� 
//===========================================================
tagListNode* EVC_GetGrpListHead(tagListCtrl* ptGrpCtrl, UINT32 dwGrpNo)
{
    tagGrpInfo      *ptGrpInfo;

    if(dwGrpNo>=CN_EVC_GRP_NUM)
    {
        return NULL;
    }
        
    // ָ���ʼ��   
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
// ��������: ��ȡGroupTree���ڵ�ָ�� 
//===========================================================
tagTreeNode* EVC_GetGrpTreeRoot(tagListCtrl* ptGrpCtrl, UINT32 dwGrpNo)
{
    tagGrpInfo      *ptGrpInfo;

    if(dwGrpNo>=CN_EVC_GRP_NUM)
    {
        return NULL;
    }
    
    // ָ���ʼ��   
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

