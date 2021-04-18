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
#include "InterruptRoutines.h"
#include "project.h"
#include "Settings.h"

extern volatile uint8_t flag_readData;
extern volatile uint8_t status;

CY_ISR(Custom_ISR_TIMER){
 
    Timer_ReadStatusRegister();
    
    if (count <= 4){
        flag_readData = 1; 
    }else{
        flag_readData = 0;
    }
    
    count++;  
}

void EZI2C_ISR_ExitCallback(void){
    uint8_t control_status = slaveBuffer[0] & 0b00000011;
    if (control_status == 0){
        status = DEVICE_STOPPED;
    }
    else if (control_status == 1){
        status = CHANNEL_TEMP;
    }
    else if (control_status == 2){
        status = CHANNEL_PHOTORES;
    }
    else if (control_status == 3){
        status = CHANNEL_BOTH;
    }
}


/* [] END OF FILE */
