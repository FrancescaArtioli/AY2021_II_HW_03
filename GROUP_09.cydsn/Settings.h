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
    #define WHO_AM_I_VALUE 0xBC

    uint8_t slaveBuffer[SLAVE_BUFFER_SIZE];
    
    void Setting_DefaultValues();
    
#endif

/* [] END OF FILE */
