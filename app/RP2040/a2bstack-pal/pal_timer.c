
/*=============================================================================
 *
 * Project: a2bstack
 *
 * Copyright (c) 2015 - Analog Devices Inc. All Rights Reserved.
 * This software is subject to the terms and conditions of the license set
 * forth in the project LICENSE file. Downloading, reproducing, distributing or
 * otherwise using the software constitutes acceptance of the license. The
 * software may not be used except as expressly authorized under the license.
 *
 *=============================================================================
 *
 * \file:   pal_timer.c
 * \brief:  RP2040 implementation of the platform Timer services.
 *
 *=============================================================================
 */

#include "pico/stdlib.h"
#include "pal_timer.h"
#include "a2b/conf.h"
#include "a2b/error.h"

a2b_HResult
pal_timerInit
    (
    A2B_ECB*    ecb
    )
{
    A2B_UNUSED(ecb);
    return A2B_RESULT_SUCCESS;
}

a2b_HResult
pal_timerShutdown
    (
    A2B_ECB*    ecb
    )
{
    A2B_UNUSED(ecb);
    return A2B_RESULT_SUCCESS;
}

a2b_UInt32
pal_timerGetSysTime(void)
{
    return to_ms_since_boot(get_absolute_time());
}
