#ifndef segment_header_h
#define segment_header_h
#include "Arduino.h"

/**
 * Segment Control class which handles the manipulation of segments
 * throughout each digi
 *
 * @author Dritan Xhabija
 * Mar 5, 2012
 */
 

namespace SegmentControl {

    void turnOnDigit(int digit);
    void turnOnDigitSegments(int * _segments, boolean withPeriod); 
    void onAllSegments();
    void clearSegments();
    void beginLEDCounter();
    void showLEDCountingSegments(int digit);

};

 
#define PIN_COUNT 11

//represent the individual segments from the 8-segment LED display
#define TOP_RIGHT A0
#define TOP_LEFT  A1
#define BOTTOM  A2
#define MIDDLE  A3
#define TOP  A4
#define BOTTOM_LEFT  A5
#define BOTTOM_RIGHT  A6
#define DOT  A7



#define EOA -99 //end of array terminator
extern int segments [];

//each 7-segment LED display digit at index digits[] has the corresponding pin
extern int digits[];

extern int * _digitOutlines[];

extern int _zero[];
extern int _one[]; 
extern int _two[]; 
extern int _three[]; 
extern int _threeDot[];
extern int _four[]; 
extern int _five[]; 
extern int _six[]; 
extern int _seven[]; 
extern int _eight[]; 
extern int _nine[]; 


//all possible letters that can be formed
extern int _a[];
extern int _b[];
extern int _c[];
extern int _d[];
extern int _e[];
extern int _f[];
extern int _g[];
extern int _h[];
extern int _i[];
extern int _j[];
extern int _l[];
extern int _o[];
extern int _p[];
extern int _q[];
extern int _r[];
extern int _s[];
extern int _t[];
extern int _u[];
extern int _space[];

extern char charsAvail [];
extern int * _charMap [];


extern int lettersAvailCount;

#endif
