
#include "sdmmc_block_sd.h"

#ifdef SDMMC_BLOCK_SD

/*******************************************************************************
 * DATA STRUCTURES
 *******************************************************************************/

/*
 * The command type has 6 fields:
 * response_type_sel, crc_check_en, index_check_en,
 * dat_present_sel, cmd_type and cmd_index
 */
#define INSERT_SDMMC_BLOCK_COMMAND(a, b, c, d, e, f) {{a, b, c, d, e, f}}

/* Command Structure defining SD, MMC and Application specific commands */
const XMC_SDMMC_COMMAND_t SDMMC_BLOCK_COMMAND[40] =
{
  /* Start: SD card commands */
  INSERT_SDMMC_BLOCK_COMMAND(0U, 0U, 0U, 0U, 0U, SDMMC_BLOCK_GO_IDLE_STATE),        /* 0 */
  INSERT_SDMMC_BLOCK_COMMAND(1U, 1U, 0U, 0U, 0U, SDMMC_BLOCK_ALL_SEND_CID),         /* 1 */
  INSERT_SDMMC_BLOCK_COMMAND(2U, 1U, 1U, 0U, 0U, SDMMC_BLOCK_SEND_RELATIVE_ADDR),   /* 2 */
  INSERT_SDMMC_BLOCK_COMMAND(0U, 0U, 0U, 0U, 0U, SDMMC_BLOCK_SET_DSR),              /* 3 */
  INSERT_SDMMC_BLOCK_COMMAND(2U, 1U, 1U, 1U, 0U, SDMMC_BLOCK_SWITCH_FUNC),          /* 4 */
  INSERT_SDMMC_BLOCK_COMMAND(3U, 1U, 1U, 0U, 0U, SDMMC_BLOCK_SELECT_DESELECT_CARD), /* 5 */
  INSERT_SDMMC_BLOCK_COMMAND(2U, 1U, 1U, 0U, 0U, SDMMC_BLOCK_SD_SEND_IF_COND),      /* 6 */
  INSERT_SDMMC_BLOCK_COMMAND(1U, 1U, 0U, 0U, 0U, SDMMC_BLOCK_SEND_CSD),             /* 7 */
  INSERT_SDMMC_BLOCK_COMMAND(1U, 1U, 0U, 0U, 0U, SDMMC_BLOCK_SEND_CID),             /* 8 */
  INSERT_SDMMC_BLOCK_COMMAND(3U, 1U, 1U, 0U, 0U, SDMMC_BLOCK_STOP_TRANSMISSION),    /* 9 */
  INSERT_SDMMC_BLOCK_COMMAND(2U, 1U, 1U, 0U, 0U, SDMMC_BLOCK_SEND_STATUS),          /* 10 */
  INSERT_SDMMC_BLOCK_COMMAND(0U, 0U, 0U, 0U, 0U, SDMMC_BLOCK_GO_INACTIVE_STATE),    /* 11 */
  INSERT_SDMMC_BLOCK_COMMAND(2U, 1U, 1U, 0U, 0U, SDMMC_BLOCK_SET_BLOCKLEN),         /* 12 */
  INSERT_SDMMC_BLOCK_COMMAND(2U, 1U, 1U, 1U, 0U, SDMMC_BLOCK_READ_SINGLE_BLOCK),    /* 13 */
  INSERT_SDMMC_BLOCK_COMMAND(2U, 1U, 1U, 1U, 0U, SDMMC_BLOCK_READ_MULTIPLE_BLOCK),  /* 14 */
  INSERT_SDMMC_BLOCK_COMMAND(2U, 1U, 1U, 1U, 0U, SDMMC_BLOCK_WRITE_BLOCK),          /* 15 */
  INSERT_SDMMC_BLOCK_COMMAND(2U, 1U, 1U, 1U, 0U, SDMMC_BLOCK_WRITE_MULTIPLE_BLOCK), /* 16 */
  INSERT_SDMMC_BLOCK_COMMAND(2U, 1U, 1U, 1U, 0U, SDMMC_BLOCK_PROGRAM_CSD),          /* 17 */
  INSERT_SDMMC_BLOCK_COMMAND(2U, 1U, 1U, 0U, 0U, SDMMC_BLOCK_SET_WRITE_PROT),       /* 18 */
  INSERT_SDMMC_BLOCK_COMMAND(2U, 1U, 1U, 0U, 0U, SDMMC_BLOCK_CLR_WRITE_PROT),       /* 19 */
  INSERT_SDMMC_BLOCK_COMMAND(2U, 1U, 1U, 1U, 0U, SDMMC_BLOCK_SEND_WRITE_PROT),      /* 20 */
  INSERT_SDMMC_BLOCK_COMMAND(2U, 1U, 1U, 0U, 0U, SDMMC_BLOCK_ERASE_WR_BLK_START),   /* 21 */
  INSERT_SDMMC_BLOCK_COMMAND(2U, 1U, 1U, 0U, 0U, SDMMC_BLOCK_ERASE_WR_BLK_END),     /* 22 */
  INSERT_SDMMC_BLOCK_COMMAND(3U, 1U, 1U, 0U, 0U, SDMMC_BLOCK_ERASE),                /* 23 */
  INSERT_SDMMC_BLOCK_COMMAND(2U, 1U, 1U, 1U, 0U, SDMMC_BLOCK_LOCK_UNLOCK),          /* 24 */
  INSERT_SDMMC_BLOCK_COMMAND(2U, 1U, 1U, 0U, 0U, SDMMC_BLOCK_APP_CMD),              /* 25 */
  INSERT_SDMMC_BLOCK_COMMAND(2U, 1U, 1U, 1U, 0U, SDMMC_BLOCK_GEN_CMD),              /* 26 */
  /* Start: application specific commands */
  INSERT_SDMMC_BLOCK_COMMAND(2U, 1U, 1U, 0U, 0U, SDMMC_BLOCK_SET_BUS_WIDTH),        /* 27 */
  INSERT_SDMMC_BLOCK_COMMAND(2U, 1U, 1U, 1U, 0U, SDMMC_BLOCK_SD_STATUS),            /* 28 */
  INSERT_SDMMC_BLOCK_COMMAND(2U, 1U, 1U, 1U, 0U, SDMMC_BLOCK_SEND_NUM_WR_BLOCKS),   /* 29 */
  INSERT_SDMMC_BLOCK_COMMAND(2U, 1U, 1U, 0U, 0U, SDMMC_BLOCK_SET_WR_BLK_ERASE_COUNT), /* 30 */
  INSERT_SDMMC_BLOCK_COMMAND(2U, 0U, 0U, 0U, 0U, SDMMC_BLOCK_SD_SEND_OP_COND),      /* 31 */
  INSERT_SDMMC_BLOCK_COMMAND(2U, 1U, 1U, 0U, 0U, SDMMC_BLOCK_SET_CLR_CARD_DETECT),  /* 32 */
  INSERT_SDMMC_BLOCK_COMMAND(2U, 1U, 1U, 1U, 0U, SDMMC_BLOCK_SEND_SCR),             /* 33 */
  /* Start of SDMMC_MMC Card specific commands */
  INSERT_SDMMC_BLOCK_COMMAND(2U, 0U, 1U, 0U, 0U, SDMMC_BLOCK_MMC_SEND_OP_COND),     /* 34 */
  INSERT_SDMMC_BLOCK_COMMAND(3U, 1U, 1U, 0U, 0U, SDMMC_BLOCK_MMC_SLEEP_AWAKE),      /* 35 */
  INSERT_SDMMC_BLOCK_COMMAND(3U, 1U, 1U, 0U, 0U, SDMMC_BLOCK_SWITCH_FUNC),          /* 36 */
  INSERT_SDMMC_BLOCK_COMMAND(2U, 1U, 1U, 1U, 0U, SDMMC_BLOCK_MMC_SEND_EXT_CSD),     /* 37 */
  INSERT_SDMMC_BLOCK_COMMAND(2U, 1U, 1U, 0U, 0U, SDMMC_BLOCK_ERASE_GROUP_START),    /* 38 */
  INSERT_SDMMC_BLOCK_COMMAND(2U, 1U, 1U, 0U, 0U, SDMMC_BLOCK_ERASE_GROUP_END)       /* 39 */
};

/*
 * SD card command index hash table
 * It contains the index of the command structure
 *
 * Array index 0-57 is for general SD commands and array
 * index 58-64 is for application specific commands.
 */
const uint8_t SDMMC_BLOCK_SD_HASH_TABLE[65] =
{
  (uint8_t)0x00, (uint8_t)0xFF, (uint8_t)0x01, (uint8_t)0x02,
  (uint8_t)0x03, (uint8_t)0xFF, (uint8_t)0x04, (uint8_t)0x05,
  (uint8_t)0x06, (uint8_t)0x07, (uint8_t)0x08, (uint8_t)0xFF,
  (uint8_t)0x09, (uint8_t)0x0A, (uint8_t)0xFF, (uint8_t)0x0B,
  (uint8_t)0x0C, (uint8_t)0x0D, (uint8_t)0x0E, (uint8_t)0xFF,
  (uint8_t)0xFF, (uint8_t)0xFF, (uint8_t)0xFF, (uint8_t)0xFF,
  (uint8_t)0x0F, (uint8_t)0x10, (uint8_t)0xFF, (uint8_t)0x11,
  (uint8_t)0x12, (uint8_t)0x13, (uint8_t)0x14, (uint8_t)0xFF,
  (uint8_t)0x15, (uint8_t)0x16, (uint8_t)0xFF, (uint8_t)0xFF,
  (uint8_t)0xFF, (uint8_t)0xFF, (uint8_t)0x17, (uint8_t)0xFF,
  (uint8_t)0xFF, (uint8_t)0xFF, (uint8_t)0x18, (uint8_t)0xFF,
  (uint8_t)0xFF, (uint8_t)0xFF, (uint8_t)0xFF, (uint8_t)0xFF,
  (uint8_t)0xFF, (uint8_t)0xFF, (uint8_t)0xFF, (uint8_t)0xFF,
  (uint8_t)0xFF, (uint8_t)0xFF, (uint8_t)0xFF, (uint8_t)0x19,
  (uint8_t)0x1A, (uint8_t)0xFF, (uint8_t)0x1B, (uint8_t)0x1C,
  (uint8_t)0x1D, (uint8_t)0x1E, (uint8_t)0x1F, (uint8_t)0x20,
  (uint8_t)0x21
};

/* Timer callback function */
static void SDMMC_BLOCK_SD_TimerCallback(void *arg)
{
  if (arg != NULL)
  {
    SDMMC_BLOCK_t *obj = (SDMMC_BLOCK_t *)arg;
    obj->sdmmc_sd->tmr_expire = (bool)0U;
  }
}

/* Create and start timer in a non-RTOS environment */
static SDMMC_BLOCK_MODE_STATUS_t SDMMC_BLOCK_SD_StartTimer(SDMMC_BLOCK_t *const obj, uint32_t delay)
{
  uint32_t tmr_id = 0U;
  SDMMC_BLOCK_MODE_STATUS_t status = SDMMC_BLOCK_MODE_STATUS_SUCCESS;
  obj->sdmmc_sd->tmr_expire = (bool)1U;

  tmr_id = SYSTIMER_CreateTimer(delay, SYSTIMER_MODE_ONE_SHOT, &SDMMC_BLOCK_SD_TimerCallback, (void *)obj);
  if (tmr_id != SYSTIMER_STATUS_FAILURE)
  {
    /* Timer creation successful */
    if (SYSTIMER_StartTimer(tmr_id) != SYSTIMER_STATUS_SUCCESS)
    {
      /* Remove timer; it can't be used */
      SYSTIMER_DeleteTimer(tmr_id);
      obj->sdmmc_sd->tmr_id = 0U;
      status = SDMMC_BLOCK_MODE_STATUS_START_TIMER_FAILED;
    }
    obj->sdmmc_sd->tmr_id = tmr_id;
  }
  else
  {
	/* Timer creation failed! */
    obj->sdmmc_sd->tmr_id = 0U;
    status = SDMMC_BLOCK_MODE_STATUS_CREATE_TIMER_FAILED;
  }

  return status;
}

/* Stop timer in a non-RTOS environment */
static uint32_t SDMMC_BLOCK_SD_StopTimer(SDMMC_BLOCK_t *const obj)
{
  uint32_t tmr_id = obj->sdmmc_sd->tmr_id;
  uint32_t status;

  status = SYSTIMER_StopTimer(tmr_id);
  if (status != SYSTIMER_STATUS_SUCCESS)
  {
	/* Remove timer; it can't be used */
    SYSTIMER_DeleteTimer(tmr_id);
    status = SDMMC_BLOCK_MODE_STATUS_STOP_TIMER_FAILED;
    obj->sdmmc_sd->tmr_id = 0U;
  }

  return status;
}

/* Delay function */
SDMMC_BLOCK_MODE_STATUS_t SDMMC_BLOCK_SD_Delay(SDMMC_BLOCK_t *const obj, uint32_t delay)
{
  uint32_t tmr_id = 0U;
  SDMMC_BLOCK_MODE_STATUS_t status = SDMMC_BLOCK_MODE_STATUS_CREATE_TIMER_FAILED;

  obj->sdmmc_sd->tmr_expire = (bool)1U;
  obj->sdmmc_sd->tmr_id = tmr_id;

  tmr_id = SYSTIMER_CreateTimer(delay, SYSTIMER_MODE_ONE_SHOT, &SDMMC_BLOCK_SD_TimerCallback, (void *)obj);
  if (tmr_id > 0U)
  {
	obj->sdmmc_sd->tmr_id = tmr_id;

	status = SYSTIMER_StartTimer(tmr_id);

    /* Is timer started successfully? */
    if (status == (uint32_t)SYSTIMER_STATUS_SUCCESS)
    {
      /* Wait infinitely until timer expires */
      while (obj->sdmmc_sd->tmr_expire)
      {
      }

      /* Stop the timer */
      if (SYSTIMER_StopTimer(tmr_id) == SYSTIMER_STATUS_SUCCESS)
      {
        status = SDMMC_BLOCK_MODE_STATUS_SUCCESS;
      }
    }
    else
    {
      status = SDMMC_BLOCK_MODE_STATUS_START_TIMER_FAILED;
    }
  }

  if (status == SDMMC_BLOCK_MODE_STATUS_SUCCESS)
  {
	/* Delete the timer */
    SYSTIMER_DeleteTimer(tmr_id);
  }

  return status;
}

/* Resets the Host Controller's register */
static uint32_t SDMMC_BLOCK_SD_Reset(SDMMC_BLOCK_t *const obj, XMC_SDMMC_SW_RESET_t reset)
{
  SDMMC_BLOCK_MODE_STATUS_t status = SDMMC_BLOCK_MODE_STATUS_SUCCESS;

  XMC_SDMMC_SetSWReset(obj->sdmmc_sd->sdmmc, reset);

  SDMMC_BLOCK_SD_StartTimer(obj, (uint32_t)SDMMC_BLOCK_RESET_DELAY);
  if (obj->sdmmc_sd->tmr_id != 0U)
  {
    do
    {
      if (obj->sdmmc_sd->tmr_expire == (bool)0U)
      {
        status = (uint32_t)SDMMC_BLOCK_MODE_STATUS_TIMEOUT_OCCURED;
        break;
      }
    } while ((XMC_SDMMC_GetSWResetStatus(obj->sdmmc_sd->sdmmc)) & (reset)); //& (1U << reset));

    /* Stop timer and delete it */
    SDMMC_BLOCK_SD_StopTimer(obj);
    SYSTIMER_DeleteTimer(obj->sdmmc_sd->tmr_id);
  }

  return status;
}

/* Clears card specific structures and stops the SD clock */
void SDMMC_BLOCK_SD_CardCleanUp(SDMMC_BLOCK_t *const obj)
{
  memset((void *)&obj->sdmmc_sd->card_info, 0, sizeof(SDMMC_BLOCK_SD_CARD_INFORMATION_t));
  obj->card_type = (uint8_t)0;
  obj->sdmmc_sd->f8 = (uint8_t)0;
  obj->sdmmc_sd->cmd_int_err = SDMMC_BLOCK_MODE_STATUS_FAILURE;
  obj->sdmmc_sd->data_int_err = SDMMC_BLOCK_MODE_STATUS_FAILURE;
  obj->sdmmc_sd->err_recovery_stat = SDMMC_BLOCK_MODE_STATUS_FAILURE;
  obj->sdmmc_sd->transfer_int_err = SDMMC_BLOCK_MODE_STATUS_FAILURE;
  obj->card_state = (uint16_t)0;

  /* SD clock disable */
  XMC_SDMMC_SDClockDisable(obj->sdmmc_sd->sdmmc);
}

/* Check if CMD and DAT lines are free before issuing a command */
static uint32_t SDMMC_BLOCK_SD_CheckDataCommandLines(SDMMC_BLOCK_t *const obj, const XMC_SDMMC_COMMAND_t *cmd)
{
  uint32_t status = (uint32_t)SDMMC_BLOCK_MODE_STATUS_CMD_LINE_BUSY;

  /* Check if command line is not busy; then proceed */
  if (XMC_SDMMC_IsCommandLineBusy(obj->sdmmc_sd->sdmmc) == false)
  {
    status = SDMMC_BLOCK_MODE_STATUS_SUCCESS;
    if ((cmd->dat_present_sel == 1U) || (cmd->cmd_index == SDMMC_BLOCK_SEND_STATUS) || (cmd->response_type_sel == 3U))
    {
      if (XMC_SDMMC_IsDataLineBusy(obj->sdmmc_sd->sdmmc) != false)
      {
        status = SDMMC_BLOCK_MODE_STATUS_DATA_LINE_BUSY;
      }
      else
      {
        if ((cmd->dat_present_sel == 1U) || (cmd->response_type_sel == 3U))
        {
          /* Update data line state to active */
          obj->card_state |= (uint16_t)SDMMC_BLOCK_CARD_STATE_DATA_ACTIVE;
        }
      }
    }

    if (status == SDMMC_BLOCK_MODE_STATUS_SUCCESS)
    {
      /* Update command line state to active */
      obj->card_state |= SDMMC_BLOCK_CARD_STATE_CMD_ACTIVE;
    }
  }

  return status;
}

/* Check response error types in command's arguments category */
void SDMMC_BLOCK_SD_CheckArgumentError(const uint32_t *card_status, uint8_t *err)
{
  if ((*card_status & (uint32_t)SDMMC_BLOCK_SD_CSR_OUT_OF_RANGE_BITMASK) != (uint32_t)0U)
  {
    *err = (uint8_t)1U;
    XMC_DEBUG("SDMMC_BLOCK_SD_CheckArgumentError: Out of range error");
  }

  if ((*card_status & (uint32_t)SDMMC_BLOCK_SD_CSR_ADDRESS_ERROR_BITMASK) != (uint32_t)0U)
  {
    *err = (uint8_t)1U;
    XMC_DEBUG("SDMMC_BLOCK_SD_CheckArgumentError: Address error");
  }

  if ((*card_status & (uint32_t)SDMMC_BLOCK_SD_CSR_BLOCK_LEN_ERROR_BITMASK) != (uint32_t)0U)
  {
	*err = (uint8_t)1U;
	XMC_DEBUG("SDMMC_BLOCK_SD_CheckArgumentError: Block length error");
  }

  if ((*card_status & (uint32_t)SDMMC_BLOCK_SD_CSR_WP_VIOLATION_BITMASK) != (uint32_t)0U)
  {
	*err = (uint8_t)1U;
	XMC_DEBUG("SDMMC_BLOCK_SD_CheckArgumentError: Write protection violation error");
  }
}

/* Checks response error types in erase category */
void SDMMC_BLOCK_SD_CheckEraseError(const uint32_t *card_status, uint8_t *err)
{
  /* An error in the sequence of erase commands occurred.*/
  if ((*card_status & (uint32_t)SDMMC_BLOCK_SD_CSR_ERASE_SEQ_ERROR_BITMASK) != (uint32_t)0)
  {
    *err = (uint8_t)1U;
    XMC_DEBUG("SDMMC_BLOCK_SD_CheckEraseError: Sequential erase error");
  }

  /* An invalid selection of write-blocks for erase occurred */
  if ((*card_status & (uint32_t)SDMMC_BLOCK_SD_CSR_ERASE_PARAM_BITMASK) != (uint32_t)0)
  {
    *err = (uint8_t)1U;
    XMC_DEBUG("SDMMC_BLOCK_SD_CheckEraseError: Parameter erase error");
  }

  /*
   * Set when only partial address space was erased due to existing
   * write protected blocks OR the temporary/permanent write protected card
   * was erased
   */
  if ((*card_status & (uint32_t)SDMMC_BLOCK_SD_CSR_WP_ERASE_SKIP_BITMASK) != (uint32_t)0)
  {
    *err = (uint8_t)1U;
    XMC_DEBUG("SDMMC_BLOCK_SD_CheckEraseError: Write protection erase skip error");
  }
}

/* Check response error types in card's internal error category */
void SDMMC_BLOCK_SD_CheckCardError(const uint32_t *card_status, uint8_t *err)
{
  /* Card internal ECC was applied but failed to correct the data */
  if ((*card_status & (uint32_t)SDMMC_BLOCK_SD_CSR_CARD_ECC_FAILED_BITMASK) != (uint32_t)0U)
  {
    *err = (uint8_t)1U;
    XMC_DEBUG("SDMMC_BLOCK_SD_CheckCardError: Card ECC error");
  }

  /* Internal card controller error */
  if ((*card_status & (uint32_t)SDMMC_BLOCK_SD_CSR_CC_ERROR_BITMASK) != (uint32_t)0)
  {
    *err = (uint8_t)1U;
    XMC_DEBUG("SDMMC_BLOCK_SD_CheckCardError: Internal card controller error");
  }

  /* A general or an unknown error occurred during the operation */
  if ((*card_status & (uint32_t)SDMMC_BLOCK_SD_CSR_ERROR_BITMASK) != (uint32_t)0)
  {
    *err = (uint8_t)1U;
    XMC_DEBUG("SDMMC_BLOCK_SD_CheckCardError: Unknown error");
  }
}

/* Check for any error in the command's (received) response */
static uint32_t SDMMC_BLOCK_SD_CheckErrorInResponse(const uint32_t *card_status)
{
  uint32_t status = (uint32_t)SDMMC_BLOCK_MODE_STATUS_SUCCESS;
  uint8_t err = (uint8_t)0; /* No error */

  /* Check errors in arguments */
  SDMMC_BLOCK_SD_CheckArgumentError(card_status, &err);

  /* Check errors specific to erase operation */
  SDMMC_BLOCK_SD_CheckEraseError(card_status, &err);

  /* Check errors specific to the card */
  SDMMC_BLOCK_SD_CheckCardError(card_status, &err);

  /*
   * Set when a sequence or password error has been detected in
   * lock/unlock card command
   */
  if ((*card_status & (uint32_t)SDMMC_BLOCK_SD_CSR_LOCK_UNLOCK_FAILED_BITMASK) != (uint32_t)0)
  {
    err = (uint8_t)1;
    XMC_DEBUG("SDMMC_BLOCK_SD_CheckErrorInResponse: Lock/unlock error");
  }

  /*
   * Can be one of the following errors:
   * 1) The read only section of the CSD does not match the card content
   * 2) An attempt to reverse the copy or permanent WP bits was made
   */
  if ((*card_status & (uint32_t)SDMMC_BLOCK_SD_CSR_CSD_OVERWRITE_BITMASK) != (uint32_t)0)
  {
    err = (uint8_t)1;
    XMC_DEBUG("SDMMC_BLOCK_SD_CheckErrorInResponse: CSD overwrite error");
  }

  /* Error in the sequence of the authentication process */
  if ((*card_status & (uint32_t)SDMMC_BLOCK_SD_CSR_ASK_SEQ_ERROR_BITMASK) != (uint32_t)0)
  {
    err = (uint8_t)1;
    XMC_DEBUG("SDMMC_BLOCK_SD_CheckErrorInResponse: Authentication sequence error");
  }

  /* Some SD cards treat CMD55 as an illegal command */
  if (err == 1U)
  {
    status = (uint32_t)SDMMC_BLOCK_MODE_STATUS_FAILURE;
  }

  return status;
}

/* Check for lock status of SD card */
void SDMMC_BLOCK_SD_GetCardLockState(SDMMC_BLOCK_t *const obj, uint32_t card_status, uint16_t cmd_index)
{
  if (((card_status & (uint32_t)SDMMC_BLOCK_SD_CSR_CARD_IS_LOCKED_BITMASK) != (uint32_t)0) &&
      (cmd_index != (uint32_t)SDMMC_BLOCK_SEND_RELATIVE_ADDR))
  {
    obj->card_state |= (uint16_t)SDMMC_BLOCK_CARD_STATE_LOCKED;
  }
  else
  {
    obj->card_state &= (uint16_t)~SDMMC_BLOCK_CARD_STATE_LOCKED;
  }
}

/* Provide transfer delay */
uint32_t SDMMC_BLOCK_SD_TransferDelay(SDMMC_BLOCK_t *const obj, uint32_t delay)
{
  uint32_t status = (uint32_t)SDMMC_BLOCK_MODE_STATUS_SUCCESS;
  obj->sdmmc_sd->tmr_expire = (bool)1;

  /* Start timer */
  SDMMC_BLOCK_SD_StartTimer(obj, delay);
  if (obj->sdmmc_sd->tmr_id == 0U)
  {
    status = (uint32_t)SDMMC_BLOCK_MODE_STATUS_START_TIMER_FAILED;
  }

  if (status != (uint32_t)SDMMC_BLOCK_MODE_STATUS_START_TIMER_FAILED)
  {
    do
    {
      if (obj->sdmmc_sd->tmr_expire == (bool)0U)
      {
        status = (uint32_t)SDMMC_BLOCK_MODE_STATUS_TIMEOUT_OCCURED;
        break;
      }
    } while (obj->sdmmc_sd->isr_context.transfer_flag == (uint8_t)0U);

    obj->sdmmc_sd->isr_context.transfer_flag = (uint8_t)0U;

    /* Stop timer and delete it */
    SDMMC_BLOCK_SD_StopTimer(obj);
    SYSTIMER_DeleteTimer(obj->sdmmc_sd->tmr_id);
  }

  if (obj->sdmmc_sd->transfer_int_err != SDMMC_BLOCK_MODE_STATUS_TRANSFER_COMPLETE)
  {
    status = (uint32_t)obj->sdmmc_sd->data_int_err;
  }

  return status;
}

/* Read response received for the command issued */
static uint32_t SDMMC_BLOCK_SD_ReadResponse(SDMMC_BLOCK_t *const obj,
                                            const XMC_SDMMC_COMMAND_t *cmd,
                                            XMC_SDMMC_RESPONSE_TYPE_t resp_type,
                                            void *resp)
{
  uint32_t *ptr;
  uint32_t card_status = 0UL;
  uint32_t err_status = 0UL;
  uint32_t status = (uint32_t)SDMMC_BLOCK_MODE_STATUS_SUCCESS;

  /* Check for no-response type commands */
  if ((cmd->cmd_index == (uint16_t)SDMMC_BLOCK_GO_IDLE_STATE) ||
	  (cmd->cmd_index == (uint16_t)SDMMC_BLOCK_GO_INACTIVE_STATE))
  {
    status = (uint32_t)SDMMC_BLOCK_MODE_STATUS_SUCCESS;
  }
  else
  {
    ptr = (uint32_t *)resp;
    card_status = obj->sdmmc_sd->sdmmc->RESPONSE[0U];

    /* Check Lock Status */
    SDMMC_BLOCK_SD_GetCardLockState(obj, card_status, cmd->cmd_index);

    /* Check response type */
    switch (resp_type)
    {
      /* Response R1 */
      case XMC_SDMMC_RESPONSE_TYPE_R1:
        /* check the error bits in the response */
        *ptr = card_status;
        status = SDMMC_BLOCK_SD_CheckErrorInResponse(&card_status);
        break;

      /* Response R1b */
      case XMC_SDMMC_RESPONSE_TYPE_R1b:
        *ptr = card_status;

        status = SDMMC_BLOCK_SD_CheckErrorInResponse(&card_status);
        if (status != (uint32_t)SDMMC_BLOCK_MODE_STATUS_SUCCESS)
        {
          /* Wait for transfer complete interrupt */
          status = SDMMC_BLOCK_SD_TransferDelay(obj, (uint32_t)SDMMC_BLOCK_DELAY_IN_TRANSFER);
          if (status != (uint32_t)SDMMC_BLOCK_MODE_STATUS_SUCCESS)
          {
            XMC_DEBUG("SDMMC_BLOCK_ReadResponse: For R1b, SDMMC_BLOCK_TransferDelay failed");
          }
        }

        break;

      /* Response R2: response register R0-R7 */
      case XMC_SDMMC_RESPONSE_TYPE_R2:
        *ptr = card_status; ptr++;
        *ptr = obj->sdmmc_sd->sdmmc->RESPONSE[1U]; ptr++;
        *ptr = obj->sdmmc_sd->sdmmc->RESPONSE[2U]; ptr++;
        *ptr = obj->sdmmc_sd->sdmmc->RESPONSE[3U];

        break;

      /* Responses R3 and R7 */
      case XMC_SDMMC_RESPONSE_TYPE_R3:
      case XMC_SDMMC_RESPONSE_TYPE_R7:
        *ptr = card_status;
        break;

      /* Response R6 */
      case XMC_SDMMC_RESPONSE_TYPE_R6:
        err_status = card_status & (uint32_t)SDMMC_RESPONSE0_RESPONSE0_Msk;
        status = SDMMC_BLOCK_SD_CheckErrorInResponse(&err_status);

        /* Read 16-bit RCA received in response R1 register */
        *ptr = ((uint32_t)(card_status & (uint32_t)SDMMC_RESPONSE0_RESPONSE1_Msk) >> SDMMC_BLOCK_HC_RESPONSE1_BITPOS);
        break;

      /* No response */
      case XMC_SDMMC_RESPONSE_TYPE_NO_RESPONSE:
        status = (uint32_t)SDMMC_BLOCK_MODE_STATUS_SUCCESS;
        break;

      default:
        status = (uint32_t)SDMMC_BLOCK_MODE_STATUS_FAILURE;
        break;
    }
  }

  return status;
}

/* Send command */
static SDMMC_BLOCK_MODE_STATUS_t SDMMC_BLOCK_SD_SendCommand(SDMMC_BLOCK_t *const obj,
                                                            const XMC_SDMMC_COMMAND_t *cmd,
                                                            uint32_t arg,
                                                            XMC_SDMMC_RESPONSE_TYPE_t resp_type,
                                                            void *resp)
{
  SDMMC_BLOCK_MODE_STATUS_t status = (uint32_t)SDMMC_BLOCK_MODE_STATUS_FAILURE;

  obj->sdmmc_sd->issue_abort = (uint8_t)0U;
  obj->sdmmc_sd->cmd_int_err = SDMMC_BLOCK_MODE_STATUS_FAILURE;
  obj->sdmmc_sd->data_int_err = SDMMC_BLOCK_MODE_STATUS_FAILURE;

  /* Data or command line free? */
  status = SDMMC_BLOCK_SD_CheckDataCommandLines(obj, cmd);
  if (!((status == (uint32_t)SDMMC_BLOCK_MODE_STATUS_DATA_LINE_BUSY) ||
       (status == (uint32_t)SDMMC_BLOCK_MODE_STATUS_CMD_LINE_BUSY)))
  {
	/* Send command */
    XMC_SDMMC_SendCommand(obj->sdmmc_sd->sdmmc, cmd, arg);

    /* Block until any of the bit in the interrupt status register gets set */
    if (SDMMC_BLOCK_SD_StartTimer(obj, (uint32_t)SDMMC_BLOCK_DELAY_IN_COMMAND) == SDMMC_BLOCK_MODE_STATUS_SUCCESS)
    {
      do
      {
        if (obj->sdmmc_sd->tmr_expire == (bool)0)
        {
          XMC_DEBUG("SDMMC_BLOCK_SendCommand: Timeout occured");
          break;
        }
      } while (obj->sdmmc_sd->isr_context.cmd_flag == (uint8_t)0);

      obj->sdmmc_sd->isr_context.cmd_flag = (uint8_t)0;

      /* Stop timer and delete it */
      SDMMC_BLOCK_SD_StopTimer(obj);
      SYSTIMER_DeleteTimer(obj->sdmmc_sd->tmr_id);

      /* Check for possible errors */
      if (obj->sdmmc_sd->cmd_int_err == SDMMC_BLOCK_MODE_STATUS_COMMAND_COMPLETE)
      {
        /* Read response received */
        status = SDMMC_BLOCK_SD_ReadResponse(obj, cmd, resp_type, resp);
      }
      /* For cmd8, check for cmd timeout interrupt */
      else if ((obj->sdmmc_sd->cmd_int_err == SDMMC_BLOCK_MODE_STATUS_COMMAND_TIMEOUT_ERROR) &&
  			   (cmd->cmd_index == (uint16_t)SDMMC_BLOCK_SD_SEND_IF_COND))
      {
        status = (uint32_t)SDMMC_BLOCK_MODE_STATUS_COMMAND_TIMEOUT_ERROR;
      }
      else
      {
        if (cmd->dat_present_sel == (uint16_t)1)
        {
          obj->sdmmc_sd->issue_abort = (uint8_t)1;
        }

        /* Error Recovery for the failed command  */
        status = SDMMC_BLOCK_SD_ErrorInterruptRecovery(obj);
      }
    }
  }

  return status;
}

/* Set voltage window in the OCR register */
uint32_t SDMMC_BLOCK_SD_SetVoltageWindow(SDMMC_BLOCK_t *const obj)
{
  uint32_t status = (uint32_t)SDMMC_BLOCK_MODE_STATUS_FAILURE;
  uint32_t card_status = 0U;
  uint32_t loop_count = 0U;
  uint32_t arg = 0U;

  if (obj->sdmmc_sd->f8 == (uint8_t)0U)
  {
    arg = SDMMC_BLOCK_SD_ACMD41_F80_ARG; /* Set HCS=0 for standard cards */
  }
  else
  {
    arg = SDMMC_BLOCK_SD_ACMD41_F81_ARG; /* Set HCS=1 for high capacity cards */
  }

  do
  {
    /* Send CMD55 for application specific commands (default RCA: 0) */
    status = SDMMC_BLOCK_SD_SendCommand(obj,
                                        &(SDMMC_BLOCK_COMMON_COMMAND(55)),
                                        SDMMC_BLOCK_ARGUMENT0,
                                        XMC_SDMMC_RESPONSE_TYPE_R1,
                                        &card_status);

    if (status == (uint32_t)SDMMC_BLOCK_MODE_STATUS_SUCCESS)
    {
      /* Send ACMD41 to set card's voltage window */
      status = SDMMC_BLOCK_SD_SendCommand(obj,
                                          &(SDMMC_BLOCK_SD_COMMAND(62)),
                                          arg,
                                          XMC_SDMMC_RESPONSE_TYPE_R3,
                                          &(obj->sdmmc_sd->card_info.ocr));

      if ((status != (uint32_t)SDMMC_BLOCK_MODE_STATUS_SUCCESS) &&
          (status != (uint32_t)SDMMC_BLOCK_MODE_STATUS_ILLEGAL_COMMAND_ERROR))
      {
        break;
      }
      status = (uint32_t)SDMMC_BLOCK_MODE_STATUS_SUCCESS;

      /* Card takes some time to set power status bit. Card must respond in a second */
      SDMMC_BLOCK_SD_Delay(obj, (uint32_t)SDMMC_BLOCK_CARD_POWER_DELAY);
    }
    else
    {
      loop_count = 100U;
    }
  } while(((loop_count++) < (uint32_t)50U) &&
		  (!(((uint32_t)obj->sdmmc_sd->card_info.ocr &
           (uint32_t)SDMMC_BLOCK_OCR_POWER_STATUS_BITMASK)!= (uint32_t)0UL)));

  return status;
}

/* Query voltage operating condition of the card */
SDMMC_BLOCK_MODE_STATUS_t SDMMC_BLOCK_SD_QueryOperatingCondition(SDMMC_BLOCK_t *const obj)
{
  uint32_t resp_data = 0U;
  SDMMC_BLOCK_MODE_STATUS_t status;

  /* Query voltage operating condition (cmd8) */
  status = SDMMC_BLOCK_SD_SendCommand(obj,
                                      &(SDMMC_BLOCK_SD_COMMAND(8)),
                                      SDMMC_BLOCK_SD_CMD8_ARG,
                                      XMC_SDMMC_RESPONSE_TYPE_R7,
                                      &resp_data);

  if (status == (uint32_t)SDMMC_BLOCK_MODE_STATUS_SUCCESS)
  {
    /* Check if pattern matches in both the argument and response */
    if (((resp_data >> SDMMC_BLOCK_SD_CMD8_CHECK_PATTERN_BITPOS) & SDMMC_BLOCK_SD_CMD8_CHECK_PATTERN_BITMASK) !=
        (SDMMC_BLOCK_SD_CMD8_CHECK_PATTERN_VALUE))
    {
      status = SDMMC_BLOCK_MODE_STATUS_BAD_RESPONSE;
    }
    /* Check if input voltage accepted by the card in the response  */
    else if (((uint8_t)(resp_data >> SDMMC_BLOCK_SD_CMD8_VHS_BITPOS) & SDMMC_BLOCK_SD_CMD8_VHS_BITMASK) !=
             (SDMMC_BLOCK_SD_VHS_PATTERN_2_7_3_6_VALUE))
    {
      status = SDMMC_BLOCK_MODE_STATUS_BAD_RESPONSE;
    }
    else
    {
      /* Set Flag f8 */
      obj->sdmmc_sd->f8 = (uint8_t)1U;
    }
  }
  /* Response received; High capacity cards */
  else
  {
    /*  No response is received for Standard Capacity SD cards or MMC card. */
    if (obj->sdmmc_sd->cmd_int_err == SDMMC_BLOCK_MODE_STATUS_COMMAND_TIMEOUT_ERROR)
    {
      obj->sdmmc_sd->f8 = (uint8_t)0U;
      status = SDMMC_BLOCK_MODE_STATUS_SUCCESS;
    }
  }

  return status;
}

/* Get card type */
static void SDMMC_BLOCK_SD_WriteCardType(SDMMC_BLOCK_t *const obj)
{
  /* If F8=0; standard capacity v1 card */
  if (obj->sdmmc_sd->f8 == (uint8_t)0U)
  {
    obj->card_type |= (uint8_t)SDMMC_BLOCK_CARD_TYPE_STANDARD_CAPACITY_V1X;
  }
  /* If F8=1; standard capacity v2 or high capacity card */
  else
  {
    /* Check CCS bit in the OCR register; CCS=1 implies a high capacity card */
    if (((uint32_t)obj->sdmmc_sd->card_info.ocr & (uint32_t)SDMMC_BLOCK_OCR_CCS_BITMASK) != (uint32_t)0U)
    {
      obj->card_type |= (SDMMC_BLOCK_CARD_TYPE_HIGH_CAPACITY |
                         SDMMC_BLOCK_CARD_TYPE_BLOCK_ADDRESSING);
    }
    else
    {
      /* CCS=0 implies standard capacity v2 */
      obj->card_type |= SDMMC_BLOCK_CARD_TYPE_STANDARD_CAPACITY_V2;
    }
  }
}

/* Query voltage supported from the card */
SDMMC_BLOCK_MODE_STATUS_t SDMMC_BLOCK_SD_QueryVoltage(SDMMC_BLOCK_t *const obj, uint32_t arg)
{
  uint32_t card_status = 0U;
  SDMMC_BLOCK_MODE_STATUS_t status;

  /* Send CMD55 for application specific commands with 0 as the default RCA */
  status = SDMMC_BLOCK_SD_SendCommand(obj,
                                      &(SDMMC_BLOCK_COMMON_COMMAND(55)),
		                              arg,
		                              XMC_SDMMC_RESPONSE_TYPE_R1,
                                      &card_status);

  if (((obj->sdmmc_sd->f8 == (uint8_t)0U) && (status == SDMMC_BLOCK_MODE_STATUS_ILLEGAL_COMMAND_ERROR)) ||
      (status == SDMMC_BLOCK_MODE_STATUS_SUCCESS))
  {
    /* Send ACMD41 to query the card's voltage window */
    status = SDMMC_BLOCK_SD_SendCommand(obj,
    		                            &(SDMMC_BLOCK_SD_COMMAND(62)),
    		                            arg,
    		                            XMC_SDMMC_RESPONSE_TYPE_R3,
                                        &(obj->sdmmc_sd->card_info.ocr));

    if ((status == (uint32_t)SDMMC_BLOCK_MODE_STATUS_ILLEGAL_COMMAND_ERROR) ||
    	(status == (uint32_t)SDMMC_BLOCK_MODE_STATUS_SUCCESS))
    {
      /* Send ACMD41 with voltage window argument set */
      status = SDMMC_BLOCK_SD_SetVoltageWindow(obj);
      if (status == (uint32_t)SDMMC_BLOCK_MODE_STATUS_SUCCESS)
      {
        /* SD Card Type */
        SDMMC_BLOCK_SD_WriteCardType(obj);
      }
    }
  }

  return status;
}

/* Get SD status information */
SDMMC_BLOCK_MODE_STATUS_t SDMMC_BLOCK_SD_GetSdStatus(SDMMC_BLOCK_t *const obj, void *buf)
{
  uint32_t arg = 0U;
  uint32_t card_status = 0U;
  SDMMC_BLOCK_MODE_STATUS_t status = SDMMC_BLOCK_MODE_STATUS_FAILURE;

  /* Select the card (CMD7) */
  status = SDMMC_BLOCK_SD_SwitchToTransferState(obj);
  if (status == SDMMC_BLOCK_MODE_STATUS_SUCCESS)
  {
    /* Send CMD55 (application specific command) */
    arg |= (uint32_t)((uint32_t)obj->sdmmc_sd->card_info.rca << (uint32_t)SDMMC_BLOCK_ARG_RCA_BITPOS);

    status = SDMMC_BLOCK_SD_SendCommand(obj,
                                        &(SDMMC_BLOCK_COMMON_COMMAND(55)),
                                        arg,
                                        XMC_SDMMC_RESPONSE_TYPE_R1,
                                        &card_status);

    if (status == SDMMC_BLOCK_MODE_STATUS_SUCCESS)
    {
      /* Set transfer mode */
      XMC_SDMMC_SetDataTransferDirection(obj->sdmmc_sd->sdmmc, XMC_SDMMC_DATA_TRANSFER_CARD_TO_HOST);

      /* Read the SD status from the data line */
      status = SDMMC_BLOCK_SD_SingleBlockTransfer(obj,
                                                  &(SDMMC_BLOCK_SD_COMMAND(59)),
                                                  (uint32_t)SDMMC_BLOCK_ARGUMENT0,
                                                  (uint16_t)64U,
                                                  (uint32_t *)buf,
                                                  SDMMC_BLOCK_SD_DATA_TRANSFER_READ_BUFFER);
    }
  }

  return status;
}

/* Check write protection status of card */
static SDMMC_BLOCK_MODE_STATUS_t SDMMC_BLOCK_SD_GetWriteProtect(SDMMC_BLOCK_t *const obj)
{
  uint32_t sd_status[16] = {0U};
  uint32_t write_protect;
  SDMMC_BLOCK_MODE_STATUS_t status = SDMMC_BLOCK_MODE_STATUS_FAILURE;

  status = SDMMC_BLOCK_SD_GetSdStatus(obj, (void *)&(sd_status[0]));
  if (status == SDMMC_BLOCK_MODE_STATUS_SUCCESS)
  {
    /* Bits 480:495 in the SD status provides write protection information */
    write_protect = ((sd_status[0] & 0xFF000000U) >> 24U) | (((sd_status[0] & 0x00FF0000U) >> 16U) << 8U);
    if ((write_protect & SDMMC_BLOCK_SD_CARD_TYPE_BITMASK) != 0U)
    {
      obj->card_state |= (uint16_t)SDMMC_BLOCK_CARD_STATE_WRITE_PROTECTED;
    }
  }

  return status;
}

/* Read the CSD, SCR and Write protection status of the card */
SDMMC_BLOCK_MODE_STATUS_t SDMMC_BLOCK_SD_ReadCardRegisters(SDMMC_BLOCK_t *const obj)
{
  uint32_t arg = 0U;
  uint32_t card_status = 0U;
  SDMMC_BLOCK_MODE_STATUS_t status;
  SDMMC_BLOCK_SCR_t scr_content = {0U};

  /* Read CSD Register  */
  arg |= obj->sdmmc_sd->card_info.rca << SDMMC_BLOCK_ARG_RCA_BITPOS;

  status = SDMMC_BLOCK_SD_SendCommand(obj,
                                      &(SDMMC_BLOCK_COMMON_COMMAND(9)),
                                      arg,
                                      XMC_SDMMC_RESPONSE_TYPE_R2,
                                      (void *)obj->sdmmc_sd->card_info.csd);

  if (status == SDMMC_BLOCK_MODE_STATUS_SUCCESS)
  {
    /* Set write protection flags */
    status = SDMMC_BLOCK_SD_GetWriteProtect(obj);

    if (status == SDMMC_BLOCK_MODE_STATUS_SUCCESS)
    {
      /* Read SCR register for SD card */
      if ((obj->card_type & SDMMC_BLOCK_CARD_TYPE_MMC) == 0U)
      {
        /* Switch to Transferring State. */
        status = SDMMC_BLOCK_SD_SwitchToTransferState(obj);

        if (status == SDMMC_BLOCK_MODE_STATUS_SUCCESS)
        {
          /* Send application specific command CMD55 */
          arg |= (uint32_t)((uint32_t)obj->sdmmc_sd->card_info.rca << (uint32_t)SDMMC_BLOCK_ARG_RCA_BITPOS);

          status = SDMMC_BLOCK_SD_SendCommand(obj,
                                              &(SDMMC_BLOCK_COMMON_COMMAND(55)),
                                              arg,
                                              XMC_SDMMC_RESPONSE_TYPE_R1,
                                              &card_status);

          if (status == SDMMC_BLOCK_MODE_STATUS_SUCCESS)
          {
            /* Set direction select bit */
            XMC_SDMMC_SetDataTransferDirection(obj->sdmmc_sd->sdmmc, XMC_SDMMC_DATA_TRANSFER_CARD_TO_HOST);

            /* Read the transferred SCR data */
            status = SDMMC_BLOCK_SD_SingleBlockTransfer(obj,
                                                        &(SDMMC_BLOCK_SD_COMMAND(64)),
                                                        (uint32_t)SDMMC_BLOCK_ARGUMENT0,
                                                        (uint16_t)8,
                                                        (uint32_t *)&scr_content,
                                                        SDMMC_BLOCK_SD_DATA_TRANSFER_READ_BUFFER);

            obj->sdmmc_sd->card_info.scr = scr_content;
          }
        }
      }
    }
  }

  return status;
}

/* Read card registers after the card initialization */
SDMMC_BLOCK_MODE_STATUS_t SDMMC_BLOCK_SD_AfterCardInitialize(SDMMC_BLOCK_t *const obj)
{
  SDMMC_BLOCK_MODE_STATUS_t status = SDMMC_BLOCK_MODE_STATUS_FAILURE;

  /* Read CSD & SCR register & card write protection flags */
  status = SDMMC_BLOCK_SD_ReadCardRegisters(obj);

  if (status == SDMMC_BLOCK_MODE_STATUS_SUCCESS)
  {
#if SDMMC_BLOCK_SD_SUPPORT_4_BUS_WIDTH
    /* Switch to 4-bit bus width if supported */
    status = SDMMC_BLOCK_SD_SwitchBusWidth(obj);

    if (status != SDMMC_BLOCK_MODE_STATUS_SUCCESS)
    {
      /* Switch to default (1-bit) bus width */
      XMC_SDMMC_SetDataTransferWidth(obj->sdmmc_sd->sdmmc, XMC_SDMMC_DATA_LINES_1);
    }

    /* Switch to high speed mode */
    status = SDMMC_BLOCK_SD_SwitchSpeed(obj);
    if (status != (uint32_t)SDMMC_BLOCK_MODE_STATUS_SUCCESS)
    {
      /* Switch host controller to normal (default) speed mode */
      XMC_SDMMC_DisableHighSpeed(obj->sdmmc_sd->sdmmc);
      status = SDMMC_BLOCK_MODE_STATUS_SUCCESS;
    }
#endif
  }

  return status;
}

/* Reads RCA (relative card address) of the card */
static uint32_t SDMMC_BLOCK_SD_ReadRCA(SDMMC_BLOCK_t *const obj)
{
  uint32_t status;

  status = SDMMC_BLOCK_SD_SendCommand(obj,
                                      &(SDMMC_BLOCK_COMMON_COMMAND(3)),
                                      SDMMC_BLOCK_ARGUMENT0,
                                      XMC_SDMMC_RESPONSE_TYPE_R6,
                                      &(obj->sdmmc_sd->card_info.rca));
  return status;
}

/* Initialize the SD card */
static SDMMC_BLOCK_MODE_STATUS_t SDMMC_BLOCK_SD_InitializeCard(SDMMC_BLOCK_t *const obj)
{
  SDMMC_BLOCK_MODE_STATUS_t status;
  SDMMC_BLOCK_MODE_STATUS_t lock_status;
  uint8_t count = (uint8_t)0U;

  /* Repeat the below steps 2 times if bad response is received */
  do
  {
    /* Reset the card (CMD0) */
    status = SDMMC_BLOCK_SD_SendCommand(obj,
    		                            &(SDMMC_BLOCK_COMMON_COMMAND(0)),
                                        SDMMC_BLOCK_ARGUMENT0,
                                        XMC_SDMMC_RESPONSE_TYPE_NO_RESPONSE,
                                        NULL);

    if (status != SDMMC_BLOCK_MODE_STATUS_SUCCESS)
    {
      break;
    }

    /* Query card's operation condition */
    status = SDMMC_BLOCK_SD_QueryOperatingCondition(obj);

    count++;
  } while((count < (uint8_t)SDMMC_BLOCK_NUM_CARD_RESET_RETRIES) &&
          (status == SDMMC_BLOCK_MODE_STATUS_BAD_RESPONSE));

  if (status == SDMMC_BLOCK_MODE_STATUS_SUCCESS)
  {
    /* Query and set voltage window  */
    status = SDMMC_BLOCK_SD_QueryVoltage(obj, (uint32_t)obj->sdmmc_sd->card_info.rca);

    if (status == SDMMC_BLOCK_MODE_STATUS_SUCCESS)
    {
      /* Read CID */
      status = SDMMC_BLOCK_SD_SendCommand(obj,
                                          &(SDMMC_BLOCK_COMMON_COMMAND(2)),
                                          SDMMC_BLOCK_ARGUMENT0,
                                          XMC_SDMMC_RESPONSE_TYPE_R2,
                                          (void *)obj->sdmmc_sd->card_info.cid);

      if (status == SDMMC_BLOCK_MODE_STATUS_SUCCESS)
      {
        /* Read RCA */
        status = SDMMC_BLOCK_SD_ReadRCA(obj);
        if (status == SDMMC_BLOCK_MODE_STATUS_SUCCESS)
        {
          /* Check card lock/unlock status */
          status = SDMMC_BLOCK_SD_GetLockStatus(obj, &lock_status);
          if (status == SDMMC_BLOCK_MODE_STATUS_SUCCESS)
          {
            if (lock_status == (uint32_t)SDMMC_BLOCK_MODE_STATUS_CARD_IS_LOCKED)
            {
              obj->card_state |= (uint16_t)SDMMC_BLOCK_CARD_STATE_LOCKED;
              status = SDMMC_BLOCK_MODE_STATUS_INITIALIZED_BUT_LOCKED;
            }

            /* Update card initialization status */
            obj->card_state &= (uint8_t)~(SDMMC_BLOCK_CARD_STATE_NOT_INITIALIZED |
                                          SDMMC_BLOCK_CARD_STATE_NO_CARD);
          }
        }
      }
    }
  }

  return status;
}

/* Configure the registers for a single block transfer */
SDMMC_BLOCK_MODE_STATUS_t SDMMC_BLOCK_SD_ConfigureSingleBlockTransfer(SDMMC_BLOCK_t *const obj,
                                                                      const XMC_SDMMC_COMMAND_t *cmd,
                                                                      uint32_t arg,
                                                                      uint16_t block_size)
{
  SDMMC_BLOCK_MODE_STATUS_t status = SDMMC_BLOCK_MODE_STATUS_FAILURE;
  uint32_t card_status = 0U;
  XMC_SDMMC_TRANSFER_MODE_t response;

  response.block_size = block_size;
  response.type = XMC_SDMMC_TRANSFER_MODE_TYPE_SINGLE;
  response.auto_cmd = XMC_SDMMC_TRANSFER_MODE_AUTO_CMD_DISABLED;

  XMC_SDMMC_SetDataTransferMode(obj->sdmmc_sd->sdmmc, &response);

  status = SDMMC_BLOCK_SD_SendCommand(obj, cmd, arg, XMC_SDMMC_RESPONSE_TYPE_R1, &card_status);

  return status;
}

/* Configure the registers for a multi-block transfer */
static SDMMC_BLOCK_MODE_STATUS_t SDMMC_BLOCK_SD_ConfigureMultiBlockTransfer(SDMMC_BLOCK_t *const obj,
		                                                                    uint32_t *arg,
                                                                            uint32_t num_blocks,
                                                                            const XMC_SDMMC_COMMAND_t *cmd)
{
  SDMMC_BLOCK_MODE_STATUS_t status;
  uint32_t card_status = 0U;
  XMC_SDMMC_TRANSFER_MODE_t response;

  /* Block addressing */
  if ((obj->card_type & SDMMC_BLOCK_CARD_TYPE_BLOCK_ADDRESSING) == (uint32_t)0U)
  {
    *arg *= (uint32_t)512U;
  }

  response.block_size = SDMMC_BLOCK_TX_BLOCK_SIZE_VALUE;
  response.num_blocks = num_blocks;
  response.type = XMC_SDMMC_TRANSFER_MODE_TYPE_MULTIPLE;
  response.auto_cmd = XMC_SDMMC_TRANSFER_MODE_AUTO_CMD_12;

  XMC_SDMMC_SetDataTransferMode(obj->sdmmc_sd->sdmmc, &response);

  /* Enable ACMD 12 interrupt signal */
  XMC_SDMMC_EnableEvent(obj->sdmmc_sd->sdmmc, XMC_SDMMC_ACMD_ERR);

  /* Send multiple block transfer command */
  status = SDMMC_BLOCK_SD_SendCommand(obj, cmd, *arg, XMC_SDMMC_RESPONSE_TYPE_R1, &card_status);

  return status;
}

/* Do data transfer to OR from card */
SDMMC_BLOCK_MODE_STATUS_t SDMMC_BLOCK_SD_DataTransfer(SDMMC_BLOCK_t *const obj,
                                                      uint32_t *buf,
                                                      SDMMC_BLOCK_SD_DATA_TRANSFER_t transfer_mode,
                                                      uint32_t quad_bytes)
{
  SDMMC_BLOCK_MODE_STATUS_t status = SDMMC_BLOCK_MODE_STATUS_FAILURE;
  uint32_t count = 0U;

  /* Block on buffer read/write ready interrupt */
  status = SDMMC_BLOCK_SD_StartTimer(obj, (uint32_t)SDMMC_BLOCK_RESET_IN_DATA_TRANSFER);
  if (status == SDMMC_BLOCK_MODE_STATUS_SUCCESS)
  {
    do
    {
      if (obj->sdmmc_sd->tmr_expire == (bool)0U)
      {
        status = SDMMC_BLOCK_MODE_STATUS_TIMEOUT_OCCURED;
        break;
      }
    } while(obj->sdmmc_sd->isr_context.data_flag == 0U);

    /* Stop timer and delete it */
    SDMMC_BLOCK_SD_StopTimer(obj);
    SYSTIMER_DeleteTimer(obj->sdmmc_sd->tmr_id);

    obj->sdmmc_sd->isr_context.data_flag = (uint8_t)0U;

    /* Check if buffer is ready */
    if (obj->sdmmc_sd->data_int_err == SDMMC_BLOCK_MODE_STATUS_BUFFER_READY)
    {
      /* 4 bytes data transmission in each iteration */
      for (count = 0U; count < quad_bytes; count++)
      {
        if (transfer_mode == SDMMC_BLOCK_SD_DATA_TRANSFER_READ_BUFFER)
        {
          *buf = XMC_SDMMC_ReadFIFO(obj->sdmmc_sd->sdmmc);
        }

        if (transfer_mode == SDMMC_BLOCK_SD_DATA_TRANSFER_WRITE_BUFFER)
        {
          XMC_SDMMC_WriteFIFO(obj->sdmmc_sd->sdmmc, buf);
        }

        buf++;
      }
      status = SDMMC_BLOCK_MODE_STATUS_SUCCESS;
    }
    else
    {
      obj->sdmmc_sd->issue_abort = (uint8_t)1U;
      status = SDMMC_BLOCK_SD_ErrorInterruptRecovery(obj);
    }
  }

  return status;
}

/* Transfer multiple blocks of data */
SDMMC_BLOCK_MODE_STATUS_t SDMMC_BLOCK_SD_MultiBlockTransfer(SDMMC_BLOCK_t *const obj,
                                                            uint32_t *addr,
                                                            uint32_t num_blocks,
                                                            const XMC_SDMMC_COMMAND_t *cmd,
                                                            uint32_t *buf,
                                                            SDMMC_BLOCK_SD_DATA_TRANSFER_t transfer_mode)
{
  SDMMC_BLOCK_MODE_STATUS_t status;
  obj->sdmmc_sd->transfer_int_err = SDMMC_BLOCK_MODE_STATUS_FAILURE;

  /* Configure registers for Multi block transfer*/
  status = SDMMC_BLOCK_SD_ConfigureMultiBlockTransfer(obj, addr, num_blocks, cmd);
  if (status == SDMMC_BLOCK_MODE_STATUS_SUCCESS)
  {
    /* Read/write block data */
    while (num_blocks > 0U)
    {
      /* Perform Transfer */
      status = SDMMC_BLOCK_SD_DataTransfer(obj, buf, transfer_mode, SDMMC_BLOCK_NUM_QUADLETS_IN_BLOCK);
      if (status != SDMMC_BLOCK_MODE_STATUS_SUCCESS)
      {
        break;
      }
      /* Decrement number of blocks */
      num_blocks--;
      /* Pointer pointing to the next block pointer */
      buf += (uint32_t)SDMMC_BLOCK_NUM_QUADLETS_IN_BLOCK;
    }

    if (status == SDMMC_BLOCK_MODE_STATUS_SUCCESS)
    {
      /* Block on transfer complete interrupt */
      /* Timeout: 5ms */
      status = SDMMC_BLOCK_SD_TransferDelay(obj, SDMMC_BLOCK_DELAY_IN_TRANSFER);
      if (status == SDMMC_BLOCK_MODE_STATUS_SUCCESS)
      {
        /* Check if transfer happened successfully; Check ACMD status */
        if (obj->sdmmc_sd->acmd_int_err == SDMMC_BLOCK_MODE_STATUS_ACMD12_ERROR)
        {
          /* Call ACMD12 error recovery */
          SDMMC_BLOCK_SD_ACMDErrorRecovery(obj);
        }
      }
    }
  }
  return status;
}

/* Performs single block transfer */
SDMMC_BLOCK_MODE_STATUS_t SDMMC_BLOCK_SD_SingleBlockTransfer(SDMMC_BLOCK_t *const obj,
                                                             const XMC_SDMMC_COMMAND_t *cmd,
                                                             uint32_t arg,
                                                             uint16_t block_size,
                                                             uint32_t *buf,
															 SDMMC_BLOCK_SD_DATA_TRANSFER_t transfer_mode)
{
  SDMMC_BLOCK_MODE_STATUS_t status;

  status = SDMMC_BLOCK_SD_ConfigureSingleBlockTransfer(obj, cmd, arg, block_size);
  if (status == SDMMC_BLOCK_MODE_STATUS_SUCCESS)
  {
    /* Perform data transfer */
    status = SDMMC_BLOCK_SD_DataTransfer(obj, buf, transfer_mode, (uint32_t)((uint32_t)block_size / 4UL));
    if (status == SDMMC_BLOCK_MODE_STATUS_SUCCESS)
    {
      /* Block on transfer complete interrupt */
      status = SDMMC_BLOCK_SD_StartTimer(obj, SDMMC_BLOCK_DELAY_IN_TRANSFER);
      if (status != SDMMC_BLOCK_MODE_STATUS_SUCCESS)
      {
        status = SDMMC_BLOCK_MODE_STATUS_TIMEOUT_OCCURED;
      }
      else
      {
        do
        {
          if (obj->sdmmc_sd->tmr_expire == (bool)0U)
          {
            status = SDMMC_BLOCK_MODE_STATUS_TIMEOUT_OCCURED;
            break;
          }
        } while (obj->sdmmc_sd->isr_context.transfer_flag == (uint8_t)0U);

        /* Stop timer and delete it */
        SDMMC_BLOCK_SD_StopTimer(obj);
        SYSTIMER_DeleteTimer(obj->sdmmc_sd->tmr_id);

        obj->sdmmc_sd->isr_context.transfer_flag = 0U;

        /* Check transfer complete status */
        if (obj->sdmmc_sd->transfer_int_err == SDMMC_BLOCK_MODE_STATUS_TRANSFER_COMPLETE)
        {
          status = SDMMC_BLOCK_MODE_STATUS_SUCCESS;
        }
        else
        {
          obj->sdmmc_sd->issue_abort = (uint8_t)1U;
          status = SDMMC_BLOCK_SD_ErrorInterruptRecovery(obj);
        }
      }
    }
  }

  return status;
}

/* Check lock status */
SDMMC_BLOCK_MODE_STATUS_t SDMMC_BLOCK_SD_CheckLockStatus(SDMMC_BLOCK_t *const obj, SDMMC_BLOCK_CARD_LOCK_MODE_t mode)
{
  SDMMC_BLOCK_MODE_STATUS_t status;
  SDMMC_BLOCK_MODE_STATUS_t lock_status = 0U;

  status = SDMMC_BLOCK_SD_GetLockStatus(obj, &lock_status);
  /* For lock, card state must be "locked" */
  if (status == (uint32_t)SDMMC_BLOCK_MODE_STATUS_SUCCESS)
  {
    if ((lock_status == (uint32_t)SDMMC_BLOCK_MODE_STATUS_CARD_IS_LOCKED) && (mode == SDMMC_BLOCK_CARD_LOCK))
    {
      status = SDMMC_BLOCK_MODE_STATUS_SUCCESS;
    }
    /* For unlock, card state must be "unlocked" */
    else if ((lock_status == (uint32_t)SDMMC_BLOCK_MODE_STATUS_CARD_UNLOCKED) && (mode == SDMMC_BLOCK_CARD_UNLOCK))
    {
      status = SDMMC_BLOCK_MODE_STATUS_SUCCESS;
    }
    else
    {
      status = SDMMC_BLOCK_MODE_STATUS_LOCK_UNLOCK_ERROR;
    }
  }

  return status;
}

/* Switch bus width to 4-bit if supported */
SDMMC_BLOCK_MODE_STATUS_t SDMMC_BLOCK_SD_SwitchBusWidth(SDMMC_BLOCK_t *const obj)
{
  uint32_t arg = 0U;
  SDMMC_BLOCK_MODE_STATUS_t status = SDMMC_BLOCK_MODE_STATUS_FAILURE;
  uint32_t card_status = 0U;

  /* Switch to transfer state (CMD7) */
  status = SDMMC_BLOCK_SD_SwitchToTransferState(obj);

  if (status == SDMMC_BLOCK_MODE_STATUS_SUCCESS)
  {
    /* Disable card insertion interrupt */
    XMC_SDMMC_DisableEvent(obj->sdmmc_sd->sdmmc, XMC_SDMMC_CARD_INS);

    /* Check data transfer width supported in SCR register */
    if ((obj->sdmmc_sd->card_info.scr.sd_bus_width & SDMMC_BLOCK_SCR_BUS_WIDTH4_BITMASK))
    {
      /* Set the argument */
      arg |= ((uint32_t)obj->sdmmc_sd->card_info.rca << (uint32_t)SDMMC_BLOCK_ARG_RCA_BITPOS);

      /* Send application specific command */
      status = SDMMC_BLOCK_SD_SendCommand(obj,
    		                              &(SDMMC_BLOCK_COMMON_COMMAND(55)),
                                          arg,
                                          XMC_SDMMC_RESPONSE_TYPE_R1,
                                          &card_status);

      if (status == (uint32_t)SDMMC_BLOCK_MODE_STATUS_SUCCESS)
      {
        /* Send ACMD6 to switch the bus width */
        status = SDMMC_BLOCK_SD_SendCommand(obj,
        		                            &(SDMMC_BLOCK_SD_COMMAND(58)),
                                            SDMMC_BLOCK_SD_4BUS_WIDTH_ARG,
                                            XMC_SDMMC_RESPONSE_TYPE_R1,
                                            &card_status);
      }
    }

    if (status == SDMMC_BLOCK_MODE_STATUS_SUCCESS)
    {
      /* Set data transfer width */
      XMC_SDMMC_SetDataTransferWidth(obj->sdmmc_sd->sdmmc, XMC_SDMMC_DATA_LINES_4);
    }
  }

  return status;
}

/* Switch the card speed mode to high speed if supported */
SDMMC_BLOCK_MODE_STATUS_t SDMMC_BLOCK_SD_SwitchSpeed(SDMMC_BLOCK_t *const obj)
{
  uint32_t switch_status[16] = {0U};
  SDMMC_BLOCK_MODE_STATUS_t status = SDMMC_BLOCK_MODE_STATUS_FAILURE;

  /* Check CMD6 support in SCR register */
  if (obj->sdmmc_sd->card_info.scr.sd_spec != 0UL)
  {
    /* Switch to transfer state (CMD7) */
    status = SDMMC_BLOCK_SD_SwitchToTransferState(obj);

    if (status == SDMMC_BLOCK_MODE_STATUS_SUCCESS)
    {
      /* Send the Switch function  command and read the transferred block of
       * data from the card */
      status = SDMMC_BLOCK_SD_SingleBlockTransfer(obj,
                                                  &(SDMMC_BLOCK_SD_COMMAND(6)),
                                                  SDMMC_BLOCK_SD_HIGH_SPEED_ARG,
                                                  64,
                                                  (uint32_t *)switch_status,
                                                  SDMMC_BLOCK_SD_DATA_TRANSFER_READ_BUFFER);

      if (status == (uint32_t)SDMMC_BLOCK_MODE_STATUS_SUCCESS)
      {
        if (((switch_status[4] & (uint32_t)SDMMC_BLOCK_SWITCH_FUNC_GRP1_STATUS_BITMASK) >>
             (uint32_t)SDMMC_BLOCK_SWITCH_FUNC_GRP1_STATUS_BITPOS) != (uint32_t)1U)
        {
          status = (uint32_t)SDMMC_BLOCK_MODE_STATUS_FAILURE;
        }
      }

      if (status == (uint32_t)SDMMC_BLOCK_MODE_STATUS_SUCCESS)
      {
        /* Change speed mode (high speed) in the host controller */
        XMC_SDMMC_EnableHighSpeed(obj->sdmmc_sd->sdmmc);
      }
    }
  }

  return status;
}

/* Provides delay in command execution */
SDMMC_BLOCK_MODE_STATUS_t SDMMC_BLOCK_SD_CommandDelay(SDMMC_BLOCK_t *const obj, uint32_t delay)
{
  SDMMC_BLOCK_MODE_STATUS_t status = SDMMC_BLOCK_MODE_STATUS_SUCCESS;
  obj->sdmmc_sd->tmr_expire = (bool)1U;

  status = SDMMC_BLOCK_SD_StartTimer(obj, delay);
  if (status != SDMMC_BLOCK_MODE_STATUS_SUCCESS)
  {
    do
    {
      if (obj->sdmmc_sd->tmr_expire == (bool)0U)
      {
        status = SDMMC_BLOCK_MODE_STATUS_TIMEOUT_OCCURED;
        break;
      }
    } while ((!((obj->sdmmc_sd->isr_context.cmd_flag == 1U) ||
    		  (obj->sdmmc_sd->isr_context.data_flag == 1U))) &&
    		 (((XMC_SDMMC_GetEvent(obj->sdmmc_sd->sdmmc, XMC_SDMMC_CARD_ERR) == true) == 0U)));
  }

  /* Stop timer and delete it */
  SDMMC_BLOCK_SD_StopTimer(obj);
  SYSTIMER_DeleteTimer(obj->sdmmc_sd->tmr_id);

  obj->sdmmc_sd->isr_context.cmd_flag = (uint8_t)0U;
  obj->sdmmc_sd->isr_context.data_flag = (uint8_t)0U;

  return status;
}

/* Recovery task for error interrupts */
SDMMC_BLOCK_MODE_STATUS_t SDMMC_BLOCK_SD_ErrorInterruptRecovery(SDMMC_BLOCK_t *const obj)
{
  XMC_SDMMC_COMMAND_t *cmd = (XMC_SDMMC_COMMAND_t *)&(SDMMC_BLOCK_COMMON_COMMAND(12));
  SDMMC_BLOCK_MODE_STATUS_t status = (uint32_t)SDMMC_BLOCK_MODE_STATUS_NONRECOVERABLE_ERROR;
  uint32_t normal_events = 0U;
  uint32_t error_events = 0U;

  error_events = XMC_SDMMC_CMD_TIMEOUT_ERR   |
                 XMC_SDMMC_CMD_CRC_ERR       |
                 XMC_SDMMC_CMD_END_BIT_ERR   |
                 XMC_SDMMC_CMD_IND_ERR       |
                 XMC_SDMMC_DATA_TIMEOUT_ERR  |
                 XMC_SDMMC_DATA_CRC_ERR      |
                 XMC_SDMMC_DATA_END_BIT_ERR  |
                 XMC_SDMMC_CURRENT_LIMIT_ERR |
                 XMC_SDMMC_TARGET_RESP_ERR;

  /* Disable all error events */
  XMC_SDMMC_DisableEvent(obj->sdmmc_sd->sdmmc, error_events);

  /* Check error interrupt status bits D0-D3 for CMD line errors */
  if ((((uint32_t)obj->sdmmc_sd->isr_context.int_status_shadow &
        (uint32_t)SDMMC_BLOCK_ERROR_CMD_STATUS_BITMASK) != (uint32_t)0U) ||
      XMC_SDMMC_IsCommandLineBusy(obj->sdmmc_sd->sdmmc) == true)
  {
    /* Set software reset for CMD line */
    status = SDMMC_BLOCK_SD_Reset(obj, (uint8_t)XMC_SDMMC_SW_RST_CMD_LINE);
  }

  /* Check error interrupt status bits D4-D6 for data line errors */
  if ((((uint32_t)obj->sdmmc_sd->isr_context.int_status_shadow &
        (uint32_t)SDMMC_BLOCK_ERROR_DATA_STATUS_BITMASK) != (uint32_t)0U) ||
      XMC_SDMMC_IsDataLineBusy(obj->sdmmc_sd->sdmmc) == true)
  {
    /* Set software reset for data line */
    status = SDMMC_BLOCK_SD_Reset(obj, (uint8_t)XMC_SDMMC_SW_RST_DAT_LINE);
  }

  error_events = XMC_SDMMC_CMD_TIMEOUT_ERR   |
		         XMC_SDMMC_CMD_CRC_ERR       |
		         XMC_SDMMC_CMD_END_BIT_ERR   |
		         XMC_SDMMC_CMD_IND_ERR       |
		         XMC_SDMMC_DATA_TIMEOUT_ERR  |
		         XMC_SDMMC_DATA_CRC_ERR      |
		         XMC_SDMMC_DATA_END_BIT_ERR  |
		         XMC_SDMMC_CURRENT_LIMIT_ERR |
		         XMC_SDMMC_CARD_ERR;

  XMC_SDMMC_ClearEvent(obj->sdmmc_sd->sdmmc, error_events);

  if (obj->sdmmc_sd->issue_abort == (uint8_t)1U)
  {
    /* Issue abort command. Set argument register */
	XMC_SDMMC_SendCommand(obj->sdmmc_sd->sdmmc, cmd, SDMMC_BLOCK_ARGUMENT0);

    /* Wait for any interrupt status bit to be set */

    /* Timeout of 5ms */
    status = SDMMC_BLOCK_SD_CommandDelay(obj, (uint32_t)SDMMC_BLOCK_DELAY_IN_COMMAND);
    if (status == SDMMC_BLOCK_MODE_STATUS_SUCCESS)
    {
      /* If error status bit is set in the status register */
      if (XMC_SDMMC_IsAnyErrorEvent(obj->sdmmc_sd->sdmmc) == true)
      {
        status = (uint32_t)SDMMC_BLOCK_MODE_STATUS_NONRECOVERABLE_ERROR;

        XMC_SDMMC_ClearEvent(obj->sdmmc_sd->sdmmc, normal_events);
        XMC_SDMMC_ClearEvent(obj->sdmmc_sd->sdmmc, error_events);

        /* Set software reset for CMD line and data line */
        SDMMC_BLOCK_SD_Reset(obj, XMC_SDMMC_SW_RST_CMD_LINE | XMC_SDMMC_SW_RST_DAT_LINE);
      }
    }

    /* Check Data lines status in present status register */
    if (XMC_SDMMC_IsAnyErrorEvent(obj->sdmmc_sd->sdmmc) == false)
    {
      if (XMC_SDMMC_IsAllDataLinesHigh(obj->sdmmc_sd->sdmmc) == true)
      {
        status = SDMMC_BLOCK_MODE_STATUS_RECOVERABLE_ERROR;
      }
      else
      {
        status = SDMMC_BLOCK_MODE_STATUS_NONRECOVERABLE_ERROR;
      }
    }
  }
  else
  {
    if (XMC_SDMMC_IsAnyErrorEvent(obj->sdmmc_sd->sdmmc) == false)
	{
	  if (XMC_SDMMC_IsAllDataLinesHigh(obj->sdmmc_sd->sdmmc) == true)
	  {
	    status = SDMMC_BLOCK_MODE_STATUS_RECOVERABLE_ERROR;
	  }
	  else
	  {
	    status = SDMMC_BLOCK_MODE_STATUS_NONRECOVERABLE_ERROR;
	  }
	}
  }

  /* Enable the error interrupt signal */
  error_events |= XMC_SDMMC_TARGET_RESP_ERR;
  XMC_SDMMC_EnableEvent(obj->sdmmc_sd->sdmmc, error_events);

  /* Global error recovery variable */
  obj->sdmmc_sd->err_recovery_stat = status;

  return status;
}

/* Handles interrupts in normal interrupt status register */
SDMMC_BLOCK_MODE_STATUS_t SDMMC_BLOCK_SD_NormalInterruptHandler(SDMMC_BLOCK_t *const obj, uint16_t int_status)
{
  SDMMC_BLOCK_MODE_STATUS_t status = SDMMC_BLOCK_MODE_STATUS_SUCCESS;

#if SDMMC_BLOCK_SD_CARD_DETECTION_SUPPORT
  /* Card removal interrupt */
  if ((int_status & XMC_SDMMC_CARD_REMOVAL) != 0U)
  {
    /* Confirm that the card insertion bit is clear in present state status */
    while((XMC_SDMMC_GetPresentState(obj->sdmmc_sd->sdmmc).b32 &
          SDMMC_PRESENT_STATE_CARD_INSERTED_Msk) != 0U)
    {
    }

    /* Clear the interrupt status bit */
    XMC_SDMMC_ClearEvent(obj->sdmmc_sd->sdmmc, XMC_SDMMC_CARD_REMOVAL);

    /* Callback to upper layer function for card removal interrupt */
    if (obj->sdmmc_sd->callback != NULL)
    {
      obj->sdmmc_sd->callback(SDMMC_BLOCK_SD_INTERRUPT_CARD_REMOVAL);
    }
    else
    {
      status = SDMMC_BLOCK_MODE_STATUS_NULL_POINTER;
    }
  }

  /* Card insertion interrupt */
  if ((int_status & XMC_SDMMC_CARD_INS) != 0U)
  {
    /* Confirm that the card insertion bit is set in present state status */
    while((XMC_SDMMC_GetPresentState(obj->sdmmc_sd->sdmmc).b32 &
          SDMMC_PRESENT_STATE_CARD_INSERTED_Msk) == 0U)
    {
    }

    /* Clear the interrupt status bit */
    XMC_SDMMC_ClearEvent(obj->sdmmc_sd->sdmmc, XMC_SDMMC_CARD_INS);

    /* Callback to upper layer function for card insertion interrupt*/
    if (obj->sdmmc_sd->callback != NULL)
    {
      obj->sdmmc_sd->callback(SDMMC_BLOCK_SD_INTERRUPT_CARD_INSERTION);
    }
    else
    {
      status = SDMMC_BLOCK_MODE_STATUS_NULL_POINTER;
    }
  }
#endif

  /* Buffer read ready interrupt */
  if (((uint32_t)int_status & (uint32_t)XMC_SDMMC_BUFFER_READ_READY) != (uint32_t)0)
  {
    obj->sdmmc_sd->data_int_err = SDMMC_BLOCK_MODE_STATUS_BUFFER_READY;
    XMC_SDMMC_ClearEvent(obj->sdmmc_sd->sdmmc, XMC_SDMMC_BUFFER_READ_READY);
    obj->sdmmc_sd->isr_context.data_flag = (uint8_t)1U;
  }

  /* Buffer write ready interrupt */
  if (((uint32_t)int_status & (uint32_t)XMC_SDMMC_BUFFER_WRITE_READY) != (uint32_t)0)
  {
    obj->sdmmc_sd->data_int_err = SDMMC_BLOCK_MODE_STATUS_BUFFER_READY;
    XMC_SDMMC_ClearEvent(obj->sdmmc_sd->sdmmc, XMC_SDMMC_BUFFER_WRITE_READY);
    obj->sdmmc_sd->isr_context.data_flag = (uint8_t)1U;
  }

  /* Transfer complete interrupt */
  if (((uint32_t)int_status & (uint32_t)XMC_SDMMC_TX_COMPLETE) != (uint32_t)0)
  {
    obj->sdmmc_sd->transfer_int_err = SDMMC_BLOCK_MODE_STATUS_TRANSFER_COMPLETE;
    XMC_SDMMC_ClearEvent(obj->sdmmc_sd->sdmmc, XMC_SDMMC_TX_COMPLETE);
    obj->card_state &= ~SDMMC_BLOCK_CARD_STATE_DATA_ACTIVE;
    obj->sdmmc_sd->isr_context.transfer_flag = (uint8_t)1U;
  }

  /* Command complete interrupt */
  if (((uint32_t)int_status & (uint32_t)XMC_SDMMC_CMD_COMPLETE) != (uint32_t)0)
  {
    obj->sdmmc_sd->cmd_int_err = SDMMC_BLOCK_MODE_STATUS_COMMAND_COMPLETE;
    XMC_SDMMC_ClearEvent(obj->sdmmc_sd->sdmmc, XMC_SDMMC_CMD_COMPLETE);
    obj->card_state &= ~SDMMC_BLOCK_CARD_STATE_CMD_ACTIVE;
    obj->sdmmc_sd->isr_context.cmd_flag = (uint8_t)1;
  }

  return (uint32_t)status;
}

/* Handles interrupt in error interrupt status register */
SDMMC_BLOCK_MODE_STATUS_t SDMMC_BLOCK_SD_ErrorInterruptHandler(SDMMC_BLOCK_t *const obj,
                                                               uint16_t int_status)
{
  SDMMC_BLOCK_MODE_STATUS_t status = SDMMC_BLOCK_MODE_STATUS_FAILURE;
  obj->sdmmc_sd->isr_context.int_status_shadow = int_status;

  /* Command timeout error interrupt */
  if (((uint32_t)int_status & ((uint32_t)XMC_SDMMC_CMD_TIMEOUT_ERR >> 16U)) != (uint32_t)0)
  {
    obj->sdmmc_sd->cmd_int_err = SDMMC_BLOCK_MODE_STATUS_COMMAND_TIMEOUT_ERROR;
    obj->card_state &= ~SDMMC_BLOCK_CARD_STATE_CMD_ACTIVE;
    XMC_SDMMC_ClearEvent(obj->sdmmc_sd->sdmmc, XMC_SDMMC_CMD_TIMEOUT_ERR);
    obj->sdmmc_sd->isr_context.cmd_flag = 1U;
  }

  /* Command CRC error interrupt */
  if (((uint32_t)int_status & ((uint32_t)XMC_SDMMC_CMD_CRC_ERR >> 16U)) != (uint32_t)0)
  {
    obj->sdmmc_sd->cmd_int_err = SDMMC_BLOCK_MODE_STATUS_COMMAND_CRC_ERROR;
    obj->card_state &= ~SDMMC_BLOCK_CARD_STATE_CMD_ACTIVE;
    XMC_SDMMC_ClearEvent(obj->sdmmc_sd->sdmmc, XMC_SDMMC_CMD_CRC_ERR);
    obj->sdmmc_sd->isr_context.cmd_flag = 1U;
  }

  /* Command end bit error interrupt */
  if (((uint32_t)int_status & ((uint32_t)XMC_SDMMC_CMD_END_BIT_ERR >> 16U)) != (uint32_t)0)
  {
    obj->sdmmc_sd->cmd_int_err = SDMMC_BLOCK_MODE_STATUS_COMMAND_ENDBIT_ERROR;
    obj->card_state &= ~SDMMC_BLOCK_CARD_STATE_CMD_ACTIVE;
    XMC_SDMMC_ClearEvent(obj->sdmmc_sd->sdmmc, XMC_SDMMC_CMD_END_BIT_ERR);
    obj->sdmmc_sd->isr_context.cmd_flag = 1U;
  }

  /* Command index error interrupt */
  if (((uint32_t)int_status & ((uint32_t)XMC_SDMMC_CMD_IND_ERR >> 16U)) != (uint32_t)0)
  {
    obj->sdmmc_sd->cmd_int_err = SDMMC_BLOCK_MODE_STATUS_COMMAND_INDEX_ERROR;
    obj->card_state &= ~SDMMC_BLOCK_CARD_STATE_CMD_ACTIVE;
    XMC_SDMMC_ClearEvent(obj->sdmmc_sd->sdmmc, XMC_SDMMC_CMD_IND_ERR);
    obj->sdmmc_sd->isr_context.cmd_flag = 1U;
  }

  /* Data timeout error interrupt */
  if (((uint32_t)int_status & ((uint32_t)XMC_SDMMC_DATA_TIMEOUT_ERR >> 16U)) != (uint32_t)0)
  {
    obj->sdmmc_sd->data_int_err = SDMMC_BLOCK_MODE_STATUS_DATA_TIMEOUT_ERROR;
    obj->card_state &= ~SDMMC_BLOCK_CARD_STATE_DATA_ACTIVE;
    XMC_SDMMC_ClearEvent(obj->sdmmc_sd->sdmmc, XMC_SDMMC_DATA_TIMEOUT_ERR);
    obj->sdmmc_sd->isr_context.data_flag = 1U;
  }

  /* Data CRC error interrupt */
  if (((uint32_t)int_status & ((uint32_t)XMC_SDMMC_DATA_CRC_ERR >> 16U)) != (uint32_t)0)
  {
    obj->sdmmc_sd->data_int_err = SDMMC_BLOCK_MODE_STATUS_DATA_CRC_ERROR;
    obj->card_state &= ~SDMMC_BLOCK_CARD_STATE_DATA_ACTIVE;
    XMC_SDMMC_ClearEvent(obj->sdmmc_sd->sdmmc, XMC_SDMMC_DATA_CRC_ERR);
    obj->sdmmc_sd->isr_context.data_flag = 1U;
  }

  /* Data end bit error interrupt */
  if (((uint32_t)int_status & ((uint32_t)XMC_SDMMC_DATA_END_BIT_ERR >> 16U)) != (uint32_t)0)
  {
    obj->sdmmc_sd->data_int_err = SDMMC_BLOCK_MODE_STATUS_DATA_ENDBIT_ERROR;
    obj->card_state &= ~SDMMC_BLOCK_CARD_STATE_DATA_ACTIVE;
    XMC_SDMMC_ClearEvent(obj->sdmmc_sd->sdmmc, XMC_SDMMC_DATA_END_BIT_ERR);
    obj->sdmmc_sd->isr_context.data_flag = 1U;
  }

  /* ACMD12 error interrupt */
  if (((uint32_t)int_status & ((uint32_t)XMC_SDMMC_ACMD_ERR >> 16U)) != (uint32_t)0)
  {
    obj->sdmmc_sd->acmd_int_err = SDMMC_BLOCK_MODE_STATUS_ACMD12_ERROR;
    obj->card_state &= ~SDMMC_BLOCK_CARD_STATE_CMD_ACTIVE;
    obj->card_state &= ~SDMMC_BLOCK_CARD_STATE_DATA_ACTIVE;
    XMC_SDMMC_ClearEvent(obj->sdmmc_sd->sdmmc, XMC_SDMMC_ACMD_ERR);
    obj->sdmmc_sd->isr_context.cmd_flag = 1U;
  }

  return status;
}

/* Switch the card state to transferring state if it isn't */
SDMMC_BLOCK_MODE_STATUS_t SDMMC_BLOCK_SD_SwitchToTransferState(SDMMC_BLOCK_t *const obj)
{
  SDMMC_BLOCK_MODE_STATUS_t status = SDMMC_BLOCK_MODE_STATUS_FAILURE;
  uint32_t arg = 0UL;
  uint32_t card_status = 0U;

  /* Check the current state of the card */
  arg |= (uint32_t)((uint32_t)obj->sdmmc_sd->card_info.rca << (uint32_t)SDMMC_BLOCK_ARG_RCA_BITPOS);

  /* Send CMD13 to read card status */
  status = SDMMC_BLOCK_SD_SendCommand(obj,
                                      &(SDMMC_BLOCK_COMMON_COMMAND(13)),
                                      arg,
                                      XMC_SDMMC_RESPONSE_TYPE_R1,
                                      &card_status);

  if (status == SDMMC_BLOCK_MODE_STATUS_SUCCESS)
  {
    /* Check if it is in transferring state */
    if (((card_status & SDMMC_BLOCK_SD_CSR_CURRENT_STATE_BITMASK) >> SDMMC_BLOCK_SD_CSR_CURRENT_STATE_BITPOS) ==
        SDMMC_BLOCK_SD_CSR_CURRENT_STATE_TRANS_VALUE)
    {
      status = SDMMC_BLOCK_MODE_STATUS_SUCCESS;
    }
	else
	{
	  /* Switch to transfer state (CMD7) */
      status = SDMMC_BLOCK_SD_SendCommand(obj,
                                          &(SDMMC_BLOCK_COMMON_COMMAND(7)),
                                          arg,
                                          XMC_SDMMC_RESPONSE_TYPE_R1b,
                                          &card_status);
	}
  }

  return status;
}

/*
 * This function registers the cal back function of upper layer which will be
 * invoked from low-level driver if card is inserted or removed in the kit
 * supporting card detection mechanism.
 */
#if SDMMC_BLOCK_SD_CARD_DETECTION_SUPPORT

SDMMC_BLOCK_MODE_STATUS_t SDMMC_BLOCK_SD_RegisterCallBack(SDMMC_BLOCK_t *const obj,
                                                          void (*cb)(SDMMC_BLOCK_SD_INTERRUPT_t))
{
  SDMMC_BLOCK_MODE_STATUS_t status = SDMMC_BLOCK_MODE_STATUS_FAILURE;

  /* Check if callback_func is not NULL */
  if (cb != NULL)
  {
    obj->sdmmc_sd->callback = cb;
    status = SDMMC_BLOCK_MODE_STATUS_SUCCESS;
  }

  return status;
}

#endif

/* Check PCMD flag */
void SDMMC_BLOCK_SD_CheckPCMDFlag(uint32_t pcmd_flag)
{
  if (pcmd_flag == 1U)
  {
    XMC_DEBUG("SDMMC_BLOCK_CheckPCMDFlag: ACMD both error");
  }
  else
  {
	XMC_DEBUG("SDMMC_BLOCK_CheckPCMDFlag: ACMD SD transfer error");
  }
}

/* Perform erase operation */
SDMMC_BLOCK_MODE_STATUS_t SDMMC_BLOCK_SD_LocalErase(SDMMC_BLOCK_t *const obj,
                                                    uint32_t start_addr,
                                                    uint32_t end_addr,
                                                    uint32_t timeout)
{
  /* Stores the response received */
  uint32_t card_status = 0U;
  SDMMC_BLOCK_MODE_STATUS_t status = (uint32_t)SDMMC_BLOCK_MODE_STATUS_FAILURE;

  if (((uint32_t)obj->card_type & SDMMC_BLOCK_CARD_TYPE_BLOCK_ADDRESSING) == (uint32_t)0U)
  {
    start_addr *= (uint32_t)512U;
    end_addr *= (uint32_t)512U;
  }

  /* SD erase start command */
  status = SDMMC_BLOCK_SD_SendCommand(obj,
                                      &(SDMMC_BLOCK_SD_COMMAND(32)),
                                      start_addr,
                                      XMC_SDMMC_RESPONSE_TYPE_R1,
                                      &card_status);

  if (status == SDMMC_BLOCK_MODE_STATUS_SUCCESS)
  {
    /* SD Erase End Command */
    status = SDMMC_BLOCK_SD_SendCommand(obj,
                                        &(SDMMC_BLOCK_SD_COMMAND(33)),
                                        end_addr,
                                        XMC_SDMMC_RESPONSE_TYPE_R1,
                                        &card_status);
  }

  if (status == SDMMC_BLOCK_MODE_STATUS_SUCCESS)
  {
    status = SDMMC_BLOCK_SD_SendCommand(obj,
  		                                &(SDMMC_BLOCK_SD_COMMAND(38)),
                                        SDMMC_BLOCK_ARGUMENT0,
                                        XMC_SDMMC_RESPONSE_TYPE_R1b,
                                        &card_status);

    SDMMC_BLOCK_SD_Delay(obj, (timeout * (uint32_t)1000U));
  }

  return status;
}

/* Check if the sector address is out of bound */
SDMMC_BLOCK_MODE_STATUS_t SDMMC_BLOCK_SD_CheckSectorBound(SDMMC_BLOCK_t *const obj,
                                                          uint32_t sector_num,
														  uint32_t sector_count)
{
  SDMMC_BLOCK_MODE_STATUS_t status;
  uint32_t local_sector_count = 0U;

  /* Get sector count function */
  status = SDMMC_BLOCK_SD_GetSectorCount(obj, (void *)&local_sector_count);
  if (status == SDMMC_BLOCK_MODE_STATUS_SUCCESS)
  {
    /* Check the sector count limit */
    if ((sector_num + sector_count) > local_sector_count)
    {
      status = SDMMC_BLOCK_MODE_STATUS_SECTOR_OUT_OF_BOUND;
    }
  }

  return status;
}

/*
 * Perform host controller initialization and card initialization.
 * Also, reading card registers
 */
SDMMC_BLOCK_MODE_STATUS_t SDMMC_BLOCK_SD_CardIdentificationProcess(SDMMC_BLOCK_t *const obj)
{
  SDMMC_BLOCK_MODE_STATUS_t status;

  /* Wait until the internal clock is stable */
  status = SDMMC_BLOCK_SD_StartTimer(obj, (uint32_t)SDMMC_BLOCK_CLOCK_STABLE_DELAY);

  if (obj->sdmmc_sd->tmr_id != 0U)
  {
    do
    {
      if (obj->sdmmc_sd->tmr_expire == (bool)0U)
      {
        status = (uint32_t)SDMMC_BLOCK_MODE_STATUS_TIMEOUT_OCCURED;
        break;
      }
    } while ((XMC_SDMMC_GetClockStability(obj->sdmmc_sd->sdmmc) == false));

    /* Stop timer and delete it */
    SDMMC_BLOCK_SD_StopTimer(obj);
    SYSTIMER_DeleteTimer(obj->sdmmc_sd->tmr_id);

    if (status != SDMMC_BLOCK_MODE_STATUS_TIMEOUT_OCCURED)
    {
      /* Enable the SD clock */
      XMC_SDMMC_SDClockEnable(obj->sdmmc_sd->sdmmc);

      /* Turn the bus power on */
      XMC_SDMMC_BusPowerOn(obj->sdmmc_sd->sdmmc);

      if (obj->init_flag == (uint8_t)0U)
      {
        status = SDMMC_BLOCK_SD_InitializeCard(obj);
        if (status == SDMMC_BLOCK_MODE_STATUS_SUCCESS)
        {
          status = SDMMC_BLOCK_SD_AfterCardInitialize(obj);
          if (status == SDMMC_BLOCK_MODE_STATUS_SUCCESS)
          {
            obj->init_flag = 1U;
          }
        }
      }
    }
  }

  return status;
}

extern SDMMC_BLOCK_t SDMMC_BLOCK_0;
volatile uint16_t normal_int_status;
volatile uint16_t err_int_status;

/* SDMMC Interrupt Handler */
void SDMMC0_0_IRQHandler(void)
{
//  uint32_t events;
//  events = XMC_SDMMC_CMD_COMPLETE       |
//		   XMC_SDMMC_TX_COMPLETE        |
//		   XMC_SDMMC_BUFFER_WRITE_READY |
//		   XMC_SDMMC_BUFFER_READ_READY  |
//		   XMC_SDMMC_CARD_INS           |
//		   XMC_SDMMC_CARD_REMOVAL       |
//		   XMC_SDMMC_CMD_TIMEOUT_ERR    |
//		   XMC_SDMMC_CMD_END_BIT_ERR    |
//		   XMC_SDMMC_CMD_IND_ERR        |
//		   XMC_SDMMC_DATA_TIMEOUT_ERR   |
//		   XMC_SDMMC_DATA_CRC_ERR       |
//		   XMC_SDMMC_DATA_END_BIT_ERR   |
//		   XMC_SDMMC_CURRENT_LIMIT_ERR  |
//		   XMC_SDMMC_TARGET_RESP_ERR;

  //XMC_SDMMC_ClearEvent(XMC_SDMMC, events);
  //XMC_SDMMC_DisableEvent(XMC_SDMMC, events);

  normal_int_status = SDMMC_BLOCK_0.sdmmc_sd->sdmmc->INT_STATUS_NORM;
  err_int_status = SDMMC_BLOCK_0.sdmmc_sd->sdmmc->INT_STATUS_ERR;

  if (normal_int_status & SDMMC_INT_STATUS_NORM_ERR_INT_Msk)
  {
    SDMMC_BLOCK_SD_ErrorInterruptHandler(&SDMMC_BLOCK_0, err_int_status);
  }

  if(normal_int_status & SDMMC003_NORMAL_INT_STATUS_BITS)
  {
    SDMMC_BLOCK_SD_NormalInterruptHandler(&SDMMC_BLOCK_0, normal_int_status);
  }
}

/* Performs the ACMD error recovery */
void SDMMC_BLOCK_SD_ACMDErrorRecovery(SDMMC_BLOCK_t *const obj)
{
  SDMMC_BLOCK_MODE_STATUS_t status = SDMMC_BLOCK_MODE_STATUS_SUCCESS;
  uint32_t pcmd_flag = 0U;
  uint32_t card_status = 0U;

  /* Check ACMD12 "Not executed err" in Auto CMD12 error status register */
  if (XMC_SDMMC_GetACMDErrStatus(obj->sdmmc_sd->sdmmc, XMC_SDMMC_ACMD12_NOT_EXEC_ERR) == true)
  {
    pcmd_flag = 1U;
    /* Check Return Status of Recovery function of CMD_wo_DAT command */
    if (obj->sdmmc_sd->err_recovery_stat == SDMMC_BLOCK_MODE_STATUS_RECOVERABLE_ERROR)
    {
      /* For recoverable error, issue CMD12 */
      status = SDMMC_BLOCK_SD_SendCommand(obj,
                                          &(SDMMC_BLOCK_COMMON_COMMAND(12)),
                                          SDMMC_BLOCK_ARGUMENT0,
                                          XMC_SDMMC_RESPONSE_TYPE_R1,
                                          &card_status);
    }
    if((status != SDMMC_BLOCK_MODE_STATUS_SUCCESS) && (status != SDMMC_BLOCK_MODE_STATUS_NONRECOVERABLE_ERROR))
    {
	  /* Set software reset for data line */
	  status = SDMMC_BLOCK_SD_Reset(obj, XMC_SDMMC_SW_RST_DAT_LINE);
	  if (status == SDMMC_BLOCK_MODE_STATUS_SUCCESS)
	  {
	    /* Check for XMC_SDMMC_CMD_NOT_ISSUED_BY_ACMD12_ERR */
        if (XMC_SDMMC_GetACMDErrStatus(obj->sdmmc_sd->sdmmc, XMC_SDMMC_CMD_NOT_ISSUED_BY_ACMD12_ERR) == true)
	    {
          XMC_DEBUG("SDMMC_BLOCK_ACMDErrorRecovery: SDMMC_BLOCK_ACMD_CMD_wo_DAT_NOT_ISSUED");
	    }
	    else
	    {
          /*
		   * Check pcmd_flag. If 1, an error occurred in CMD_wo_DAT,
		   * and also in the SD memory transfer
		   */
          SDMMC_BLOCK_SD_CheckPCMDFlag(pcmd_flag);
	    }
	  }
    }	
  }
  else
  {
    /* Set software reset for CMD line */
    status = SDMMC_BLOCK_SD_Reset(obj, XMC_SDMMC_SW_RST_CMD_LINE);
    if (status == SDMMC_BLOCK_MODE_STATUS_SUCCESS)
    {
      /* Issue CMD12 */
      status = SDMMC_BLOCK_SD_SendCommand(obj,
                                          &(SDMMC_BLOCK_COMMON_COMMAND(12)),
                                          SDMMC_BLOCK_ARGUMENT0,
								          XMC_SDMMC_RESPONSE_TYPE_R1,
                                          &card_status);
	  if (status != SDMMC_BLOCK_MODE_STATUS_NONRECOVERABLE_ERROR)
      {
        /*Set Software Reset for  Data line*/
        status = SDMMC_BLOCK_SD_Reset(obj, XMC_SDMMC_SW_RST_DAT_LINE);
        if (status == SDMMC_BLOCK_MODE_STATUS_SUCCESS)
        {
	      /* Check XMC_SDMMC_CMD_NOT_ISSUED_BY_ACMD12_ERR */
          if (XMC_SDMMC_GetACMDErrStatus(obj->sdmmc_sd->sdmmc, XMC_SDMMC_CMD_NOT_ISSUED_BY_ACMD12_ERR) == true)
          {
            XMC_DEBUG("SDMMC_BLOCK_ACMDErrorRecovery: SDMMC_BLOCK_ACMD_CMD_wo_DAT_NOT_ISSUED");
    	  }
	      else
	      {
		    /*
		     * Check PCMD flag. If 1, an error occurred in CMD_wo_DAT,
		     * and also in the SD memory transfer
		     */
		    SDMMC_BLOCK_SD_CheckPCMDFlag(pcmd_flag);
	      }
        }
      }
    }
  }
}

/*
 * PUBLIC FUNCTIONS
 */

extern const XMC_SDMMC_COMMAND_t SD_HOST_COMMAND[40];
extern const uint8_t SD_HOST_SD_HASH_TABLE[65];

/* Initialize host controller */
SDMMC_BLOCK_MODE_STATUS_t SDMMC_BLOCK_SD_HostControllerInit(SDMMC_BLOCK_t *const obj)
{
  SDMMC_BLOCK_MODE_STATUS_t status = SDMMC_BLOCK_MODE_STATUS_HOST_CONTROLLER_INITIALIZED;

  /* Check if host controller is initialized */
  if (((uint32_t)obj->card_state & (uint32_t)SDMMC_BLOCK_CARD_STATE_HC_INITIALIZED) == (uint32_t)0U)
  {
    /* Reset the registers to default values */
    status = SDMMC_BLOCK_SD_Reset(obj, (uint8_t)XMC_SDMMC_SW_RESET_ALL);
    if (status == SDMMC_BLOCK_MODE_STATUS_SUCCESS)
    {
      /*
       * The internal clock should be disabled before
       * updating frequency clock select (Please see
       * section 2.2.14 -> Clock Control Register)
       */
      XMC_SDMMC_Stop(obj->sdmmc_sd->sdmmc);

      /* Select SD clock frequency */
      XMC_SDMMC_SDClockFreqSelect(obj->sdmmc_sd->sdmmc, XMC_SDMMC_CLK_DIV_2);

      /* Internal clock enable */
      XMC_SDMMC_Start(obj->sdmmc_sd->sdmmc);

      /*
       * Enable all normal interrupt status bits except block-gap
       * event, card interrupt event, DMA int., ADMA and auto cmd
       * errors. Enable the status and the events themselves.
       */
      /*
      events = XMC_SDMMC_CMD_COMPLETE       |
    		   XMC_SDMMC_TX_COMPLETE        |
    		   XMC_SDMMC_BUFFER_WRITE_READY |
    		   XMC_SDMMC_BUFFER_READ_READY  |
    		   XMC_SDMMC_CARD_INS           |
    		   XMC_SDMMC_CARD_REMOVAL       |
    		   XMC_SDMMC_CMD_TIMEOUT_ERR    |
    		   XMC_SDMMC_CMD_END_BIT_ERR    |
    		   XMC_SDMMC_CMD_IND_ERR        |
    		   XMC_SDMMC_DATA_TIMEOUT_ERR   |
    		   XMC_SDMMC_DATA_CRC_ERR       |
    		   XMC_SDMMC_DATA_END_BIT_ERR   |
    		   XMC_SDMMC_CURRENT_LIMIT_ERR  |
    		   XMC_SDMMC_TARGET_RESP_ERR; */

      //XMC_SDMMC_EnableEvent(obj->sdmmc, events);

      #define SDMMC003_NORMAL_INT_STATUS_ENABLE                     (0x00F3U)
      #define SDMMC003_ERROR_INT_STATUS_ENABLE                      (0xE0FFU)
      #define SDMMC003_NORMAL_INT_SIGNAL_ENABLE                     (0x0033U)
      #define SDMMC003_ERROR_INT_SIGNAL_ENABLE                      (0xE0FFU)

      SDMMC->EN_INT_STATUS_NORM = SDMMC003_NORMAL_INT_STATUS_ENABLE;
      SDMMC->EN_INT_STATUS_ERR = SDMMC003_ERROR_INT_STATUS_ENABLE ;

      SDMMC->EN_INT_SIGNAL_NORM = SDMMC003_NORMAL_INT_SIGNAL_ENABLE;
      SDMMC->EN_INT_SIGNAL_ERR = SDMMC003_ERROR_INT_SIGNAL_ENABLE;

      /* Set data-line timeout */
      XMC_SDMMC_SetDataLineTimeout(obj->sdmmc_sd->sdmmc, XMC_SDMMC_DAT_TIMEOUT_COUNTER_2_POW_27);

      /* Set bus voltage in the power control register: flattop 3.3 volts */
      XMC_SDMMC_SetBusVoltage(obj->sdmmc_sd->sdmmc, XMC_SDMMC_BUS_VOLTAGE_3_3_VOLTS);

      /* Update the state status to card initialized */
      obj->card_state |= (uint16_t)((uint32_t)SDMMC_BLOCK_CARD_STATE_HC_INITIALIZED |
                                    (uint32_t)SDMMC_BLOCK_CARD_STATE_NO_CARD |
                                    (uint32_t)SDMMC_BLOCK_CARD_STATE_NOT_INITIALIZED);
									
	  for(volatile uint32_t i=0; i<100000U; i++);
    }
  }

  return status;
}

/* De-initialize the host controller */
SDMMC_BLOCK_MODE_STATUS_t SDMMC_BLOCK_SD_HostControllerDeInit(SDMMC_BLOCK_t *const obj)
{
  SDMMC_BLOCK_MODE_STATUS_t status = (uint32_t)SDMMC_BLOCK_MODE_STATUS_FAILURE;

  /* Check if the host controller is initialized */
  if (((uint32_t)obj->card_state & (uint32_t)SDMMC_BLOCK_CARD_STATE_HC_INITIALIZED) != (uint32_t)0U)
  {
    /* Cleanup the card */
    SDMMC_BLOCK_SD_CardCleanUp(obj);

    /* Reset host controller's registers */
    status = SDMMC_BLOCK_SD_Reset(obj, (uint8_t)XMC_SDMMC_SW_RESET_ALL);
  }

  return status;
}

/* Read multiple blocks of data from the card */
SDMMC_BLOCK_MODE_STATUS_t SDMMC_BLOCK_SD_CardReadMultipleBlocks(SDMMC_BLOCK_t *const obj,
                                                                uint32_t *read_buf,
                                                                uint32_t read_addr,
                                                                uint32_t num_blocks)
{
  SDMMC_BLOCK_MODE_STATUS_t status = SDMMC_BLOCK_MODE_STATUS_INIT_FAIL;
  obj->sdmmc_sd->cmd_int_err = SDMMC_BLOCK_MODE_STATUS_FAILURE;
  obj->sdmmc_sd->data_int_err = SDMMC_BLOCK_MODE_STATUS_FAILURE;
  obj->sdmmc_sd->transfer_int_err = SDMMC_BLOCK_MODE_STATUS_FAILURE;

  /* Check if initialization is successful */
  if (obj->init_flag == (uint8_t)1U)
  {
    /* Ensure that sector number is not out of bound */
    status = SDMMC_BLOCK_SD_CheckSectorBound(obj, read_addr, num_blocks);

    if (status == SDMMC_BLOCK_MODE_STATUS_SUCCESS)
    {
      /* Set transfer direction select in the Transfer Mode Register */
      XMC_SDMMC_SetDataTransferDirection(obj->sdmmc_sd->sdmmc, XMC_SDMMC_DATA_TRANSFER_CARD_TO_HOST);

      /* Send Multiple Block  Read Command i.e CMD18 */
      status = SDMMC_BLOCK_SD_MultiBlockTransfer(obj,
                                                 &read_addr,
                                                 num_blocks,
                                                 &(SDMMC_BLOCK_COMMON_COMMAND(18)),
                                                 read_buf,
                                                 SDMMC_BLOCK_SD_DATA_TRANSFER_READ_BUFFER);
    }
  }

  return status;
}

/* Read single block of data from the card */
SDMMC_BLOCK_MODE_STATUS_t SDMMC_BLOCK_SD_CardReadSingleBlock(SDMMC_BLOCK_t *const obj, uint32_t *read_buf, uint32_t read_addr)
{
  SDMMC_BLOCK_MODE_STATUS_t status = SDMMC_BLOCK_MODE_STATUS_INIT_FAIL;
  uint32_t sector_count = 1U;

  /* Check if initialization successful */
  if (obj->init_flag == (uint8_t)1U)
  {
    /* Ensure that the sector number is not out of bound */
    status = SDMMC_BLOCK_SD_CheckSectorBound(obj, read_addr, sector_count);
    if (status == SDMMC_BLOCK_MODE_STATUS_SUCCESS)
    {
      /* Block addressing or byte addressing */
      if (((uint32_t)obj->card_type & (uint32_t)SDMMC_BLOCK_CARD_TYPE_BLOCK_ADDRESSING) == (uint32_t)0UL)
      {
    	read_addr = (uint32_t)(read_addr * 512UL);
      }

      XMC_SDMMC_SetDataTransferDirection(obj->sdmmc_sd->sdmmc, XMC_SDMMC_DATA_TRANSFER_CARD_TO_HOST);
      /* SDMMC->TRANSFER_MODE |= (uint16_t)((uint32_t)1U << (uint32_t)SDMMC_TRANSFER_MODE_TX_DIR_SELECT_Pos); */

      /* Perform the Single block transfer operation */
      status = SDMMC_BLOCK_SD_SingleBlockTransfer(obj,
                                                  &(SDMMC_BLOCK_COMMON_COMMAND(17)),
                                                  read_addr,
                                                  (uint16_t)SDMMC_BLOCK_BLOCK_SIZE,
                                                  read_buf,
                                                  SDMMC_BLOCK_SD_DATA_TRANSFER_READ_BUFFER);
    }
  }

  return status;
}

/* Write multiple blocks of data on the card */
SDMMC_BLOCK_MODE_STATUS_t SDMMC_BLOCK_SD_CardWriteMultipleBlocks(SDMMC_BLOCK_t *const obj,
                                                                 const uint32_t *write_buf,
                                                                 uint32_t write_addr,
                                                                 uint32_t num_blocks)
{
  SDMMC_BLOCK_MODE_STATUS_t status = SDMMC_BLOCK_MODE_STATUS_INIT_FAIL;

  obj->sdmmc_sd->cmd_int_err = SDMMC_BLOCK_MODE_STATUS_FAILURE;
  obj->sdmmc_sd->data_int_err = SDMMC_BLOCK_MODE_STATUS_FAILURE;
  obj->sdmmc_sd->transfer_int_err = SDMMC_BLOCK_MODE_STATUS_FAILURE;

  /* Check if initialization is successful */
  if (obj->init_flag == (uint8_t)1U)
  {
    /* Ensure sector number is not out of bound */
    status = SDMMC_BLOCK_SD_CheckSectorBound(obj, write_addr, num_blocks);
    if (status == SDMMC_BLOCK_MODE_STATUS_SUCCESS)
    {
      /* Clear transfer direction select in transfer mode register */
      XMC_SDMMC_SetDataTransferDirection(obj->sdmmc_sd->sdmmc, XMC_SDMMC_DATA_TRANSFER_HOST_TO_CARD);

      /* Send Multiple Block  Write  Command i.e CMD25 */
      status = SDMMC_BLOCK_SD_MultiBlockTransfer(obj,
                                                 &write_addr,
                                                 num_blocks,
                                                 &(SDMMC_BLOCK_COMMON_COMMAND(25)),
                                                 (uint32_t *)write_buf,
                                                 SDMMC_BLOCK_SD_DATA_TRANSFER_WRITE_BUFFER);
    }
  }

  return status;
}

/* Write single block of data on the card */
SDMMC_BLOCK_MODE_STATUS_t SDMMC_BLOCK_SD_CardWriteSingleBlock(SDMMC_BLOCK_t *const obj,
                                                              const uint32_t *write_buf,
                                                              uint32_t write_addr)
{
  SDMMC_BLOCK_MODE_STATUS_t status = SDMMC_BLOCK_MODE_STATUS_INIT_FAIL;
  uint32_t sector_count = 1U;

  /* Check if initialization is successful */
  if (obj->init_flag == (uint8_t)1U)
  {
    /* Check if sector number is not out of bound */
    status = SDMMC_BLOCK_SD_CheckSectorBound(obj, write_addr, sector_count);
    if (status == SDMMC_BLOCK_MODE_STATUS_SUCCESS)
    {
      /* If not block addressing, then multiply by 512 bytes */
      if (((uint32_t)obj->card_type & (uint32_t)SDMMC_BLOCK_CARD_TYPE_BLOCK_ADDRESSING) == (uint32_t)0U)
      {
        write_addr = (uint32_t)(write_addr * 512U);
      }

      /* Clear transfer direction select bit */
      XMC_SDMMC_SetDataTransferDirection(obj->sdmmc_sd->sdmmc, XMC_SDMMC_DATA_TRANSFER_HOST_TO_CARD);

      /* Single block transfer function */
      status = SDMMC_BLOCK_SD_SingleBlockTransfer(obj,
                                                  &(SDMMC_BLOCK_COMMON_COMMAND(24)),
                                                  write_addr,
                                                  (uint16_t)SDMMC_BLOCK_BLOCK_SIZE,
                                                  (uint32_t *)write_buf,
                                                  SDMMC_BLOCK_SD_DATA_TRANSFER_WRITE_BUFFER);
    }
  }

  return status;
}

/* Erase data from the card */
SDMMC_BLOCK_MODE_STATUS_t SDMMC_BLOCK_SD_EraseBlock(SDMMC_BLOCK_t *const obj, uint32_t start_addr, uint32_t end_addr)
{
  SDMMC_BLOCK_MODE_STATUS_t status = SDMMC_BLOCK_MODE_STATUS_INIT_FAIL;
  uint32_t num_sectors = 0U;
  /* Allocation unit to no. of sectors in 1 AU table mapping */
  uint32_t au_to_sectors[10] = {0U, 32U, 64U, 128U, 256U, 512U, 1024U, 2048U, 4096U, 8192U};
  uint16_t erase_size = (uint16_t)0U;
  uint8_t erase_offset = (uint8_t)0U;
  uint8_t erase_timeout = (uint8_t)0U;
  uint8_t au_size = (uint8_t)0U;
  uint32_t sectors_in_au = 0U;
  uint32_t sectors_in_erase_cluster = 0U;
  /* Read SD status  */
  uint32_t sd_status[16] = {0U};
  uint32_t erase_timeout_per_cluster = 0UL;

  obj->sdmmc_sd->cmd_int_err = SDMMC_BLOCK_MODE_STATUS_FAILURE;
  obj->sdmmc_sd->data_int_err = SDMMC_BLOCK_MODE_STATUS_FAILURE;
  obj->sdmmc_sd->transfer_int_err = SDMMC_BLOCK_MODE_STATUS_FAILURE;

  /* Check if initialization is successful */
  if (obj->init_flag == (uint8_t)1U)
  {
    num_sectors = end_addr - start_addr;
    /* Check sector number is not out of bound */
    status = SDMMC_BLOCK_SD_CheckSectorBound(obj, start_addr, num_sectors);
    if (status == SDMMC_BLOCK_MODE_STATUS_SUCCESS)
    {
      /* Erase timeout calculation */
      /* Get SD status */
      status = SDMMC_BLOCK_SD_GetSdStatus(obj, (void*)&(sd_status[0]));
      if (status == SDMMC_BLOCK_MODE_STATUS_SUCCESS)
      {
        /* Bits 400-401 in SD status: Erase offset */
        erase_offset =  (uint8_t)(((sd_status[3] & 0x00000300UL)) >> 8U);

        /* Bits 402-407: Erase timeout */
        erase_timeout = (uint8_t)(((sd_status[3] & 0x0000FC00UL)) >> 10UL);

        /* Bits 408-423: Erase size */
        erase_size = (uint16_t)((((sd_status[2] & 0xFF000000U) >> 24U) << 8U) | (sd_status[3] & 0x000000FFU));

        /* Bits 428-431: Allocation unit size */
        au_size  = (uint8_t)((sd_status[2] & 0x00F00000U) >> 20);

        /* Erase timeout calculations */
        erase_timeout_per_cluster = (erase_timeout / erase_size) + erase_offset;

        /* Number of sectors in 1 AU */
        sectors_in_au = au_to_sectors[au_size];
        sectors_in_erase_cluster = sectors_in_au * erase_size;

        while (num_sectors > sectors_in_erase_cluster)
        {
          status = SDMMC_BLOCK_SD_LocalErase(obj,
                                             start_addr,
                                             (start_addr + sectors_in_erase_cluster),
                                             erase_timeout_per_cluster);
          if (status != SDMMC_BLOCK_MODE_STATUS_SUCCESS)
          {
            break;
          }
          start_addr = start_addr + sectors_in_erase_cluster;
          num_sectors = num_sectors - sectors_in_erase_cluster;
        }

        if (num_sectors != 0U)
        {
          status = SDMMC_BLOCK_SD_LocalErase(obj, start_addr, end_addr, erase_timeout_per_cluster);
        }
      }
    }
  }

  return status;
}

/* Set, clear password, lock/unlock card */
SDMMC_BLOCK_MODE_STATUS_t SDMMC_BLOCK_SD_LockUnlockCard(SDMMC_BLOCK_t *const obj,
                                                        SDMMC_BLOCK_LOCK_STRUCTURE_t *lock,
                                                        SDMMC_BLOCK_CARD_LOCK_MODE_t operation_mode)
{
  SDMMC_BLOCK_MODE_STATUS_t status = SDMMC_BLOCK_MODE_STATUS_FAILURE;

  /*  Select the card before proceeding */
  status = SDMMC_BLOCK_SD_SwitchToTransferState(obj);
  if (status == SDMMC_BLOCK_MODE_STATUS_SUCCESS)
  {
    /* Send CMD42 and write the lock data structure */
    /* Clear transfer direction select in transfer mode register */
    XMC_SDMMC_SetDataTransferDirection(obj->sdmmc_sd->sdmmc, XMC_SDMMC_DATA_TRANSFER_HOST_TO_CARD);

    status = SDMMC_BLOCK_SD_SingleBlockTransfer(obj,
                                                &(SDMMC_BLOCK_COMMON_COMMAND(42)),
                                                (uint32_t)SDMMC_BLOCK_ARGUMENT0,
                                                (uint16_t)512,
                                                (uint32_t *)lock,
                                                SDMMC_BLOCK_SD_DATA_TRANSFER_READ_BUFFER);

    if (status == SDMMC_BLOCK_MODE_STATUS_SUCCESS)
    {
      status = SDMMC_BLOCK_SD_CheckLockStatus(obj, operation_mode);
    }
  }

  return status;
}

/* Get the lock status from card */
SDMMC_BLOCK_MODE_STATUS_t SDMMC_BLOCK_SD_GetLockStatus(SDMMC_BLOCK_t *const obj,
                                                       SDMMC_BLOCK_MODE_STATUS_t *lock_status)
{
  uint32_t card_status = 0UL;
  uint32_t arg = 0UL;
  SDMMC_BLOCK_MODE_STATUS_t status = (uint32_t)SDMMC_BLOCK_MODE_STATUS_FAILURE;

  arg |= ((uint32_t)obj->sdmmc_sd->card_info.rca << SDMMC_BLOCK_ARG_RCA_BITPOS);

  /* Send CMD13 to read card status  */
  status = SDMMC_BLOCK_SD_SendCommand(obj,
                                      &(SDMMC_BLOCK_COMMON_COMMAND(13)),
                                      arg,
                                      XMC_SDMMC_RESPONSE_TYPE_R1,
                                      &card_status);

  if (status == SDMMC_BLOCK_MODE_STATUS_SUCCESS)
  {
    /* Lock/unlock status bit in the CSR register */
    if (((uint32_t)card_status & (uint32_t)SDMMC_BLOCK_SD_CSR_CARD_IS_LOCKED_BITMASK) != (uint32_t)0)
    {
      *lock_status = SDMMC_BLOCK_MODE_STATUS_CARD_IS_LOCKED;
    }
    else
    {
      *lock_status = SDMMC_BLOCK_MODE_STATUS_CARD_UNLOCKED;
    }
  }

  return status;
}

/* Get card type */
__INLINE SDMMC_BLOCK_MODE_STATUS_t SDMMC_BLOCK_SD_GetCardType(SDMMC_BLOCK_t *const obj, uint32_t *card_type)
{
  SDMMC_BLOCK_MODE_STATUS_t status = SDMMC_BLOCK_MODE_STATUS_SUCCESS;

  /* Check if initialization is successful */
  if (obj->init_flag != (uint8_t)1U)
  {
    status = SDMMC_BLOCK_MODE_STATUS_INIT_FAIL;
  }
  else
  {
    *card_type = obj->card_type;
  }

  return status;
}

/* Get CID register information of card */
SDMMC_BLOCK_MODE_STATUS_t SDMMC_BLOCK_SD_GetCid(SDMMC_BLOCK_t *const obj, void *buf)
{
  SDMMC_BLOCK_CID_t *temp = (SDMMC_BLOCK_CID_t *)buf;
  SDMMC_BLOCK_MODE_STATUS_t status = SDMMC_BLOCK_MODE_STATUS_SUCCESS;

  /* Check if initialization is successful */
  if (obj->init_flag != (uint8_t)1U)
  {
    status = (uint32_t)SDMMC_BLOCK_MODE_STATUS_INIT_FAIL;
  }
  else
  {
    temp->manufacturing_date = (uint16_t)((obj->sdmmc_sd->card_info.cid[0]) & 0xFFFU);
    temp->product_serial_num = (obj->sdmmc_sd->card_info.cid[1] << 16U) | (obj->sdmmc_sd->card_info.cid[0] >> 16U);
    temp->product_rev = (uint8_t)((obj->sdmmc_sd->card_info.cid[1] >> 16U) & 0xFFU);
    temp->product_name[0] = (uint8_t)((obj->sdmmc_sd->card_info.cid[2] >> 24U) & 0xFFU);
    temp->product_name[1] = (uint8_t)((obj->sdmmc_sd->card_info.cid[2] >> 16U) & 0xFFU);
    temp->product_name[2] = (uint8_t)((obj->sdmmc_sd->card_info.cid[2] >> 8U) & 0xFFU);
    temp->product_name[3] = (uint8_t)((obj->sdmmc_sd->card_info.cid[2] >> 0U) & 0xFFU);
    temp->product_name[4] = (uint8_t)((obj->sdmmc_sd->card_info.cid[1] >> 24U) & 0xFFU);
    temp->app_oem_id[0] = (uint8_t)((obj->sdmmc_sd->card_info.cid[3] >> 8U) & 0xFFU);
    temp->app_oem_id[1] = (uint8_t)((obj->sdmmc_sd->card_info.cid[3]) & 0xFFU);
    temp->manufacturer_id = (uint8_t)((obj->sdmmc_sd->card_info.cid[3] >> 16U) & 0xFFU);
  }

  return status;
}

/* Get OCR information */
SDMMC_BLOCK_MODE_STATUS_t SDMMC_BLOCK_SD_GetOcr(SDMMC_BLOCK_t *const obj, void *buf)
{
  SDMMC_BLOCK_MODE_STATUS_t status = SDMMC_BLOCK_MODE_STATUS_SUCCESS;

  /* Check if initialization is successful */
  if (obj->init_flag != (uint8_t)1U)
  {
    status = SDMMC_BLOCK_MODE_STATUS_INIT_FAIL;
  }
  else
  {
    *(uint32_t *)buf = obj->sdmmc_sd->card_info.ocr;
  }

  return status;
}

/* Get CSD information */
SDMMC_BLOCK_MODE_STATUS_t SDMMC_BLOCK_SD_GetCsd(SDMMC_BLOCK_t *const obj, void *buf)
{
  SDMMC_BLOCK_MODE_STATUS_t status = (uint32_t)SDMMC_BLOCK_MODE_STATUS_SUCCESS;

  /* Check if initialization is successful */
  if (obj->init_flag != (uint8_t)1U)
  {
    status = (uint32_t)SDMMC_BLOCK_MODE_STATUS_INIT_FAIL;
  }
  else
  {
	/*
	 * CSD Structure includes 7-bit CRC and 1-bit fixed bit
	 * which is not sent by the card. So, skip 1 byte before
	 * copying into the structure.
	 */
    memcpy(((uint8_t *)buf + 1U), (void *)obj->sdmmc_sd->card_info.csd, 15U);
  }

  return status;
}

/* Get number of sectors present on the card */
SDMMC_BLOCK_MODE_STATUS_t SDMMC_BLOCK_SD_GetSectorCount(SDMMC_BLOCK_t *const obj, void *buf)
{
  uint32_t mult = 0U;
  SDMMC_BLOCK_MODE_STATUS_t status = (uint32_t)SDMMC_BLOCK_MODE_STATUS_INIT_FAIL;

  /* Check if initialization is successful */
  if (obj->init_flag == (uint8_t)1U)
  {
    if (((uint32_t)obj->card_type & (uint32_t)SDMMC_BLOCK_CARD_TYPE_HIGH_CAPACITY) != (uint32_t)0U)
    {
      SDMMC_BLOCK_SDV2_CSD_t temp_csd_v2 = {0U};

      /* Get CSD function */
      status = SDMMC_BLOCK_SD_GetCsd(obj, (void *)&temp_csd_v2);
      if (status == (uint32_t)SDMMC_BLOCK_MODE_STATUS_SUCCESS)
      {
        /*
         * For High Capacity SD card, (C_SIZE field value + 1) * 1024
         * gives the sector count
         */
		*(uint32_t *)buf = (uint32_t)(((((uint32_t)temp_csd_v2.dev_size_high << (uint32_t)16UL) |
				                       ((uint32_t)temp_csd_v2.dev_size_low)) + (uint32_t)1UL) << (uint32_t)10UL);
	  }
    }
    /*
     * For Standard SD (and MMC) cards:
     * Sector Count = (Device Size + 1) * Mult, where Mult =  2 ^ C_SIZE_MULT
     */
    else
    {
      SDMMC_BLOCK_SDV1_CSD_t temp_csd_v1 = {(uint32_t)0U};
      /* Get CSD function */
      status = SDMMC_BLOCK_SD_GetCsd(obj, (void *)&temp_csd_v1);
      if (status == SDMMC_BLOCK_MODE_STATUS_SUCCESS)
      {
        /* Left shift evaluates 1 * 2 ^ (TmpMmcCsd.DeviceSizeMult + 2) */
        mult = (uint32_t)(((uint32_t)temp_csd_v1.dev_size_mult + (uint32_t)temp_csd_v1.read_blk_len) -
        		          (uint32_t)7U);

        /* Sector Count = device_size * mult */
        *(uint32_t *)buf = (uint32_t)((((uint32_t)temp_csd_v1.dev_size_high << (uint32_t)2UL) |
                                       ((uint32_t)temp_csd_v1.dev_size_low)) + (uint32_t)1UL) << mult;
      }
    }
  }

  return status;
}

/* Get sector size info from the card */
__INLINE SDMMC_BLOCK_MODE_STATUS_t SDMMC_BLOCK_SD_GetSectorSize(SDMMC_BLOCK_t *const obj, void *buf)
{
  SDMMC_BLOCK_MODE_STATUS_t status = (uint32_t)SDMMC_BLOCK_MODE_STATUS_SUCCESS;

  /* Check if initialization is successful */
  if (obj->init_flag != (uint8_t)1U)
  {
    status = (uint32_t)SDMMC_BLOCK_MODE_STATUS_INIT_FAIL;
  }
  else
  {
    /* Sector Size is fixed to 512 bytes */
    *(uint16_t *)buf = (uint16_t)512U;
  }

  return status;
}

/*
 * TODO: Get erase block size of the card in unit of sector into
 * the DWORD variable pointed by Buffer
 */

SDMMC_BLOCK_MODE_STATUS_t SDMMC_BLOCK_SD_GetBlockSize(SDMMC_BLOCK_t *const obj, void *buf)
{
  SDMMC_BLOCK_MODE_STATUS_t status = (uint32_t)SDMMC_BLOCK_MODE_STATUS_SUCCESS;

  /* Check if initialization is successful */
  if (obj->init_flag != (uint8_t)1U)
  {
    status = (uint32_t)SDMMC_BLOCK_MODE_STATUS_INIT_FAIL;
  }

  /* SD high capacity card (CSD V2) */
  else if (((uint32_t)obj->card_type & (uint32_t)SDMMC_BLOCK_CARD_TYPE_HIGH_CAPACITY) != (uint32_t)0)
  {
	SDMMC_BLOCK_SDV2_CSD_t temp_csd_v2 = {(uint32_t)0U};
    /* Get CSD function */
    status = SDMMC_BLOCK_SD_GetCsd(obj, (void *)&temp_csd_v2);
    *(uint32_t *)buf = (uint32_t)((uint32_t)temp_csd_v2.erase_sector_size + (uint32_t)1U);
  }

  /* SD standard capacity card (CSD V1) */
  else
  {
	SDMMC_BLOCK_SDV2_CSD_t temp_csd_v1  = {(uint32_t)0U};
    /* Get CSD function */
    status = SDMMC_BLOCK_SD_GetCsd(obj, (void *)&temp_csd_v1);
    *(uint32_t *)buf = (uint32_t)(temp_csd_v1.erase_sector_size + 1U);
  }

  return status;
}

/* Eject SD card */
SDMMC_BLOCK_MODE_STATUS_t SDMMC_BLOCK_SD_EjectCard(SDMMC_BLOCK_t *const obj)
{
  SDMMC_BLOCK_MODE_STATUS_t status = (uint32_t)SDMMC_BLOCK_MODE_STATUS_FAILURE;
  uint32_t arg = 0U;

  if ((obj->card_state & (uint16_t)SDMMC_BLOCK_CARD_STATE_NO_CARD) == 0U)
  {
    /* Send CMD15 to deactivate the card */
    arg |= (uint32_t)((uint32_t)obj->sdmmc_sd->card_info.rca << (uint32_t)SDMMC_BLOCK_ARG_RCA_BITPOS);

    status = SDMMC_BLOCK_SD_SendCommand(obj,
                                        &(SDMMC_BLOCK_COMMON_COMMAND(15)),
                                        arg,
                                        XMC_SDMMC_RESPONSE_TYPE_NO_RESPONSE,
                                        NULL);

    if (status == (uint32_t)SDMMC_BLOCK_MODE_STATUS_SUCCESS)
    {
      /* Card Cleanup */
      SDMMC_BLOCK_SD_CardCleanUp(obj);
      obj->init_flag = (uint8_t)0U;
    }
  }

  return status;
}

/* De-assert the SDMMC peripheral */
SDMMC_BLOCK_MODE_STATUS_t SDMMC_BLOCK_SD_Init(SDMMC_BLOCK_t *const obj)
{
  /* Enable SDMMC peripheral */
  XMC_SDMMC_Enable(obj->sdmmc_sd->sdmmc);

  /* Initialize System timer APP */
  SYSTIMER_Init(&SYSTIMER_0);

  /* Enable SCU clock for SDMMC */
  XMC_SCU_CLOCK_EnableClock(XMC_SCU_CLOCK_MMC);

  /* De-initialize host controller */
  SDMMC_BLOCK_SD_HostControllerDeInit(obj);

  /* Initialize LLD and host controller */
  return SDMMC_BLOCK_SD_Start(obj);
}

/*
 * Initialize low level drivers, host controller, the card
 * and read card registers.
 */
SDMMC_BLOCK_MODE_STATUS_t SDMMC_BLOCK_SD_Start(SDMMC_BLOCK_t *const obj)
{
  SDMMC_BLOCK_MODE_STATUS_t status = SDMMC_BLOCK_MODE_STATUS_HOST_CONTROLLER_INITIALIZED;

  /* Check If host controller is already initialized */
  if (((uint32_t)obj->card_state & (uint32_t)SDMMC_BLOCK_CARD_STATE_HC_INITIALIZED) == (uint32_t)0U)
  {
    /* Enable Interrupt */
    NVIC_SetPriority(SDMMC0_0_IRQn,
                     NVIC_EncodePriority(NVIC_GetPriorityGrouping(),
                     obj->sdmmc_sd->int_priority,
                     obj->sdmmc_sd->int_sub_priority));

    NVIC_ClearPendingIRQ(SDMMC0_0_IRQn);
    NVIC_EnableIRQ(SDMMC0_0_IRQn);

    /* Host controller initialize */
    status = SDMMC_BLOCK_SD_HostControllerInit(obj);
  }

  return status;
}

/* Get card's current state */
uint8_t SDMMC_BLOCK_SD_GetState(SDMMC_BLOCK_t *obj)
{
  return obj->card_state;
}

/* Reads the data from the card */
SDMMC_BLOCK_STATUS_t SDMMC_BLOCK_SD_ReadBlock(SDMMC_BLOCK_t *const obj,
                                              uint8_t *read_buf,
											  uint32_t sector_num,
											  uint8_t sector_count)
{
  SDMMC_BLOCK_MODE_STATUS_t status;
  uint8_t disk_status;
  SDMMC_BLOCK_STATUS_t res;

  /* Check the status before reading data */
  disk_status = SDMMC_BLOCK_SD_GetState(obj);

  if ((disk_status & (uint8_t)SDMMC_BLOCK_CARD_STATE_NOT_INITIALIZED) != (uint8_t)0U)
  {
    res = SDMMC_BLOCK_STATUS_NOTRDY;
  }
  else
  {
    /* Check for single block read or multiple block read based on sector count */
    if (sector_count == (uint8_t)1U)
    {
      status = SDMMC_BLOCK_SD_CardReadSingleBlock(obj, (uint32_t *)read_buf, sector_num);
    }
    else
    {
      status = SDMMC_BLOCK_SD_CardReadMultipleBlocks(obj, (uint32_t *)read_buf, sector_num, (uint32_t)sector_count);
    }

    if (status == (uint32_t)SDMMC_BLOCK_MODE_STATUS_SUCCESS)
    {
      res = SDMMC_BLOCK_STATUS_SUCCESS;
    }
    else
    {
      res = SDMMC_BLOCK_STATUS_FAILURE;
    }
  }

  return res;
}

/* Writes the data on the card */
SDMMC_BLOCK_STATUS_t SDMMC_BLOCK_SD_WriteBlock(SDMMC_BLOCK_t *const obj,
                                               const uint8_t *write_buf,
								               uint32_t sector_num,
								               uint8_t sector_count)
{
  SDMMC_BLOCK_MODE_STATUS_t status;
  uint8_t disk_status;
  SDMMC_BLOCK_STATUS_t res;

  disk_status = SDMMC_BLOCK_SD_GetState(obj);

  /* If the card is not initialized */
  if ((disk_status & (uint8_t)SDMMC_BLOCK_CARD_STATE_NOT_INITIALIZED) != (uint8_t)0U)
  {
    res = SDMMC_BLOCK_STATUS_NOTRDY;
  }
  /* If the card is read only or write protected */
  else if ((disk_status & (uint8_t)SDMMC_BLOCK_CARD_STATE_WRITE_PROTECTED) != (uint8_t)0U)
  {
    res = (uint32_t)SDMMC_BLOCK_STATUS_WRPRT;
  }
  else
  {
    /* Check for single block write or multiple block write */
    if (sector_count == (uint8_t)1U)
    {
      status = SDMMC_BLOCK_SD_CardWriteSingleBlock(obj, (const uint32_t *)write_buf, sector_num);
    }
    else
    {
      status = SDMMC_BLOCK_SD_CardWriteMultipleBlocks(obj, (const uint32_t *)write_buf, sector_num, (uint32_t)sector_count);
    }

    if (status == SDMMC_BLOCK_MODE_STATUS_SUCCESS)
    {
      res = SDMMC_BLOCK_STATUS_SUCCESS;
    }
    else
    {
      res = SDMMC_BLOCK_STATUS_FAILURE;
    }
  }

  return res;
}


#endif /* SDMMC_BLOCK_SD */

