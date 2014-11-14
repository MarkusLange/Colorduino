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
#include "font.h"

void (*backgroundFunc)(void);

void attachground(void (*userFunction)(void)) {
  backgroundFunc = userFunction;
}

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
  attachground(Backbroundcolor);
}

char message[] = "The licenses for most software are designed to take away your freedom to share and change it. By contrast, the GNU General Public Licenses are intended to guarantee your freedom to share and change free software--to make sure the software is free for all its users. This license, the Lesser General Public License, applies to some specially designated software packages--typically libraries--of the Free Software Foundation and other authors who decide to use it. You can use it too, but we suggest you first think carefully about whether this license or the ordinary General Public License is the better strategy to use in any particular case, based on the explanations below.";

int textcolor[3] = {0, 125, 125};

void loop() {
  //plasma_morph();
  //ColorFill(  R,  G,  B)
  //Colorduino.ColorFill(0, 5, 0);
  delay(1000);
  Serial.println(message);
  Serial.print("Textlenght: ");
  Serial.println(sizeof(message));
  set_text(5, textcolor);
}

void Backbroundcolor() {
  Colorduino.ColorFill(0, 0, 0);
  //Colorduino.plasma_morph();
}

void set_text(int speed, int tc[3]) {
  int sidestep = 1;
  int letters = sizeof(message)-1;
  for (int m=sidestep; m>-(6*(letters)-(sidestep)-6); m--) {
    backgroundFunc();
    Colorduino.FlipPage();
    int d = 0;
    for (int i=0; i<sizeof(message); i++) {
      set_letter(sat_normal[message[i]-32], m+6*d, tc);
      d++;
    }
    Colorduino.FlipPage();
    delay(speed);
  }
}

//working
void set_letter(int letters[][5], int drift, int tc[3]) {
  int y = 1;
  for (int i=6; i>-1; i--) {
    for (int j=0; j<5; j++) {
      int pix = pgm_read_byte(&(letters[i][j]));
      int x = j + drift;
      if (pix == true && x >= 0 && x <= 7)
        Colorduino.SetPixel(x, y, tc[0], tc[1], tc[2]);
    }
    y++;
  }
}
