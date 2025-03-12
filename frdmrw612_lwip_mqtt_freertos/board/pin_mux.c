/*
 * Copyright 2021 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_common.h"
#include "pin_mux.h"
#include "fsl_io_mux.h"
#include "fsl_gpio.h"

/* FUNCTION ************************************************************************************************************
 * 
 * Function Name : BOARD_InitBootPins
 * Description   : Calls initialization functions.
 * 
 * END ****************************************************************************************************************/
void BOARD_InitBootPins(void) {
    BOARD_InitPins();
}

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 * END ****************************************************************************************************************/
void BOARD_InitPins(void) {                                /*!< Function assigned for the core: Cortex-M33[cm33] */

    /* Initialize GPIO0 functionality on pin GPIO_0 (pin D12) */
   IO_MUX_SetPinMux(IO_MUX_GPIO0);
   IO_MUX_SetPinMux(IO_MUX_GPIO1);
   IO_MUX_SetPinMux(IO_MUX_GPIO12);

   IO_MUX_SetPinMux(IO_MUX_FC3_USART_DATA);
   IO_MUX_SetPinMux(IO_MUX_ENET_CLK);
   IO_MUX_SetPinMux(IO_MUX_ENET_RX);
   IO_MUX_SetPinMux(IO_MUX_ENET_TX);
   IO_MUX_SetPinMux(IO_MUX_ENET_MDIO);
   IO_MUX_SetPinMux(IO_MUX_GPIO21);
   IO_MUX_SetPinMux(IO_MUX_GPIO55);
}

/***********************************************************************************************************************
 * EOF
 **********************************************************************************************************************/
