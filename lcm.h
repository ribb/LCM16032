// lcm.h

unsigned char cstr[]={0xB1, 0xE2, 0xB5, 0xD2, 0xD6, 0x5F, 0xAD, 0x64, 0x20, 0x20, 0xB1, 0xE2, 0xB5, 0xD2, 0xC3, 0xD2, 0xAD, 0x64};

#define GPIO_LCM_DATA_RS GPIO_NUM_21
#define GPIO_LCM_DATA_RW GPIO_NUM_2
#define GPIO_LCM_DATA_EN GPIO_NUM_4
#define GPIO_LCM_DATA_D0 GPIO_NUM_5
#define GPIO_LCM_DATA_D1 GPIO_NUM_12
#define GPIO_LCM_DATA_D2 GPIO_NUM_13
#define GPIO_LCM_DATA_D3 GPIO_NUM_14
#define GPIO_LCM_DATA_D4 GPIO_NUM_15
#define GPIO_LCM_DATA_D5 GPIO_NUM_18
#define GPIO_LCM_DATA_D6 GPIO_NUM_19
#define GPIO_LCM_DATA_D7 GPIO_NUM_23

	// LCM commands
#define LCD_CLEARDISPLAY 0x01
#define LCD_RETURNHOME 0x02
#define LCD_ENTRYMODESET 0x04
#define LCD_DISPLAYCONTROL 0x08
#define LCD_CURSORSHIFT 0x10
#define LCD_FUNCTIONSET 0x20
#define LCD_SETCGRAMADDR 0x40
#define LCD_SETDDRAMADDR 0x80
	
	// flags for function set
#define LCD_8BITMODE 0x10
#define LCD_4BITMODE 0x00
#define LCD_2LINE 0x08
#define LCD_1LINE 0x00
#define LCD_5x10DOTS 0x04
#define LCD_5x8DOTS 0x00

	// flags for display entry mode
#define LCD_ENTRYLEFT 0x03
#define LCD_ENTRYRIGHT 0x02
#define LCD_ENTRYSHIFTINCREMENT 0x01
#define LCD_ENTRYSHIFTDECREMENT 0x00
	
	// flags for display on/off control
#define LCD_DISPLAYON 0x04
#define LCD_DISPLAYOFF 0x00
#define LCD_CURSORON 0x02
#define LCD_CURSOROFF 0x00
#define LCD_BLINKON 0x01
#define LCD_BLINKOFF 0x00
	
	
	// flags for CURSOR SHIFT control
#define LCD_CURSORSHIFT_LEFT 0x00
#define LCD_CURSORSHIFT_RIGHT 0x04
#define LCD_DISPLAY_LEFT 0x08
#define LCD_DISPLAY_RIGHT 0x0C

void show_string_lcm(int ilocation, unsigned char* text);
void LCM_BLINK(bool bOn);
void DS_LCM_init(void);


