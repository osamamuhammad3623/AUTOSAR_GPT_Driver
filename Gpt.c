#include "Gpt.h"
#include "Gpt_Regs.h"
#include "Common_Macros.h"


STATIC const Gpt_ConfigChannel * Gpt_GptTimers = NULL_PTR;
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
#if (GPT_VERSION_INFO_API == STD_ON)
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
#endif

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
    Gpt_Status = GPT_INITIALIZED;
    Gpt_GptTimers = ConfigPtr->timers;
    uint8 timer_id=0;
    
	volatile uint32* current_timer = NULL_PTR; /* a pointer to indicate what timer we will operate on  */

    for (uint8 i=0; i<GPT_NUMBER_OF_TIMERS; i++){

        /* get the timer base address */
        switch (Gpt_GptTimers[i].channel_id)
        {
        case GPT_TIMER0A:
        case GPT_TIMER0B:
            current_timer = (volatile uint32*)GPT_TIMER0_BASE_ADDRESS;
            timer_id = GPT_TIMER0_ID;
            break;
        
        case GPT_TIMER1A:
        case GPT_TIMER1B:
            current_timer = (volatile uint32*)GPT_TIMER1_BASE_ADDRESS;
            timer_id = GPT_TIMER1_ID;
            break;
        
        case GPT_TIMER2A:
        case GPT_TIMER2B:
            current_timer = (volatile uint32*)GPT_TIMER2_BASE_ADDRESS;
            timer_id = GPT_TIMER2_ID;
            break;

        case GPT_TIMER3A:
        case GPT_TIMER3B:
            current_timer = (volatile uint32*)GPT_TIMER3_BASE_ADDRESS;
            timer_id = GPT_TIMER3_ID;
            break;

        case SYSTICK_TIMER:
            CLEAR_BIT(SYSTICK_CTRL_REG, 0); /* disable the timer */
            SYSTICK_CURRENT_REG = 0; /* clear current ticks */
            SET_BIT(SYSTICK_CTRL_REG, 2);  /* set clock source to System Clock */
            return; /* return, no use for other parameters */
            break;

        default:
            break;
        }

        /* enable timer clock */
        if (Gpt_GptTimers[i].power_mode == GPT_MODE_NORMAL){
            SET_BIT(SYSCTL_RCGCTIMER_REG, timer_id); /* enable Run Mode clock */
            CLEAR_BIT(SYSCTL_SCGCTIMER_REG, timer_id); /* disable Sleep mode clock */

        }else if (Gpt_GptTimers[i].power_mode == GPT_MODE_SLEEP){
            SET_BIT(SYSCTL_SCGCTIMER_REG, timer_id); /* enable Sleep Mode clock */
            CLEAR_BIT(SYSCTL_RCGCTIMER_REG, timer_id); /* disable Run mode clock */
        }

        /* disable the timer */
        CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)current_timer + GPT_GPTMCTL_REG_OFFSET) , Gpt_GptTimers[i].timer_channel);

        /* set timer type (individual or concatenated) */
        *(volatile uint32 *)((volatile uint8 *)current_timer + GPT_GPTMCFG_REG_OFFSET) = Gpt_GptTimers[i].timer_type;

        if (Gpt_GptTimers[i].timer_channel == Channel_A || Gpt_GptTimers[i].timer_channel == CONCATENATED){
            /* set timer running mode (one-shot or periodic) */
            *(volatile uint32 *)((volatile uint8 *)current_timer + GPT_GPTMTAMR_REG_OFFSET) |= Gpt_GptTimers[i].running_mode;
            
            /* set the count direction to be count-up (from AUTOSAR document) */
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)current_timer + GPT_GPTMTAMR_REG_OFFSET), 4);

        }else if (Gpt_GptTimers[i].timer_channel == Channel_B){
            *(volatile uint32 *)((volatile uint8 *)current_timer + GPT_GPTMTBMR_REG_OFFSET) |= Gpt_GptTimers[i].running_mode;
        
            /* set the count direction to be count-up (from AUTOSAR document) */
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)current_timer + GPT_GPTMTBMR_REG_OFFSET), 4);
        }

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
#if (GPT_DEINIT_API == STD_ON)
void Gpt_DeInit(void){
    if (GPT_NOT_INITIALIZED == Gpt_Status){
        return;
    }
    
    volatile uint32* current_timer = NULL_PTR; /* a pointer to indicate what timer we will operate on */
    uint8 timer_id=0;
    for (uint8 i=0; i<GPT_NUMBER_OF_TIMERS; i++){

        /* get the timer base address */
        switch (Gpt_GptTimers[i].channel_id)
        {
        case GPT_TIMER0A:
        case GPT_TIMER0B:
            current_timer = (volatile uint32*)GPT_TIMER0_BASE_ADDRESS;
            timer_id = GPT_TIMER0_ID;
            break;
        
        case GPT_TIMER1A:
        case GPT_TIMER1B:
            current_timer = (volatile uint32*)GPT_TIMER1_BASE_ADDRESS;
            timer_id = GPT_TIMER1_ID;
            break;
        
        case GPT_TIMER2A:
        case GPT_TIMER2B:
            current_timer = (volatile uint32*)GPT_TIMER2_BASE_ADDRESS;
            timer_id = GPT_TIMER2_ID;
            break;

        case GPT_TIMER3A:
        case GPT_TIMER3B:
            current_timer = (volatile uint32*)GPT_TIMER3_BASE_ADDRESS;
            timer_id = GPT_TIMER3_ID;
            break;

        case SYSTICK_TIMER:
            CLEAR_BIT(SYSTICK_CTRL_REG, 0); /* disable the timer */
            SYSTICK_CURRENT_REG = 0; /* clear current ticks */
            CLEAR_BIT(SYSTICK_CTRL_REG, 1); /* disable SysTick interrupts */
            CLEAR_BIT(SYSTICK_NVIC_INTERRUPT_REG ,15); /* disable systick timer interrupt in NVIC table */
            return; /* return, no use for other parameters */
            break;

        default:
            break;
        }

        /* disable timer clock */
        CLEAR_BIT(SYSCTL_RCGCTIMER_REG, timer_id); /* disable Run Mode clock */
        CLEAR_BIT(SYSCTL_SCGCTIMER_REG, timer_id); /* disable Sleep mode clock */

        /* disable the timer */
        CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)current_timer + GPT_GPTMCTL_REG_OFFSET) , Gpt_GptTimers[i].timer_channel);

        /* disable interrupt */
        CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)current_timer + GPT_GPTMIMR_REG_OFFSET) , Gpt_GptTimers[i].timer_channel);

    }

}
#endif

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
#if (GPT_TIME_ELAPSED_API == STD_ON)
Gpt_ValueType Gpt_GetTimeElapsed(Gpt_ChannelType Channel){
    if (GPT_NOT_INITIALIZED == Gpt_Status){
        return 0;
    }

    volatile uint32* current_timer = NULL_PTR; /* a pointer to indicate what timer we will operate on */

    /* get the timer base address */
    switch (Gpt_GptTimers[Channel].channel_id)
    {
    case GPT_TIMER0A:
    case GPT_TIMER0B:
        current_timer = (volatile uint32*)GPT_TIMER0_BASE_ADDRESS;
        break;
    
    case GPT_TIMER1A:
    case GPT_TIMER1B:
        current_timer = (volatile uint32*)GPT_TIMER1_BASE_ADDRESS;
        break;
    
    case GPT_TIMER2A:
    case GPT_TIMER2B:
        current_timer = (volatile uint32*)GPT_TIMER2_BASE_ADDRESS;
        break;

    case GPT_TIMER3A:
    case GPT_TIMER3B:
        current_timer = (volatile uint32*)GPT_TIMER3_BASE_ADDRESS;
        break;

    case SYSTICK_TIMER:
        return SYSTICK_CURRENT_REG;

    default:
        break;
    }

    uint64 elapsed_time=0;
    /* to get the elapsed time, get the counted ticks from value register * number of clock cycles per tick */
    if (Gpt_GptTimers[Channel].timer_channel == Channel_A || Gpt_GptTimers[Channel].timer_channel == CONCATENATED){
        elapsed_time = (*(volatile uint32 *)((volatile uint8 *)current_timer + GPT_GPTMTAV_REG_OFFSET))*Gpt_GptTimers[Channel].clocks_per_tick;
    
    }else if (Gpt_GptTimers[Channel].timer_channel == Channel_B){
        elapsed_time = (*(volatile uint32 *)((volatile uint8 *)current_timer + GPT_GPTMTBV_REG_OFFSET))*Gpt_GptTimers[Channel].clocks_per_tick;
    }

    return elapsed_time;
}
#endif

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
#if (GPT_TIME_REMAINING_API == STD_ON)
Gpt_ValueType Gpt_GetTimeRemaining(Gpt_ChannelType Channel){
    if (GPT_NOT_INITIALIZED == Gpt_Status){
        return 0;
    }
}
#endif

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
    if (GPT_NOT_INITIALIZED == Gpt_Status){
        return;
    }

	volatile uint32* current_timer = NULL_PTR; /* a pointer to indicate what timer we will operate on  */

    /* get the timer base address */
    switch (Gpt_GptTimers[Channel].channel_id)
    {
    case GPT_TIMER0A:
    case GPT_TIMER0B:
        current_timer = (volatile uint32*)GPT_TIMER0_BASE_ADDRESS;
        break;
    
    case GPT_TIMER1A:
    case GPT_TIMER1B:
        current_timer = (volatile uint32*)GPT_TIMER1_BASE_ADDRESS;
        break;
    
    case GPT_TIMER2A:
    case GPT_TIMER2B:
        current_timer = (volatile uint32*)GPT_TIMER2_BASE_ADDRESS;
        break;

    case GPT_TIMER3A:
    case GPT_TIMER3B:
        current_timer = (volatile uint32*)GPT_TIMER3_BASE_ADDRESS;
        break;

    case SYSTICK_TIMER:
        SYSTICK_RELOAD_REG = Value-1; /* set compare value */
        SET_BIT(SYSTICK_CTRL_REG, 0); /* enable the timer to start counting */
        return; /* return, no use for other code */
        break;
    default:
        break;
    }

    if (Gpt_GptTimers[Channel].timer_channel == Channel_A){
        /* set the prescale */
        *(volatile uint32 *)((volatile uint8 *)current_timer + GPT_GPTMTAPR_REG_OFFSET) = Gpt_GptTimers[Channel].clocks_per_tick;

        /* set the value */
        *(volatile uint32 *)((volatile uint8 *)current_timer + GPT_GPTMTAILR_REG_OFFSET) = Value;

    }else if (Gpt_GptTimers[Channel].timer_channel == Channel_B){
        /* set the prescale */
        *(volatile uint32 *)((volatile uint8 *)current_timer + GPT_GPTMTBPR_REG_OFFSET) = Gpt_GptTimers[Channel].clocks_per_tick;

        /* set the value */
        *(volatile uint32 *)((volatile uint8 *)current_timer + GPT_GPTMTBILR_REG_OFFSET) = Value;
    }

    /* enable the timer to start counting */
    SET_BIT(*(volatile uint32 *)((volatile uint8 *)current_timer + GPT_GPTMCTL_REG_OFFSET) , Gpt_GptTimers[Channel].timer_channel);

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
    if (GPT_NOT_INITIALIZED == Gpt_Status){
        return;
    }

	volatile uint32* current_timer = NULL_PTR; /* a pointer to indicate what timer we will operate on  */

    /* get the timer base address */
    switch (Gpt_GptTimers[Channel].channel_id)
    {
    case GPT_TIMER0A:
    case GPT_TIMER0B:
        current_timer = (volatile uint32*)GPT_TIMER0_BASE_ADDRESS;
        break;
    
    case GPT_TIMER1A:
    case GPT_TIMER1B:
        current_timer = (volatile uint32*)GPT_TIMER1_BASE_ADDRESS;
        break;
    
    case GPT_TIMER2A:
    case GPT_TIMER2B:
        current_timer = (volatile uint32*)GPT_TIMER2_BASE_ADDRESS;
        break;

    case GPT_TIMER3A:
    case GPT_TIMER3B:
        current_timer = (volatile uint32*)GPT_TIMER3_BASE_ADDRESS;
        break;

    case SYSTICK_TIMER:
        CLEAR_BIT(SYSTICK_CTRL_REG, 0); /* disable the timer */
        return; /* return, no use for other code */
        break;
    default:
        break;
    }

    /* disable the timer to stop counting */
    CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)current_timer + GPT_GPTMCTL_REG_OFFSET) , Gpt_GptTimers[Channel].timer_channel);
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
#if (GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON)
void Gpt_EnableNotification(Gpt_ChannelType Channel){
    if (GPT_NOT_INITIALIZED == Gpt_Status){
        return;
    }

    volatile uint32* current_timer = NULL_PTR; /* a pointer to indicate what timer we will operate on  */

    /* get the timer base address */
    switch (Gpt_GptTimers[Channel].channel_id)
    {
    case GPT_TIMER0A:
    case GPT_TIMER0B:
        current_timer = (volatile uint32*)GPT_TIMER0_BASE_ADDRESS;
        break;
    
    case GPT_TIMER1A:
    case GPT_TIMER1B:
        current_timer = (volatile uint32*)GPT_TIMER1_BASE_ADDRESS;
        break;
    
    case GPT_TIMER2A:
    case GPT_TIMER2B:
        current_timer = (volatile uint32*)GPT_TIMER2_BASE_ADDRESS;
        break;

    case GPT_TIMER3A:
    case GPT_TIMER3B:
        current_timer = (volatile uint32*)GPT_TIMER3_BASE_ADDRESS;
        break;

    case SYSTICK_TIMER:
        SET_BIT(SYSTICK_CTRL_REG, 1); /* enable SysTick interrupts */
        SET_BIT(SYSTICK_NVIC_INTERRUPT_REG ,15); /* enable systick timer interrupt in NVIC table */
        return; /* return, no use for code */
        break;
    default:
        break;
    }

    /* enable interrupt */
    SET_BIT(*(volatile uint32 *)((volatile uint8 *)current_timer + GPT_GPTMIMR_REG_OFFSET) , Gpt_GptTimers[Channel].timer_channel);
}
#endif

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
#if (GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON)
void Gpt_DisableNotification(Gpt_ChannelType Channel){
    if (GPT_NOT_INITIALIZED == Gpt_Status){
        return;
    }

    volatile uint32* current_timer = NULL_PTR; /* a pointer to indicate what timer we will operate on  */

    /* get the timer base address */
    switch (Gpt_GptTimers[Channel].channel_id)
    {
    case GPT_TIMER0A:
    case GPT_TIMER0B:
        current_timer = (volatile uint32*)GPT_TIMER0_BASE_ADDRESS;
        break;
    
    case GPT_TIMER1A:
    case GPT_TIMER1B:
        current_timer = (volatile uint32*)GPT_TIMER1_BASE_ADDRESS;
        break;
    
    case GPT_TIMER2A:
    case GPT_TIMER2B:
        current_timer = (volatile uint32*)GPT_TIMER2_BASE_ADDRESS;
        break;

    case GPT_TIMER3A:
    case GPT_TIMER3B:
        current_timer = (volatile uint32*)GPT_TIMER3_BASE_ADDRESS;
        break;

    case SYSTICK_TIMER:
        CLEAR_BIT(SYSTICK_CTRL_REG, 1); /* disable SysTick interrupts */
        CLEAR_BIT(SYSTICK_NVIC_INTERRUPT_REG ,15); /* disable systick timer interrupt in NVIC table */
        return; /* return, no use for code */
        break;
    default:
        break;
    }

    /* disable interrupt */
    CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)current_timer + GPT_GPTMIMR_REG_OFFSET) , Gpt_GptTimers[Channel].timer_channel);
}
#endif

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
#if (GPT_WAKEUP_FUNCTIONALITY_API == STD_ON)
void Gpt_SetMode(Gpt_ModeType Mode){
    if (GPT_NOT_INITIALIZED == Gpt_Status){
        return;
    }

}
#endif

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
#if (GPT_WAKEUP_FUNCTIONALITY_API == STD_ON)
void Gpt_DisableWakeup(Gpt_ChannelType Channel){
    if (GPT_NOT_INITIALIZED == Gpt_Status){
        return;
    }
}
#endif

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
#if (GPT_WAKEUP_FUNCTIONALITY_API == STD_ON)
void Gpt_EnableWakeup(Gpt_ChannelType Channel){
    if (GPT_NOT_INITIALIZED == Gpt_Status){
        return;
    }
}
#endif