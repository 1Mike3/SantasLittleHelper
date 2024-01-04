sbit     LRR_LAT  at   GPIOD_ODR.B13;
sbit     LRR_RST  at   GPIOC_ODR.B2;
#include <stdint.h>
#include "led_ring_hw.h"

void main()
{

     uint8_t test_bfr[4];
     uint8_t i = 0;
     uint16_t var_time = 500;
     uint32_t led = 0x00000001;

     // set latch and reset pins as output

     GPIO_Digital_Output(&GPIOD_BASE, _GPIO_PINMASK_13);
     GPIO_Digital_Output(&GPIOC_BASE, _GPIO_PINMASK_2);

     // initalize SPI

     SPI3_Init_Advanced( _SPI_FPCLK_DIV16, _SPI_MASTER | _SPI_8_BIT |
                        _SPI_CLK_IDLE_LOW | _SPI_FIRST_CLK_EDGE_TRANSITION |
                        _SPI_MSB_FIRST | _SPI_SS_DISABLE | _SPI_SSM_ENABLE |
                        _SPI_SSI_1, &_GPIO_MODULE_SPI3_PC10_11_12);

     led_ring_hal_init();
     led_ring_start();

     test_bfr[0] = 0xAA;
     test_bfr[1] = 0xAA;
     test_bfr[2] = 0xAA;
     test_bfr[3] = 0xAA;

     led_ring_hal_write(&test_bfr, 4); // demonstration of HAL write function
     led_ring_latch();

     Delay_ms(1000);

     led_ring_send_32 ( 0xFAFAFAFA ); // demonstration of writing 4 bytes

     Delay_ms(2000);
     led_ring_send_8 ( test_bfr[0] ); // writing one byte at a time
     led_ring_send_8 ( test_bfr[0] );
     led_ring_send_8 ( test_bfr[0] );
     led_ring_send_8 ( test_bfr[0] );

     while (1)
     {
       led_ring_send_32 ( led );   // dot circling faster and faster
       vDelay_ms(var_time);
       led = led << 1;
       if (led == 0)
       {
          led = 1;
          i++;
          if (i == 0)
            var_time = 500;
          else if (i == 1)
            var_time = 250;
          else if (i == 2)
            var_time = 100;
          else if (i == 3)
            var_time = 50;
          else if ( i == 4 )
          {
              var_time = 500;
              i = 0;
          }
       }
     }
}