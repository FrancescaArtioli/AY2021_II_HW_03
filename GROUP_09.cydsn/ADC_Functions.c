/* ========================================
 * \file ADC_Functions.c
 * This function allows to Read the data coming from the ADC after conversion and convert this value in 
 * milliVolts. 
 * ========================================
*/
#include "project.h"
#include "ADC_Functions.h"

int32 value_digit;
int32 value_mv;

 int32 DataRead(void){
    value_digit = ADC_DelSig_Read32();
    if (value_digit < 0) value_digit = 0;
    if (value_digit > 65535) value_digit = 65535;
    value_mv = ADC_DelSig_CountsTo_mVolts(value_digit);
    return  value_mv;
}

/* [] END OF FILE */
