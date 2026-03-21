/*******************************************************************************
Copyright (c) 2023 - Analog Devices Inc. All Rights Reserved.
This software is proprietary & confidential to Analog Devices, Inc.
and its licensors.
*******************************************************************************/

#include <stdio.h>                         	/*!< System Stdio library */
#include <stdarg.h>
#include <string.h>
#include <stdint.h>
#include "adi_a2b_datatypes.h"


#ifndef __CMD_QUEUE_H_
#define __CMD_QUEUE_H_


/******************* U S E R  C O N F I G U R A T I O N S *********************/
#define 										ADI_UART_ENABLE
#define ADI_TERMINAL_CMD_SIZE             			(300u)			/*!< Max size of command string */
#define ADI_TERMINAL_CMD_HIS_SIZE             		(5u)			/*!< Max size of command history */


#define SERIAL_TX_FIFO_SIZE     				(64u*1024u)
#define SERIAL_RX_FIFO_SIZE     				(128u)
#define ADI_TERMINAL_RX_MSG_QUEUE_SIZE			(ADI_TERMINAL_CMD_SIZE * 2)	/*!< UART RX message queue */
#define ADI_TERMINAL_TX_MSG_QUEUE_SIZE			(32u)						/*!< UART TX message queue */
#define ADI_TERMINAL_TX_MSG_SIZE_MAX			(300u)						/*!< UART TX message size in bytes */


#if defined(A2B_PRINT_CONSOLE)
#ifndef A2B_PRINT_DEFINED
#define A2B_APP_LOG(...) do{\
						(void)printf(__VA_ARGS__);\
                        }while(0)
#endif
#elif defined(ADI_UART_ENABLE)
#define A2B_APP_LOG uart_printf
#else
#define A2B_APP_LOG(...)
#endif


#ifdef A2B_PRINT_CONSOLE
#ifndef A2B_PRINT_DEFINED
#define A2B_APP_DBG_LOG(...) do{\
						if(gpApp_Info[0]->bDebug)\
						(void)printf(__VA_ARGS__);\
                        }while(0)
#endif
#else
#define A2B_APP_DBG_LOG(...)
#endif

#ifdef ADI_UART_ENABLE
#define ADI_UART_PRINT    		terminal_printf
#else
#define ADI_UART_PRINT    		dummy_printf
#endif
#define _NORMALTEXT_                   "\x1b[0m"
#define _BOLDTEXT_                     "\x1b[1m"
#define _ITALICTEXT_                   "\x1b[3m"
#define _UNDERLINETEXT_                "\x1b[4m"
#define _BLINKTEXT_                    "\x1b[5m"
#define _REDTEXT_					   "\x1b[31m"
#define _GREENTEXT_					   "\x1b[32m"
#define _YELLOWTEXT_                   "\x1b[33m"
#define _BLUETEXT_                     "\x1b[34m"
#define _MAGENTATEXT_                  "\x1b[35m"
#define _CYANTEXT_                     "\x1b[36m"
#define _WHITETEXT_                    "\x1b[37m"
#define _BLACKTEXT_                    "\x1b[30m"
#define _IREDTEXT_                     "\x1b[91m"
#define _IGREENTEXT_                   "\x1b[92m"
#define _IYELLOWTEXT_                  "\x1b[93m"
#define _IBLUETEXT_                    "\x1b[94m"
#define _IMAGENTATEXT_                 "\x1b[95m"
#define _ICYANTEXT_                    "\x1b[96m"
#define _IWHITETEXT_                   "\x1b[97m"
#define _IBLACKTEXT_                   "\x1b[90m"
#define _CLEARSCREEN_                  "\x1b[2J"
#define _CURSORHOME_                   "\x1b[H"

/*============= D A T A  T Y P E S =============*/



typedef enum
{
	NORMAL_TEXT,
	BOLD_TEXT,
	UNDERLINE_TEXT,
	BLINK_TEXT,
	RED_TEXT,
	GREEN_TEXT,
	YELLOW_TEXT,
	BLUE_TEXT,
	MAGENTA_TEXT,
	CYAN_TEXT,
	WHITE_TEXT,
	BLACK_TEXT,

}CONSOLE_FONT;


typedef struct
{
	uint8_t aMsg[ADI_TERMINAL_TX_MSG_SIZE_MAX];			/*!< UART Tx message */
	uint32_t nLen;										/*!< UART Tx payload length */
}ADI_TERMINAL_TX_MSG;

typedef struct
{
	ADI_TERMINAL_TX_MSG oMsg[ADI_TERMINAL_TX_MSG_QUEUE_SIZE];		/*!< UART Tx message */
    volatile uint16_t Head;												/*!< Head value of the queue */
    volatile uint16_t Tail;												/*!< Tail value of the queue */
    volatile uint16_t Size;												/*!< Size of the queue */
    volatile uint16_t Max;
}ADI_TERMINAL_TX_MSG_FIFO;

typedef struct
{
	uint8_t aData[ADI_TERMINAL_RX_MSG_QUEUE_SIZE];                /*!< UART Rx message */
    volatile uint16_t Head;                                                /*!< Head value of the queue */
    volatile uint16_t Tail;                                                /*!< Tail value of the queue */
    volatile uint16_t Size;                                                /*!< Size of the queue */
    volatile uint16_t Max;
}ADI_TERMINAL_RX_MSG_FIFO;



/*=====================Function Prototypes==============================*/
void terminal_printf(const a2b_Char *data, ...);
void adi_UartInit(void);

 void adi_terminal_InitTxQueue(void);
 void adi_terminal_InitRxQueue(void);
 bool adi_terminal_RxEnqueue(uint8_t nChar);
 bool adi_terminal_TxEnqueue(uint8_t *pData);
 bool adi_terminal_TxDequeue(uint8_t **pData, uint32_t *pLen);
bool adi_terminal_RxDequeue(uint8_t *pData);

void SetConsoleFont(CONSOLE_FONT eFont);

#endif
