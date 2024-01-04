/******************************************************************************
* Includes
*******************************************************************************/
#include <stdint.h>
#include "led_ring_hw.h"
/******************************************************************************
* Module Preprocessor Constants
*******************************************************************************/

/******************************************************************************
* Module Preprocessor Macros
*******************************************************************************/

/******************************************************************************
* Module Typedefs
*******************************************************************************/

/******************************************************************************
* Module Variable Definitions
*******************************************************************************/
extern sfr sbit LRR_RST;
extern sfr sbit LRR_LAT;
/******************************************************************************
* Function Prototypes
*******************************************************************************/

/******************************************************************************
* Function Definitions
*******************************************************************************/

void led_ring_start()
{
    led_ring_hal_reset();
    LRR_LAT = 0;
}

void led_ring_send_8 (uint8_t _data)
{
    uint8_t temp_buffer;
    temp_buffer = _data;
    led_ring_hal_write(&temp_buffer, 1);
    led_ring_latch();
}

void led_ring_send_32 ( uint32_t _data )
{
    uint8_t temp_buffer[4];
    temp_buffer[0] = _data;
    temp_buffer[1] = _data >> 8;
    temp_buffer[2] = _data >> 16;
    temp_buffer[3] = _data >> 24;

    led_ring_hal_write(&temp_buffer, 4);
    led_ring_latch();
}

void led_ring_latch()
{
    LRR_LAT = 1;
    Delay_ms(1);
    LRR_LAT = 0;
}

void led_ring_latch_low()
{
    LRR_LAT = 0;
}

void led_ring_latch_high()
{
    LRR_LAT = 1;
}

void led_ring_reset_low()
{
    LRR_RST = 0;
}

void led_ring_reset_high()
{
    LRR_RST = 1;
}


/*************** END OF FUNCTIONS **********************************************/