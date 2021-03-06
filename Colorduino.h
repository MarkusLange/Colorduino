/*
  Colorduino - Colorduino Library for Arduino
  Copyright (c) 2011-2012 Sam C. Lin <lincomatic@hotmail.com>
    based on C code by zzy@iteadstudio
  Copyright (c) 2010 zzy@IteadStudio.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/
#ifndef _COLORDUINO_H_
	#define _COLORDUINO_H_

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
	#include "pins_arduino.h"
#endif

#include <avr/pgmspace.h> 
#include <avr/io.h>
#include <avr/interrupt.h>

#define ColorduinoBitsPerColor 8

#define ColorduinoScreenWidth 8
#define ColorduinoScreenHeight 8

/****************************************************
define the IO
****************************************************/
#if defined(ARDUINO) && ARDUINO >= 100
  #define RST_BIT digitalPinToBitMask(A2)
  #define LAT_BIT digitalPinToBitMask(A1)
  #define SLB_BIT digitalPinToBitMask(A0)
  #define SCL_BIT digitalPinToBitMask(6)
  #define SDA_BIT digitalPinToBitMask(7)
  #define RST* portOutputRegister(digitalPinToPort(A0))
  #define LAT* portOutputRegister(digitalPinToPort(A1))
  #define SLB* portOutputRegister(digitalPinToPort(A2))
  #define SCL* portOutputRegister(digitalPinToPort(6))
  #define SDA* portOutputRegister(digitalPinToPort(7))
  #define open_line0	{*portOutputRegister(digitalPinToPort(8))=digitalPinToBitMask(8);}
  #define open_line1	{*portOutputRegister(digitalPinToPort(9))=digitalPinToBitMask(9);}
  #define open_line2	{*portOutputRegister(digitalPinToPort(10))=digitalPinToBitMask(10);}
  #define open_line3	{*portOutputRegister(digitalPinToPort(11))=digitalPinToBitMask(11);}
  #define open_line4	{*portOutputRegister(digitalPinToPort(12))=digitalPinToBitMask(12);}
  #define open_line5	{*portOutputRegister(digitalPinToPort(13))=digitalPinToBitMask(13);}
  #define open_line6	{*portOutputRegister(digitalPinToPort(3))=digitalPinToBitMask(3);}
  #define open_line7	{*portOutputRegister(digitalPinToPort(4))=digitalPinToBitMask(4);}
#if defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
	#define close_all_lines	{PORTB&=0b00001111;PORTG&=0b11101111;PORTE&=0b11101111;PORTH&=0b11001111;}
#elif defined(__AVR_ATmega32U4__)
	#define close_all_lines {PORTB&=0b00001111;PORTC&=0b01111111;PORTD&=0b10101110;}
#else // 328/168
	#define close_all_lines	{PORTB&=0b11000000;PORTD&=0b11000000;}
#endif

#else // < arduino 1.0
  #if defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
    #define RST PORTF // A2 = PF2
    #define RST_BIT 0x04
    #define LAT PORTF // A1 = PF1
    #define LAT_BIT 0x02
    #define SLB PORTF // A0 = PF0
    #define SLB_BIT 0x01
    #define SCL PORTH // D6 = PH3
    #define SCL_BIT 0x08
    #define SDA PORTH // D7 = PH4
    #define SDA_BIT 0x10
    
    #define open_line0	{PORTH=0x20;} // D8  = PH5
    #define open_line1	{PORTH=0x40;} // D9  = PH6
    #define open_line2	{PORTB=0x10;} // D10 = PB4
    #define open_line3	{PORTB=0x20;} // D11 = PB5
    #define open_line4	{PORTB=0x40;} // D12 = PB6
    #define open_line5	{PORTB=0x80;} // D13 = PB7
    #define open_line6	{PORTE=0x20;} // D3  = PE5
    #define open_line7	{PORTG=0x20;} // D4  = PG5
    #define close_all_lines	{PORTH=0x00;PORTB=0x00;PORTE=0x00;PORTG=0x00;}
  #elif defined(__AVR_ATmega32U4__)
  	
  #else // 328/168
    #define RST PORTC // A2 = PC2
    #define RST_BIT 0x04
    #define LAT PORTC // A1 = PC1
    #define LAT_BIT 0x02
    #define SLB PORTC // A0 = PC0
    #define SLB_BIT 0x01
    #define SCL PORTD // D6 = PD6
    #define SCL_BIT 0x40
    #define SDA PORTD // D7 = PD7
    #define SDA_BIT 0x80
    
    #define open_line0	{PORTB=0x01;} // D8  = PB0
    #define open_line1	{PORTB=0x02;} // D9  = PB1
    #define open_line2	{PORTB=0x04;} // D10 = PB2
    #define open_line3	{PORTB=0x08;} // D11 = PB3
    #define open_line4	{PORTB=0x10;} // D12 = PB4
    #define open_line5	{PORTB=0x20;} // D13 = PB5
    #define open_line6	{PORTD=0x08;} // D3  = PD3
    #define open_line7	{PORTD=0x10;} // D4  = PD4
    #define close_all_lines	{PORTD=0x00;PORTB=0x00;}
  #endif // defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
#endif // defined(ARDUINO) && ARDUINO >= 100

#define LED_RST_SET RST|=RST_BIT
#define LED_RST_CLR RST&=~RST_BIT
#define LED_SDA_SET SDA|=SDA_BIT
#define LED_SDA_CLR SDA&=~SDA_BIT
#define LED_SCL_SET SCL|=SCL_BIT
#define LED_SCL_CLR SCL&=~SCL_BIT
#define LED_LAT_SET LAT|=LAT_BIT
#define LED_LAT_CLR LAT&=~LAT_BIT
#define LED_SLB_SET SLB|=SLB_BIT
#define LED_SLB_CLR SLB&=~SLB_BIT

typedef struct pixelRGB {
  unsigned char r;
  unsigned char g;
  unsigned char b;
} PixelRGB;

class ColorduinoObject {
  private:
  	void _IO_Init();
  	void _LED_Init();
    void _TC_Init();
    void LED_Delay(unsigned char i);
  public:
    PixelRGB frameBuffer0[ColorduinoScreenWidth*ColorduinoScreenHeight];
    PixelRGB frameBuffer1[ColorduinoScreenWidth*ColorduinoScreenHeight];
    PixelRGB *curDrawFrame;
    PixelRGB *curWriteFrame;
    unsigned char line;
    boolean morphinit_bool;
    
    unsigned char plasma[ColorduinoScreenWidth][ColorduinoScreenHeight];
		long paletteShift;
    
    typedef struct {
      unsigned char r;
      unsigned char g;
      unsigned char b;
    } ColorRGB;
    
    //a color with 3 components: h, s and v
    typedef struct {
      unsigned char h;
      unsigned char s;
      unsigned char v;
    } ColorHSV;
    
    ColorduinoObject() {
      line = 0;
      curWriteFrame = frameBuffer0;
      curDrawFrame = frameBuffer1;
    }
    
    void SetWhiteBal(unsigned char wbval[3]);
    void open_line(unsigned char x);
    void Init();
    void FlipPage();
    void run();
    void HSVtoRGB(void *vRGB, void *vHSV);
    void morphinit();
    void plasma_morph();
    void Create_Letter(uint8_t letters[][5], int drift, int tc[3]);
    void Scroll_Text(String text, int speed, int tc[3]);
    void Scroll_Text_inverted(String text, int speed);
    void Scroll_Text_Multicolor(String text, int speed, int* tc[], int varies);
    
    void attachbackgroundcolor (void (*)(void));
    
    float dist(float a, float b, float c, float d) {
      return sqrt((c - a)*(c - a) + (d - b)*(d - b));
    }
  	
    // get a pixel for writing in the offscreen framebuffer
    PixelRGB *GetPixel(unsigned char x, unsigned char y) {
      return curWriteFrame + (y * ColorduinoScreenWidth) + x;
    }
  	
    // get a pixel from the active framebuffer
    PixelRGB *GetDrawPixel(unsigned char x, unsigned char y) {
      return curDrawFrame + (y * ColorduinoScreenWidth) + x;
    }
  	
    // set a pixel in the offscreen frame buffer
    void SetPixel(unsigned char x, unsigned char y, unsigned char r, unsigned char g, unsigned char b);
  	
    /**************************************************
    Name: ColorFill
    Function:  Fill the frame with a color
    Parameter: R: the value of RED.   Range:RED 0~255
               G: the value of GREEN. Range:RED 0~255
               B: the value of BLUE.  Range:RED 0~255
    ***************************************************/
    void ColorFill(unsigned char R,unsigned char G,unsigned char B);
};

extern ColorduinoObject Colorduino;

#endif // _COLORDUINO_H_