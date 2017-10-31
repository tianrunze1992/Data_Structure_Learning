/*================================================================================
 * 文件描述: 数据队列 
 * 文件版本: V1.00
 * 开发人员: wangrq
 * 定版时间:
 * 版本修订:
 * 修订人员:
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

//#define CN_NUM_CAN_DATA                 ( 2 )      // CAN数据区个数（1个数据区=1个接收缓存区+1个发送缓存区）

//#define CN_LEN_DATA_FRAME               ( 13  )    // 每个数据帧的长度
//#define CN_NUM_BUF_RECV                 ( 100 )    // 接收缓存区的帧数
//#define CN_NUM_BUF_SEND                 ( 30  )    // 发送缓存区的帧数

// 环形队列控制结构体
typedef struct
{
    void            *pQue;                  // 队列指针
    UINT32          dwNum;                  // 数据个数
    UINT32          dwSize;                 // 数据长度
                                            
    UINT32          dwWr;                   // 数据写入
    UINT32          dwRd;                   // 数据读出
                 
    UINT32          dwEmpty;                // 空闲数据个数
    UINT32          dwUsed;                 // 当前写入个数
    UINT32          dwMax;                  // 最大写入个数      

}tagQueCtrl;                                
                                            
              
/*================================================================================
 * 对外声明函数
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
