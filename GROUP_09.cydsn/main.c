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

volatile uint8_t flag_dataRead;
volatile uint8_t flag_sendData;

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    Setting_DefaultValues();
    
    count = 0;
    
    for(;;)
    {
        /* Place your application code here. */
    }
}

/* [] END OF FILE */
