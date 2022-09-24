 /******************************************************************************
 *
 * Module: Gpt
 *
 * File Name: Gpt.h
 *
 * Description: Header file for TM4C123GH6PM Microcontroller - Gpt Driver
 *
 ******************************************************************************/
#ifndef GPT_H
#define GPT_H

/* Id for the company in the AUTOSAR
 * assuming random Id .. */
#define GPT_VENDOR_ID    (1000U)

/* Gpt Module Id */
#define GPT_MODULE_ID    (100U)

/* Gpt Instance Id */
#define GPT_INSTANCE_ID  (0U)

/*
 * Module Version 1.0.0
 */
#define GPT_SW_MAJOR_VERSION           (1U)
#define GPT_SW_MINOR_VERSION           (0U)
#define GPT_SW_PATCH_VERSION           (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define GPT_AR_RELEASE_MAJOR_VERSION   (4U)
#define GPT_AR_RELEASE_MINOR_VERSION   (0U)
#define GPT_AR_RELEASE_PATCH_VERSION   (3U)

/*
 * Macros for Gpt Status
 */
#define GPT_INITIALIZED                (1U)
#define GPT_NOT_INITIALIZED            (0U)

/* Standard AUTOSAR types */
#include "Std_Types.h"

/* AUTOSAR checking between Std Types and Gpt Modules */
#if ((STD_TYPES_AR_RELEASE_MAJOR_VERSION != GPT_AR_RELEASE_MAJOR_VERSION)\
 ||  (STD_TYPES_AR_RELEASE_MINOR_VERSION != GPT_AR_RELEASE_MINOR_VERSION)\
 ||  (STD_TYPES_AR_RELEASE_PATCH_VERSION != GPT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Std_Types.h does not match the expected version"
#endif

/* Gpt Pre-Compile Configuration Header file */
#include "Gpt_Cfg.h"

/* AUTOSAR Version checking between Gpt_Cfg.h and Gpt.h files */
#if ((GPT_CFG_AR_RELEASE_MAJOR_VERSION != GPT_AR_RELEASE_MAJOR_VERSION)\
 ||  (GPT_CFG_AR_RELEASE_MINOR_VERSION != GPT_AR_RELEASE_MINOR_VERSION)\
 ||  (GPT_CFG_AR_RELEASE_PATCH_VERSION != GPT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Gpt_Cfg.h does not match the expected version"
#endif

/* Software Version checking between Gpt_Cfg.h and Gpt.h files */
#if ((GPT_CFG_SW_MAJOR_VERSION != GPT_SW_MAJOR_VERSION)\
 ||  (GPT_CFG_SW_MINOR_VERSION != GPT_SW_MINOR_VERSION)\
 ||  (GPT_CFG_SW_PATCH_VERSION != GPT_SW_PATCH_VERSION))
  #error "The SW version of Gpt_Cfg.h does not match the expected version"
#endif

/* Non AUTOSAR files */
#include "Common_Macros.h"

/******************************************************************************
 *                      API Service Id Macros                                 *
******************************************************************************/
#define GPT_GET_VERSION_INFO_SID        (uint8)0x00
#define GPT_INIT_SID                    (uint8)0x01
#define GPT_DEINIT_SID                  (uint8)0x02
#define GPT_GET_TIME_ELAPSED_SID        (uint8)0x03
#define GPT_GET_TIME_REMAINING_SID      (uint8)0x04 
#define GPT_START_TIMER_SID             (uint8)0x05
#define GPT_STOP_TIMER_SID              (uint8)0x06
#define GPT_ENABLE_NOTIFICATION_SID     (uint8)0x07
#define GPT_DISABLE_NOTIFICATION_SID    (uint8)0x08
#define GPT_SET_MODE_SID                (uint8)0x09
#define GPT_DISABLE_WAKEUP_SID          (uint8)0x0a
#define GPT_ENABLE_WAKEUP_SID           (uint8)0x0b  
#define GPT_CHECK_WAKEUP_SID            (uint8)0x0c  

/*******************************************************************************
 *                              Module Data Types                              *
*******************************************************************************/
/* Numeric ID of a GPT channel */
typedef uint8 Gpt_ChannelType;

/* Type for reading and setting the timer values (in number of ticks). */
typedef uint8 Gpt_ValueType;

/* Enum to allow the selection of different power modes. */
typedef enum{
  GPT_MODE_NORMAL, GPT_MODE_SLEEP
}Gpt_ModeType;

/* Enum for timer running mode */
typedef enum{
  One_Shot=0x1, Periodic=0x2
}Gpt_RunningModeType;

/* Enum for timer channel width [16, 32 or 64 bits] */
typedef enum{
  TIMER_INDIVIDUAL_MODE=0x4, TIMER_CONCATENATED_MODE=0x0
}Gpt_TimerType;

typedef enum{
  Channel_A=0, Channel_B=7, CONCATENATED=0
}Gpt_TimerChannel;

/* This is the type of the data structure including the configuration set required for
initializing the GPT timer unit[channel].
  1. Timer Id
  2. Running mode [one-shot or periodic]
  3. Power mode [normal or sleep mode]
  4. Timer type [16, 32 or 64 bits]
  // Timer value are set by Gpt_StartTimer api
  // Notification [interrupt] are disabled by default, and enabled by Gpt_EnableNotification api
*/
typedef struct
{
  Gpt_ChannelType channel_id;
  Gpt_TimerChannel timer_channel;
  Gpt_RunningModeType running_mode;
  Gpt_ModeType power_mode;
  Gpt_TimerType timer_type;

}Gpt_ConfigChannel;

/* Type of the external data structure containing the initialization data for this module. */
typedef struct 
{
  Gpt_ConfigChannel timers[GPT_NUMBER_OF_TIMERS];
}Gpt_ConfigType;


/*******************************************************************************
 *                      Function Prototypes                                    *
*******************************************************************************/
/* Returns the version information of this module. */
void Gpt_GetVersionInfo(Std_VersionInfoType* VersionInfoPtr); 

/* Initializes the hardware timer module. */
void Gpt_Init(const Gpt_ConfigType* ConfigPtr);

/* Deinitializes all hardware timer channels. */
void Gpt_DeInit(void);

/* Returns the time already elapsed. */
Gpt_ValueType Gpt_GetTimeElapsed(Gpt_ChannelType Channel);

/* Returns the time remaining until the target time is reached. */
Gpt_ValueType Gpt_GetTimeRemaining(Gpt_ChannelType Channel);

/* Starts a timer channel. */
void Gpt_StartTimer( Gpt_ChannelType Channel,Gpt_ValueType Value);

/* Stops a timer channel. */
void Gpt_StopTimer(Gpt_ChannelType Channel);

/* Enables the interrupt notification for a channel (relevant in normal mode) */
void Gpt_EnableNotification(Gpt_ChannelType Channel);

/* Disables the interrupt notification for a channel (relevant in normal mode) */
void Gpt_DisableNotification(Gpt_ChannelType Channel);

/* Sets the operation mode of the GPT. */
void Gpt_SetMode(Gpt_ModeType Mode);

/* Disables the wakeup interrupt of a channel (relevant in sleep mode). */
void Gpt_DisableWakeup(Gpt_ChannelType Channel);

/* Enables the wakeup interrupt of a channel (relevant in sleep mode). */
void Gpt_EnableWakeup(Gpt_ChannelType Channel);

/* NOT IMPLEMENTED */
//void Gpt_CheckWakeup(EcuM_WakeupSourceType WakeupSource);


/*******************************************************************************
 *                       External Variables                                    *
*******************************************************************************/
/* Extern PB structures to be used by Gpt and other modules */
extern const Gpt_ConfigType Gpt_Configuration;


/*******************************************************************************
 *                       Timers IDs                                           *
*******************************************************************************/
#define GPT_TIMER0_ID       (uint8)0
#define GPT_TIMER1_ID       (uint8)1
#define GPT_TIMER2_ID       (uint8)2
#define GPT_TIMER3_ID       (uint8)3

#define GPT_WTIMER0_ID       (uint8)0
#define GPT_WTIMER1_ID       (uint8)1
#define GPT_WTIMER2_ID       (uint8)2
#define GPT_WTIMER3_ID       (uint8)3
#define GPT_WTIMER4_ID       (uint8)4
#define GPT_WTIMER5_ID       (uint8)5


/*******************************************************************************
 *                      GPT Channel Types                                    *
*******************************************************************************/

/* 16/32-bit timers */
#define GPT_TIMER0A        (uint8)0
#define GPT_TIMER0B        (uint8)1
#define GPT_TIMER1A        (uint8)2
#define GPT_TIMER1B        (uint8)3
#define GPT_TIMER2A        (uint8)4
#define GPT_TIMER2B        (uint8)5
#define GPT_TIMER3A        (uint8)6
#define GPT_TIMER3B        (uint8)7

/* 32/64-bit timers */
#define GPT_WIDE_TIMER0A        (uint8)0
#define GPT_WIDE_TIMER0B        (uint8)1
#define GPT_WIDE_TIMER1A        (uint8)2
#define GPT_WIDE_TIMER1B        (uint8)3
#define GPT_WIDE_TIMER2A        (uint8)4
#define GPT_WIDE_TIMER2B        (uint8)5
#define GPT_WIDE_TIMER3A        (uint8)6
#define GPT_WIDE_TIMER3B        (uint8)7
#define GPT_WIDE_TIMER4A        (uint8)8
#define GPT_WIDE_TIMER4B        (uint8)9
#define GPT_WIDE_TIMER5A        (uint8)10
#define GPT_WIDE_TIMER5B        (uint8)11

/* SysTick Timer */
#define SYSTICK_TIMER           (uint8)12

#endif /* GPT_H */