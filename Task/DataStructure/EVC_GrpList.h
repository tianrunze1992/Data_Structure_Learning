/*================================================================================
 * 文件描述: 充电机分组链表
 * 文件版本: V1.00
 * 开发人员: wangrq
 * 定版时间:
 * 版本修订:
 * 修订人员:
 *================================================================================*/

#ifndef _EVC_GRP_LIST_H_
#define _EVC_GRP_LIST_H_


//#include "Resource.h"
//#include "InstCell.h"
#include "DataList.h"
#include "DataTree.h"

#ifdef __cplusplus
extern "C" {
#endif

/*================================================================================*/

#define CN_EVC_GRP_NUM         ( 4 )                  // 多枪分组支持的组数

#define M_CAST_UINT(pData)	   (*((UINT32*)pData))    // void* 转换 UINT32 

// 定义充电分组节点的升级/降级方向
enum _EVC_GRP_LIST_TRANS_TYPE_
{	
	EN_MST_LIST_ADD,     	   // 添加分组节点--Add Master	
	EN_MST_LIST_DEL,     	   // 删除分组节点--Del Master

	EN_GRP_LIST_UPGD_NONE,     // 内部根节点--Add Grp
    EN_GRP_LIST_UPGD_LEFT,     // 内部左节点--Add Grp
    EN_GRP_LIST_UPGD_RIGHT,    // 内部右节点--Add Grp
    
   	EN_GRP_LIST_DEGD_NONE,     // 未知节点--Del Grp
};

/*================================================================================*/
// 定义充电机分组信息结构体
typedef struct
{  
    //--第一个成员的位置不可变动 --need fix 
	UINT32          dwGrpNo;        // 充电机分组号 

    tagListCtrl     tListCtrl;      // 充电机分组内部链表-记录启动顺序
    tagTreeCtrl     tTreeCtrl;      // 充电机分组内部二叉树-记录功率方向
    
    tagListNode     tListRam[CN_EVC_GRP_NUM];
    tagTreeNode     tTreeRam[CN_EVC_GRP_NUM];
    
}tagGrpInfo;

// 定义充电机分组信息结构体
typedef struct
{  
    UINT32          dwGrpNo;        // 充电机分组节点号
    UINT32          dwPlugNo;       // 充电机分组内部的变化节点号
    UINT32          dwTrans;        // 充电机分组内部的变化节点方向
}tagGrpTrans;

/*================================================================================*/
// 外部函数声明
/*================================================================================*/

extern void   EVC_GrpListShow(tagListCtrl* ptGrpCtrl);         // 显示充电机分组链表

extern UINT32 EVC_GrpListBuild(tagListCtrl* ptGrpCtrl);        // 构造充电机分组链表
extern UINT32 EVC_GrpListDestory(tagListCtrl* ptGrpCtrl);      // 删除充电机分组链表
                                                                               
extern UINT32 EVC_GrpListAdd(tagListCtrl* ptGrpCtrl, UINT32 dwGrpNo);     // 分组链表添加节点-仅添加GrpNode,不添加内部节点
extern UINT32 EVC_GrpListDel(tagListCtrl* ptGrpCtrl, UINT32 dwGrpNo);     // 分组链表删除节点

extern UINT32 EVC_GrpNodeUpgd(tagListCtrl* ptGrpCtrl, tagGrpTrans *ptGrpTrans);     // 分组链表节点变化升级-仅添加内部节点
extern UINT32 EVC_GrpNodeDegd(tagListCtrl* ptGrpCtrl, tagGrpTrans *ptGrpTrans);     // 分组链表节点变化降级-仅删除内部节点

extern void EVC_GrpListTrans(tagGrpTrans *pTrans, UINT32 dwGrpNo, UINT32 dwPlugNo, UINT32 dwTrans);
extern void EVC_GrpListResp(tagGrpTrans *ptTrans, tagListCtrl* ptGrpCtrl);

extern tagListNode* EVC_GetMstListHead(tagListCtrl* ptGrpCtrl);
extern tagListNode* EVC_GetGrpListHead(tagListCtrl* ptGrpCtrl, UINT32 dwGrpNo);
extern tagTreeNode* EVC_GetGrpTreeRoot(tagListCtrl* ptGrpCtrl, UINT32 dwGrpNo);
/*================================================================================*/


#ifdef __cplusplus
}
#endif

#endif
