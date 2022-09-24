#include "Gpt.h"
#include "Gpt_Regs.h"
#include "Common_Macros.h"


STATIC const Gpt_ConfigType * Gpt_GptChannels = NULL_PTR;
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
