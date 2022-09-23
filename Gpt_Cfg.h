 /******************************************************************************
 *
 * Module: GPT
 *
 * File Name: GPT_Cfg.h
 *
 * Description: Pre-Compile Configuration Header file for TM4C123GH6PM Microcontroller - GPT Driver
 *
 ******************************************************************************/

#ifndef GPT_CFG_H
#define GPT_CFG_H

/*
 * Module Version 1.0.0
 */
#define GPT_CFG_SW_MAJOR_VERSION              (1U)
#define GPT_CFG_SW_MINOR_VERSION              (0U)
#define GPT_CFG_SW_PATCH_VERSION              (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define GPT_CFG_AR_RELEASE_MAJOR_VERSION     (4U)
#define GPT_CFG_AR_RELEASE_MINOR_VERSION     (0U)
#define GPT_CFG_AR_RELEASE_PATCH_VERSION     (3U)


/*******************************************************************************
*                              Pre-Compile configurations                      *
*******************************************************************************/
/* Pre-compile option for report wakeup source */
#define GPT_REPORT_WAKEUP_SOURCE                (STD_ON)

/* Pre-compile option for deInit api */
#define GPT_DEINIT_API                          (STD_ON)

/* Pre-compile option for enable/disable notifications api */
#define GPT_ENABLE_DISABLE_NOTIFICATION_API     (STD_ON)

/* Pre-compile option for Gpt_GetTimeElapsed api */
#define GPT_TIME_ELAPSED_API                    (STD_ON)

/* Pre-compile option for Gpt_GetTimeRemaining api */
#define GPT_TIME_REMAINING_API                  (STD_ON)

/* Pre-compile option for Gpt_GetVersionInfo api */
#define GPT_VERSION_INFO_API                    (STD_ON)

/* Pre-compile option for Gpt_SetMode, Gpt_DisableWakeup, Gpt_EnableWakeup APIs */
#define GPT_WAKEUP_FUNCTIONALITY_API            (STD_ON)

#define GPT_NUMBER_OF_TIMERS                    (13U)

#endif /* GPT_CFG_H */
