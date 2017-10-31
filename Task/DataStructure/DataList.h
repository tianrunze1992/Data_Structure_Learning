/*================================================================================
 * �ļ�����: ��������
 * �ļ��汾: V1.00
 * ������Ա: wangrq
 * ����ʱ��:
 * �汾�޶�:
 * �޶���Ա:
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

#define CN_DATA_LIST_MODE	( CN_DATA_LOCATE_MODE )   // 0-��̬����ģʽ 1-��̬����ģʽ


// ������������ڵ�
typedef struct ListNode
{
    struct ListNode* pNext;         // ��һ���ڵ�ָ�� 

    void             *pData;        // �ڵ�����
    
}tagListNode;

// ����������ƽṹ��
typedef struct
{
    tagListNode     *pHead;         // ����ͷ��ָ��
    FUNCPTR         pfnCmp;         // ����ָ��-�ȽϽڵ����� 
    
    FUNCPTR         pfnShow;        // ����ָ��-��ʾ�ڵ�����     
    UINT32          dwNum;          // �ڵ����
#if(CN_DATA_LIST_MODE!=0)
//    tagListNode     *pRam;          // ��̬�����ڴ���ָ�� 
    UINT32			dwBlk;    	    // ��̬�����ڴ����� 
    
    tagPoolCtrl     tPoolCtrl;		// ��̬�����ڴ�� 
#endif

}tagListCtrl; 

/*================================================================================
 * ������������
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
