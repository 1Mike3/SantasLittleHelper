#include <joystick_click.h>

char txt1[]="Mikroelektronika";
char txt2[]="Joystick  Click  Example";
char txt3[]="Please move or press";
char txt4[]="joystick in any";
char txt5[]="desirable direction";
char txt6[]="when cross appears" ;

signed int x_reg,y_reg;
char dot_x,dot_y,dot_x_old,dot_y_old;
short temptemp;
char xx[7];
char yy[7];
int sum_x=0,sum_y=0;
char frame_flag=0, frame_active=0, navi_button_pressed=0;

void NAVI_Write(unsigned short address, unsigned short data1) {
  I2C1_Start();                 // issue I2C start signal
  I2C1_Wr(_NAVI_W_ADDRESS);     // send byte via I2C  (device address + W)
  I2C1_Wr(address);             // send byte (address of the location)
  I2C1_Wr(data1);               // send data (data to be written)
  I2C1_Stop();                  // issue I2C stop signal
}

unsigned short NAVI_Read(unsigned short address) {
  unsigned short tmp = 0;
  I2C1_Start();                 // issue I2C start signal
  I2C1_Wr(_NAVI_W_ADDRESS);     // send byte via I2C (device address + W)
  I2C1_Wr(address);             // send byte (data address)
  I2C1_Repeated_Start();        // issue I2C signal repeated start
  I2C1_Wr(_NAVI_R_ADDRESS);     // send byte (device address + R)
  tmp = I2C1_Rd(_I2C_NACK);     // Read the data (NO acknowledge)
  I2C1_Stop();                  // issue I2C stop signal
  return tmp;
}

void draw_cross(){
  // This block clears old cross
  Glcd_Dot(dot_x_old, dot_y_old, 0);
  Glcd_Dot(dot_x_old+1, dot_y_old, 0);
  Glcd_Dot(dot_x_old+2, dot_y_old, 0);
  Glcd_Dot(dot_x_old-1, dot_y_old, 0);
  Glcd_Dot(dot_x_old-2, dot_y_old, 0);
  Glcd_Dot(dot_x_old, dot_y_old+1, 0);
  Glcd_Dot(dot_x_old, dot_y_old+2, 0);
  Glcd_Dot(dot_x_old, dot_y_old-1, 0);
  Glcd_Dot(dot_x_old, dot_y_old-2, 0);
  
  //if frame_flag is set clear old frame
  if(frame_flag){
    Glcd_Line(dot_x_old-4, dot_y_old-4, dot_x_old+4, dot_y_old-4, 0);
    Glcd_Line(dot_x_old-4, dot_y_old+4, dot_x_old+4, dot_y_old+4, 0);
    Glcd_Line(dot_x_old-4, dot_y_old-4, dot_x_old-4, dot_y_old+4, 0);
    Glcd_Line(dot_x_old+4, dot_y_old-4, dot_x_old+4, dot_y_old+4, 0);
  }
  
  //This block draws new cross
  Glcd_Dot(dot_x, dot_y, 1);
  Glcd_Dot(dot_x+1, dot_y, 1);
  Glcd_Dot(dot_x+2, dot_y, 1);
  Glcd_Dot(dot_x-1, dot_y, 1);
  Glcd_Dot(dot_x-2, dot_y, 1);
  Glcd_Dot(dot_x, dot_y+1, 1);
  Glcd_Dot(dot_x, dot_y+2, 1);
  Glcd_Dot(dot_x, dot_y-1, 1);
  Glcd_Dot(dot_x, dot_y-2, 1);
  
  //if frame_flag is set draw new frame
  if(frame_flag){
    Glcd_Line(dot_x-4, dot_y-4, dot_x+4, dot_y-4, 1);
    Glcd_Line(dot_x-4, dot_y+4, dot_x+4, dot_y+4, 1);
    Glcd_Line(dot_x-4, dot_y-4, dot_x-4, dot_y+4, 1);
    Glcd_Line(dot_x+4, dot_y-4, dot_x+4, dot_y+4, 1);
  }
  //if switched to mode without frame, erase very last one
  if((frame_active)&&(frame_flag==0)) {
    Glcd_Line(dot_x_old-4, dot_y_old-4, dot_x_old+4, dot_y_old-4, 0);
    Glcd_Line(dot_x_old-4, dot_y_old+4, dot_x_old+4, dot_y_old+4, 0);
    Glcd_Line(dot_x_old-4, dot_y_old-4, dot_x_old-4, dot_y_old+4, 0);
    Glcd_Line(dot_x_old+4, dot_y_old-4, dot_x_old+4, dot_y_old+4, 0);
    frame_active = 0;
  }
}