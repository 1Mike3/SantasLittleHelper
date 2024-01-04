/******************************************************************************
* Includes
*******************************************************************************/
#include "led_ring_hal.h"

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
#if defined( __MIKROC_PRO_FOR_ARM__ )   || \
    defined( __MIKROC_PRO_FOR_DSPIC__ )
static void ( *write_spi_p )( unsigned int data_out );
static unsigned int ( *read_spi_p )( unsigned int buffer );

#elif defined( __MIKROC_PRO_FOR_AVR__ )     || \
      defined( __MIKROC_PRO_FOR_PIC__ )     || \
      defined( __MIKROC_PRO_FOR_8051__ )
static void ( *write_spi_p )( unsigned char data_out );
static unsigned char ( *read_spi_p )( unsigned char dummy );

#elif defined( __MIKROC_PRO_FOR_PIC32__ )
static void ( *write_spi_p )( unsigned long data_out );
static unsigned long ( *read_spi_p )( unsigned long buffer );

#elif defined( __MIKROC_PRO_FOR_FT90x__ )
static void ( *write_spi_p )( unsigned char data_out );
static unsigned char ( *read_spi_p )( unsigned char dummy );
static void ( *write_bytes_spi_p )( unsigned char *data_out,
                                    unsigned int count );
static void ( *read_bytes_spi_p )( unsigned char *buffer,
                                   unsigned int count );
#endif

#if defined( __MIKROC_PRO_FOR_ARM__ )     || \
    defined( __MIKROC_PRO_FOR_AVR__ )     || \
    defined( __MIKROC_PRO_FOR_PIC__ )     || \
    defined( __MIKROC_PRO_FOR_PIC32__ )   || \
    defined( __MIKROC_PRO_FOR_DSPIC__ )   || \
    defined( __MIKROC_PRO_FOR_8051__ )    || \
    defined( __MIKROC_PRO_FOR_FT90x__ )

extern sfr sbit LRR_RST;
extern sfr sbit LRR_LAT;
#endif

/******************************************************************************
* Function Prototypes
*******************************************************************************/

/******************************************************************************
* Function Definitions
*******************************************************************************/

void led_ring_hal_init()
{
#if defined( __MIKROC_PRO_FOR_ARM__ )   || \
    defined( __MIKROC_PRO_FOR_AVR__ )   || \
    defined( __MIKROC_PRO_FOR_DSPIC__ ) || \
    defined( __MIKROC_PRO_FOR_PIC32__ ) || \
    defined( __MIKROC_PRO_FOR_8051__ )
    write_spi_p = SPI_Wr_Ptr;
    read_spi_p = SPI_Rd_Ptr;

#elif defined( __MIKROC_PRO_FOR_PIC__ )
    write_spi_p = SPI1_Write;
    read_spi_p = SPI1_Read;

#elif defined( __MIKROC_PRO_FOR_FT90x__ )
    write_spi_p = SPIM_Wr_Ptr;
    read_spi_p = SPIM_Rd_Ptr;
    write_bytes_spi_p = SPIM_WrBytes_Ptr;
    read_bytes_spi_p = SPIM_RdBytes_Ptr;
#endif
}

void led_ring_hal_reset()
{
    LRR_RST = 0;
    Delay_ms(1);
    LRR_RST = 1;
}

void led_ring_hal_write( uint8_t *buffer,
                    uint16_t count )
{
    while( count-- )
    {
        write_spi_p( *( buffer++ ) );
    }
}

/*************** END OF FUNCTIONS ***************************************************************************/