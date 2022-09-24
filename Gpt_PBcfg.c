 /******************************************************************************
 * Module: Gpt
 *
 * File Name: Gpt_PBcfg.c
 *
 * Description: Source file for TM4C123GH6PM Microcontroller - Gpt Driver.
 *
 ******************************************************************************/

/*
 * Module Version 1.0.0
 */
#define GPT_PBCFG_SW_MAJOR_VERSION           (1U)
#define GPT_PBCFG_SW_MINOR_VERSION           (0U)
#define GPT_PBCFG_SW_PATCH_VERSION           (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define GPT_PBCFG_AR_RELEASE_MAJOR_VERSION   (4U)
#define GPT_PBCFG_AR_RELEASE_MINOR_VERSION   (0U)
#define GPT_PBCFG_AR_RELEASE_PATCH_VERSION   (3U)

#include "Gpt.h"

/* AUTOSAR Version checking between Gpt_PBcfg.c and Gpt.h files */
#if ((GPT_PBCFG_AR_RELEASE_MAJOR_VERSION != GPT_AR_RELEASE_MAJOR_VERSION)\
 ||  (GPT_PBCFG_AR_RELEASE_MINOR_VERSION != GPT_AR_RELEASE_MINOR_VERSION)\
 ||  (GPT_PBCFG_AR_RELEASE_PATCH_VERSION != GPT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of PBcfg.c does not match the expected version"
#endif

/* Software Version checking between Gpt_PBcfg.c and Gpt.h files */
#if ((GPT_PBCFG_SW_MAJOR_VERSION != GPT_SW_MAJOR_VERSION)\
 ||  (GPT_PBCFG_SW_MINOR_VERSION != GPT_SW_MINOR_VERSION)\
 ||  (GPT_PBCFG_SW_PATCH_VERSION != GPT_SW_PATCH_VERSION))
  #error "The SW version of PBcfg.c does not match the expected version"
#endif

/* PB structure used with Gpt_Init API */
const Gpt_ConfigType Gpt_Configuration = {
  GPT_TIMER0A, Channel_A, Periodic, GPT_MODE_NORMAL, TIMER_INDIVIDUAL_MODE, 1
};