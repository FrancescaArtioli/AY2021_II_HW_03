/* ========================================
 * \file InterruptRoutines.c
 * In this file we manage: 
 * -> ISR of the Timer required to sample the analog channels
 * -> EZI2C_ISR_ExitCallback(): used to control values written by the USER on the BCP
 * -> Reset_Timer(): when a new period is provided by the USER on the BCP, the function reloads the counter
 *    and writes the new period
 * -> Reset_Variables(): resets all the variables of interest
 * ========================================
*/

#include "InterruptRoutines.h"
#include "project.h"
#include "ADC_Functions.h"

extern volatile uint8_t status;
extern volatile uint8_t Period;
extern volatile uint8_t NumSamples;
extern volatile uint8_t flag_ready;
extern volatile int32 sum_temp;
extern volatile int32 sum_photores;
extern volatile uint8_t slaveBuffer[SLAVE_BUFFER_SIZE];

uint8_t channel;
uint8_t i;

CY_ISR(Custom_ISR_TIMER){
    // Read status register to bring the interrupt line low
    Timer_ReadStatusRegister();

    count++;
    
    // As long as count is equal or lower than NumSamples, data are acquired and the sum is computed. When count is 
    // equal to NumSamples, the flag is risen. 
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
    // When a new value is detected into the control registers (1 or 2) either we update the status, 
    // the period or the number of samples for the mean. 
    
    // In order to ignore the values that do not determine the status, we have used a specific mask defined
    // in the .h file. 
    uint8_t control_status = slaveBuffer[0] & MASK_STATUS; 
    if (control_status != status){
        if (control_status == 0){
            i = 3;
            for(i = 3; i < 7; i++){
                slaveBuffer[i] = 0;
            }
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
        
        Reset_Variables();    
    }
      
    // In order to consider just the bits associated to the number of samples, we have used a specific mask defined
    // in the .h file. Then, the value is shifted of 2 position (right) to select the correct value. 
    if (((slaveBuffer[0] & MASK_SAMPLES) >> 2) != NumSamples){
        NumSamples = (slaveBuffer[0] & MASK_SAMPLES) >> 2;
        Reset_Variables();
    }
    
    if (slaveBuffer[1] != Period){
        Period = slaveBuffer[1];
        Reset_Timer(Period);
        Reset_Variables();
    }   
}

void Reset_Timer(uint8_t Period){
    Timer_Stop();
    Timer_WritePeriod((Period * PERIOD_ADJ) - 1);
    Timer_WriteCounter(0);
    Timer_Start();
}

void Reset_Variables(){
    sum_temp = 0;
    sum_photores = 0;
    count = 0;
    flag_ready = 0;    
}

/* [] END OF FILE */
