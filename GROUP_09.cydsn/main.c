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

#define LED_OFF 0
#define LED_ON 1

volatile uint8_t flag_readData = 0;
volatile uint8_t status = 0;

int32 value_digit;
int32 sum; 

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    AMux_Start();
    ADC_DelSig_Start();
    Timer_Start();
    isr_Timer_StartEx(Custom_ISR_TIMER);
    EZI2C_Start();
    
    Setting_DefaultValues();
    
    count = 0;
    sum = 0; // Inizializzazione VALUE DIGIT
    
    for(;;)
    {
        if (flag_readData == 1){
          switch(status){
            
            case DEVICE_STOPPED:
                Blue_LED_Write(LED_OFF);
                count = 0;
            break;
                
            case CHANNEL_TEMP:
                AMux_Select(0);
                value_digit = ADC_DelSig_Read32();
                sum = sum + value_digit;
                flag_readData = 0;
                if (count == 4){
                    //Calcola media
                    //Salva nel registro 8 bit + 8 bit
                    //Manda dato
                }
            
        }
        }    
    }
}

/* [] END OF FILE */
