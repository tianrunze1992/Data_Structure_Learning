#include <stdio.h>


#include "DataPool.h"
#include "Random.h" 

#define CN_POOL_BLK_NUM     ( 10 )
#define CN_POOL_BLK_SIZE    ( 16 )


static UINT32   g_Pool[CN_POOL_BLK_NUM * CN_POOL_BLK_SIZE];


UINT32 DataPoolGetRand(void)
{
	static  UINT32	dwSetSeed, dwCnt; 
	static	UINT32	dwSetFlag[CN_POOL_BLK_NUM];
	UINT32	dwLoop, dwRandom;
	
	if(!dwSetSeed)
		M_SetRandomSeed();
	
	while(dwCnt<CN_POOL_BLK_NUM)
	{
		dwRandom = M_GetRandom(CN_POOL_BLK_NUM);
		if(!dwSetFlag[dwRandom])
		{
			dwSetFlag[dwRandom] = 1;
			dwCnt++;
			break;
		}
	}

	return dwRandom;
}


int DataPoolDemo(void)
{
    tagPoolCtrl     tPoolCtrl;
    UINT32          dwErrInfo=0, **ppdwData, *pdw[CN_POOL_BLK_NUM];
    UINT32          dwLoop, dwRand;    
    
    UINT32			*pdwDbg;
    
    dwErrInfo = DataPoolCreat(&tPoolCtrl, g_Pool, CN_POOL_BLK_NUM, CN_POOL_BLK_SIZE);
	
	if(dwErrInfo)
	{
		printf("DataPoolCreat: ErrInfo=%d\n",dwErrInfo);
		
		return;
	}


    DataPoolInfo(&tPoolCtrl);
	DataPoolShow(&tPoolCtrl);

    for(dwLoop=0;dwLoop<10;dwLoop++)
    {
		ppdwData = &pdw[dwLoop];
    	*ppdwData = (UINT32 * )DataPoolGet(&tPoolCtrl, &dwErrInfo);
    	if(!*ppdwData||dwErrInfo)
    	{
    	    printf("DataPoolGet: pData=%p,ErrInfo=%d\n",*ppdwData,dwErrInfo);
    	}
    	**ppdwData = dwLoop + 1;        
 
 		DataPoolInfo(&tPoolCtrl);    
        DataPoolShow(&tPoolCtrl);
    }

//--test for condition
//    	pdwDbg = (UINT32 * )DataPoolGet(&tPoolCtrl, &dwErrInfo);
//    	if(!pdwDbg||dwErrInfo)
//    	{
//    	    printf("DataPoolGet: pData=%p,ErrInfo=%d\n",pdwDbg,dwErrInfo);
//    	}


    for(dwLoop=0;dwLoop<10;dwLoop++)
    {
		ppdwData = &pdw[DataPoolGetRand()];
		
		dwErrInfo = DataPoolPut(&tPoolCtrl, *ppdwData);
		
    	if(dwErrInfo)
    	{
    	    printf("DataPoolPut: pData=%p,ErrInfo=%d\n",*ppdwData,dwErrInfo);
    	}
        DataPoolInfo(&tPoolCtrl);
        DataPoolShow(&tPoolCtrl);
    }
	
//--test for condition
//		dwErrInfo = DataPoolPut(&tPoolCtrl, *ppdwData);
//		
//    	if(dwErrInfo)
//    	{
//    	    printf("DataPoolPut: pData=%p,ErrInfo=%d\n",*ppdwData,dwErrInfo);
//    	}



    for(dwLoop=0;dwLoop<5;dwLoop++)
    {
		ppdwData = &pdw[dwLoop];
    	*ppdwData = (UINT32 * )DataPoolGet(&tPoolCtrl, &dwErrInfo);
    	if(!*ppdwData||dwErrInfo)
    	{
    	    printf("DataPoolGet: pData=%p,ErrInfo=%d\n",*ppdwData,dwErrInfo);
    	}
    	**ppdwData = dwLoop + 1;        
 
 		DataPoolInfo(&tPoolCtrl);    
        DataPoolShow(&tPoolCtrl);
    }

	
	return 0;
}
