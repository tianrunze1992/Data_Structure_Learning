/*================================================================================
 * �ļ�����: ���ݶ��� 
 * �ļ��汾: V1.00
 * ������Ա: wangrq
 * ����ʱ��:
 * �汾�޶�:
 * �޶���Ա:
 *================================================================================*/

#ifndef _DATAQUE_H_
#define _DATAQUE_H_


//#include "Resource.h"
//#include "InstCell.h"
#include "Macro.h"

#ifdef __cplusplus
extern "C" {
#endif

/*================================================================================*/

//#define CN_NUM_CAN_DATA                 ( 2 )      // CAN������������1��������=1�����ջ�����+1�����ͻ�������

//#define CN_LEN_DATA_FRAME               ( 13  )    // ÿ������֡�ĳ���
//#define CN_NUM_BUF_RECV                 ( 100 )    // ���ջ�������֡��
//#define CN_NUM_BUF_SEND                 ( 30  )    // ���ͻ�������֡��

// ���ζ��п��ƽṹ��
typedef struct
{
    void            *pQue;                  // ����ָ��
    UINT32          dwNum;                  // ���ݸ���
    UINT32          dwSize;                 // ���ݳ���
                                            
    UINT32          dwWr;                   // ����д��
    UINT32          dwRd;                   // ���ݶ���
                 
    UINT32          dwEmpty;                // �������ݸ���
    UINT32          dwUsed;                 // ��ǰд�����
    UINT32          dwMax;                  // ���д�����      

}tagQueCtrl;                                
                                            
              
/*================================================================================
 * ������������
 *================================================================================*/
extern BOOL DataQueIsFull(tagQueCtrl *ptQueCtrl);
extern void DataQueInfo(tagQueCtrl *ptQueCtrl); 
extern void DataQueShow(tagQueCtrl *ptQueCtrl); 
extern UINT32 DataQueInit(tagQueCtrl *ptQueCtrl, void *pQue, UINT32 dwNum, UINT32 dwSize);
extern UINT32 DataQueRead(tagQueCtrl *ptQueCtrl, void *pDst, UINT32 dwRdNum);
extern UINT32 DataQueWrite(tagQueCtrl *ptQueCtrl, void *pSrc, UINT32 dwWrNum);
/*================================================================================*/


#ifdef __cplusplus
}
#endif

#endif
