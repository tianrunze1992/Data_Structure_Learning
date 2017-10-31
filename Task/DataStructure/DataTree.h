/*================================================================================
 * �ļ�����: ���ݶ����� 
 * �ļ��汾: V1.00
 * ������Ա: wangrq
 * ����ʱ��:
 * �汾�޶�:
 * �޶���Ա:
 *================================================================================*/

#ifndef _DATATREE_H_
#define _DATATREE_H_


//#include "Resource.h"
//#include "InstCell.h"
#include "Macro.h"
#include "DataPool.h"

#ifdef __cplusplus
extern "C" {
#endif

/*================================================================================*/

#define CN_DATA_TREE_MODE	( CN_DATA_LOCATE_MODE )    // 0-��̬����ģʽ 1-��̬����ģʽ

// �������ݶ������ڵ�
typedef struct TreeNode
{
    struct TreeNode* pRight;        // �Ҳ�ڵ�ָ�� 
    struct TreeNode* pLeft ;        // ���ڵ�ָ�� 

    void             *pData;        // �ڵ�����ָ��

}tagTreeNode;

// ���ݶ��������ƽṹ��
typedef struct
{
    tagTreeNode     *pRoot;         // ���������ڵ�ָ��
    FUNCPTR         pfnCmp;         // ����ָ��-�ȽϽڵ����� 
    
    FUNCPTR         pfnShow;        // ����ָ��-��ʾ�ڵ�����     
    UINT32          dwNum;          // �ڵ����
#if(CN_DATA_TREE_MODE!=0)
    //tagTreeNode     *pRam;          // ��̬�����ڴ���ָ�� 
    UINT32			dwBlk;    	    // ��̬�����ڴ����� 

    tagPoolCtrl     tPoolCtrl;		// ��̬�����ڴ�� 
#endif

}tagTreeCtrl; 

/*================================================================================
 * ������������
 *================================================================================*/
extern UINT32 DataTreeBuild(tagTreeCtrl *ptTreeCtrl, tagTreeNode *pRam, UINT32 dwBlk);
extern UINT32 DataTreeDestory(tagTreeCtrl *ptTreeCtrl);

extern UINT32 DataTreeAddRoot(tagTreeCtrl *ptTreeCtrl, void *pData);
extern UINT32 DataTreeAddLeft(tagTreeCtrl *ptTreeCtrl, void *pData);
extern UINT32 DataTreeAddRight(tagTreeCtrl *ptTreeCtrl, void *pData);

extern UINT32 DataTreeCutLeft(tagTreeCtrl *ptTreeCtrl, void *pData); 
extern UINT32 DataTreeCutRight(tagTreeCtrl *ptTreeCtrl, void *pData);

extern tagTreeNode* DataTreeSrch(tagTreeCtrl *ptTreeCtrl, void *pData);
extern tagTreeNode* DataTreeSrchLeft(tagTreeCtrl *ptTreeCtrl, void *pData);
extern tagTreeNode* DataTreeSrchRight(tagTreeCtrl *ptTreeCtrl, void *pData);

extern tagTreeNode* DataTreeLeftLeaf(tagTreeCtrl *ptTreeCtrl);
extern tagTreeNode* DataTreeRightLeaf(tagTreeCtrl *ptTreeCtrl);
/*================================================================================*/


#ifdef __cplusplus
}
#endif

#endif
