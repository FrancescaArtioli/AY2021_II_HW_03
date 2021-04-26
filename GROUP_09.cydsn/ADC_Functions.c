 /*
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
#include "ADC_Functions.h"


int32 value_digit;
int32 value_mv;
// uint8_t channel

 int32 DataRead(void){
    //AMux_Select(channel);
    value_digit = ADC_DelSig_Read32();
    if (value_digit < 0) value_digit = 0;
    if (value_digit > 65535) value_digit = 65535;
    value_mv = ADC_DelSig_CountsTo_mVolts(value_digit);
    return  value_mv;
}

/* [] END OF FILE */
