/*********************************************************************************************************************
* DAVE APP Name : SDMMC_BLOCK       APP Version: 4.0.5
*
* NOTE:
* This file is generated by DAVE. Any manual modification done to this file will be lost when the code is regenerated.
*********************************************************************************************************************/

/**
 * @cond
 ***********************************************************************************************************************
 * Copyright (c) 2016, Infineon Technologies AG
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,are permitted provided that the
 * following conditions are met:
 *
 *   Redistributions of source code must retain the above copyright notice, this list of conditions and the  following
 *   disclaimer.
 *
 *   Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the
 *   following disclaimer in the documentation and/or other materials provided with the distribution.
 *
 *   Neither the name of the copyright holders nor the names of its contributors may be used to endorse or promote
 *   products derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE  FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY,OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT  OF THE
 * USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * To improve the quality of the software, users are encouraged to share modifications, enhancements or bug fixes
 * with Infineon Technologies AG (dave@infineon.com).
 ***********************************************************************************************************************
 *
 * Change History
 * --------------
 *
 * 2016-01-20:
 *     - Initial version <br>
 *
 * 2016-02-05:
 *     - RTOS support added <br>
 *
 * @endcond
 */

/***********************************************************************************************************************
 * HEADER FILES
 **********************************************************************************************************************/

#include "sdmmc_block.h"

/**********************************************************************************************************************
 * LOCAL ROUTINES
 **********************************************************************************************************************/


/**********************************************************************************************************************
  * DATA STRUCTURES
 **********************************************************************************************************************/


/* SDMMC SPI instance */
SDMMC_BLOCK_SPI_t SDMMC_BLOCK_0_SPI =
{
  .spi_master_handle = &SPI_MASTER_0, /* SDMMC SPI instance */
  .mode_init_flag = false,
};

/* SDMMC_BLOCK APP instance */
SDMMC_BLOCK_t SDMMC_BLOCK_0 =
{
  .interface_mode = SDMMC_BLOCK_CARD_INTERFACE_SPI, /* SPI interface */
  .sdmmc_spi = &SDMMC_BLOCK_0_SPI, /* SDMMC_SPI instance */

  .rtos_mode = SDMMC_BLOCK_RTOS_MODE_DISABLED, /* RTOS mose is not used */

  #ifdef SDMMC_BLOCK_RTOS_MODE_SELECT
  .cmsis_rtos = NULL, /* RTOS mose is not used */
  #endif /* SDMMC_BLOCK_RTOS_MODE_SELECT */

  .init_pins = NULL, /* true: Initialized; false: Uninitialized */
  .init_flag = false, /* true: Initialized; false: Uninitialized */
  .card_state = (uint8_t)(SDMMC_BLOCK_CARD_STATE_NOT_INITIALIZED | SDMMC_BLOCK_CARD_STATE_NO_CARD) /* Card state */
};

/**********************************************************************************************************************
 * FUNCTION DEFINITIONS
 **********************************************************************************************************************/

