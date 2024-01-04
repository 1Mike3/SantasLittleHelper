/****************************************************************************
* Title                 :   LED Ring HWL
* Filename              :   led_ring_hw.h
* Author                :   VM
* Origin Date           :   14/06/2016
* Notes                 :   None
*****************************************************************************/
/**************************CHANGE LIST **************************************
*
*    Date    Software Version    Initials   Description 
*  14/06/16    1.0.0               VM      Interface Created.
*
*****************************************************************************/
/** @file led_ring_hw.h
 *  @brief HW Layer for working with the LED Ring Click board
 *
 *  @date 14 Jun 2016
 *  @author Viktor Milovanovic
 *  @copyright GNU Public License
 *
 *  @version 1 - Initial testing and verification
 *
 *  @note Test configuration:
 *   MCU:             STM32F107VC
 *   Dev.Board:       EasyMx Pro v7
 *   Oscillator:      72 Mhz internal
 *   Ext. Modules:    GPS Click
 *   SW:              ARM 4.5.2
 *
 */

#ifndef LED_RING_HW_H_
#define LED_RING_HW_H_
/******************************************************************************
* Includes
*******************************************************************************/
#include "led_ring_hal.h"

/******************************************************************************
* Preprocessor Constants
*******************************************************************************/

/******************************************************************************
* Configuration Constants
*******************************************************************************/

/******************************************************************************
* Macros
*******************************************************************************/

/******************************************************************************
* Typedefs
*******************************************************************************/

/******************************************************************************
* Variables
*******************************************************************************/


/******************************************************************************
* Function Prototypes
*******************************************************************************/
#ifdef __cplusplus
extern "C"{
#endif

void led_ring_start();

void led_ring_send_8 (uint8_t _data);

void led_ring_send_32 ( uint32_t _data );

void led_ring_latch();

void led_ring_latch_low();

void led_ring_latch_high();

void led_ring_reset_low();

void led_ring_reset_high();

#ifdef __cplusplus
} // extern "C"
#endif

#endif

/*** End of File **************************************************************/