/*********************************************************************************************************//**
 * @file    USART/Interrupt/ht32_board_config.h
 * @version $Rev:: 5656         $
 * @date    $Date:: 2021-11-24 #$
 * @brief   The header file of board configuration.
 *************************************************************************************************************

/* Define to prevent recursive inclusion -------------------------------------------------------------------*/
#ifndef __HT32_BOARD_CONFIG_H
#define __HT32_BOARD_CONFIG_H

#ifdef __cplusplus
 extern "C" {
#endif


// #define _HTCFG_UART_TX_GPIOX                    A
// #define _HTCFG_UART_TX_GPION                    2
// #define _HTCFG_UART_RX_GPIOX                    A
// #define _HTCFG_UART_RX_GPION                    3
// #define HTCFG_UART_IPN                          USART0

#define _HTCFG_UART_TX_GPIOX                    B
#define _HTCFG_UART_TX_GPION                    15
#define _HTCFG_UART_RX_GPIOX                    C
#define _HTCFG_UART_RX_GPION                    0
#define HTCFG_UART_IPN                          USART1

/* ******************************************************** */

// #define _HTCFG_UART_TX_GPIOX                    B
// #define _HTCFG_UART_TX_GPION                    4
// #define _HTCFG_UART_RX_GPIOX                    B
// #define _HTCFG_UART_RX_GPION                    5
// #define HTCFG_UART_IPN                          UART1

/* ******************************************************** */

#define HTCFG_I2C_MASTER_CLK(ck)         (ck.Bit.I2C1)
#define HTCFG_I2C_MASTER_PORT            (HT_I2C1)
#define HTCFG_I2C_MASTER_SCL_GPIO_ID     (GPIO_PA)
#define HTCFG_I2C_MASTER_SCL_AFIO_PIN    (AFIO_PIN_0)
#define HTCFG_I2C_MASTER_SDA_GPIO_ID     (GPIO_PA)
#define HTCFG_I2C_MASTER_SDA_AFIO_PIN    (AFIO_PIN_1)

#define HTCFG_UART_TX_GPIO_ID                     STRCAT2(GPIO_P,         _HTCFG_UART_TX_GPIOX)
#define HTCFG_UART_RX_GPIO_ID                     STRCAT2(GPIO_P,         _HTCFG_UART_RX_GPIOX)
#define HTCFG_UART_TX_AFIO_PIN                    STRCAT2(AFIO_PIN_,      _HTCFG_UART_TX_GPION)
#define HTCFG_UART_RX_AFIO_PIN                    STRCAT2(AFIO_PIN_,      _HTCFG_UART_RX_GPION)
#define HTCFG_UART_PORT                           STRCAT2(HT_,             HTCFG_UART_IPN)
#define HTCFG_UART_IRQn                           STRCAT2(HTCFG_UART_IPN, _IRQn)
#define HTCFG_UART_IRQHandler                     STRCAT2(HTCFG_UART_IPN, _IRQHandler)
#define HTCFG_UART_RX_GPIO_CLK                    STRCAT2(P,              _HTCFG_UART_RX_GPIOX)
#define HTCFG_UART_RX_GPIO_PORT                   STRCAT2(HT_GPIO,        _HTCFG_UART_RX_GPIOX)
#define HTCFG_UART_RX_GPIO_PIN                    STRCAT2(GPIO_PIN_,      _HTCFG_UART_RX_GPION)

#ifdef __cplusplus
}
#endif

#endif
