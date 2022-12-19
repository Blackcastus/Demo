/*********************************************************************************************************//**
 * @file    i2c_master.h
 * @version $Rev:: 607          $
 * @date    $Date:: 2022-06-28 #$
 * @brief   The header file of I2C Master (interrupt mode with buffer).
 *************************************************************************************************************
 * @attention
 *
 * Firmware Disclaimer Information
 *
 * 1. The customer hereby acknowledges and agrees that the program technical documentation, including the
 *    code, which is supplied by Holtek Semiconductor Inc., (hereinafter referred to as "HOLTEK") is the
 *    proprietary and confidential intellectual property of HOLTEK, and is protected by copyright law and
 *    other intellectual property laws.
 *
 * 2. The customer hereby acknowledges and agrees that the program technical documentation, including the
 *    code, is confidential information belonging to HOLTEK, and must not be disclosed to any third parties
 *    other than HOLTEK and the customer.
 *
 * 3. The program technical documentation, including the code, is provided "as is" and for customer reference
 *    only. After delivery by HOLTEK, the customer shall use the program technical documentation, including
 *    the code, at their own risk. HOLTEK disclaims any expressed, implied or statutory warranties, including
 *    the warranties of merchantability, satisfactory quality and fitness for a particular purpose.
 *
 * <h2><center>Copyright (C) Holtek Semiconductor Inc. All rights reserved</center></h2>
 ************************************************************************************************************/
// <<< Use Configuration Wizard in Context Menu >>>

/* Define to prevent recursive inclusion -------------------------------------------------------------------*/
#ifndef __I2C_MASTER_H
#define __I2C_MASTER_H

/* Includes ------------------------------------------------------------------------------------------------*/

/** @addtogroup HT32_Series_Peripheral_Examples HT32 Peripheral Examples
  * @{
  */

/** @addtogroup I2C I2C
  * @{
  */

/** @addtogroup I2C_Master I2C Master
  * @{
  */

/* Settings ------------------------------------------------------------------------------------------------*/
//<q0> Enable Debug mode
// <i> Enable Debug mode which output debug message to retarget.
//<o1> Support I2C Master Channel
//   <1=> 1
//   <2=> 2
//   <3=> 3
//   <4=> 4
// <i> I2C Master Channel
//<q2> Enable Master NACK Auto retry
// <i> Master NACK Auto retry by I2CMaster_GetStatus().
//<q3> Enable Clock Generated
// <i> Master generates clock in the initialization phase.

//<e4> Enable I2C Hardware Time-out Mode Configuration
// <i> The hardware time-out calculator is:
// <i> F_PCLK = CK_AHB / (2 ^ I2CPCLK)    (I2CPCLK: APB Peripheral Clock Prescaler)
// <i> F_I2CTO = F_PCLK / (2 ^ PSC)
// <i> Time-out = TOUT / F_I2CTO
//    <o5> Counter Prescaler Selection (2 ^ PSC)
//       <0=> /1
//       <1=> /2
//       <2=> /4
//       <3=> /8
//       <4=> /16
//       <5=> /32
//       <6=> /64
//       <7=> /128
//     <i> F_I2CTO = F_PCLK / (2 ^ PSC)
//    <o6> Counter Preload Value (TOUT) <1-0xFFFF:1>
//     <i> Time-out = TOUT / F_I2CTO
//     <i> TOUT range of (1 ~ 0xFFFF). 
//</e>

//<e7> Enable I2C Software Time-out Mode configuration
// <i> The software time-out configuration is based on Interrupt or Tick mode.
//    <o7> I2C Software Time-out Mode Selection
//       <1=> Interrupt Mode
//       <2=> Tick Mode
//       <i> 1 = Interrupt Mode
//       <i> 2 = Tick Mode
//    <o8> Time-out Timer Base (Hz) <1-0xFFFFFFFF:1>
//       <i> Please follow the external interrupt / tick source parameter.
//       <i> (Tick refer to "ht32f5xxxx_conf.h") 
//</e>

#define ISC_MASTER_DEBUG_MODE               (0)
#define I2C_MASTER_SUPPORT_CH               (2)
#define I2C_MASTER_NACK_AUTO_RETRY          (0)     /* Auto retry when NACK by I2CMaster_GetStatus()        */
#define I2C_MASTER_INITIAL_BUS              (0)     /* Master generates clock in the initialization phase.  */

#define I2C_MASTER_HW_TIMEOUT_MODE          (0)     /* 0: DISABLE, 1: ENABLE                                */
#define I2C_MASTER_HW_TIMEOUT_DIV           (2)     /* Timeout Clock = TOUT / (Core Clock / (2 ^ I2C_MASTER_HW_TIMEOUT_DIV))  */
#define I2C_MASTER_HW_TIMEOUT_BASE          (1000)  /* TOUT                                                 */
#define I2C_MASTER_SW_TIMEOUT_MODE          (1)     /* 1: Interrupt, 2: TimeTick                            */
#define I2C_MASTER_SW_TIMEOUT_BASE          (1000)  /* Time-out Timer Base (Hz)                             */

#if (I2C_MASTER_SW_TIMEOUT_MODE == 2)
#define I2CMASTER_GETTICK   Time_GetTick            /* Call from external function                          */
#endif

#ifndef HTCFG_I2CM_CH0
  /* !!! NOTICE !!!
     Default Setting which will be override by configuration outside (such as "ht32_board_config.h"),
     shall be modified according to the device you are using.
  */
  #define HTCFG_I2CM_CH0               I2C0
  #define HTCFG_M0_SCL_GPIO_PORT       B
  #define HTCFG_M0_SCL_GPIO_PIN        7
  #define HTCFG_M0_SDA_GPIO_PORT       B
  #define HTCFG_M0_SDA_GPIO_PIN        8
#endif

/* Exported typedef ----------------------------------------------------------------------------------------*/
/**
 * @brief I2C Master status
 */
typedef enum
{
  I2C_MASTER_GOING        = 0,
  I2C_MASTER_FINISH       = 1,
  I2C_MASTER_SW_TIMEOUT   = 2,
  I2C_MASTER_NACK         = 3,
  I2C_MASTER_BUSERR       = 4,
  I2C_MASTER_HW_TIMEOUT   = 5,
} I2CMaster_Status_Enum;

/**
 * @brief I2C Master command
 */
typedef enum
{
  I2C_MASTER_CMD_READ          = 0,
  I2C_MASTER_CMD_WRITE         = 1,
  I2C_MASTER_CMD_WRITEREAD     = 2,
  I2C_MASTER_CMD_WRITESTOPREAD = 3,
} I2CMaster_CMD_Enum;

/**
 * @brief I2C Master buffer struct
 */
typedef struct
{
  u8 *puBuffer;
  u32 uLength;
} I2CMaster_BufferTypedef;

/**
 * @brief I2C Master struct
 */
typedef struct
{
  u32 uSlaveAddress;
  I2CMaster_BufferTypedef Tx;
  I2CMaster_BufferTypedef Rx;
  u32 uTimeout_us;
  I2CMaster_CMD_Enum Command;
  bool isDynamicOnOff_I2C;
} I2CMaster_Typedef;

/* Exported constants --------------------------------------------------------------------------------------*/
#define   I2C_MASTER_CH0    0
#define   I2C_MASTER_CH1    1
#define   I2C_MASTER_CH2    2
#define   I2C_MASTER_CH3    3

/* Exported macro ------------------------------------------------------------------------------------------*/
#define DIFF_TICK(start,current)      ((current) >= (start) ? (u32)(current - start) : (u32)(0xFFFFFFFF - start + current + 1))

#if (I2C_MASTER_SW_TIMEOUT_BASE >= 1000000)
#define TRANSFER_TIMER(us)            (u32) (us * (I2C_MASTER_SW_TIMEOUT_BASE / 1000000))
#else
#define TRANSFER_TIMER(us)            (u32) (us / (1000000 / I2C_MASTER_SW_TIMEOUT_BASE))
#endif

#define I2CM_CH0_IRQHandler            STRCAT2(HTCFG_I2CM_CH0, _IRQHandler)
#ifdef HTCFG_I2CM_CH1
#define I2CM_CH1_IRQHandler            STRCAT2(HTCFG_I2CM_CH1, _IRQHandler)
#endif
#ifdef HTCFG_I2CM_CH2
#define I2CM_CH2_IRQHandler            STRCAT2(HTCFG_I2CM_CH2, _IRQHandler)
#endif
#ifdef HTCFG_I2CM_CH3
#define I2CM_CH3_IRQHandler            STRCAT2(HTCFG_I2CM_CH3, _IRQHandler)
#endif

/* Exported functions --------------------------------------------------------------------------------------*/
void I2CMaster_Init(u32 CH, u32 uMasterAddress, u32 uClockSpeed);
void I2CMaster_Write(u32 CH, I2CMaster_Typedef *pI2CMaster);
void I2CMaster_Read(u32 CH, I2CMaster_Typedef *pI2CMaster);
void I2CMaster_WriteRead(u32 CH, I2CMaster_Typedef *pI2CMaster);
void I2CMaster_WriteStopRead(u32 CH, I2CMaster_Typedef *pI2CMaster);
void I2CMaster_Start(u32 CH, I2CMaster_Typedef *pI2CMaster);
I2CMaster_Status_Enum I2CMaster_GetStatus(u32 CH);
u32 I2CMaster_GetRxIndex(u32 CH);
void I2CMaster_UpdateRxLength(u32 CH, u32 uLnegth);

void I2CMaster_IRQHandler(u32 CH);
void I2CMaster_TimeoutHandler(void);
I2CMaster_Status_Enum I2CMaster_DynamicTimeout(u32 CH);


/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#endif
