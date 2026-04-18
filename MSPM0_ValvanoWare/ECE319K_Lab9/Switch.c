/*
 * Switch.c
 *
 *  Created on: January 12, 2026
 *      Author:
 */
#include <ti/devices/msp/msp.h>
#include "../inc/LaunchPad.h"
// LaunchPad.h defines all the indices into the PINCM table
void Switch_Init(void){
    // write this
    IOMUX->SECCFG.PINCM[PB12INDEX] = 0x40081;
    //IOMUX->SECCFG.PINCM[PB16INDEX] = 0x40081;
}
// return current state of switches
uint32_t Switch_In(void){
    // write this
  return 0; // replace this line
}
