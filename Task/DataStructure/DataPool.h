/*================================================================================
 * 文件描述: 内存池 
 * 文件版本: V1.00
 * 开发人员: wangrq
 * 定版时间:
 * 版本修订:
 * 修订人员:
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

// 内存池控制结构体
typedef struct
{
    void            *pPool;                 // 内存池指针
    void            *pFree;                 // 空闲块指针
 
    UINT32          dwNum;                  // 数据块个数
    UINT32          dwSize;                 // 数据块长度
                 
    UINT32          dwEmpty;                // 空闲数据块个数
    UINT32          dwUsed;                 // 当前使用块个数
    UINT32          dwMax;                  // 最大使用块个数

}tagPoolCtrl;

/*================================================================================
 * 对外声明函数
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
