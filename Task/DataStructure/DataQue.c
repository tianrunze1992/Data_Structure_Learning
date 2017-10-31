/*================================================================================
 * �ļ�����: ���ݶ��� 
 * �ļ��汾: V1.00
 * ������Ա: wangrq
 * ����ʱ��:
 * �汾�޶�:
 * �޶���Ա:
 *================================================================================*/
#include <stdio.h>
#include "DataQue.h"

//===========================================================
// ��������: ���ݶ�����Ϣ
//===========================================================
BOOL DataQueIsFull(tagQueCtrl *ptQueCtrl)
{
    return (ptQueCtrl->dwMax >= ptQueCtrl->dwNum);    
}

//===========================================================
// ��������: ���ݶ�����Ϣ
//===========================================================
void DataQueInfo(tagQueCtrl *ptQueCtrl)
{

    printf("DataQueInfo:\n");
    printf("Addr=%p,Num=%d,Size=%d\nWr=%d,Rd=%d,Empty=%d,Used=%d,Max=%d\n\n",
                                                ptQueCtrl->pQue   ,\
                                                ptQueCtrl->dwNum  ,\
                                                ptQueCtrl->dwSize ,\
                                                ptQueCtrl->dwWr   ,\
                                                ptQueCtrl->dwRd   ,\
                                                ptQueCtrl->dwEmpty,\
                                                ptQueCtrl->dwUsed ,\
                                                ptQueCtrl->dwMax);

    return;    
}

//===========================================================
// ��������: ���ݶ�������
//===========================================================
void DataQueShow(tagQueCtrl *ptQueCtrl)
{
    UINT8           *pbyQue,*pbyData;
    UINT32          dwNum, dwSize, dwLen;

    // ָ���ʼ��
    pbyQue  = (UINT8 *)ptQueCtrl->pQue;
    dwLen   = ptQueCtrl->dwNum * ptQueCtrl->dwSize;
    pbyData = &pbyQue[dwLen - 1];

    printf("Que:Top\n");
    dwNum  = ptQueCtrl->dwNum   ;
    while(dwNum)
    {
        printf("Que[%04d]:",dwNum-1);
        dwSize = ptQueCtrl->dwSize  ;   
        while(dwSize)
        {
            printf("%02x ",*pbyData);
            
            dwSize--;
            pbyData--;
        }
        
        dwNum--;
        
        if(dwNum==ptQueCtrl->dwRd)  printf("<--Rd ");
        if(dwNum==ptQueCtrl->dwWr)  printf("<--Wr ");       
        if(dwNum!=0)                printf("\n");
        
    }

	printf("\n");
    printf("Que:Bottom\n\n");


    return;    
}

//===========================================================
// ��������: ���ݶ��г�ʼ��
//===========================================================
UINT32 DataQueInit(tagQueCtrl *ptQueCtrl, void *pQue, UINT32 dwNum, UINT32 dwSize)
{
    // ��� 
	if(!dwNum)
	{
	    printf("DataQueInit:Err\n");
	    return 1;
	}
	
	// ���нṹ
    ptQueCtrl->pQue   = pQue    ;                  // ����ָ��
    ptQueCtrl->dwNum  = dwNum   ;                  // ���ݸ���
    ptQueCtrl->dwSize = dwSize  ;                  // ���ݳ���

    // ���п���             
    ptQueCtrl->dwWr   = 0       ;                  // ����д��
    ptQueCtrl->dwRd   = 0       ;                  // ���ݶ���

    // ������Ϣ
    ptQueCtrl->dwEmpty= dwNum   ;                  // �������ݸ���
    ptQueCtrl->dwUsed = 0       ;                  // ��ǰд�����
    ptQueCtrl->dwMax  = 0       ;                  // ���д�����  

    return 0;    
}

//===========================================================
// ��������: ���ݶ��ж���
//===========================================================
UINT32 DataQueRead(tagQueCtrl *ptQueCtrl, void *pDst, UINT32 dwRdNum)
{
    UINT8           *pbyQue, *pbyDst, *pbySrc;
    UINT32          dwCnt1=0, dwCnt2=0;
    UINT32          dwRdCnt, dwRd;
    UINT32          dwNum, dwSize;
    UINT32          dwEmpty;                // �������ݸ���
    UINT32          dwUsed;                 // ��ǰд�����

    // ָ���ʼ��
    pbyQue = (UINT8 *)ptQueCtrl->pQue    ;
    pbyDst = (UINT8 *)pDst;

    // ��ȡ���нṹ��Ϣ  
    dwRd   = ptQueCtrl->dwRd    ;
    dwNum  = ptQueCtrl->dwNum   ;
    dwSize = ptQueCtrl->dwSize  ;
    
    dwEmpty= ptQueCtrl->dwEmpty ;
    dwUsed = ptQueCtrl->dwUsed  ;

    // ���ÿռ��Ƿ�����
    dwRdCnt = (dwRdNum > dwUsed)? dwUsed : dwRdNum ;

    // �����ݸ���
    if(!dwRdCnt)
    {
        return 0;
    }
    // �����ݸ���
    if((dwRd + dwRdCnt) < dwNum)
    {
        dwCnt1 = dwRdCnt;
        pbySrc = &pbyQue[dwRd * dwSize];
        memcpy((UINT8 *)&pbyDst[0], (UINT8 *)pbySrc, dwCnt1*dwSize);

    }
    else
    {
        dwCnt1 = dwNum - dwRd;
        pbySrc = &pbyQue[dwRd * dwSize];
        memcpy((UINT8 *)&pbyDst[0], (UINT8 *)pbySrc, dwCnt1*dwSize);

        dwCnt2 = dwRdCnt - dwCnt1;
        pbySrc = &pbyQue[0];
        memcpy((UINT8 *)&pbyDst[dwCnt1*dwSize], (UINT8 *)pbySrc, dwCnt2*dwSize);

    }
    
    // �������ݶ���λ��
    dwRd   = (dwRd + dwRdCnt)% dwNum;
    // �������ÿռ����
    dwUsed = dwUsed - dwRdCnt;

    // ���нṹ��Ϣ����
    ptQueCtrl->dwRd    = dwRd;       
    ptQueCtrl->dwEmpty = dwNum - dwUsed;
    ptQueCtrl->dwUsed  = dwUsed;


    return dwRdCnt;
}

//===========================================================
// ��������: ���ݶ���д��
//===========================================================
UINT32 DataQueWrite(tagQueCtrl *ptQueCtrl, void *pSrc, UINT32 dwWrNum)
{
    UINT8           *pbyQue, *pbyDst, *pbySrc;
    UINT32          dwCnt1=0, dwCnt2=0;
    UINT32          dwWrCnt, dwWr;
    UINT32          dwNum, dwSize;
    UINT32          dwEmpty;                // �������ݸ���
    UINT32          dwUsed;                 // ��ǰд�����
    UINT32          dwMax;                  // ���д�����

    // ָ���ʼ��
    pbyQue = (UINT8 *)ptQueCtrl->pQue    ;
    pbySrc = (UINT8 *)pSrc;

    // ��ȡ���нṹ��Ϣ  
    dwWr   = ptQueCtrl->dwWr    ;
    dwNum  = ptQueCtrl->dwNum   ;
    dwSize = ptQueCtrl->dwSize  ;
    
    dwEmpty= ptQueCtrl->dwEmpty ;
    dwUsed = ptQueCtrl->dwUsed  ;
    dwMax  = ptQueCtrl->dwMax   ;
    
    // ʣ��ռ��Ƿ����
    dwWrCnt = (dwWrNum > dwEmpty)? dwEmpty : dwWrNum ;
    
    // д������
    if((dwWr + dwWrCnt) < dwNum )
    {
        dwCnt1 = dwWrCnt;
        pbyDst = &pbyQue[dwWr * dwSize];
        memcpy((UINT8 *)pbyDst, (UINT8 *)&pbySrc[0], dwCnt1*dwSize);
    }
    else
    {
        dwCnt1 = dwNum - dwWr;
        pbyDst = &pbyQue[dwWr * dwSize];
        memcpy((UINT8 *)pbyDst, (UINT8 *)&pbySrc[0], dwCnt1*dwSize);

        dwCnt2 = dwWrCnt - dwCnt1;
        pbyDst = &pbyQue[0];
        memcpy((UINT8 *)pbyDst, (UINT8 *)&pbySrc[dwCnt1*dwSize], dwCnt2*dwSize);
    }

    // ��������д��λ��
    dwWr   = (dwWr + dwWrCnt)% dwNum;
    // �������ÿռ����
    dwUsed = dwUsed + dwWrCnt;

    // ���нṹ��Ϣ����
    ptQueCtrl->dwWr    = dwWr;       
    ptQueCtrl->dwEmpty = dwNum - dwUsed;
    ptQueCtrl->dwUsed  = dwUsed;
    ptQueCtrl->dwMax   = (dwUsed > dwMax)? dwUsed: dwMax;


    return dwWrCnt;
}
