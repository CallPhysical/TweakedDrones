/* 
    Based on 8knobs Drones, which is based on Control_Oscil_Wash
    Analog Inputs: A0-A7, two switches on Digital 2 and 3 
    Switch waveforms using toggle switch on pin 2, 3
    
    Only check two of the eight pots each cycle to avoid clicking at high CONTROL_RATE
    
*/

#include <MozziGuts.h>
#include <Oscil.h>
#include <tables/sin2048_int8.h>
#include <tables/cos2048_int8.h>
#include <tables/triangle_valve_2_2048_int8.h>
#include <tables/saw2048_int8.h>
#define CONTROL_RATE 128

// harmonics
Oscil<SIN2048_NUM_CELLS, AUDIO_RATE> aOsc1;
Oscil<SIN2048_NUM_CELLS, AUDIO_RATE> aOsc2;
Oscil<SIN2048_NUM_CELLS, AUDIO_RATE> aOsc3;
Oscil<SIN2048_NUM_CELLS, AUDIO_RATE> aOsc4;
Oscil<SIN2048_NUM_CELLS, AUDIO_RATE> aOsc5;
Oscil<SIN2048_NUM_CELLS, AUDIO_RATE> aOsc6;
Oscil<SIN2048_NUM_CELLS, AUDIO_RATE> aOsc7;
Oscil<SIN2048_NUM_CELLS, AUDIO_RATE> aOsc8;

// volume controls
Oscil<SIN2048_NUM_CELLS, CONTROL_RATE> kVol1;
Oscil<SIN2048_NUM_CELLS, CONTROL_RATE> kVol2;
Oscil<SIN2048_NUM_CELLS, CONTROL_RATE> kVol3;
Oscil<SIN2048_NUM_CELLS, CONTROL_RATE> kVol4;
Oscil<SIN2048_NUM_CELLS, CONTROL_RATE> kVol5;
Oscil<SIN2048_NUM_CELLS, CONTROL_RATE> kVol6;
Oscil<SIN2048_NUM_CELLS, CONTROL_RATE> kVol7;
Oscil<SIN2048_NUM_CELLS, CONTROL_RATE> kVol8;

// 
char v1,v2,v3,v4,v5,v6,v7,v8;
int pot = 0;
int wav = 0;
int oldWav = 0;

void setup(){
//Serial.begin(9600);
  // set harmonic frequencies
  aOsc1.setFreq(100);
  aOsc2.setFreq(100);
  aOsc3.setFreq(100);
  aOsc4.setFreq(100);
  aOsc5.setFreq(100);
  aOsc6.setFreq(100);
  aOsc7.setFreq(100);
  aOsc8.setFreq(100);

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

  pinMode(2, INPUT_PULLUP); 
  pinMode(3, INPUT_PULLUP);   

  startMozzi(CONTROL_RATE);
  setupFastAnalogRead(FASTEST_ADC);
  
}

void setTable1() {
      aOsc1.setTable(SIN2048_DATA);
      aOsc2.setTable(SIN2048_DATA);
      aOsc3.setTable(SIN2048_DATA);
      aOsc4.setTable(SIN2048_DATA);
      aOsc5.setTable(SIN2048_DATA);
      aOsc6.setTable(SIN2048_DATA);
      aOsc7.setTable(SIN2048_DATA);
      aOsc8.setTable(SIN2048_DATA);  
  
      kVol1.setTable(SIN2048_DATA);
      kVol2.setTable(SIN2048_DATA);
      kVol3.setTable(SIN2048_DATA);
      kVol4.setTable(SIN2048_DATA);
      kVol5.setTable(SIN2048_DATA);
      kVol6.setTable(SIN2048_DATA);
      kVol7.setTable(SIN2048_DATA);
      kVol8.setTable(SIN2048_DATA);  
      }
      
void setTable2() {
      aOsc1.setTable(COS2048_DATA);
      aOsc2.setTable(COS2048_DATA);
      aOsc3.setTable(COS2048_DATA);
      aOsc4.setTable(COS2048_DATA);
      aOsc5.setTable(COS2048_DATA);
      aOsc6.setTable(COS2048_DATA);
      aOsc7.setTable(COS2048_DATA);
      aOsc8.setTable(COS2048_DATA);  
  
      kVol1.setTable(COS2048_DATA);
      kVol2.setTable(COS2048_DATA);
      kVol3.setTable(COS2048_DATA);
      kVol4.setTable(COS2048_DATA);
      kVol5.setTable(COS2048_DATA);
      kVol6.setTable(COS2048_DATA);
      kVol7.setTable(COS2048_DATA);
      kVol8.setTable(COS2048_DATA);  
      }
      
void setTable3() {
      aOsc1.setTable(TRIANGLE_VALVE_2_2048_DATA);
      aOsc2.setTable(TRIANGLE_VALVE_2_2048_DATA);
      aOsc3.setTable(TRIANGLE_VALVE_2_2048_DATA);
      aOsc4.setTable(TRIANGLE_VALVE_2_2048_DATA);
      aOsc5.setTable(TRIANGLE_VALVE_2_2048_DATA);
      aOsc6.setTable(TRIANGLE_VALVE_2_2048_DATA);
      aOsc7.setTable(TRIANGLE_VALVE_2_2048_DATA);
      aOsc8.setTable(TRIANGLE_VALVE_2_2048_DATA);  
  
      kVol1.setTable(TRIANGLE_VALVE_2_2048_DATA);
      kVol2.setTable(TRIANGLE_VALVE_2_2048_DATA);
      kVol3.setTable(TRIANGLE_VALVE_2_2048_DATA);
      kVol4.setTable(TRIANGLE_VALVE_2_2048_DATA);
      kVol5.setTable(TRIANGLE_VALVE_2_2048_DATA);
      kVol6.setTable(TRIANGLE_VALVE_2_2048_DATA);
      kVol7.setTable(TRIANGLE_VALVE_2_2048_DATA);
      kVol8.setTable(TRIANGLE_VALVE_2_2048_DATA);  
      }
      
void setTable4() {
      aOsc1.setTable(SAW2048_DATA);
      aOsc2.setTable(SAW2048_DATA);
      aOsc3.setTable(SAW2048_DATA);
      aOsc4.setTable(SAW2048_DATA);
      aOsc5.setTable(SAW2048_DATA);
      aOsc6.setTable(SAW2048_DATA);
      aOsc7.setTable(SAW2048_DATA);
      aOsc8.setTable(SAW2048_DATA);  
  
      kVol1.setTable(SAW2048_DATA);
      kVol2.setTable(SAW2048_DATA);
      kVol3.setTable(SAW2048_DATA);
      kVol4.setTable(SAW2048_DATA);
      kVol5.setTable(SAW2048_DATA);
      kVol6.setTable(SAW2048_DATA);
      kVol7.setTable(SAW2048_DATA);
      kVol8.setTable(SAW2048_DATA);  
    } 

void updateControl(){
  // read only two of the pots per update to reduce the clicking
  // read the oscillator switch only every 5th cycle

  pot++; // select the next pot number which runs from 1 to 5 
  
  switch (pot) { // decide which pots to read
    case 1:
    aOsc1.setFreq((mozziAnalogRead(A0))<<2);
    aOsc2.setFreq((mozziAnalogRead(A1))<<2);
    break;
    case 2:
    aOsc3.setFreq((mozziAnalogRead(A2))<<2);
    aOsc4.setFreq((mozziAnalogRead(A3))<<2);
    break;
    case 3:
    aOsc5.setFreq((mozziAnalogRead(A4))<<2);
    aOsc6.setFreq((mozziAnalogRead(A5))<<2);
    break;
    case 4:
    aOsc7.setFreq((mozziAnalogRead(A6))<<2);
    aOsc8.setFreq((mozziAnalogRead(A7))<<2);
    break;
    case 5:
    // every fifth cycle also check the oscillator switches
    wav = digitalRead(2) + (digitalRead(3)<<1);  
    if (wav!=oldWav) // only swap the tables if the switch position is different from before
      {
      switch (wav) {
          case 1:
          setTable1();
          break;
          case 2:
          setTable2();
          break;
          case 3:
          setTable3();
          break;
          default: // case 0
          setTable4();
          break;      
          } // end of switch wav
      oldWav = wav;
      }
  
    
    pot=0;   // reset the pot cycle to 0 (It'll be incremented on the next update)
    break;
    }  // end of switch sensor
    
   v1 = kVol1.next(); // 
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
    aOsc1.next()*v1 +
    aOsc2.next()*v2 +
    aOsc3.next()*v3 +
    aOsc4.next()*v4 +
    aOsc5.next()*v5 +
    aOsc6.next()*v6 +
    aOsc7.next()*v7 +
    aOsc8.next()*v8;
  asig >>= 9;
  return (int) asig;
}
  
void loop(){
  audioHook();
}
