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

/* This is the type of the data structure including the configuration set required for
initializing the GPT timer unit[channel]. */
typedef struct Gpt
{
  /* data */
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

/*******************************************************************************
 *                       External Variables                                    *
*******************************************************************************/
/* Extern PB structures to be used by Gpt and other modules */
extern const Gpt_ConfigType Gpt_Configuration;

#endif /* GPT_H */