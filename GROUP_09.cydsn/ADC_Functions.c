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
#include "ADC_Functions.h"


int32 value_digit;

// Channel selection for Amux
//void ChannelSelect(uint8_t channel){
   // ADC_DelSig_StopConvert();
   // AMux_Select(channel);
   // ADC_DelSig_StartConvert();
//}

 int32 DataRead(uint8_t channel){
    ADC_DelSig_StopConvert();
    AMux_Select(channel);
    ADC_DelSig_StartConvert();
    value_digit = ADC_DelSig_Read32();
    if (value_digit < 0) value_digit = 0;
    if (value_digit > 65535) value_digit = 65535;
    return  value_digit;
}

/* [] END OF FILE */
