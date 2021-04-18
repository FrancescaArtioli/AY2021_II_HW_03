/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#ifndef __INTERRUPT_ROUTINES_H__
    #define __INTERRUPT_ROUTINES_H__
    
    #include "project.h"
    
    #define DEVICE_STOPPED 0
    #define CHANNEL_TEMP 1
    #define CHANNEL_PHOTORES 2
    #define CHANNEL_BOTH 3
    
    uint8_t count;
    
    CY_ISR_PROTO(Custom_ISR_TIMER);
    
    
#endif

/* [] END OF FILE */
