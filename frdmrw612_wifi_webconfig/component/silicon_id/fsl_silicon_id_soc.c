/*
 * Copyright 2022 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */


#include "fsl_ocotp.h"

status_t SILICONID_ReadUniqueID(uint8_t *siliconId, uint32_t *idLen)
{
    return OCOTP_ReadUniqueID(&siliconId[0], idLen);
}
