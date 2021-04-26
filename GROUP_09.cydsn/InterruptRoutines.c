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
extern volatile uint8_t NumSamples;
extern volatile uint8_t slaveBuffer[SLAVE_BUFFER_SIZE];
extern volatile uint8_t Period;

uint8_t channel;

CY_ISR(Custom_ISR_TIMER){
    Timer_ReadStatusRegister();
    count++;
    
    if (flag_ready == 0){
        switch(status){
            
            case CHANNEL_TEMP: 
                sum_temp += DataRead();
                if(count == NumSamples){
                    flag_ready = 1;
                }   
            break;
                
            case CHANNEL_PHOTORES:
                sum_photores += DataRead();
                if(count == NumSamples){
                    flag_ready = 1;
                }   
            break;
            
            case CHANNEL_BOTH:
                    channel = TEMP;
                    AMux_Select(channel);
                    sum_temp += DataRead();
                    
                    channel = PHOTORES;
                    AMux_Select(channel);
                    sum_photores += DataRead();
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
    if (control_status != status){
        if (control_status == 0){
            //ADC_DelSig_StopConvert();
            Blue_LED_Write(LED_OFF);
            status = DEVICE_STOPPED;
        }
        else if (control_status == 1){
            channel = TEMP;
            AMux_Select(channel);
            Blue_LED_Write(LED_OFF);
            status = CHANNEL_TEMP;
        }
        else if (control_status == 2){
            channel = PHOTORES;
            AMux_Select(channel);
            Blue_LED_Write(LED_OFF);        
            status = CHANNEL_PHOTORES;
        }
        else if (control_status == 3){
            Blue_LED_Write(LED_ON);
            status = CHANNEL_BOTH;
        }
    }
       
    if (((slaveBuffer[0] & MASK_SAMPLES) >> 2) != NumSamples){
        NumSamples = (slaveBuffer[0] & MASK_SAMPLES) >> 2;
    }
    
    if (slaveBuffer[1] != Period){
        Period = slaveBuffer[1];
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
