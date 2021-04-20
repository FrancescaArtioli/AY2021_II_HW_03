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
#include "Settings.h"
#include "InterruptRoutines.h"

volatile uint8_t flag_readData = 0;
volatile uint8_t status = 0;
volatile int32 value_digit;
volatile int32 sum_temp; 
volatile int32 sum_photores; 

int32 mean_temp;
int32 mean_photores;

uint8_t i; 

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    EZI2C_Start();
    AMux_Start();
    ADC_DelSig_Start();
    Timer_Start();
    isr_Timer_StartEx(Custom_ISR_TIMER);
    
    EZI2C_SetBuffer1(SLAVE_BUFFER_SIZE, 2, slaveBuffer);
    
    Setting_DefaultValues(); // Funzione creata da noi 
   
    //sum_temp = 0; // Inizializzazione VALUE DIGIT
    //sum_photores = 0;
    mean_temp = 0;
    mean_photores = 0;
    
    for(;;)
    {       
            switch(status){
            
                case DEVICE_STOPPED:
                    count = 0;
                    //flag_readData = 0;
                break;
                
                case CHANNEL_TEMP:
                    if(flag_readData == 1){
                        mean_temp = sum_temp/5;
                        slaveBuffer[3] = mean_temp >> 8;
                        slaveBuffer[4] = mean_temp & 0xFF;
                        sum_temp = 0;
                        count = 0;
                        flag_readData = 0;
                    }
                break;
                
                case CHANNEL_PHOTORES:
                    if (flag_readData == 1){
                        mean_photores = sum_photores/5;
                        slaveBuffer[5] = mean_photores >> 8;
                        slaveBuffer[6] = mean_photores & 0xFF;
                        sum_photores = 0;
                        count = 0;
                        flag_readData = 0;
                    }
                break;
            
                case CHANNEL_BOTH:
                    if (flag_readData == 1){
                        mean_temp = sum_temp/5;
                        mean_photores = sum_photores/5;
                        
                        slaveBuffer[3] = mean_temp >> 8;
                        slaveBuffer[4] = mean_temp & 0xFF;
                        slaveBuffer[5] = mean_photores >> 8;
                        slaveBuffer[6] = mean_photores & 0xFF;
                        sum_temp = 0;
                        sum_photores = 0;
                        count = 0;
                        flag_readData = 0;
                    }
                break;
            } 
        }  
    }

/* [] END OF FILE */


