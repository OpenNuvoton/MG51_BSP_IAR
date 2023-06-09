/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2023 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/


//***********************************************************************************************************
//  File Function: MG51 system clock enable LIRC demo code
//***********************************************************************************************************
#include "MG51_IAR.H"


/*=============================================================================================*/
/*  The test process:                                                                          */
/*  1. Power on is run as default HIRC, show LED Fsys tickle faster                            */
/*  2. toggle P1.7 to GND. Call modify Fsys code to LIRC.                                      */
/*  3. toggle P1.7 to VDD. Call modify Fsys code to HIRC.                                      */
/*=============================================================================================*/

void main(void)
{

    P11_QUASI_MODE;
    set_CKCON_CLOEN;                                  // Also can check P1.1 CLO pin for clock to find the Fsys change.
    while (P17);
    FsysSelect(FSYS_LIRC);
    Timer0_Delay(10000,200,1000);
    while (!P17);
    FsysSelect(FSYS_HIRC);
    Timer0_Delay(16000000,2000,1000);
    while (P17);
    set_PCON_PD;
    while(1);

}

