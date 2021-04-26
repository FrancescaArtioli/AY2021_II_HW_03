/* ========================================
 * Project GROUP_09: ASSIGNMENT 03
 * 
 * CODE DESCRIPTION:
 * The code samples two analog sensors (TMP36 and PHOTORESISTOR) through a Delta-SigmaADC
 * usign the PSoC as an I2C slave. The USER enters the number of samples (NumSamples) on
 * which he wants to compute the mean and the period at which he wants to sample the channel.
 * In this way, the computed mean will be transmitted with a period given by:
 * Trasmission Period (ms) = NumSamples*Period
 * The transmission frequency will be known by the USER as:
 * Transmission rate (Hz) = 1 / Transmission Period (s)
 * Combining different values of NumSamples and Period, the USER can achieve different transmission
 * frequencies.
 * In the files .iic and .ini, we have provided some examples of combinations used to configure the 
 * two Control Registers.
 * 
 * NOTE: 
 * Authors: Artioli Francesca, Buquicchio Antonella
 * ========================================
*/
#include "project.h"
#include "InterruptRoutines.h"

volatile uint8_t Period = 0;
volatile uint8_t status = DEVICE_STOPPED;
volatile int32 sum_temp = 0; 
volatile int32 sum_photores = 0; 
volatile uint8_t flag_ready = 0;
volatile uint8_t NumSamples = 0;

// Slave Buffer Initialization, default values are 0
volatile uint8_t slaveBuffer[SLAVE_BUFFER_SIZE]; 

int16 mean_temp = 0;
int16 mean_photores = 0;

int main(void)
{
    // Enable global interrupts. 
    CyGlobalIntEnable; 
    
    // Start of different peripherals and ISR
    EZI2C_Start();
    AMux_Start();
    ADC_DelSig_Start();
    Timer_Start();
    
    isr_Timer_StartEx(Custom_ISR_TIMER);
    
    // Set up EZI2C Buffer 
    EZI2C_SetBuffer1(SLAVE_BUFFER_SIZE, SLAVE_RW_BOUNDARY, slaveBuffer);
    
    // Slave buffer initialization
    slaveBuffer[0] = slaveBuffer[0] & MASK_INIT;
    slaveBuffer[1] = DEFAULT_VALUE;
    slaveBuffer[2] = WHO_AM_I_VALUE;
    slaveBuffer[3] = DEFAULT_VALUE;
    slaveBuffer[4] = DEFAULT_VALUE;
    slaveBuffer[5] = DEFAULT_VALUE;
    slaveBuffer[6] = DEFAULT_VALUE;
          
    for(;;)
    {   // Depending on the status in which we are, we compute the mean and save it in its proper position in the 
        // slaveBuffer[]
        switch(status){
        
            case DEVICE_STOPPED:
                count = 0;
            break;
            
            case CHANNEL_TEMP:
                if(flag_ready == 1){
                    mean_temp = sum_temp/NumSamples;
                    slaveBuffer[3] = mean_temp >> 8;    //MSB
                    slaveBuffer[4] = mean_temp & 0xFF;  //LSB
                    Reset_Variables();
                }
            break;
            
            case CHANNEL_PHOTORES:
                if (flag_ready == 1){
                    mean_photores = sum_photores/NumSamples;
                    slaveBuffer[5] = mean_photores >> 8;   //MSB
                    slaveBuffer[6] = mean_photores & 0xFF; //LSB
                    Reset_Variables();
                }
            break;
        
            case CHANNEL_BOTH:
                if (flag_ready == 1){
                    mean_temp = sum_temp/NumSamples;
                    mean_photores = sum_photores/NumSamples;
                    
                    slaveBuffer[3] = mean_temp >> 8;       //MSB
                    slaveBuffer[4] = mean_temp & 0xFF;     //LSB
                    slaveBuffer[5] = mean_photores >> 8;   //MSB
                    slaveBuffer[6] = mean_photores & 0xFF; //LSB
                    Reset_Variables();
                }
            break;
                  
            default:
            break;
        } 
    }  
}

/* [] END OF FILE */


