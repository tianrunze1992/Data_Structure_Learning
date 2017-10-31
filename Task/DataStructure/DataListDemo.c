#include <stdio.h>
#include "DataList.h"


#define CN_DATA_LIST_NUM            ( 4 )    // 静态分配模式支持节点数量

static tagListNode g_tRam[CN_DATA_LIST_NUM];

static UINT32      g_dwData[]={0,1,2,3,4,5,6,7,8,9,10};

void DataListShow(tagListCtrl *ptListCtrl)
{
    tagListNode*  pNode;
 
    printf("DataList: Addr=%p,Num=%d\n",ptListCtrl->pHead,ptListCtrl->dwNum);
    
    pNode = ptListCtrl->pHead;
    
    while(pNode)
    {
        printf("DataList: Addr=%p,Next=%p,Data=%d\n",pNode,			\
													 pNode->pNext,	\
													 *((UINT32*)pNode->pData));
    
        pNode = pNode->pNext;   
    }

	printf("/*****DataPoolShow*****/\n");
    DataPoolInfo(&ptListCtrl->tPoolCtrl);
	DataPoolShow(&ptListCtrl->tPoolCtrl);   

    return;   
}
void DataListShowNode(tagListNode*  pNode)
{ 
    printf("DataList: DataListShowNode Addr=%p\n",pNode);
       
    while(pNode)
    {
        printf("DataList: Addr=%p,Next=%p,Data=%d\n",pNode,			\
													 pNode->pNext,	\
													 *((UINT32*)pNode->pData));
    
        pNode = pNode->pNext;   
    }


    return;   
}


int DataListDemo(void)
{
	tagListCtrl 	g_tListCtrl; 
	
	// Initial 
	DataListBuild(&g_tListCtrl, &g_tRam[0], CN_DATA_LIST_NUM);
	
	// main 
	DataListAdd(&g_tListCtrl, &g_dwData[1]);
	DataListAdd(&g_tListCtrl, &g_dwData[2]);
	DataListAdd(&g_tListCtrl, &g_dwData[3]);
	DataListAdd(&g_tListCtrl, &g_dwData[4]);
	DataListAdd(&g_tListCtrl, &g_dwData[5]);
	DataListAdd(&g_tListCtrl, &g_dwData[6]);

	DataListAdd(&g_tListCtrl, &g_dwData[0]);
	DataListShow(&g_tListCtrl);


	DataListDel(&g_tListCtrl, &g_dwData[1]);	
	DataListShow(&g_tListCtrl);
	
	DataListAdd(&g_tListCtrl, &g_dwData[1]);	
	DataListShow(&g_tListCtrl);


	DataListCut(&g_tListCtrl, &g_dwData[4]);	
	DataListShow(&g_tListCtrl);

	
	DataListDestory(&g_tListCtrl);
	DataListShow(&g_tListCtrl);

	DataListAdd(&g_tListCtrl, &g_dwData[1]);	
	DataListShow(&g_tListCtrl);
	DataListAdd(&g_tListCtrl, &g_dwData[2]);	
	DataListShow(&g_tListCtrl);
	
	return 0;
}
