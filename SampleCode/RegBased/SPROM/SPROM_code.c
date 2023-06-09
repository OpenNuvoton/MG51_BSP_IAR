/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2023 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/


//***********************************************************************************************************
//  File Function: MG51 locate data in APROM simple demo 
//***********************************************************************************************************
#include "MG51_IAR.H"
#include "SPROM.h"

/* SPROM area address define in .xcl file */
unsigned char SPROM_FUNC(unsigned char unused)  @ "SPROM_C"
{
  P12_PUSHPULL_MODE;
  P12 ^= 1;
  SPTEMP++;
  return SPTEMP;
}
