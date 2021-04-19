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

int32 value_digit;
int32 sum_temp; 
int32 sum_photores; 
int32 mean_temp;
int32 mean_photores;

uint8_t i; 

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    AMux_Start();
    ADC_DelSig_Start();
    Timer_Start();
    isr_Timer_StartEx(Custom_ISR_TIMER);
    EZI2C_Start();
    
    Setting_DefaultValues(); // Funzione creata da noi 
    
    EZI2C_SetBuffer1(SLAVE_BUFFER_SIZE, 2, slaveBuffer);
    
    count = 0;
    sum_temp = 0; // Inizializzazione VALUE DIGIT
    sum_photores = 0;
    mean_temp = 0;
    mean_photores = 0;
    
    i = 0;
    
    for(;;)
    {
        if (flag_readData == 1){
        
            switch(status){
            
                case DEVICE_STOPPED:
                    count = 0;
                break;
                
                case CHANNEL_TEMP:
                    value_digit = ADC_DelSig_Read32();
                    if (value_digit < 0) value_digit = 0;
                    if (value_digit > 65535) value_digit = 65535;
                    sum_temp = sum_temp + value_digit;
                    flag_readData = 0;
                    if (count == 4){
                        mean_temp = sum_temp/5;
                        slaveBuffer[3] = mean_temp >> 8;
                        slaveBuffer[4] = mean_temp & 0xFF;
                        count = 0;
                    }
                break;
                
                case CHANNEL_PHOTORES:;
                    value_digit = ADC_DelSig_Read32();
                    if (value_digit < 0) value_digit = 0;
                    if (value_digit > 65535) value_digit = 65535;
                    sum_photores = sum_photores + value_digit;
                    flag_readData = 0;
                    if (count == 4){
                        mean_photores = sum_photores/5;
                        slaveBuffer[5] = mean_photores >> 8;
                        slaveBuffer[6] = mean_photores & 0xFF;
                        count = 0;
                    }
                break;
            
                case CHANNEL_BOTH:
                    ADC_DelSig_StopConvert();
                    AMux_Select(0);
                    ADC_DelSig_StartConvert();
                    value_digit = ADC_DelSig_Read32();
                    if (value_digit < 0) value_digit = 0;
                    if (value_digit > 65535) value_digit = 65535;
                    sum_temp = sum_temp + value_digit;
                    
                    ADC_DelSig_StopConvert();
                    AMux_Select(1);
                    ADC_DelSig_StartConvert();
                    value_digit = ADC_DelSig_Read32();
                    if (value_digit < 0) value_digit = 0;
                    if (value_digit > 65535) value_digit = 65535;
                    sum_photores = sum_photores + value_digit;
                    
                    flag_readData = 0;
                
                    if (count == 4){
                        mean_temp = sum_temp/5;
                        slaveBuffer[3] = mean_temp >> 8;
                        slaveBuffer[4] = mean_temp & 0xFF;
                        mean_photores = sum_photores/5;
                        slaveBuffer[5] = mean_photores >> 8;
                        slaveBuffer[6] = mean_photores & 0xFF;
                        count = 0;
                    }
                break;
            }    
        }
    }
}

/* [] END OF FILE */
