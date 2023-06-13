/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2023 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/


//***********************************************************************************************************
//  File Function: MG51 IAP erase / program / read verify demo code
//***********************************************************************************************************
#include "MG51_IAR.H"

#define     DATA_START_ADDR     0x3800 

void main (void) 
{
    unsigned char i;

    MODIFY_HIRC(HIRC_24);
    P05_QUASI_MODE;
    for(i=0;i<128;i++)
       IAPDataBuf[i] =  i;
       
    while(P05);
    Erase_APROM(DATA_START_ADDR,128);
    Erase_Verify_APROM(DATA_START_ADDR,128);
    Program_APROM(DATA_START_ADDR,128);
    Program_Verify_APROM(DATA_START_ADDR,128);

    while(1);
}
//-----------------------------------------------------------------------------------------------------------
