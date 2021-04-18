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
#include "Timer.h"

extern volatile uint8_t flag_dataRead;
extern volatile uint8_t flag_sendData;

CY_ISR(Custom_ISR_TIMER){
 
    Timer_ReadStatusRegister();
    
    if (count < 5){
        flag_dataRead = 1; 
    }else{
        flag_dataRead = 0;
    }
    
    if (count == 9){
        flag_sendData = 1;
    }
    
    count++;
    
}

/* [] END OF FILE */
