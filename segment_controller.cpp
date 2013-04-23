
/**
 * Segment Controller
 * Helper class that turns on or off any specified digit. There are digits and
 * characters defined comprising the alphabet of this 7-segment display with dot.
 * Additionally a number counter is provided that just increments until the max.
 * 
 * @author Dritan Xhabija
 * Copyright (C) 2012 Dritan Xhabija
 * Licensed under the GNU General Public License, version 3 (GPL-3.0)
 * Found at http://opensource.org/licenses/GPL-3.0 
 */

#include "Arduino.h"
#include "segment_controller.h"


#define EOA -99 //end of array terminator

int segments [] = {
  TOP_RIGHT, TOP_LEFT, BOTTOM, MIDDLE, TOP, BOTTOM_LEFT, BOTTOM_RIGHT, DOT
}; 

//each 7-segment LED display digit at index digits[] has the corresponding pin
//force a digit count beginning at 1
int digits[] = {
  -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10
};

int digitsReversed[] = {
  10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0
};

int _zero [] = { 
  TOP,
  TOP_LEFT,
  BOTTOM_LEFT,
  BOTTOM,
  BOTTOM_RIGHT,
  TOP_RIGHT,
  TOP,
  EOA
};

int _one [] = { 
  TOP_RIGHT,
  BOTTOM_RIGHT,
  EOA
};

int _two [] = { 
  TOP,
  TOP_RIGHT,
  MIDDLE,
  BOTTOM_LEFT,
  BOTTOM,
  EOA
};

int _three [] = { 
  TOP,
  TOP_RIGHT,
  MIDDLE,
  BOTTOM_RIGHT,
  BOTTOM,
  EOA
};

int _threeDot [] = { 
  TOP,
  TOP_RIGHT,
  MIDDLE,
  BOTTOM_RIGHT,
  BOTTOM,
  DOT,
  EOA
};

int _four [] = { 
  TOP_LEFT,
  TOP_RIGHT,
  MIDDLE,
  BOTTOM_RIGHT,
  EOA
};

int _five [] = { 
  TOP,
  TOP_LEFT,
  MIDDLE,
  BOTTOM_RIGHT,
  BOTTOM,
  EOA
};

int _six [] = { 
  TOP,
  TOP_LEFT,
  MIDDLE,
  BOTTOM_RIGHT,
  BOTTOM,
  BOTTOM_LEFT,
  EOA
};

int _seven [] = { 
  TOP,
  TOP_RIGHT,
  BOTTOM_RIGHT,
  EOA
};

int _eight [] = { 
  TOP,
  TOP_LEFT,
  BOTTOM_LEFT,
  BOTTOM,
  BOTTOM_RIGHT,
  TOP_RIGHT,
  TOP,
  MIDDLE,
  EOA
};

int _nine [] = { 
  TOP,
  TOP_LEFT,
  TOP_RIGHT,
  MIDDLE,
  BOTTOM_RIGHT,
  EOA
};


int _a [] = {
  TOP,
  TOP_RIGHT,
  TOP_LEFT,
  MIDDLE,
  BOTTOM_LEFT,
  BOTTOM_RIGHT,
  EOA
};

int _b [] = {
  TOP,
  TOP_LEFT,
  BOTTOM_LEFT,
  BOTTOM,
  BOTTOM_RIGHT,
  TOP_RIGHT,
  TOP,
  MIDDLE,
  EOA
};

int _c [] = {
  TOP,
  TOP_LEFT,
  BOTTOM_LEFT,
  BOTTOM,
  EOA
};

int _d [] = {
  MIDDLE,
  BOTTOM_LEFT,
  BOTTOM_RIGHT,
  BOTTOM,
  TOP_RIGHT,
  EOA
};

int _e [] = {
  TOP,
  TOP_LEFT,
  MIDDLE,
  BOTTOM_LEFT,
  BOTTOM,
  EOA
};

int _f [] = {
  TOP,
  TOP_LEFT,
  MIDDLE,
  BOTTOM_LEFT,
  EOA
};

int _g [] = {
  TOP,
  TOP_LEFT,
  MIDDLE,
  BOTTOM_RIGHT,
  BOTTOM,
  BOTTOM_LEFT,
  EOA 
};

int _h [] = {
  TOP_LEFT,
  TOP_RIGHT,
  MIDDLE,
  BOTTOM_LEFT,
  BOTTOM_RIGHT,
  EOA
};

int _i [] = {
  TOP_RIGHT,
  BOTTOM_RIGHT,
  EOA 
};

int _j [] = {
  TOP_RIGHT,
  BOTTOM_RIGHT,
  BOTTOM,
  EOA
};

int _l [] = {
  TOP_LEFT,
  BOTTOM_LEFT,
  BOTTOM,
  EOA
};

int _o [] = {
  TOP,
  TOP_LEFT,
  BOTTOM_LEFT,
  BOTTOM,
  BOTTOM_RIGHT,
  TOP_RIGHT,
  TOP,
  EOA
};


int _p [] = {
  TOP,
  TOP_LEFT,
  TOP_RIGHT,
  MIDDLE,
  BOTTOM_LEFT,
  EOA
};

int _q [] = {
  TOP,
  TOP_RIGHT,
  TOP_LEFT,
  MIDDLE,
  BOTTOM_RIGHT,
  EOA
};

int _s [] = {
  TOP,
  TOP_LEFT,
  MIDDLE,
  BOTTOM_RIGHT,
  BOTTOM,
  EOA
};

int _t [] = {
  TOP,
  TOP_RIGHT,
  BOTTOM_RIGHT,
  EOA
};
int _u [] = {
  TOP_LEFT,
  BOTTOM_LEFT,
  BOTTOM,
  BOTTOM_RIGHT,
  TOP_RIGHT,
  EOA
};

int _exclamation [] = {
  TOP_RIGHT,
  BOTTOM_RIGHT,
  DOT,
  EOA
};

int _dash [] = {
  MIDDLE,
  EOA
};

int _underscore [] = {
  BOTTOM,
  EOA
};

int _hashpound [] = {
  TOP,
  MIDDLE,
  BOTTOM,
  EOA
};

int _pipe [] = {
  TOP_LEFT,
  TOP_RIGHT,
  BOTTOM_LEFT,
  BOTTOM_RIGHT,
  EOA
};

int _plusRight [] = {
  TOP_LEFT,
  MIDDLE,
  BOTTOM_LEFT,
  EOA
};

int _plusLeft [] = {
  TOP_RIGHT,
  MIDDLE,
  BOTTOM_RIGHT,
  EOA
};

int _dot [] = {
  DOT,
  EOA
};

int _top[] = {
  TOP,
  EOA
};
int * _digitOutlines[] = { 
  _zero, _one, _two, _three, _four, _five, _six, _seven, _eight, _nine };
  
char charsAvail [] = { 
  'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'l', 'o', 'p', 'q', 's', 't', 'u', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '!', '-', '_', '#', '|', '+', '*', '.', '='};
int * _charMap [] = { 
  _a, _b, _c, _d, _e, _f, _g, _h, _i, _j, _l, _o, _p, _q, _s, _t, _u, _one, _two, _three, _four, _five, _six, _seven, _eight, _nine, _zero, _exclamation, _dash, _underscore, _hashpound, _pipe, _plusRight, _plusLeft, _dot, _top};

int lettersAvailCount = strlen(charsAvail);
/********************** "static class" *************************/

namespace SegmentControl {
  int digitCurrentlyOn = 1; //beginning index at 1, not 0

  /**
   * Clear all 8 segments of some digit.
   */
  void clearSegments(){
    for (int i=0; i<8; i++){
      digitalWrite(segments[i], LOW);
    }
  }

  void onAllSegments(){
    for (int i=0; i<8; i++){
      digitalWrite(segments[i], HIGH);
    }
  }


  void turnOnDigit(int digit){
    if (digit == 0){ //index
      return;
    }
    //turn off the last digit that was ON
    if (digitCurrentlyOn != digit){
      digitalWrite(digits[digitCurrentlyOn], HIGH);  //HIGH is OFF
    }

    digitCurrentlyOn = digit;

    digitalWrite(digits[digit], LOW); //LOW is ON     
  }

  void turnOnDigitSegments(int * _segments, boolean withPeriod){
    int arraySize = 8;
    clearSegments();

    for (int i=0; i<arraySize && _segments[i]!=EOA; i++){
      digitalWrite(_segments[i], HIGH);    
    }

    if (withPeriod){
      digitalWrite(DOT, HIGH);
    }
  }

  /*** LED COUNTER ***/
  int ones=0, tens=0, hundreds=0, thousands=0, tenthous=0, hundredthous=0, millionths=0, tenmillionths=0, hundredmillionths=0, billionths=0, tenbillionths=0;
  
  /**
    Must be called from loop() then show the segment for each digit via showLEDCountingSegments(int)
  */
  void beginLEDCounter(){

    ones++;

    if (ones>9){
      ones = 0;
      tens++;

      if (tens>9){
        tens = 0;
        hundreds++;

        if (hundreds>9){
          hundreds = 0;
          thousands++;

          if (thousands>9){
            thousands = 0;
            tenthous++;

            if (tenthous >9){
              tenthous = 0;
              hundredthous++;

              if (hundredthous >9){
                hundredthous = 0;
                millionths++;

                if (millionths >9){
                  millionths = 0;
                  tenmillionths++;

                  if (tenmillionths >9){
                    tenmillionths = 0;
                    hundredmillionths++;

                    if (hundredmillionths>9){
                      hundredmillionths = 0;
                      billionths++;

                      if (billionths >9){
                        billionths = 0;
                        tenbillionths++;

                        if (tenbillionths>9){
                          tenbillionths=0;
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }

  void showLEDCountingSegments(int digit){
    int num = 0;
    if (digit == 0)
      num = ones;
    else if (digit == 1)
      num = tens;
    else if (digit == 2)
      num = hundreds;
    else if (digit == 3)
      num = thousands;
    else if (digit == 4)
      num = tenthous;
    else if (digit == 5)
      num = hundredthous;
    else if (digit == 6)
      num = millionths;
    else if (digit == 7)
      num = tenmillionths;
    else if (digit == 8)
      num = hundredmillionths;
    else if (digit == 9)
      num = billionths;
    else if (digit == 10)
      num = tenbillionths;
    if (num >=0 && num < 10){
      SegmentControl::turnOnDigitSegments(_digitOutlines[num], false);
    } 
    else {
      //to distinguish for ebkac
      SegmentControl::onAllSegments();
    }
  }
}

