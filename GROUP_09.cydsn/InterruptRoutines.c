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
#include "ADC_Functions.h"

extern volatile uint8_t flag_ready;
extern volatile uint8_t status;
extern volatile int32 sum_temp;
extern volatile int32 sum_photores;
extern volatile uint8_t Period;
extern volatile uint8_t NumSamples;
extern volatile uint8_t slaveBuffer[SLAVE_BUFFER_SIZE];
extern volatile uint8_t Period;

uint8_t channel;
uint8_t New_period;


CY_ISR(Custom_ISR_TIMER){
    Timer_ReadStatusRegister();
    count++;
    
    if (flag_ready == 0){
        switch(status){
            
            case CHANNEL_TEMP: 
                sum_temp += DataRead(channel);
                if(count == NumSamples){
                    flag_ready = 1;
                }   
            break;
                
            case CHANNEL_PHOTORES:
                sum_photores += DataRead(channel);
                if(count == NumSamples){
                    flag_ready = 1;
                }   
            break;
            
            case CHANNEL_BOTH:
                    channel = TEMP;
                    sum_temp += DataRead(channel);
                    
                    channel = PHOTORES;
                    sum_photores += DataRead(channel);
                    if(count == NumSamples){
                        flag_ready = 1;
                        
                    }   
            break; 
                    
            default:
            break;
        }
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
        channel = TEMP;
        Blue_LED_Write(LED_OFF);
        status = CHANNEL_TEMP;
    }
    else if (control_status == 2){
        channel = PHOTORES;
        Blue_LED_Write(LED_OFF);        
        status = CHANNEL_PHOTORES;
    }
    else if (control_status == 3){
        Blue_LED_Write(LED_ON);
        status = CHANNEL_BOTH;
    }
    
    New_period = slaveBuffer [1];
    
    if (slaveBuffer[0] >> 2 != NumSamples){
        NumSamples = slaveBuffer[0] >> 2;
    }
    
    if (New_period != Period){
        Period = New_period;
        Reset_Timer(Period);    // Aggiorno counter e period
    }   
}

void Reset_Timer(uint8_t Period){
    Timer_Stop();
    Timer_WriteCounter(Period - 1);
    Timer_WritePeriod(Period - 1);
    Timer_Start();
}

/* [] END OF FILE */
