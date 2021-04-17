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

void Setting_DefaultValues(){
    
    slaveBuffer[0] |= (1 << 2);
    slaveBuffer[0] |= (1 << 4);
    slaveBuffer[1] = Timer_ReadPeriod();
    slaveBuffer[2] = WHO_AM_I_VALUE;
    
}
    
/* [] END OF FILE */
