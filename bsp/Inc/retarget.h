#ifndef _RETARGET_H__
#define _RETARGET_H__

#ifdef __cplusplus
extern "C" {
#endif

#ifdef STM32F446xx
#include "stm32f4xx_hal.h"
#elif STM32F411xE
#include "stm32f4xx_hal.h"
#endif

#include <sys/stat.h>
#include <stdio.h>

//debug 开关
#define BON_DEBUG_ON    1

//c语言 预编译器 (#)运算符、(##)粘合剂、(...)变参宏
#define BON_INFO(fmt,arg...)        printf("<<-INFO->> "#fmt"\r\n",##arg)
#define BON_ERROR(fmt,arg...)       printf("<<-ERROR->> "#fmt"\r\n",##arg)
#define BON_DEBUG(fmt,arg...)   do{\
                                if(BON_DEBUG_ON)\
                                printf("<<-DEBUG->> [%s: %d]"#fmt"\r\n",__func__,__LINE__, ##arg);\
                                }while(0)

void RetargetInit(UART_HandleTypeDef *huart);
int _isatty(int fd);
int _write(int fd, char *ptr, int len);
int _close(int fd);
int _lseek(int fd, int ptr, int dir);
int _read(int fd, char *ptr, int len);
int _fstat(int fd, struct stat *st);

#ifdef __cplusplus
}
#endif

#endif