/*
       /$$   /$$ /$$$$$$$$ /$$       /$$$$$$  /$$$$$$   /$$$$$$       /$$$$$$$  /$$$$$$$   /$$$$$$  /$$   /$$ /$$$$$$$$          
      | $$  | $$| $$_____/| $$      |_  $$_/ /$$__  $$ /$$__  $$     | $$  | $$| $$__  $$ /$$__  $$| $$$ | $$| $$_____/          
      | $$  | $$| $$      | $$        | $$  | $$  \ $$| $$  \__/     | $$  | $$| $$  | $$| $$  \ $$| $$$$| $$| $$                
      | $$$$$$$$| $$$$$   | $$        | $$  | $$  | $$|  $$$$$$      | $$  | $$| $$$$$$  | $$  | $$| $$ $$ $$| $$$$$             
      | $$__  $$| $$__/   | $$        | $$  | $$  | $$ \____  $$     | $$  | $$| $$__  $$| $$  | $$| $$  $$$$| $$__/             
      | $$  | $$| $$      | $$        | $$  | $$  | $$ /$$  \ $$     | $$  | $$| $$  | $$| $$  | $$| $$\  $$$| $$                
      | $$  | $$| $$$$$$$$| $$$$$$$$ /$$$$$$|  $$$$$$/|  $$$$$$/     | $$$$$$$$| $$  | $$|  $$$$$$/| $$ \  $$| $$$$$$$$          
      |__/  |__/|________/|________/|______/ \______/  \______/      |________/|__/  |__/ \______/ |__/  \__/|________/          
                                                                                                              
                                                                                                              
                                                                                                              
                                       /$$     /$$                           /$$                              
                                      | $$    | $$                          |__/                              
        /$$$$$$$ /$$   /$$ /$$$$$$$  /$$$$$$  | $$$$$$$   /$$$$$$   /$$$$$$$ /$$ /$$$$$$$$  /$$$$$$   /$$$$$$ 
       /$$_____/| $$  | $$| $$__  $$|_  $$_/  | $$__  $$ /$$__  $$ /$$_____/| $$|____ /$$/ /$$__  $$ /$$__  $$
      |  $$$$$$ | $$  | $$| $$  \ $$  | $$    | $$  \ $$| $$$$$$$$|  $$$$$$ | $$   /$$$$/ | $$$$$$$$| $$  \__/
       \____  $$| $$  | $$| $$  | $$  | $$ /$$| $$  | $$| $$_____/ \____  $$| $$  /$$__/  | $$_____/| $$      
       /$$$$$$$/|  $$$$$$$| $$  | $$  |  $$$$/| $$  | $$|  $$$$$$$ /$$$$$$$/| $$ /$$$$$$$$|  $$$$$$$| $$      
      |_______/  \____  $$|__/  |__/   \___/  |__/  |__/ \_______/|_______/ |__/|________/ \_______/|__/      
                 /$$  | $$                                                                                    
                |  $$$$$$/                                                                                    
                 \______/     
                                                                
                                                                                 v4.6 

   
 // A BlogHoskins Monstrosity @ 2019 / 2020
// https://bloghoskins.blogspot.com/
/*    v5
 *    Added drone based on  Control Oscill Wash using 8 pots to change pitch
 *    and switches 2 and 3 to change oscillator type
 *    added switch 4 to toggle between Helios and Drone mode
 *     
 *    v4.6 
 *    Time to fix distortion - Fixed
 *    changed update audio from 8 -> 9
 *    Change Filter Res and Cut-off from >>2 to mozzieMap -> done
 *    change lfo amount pot - check if all are still in spec with multimeter - done
 *    add resistors? - yep, done & done
 *    reduce resonance total in res pot - done
 *    
 *    v4.5
 *    LFO On/off switch added - using arduino digital pin 3
 *     
 *    v4.4 
 *    Applied advice given from Mozzi Forums - working much better now - thanks Staffan
 *    Still need to apply values to stop distortion + add on/off switch for LFO
 *     
 *    v4.3 LFO implementation
 *    LFO is working(?), but filter is interfering.  Figure it out!
 *    *replaced pin assignments 'const int' with #define -> now reassign values to stop distortion
 *    
 *    
 *    V3.1 - Minor Updates
 *   *IImproved Filter Resonance (?).  Apparantly After setting resonance, you need to call setCuttoffFreq() to hear the change.
 *   Swapped order of cut-off and resonance in code.  Filter Sounds Better now?
 *   *Increased note sustain from 10 seconds to 60 seconds
 *   *OSC OUTPUT made louder on audio update>>9; // changed down from 10 to 9 because was louder
 *   
 *   
 *   V3
 *   In this version we add a low pass filter.  A cut off pot and resonance pot are added.
 *   For this you'll need two B10k pots, and a 220ohm resistor.
 *   A3: for Resonance (center pot).  Other lugs go to ground and +5v
 *   A2: for Cut-off (center pot).   Other lugs go to ground (with 220ohm resistor) and +5v
 *   
 *   
 *   v2
 *   https://bloghoskins.blogspot.com/2020/06/helios-one-arduino-synth-part-2.html
 *   This version adds Attack & Release on the analog inputs. You'll need 2 pots. 
 *   Connect center pot pin to;
 *   A5: for Atk
 *   A4: for Release
 *   connect the other pot pins to ground and 5v. 
 *   To stop mis-triggering on the atk I have x2 1k resistors in parallel (amounting 
 *   to 500 ohms resistance) on the ground input of the atk pot. you could put two 
 *   200(ish)ohm resisters in series instead, or play with the code...  maybe set the
 *   int val of the atkVal to something over 20 instead of 0?
 *   
 *   
 *   v1
 *   http://bloghoskins.blogspot.com/2019/07/helios-one-arduino-synth-part-1.html
 *   This vesrion of code lets you set between SQR and SAW wave with a 
 *   switch (input 2 on arduino)
 *   MIDI is working.
 *   You'll need to install the MIDI & Mozzi arduino libraries to get it to work.
*/


#include <MIDI.h>
#include <MozziGuts.h>
#include <Oscil.h> // oscillator template
#include <mozzi_midi.h>
#include <ADSR.h>
#include <LowPassFilter.h> // You need this for the LPF
#include <AutoMap.h> // to track and reassign the pot values

#include <tables/saw2048_int8.h> // saw table for oscillator  -- Shared by Helios and Drone
#include <tables/square_no_alias_2048_int8.h> // square table for oscillator
#include <tables/sin2048_int8.h>                // for Drone
#include <tables/cos2048_int8.h>                // for Drone
#include <tables/triangle_valve_2_2048_int8.h>  // for Drone

//*****************LFO******************************************************************************************
#include <tables/cos2048_int8.h> // for filter modulation
#include <StateVariable.h>
#include <mozzi_rand.h> // for rand()
#include <AutoMap.h> // To track pots 
//***************END********************************************************************************************

//********ADD LFO FILTER MODULATION OSC*************************************************************************
Oscil<COS2048_NUM_CELLS, CONTROL_RATE> kFilterMod(COS2048_DATA);
StateVariable <NOTCH> svf; // can be LOWPASS, BANDPASS, HIGHPASS or NOTCH
//***************END********************************************************************************************

//// Set up LFO Rate Pot****************************************************************************************
#define LFOratePot A1    // select the input pin for the potentiometer
AutoMap LFOratePotMap(0, 1023, 40, 750);  // LFO Rate mapped 25 to 1300 (up from 5 - 1023)
//***************END********************************************************************************************

//// ****************Set up LFO Res Pot*************************************************************************
#define LFOresPot A0    // select the input pin for the potentiometer
AutoMap LFOresPotMap(0, 1023, 40, 180);  // 0-255 val distorted, 2-212 within range - find better value?
//***************END********************************************************************************************

//Create an instance of a low pass filter
LowPassFilter lpf; 

MIDI_CREATE_DEFAULT_INSTANCE();

#define WAVE_SWITCH 2 // switch for switching waveforms
#define LFO_ON_OFF_SWITCH 3 // switch for LFO ON/OFF
#define HELIOS_DRONE_SWITCH 4 // switch between Helios Synth or Drone mode

// Set up Attack & Decay Envelope
#define atkPot A5    // select the input pin for the potentiometer
//int atkVal = 0;       // variable to store the value coming from the pot
AutoMap atkPotMap(0, 1023, 0, 2000);  // remap the atk pot to 3 seconds
#define dkyPot A4    // select the input pin for the potentiometer
//int dkyVal = 0;       // variable to store the value coming from the pot
AutoMap dkyPotMap(0, 1023, 0, 3000);  // remap the atk pot to 3 seconds

//*******CUT-OFF POT***********
#define cutoffPot A2    // cut-off pot will be on A2
AutoMap cutOffPotMap(0, 1023, 20, 250);  // 0 - 255

//*******RESONANCE POT***********
#define resPot A3    // resonance pot will be on A2
AutoMap resFreqPotMap(0, 1023, 0, 255);  // 0 - 255

// use #define for CONTROL_RATE, not a constant
// #define CONTROL_RATE 128 // powers of 2 please
// Drone would like to use a different control rate.  What to do??????
#define CONTROL_RATE 128
// ???????????

// audio sinewave oscillator for Helios
Oscil <SAW2048_NUM_CELLS, AUDIO_RATE> oscil1; //Saw Wav
Oscil <SQUARE_NO_ALIAS_2048_NUM_CELLS, AUDIO_RATE> oscil2; //Sqr wave

////***************Drone oscillators***************************************************************************
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
//***************END********************************************************************************************

// ******** for Drone *****************************************************************************************
char v1,v2,v3,v4,v5,v6,v7,v8;
int synthMode = 1; //1 = Helios, 0 = Drone
int pot = 0; // to select pots to read in Drone mode
int wav = 0; // to select oscillators in Drone mode

// envelope generator
ADSR <CONTROL_RATE, AUDIO_RATE> envelope;

#define LED 13 // Internal LED lights up if MIDI is being received

void HandleNoteOn(byte channel, byte note, byte velocity) { 
  oscil1.setFreq(mtof(float(note)));
  envelope.noteOn();
  digitalWrite(LED,HIGH);
}

void HandleNoteOff(byte channel, byte note, byte velocity) { 
  envelope.noteOff();
  digitalWrite(LED,LOW);
}

void setup() {
//  Serial.begin(9600); // see the output
  pinMode(LED, OUTPUT);  // built-in arduino led lights up with midi sent data 
  // Connect the HandleNoteOn function to the library, so it is called upon reception of a NoteOn.
  MIDI.setHandleNoteOn(HandleNoteOn);  // Put only the name of the function
  MIDI.setHandleNoteOff(HandleNoteOff);  // Put only the name of the function
  // Initiate MIDI communications, listen to all channels (not needed with Teensy usbMIDI)
  MIDI.begin(MIDI_CHANNEL_OMNI);  
  envelope.setADLevels(255,64); // A bit of attack / decay while testing
  oscil1.setFreq(440); // default frequency

  

//****************Set up LFO**************************************************************************************
  kFilterMod.setFreq(1.3f); // Can be deleted??
//****************End*********************************************************************************************

//****************Set toggle switches***************************************************************************** 
  pinMode(2, INPUT_PULLUP); // Pin two to switch, high switch goes to 5v, low to ground. Selects WAVE in Helios and Drone mode
  pinMode(3, INPUT_PULLUP); // Pin three to switch, high switch goes to 5v, low to ground. Selects LFO in Helios and WAVE in Drone
  pinMode(4, INPUT_PULLUP); // Pin four to switch, high switch goes to 5v, low to ground. Selects either Helios or Drone mode
//****************End*********************************************************************************************

// ****************Set frequencies for Drone************************************************************************

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

  v1=v2=v3=v4=v5=v6=v7=v8=128;  // 
  
//****************End*********************************************************************************************
  startMozzi(CONTROL_RATE); 
//  setupFastAnalogRead(FASTEST_ADC);  
}

// oscillator type 1 for Drone
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
// oscillator type 2 for Drone      
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
// oscillator type 3 for Drone      
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
// oscillator type 4 for Drone      
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

void loop() {
  audioHook(); // required here
} 
 
void updateControl()
{
//
synthMode = digitalRead(4);
//if (sensorVal3 == HIGH) // If switch is set to high
//  {
//  synthMode = 1;
//  }
//  else
//  {
//  synthMode = 0;
//  }

// comment the next bit out after wiring in switch 3 ******************************************************************
//  synthMode = 0;
// ********************************************************************************************************************
  
if (synthMode==1) // If switch is set to high, run this portion of code
  {
  // *****************HELIOS CONTROLS****************************************************************************
  MIDI.read();
  
  // set ADSR times
  int atkVal = mozziAnalogRead(atkPot);    // read the value from the attack pot
  atkVal = atkPotMap(atkVal);
  int dkyVal = mozziAnalogRead(dkyPot);    // read the value from the decay pot
  dkyVal = dkyPotMap(dkyVal);
  envelope.setTimes(atkVal,60000,60000,dkyVal); // 60000 is so the note will sustain 60 seconds unless a noteOff comes
  envelope.update();

  //**************RESONANCE POT****************
  int resVal = mozziAnalogRead(resPot);  // arduino checks pot value
  //  uint8_t res_freq = resVal >> 2; // ***8 bit unsigned to store 0-1023 / 4 
  resVal = resFreqPotMap(resVal);
  lpf.setResonance(resVal);  // change the freq

  //**************CUT-OFF POT****************
  int cutVal = mozziAnalogRead(cutoffPot);  // arduino checks pot value
  //  uint8_t cutoff_freq = cutVal >> 2; // ***8 bit unsigned to store 0-1023 / 4
  cutVal = cutOffPotMap(cutVal);
  lpf.setCutoffFreq(cutVal);  // change the freq
  
  //*****************Set up LFO control pots****************************************************************************
  int LFOrateVal = mozziAnalogRead(LFOratePot);    // Speed of LFO
  LFOrateVal = LFOratePotMap(LFOrateVal);         // map to 25-1300

  int LFOresVal = mozziAnalogRead(LFOresPot);    // read the value from the attack pot
  LFOresVal = LFOresPotMap(LFOresVal);            // map to 10-210

  //*****************************Helios LFO**********************************************************************************
  int sensorVal1 = digitalRead(3); // read the switch position value into a  variable
  if (sensorVal1 == HIGH) // If switch is set to high, run this portion of code
    {
    if (rand(CONTROL_RATE/2) == 0)
        { // about once every half second
        kFilterMod.setFreq(LFOrateVal/64);  // choose a new modulation frequency****Replace setFreq((float)rand(255)/64)****
        }
    int LFOrate_freq = 2200 + kFilterMod.next()*12; // cos oscillator, 2200 + (int8)*12
    svf.setCentreFreq(LFOrate_freq);
    svf.setResonance(LFOresVal); 
    }
  else  // If switch not set to high, run this portion of code instead
    {
    svf.setCentreFreq(0);
    svf.setResonance(200); 
    }
  //**********************************END*******************************************************************************


  int sensorVal2 = digitalRead(2); // read the switch position value into a  variable
  if (sensorVal2 == HIGH) // If switch is set to high, run this portion of code
    {
    oscil1.setTable(SAW2048_DATA);
    }
  else  // If switch not set to high, run this portion of code instead
    {
    oscil1.setTable(SQUARE_NO_ALIAS_2048_DATA);
    }
  //**********************************END HELIOS CONTROLS***************************************************************
  }
else
  {
  //**************** START OF THE DRONE CONTROLS *******************
   // read only two of the pots per update to reduce the clicking
  // read the oscillator switch only every 5th cycle

  pot++; // select the next pot number which runs from 1 to 5 
  
  switch (pot) { // decide which pots to read
    case 1:
    aOsc1.setFreq((mozziAnalogRead(A0))*4);
    aOsc2.setFreq((mozziAnalogRead(A1))*4);
    break;
    case 2:
    aOsc3.setFreq((mozziAnalogRead(A2))*4);
    aOsc4.setFreq((mozziAnalogRead(A3))*4);
    break;
    case 3:
    aOsc5.setFreq((mozziAnalogRead(A4))*4);
    aOsc6.setFreq((mozziAnalogRead(A5))*4);
    break;
    case 4:
    aOsc7.setFreq((mozziAnalogRead(A6))*4);
    aOsc8.setFreq((mozziAnalogRead(A7))*4);
    break;
    case 5:
    // every fifth cycle also check the oscillator switches
    wav = digitalRead(2) + (digitalRead(3) * 2);

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
}


int updateAudio(){

// Choose Drone or Helios mode
if (synthMode==0)
  {
   //Drone
  long asigDRN = (long)
    aOsc1.next()*v1 +
    aOsc2.next()*v2 +
    aOsc3.next()*v3 +
    aOsc4.next()*v4 +
    aOsc5.next()*v5 +
    aOsc6.next()*v6 +
    aOsc7.next()*v7 +
    aOsc8.next()*v8;
  asigDRN >>= 9;
  return (int) asigDRN;
  }
  else
  {
   // Helios
    int asigHLS = (envelope.next() * oscil1.next()) >> 10; // multiplying by 0-255 and then dividing by 256
    int asigSVF = svf.next(asigHLS); // SVF
    int asigLPF = lpf.next(asigSVF); // LPF 
    return (asigLPF); 
  }
}
