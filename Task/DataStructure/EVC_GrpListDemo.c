#include <stdio.h>
#include "EVC_GrpList.h"

double x;

void DuplicateErr()
{
	x = -0.0;
}

int EVC_GrpListDemo(void)
{
	tagListCtrl 	g_tGrpCtrl; 
	tagGrpTrans		g_tGrpTrans;
	
	// Initial 
	EVC_GrpListBuild(&g_tGrpCtrl);
	
	// main
	EVC_GrpListTrans(&g_tGrpTrans, 1, 1, EN_MST_LIST_ADD);
	EVC_GrpListResp(&g_tGrpTrans, &g_tGrpCtrl);
	EVC_GrpListShow(&g_tGrpCtrl);
	
	EVC_GrpListTrans(&g_tGrpTrans, 1, 1, EN_GRP_LIST_UPGD_NONE);
	EVC_GrpListResp(&g_tGrpTrans, &g_tGrpCtrl);
	EVC_GrpListShow(&g_tGrpCtrl);
	
	EVC_GrpListTrans(&g_tGrpTrans, 1, 2, EN_GRP_LIST_UPGD_RIGHT);
	EVC_GrpListResp(&g_tGrpTrans, &g_tGrpCtrl);
	EVC_GrpListShow(&g_tGrpCtrl);

	EVC_GrpListTrans(&g_tGrpTrans, 1, 0, EN_GRP_LIST_UPGD_LEFT);
	EVC_GrpListResp(&g_tGrpTrans, &g_tGrpCtrl);
	EVC_GrpListShow(&g_tGrpCtrl);

	EVC_GrpListTrans(&g_tGrpTrans, 1, 3, EN_GRP_LIST_UPGD_RIGHT);
	EVC_GrpListResp(&g_tGrpTrans, &g_tGrpCtrl);
	EVC_GrpListShow(&g_tGrpCtrl);

	EVC_GrpListTrans(&g_tGrpTrans, 1, 2, EN_GRP_LIST_DEGD_NONE);
	EVC_GrpListResp(&g_tGrpTrans, &g_tGrpCtrl);
	EVC_GrpListShow(&g_tGrpCtrl);

	EVC_GrpListTrans(&g_tGrpTrans, 2, 1, EN_MST_LIST_ADD);
	EVC_GrpListResp(&g_tGrpTrans, &g_tGrpCtrl);
	EVC_GrpListShow(&g_tGrpCtrl);

	EVC_GrpListTrans(&g_tGrpTrans, 2, 2, EN_GRP_LIST_UPGD_NONE);
	EVC_GrpListResp(&g_tGrpTrans, &g_tGrpCtrl);
	EVC_GrpListShow(&g_tGrpCtrl);

	EVC_GrpListTrans(&g_tGrpTrans, 2, 3, EN_GRP_LIST_UPGD_RIGHT);
	EVC_GrpListResp(&g_tGrpTrans, &g_tGrpCtrl);
	EVC_GrpListShow(&g_tGrpCtrl);

//	EVC_GrpListTrans(&g_tGrpTrans, 1, 3, EN_MST_LIST_DEL);
//	EVC_GrpListResp(&g_tGrpTrans, &g_tGrpCtrl);
//	EVC_GrpListShow(&g_tGrpCtrl);

	DataListShowNode(EVC_GetMstListHead(&g_tGrpCtrl));	
	DataListShowNode(EVC_GetGrpListHead(&g_tGrpCtrl, 3));
	DataTreeShowNode(EVC_GetGrpTreeRoot(&g_tGrpCtrl, 3));

//	EVC_GrpListTrans(&g_tGrpTrans, 2, 3, EN_MST_LIST_DEL);
//	EVC_GrpListResp(&g_tGrpTrans, &g_tGrpCtrl);
//	EVC_GrpListShow(&g_tGrpCtrl);
//	
//
//	EVC_GrpListTrans(&g_tGrpTrans, 3, 1, EN_MST_LIST_ADD);
//	EVC_GrpListResp(&g_tGrpTrans, &g_tGrpCtrl);
//	EVC_GrpListShow(&g_tGrpCtrl);
//	
//
//	EVC_GrpListTrans(&g_tGrpTrans, 2, 3, EN_MST_LIST_DEL);
//	EVC_GrpListResp(&g_tGrpTrans, &g_tGrpCtrl);
//	EVC_GrpListShow(&g_tGrpCtrl);
	return 0;
}
