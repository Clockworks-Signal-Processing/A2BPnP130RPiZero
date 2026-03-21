
/*******************************************************************************
Copyright (c) 2023 - Analog Devices Inc. All Rights Reserved.
This software is proprietary & confidential to Analog Devices, Inc.
and its licensors.
*******************************************************************************/
#include <stdbool.h>

#ifndef __CMD_PLATFORM_H_
#define __CMD_PLATFORM_H_


#define PAL_PRINTF(x)   	adi_terminal_TxEnqueue(x)

/******************* U S E R  C O N F I G U R A T I O N S *********************/


#define UART_BUFFER_SIZE     					(1024u)


/*=====================Function Prototypes==============================*/




#endif
