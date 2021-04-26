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
    
    #define TEMP 0
    #define PHOTORES 1
    
    #define LED_OFF 0
    #define LED_ON 1
    
    #define SLAVE_BUFFER_SIZE 7
    #define SLAVE_RW_BOUNDARY 2
    
    #define WHO_AM_I_VALUE 0xBC  
    #define MASK_STATUS 0b00000011
    #define MASK_SAMPLES 0b00111100
    #define MASK_INIT 0b11000000
    #define DEFAULT_VALUE 0x00
    
    volatile uint8_t count;
    
    void Reset_Timer(uint8_t period);
    
    CY_ISR_PROTO(Custom_ISR_TIMER);
    
#endif

/* [] END OF FILE */
