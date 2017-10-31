/*================================================================================
 * �ļ�����: ������������
 * �ļ��汾: V1.00
 * ������Ա: wangrq
 * ����ʱ��:
 * �汾�޶�:
 * �޶���Ա:
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

#define CN_EVC_GRP_NUM         ( 4 )                  // ��ǹ����֧�ֵ�����

#define M_CAST_UINT(pData)	   (*((UINT32*)pData))    // void* ת�� UINT32 

// ���������ڵ������/��������
enum _EVC_GRP_LIST_TRANS_TYPE_
{	
	EN_MST_LIST_ADD,     	   // ��ӷ���ڵ�--Add Master	
	EN_MST_LIST_DEL,     	   // ɾ������ڵ�--Del Master

	EN_GRP_LIST_UPGD_NONE,     // �ڲ����ڵ�--Add Grp
    EN_GRP_LIST_UPGD_LEFT,     // �ڲ���ڵ�--Add Grp
    EN_GRP_LIST_UPGD_RIGHT,    // �ڲ��ҽڵ�--Add Grp
    
   	EN_GRP_LIST_DEGD_NONE,     // δ֪�ڵ�--Del Grp
};

/*================================================================================*/
// �������������Ϣ�ṹ��
typedef struct
{  
    //--��һ����Ա��λ�ò��ɱ䶯 --need fix 
	UINT32          dwGrpNo;        // ��������� 

    tagListCtrl     tListCtrl;      // ���������ڲ�����-��¼����˳��
    tagTreeCtrl     tTreeCtrl;      // ���������ڲ�������-��¼���ʷ���
    
    tagListNode     tListRam[CN_EVC_GRP_NUM];
    tagTreeNode     tTreeRam[CN_EVC_GRP_NUM];
    
}tagGrpInfo;

// �������������Ϣ�ṹ��
typedef struct
{  
    UINT32          dwGrpNo;        // ��������ڵ��
    UINT32          dwPlugNo;       // ���������ڲ��ı仯�ڵ��
    UINT32          dwTrans;        // ���������ڲ��ı仯�ڵ㷽��
}tagGrpTrans;

/*================================================================================*/
// �ⲿ��������
/*================================================================================*/

extern void   EVC_GrpListShow(tagListCtrl* ptGrpCtrl);         // ��ʾ������������

extern UINT32 EVC_GrpListBuild(tagListCtrl* ptGrpCtrl);        // ���������������
extern UINT32 EVC_GrpListDestory(tagListCtrl* ptGrpCtrl);      // ɾ��������������
                                                                               
extern UINT32 EVC_GrpListAdd(tagListCtrl* ptGrpCtrl, UINT32 dwGrpNo);     // ����������ӽڵ�-�����GrpNode,������ڲ��ڵ�
extern UINT32 EVC_GrpListDel(tagListCtrl* ptGrpCtrl, UINT32 dwGrpNo);     // ��������ɾ���ڵ�

extern UINT32 EVC_GrpNodeUpgd(tagListCtrl* ptGrpCtrl, tagGrpTrans *ptGrpTrans);     // ��������ڵ�仯����-������ڲ��ڵ�
extern UINT32 EVC_GrpNodeDegd(tagListCtrl* ptGrpCtrl, tagGrpTrans *ptGrpTrans);     // ��������ڵ�仯����-��ɾ���ڲ��ڵ�

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
