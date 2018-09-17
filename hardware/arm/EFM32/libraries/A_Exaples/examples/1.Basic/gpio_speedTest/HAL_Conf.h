/*   ARDUINO HAL special config file, overriden default define 
 *   config arduino/hal/os/priority/......
 *    ARDUINO HAL 项目配置文件， 改写 系统、库、缺省定义，配置改变系统的缺省参数/中断优先级等
 *   !!! Don't rename this file, 请不要改变文件名和扩展名!!!
 *  
 *   ---------------------------------------------------------------------------------------
 *    for FreeRTOS search FreeRTOSConfig.h:
 *      1 this sketch project path if has
 *      2 {variant}/config/   if has
 *      3 FreeRTOS/default
 *      This file defined can overload above.
 *   
 *    2017.12 by huaweiwx@sina.com
 */
 
#ifndef __HALSPECELCONFIG_H__
#define __HALSPECELCONFIG_H__

#define  USE_ARDUINOSTREAMING 1
#define  USE_BITBAND 1

/*select Release or Release(exceptions) from menu should be closed the DEBUG auto*/
#ifdef DEBUG_EFM_USER
/* ------------------------------------------------------------------
 * set USE_ERRORBLINK 1 enable blink a err code for debug 
 * blink err code:
 *   HardFault       31
 *   MemManage fault 32
 *   BusFault        33
 *   UsageFault      34
 *   MallocFailed    22 (freertos if set configUSE_MALLOC_FAILED_HOOK 1)
 *   StackOverflow   23 (freertos if configCHECK_FOR_STACK_OVERFLOW 1)
 *   others          __LINE__   (err line from assert_failed or _Error_Handler )
 */
#define USE_ERRORBLINK 1
#endif /* DEBUG_EFM_USER */

//---------------------------------------- for FreeRTOS overload ---------------------------------------------------------
#endif  /*__HALSPECELCONFIG_H__*/
