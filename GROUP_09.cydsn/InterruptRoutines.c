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
#include "ADC_Functions.h"

extern volatile uint8_t flag_sendData;
extern volatile uint8_t status;
extern volatile int32 sum_temp;
extern volatile int32 sum_photores;

uint8_t channel;


CY_ISR(Custom_ISR_TIMER){
 
    Timer_ReadStatusRegister();
    count++;
    
    switch(status){
        
        case CHANNEL_TEMP:
            sum_temp += DataRead(channel);
            if(count == 5){
                flag_sendData = 1;
            }   
        break;
            
        case CHANNEL_PHOTORES:
            sum_photores += DataRead(channel);
            if(count == 5){
                flag_sendData = 1;
            }   
        break;
        
        case CHANNEL_BOTH:
                channel = 0;
                sum_temp += DataRead(channel);
                
                channel = 1;
                sum_photores += DataRead(channel);
                if(count == 5){
                    flag_sendData = 1;
                }   
        break;        
    }
          
}

void EZI2C_ISR_ExitCallback(void){
    uint8_t control_status = slaveBuffer[0] & MASK_STATUS;
    if (control_status == 0){
        ADC_DelSig_StopConvert();
        Blue_LED_Write(LED_OFF);
        status = DEVICE_STOPPED;
    }
    else if (control_status == 1){
        channel = 0;
        Blue_LED_Write(LED_OFF);
        status = CHANNEL_TEMP;
    }
    else if (control_status == 2){
        channel = 1;
        Blue_LED_Write(LED_OFF);        
        status = CHANNEL_PHOTORES;
    }
    else if (control_status == 3){
        Blue_LED_Write(LED_ON);
        status = CHANNEL_BOTH;
    }
}


/* [] END OF FILE */
