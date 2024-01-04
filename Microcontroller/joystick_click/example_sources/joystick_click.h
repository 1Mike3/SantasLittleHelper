#define _ID_CODE 0x0C                   //   Manufacture ID code
#define _ID_VERSION 0x0D                //    Component ID version
#define _SIL_REV 0x0E                   //    Silicon revision
#define _Control1 0x0F                  //   Control register 1
#define _X 0x10                         //    Result x
#define _Y_RES_INT 0x11                 //    Result y
#define _XP 0x12                        //    Positive X direction
#define _XN 0x13                        //    Negative X direction
#define _YP 0x14                        //    Positive Y direction
#define _YN 0x15                        //    Negative Y direction
#define _AGC 0x2A                       //    AGC
#define _M_CTRL 0x2B                    //    Control register for the middle Hall element C5
#define _J_CTRL 0x2C                    //    Control register for the sector dependent attenuation of the outer Hall elements
#define _T_CTRL 0x2D                    //    Scale input to fit to the 8 bit result register
#define _Control2 0x2E                  //   Control register 2
#define _NAVI_W_ADDRESS  0x80           //DEVICE WRITE ADDRES - 80 ( if jumper in I2 position) or  82
#define _NAVI_R_ADDRESS  0x81           //DEVICE WRITE ADDRES - 81 (if jumper in I2 position) or  83

//Commands:
#define F_50 'A'
#define F_75 'B'
#define F_100 'C'
#define B_50 'D'
#define B_75 'E'
#define B_100 'F'
#define FL_50 'G'
#define FL_75 'H'
#define BL_50 'I'
#define BL_75 'J'
#define FR_50 'K'
#define FR_75 'L'
#define BR_50 'M'
#define BR_75 'N'
#define CIRCLE_R50 'O'
#define CIRCLE_R75 'P'
#define CIRCLE_R100 'Q'
#define CIRCLE_L50 'R'
#define CIRCLE_L75 'S'
#define CIRCLE_L100 'T'
#define BRAKE 'U'

extern signed short x_reg,y_reg;
extern char dot_x,dot_y,dot_x_old,dot_y_old;
extern char txt1[],txt2[],txt3[],txt4[],txt5[],txt6[];
extern short temptemp;
extern char xx[7];
extern char yy[7];
extern int sum_x=0,sum_y=0;
extern char frame_flag=0, frame_active=0, navi_button_pressed=0;
extern sfr sbit NAVI_TST_Dir;
extern sfr sbit NAVI_RST_Dir;
extern sfr sbit NAVI_TST;
extern sfr sbit NAVi_RST;

void NAVI_Write(unsigned short address, unsigned short data1);
unsigned short NAVI_Read(unsigned short address);
void draw_cross();