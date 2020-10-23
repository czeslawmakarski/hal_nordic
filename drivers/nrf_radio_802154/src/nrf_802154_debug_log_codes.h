/*
 * Copyright (c) 2019 - 2020, Nordic Semiconductor ASA
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY, AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef NRF_802154_DEBUG_LOG_CODES_H_
#define NRF_802154_DEBUG_LOG_CODES_H_

#include "nrf_802154_sl_log.h"

/**
 * @brief List of C modules in nRF 802.15.4 Driver, with theirs ID-s
 *
 * Range of possible values for the 802.15.4 Driver modules has been indicated
 * in nrf_802154_sl_log.h (see "Distribution of IDs for Debug Logs" in there)
 * Prefix "NRF_802154_DRV_MODULE_ID_" is mandatory here,
 * the final part is the module name to be presented by "event_decoder" tool.
 *
 * @note Certain NRF_802154_DRV_MODULE_ID.. value may be shared
 *       between alternative implementations of module
 *       (e.g. random_stdlib/random_zephyr/random_newlib)
 *       In other cases they must be unique.
 *       This enum must exist in .elf file to provide metadata for decoder.html tool
 *       (enum is extracted from .elf in the preparatory stage before using decoder.html)
 */
typedef enum
{
    NRF_802154_DRV_MODULE_ID_APPLICATION      = 1U,
    NRF_802154_DRV_MODULE_ID_CORE             = 2U,
    NRF_802154_DRV_MODULE_ID_CRITICAL_SECTION = 3U,
    NRF_802154_DRV_MODULE_ID_TRX         = 4U,
    NRF_802154_DRV_MODULE_ID_CSMACA      = 5U,
    NRF_802154_DRV_MODULE_ID_DELAYED_TRX = 6U,
    NRF_802154_DRV_MODULE_ID_ACK_TIMEOUT = 7U
} nrf_802154_drv_modules_list_t;

/**
 * @brief List of LOCAL EVENTS generated by module CORE
 *
 * To define elements of this enum, use
 *   - syntax: NRF_802154_LOG_LOCAL_EVENT_ID_{m}__{e} = {nID}
 *    or
 *   - macro: NRF_802154_LOG_L_EVENT_DEFINE({m},{e},{nID},{p_values})
 *  where:
 *    {m} is the name of module
 *    {e} is the name of local event
 *    {nID} is numeric ID of local event (unique in module {m})
 *    {p_values} further enum that defines the set of possible values of parameter for event {e}
 *
 * Both options (syntax/macro) are equivalent, except that using the macro causes additional
 * link creation to {p_values}. See below - currently in the module CORE there is an local
 * event SET_STATE, that has id 1 and possible parameter values for this event are as in
 * enum radio_state_t
 */
typedef enum
{
    NRF_802154_LOG_L_EVENT_DEFINE(CORE, SET_STATE, 1, radio_state_t)
} nrf_802154_drv_local_events_in_CORE_t;

/**
 * @brief List of GLOBAL EVENTS generated in 802.15.4 Driver modules
 *
 * Range of possible values for the 802.15.4 Driver modules has been indicated
 * in nrf_802154_sl_log.h (see "Distribution of IDs for Debug Logs" in there)
 */
typedef enum
{
    NRF_802154_LOG_GLOBAL_EVENT_ID_RADIO_RESET = 1U
 // Possible "RADIO_RESET" parameter values are : 0 (the only possible value)
} nrf_802154_drv_global_events_list_t;

/**
 * @brief List of all definitions that are needed for the correct presentation of debug logs
 *
 * All of the 'typedefs' defined above that are not used anywhere else in the code should occur
 * in the union below, to ensure that information about them will appear in the final .elf file
 */
typedef union
{
    uint8_t                               dummy00tag;
    nrf_802154_drv_modules_list_t         dummy01tag;
    nrf_802154_drv_global_events_list_t   dummy02tag;
    nrf_802154_drv_local_events_in_CORE_t dummy03tag;
} nrf_802154_drv_typedefs_to_save_in_elf_t;

#endif /* NRF_802154_DEBUG_LOG_CODES_H_ */
