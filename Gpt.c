#include "Gpt.h"
#include "Gpt_Regs.h"
#include "Common_Macros.h"


STATIC const Gpt_ConfigChannel * Gpt_GptChannels = NULL_PTR;
STATIC uint8 Gpt_Status = GPT_NOT_INITIALIZED;

/*
Service ID[hex]: 0x00
Sync/Async: Synchronous
Reentrancy: Reentrant
Parameters (in): None
Parameters (inout):None
Parameters (out): VersionInfoPtr Pointer to where to store the version information of this module.
Return value: None
Description: Returns the version information of this module.
*/
void Gpt_GetVersionInfo(Std_VersionInfoType* VersionInfoPtr){
    if (NULL_PTR == VersionInfoPtr){
        return;
    }
    /* Copy the vendor Id */
    VersionInfoPtr->vendorID = (uint16)GPT_VENDOR_ID;
    /* Copy the module Id */
    VersionInfoPtr->moduleID = (uint16)GPT_MODULE_ID;
    /* Copy Software Major Version */
    VersionInfoPtr->sw_major_version = (uint8)GPT_SW_MAJOR_VERSION;
    /* Copy Software Minor Version */
    VersionInfoPtr->sw_minor_version = (uint8)GPT_SW_MINOR_VERSION;
    /* Copy Software Patch Version */
    VersionInfoPtr->sw_patch_version = (uint8)GPT_SW_PATCH_VERSION;
}

/*
Service ID[hex]: 0x01
Sync/Async: Synchronous
Reentrancy: Non Reentrant
Parameters (in): ConfigPtr Pointer to a selected configuration structure
Parameters (inout): None
Parameters (out): None
Return value: None
Description: Initializes the hardware timer module. 
*/
void Gpt_Init(const Gpt_ConfigType* ConfigPtr){
    if (NULL_PTR == ConfigPtr){
        return;
    }
    
}

/*
Service ID[hex]: 0x02
Sync/Async: Synchronous
Reentrancy: Non Reentrant
Parameters (in): None
Parameters (inout):None
Parameters (out): None
Return value: None
Description: Deinitializes all hardware timer channels. 
*/
void Gpt_DeInit(void){

}

/*
Service ID[hex]: 0x03
Sync/Async: Synchronous
Reentrancy: Reentrant
Parameters (in): Channel Numeric identifier of the GPT channel.
Parameters (inout): None
Parameters (out): None
Return value: Gpt_ValueType Elapsed timer value (in number of ticks)
Description: Returns the time already elapsed.
*/
Gpt_ValueType Gpt_GetTimeElapsed(Gpt_ChannelType Channel){

}

/*
Service ID[hex]: 0x04
Sync/Async: Synchronous
Reentrancy: Reentrant
Parameters (in): Channel Numeric identifier of the GPT channel.
Parameters (inout): None
Parameters (out): None
Return value: Gpt_ValueType Remaining timer value (in number of ticks)
Description: Returns the time remaining until the target time is reached. 
*/
Gpt_ValueType Gpt_GetTimeRemaining(Gpt_ChannelType Channel){

}

/*
Service ID[hex]: 0x05
Sync/Async: Synchronous
Reentrancy: Reentrant
Parameters (in): Channel - Numeric identifier of the GPT channel
                Value - Target time in number of ticks. 
Parameters (inout):None
Parameters (out): None
Return value: None
Description: Starts a timer channel. 
*/
void Gpt_StartTimer( Gpt_ChannelType Channel,Gpt_ValueType Value){

}

/*
Service ID[hex]: 0x06
Sync/Async: Synchronous
Reentrancy: Reentrant
Parameters (in): Channel Numeric identifier of the GPT channel.
Parameters(inout):None
Parameters (out): None
Return value: None
Description: Stops a timer channel. 
*/
void Gpt_StopTimer(Gpt_ChannelType Channel){

}

/*
Service ID[hex]: 0x07
Sync/Async: Synchronous
Reentrancy: Reentrant
Parameters (in): Channel Numeric identifier of the GPT channel.
Parameters (inout):None
Parameters (out): None
Return value: None
Description: Enables the interrupt notification for a channel (relevant in normal mode). 
*/
void Gpt_EnableNotification(Gpt_ChannelType Channel){

}

/*
Service ID[hex]: 0x08
Sync/Async: Synchronous
Reentrancy: Reentrant
Parameters (in): Channel Numeric identifier of the GPT channel.
Parameters(inout):None
Parameters (out): None
Return value: None
Description: Disables the interrupt notification for a channel (relevant in normal mode)
*/
void Gpt_DisableNotification(Gpt_ChannelType Channel){

}

/*
Service ID[hex]: 0x09
Sync/Async: Synchronous
Reentrancy: Non Reentrant
Parameters (in): Mode :
                        - GPT_MODE_NORMAL: Normal operation mode of the GPT driver.
                        - GPT_MODE_SLEEP: Sleep mode of the GPT driver (wakeup capable).
                        - See also Gpt_ModeType. 
Parameters (inout):None
Parameters (out): None
Return value: None
Description: Sets the operation mode of the GPT. 
*/
void Gpt_SetMode(Gpt_ModeType Mode){

}

/*
Service ID[hex]: 0x0a
Sync/Async: Synchronous
Reentrancy: Reentrant
Parameters (in): Channel Numeric identifier of the GPT channel.
Parameters (inout):None
Parameters (out): None
Return value: None
Description: Disables the wakeup interrupt of a channel (relevant in sleep mode)
*/
void Gpt_DisableWakeup(Gpt_ChannelType Channel){

}

/*
Service ID[hex]: 0x0b
Sync/Async: Synchronous
Reentrancy: Reentrant
Parameters (in): Channel Numeric identifier of the GPT channel.
Parameters (inout):None
Parameters (out): None
Return value: None
Description: Enables the wakeup interrupt of a channel (relevant in sleep mode). 
*/
void Gpt_EnableWakeup(Gpt_ChannelType Channel){
    
}