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

int32 value_digit;

volatile uint8_t flag_readData = 0;
volatile uint8_t flag_sendData = 0;
volatile uint8_t status = 0;

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    ADC_DelSig_Start();
    Timer_Start();
    isr_Timer_StartEx(Custom_ISR_TIMER);
    EZI2C_Start();
    
    Setting_DefaultValues();
    
    count = 0;
    
    for(;;)
    {
        if (flag_readData == 1){
          
        }    
    }
}

/* [] END OF FILE */
