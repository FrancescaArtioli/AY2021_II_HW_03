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

#define LED_OFF 0
#define LED_ON 1

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
        ADC_DelSig_StopConvert();
        Blue_LED_Write(LED_OFF);
    }
    else if (control_status == 1){
        status = CHANNEL_TEMP;
        ADC_DelSig_StopConvert();
        AMux_Select(0);
        ADC_DelSig_StartConvert(); 
        Blue_LED_Write(LED_OFF);
    }
    else if (control_status == 2){
        status = CHANNEL_PHOTORES;
        ADC_DelSig_StopConvert();
        AMux_Select(1);
        ADC_DelSig_StartConvert();
        Blue_LED_Write(LED_OFF);
    }
    else if (control_status == 3){
        Blue_LED_Write(LED_ON);
        status = CHANNEL_BOTH;
    }
}


/* [] END OF FILE */
