/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2023 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#include "mg51_iar.h"
#include "sprom.h"

/* SPROM area address define in .xcl file */
unsigned char SPROM_FUNC(unsigned char unused)  @ "SPROM_C"
{
  GPIO_LED_QUASI_MODE;
  GPIO_LED ^= 1;
  SPTEMP++;
  return SPTEMP;
}
