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

#ifndef __SETTINGS_H__
    #define __SETTINGS_H__
    
    #include "project.h"
    
    #define SLAVE_BUFFER_SIZE 7
    #define SLAVE_RW_BOUNDARY 2
    
    #define WHO_AM_I_VALUE 0xBC
    
    #define MASK_STATUS 0b00000011
    #define MASK_SAMPLES 0b00111100
    
    #define AVERAGED_DATA 0x14
    
    volatile uint8_t slaveBuffer[SLAVE_BUFFER_SIZE];
    
    void Setting_DefaultValues();
    
#endif

/* [] END OF FILE */
