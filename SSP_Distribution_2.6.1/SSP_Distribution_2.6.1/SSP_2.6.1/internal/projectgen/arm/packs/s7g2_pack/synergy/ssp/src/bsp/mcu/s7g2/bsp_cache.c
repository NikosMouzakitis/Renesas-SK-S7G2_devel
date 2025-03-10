/***********************************************************************************************************************
 * Copyright [2015-2024] Renesas Electronics Corporation and/or its licensors. All Rights Reserved.
 * 
 * This file is part of Renesas SynergyTM Software Package (SSP)
 *
 * The contents of this file (the "contents") are proprietary and confidential to Renesas Electronics Corporation
 * and/or its licensors ("Renesas") and subject to statutory and contractual protections.
 *
 * This file is subject to a Renesas SSP license agreement. Unless otherwise agreed in an SSP license agreement with
 * Renesas: 1) you may not use, copy, modify, distribute, display, or perform the contents; 2) you may not use any name
 * or mark of Renesas for advertising or publicity purposes or in connection with your use of the contents; 3) RENESAS
 * MAKES NO WARRANTY OR REPRESENTATIONS ABOUT THE SUITABILITY OF THE CONTENTS FOR ANY PURPOSE; THE CONTENTS ARE PROVIDED
 * "AS IS" WITHOUT ANY EXPRESS OR IMPLIED WARRANTY, INCLUDING THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
 * PARTICULAR PURPOSE, AND NON-INFRINGEMENT; AND 4) RENESAS SHALL NOT BE LIABLE FOR ANY DIRECT, INDIRECT, SPECIAL, OR
 * CONSEQUENTIAL DAMAGES, INCLUDING DAMAGES RESULTING FROM LOSS OF USE, DATA, OR PROJECTS, WHETHER IN AN ACTION OF
 * CONTRACT OR TORT, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THE CONTENTS. Third-party contents
 * included in this file may be subject to different terms.
 **********************************************************************************************************************/
/***********************************************************************************************************************
* File Name    : bsp_cache.c
* Description  : This module provides APIs for turning cache on and off.
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/
#include "bsp_api.h"

#if defined(BSP_MCU_GROUP_S7G2)

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/
#define BSP_CACHE_TIMEOUT (UINT32_MAX)   /* This timeout is not precise and is only to prevent the code from being
                                          * stuck in a "while" loop.
                                          */
/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Exported global variables (to be accessed by other files)
***********************************************************************************************************************/
 
/***********************************************************************************************************************
Private global variables and functions
***********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @brief Attempt to turn cache off.
 *
 * @param[in] p_state Pointer to the on/off state of cache when the function was called.
 *
 * @retval SSP_SUCCESS          Cache was turned off.
 * @retval SSP_ERR_ASSERTION    NULL pointer.
 **********************************************************************************************************************/

ssp_err_t   R_BSP_CacheOff(bsp_cache_state_t * p_state)
{
    ssp_err_t ret_val;
    ret_val = SSP_SUCCESS;
#if BSP_CFG_PARAM_CHECKING_ENABLE
    /* Check pointer for NULL value. */
    if (NULL == p_state)
    {
        ret_val = SSP_ERR_ASSERTION;        // return ASSERTION ERROR for NULL pointers.
    }
#endif
    if (SSP_SUCCESS == ret_val)
    {
        *p_state = (bsp_cache_state_t)R_ROMC->ROMCE_b.ROMCEN;
        R_ROMC->ROMCE_b.ROMCEN = (uint16_t)0U;         /** Disable ROM cache. */
    }
    else
    {
        /* log assertion */
        SSP_ASSERT_FAIL;
    }
    return ret_val;
}

/*******************************************************************************************************************//**
 * @brief Attempt to set the cache on or off.
 *
 * @param[in] state on/off state to set cache to.
 *
 * @retval SSP_SUCCESS          Cache was set or restored.
 * @retval SSP_ERR_TIMEOUT      Cache was not restored.
 **********************************************************************************************************************/

ssp_err_t   R_BSP_CacheSet(bsp_cache_state_t state)
{
    ssp_err_t ret_val;
    ret_val = SSP_SUCCESS;
    uint32_t i = BSP_CACHE_TIMEOUT;

    R_ROMC->ROMCIV_b.ROMCIV = (uint16_t)1;      /** Invalidate cache. */
    while ( (R_ROMC->ROMCIV_b.ROMCIV != (uint16_t)0) && (i!=(uint32_t)0x00))
    {
        /* Wait for bit to clear. Timeout on hardware failure.*/
        i--;
    }
    if ((uint32_t)0 == i)
    {
        ret_val = SSP_ERR_TIMEOUT;                          /** Return error on timeout. */
    }
    else
    {
        R_ROMC->ROMCE_b.ROMCEN = (uint16_t)state & 0x01U;   /** Enable ROM cache. */
    }
    return ret_val;
}



#endif



