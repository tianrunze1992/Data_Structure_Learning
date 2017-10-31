/*================================================================================
 * �ļ�����: �ڴ�� 
 * �ļ��汾: V1.00
 * ������Ա: wangrq
 * ����ʱ��:
 * �汾�޶�:
 * �޶���Ա:
 *================================================================================*/
#include <stdio.h>
#include "DataPool.h"

//===========================================================
// ��������: �ڴ����Ϣ
//===========================================================
BOOL DataPoolIsFull(tagPoolCtrl *ptPoolCtrl)
{
    return (ptPoolCtrl->dwMax >= ptPoolCtrl->dwNum);    
}

//===========================================================
// ��������: �ڴ����Ϣ
//===========================================================
void DataPoolInfo(tagPoolCtrl *ptPoolCtrl)
{

    printf("DataPoolInfo:\n");
    printf("Addr=%p,Free=%p,Num=%d,Size=%d\nEmpty=%d,Used=%d,Max=%d\n\n",
                                                ptPoolCtrl->pPool  ,\
                                                ptPoolCtrl->pFree  ,\
                                                ptPoolCtrl->dwNum  ,\
                                                ptPoolCtrl->dwSize ,\
                                                ptPoolCtrl->dwEmpty,\
                                                ptPoolCtrl->dwUsed ,\
                                                ptPoolCtrl->dwMax);

    return;    
}

//===========================================================
// ��������: �ڴ������
//===========================================================
void DataPoolShow(tagPoolCtrl *ptPoolCtrl)
{
    UINT8           *pbyPool,*pbyData;
    UINT32          dwNum, dwSize, dwLen;

    // ָ���ʼ��
    pbyPool  = (UINT8 *)ptPoolCtrl->pPool;
    dwLen   = ptPoolCtrl->dwNum * ptPoolCtrl->dwSize;
    pbyData = &pbyPool[dwLen - 1];

    printf("Pool:Top\n");
    dwNum  = ptPoolCtrl->dwNum   ;
    while(dwNum)
    {
        printf("Pool[%04d]:",dwNum-1);
        dwSize = ptPoolCtrl->dwSize  ;   
        while(dwSize)
        {
            printf("%02x ",*pbyData);
            
            dwSize--;      
			  
            if(!dwSize)
				printf("<--Addr:0x%p\n",pbyData);   
            
            pbyData--;
        }
        
        dwNum--;     
    }
    
    printf("Pool:Bottom\n\n\n");


    return;    
}

//===========================================================
// ��������: �ڴ�س�ʼ��
//===========================================================
UINT32 DataPoolCreat(tagPoolCtrl *ptPoolCtrl, void *pPool, UINT32 dwNum, UINT32 dwSize)
{
    void        **ppNode;
    UINT8       *pNext;
    UINT32      dwLoop;

    
    // ��� 
	if(dwNum < 2)   // ����ֻ��1��,�����Խ����ڴ��
	{
	    printf("DataPoolCreat:Num Err\n");
	    return 1;
	}
	if(dwSize < sizeof(void *)) // ����С��һ��ָ��Ĵ�С....�����ף����ݳ���Ϊʲô��ָ���sizeof���Ƚ�
	{
	    printf("DataPoolCreat:Size Err\n");
	    return 2;
	}
	if(!pPool)                  // �ڴ����׵�ַ��Ϊ��
	{
	    printf("DataPoolCreat:Pool Err\n");
	    return 3;
	}
    if (((UINT32)pPool & (sizeof(void *) - 1)))   // ����⣬���ƺ����ڴ�����й�ϵ
	{
	    // Trick ��So elegant ��
	    printf("DataPoolCreat:Alignment Err\n");
	    return 4;
	}

    ppNode = (void **)pPool;
    pNext  = (UINT8 *)pPool + dwSize;
    
    for(dwLoop=1;dwLoop<dwNum;dwLoop++)
    {
        // ������һ�����ݿ�ĵ�ַ
        *ppNode = (void *)pNext;
        // ����ָ�����ݿ��ָ��
        ppNode = (void **)pNext;
        // ������һ�����ݿ�ĵ�ַ
        pNext += dwSize;
        
    }

	// �ڴ�ؽṹ
    ptPoolCtrl->pPool  = pPool    ;                 // �ڴ��ָ��
    ptPoolCtrl->pFree  = pPool    ;                 // ���п�ָ��
    ptPoolCtrl->dwNum  = dwNum   ;                  // ���ݸ���
    ptPoolCtrl->dwSize = dwSize  ;                  // ���ݳ���

    // �ڴ����Ϣ
    ptPoolCtrl->dwEmpty= dwNum   ;                  // �������ݸ���
    ptPoolCtrl->dwUsed = 0       ;                  // ��ǰд�����
    ptPoolCtrl->dwMax  = 0       ;                  // ���д�����  

    return 0;    
}

//===========================================================
// ��������: �ڴ�ػ�ȡ���ݿ�ָ��
//===========================================================
void * DataPoolGet(tagPoolCtrl *ptPoolCtrl, UINT32 *pdwErr)
{
    void    *pData = NULL;
    

    if(!ptPoolCtrl)
    {
        *pdwErr = 1;         
    }
    else if(!ptPoolCtrl->dwEmpty)
    {
        *pdwErr = 2;    
    }
    else
    {
        pData = ptPoolCtrl->pFree;
    
        ptPoolCtrl->pFree = *((void **)pData);// pFreeָ������һ����������
                
        ptPoolCtrl->dwUsed++;
        ptPoolCtrl->dwEmpty--;
            
        if(ptPoolCtrl->dwMax < ptPoolCtrl->dwUsed)
        {
            ptPoolCtrl->dwMax = ptPoolCtrl->dwUsed;           
        }
    }

    return pData;
}

//===========================================================
// ��������: �ڴ�طŻ����ݿ�ָ��
//===========================================================
UINT32 DataPoolPut(tagPoolCtrl *ptPoolCtrl, void *pData)
{
    UINT32  dwRt = 0;


    if(!ptPoolCtrl)
    {
        dwRt = 1;         
    }
    else if(!pData)
    {
        dwRt = 2;    
    }
    else if(!ptPoolCtrl->dwUsed)
    {      
        dwRt = 3;   
    }
    else
    {        
        *((void **)pData) = ptPoolCtrl->pFree;
        
        ptPoolCtrl->pFree = pData;                
        ptPoolCtrl->dwUsed--;
        ptPoolCtrl->dwEmpty++;
        
    }

    return dwRt;
}
