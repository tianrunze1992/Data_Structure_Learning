/*================================================================================
 * 文件描述: 数据链表
 * 文件版本: V1.00
 * 开发人员: wangrq
 * 定版时间:
 * 版本修订:
 * 修订人员:
 *================================================================================*/

#ifndef _DATALIST_H_
#define _DATALIST_H_


//#include "Resource.h"
//#include "InstCell.h"
#include "Macro.h"
#include "DataPool.h"

#ifdef __cplusplus
extern "C" {
#endif

/*================================================================================*/

#define CN_DATA_LIST_MODE	( CN_DATA_LOCATE_MODE )   // 0-动态分配模式 1-静态分配模式


// 定义数据链表节点
typedef struct ListNode
{
    struct ListNode* pNext;         // 下一个节点指针 

    void             *pData;        // 节点数据
    
}tagListNode;

// 数据链表控制结构体
typedef struct
{
    tagListNode     *pHead;         // 链表头部指针
    FUNCPTR         pfnCmp;         // 函数指针-比较节点数据 
    
    FUNCPTR         pfnShow;        // 函数指针-显示节点数据     
    UINT32          dwNum;          // 节点个数
#if(CN_DATA_LIST_MODE!=0)
//    tagListNode     *pRam;          // 静态分配内存区指针 
    UINT32			dwBlk;    	    // 静态分配内存块个数 
    
    tagPoolCtrl     tPoolCtrl;		// 静态分配内存池 
#endif

}tagListCtrl; 

/*================================================================================
 * 对外声明函数
 *================================================================================*/
extern UINT32 DataListBuild(tagListCtrl *ptListCtrl, tagListNode *pRam, UINT32 dwBlk);
extern UINT32 DataListDestory(tagListCtrl *ptListCtrl);

extern UINT32 DataListAdd(tagListCtrl *ptListCtrl, void *pData);
extern UINT32 DataListDel(tagListCtrl *ptListCtrl, void *pData);
extern UINT32 DataListCut(tagListCtrl *ptListCtrl, void *pData);

extern tagListNode* DataListSrch(tagListCtrl *ptListCtrl, void *pData);
/*================================================================================*/


#ifdef __cplusplus
}
#endif

#endif
