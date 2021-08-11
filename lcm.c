// lcm.c

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"


static xSemaphoreHandle display_mutex;

static void LCM_Character(unsigned char * bCharacter)
{
	while(bCharacter[0] != '\0')
	{
		gpio_set_level(GPIO_LCM_DATA_RS, true);//RS
		gpio_set_level(GPIO_LCM_DATA_RW, false);//RW
		ets_delay_us(3);	
	
		gpio_set_level(GPIO_LCM_DATA_D0, (bCharacter[0] & 0x01));
		gpio_set_level(GPIO_LCM_DATA_D1, (bCharacter[0] & 0x02)>>1);
		gpio_set_level(GPIO_LCM_DATA_D2, (bCharacter[0] & 0x04)>>2);
		gpio_set_level(GPIO_LCM_DATA_D3, (bCharacter[0] & 0x08)>>3);
		gpio_set_level(GPIO_LCM_DATA_D4, (bCharacter[0] & 0x10)>>4);
		gpio_set_level(GPIO_LCM_DATA_D5, (bCharacter[0] & 0x20)>>5);
		gpio_set_level(GPIO_LCM_DATA_D6, (bCharacter[0] & 0x40)>>6);
		gpio_set_level(GPIO_LCM_DATA_D7, (bCharacter[0] & 0x80)>>7);
		ets_delay_us(50);
		gpio_set_level(GPIO_LCM_DATA_EN, true);
		ets_delay_us(3);
		gpio_set_level(GPIO_LCM_DATA_EN, false);
		ets_delay_us(3);
		gpio_set_level(GPIO_LCM_DATA_RS, false);//RS
		gpio_set_level(GPIO_LCM_DATA_RW, false);//RW
		ets_delay_us(3);
		bCharacter++;
	}
}

static void LCM_commmand(uint8_t bcommand)
{
	gpio_set_level(GPIO_LCM_DATA_RS, false);//RS
	gpio_set_level(GPIO_LCM_DATA_RW, false);//RW

	gpio_set_level(GPIO_LCM_DATA_D0, (bcommand&0x01));
	gpio_set_level(GPIO_LCM_DATA_D1, (bcommand&0x02)>>1);
	gpio_set_level(GPIO_LCM_DATA_D2, (bcommand&0x04)>>2);
	gpio_set_level(GPIO_LCM_DATA_D3, (bcommand&0x08)>>3);
	gpio_set_level(GPIO_LCM_DATA_D4, (bcommand&0x10)>>4);
	gpio_set_level(GPIO_LCM_DATA_D5, (bcommand&0x20)>>5);
	gpio_set_level(GPIO_LCM_DATA_D6, (bcommand&0x40)>>6);
	gpio_set_level(GPIO_LCM_DATA_D7, (bcommand&0x80)>>7);
	ets_delay_us(3);
	gpio_set_level(GPIO_LCM_DATA_EN, true);
	ets_delay_us(3);
	gpio_set_level(GPIO_LCM_DATA_EN, false);
}

void show_string_lcm(int ilocation, unsigned char* text)
{
	
	if( xSemaphoreTake( display_mutex, 10) == pdTRUE )
	{
	
		if(ilocation >= 40)
		{
			ilocation = (ilocation/2)-4;
		}
		else if((ilocation >= 10) && (ilocation <= 15))
			ilocation = (ilocation-5);

		LCM_commmand(LCD_SETDDRAMADDR|ilocation);
		LCM_Character(text);
	
		xSemaphoreGive(display_mutex);
	}
}

void LCM_BLINK(bool bOn)
{
	ets_delay_us(50000);
	if (bOn)
	{
		LCM_commmand(LCD_DISPLAYCONTROL|LCD_DISPLAYON|LCD_CURSORON|LCD_BLINKON);
	}
	else
	{
		LCM_commmand(LCD_DISPLAYCONTROL|LCD_DISPLAYON|LCD_CURSOROFF|LCD_BLINKOFF);
	}
}

void DS_LCM_init(void)
{
	display_mutex  = xSemaphoreCreateMutex();

	//check mode
	LCM_commmand(LCD_FUNCTIONSET|LCD_8BITMODE|LCD_2LINE|LCD_5x8DOTS);//8bit mode/2line/5x8dot
	ets_delay_us(50000);
	LCM_commmand(LCD_FUNCTIONSET|LCD_8BITMODE|LCD_2LINE|LCD_5x8DOTS);//8bit mode/2line/5x8dot
	ets_delay_us(50000);
	LCM_commmand(LCD_FUNCTIONSET|LCD_8BITMODE|LCD_2LINE|LCD_5x8DOTS);//8bit mode/2line/5x8dot
	ets_delay_us(50000);
	LCM_commmand(LCD_FUNCTIONSET|LCD_8BITMODE|LCD_2LINE|LCD_5x8DOTS);//8bit mode/2line/5x8dot

	ets_delay_us(10000);
	LCM_commmand(LCD_DISPLAYCONTROL);//display off
	ets_delay_us(10000);
	LCM_commmand(LCD_CLEARDISPLAY);//display clear
	ets_delay_us(10000);
	LCM_commmand(LCD_ENTRYMODESET|LCD_ENTRYRIGHT);//entry mode setting
	//===========================================
	LCM_BLINK(false);
	ets_delay_us(50000);
	LCM_commmand(LCD_CURSORSHIFT|LCD_CURSORSHIFT_RIGHT);
}

