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
#include "project.h"
#include "InterruptRoutines.h"

#define WHO_AM_I_VALUE 0xBC

volatile uint8_t Period = 0;
volatile uint8_t status = 0;
volatile int32 sum_temp = 0; 
volatile int32 sum_photores = 0; 
volatile uint8_t flag_ready = 0;
volatile uint8_t NumSamples = 0;
volatile uint8_t slaveBuffer[SLAVE_BUFFER_SIZE] = {0};

int32 mean_temp = 0;
int32 mean_photores = 0;


int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    
    EZI2C_Start();
    
    AMux_Start();
    ADC_DelSig_Start();
    
    // Start Timer gestione ADC
    Timer_Start();
    
    isr_Timer_StartEx(Custom_ISR_TIMER);
    
    EZI2C_SetBuffer1(SLAVE_BUFFER_SIZE, SLAVE_RW_BOUNDARY, slaveBuffer);
    
    slaveBuffer[2] = WHO_AM_I_VALUE;
    
    Period = slaveBuffer[1];
       
    for(;;)
    {       
        switch(status){
        
            case DEVICE_STOPPED:
                count = 0;
            break;
            
            case CHANNEL_TEMP:
                if(flag_ready == 1){
                    mean_temp = sum_temp/NumSamples;
                    slaveBuffer[3] = mean_temp >> 8;
                    slaveBuffer[4] = mean_temp & 0xFF;
                    sum_temp = 0;
                    count = 0;
                    flag_ready = 0;
                }
            break;
            
            case CHANNEL_PHOTORES:
                if (flag_ready == 1){
                    mean_photores = sum_photores/NumSamples;
                    slaveBuffer[5] = mean_photores >> 8;
                    slaveBuffer[6] = mean_photores & 0xFF;
                    sum_photores = 0;
                    count = 0;
                    flag_ready = 0;
                }
            break;
        
            case CHANNEL_BOTH:
                if (flag_ready == 1){
                    mean_temp = sum_temp/NumSamples;
                    mean_photores = sum_photores/NumSamples;
                    
                    slaveBuffer[3] = mean_temp >> 8;
                    slaveBuffer[4] = mean_temp & 0xFF;
                    slaveBuffer[5] = mean_photores >> 8;
                    slaveBuffer[6] = mean_photores & 0xFF;
                    sum_temp = 0;
                    sum_photores = 0;
                    count = 0;
                    flag_ready = 0;
                }
            break;
                  
            default:
            break;
        } 
    }  
}

/* [] END OF FILE */


