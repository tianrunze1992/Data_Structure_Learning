/*================================================================================
 * �ļ�����: �ڴ�� 
 * �ļ��汾: V1.00
 * ������Ա: wangrq
 * ����ʱ��:
 * �汾�޶�:
 * �޶���Ա:
 *================================================================================*/

#ifndef _DATAPOOL_H_
#define _DATAPOOL_H_


//#include "Resource.h"
//#include "InstCell.h"
#include "Macro.h"

#ifdef __cplusplus
extern "C" {
#endif

/*================================================================================*/

// �ڴ�ؿ��ƽṹ��
typedef struct
{
    void            *pPool;                 // �ڴ��ָ��
    void            *pFree;                 // ���п�ָ��
 
    UINT32          dwNum;                  // ���ݿ����
    UINT32          dwSize;                 // ���ݿ鳤��
                 
    UINT32          dwEmpty;                // �������ݿ����
    UINT32          dwUsed;                 // ��ǰʹ�ÿ����
    UINT32          dwMax;                  // ���ʹ�ÿ����

}tagPoolCtrl;

/*================================================================================
 * ������������
 *================================================================================*/
extern UINT32 DataPoolCreat(tagPoolCtrl *ptPoolCtrl, void *pPool, UINT32 dwNum, UINT32 dwSize);
extern void * DataPoolGet(tagPoolCtrl *ptPoolCtrl, UINT32 *pdwErr);
extern UINT32 DataPoolPut(tagPoolCtrl *ptPoolCtrl, void *pData);

extern void DataPoolShow(tagPoolCtrl *ptPoolCtrl);
extern void DataPoolInfo(tagPoolCtrl *ptPoolCtrl);
/*================================================================================*/


#ifdef __cplusplus
}
#endif

#endif
