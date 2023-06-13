/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2023 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/



//***********************************************************************************************************
//  File Function: MG51 ADC / Bandgap input demo code
//***********************************************************************************************************
#include "MG51_IAR.H"

/*---------------------------------------------*/
void main(void)
{
    MODIFY_HIRC(HIRC_24);
    Set_Interrupt_Priority_Level(INT_WDT, 0);
    Set_Interrupt_Priority_Level(INT_ADC, 1);
    SET_INT_UART0_LEVEL2;
    while(1);
}
/* Check isr.c for full interrupt vector      */
