/* 
    Based on 8knobs Drones
    Analog Inputs: A0-A5, A6 - A11 (on digital pins 4, 6, 8, 9, 10, and 12). 
    Modified to switch waveforms using toggle switch on pin 2, 3
    Only check one of the eight pots each cycle to avoid clicking at high CONTROL_RATE
    
*/

#include <MozziGuts.h>
#include <Oscil.h>
#include <tables/sin2048_int8.h>
#include <tables/cos2048_int8.h>
#include <tables/triangle_valve_2_2048_int8.h>
#include <tables/saw2048_int8.h>
#define CONTROL_RATE 64

// harmonics
Oscil<SIN2048_NUM_CELLS, AUDIO_RATE> aCos1(SIN2048_DATA);
Oscil<SIN2048_NUM_CELLS, AUDIO_RATE> aCos2(SIN2048_DATA);
Oscil<SIN2048_NUM_CELLS, AUDIO_RATE> aCos3(SIN2048_DATA);
Oscil<SIN2048_NUM_CELLS, AUDIO_RATE> aCos4(SIN2048_DATA);
Oscil<SIN2048_NUM_CELLS, AUDIO_RATE> aCos5(SIN2048_DATA);
Oscil<SIN2048_NUM_CELLS, AUDIO_RATE> aCos6(SIN2048_DATA);
Oscil<SIN2048_NUM_CELLS, AUDIO_RATE> aCos7(SIN2048_DATA);
Oscil<SIN2048_NUM_CELLS, AUDIO_RATE> aCos8(SIN2048_DATA);

// volume controls
Oscil<SIN2048_NUM_CELLS, CONTROL_RATE> kVol1(SIN2048_DATA);
Oscil<SIN2048_NUM_CELLS, CONTROL_RATE> kVol2(SIN2048_DATA);
Oscil<SIN2048_NUM_CELLS, CONTROL_RATE> kVol3(SIN2048_DATA);
Oscil<SIN2048_NUM_CELLS, CONTROL_RATE> kVol4(SIN2048_DATA);
Oscil<SIN2048_NUM_CELLS, CONTROL_RATE> kVol5(SIN2048_DATA);
Oscil<SIN2048_NUM_CELLS, CONTROL_RATE> kVol6(SIN2048_DATA);
Oscil<SIN2048_NUM_CELLS, CONTROL_RATE> kVol7(SIN2048_DATA);
Oscil<SIN2048_NUM_CELLS, CONTROL_RATE> kVol8(SIN2048_DATA);

// 
char v1,v2,v3,v4,v5,v6,v7,v8;
int pot;
void setup(){

  // set harmonic frequencies
  aCos1.setFreq(100);
  aCos2.setFreq(100);
  aCos3.setFreq(100);
  aCos4.setFreq(100);
  aCos5.setFreq(100);
  aCos6.setFreq(100);
  aCos7.setFreq(100);
  aCos8.setFreq(100);

// set volume change freq
  kVol1.setFreq(0.21f); 
  kVol2.setFreq(0.0245f);
  kVol3.setFreq(0.019f);
  kVol4.setFreq(0.07f);
  kVol5.setFreq(0.047f);
  kVol6.setFreq(0.031f);
  kVol7.setFreq(0.0717f);
  kVol8.setFreq(0.041f);

  v1=v2=v3=v4=v5=v6=v7=v8=127;
  pot=0;
  pinMode(2, INPUT_PULLUP); 
  pinMode(3, INPUT_PULLUP);   
  startMozzi(CONTROL_RATE);
}

void loop(){
  audioHook();
}


void updateControl(){
  int sensorVal1; 
  int sensorVal2;

  
  pot++; // select the next pot number
  if (pot==9) { // reset the pot number back to zero
    pot=0;
    }
  switch (pot) {
    case 0:
    aCos1.setFreq((mozziAnalogRead(A0))*4);
    break;
    case 1:
    aCos2.setFreq((mozziAnalogRead(A1))*4);
    break;
    case 2:
    aCos3.setFreq((mozziAnalogRead(A2))*4);
    break;   
    case 3:
    aCos4.setFreq((mozziAnalogRead(A3))*4);
    break;
    case 4:
    aCos5.setFreq((mozziAnalogRead(A4))*4);
    break;
    case 5:
    aCos6.setFreq((mozziAnalogRead(A5))*4);
    break;
    case 6:
    aCos7.setFreq((mozziAnalogRead(A6))*4);
    break;
    case 7:
    aCos8.setFreq((mozziAnalogRead(A7))*4);
    break;
    case 8:
    // every ninth cycle also check the waveform switches
    sensorVal1= digitalRead(2); 
    sensorVal2 = digitalRead(3); 
    if (sensorVal1 == HIGH && sensorVal2 == HIGH) 
    {
      aCos1.setTable(SIN2048_DATA);
      aCos2.setTable(SIN2048_DATA);
      aCos3.setTable(SIN2048_DATA);
      aCos4.setTable(SIN2048_DATA);
      aCos5.setTable(SIN2048_DATA);
      aCos6.setTable(SIN2048_DATA);
      aCos7.setTable(SIN2048_DATA);
      aCos8.setTable(SIN2048_DATA);  
  
      kVol1.setTable(SIN2048_DATA);
      kVol2.setTable(SIN2048_DATA);
      kVol3.setTable(SIN2048_DATA);
      kVol4.setTable(SIN2048_DATA);
      kVol5.setTable(SIN2048_DATA);
      kVol6.setTable(SIN2048_DATA);
      kVol7.setTable(SIN2048_DATA);
      kVol8.setTable(SIN2048_DATA);  
      
    }
    else if (sensorVal1 == HIGH && sensorVal2 == LOW) 
    {
      aCos1.setTable(COS2048_DATA);
      aCos2.setTable(COS2048_DATA);
      aCos3.setTable(COS2048_DATA);
      aCos4.setTable(COS2048_DATA);
      aCos5.setTable(COS2048_DATA);
      aCos6.setTable(COS2048_DATA);
      aCos7.setTable(COS2048_DATA);
      aCos8.setTable(COS2048_DATA);  
  
      kVol1.setTable(COS2048_DATA);
      kVol2.setTable(COS2048_DATA);
      kVol3.setTable(COS2048_DATA);
      kVol4.setTable(COS2048_DATA);
      kVol5.setTable(COS2048_DATA);
      kVol6.setTable(COS2048_DATA);
      kVol7.setTable(COS2048_DATA);
      kVol8.setTable(COS2048_DATA);  
    }
    else if (sensorVal1 == LOW && sensorVal2 == HIGH) 
    {
      aCos1.setTable(TRIANGLE_VALVE_2_2048_DATA);
      aCos2.setTable(TRIANGLE_VALVE_2_2048_DATA);
      aCos3.setTable(TRIANGLE_VALVE_2_2048_DATA);
      aCos4.setTable(TRIANGLE_VALVE_2_2048_DATA);
      aCos5.setTable(TRIANGLE_VALVE_2_2048_DATA);
      aCos6.setTable(TRIANGLE_VALVE_2_2048_DATA);
      aCos7.setTable(TRIANGLE_VALVE_2_2048_DATA);
      aCos8.setTable(TRIANGLE_VALVE_2_2048_DATA);  
  
      kVol1.setTable(TRIANGLE_VALVE_2_2048_DATA);
      kVol2.setTable(TRIANGLE_VALVE_2_2048_DATA);
      kVol3.setTable(TRIANGLE_VALVE_2_2048_DATA);
      kVol4.setTable(TRIANGLE_VALVE_2_2048_DATA);
      kVol5.setTable(TRIANGLE_VALVE_2_2048_DATA);
      kVol6.setTable(TRIANGLE_VALVE_2_2048_DATA);
      kVol7.setTable(TRIANGLE_VALVE_2_2048_DATA);
      kVol8.setTable(TRIANGLE_VALVE_2_2048_DATA);  
    }
     else
    {
      aCos1.setTable(SAW2048_DATA);
      aCos2.setTable(SAW2048_DATA);
      aCos3.setTable(SAW2048_DATA);
      aCos4.setTable(SAW2048_DATA);
      aCos5.setTable(SAW2048_DATA);
      aCos6.setTable(SAW2048_DATA);
      aCos7.setTable(SAW2048_DATA);
      aCos8.setTable(SAW2048_DATA);  
  
      kVol1.setTable(SAW2048_DATA);
      kVol2.setTable(SAW2048_DATA);
      kVol3.setTable(SAW2048_DATA);
      kVol4.setTable(SAW2048_DATA);
      kVol5.setTable(SAW2048_DATA);
      kVol6.setTable(SAW2048_DATA);
      kVol7.setTable(SAW2048_DATA);
      kVol8.setTable(SAW2048_DATA);  
    } 
    break;

    }  // end of switch
    
   v1 = kVol1.next()>>1; // 
   v2 = kVol2.next();
   v3 = kVol3.next();
   v4 = kVol4.next();
   v5 = kVol5.next();
   v6 = kVol6.next();
   v7 = kVol7.next();
   v8 = kVol8.next();
}

int updateAudio(){
  long asig = (long)
    aCos1.next()*v1 +
    aCos2.next()*v2 +
    aCos3.next()*v3 +
    aCos4.next()*v4 +
    aCos5.next()*v5 +
    aCos6.next()*v6 +
    aCos7.next()*v7 +
    aCos8.next()*v8;
  asig >>= 9;
  return (int) asig;
}
