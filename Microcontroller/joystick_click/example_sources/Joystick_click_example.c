/*
 * Project name:
     Joystick_Click_Example
 * Copyright:
     (c) Mikroelektronika, 2013.
 * Revision History:
     20131121:
       - initial release (MV);
 * Description:
     When moving joystick in any direction, a cross will move on GLCD. When
     joystick button is pressed frame around cross will appear.
 * Test configuration:
     MCU:             PIC18F45K22
                      http://ww1.microchip.com/downloads/en/DeviceDoc/41412D.pdf
     dev.board:       EasyPic v7
                      ac:EasyPIC7
                      http://www.mikroe.com/easypic/
     Oscillator:      HS-PLL 32.0000 MHz, 8.0000 MHz Crystal
     Ext. Modules:    GLCD
                      ac:GLCD
                      http://www.mikroe.com/rs/store/components/displays/
                      Joystick Click board
                      ac:Joystick_click
                      http://www.mikroe.com/click/joystick/
     SW:              mikroC PRO for PIC
                      http://www.mikroe.com/mikroc/pic/
 * NOTES:
     - Turn ON SW4.6 and PULL UP RE0, RC3 and RC4.
 */
#include <joystick_click.h>

// NAVI click module connections
sbit NAVI_RST          at LATE1_bit;
sbit NAVI_TST          at RE0_bit;
sbit NAVI_RST_Dir      at TRISE1_bit;
sbit NAVI_TST_Dir      at TRISE0_bit;
// End of NAVI click module connections

// Glcd module connections
char GLCD_DataPort at PORTD;
sbit GLCD_CS1 at LATB0_bit;
sbit GLCD_CS2 at LATB1_bit;
sbit GLCD_RS  at LATB2_bit;
sbit GLCD_RW  at LATB3_bit;
sbit GLCD_EN  at LATB4_bit;
sbit GLCD_RST at LATB5_bit;

sbit GLCD_CS1_Direction at TRISB0_bit;
sbit GLCD_CS2_Direction at TRISB1_bit;
sbit GLCD_RS_Direction  at TRISB2_bit;
sbit GLCD_RW_Direction  at TRISB3_bit;
sbit GLCD_EN_Direction  at TRISB4_bit;
sbit GLCD_RST_Direction at TRISB5_bit;
// End Glcd module connections

void main() {
  ANSELA = 0;                         // Configure all pins as digital I/O
  ANSELB = 0;
  ANSELC = 0;
  ANSELD = 0;
  ANSELE = 0;
  
  NAVI_TST_Dir = 1;                   // Set pin for Joystick button as input
  NAVI_RST_Dir = 0;                   // Set pin connected to reset as output
  
  NAVI_RST = 1;                       // Set Reset pin of Joystick click high
  
  Glcd_Init();                        // Initialize GLCD
  Glcd_Fill(0x00);                    // Clear GLCD
  
  I2C1_Init(100000);                  // Initialize I2C module
  Delay_ms(100);
  
  NAVI_Write(_Control2, 0x84);        // set required Test bits of
                                      // Control Register2 see datasheet AS5013
  NAVI_Write(_AGC, 0x3F);             // Write 3Fh to Hall Element Direct Read
                                      // Registers for maximum sensitivity
  
  NAVI_Write(_T_CTRL, 10);            // Write 10 to T_ctrl Register
                                      // to set scaling Factor to 90.8%
  
  temptemp = NAVI_read(_Control1);    // Read content of Control Register 1
  temptemp &= 0x01;                   // Reset read value  but live bit 0
                                      // unchanged
  
  NAVI_Write(_Control1, 0x88 | temptemp); // result of logical OR between 
                                          // 88h and temptemp value write to
                                          // Control Register 1

  // Display first intro screen
  Glcd_Set_Font(Font_Glcd_5x7, 5, 7, 32);       // Change font
  Glcd_Write_Text(txt1,16,2,2);                 // Write text on the screen
  Glcd_Write_Text_Adv(txt2,16,26);
  delay_ms(3000);
  Glcd_Fill(0x00);
  
  // Display second intro screen
  Glcd_Write_Text_Adv(txt3,20,10);
  Glcd_Write_Text_Adv(txt4,20,20);
  Glcd_Write_Text_Adv(txt5,20,30);
  Glcd_Write_Text_Adv(txt6,20,40);
  delay_ms(4000);
  Glcd_Fill(0x00);
  
  while(1){
    // Get joystick position
    x_reg = NAVI_read(_X);
    x_reg -= 4;
    y_reg = NAVI_read(_Y_RES_INT);
    y_reg += 2;

    // Depend on joystick position recalculate position on the screen
    if ( x_reg > 0 )
     dot_x = 64-abs(x_reg/2);
    else
     dot_x = 63+abs(x_reg/2);
  
    if ( y_reg > 0 )
     dot_y = 32-abs(y_reg/4);
    else
     dot_y = 31+abs(y_reg/4);
  
    // Stabilization of central point
    if (abs(x_reg)<10)
      dot_x=64;
    if (abs(y_reg)<10)
      dot_y=32;
   
    draw_cross();
    dot_x_old=dot_x; // Cross that has been drawn
    dot_y_old=dot_y; //   becomes "old one"
   
    // Detect press of joystick button
    if(NAVI_TST==0)
     navi_button_pressed = 1;
  
    // Detect release of joystick button
    if((NAVI_TST) && (navi_button_pressed)){
      navi_button_pressed = 0;
    
    frame_flag=!frame_flag;
    
    if (frame_flag)
      frame_active=1;
    }
    delay_ms(50);
  }
}