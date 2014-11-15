/*
  ColorduinoPlasma - Plasma demo using Colorduino Library for Arduino
  Copyright (c) 2011 Sam C. Lin lincomatic@hotmail.com ALL RIGHTS RESERVED
  
  based on  Color cycling plasma
    Version 0.1 - 8 July 2009
    Copyright (c) 2011 Sam C. Lin.  All Rights Reserved
    Copyright (c) 2009 Ben Combee.  All right reserved.
    Copyright (c) 2009 Ken Corey.  All right reserved.
    Copyright (c) 2008 Windell H. Oskay.  All right reserved.
  
  This demo is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.
  
  This demo is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.
  
  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include <Colorduino.h>

void setup() {
  Serial.begin(9600);
  Colorduino.Init(); // initialize the board
  
  // compensate for relative intensity differences in R/G/B brightness
  // array of 6-bit base values for RGB (0~63)
  // whiteBalVal[0] = red
  // whiteBalVal[1] = green
  // whiteBalVal[2] = blue
  unsigned char whiteBalVal[3] = {36,63,63}; // for LEDSEE 6x6cm round matrix
  Colorduino.SetWhiteBal(whiteBalVal);
  
  // to adjust white balance you can uncomment this line
  // and comment out the plasma_morph() in loop()
  // and then experiment with whiteBalVal above
  // Colorduino.ColorFill(255,255,255);
  Colorduino.attachbackgroundcolor(backgroundcolor);
}

String Text = "ColorDuino";

int textcolor0[3] = {0, 125, 125};
int textcolor1[3] = {125, 0, 125};
int textcolor2[3] = {0, 0, 125};
int textcolor3[3] = {125, 125, 0};
int textcolor4[3] = {255, 0, 0};
int textcolor5[3] = {0, 255, 0};
int textcolor6[3] = {0, 0, 255};

int* colorarray[] = {textcolor0, textcolor1, textcolor2, textcolor3, textcolor4, textcolor5, textcolor6};

void loop() {
  delay(1000);
  //                                Text,Speed,textcolor, members of array
  Colorduino.Scroll_Text_Multicolor(Text, 125, colorarray, 7);
}

void backgroundcolor() {
  //ColorFill(  R,  G,  B)
  Colorduino.ColorFill(0, 0, 0);
  //Colorduino.ColorFill(255, 255, 255);
  //Colorduino.plasma_morph();
}
