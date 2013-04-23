
/**
 * Arduino LED Array Controller
 * A controller for the LU-3011 11-array 7-segment display with dot.
 * 
 * @author Dritan Xhabija
 * Copyright (C) 2012 Dritan Xhabija
 * For more context see http://ohthosegadgets.com/led-display-module
 * Licensed under the GNU General Public License, version 3 (GPL-3.0)
 * Found at http://opensource.org/licenses/GPL-3.0 
 */


#include "segment_controller.h"

//how fast the left/right scrolling should be
#define FLASH_SPEED 1000

#define SCROLL_SPEED 10
#define SCROLL_RIGHT 1
#define SCROLL_LEFT -1
//which side to scroll the text
int scroll = SCROLL_LEFT;


//Define messages here yo
//and be sure to see what letters/numbers/chars you can use
// 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'l', 
// 'o', 'p', 'q', 's', "t", 'u', '1', '2', '3', '4', '5', 
// '6', '7', '8', '9', '0', '!', '-', '_', '#', '|', '+', 
// '*', '.',
#define MESSAGE_1 "    hello sup! -_#|#_ *+*+ .|+|*|.           "
#define MESSAGE_2 "    ____-----====---__-=-_-=-_-=-_____--__-=___---=_--=__--=_____-=-=-=-=-____--_-_____-_---_--___-----__- EOD"
#define MESSAGE_3 "    3.14159265358979323846264338327950288419716939937510582097494459230781640628620899862803482534       "
#define MESSAGE_4 "    abcdefghijlopqstu1234567890!-_#|+*.=         "
#define txt "    uuUUUUSSTTTUUUU01232             "
char * message = MESSAGE_4;
int sizeOfText = strlen(message);
char * revMessage = message;

//potentiometers
#define FLASH_SPEED_PIN A10
#define SCROLL_SPEED_PIN A11

#define BUTTON_1 18
#define BUTTON_2 17
#define BUTTON_3 16
#define BUTTON_4 15

#define BUZZER 21

void setup() {

  //  reverseArray();
  pinMode(FLASH_SPEED_PIN, INPUT);
  pinMode(SCROLL_SPEED_PIN, INPUT);

  pinMode(BUTTON_1, INPUT);
  pinMode(BUTTON_2, INPUT);
  pinMode(BUTTON_3, INPUT);
  pinMode(BUTTON_4, INPUT);
  pinMode(BUZZER, OUTPUT);

  digitalWrite(BUTTON_1, HIGH);
  digitalWrite(BUTTON_2, HIGH);
  digitalWrite(BUTTON_3, HIGH);
  digitalWrite(BUTTON_4, HIGH);
  digitalWrite(FLASH_SPEED_PIN, HIGH);
  digitalWrite(SCROLL_SPEED_PIN, HIGH);

  //prepare the pins associated with each digit, beginning with 1st digit
  for (int digit = 1; digit <= PIN_COUNT; digit++)  {
    pinMode(digits[digit], OUTPUT);
    digitalWrite(digits[digit], HIGH); //HIGH = OFF
  }
  //prepare the segment pins
  for (int pin =0; pin<8; pin++){
    pinMode(segments[pin], OUTPUT);
    //    digitalWrite(segments[pin], HIGH);
  }

  pinMode(13, OUTPUT); //for debug
}



int currDigit = 1; //digit counting begins at 1
int counter = 0;
int passedSeconds = 0;
boolean inButtonPress = false;
int buttonPressValue = 0;
int btnPC = 0; //button press counter;
int currBtnCount = 0;
int secCounter = 0;
int actualNumber = 9;
int currNumber = -1;

int flashSpeed = FLASH_SPEED;
int scrollSpeed = SCROLL_SPEED;

int lrToggle = -1; //left right toggle switch

int btn1, btn2, btn3, btn4;

boolean soundOff = false;
//buttons 1 to 4.. whether they're in use
boolean btn1_iu = false, btn2_iu = false, btn3_iu = false, btn4_iu = false;
int gbc = 0; //general button counter

int beginCharIx = 0;
int scrollCount = 0;
int pressCounter = 0;
// edit mode variables
boolean inEditMode = false;
int editDigit = 1;
int editAIx = 0; //edit alphabet index, for keeping track of which index the user is seeing 

void loop() {


  flashSpeed = analogRead(FLASH_SPEED_PIN);
  scrollSpeed = analogRead(SCROLL_SPEED_PIN);
  analogWrite(13, flashSpeed);
  flashSpeed *= 0.1;
  if (flashSpeed < 1){
    flashSpeed = 1;
  }

  scrollSpeed *= 0.3;


  btn1 = digitalRead(BUTTON_1);
  btn2 = digitalRead(BUTTON_2);
  btn3 = digitalRead(BUTTON_3);
  btn4 = digitalRead(BUTTON_4);

  btn1_iu = btn1 == LOW;  
  btn2_iu = btn2 == LOW;
  btn3_iu = btn3 == LOW;
  btn4_iu = btn4 == LOW;

  if (btn1_iu || btn2_iu || btn3_iu || btn4_iu){
    beep();
    /*
    if (pressCounter++ == 1){
      return;
    }

    if (btn1_iu && btn4_iu){
      if (!inEditMode){
        message = "EDIT 1";
        inEditMode = true;
      } 
      else {
        message = "EDIT 0";
        inEditMode = false;
      }

    }
*/
    if (btn3_iu && btn4_iu){
      soundOff = true;
    } 

//    if (!inEditMode){

      if (btn1_iu){
        updateMessage(MESSAGE_1);
      } 
      else if (btn2_iu){
        updateMessage(MESSAGE_2);
      } 
      else if (btn3_iu){
        updateMessage(MESSAGE_3);
      } 
      else if (btn4_iu){
        updateMessage(MESSAGE_4);

      }


      /*
    } else { //in edit mode
      if (btn1_iu){
        editAIx++;
        if (editAIx >= lettersAvailCount){
          editAIx = 0;
        }
      } else if (btn2_iu){
        editAIx--;
        if (editAIx < 0){
          editAIx = lettersAvailCount-1;
        }
      } else if (btn3_iu){
        editDigit++;
        if (editDigit>PIN_COUNT){
          editDigit = 1;
        }
      }
      handleEditMode();      
    }
    */
  }
  else {
    gbc = 0;
    pressCounter = 0;
  }
  
  showMessage();
}
int usersMessage [50];
void handleEditMode(){
    SegmentControl::turnOnDigit(editDigit);
    SegmentControl::turnOnDigitSegments(_charMap[editAIx], false); 
}
void updateMessage(char * msg){
  message = msg;
  sizeOfText = strlen(message)-6;
  beginCharIx = 0;
}

/**
 * Show message on LEDs
 */
void showMessage(){
  for (int digit=1; digit<=PIN_COUNT; digit++){
    SegmentControl::turnOnDigit(digit);
    //    SegmentControl::turnOnDigitSegments(_threeDot, false); 
    showSegmentForDigit(digit);
    delay(flashSpeed);
  }
  scrollCount++;
  if (scrollCount % scrollSpeed == 0){
    beginCharIx++;
    scrollCount = 0;
  }


  if (beginCharIx >= sizeOfText){
    beginCharIx = 0;
  }
}

char letter;
int currPIx = 0; //current position index

/**
 * Shows the segment for the current digit
 */
void showSegmentForDigit(int digit){
  int pos = beginCharIx + digit;
  letter = message[pos];


  int * segMap = NULL;
  for (int i=0; i<lettersAvailCount; i++){
    if (charsAvail[i] == letter){

      segMap = _charMap[i];
      if (letter == '3' && message[pos+1]=='.'){
        segMap = _threeDot;
      }
      break;
    }
  }

  if (segMap != NULL){
    SegmentControl::turnOnDigitSegments(segMap, false);
  } 
  else {
    //clear unkown letters, such as space                                           
    SegmentControl::clearSegments(); 
  }

}


//keeping track of which digit (from 11) to use to display something
int usingDigit = scroll == SCROLL_LEFT ? 11 : 0;
//scrollCounter is used to know how many cycles have passed for each scroll of digit
int scrollCounter = 0;



int index = 0;
int ix = 0;
int charPos = 0; //character position to currently focus on
void manageDigit(int digit){

  SegmentControl::turnOnDigit(digit);

  //  showLEDCountingSegments(); //show the counting effect

    char letter = 'm';

  if (index >= sizeOfText){
    index = 0;
  }


  if (index>0 && index % PIN_COUNT==0){
    ix++;
  }

  if (ix >= sizeOfText){
    ix = 0;
  }
  index++;

  charPos = digit + ix;
  letter = message[charPos];



  int * segMap = NULL;
  for (int i=0; i<lettersAvailCount; i++){
    if (charsAvail[i] == letter){

      segMap = _charMap[i];
      if (letter == '3' && message[charPos+1]=='.'){
        segMap = _threeDot;
        ix++; //skip the dot as a standalone character
      }
      break;
    }
  }

  if (segMap != NULL){
    SegmentControl::turnOnDigitSegments(segMap, false);
  } 
  else {
    SegmentControl::clearSegments(); 
  }

}

void beep(){
  if (soundOff){
    return;
  }
  digitalWrite(BUZZER, HIGH);
  delay(1);
  digitalWrite(BUZZER, LOW);
}

void reverseMessage(){
  //reverse the message for scrolling LEFT (right to left)
  char *first = &revMessage[0];
  char *last = &revMessage[strlen(revMessage)-1];
  while (first < last){
    char tmp = *first;
    *first = *last;
    *last = tmp;
    ++first;
    --last;
  }

}
