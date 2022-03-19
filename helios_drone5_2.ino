/*
       /$$   /$$ /$$$$$$$$ /$$       /$$$$$$  /$$$$$$   /$$$$$$       /$$$$$$$  /$$$$$$$   /$$$$$$  /$$   /$$ /$$$$$$$$          
      | $$  | $$| $$_____/| $$      |_  $$_/ /$$__  $$ /$$__  $$     | $$  | $$| $$__  $$ /$$__  $$| $$$ | $$| $$_____/          
      | $$  | $$| $$      | $$        | $$  | $$  \ $$| $$  \__/     | $$  | $$| $$  | $$| $$  \ $$| $$$$| $$| $$                
      | $$$$$$$$| $$$$$   | $$        | $$  | $$  | $$|  $$$$$$      | $$  | $$| $$$$$$  | $$  | $$| $$ $$ $$| $$$$$             
      | $$__  $$| $$__/   | $$        | $$  | $$  | $$ \____  $$     | $$  | $$| $$__  $$| $$  | $$| $$  $$$$| $$__/             
      | $$  | $$| $$      | $$        | $$  | $$  | $$ /$$  \ $$     | $$  | $$| $$  | $$| $$  | $$| $$\  $$$| $$                
      | $$  | $$| $$$$$$$$| $$$$$$$$ /$$$$$$|  $$$$$$/|  $$$$$$/     | $$$$$$$ | $$  | $$|  $$$$$$/| $$ \  $$| $$$$$$$$          
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
                                                                
                                                                                 v5.0

   
// Based on BlogHoskin's Helios Synth sketch @ 2019 / 2020
// https://bloghoskins.blogspot.com/



/*    v5.1
 *    Add code for sustain and release time for Helios using pots on A6 and A7.
 *     
 *     
 *     v5.0
 *    IMPORTANT NOTE: to use this you need to add two extra control pots and one switch to the standard Helios unit 
 *    If you don't want to do that, try the 6 oscillator version v5.0a
 *    This sketch adds an 8-voice Drone based on the Control_Oscill_Wash sketch using 8 pots to change pitch
 *    and switches 2 and 3 to change oscillator type. 
 *    To use it, you need two more 10K pots on A6 and A7, and a switch on D4 of the original Helios build
 *    Switch 4 to toggles between Helios and Drone mode
 *    Fixed clicking by splitting calculation of updateAudio into int-sized pieces
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
#include <tables/square_no_alias_2048_int8.h> // square table for oscillator   -- Shared by Helios and Drone
#include <tables/sin2048_int8.h>                // for Drone alone
#include <tables/triangle_valve_2_2048_int8.h>  // for Drone alone

//*****************LFO******************************************************************************************
#include <tables/cos2048_int8.h> // for filter modulation
#include <StateVariable.h>
#include <mozzi_rand.h> // for rand()
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
AutoMap LFOresPotMap(0, 1023, 2, 212);  // 0-255 val distorted, 2-212 within range - find better value? Was 40-180
//***************END********************************************************************************************

//Create an instance of a low pass filter
LowPassFilter lpf; 

MIDI_CREATE_DEFAULT_INSTANCE();

#define WAVE_SWITCH 2 // switch for switching waveforms
#define LFO_ON_OFF_SWITCH 3 // switch for LFO ON/OFF
#define MODE_SWITCH 4 // switch between Helios Synth or Drone mode

// Set up Attack & Decay Envelope
#define atkPot A5    // select the input pin for the potentiometer
//int atkVal = 0;       // variable to store the value coming from the pot
AutoMap atkPotMap(0, 1023, 0, 3000);  // remap the atk pot to 3 seconds
#define dkyPot A4    // select the input pin for the potentiometer
//int dkyVal = 0;       // variable to store the value coming from the pot
AutoMap dkyPotMap(0, 1023, 30, 3000);  // remap the decay pot to 3 seconds

// Set up Sustain & Release Envelope (note: sustain is a level, release is a time)
#define susPot A6    // select the input pin for the potentiometer
//int susVal = 0;       // variable to store the value coming from the pot
AutoMap susPotMap(0, 1023, 64, 255);  // remap the sustain pot from 64 to max sustain level
#define relPot A7    // select the input pin for the potentiometer
//int relVal = 0;       // variable to store the value coming from the pot
AutoMap relPotMap(0, 1023, 30, 6000);  // remap the release pot to 6 seconds


//*******CUT-OFF POT***********
#define cutoffPot A2    // cut-off pot will be on A2
AutoMap cutOffPotMap(0, 1023, 20, 250);  // 0 - 255

//*******RESONANCE POT***********
#define resPot A3    // resonance pot will be on A2
AutoMap resFreqPotMap(0, 1023, 20, 250);  // 0 - 255

// use #define for CONTROL_RATE, not a constant
#define CONTROL_RATE 128 // powers of 2 please

// audio sinewave oscillator for Helios
Oscil <SAW2048_NUM_CELLS, AUDIO_RATE> oscil1; //Saw Wav
Oscil <SQUARE_NO_ALIAS_2048_NUM_CELLS, AUDIO_RATE> oscil2; //Sqr wave

////*********************** Defaults for Drone oscillators ***************************************************
// harmonics
Oscil<SIN2048_NUM_CELLS, AUDIO_RATE> aOsc1;
Oscil<SIN2048_NUM_CELLS, AUDIO_RATE> aOsc2;
Oscil<SIN2048_NUM_CELLS, AUDIO_RATE> aOsc3;
Oscil<SIN2048_NUM_CELLS, AUDIO_RATE> aOsc4;
Oscil<SIN2048_NUM_CELLS, AUDIO_RATE> aOsc5;
Oscil<SIN2048_NUM_CELLS, AUDIO_RATE> aOsc6;
Oscil<SIN2048_NUM_CELLS, AUDIO_RATE> aOsc7;
Oscil<SIN2048_NUM_CELLS, AUDIO_RATE> aOsc8;

// volume controls, use sin regardless of the harmonic oscillator
Oscil<SIN2048_NUM_CELLS, CONTROL_RATE> kVol1(SIN2048_DATA);
Oscil<SIN2048_NUM_CELLS, CONTROL_RATE> kVol2(SIN2048_DATA);
Oscil<SIN2048_NUM_CELLS, CONTROL_RATE> kVol3(SIN2048_DATA);
Oscil<SIN2048_NUM_CELLS, CONTROL_RATE> kVol4(SIN2048_DATA);
Oscil<SIN2048_NUM_CELLS, CONTROL_RATE> kVol5(SIN2048_DATA);
Oscil<SIN2048_NUM_CELLS, CONTROL_RATE> kVol6(SIN2048_DATA);
Oscil<SIN2048_NUM_CELLS, CONTROL_RATE> kVol7(SIN2048_DATA);
Oscil<SIN2048_NUM_CELLS, CONTROL_RATE> kVol8(SIN2048_DATA);
//***************END********************************************************************************************

// ******** variables for Drone *******************************************************************************
bool synthMode = 1;             //1 = Helios, 0 = Drone
char v1,v2,v3,v4,v5,v6,v7,v8;   //char is more efficient than int, for some reason
int f1,f2,f3,f4,f5,f6,f7,f8;    // store the values from the analog pins to set frequency
int wav = 0;      // store the value of the two wave switches
int oldWav = 99;  // remember the previous value of the wave switches, so we know if it's changed 
int upCycle = 1;  // count the update cycle.  We only read a few of the inputs on each cycle, to reduce clicking souds
int iDebug = 0;   // multipurpose int for debugging, use it where you need it

// ******** variables for Helios *******************************************************************************
int oldOsc = 99;  // remember the previous value of the wave switches, so we know if it's changed 
int oldAtk = 0;  // remember attack value so envelope is only updated on change
int oldDky = 0;  // remember decay value so envelope is only updated on change
int oldSus = 0;  // remember sustain value so envelope is only updated on change
int oldRel = 0;  // remember release value so envelope is only updated on change
byte lastnote;
//***************END********************************************************************************************

// envelope generator
ADSR <CONTROL_RATE, AUDIO_RATE> envelope;

#define LED 13 // Internal LED lights up if MIDI is being received

void HandleNoteOn(byte channel, byte note, byte velocity) { 
  oscil1.setFreq(mtof(float(note)));
  envelope.noteOn();
  digitalWrite(LED,HIGH);
  lastnote = note;
}

void HandleNoteOff(byte channel, byte note, byte velocity) { 
  if (lastnote==note) {
    envelope.noteOff();
    digitalWrite(LED,LOW); 
  }
}

void setup() {
//  Serial.begin(9600); 
  pinMode(LED, OUTPUT);  // built-in arduino led lights up with midi sent data 
  // Connect the HandleNoteOn function to the library, so it is called upon reception of a NoteOn.
  MIDI.setHandleNoteOn(HandleNoteOn);  // Put only the name of the function
  MIDI.setHandleNoteOff(HandleNoteOff);  // Put only the name of the function
  // Initiate MIDI communications, listen to all channels (not needed with Teensy usbMIDI)
  MIDI.begin(MIDI_CHANNEL_OMNI);  
  
  envelope.setADLevels(255,64); // A bit of attack / decay while testing
  envelope.setTimes(30, 1000, 60000, 1000); // set some default times
  oscil1.setFreq(440); // default frequency

//****************Set up LFO**************************************************************************************
  kFilterMod.setFreq(1.3f); // Can be deleted??
//****************End*********************************************************************************************

//****************Set toggle switches***************************************************************************** 
  pinMode(2, INPUT_PULLUP); // Pin two to switch, high switch goes to 5v, low to ground. Selects WAVE in Helios and Drone mode
  pinMode(3, INPUT_PULLUP); // Pin three to switch, high switch goes to 5v, low to ground. Selects LFO in Helios and WAVE in Drone
  pinMode(4, INPUT_PULLUP); // Pin four to switch, high switch goes to 5v, low to ground. Selects either Helios or Drone mode
//****************End*********************************************************************************************

// ****************Set default frequencies for Drone**************************************************************

// set harmonic frequencies
  aOsc1.setFreq(100);
  aOsc2.setFreq(100);
  aOsc3.setFreq(100);
  aOsc4.setFreq(100);
  aOsc5.setFreq(100);
  aOsc6.setFreq(100);
  aOsc7.setFreq(100);
  aOsc8.setFreq(100);

//// set volume change freq
  kVol1.setFreq(0.84f); 
  kVol2.setFreq(0.098f);
  kVol3.setFreq(0.076f);
  kVol4.setFreq(0.28f);
  kVol5.setFreq(0.188f);
  kVol6.setFreq(0.124f);
  kVol7.setFreq(0.42f);
  kVol8.setFreq(0.164f);
  kVol8.setFreq(0.041f);

  v1=v2=v3=v4=v5=v6=v7=v8=127;  
  
//****************End*********************************************************************************************

  startMozzi(CONTROL_RATE); 
  
}

// the following four voids switch the harmonic oscillator waveforms for the drone
// you can try other waveform types, but keep them all to the same # of samples, eg 2048

// ******************************** oscillator type 1 for Drone ************************************************
void setTable1() { 
      aOsc1.setTable(SIN2048_DATA);
      aOsc2.setTable(SIN2048_DATA);
      aOsc3.setTable(SIN2048_DATA);
      aOsc4.setTable(SIN2048_DATA);
      aOsc5.setTable(SIN2048_DATA);
      aOsc6.setTable(SIN2048_DATA);
      aOsc7.setTable(SIN2048_DATA);
      aOsc8.setTable(SIN2048_DATA);  
      }
// ******************************** oscillator type 2 for Drone ************************************************      
void setTable2() {
      aOsc1.setTable(SQUARE_NO_ALIAS_2048_DATA);
      aOsc2.setTable(SQUARE_NO_ALIAS_2048_DATA);
      aOsc3.setTable(SQUARE_NO_ALIAS_2048_DATA);
      aOsc4.setTable(SQUARE_NO_ALIAS_2048_DATA);
      aOsc5.setTable(SQUARE_NO_ALIAS_2048_DATA);
      aOsc6.setTable(SQUARE_NO_ALIAS_2048_DATA);
      aOsc7.setTable(SQUARE_NO_ALIAS_2048_DATA);
      aOsc8.setTable(SQUARE_NO_ALIAS_2048_DATA);       
      }
// ******************************** oscillator type 3 for Drone ************************************************    
void setTable3() {
      aOsc1.setTable(TRIANGLE_VALVE_2_2048_DATA);
      aOsc2.setTable(TRIANGLE_VALVE_2_2048_DATA);
      aOsc3.setTable(TRIANGLE_VALVE_2_2048_DATA);
      aOsc4.setTable(TRIANGLE_VALVE_2_2048_DATA);
      aOsc5.setTable(TRIANGLE_VALVE_2_2048_DATA);
      aOsc6.setTable(TRIANGLE_VALVE_2_2048_DATA);
      aOsc7.setTable(TRIANGLE_VALVE_2_2048_DATA);
      aOsc8.setTable(TRIANGLE_VALVE_2_2048_DATA);  
      }
// ******************************** oscillator type 4 for Drone ************************************************
void setTable4() {
      aOsc1.setTable(SAW2048_DATA);
      aOsc2.setTable(SAW2048_DATA);
      aOsc3.setTable(SAW2048_DATA);
      aOsc4.setTable(SAW2048_DATA);
      aOsc5.setTable(SAW2048_DATA);
      aOsc6.setTable(SAW2048_DATA);
      aOsc7.setTable(SAW2048_DATA);
      aOsc8.setTable(SAW2048_DATA);  
    } 
// ******************************** end of oscillator setTable voids ********************************************

void loop() {
  audioHook(); // required here
} 
 
void updateControl()
{
//
synthMode = digitalRead (MODE_SWITCH);

if (synthMode) // If switch is set to high, run this portion of code
  {
  // *****************HELIOS CONTROLS****************************************************************************
  MIDI.read();
  
  // set ADSR times
  int atkVal = mozziAnalogRead(atkPot);    // read the value from the attack pot
  atkVal = atkPotMap(atkVal);
  int dkyVal = mozziAnalogRead(dkyPot);    // read the value from the decay pot
  dkyVal = dkyPotMap(dkyVal);
  int susVal = mozziAnalogRead(susPot);    // read the value from the sustain pot
  susVal = susPotMap(susVal);
  int relVal = mozziAnalogRead(relPot);    // read the value from the release pot
  relVal = relPotMap(relVal);

 if ((abs(oldAtk-atkVal)>6) || (abs(oldDky-dkyVal)>6) || (abs(oldSus-susVal)>6) || (abs(oldRel-relVal)>6))  //see if pots have been moved, but ignore noise
  { 
  envelope.setADLevels(255,susVal);
  envelope.setTimes(atkVal,dkyVal,60000,relVal); // added sustain and release, previously fixed to 60000 (sixty sec) 
  envelope.update();  
 
  // remember the ADSR values so we only need to update the envelpe when they've changed
  oldAtk==atkVal;
  oldDky==dkyVal;
  oldSus==susVal;
  oldRel==relVal;  
  }

  //**************RESONANCE POT****************
  int resVal = mozziAnalogRead(resPot);  // arduino checks pot value
  //  uint8_t res_freq = resVal >> 2; // ***8 bit unsigned to store 0-1023 / 4 
  resVal = resFreqPotMap(resVal);
  // lpf.setResonance(resVal);  // deprecated, so removed
 
  //**************CUT-OFF POT****************
  int cutVal = mozziAnalogRead(cutoffPot);  // arduino checks pot value
  //  uint8_t cutoff_freq = cutVal >> 2; // ***8 bit unsigned to store 0-1023 / 4
  cutVal = cutOffPotMap(cutVal);
  // lpf.setCutoffFreq(cutVal);  // deprecated, so removed
  
  lpf.setCutoffFreqAndResonance(cutVal,resVal);   // change the cutoff and resonnance
  
  //*****************Set up LFO control pots****************************************************************************
  int LFOrateVal = mozziAnalogRead(LFOratePot);    // Speed of LFO
  LFOrateVal = LFOratePotMap(LFOrateVal);         // map to 25-1300

  int LFOresVal = mozziAnalogRead(LFOresPot);    // read the value from the attack pot
  LFOresVal = LFOresPotMap(LFOresVal);            // map to 10-210

  //*****************************Helios LFO**********************************************************************************
  int sensorVal1 = digitalRead(LFO_ON_OFF_SWITCH); // read the switch position value into a  variable
  if (sensorVal1 == HIGH) // If switch is set to high, run this portion of code
    {
    if (rand(CONTROL_RATE>>1) == 0)
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


  int sensorVal2 = digitalRead(WAVE_SWITCH); // read the switch position value into a  variable
  if (sensorVal2 != oldOsc) { // only set the oscillator if the wave switch has changed value
    if (sensorVal2 == HIGH)   // If switch is set to high, run this portion of code
      {
      oscil1.setTable(SAW2048_DATA);
      }
    else  // If switch not set to high, run this portion of code instead
      {
      oscil1.setTable(SQUARE_NO_ALIAS_2048_DATA);
      }
     oldOsc = sensorVal2; // remember this value so we can check if it changes
  }
  //**********************************END HELIOS CONTROLS***************************************************************

  }
else
  {

  //********************************* START OF THE DRONE CONTROLS ********************************************************
// To reduce regular clicking sounds caused by performance problems, 
// the control updates are split into 5 cycles, as follows:
// In cycles 1 and 3, four of the eight pots are read
// In cycles 2 and 4, the values read from the pots are set to the oscillators
// Also, two oscillator volume changes are progressed in each cycle
// In cycle 5, the digital inputs are read, and if changed, the oscillator types are switched

    switch (upCycle) {
    case 1:  
      // read four analog pins 
      f1=(mozziAnalogRead(A0));
      f2=(mozziAnalogRead(A1));
      f3=(mozziAnalogRead(A2));
      f4=(mozziAnalogRead(A3)); 
       // update two oscillator volumes
      v1 = kVol1.next();  
      v2 = kVol2.next();
    break;
    case 2:  
      // set four oscillator frequencies
      aOsc1.setFreq(f1<<2);
      aOsc2.setFreq(f2<<2);
      aOsc3.setFreq(f3<<2);
      aOsc4.setFreq(f4<<2); 
      // update two oscillator volumes
      v3 = kVol3.next();
      v4 = kVol4.next();       
    break;
    case 3:    
      // read four analog pins 
      f5=(mozziAnalogRead(A4));
      f6=(mozziAnalogRead(A5));
      f7=(mozziAnalogRead(A6));
      f8=(mozziAnalogRead(A7)); 
      // update two oscillator volumes
      v5 = kVol5.next();  
      v6 = kVol6.next();
    break;
    case 4:
      // set four oscillator frequencies
      aOsc5.setFreq(f5<<2);
      aOsc6.setFreq(f6<<2);    
      aOsc7.setFreq(f7<<2);
      aOsc8.setFreq(f8<<2);    
      // update two oscillator volumes
      v7 = kVol7.next(); 
      v8 = kVol8.next();                
    break;
    case 5:   // read two digital pins
      wav = digitalRead(2) + (digitalRead(3)<<1); 
      if (wav!=oldWav) // swap the oscillator tables, but only if the switch position has changed
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
       
        oldWav = wav;   //remember the old switch positions
        }  
    } // end up update cycle switch
    
    upCycle++;  // move on to the next update cycle
    if (upCycle > 5)  // if we've done all the cycles, return to the first
      {
        upCycle = 1;
      }
}
}

int updateAudio(){

// Choose Drone or Helios mode
if (synthMode)
  {
   // Helios
    int asigHLS = (envelope.next() * oscil1.next()) >> 10; // multiplying by 0-255 and then dividing by 256
    int asigSVF = svf.next(asigHLS); // SVF
    int asigLPF = lpf.next(asigSVF); // LPF 
    return (asigLPF); 
  }  
  else
  {
   //Drone (I split the original Control_Oscil_Wash calculation up into int-sized chunks for faster processing)
    int asig1 = (aOsc1.next()*v1 + aOsc2.next()*v2)>>1; // sum two and divide by 2
    int asig2 = (aOsc3.next()*v3 + aOsc4.next()*v4)>>1;
    int asig3 = (aOsc5.next()*v5 + aOsc6.next()*v6)>>1;
    int asig4 = (aOsc7.next()*v7 + aOsc8.next()*v8)>>1;
    int asig5 = (asig1 + asig2)>>1; // sum two and divide by 2
    int asig6 = (asig3 + asig4)>>1;
    int asigDRN = (asig5 + asig6)>>7; // divide by 128
    return(asigDRN); 
  }

 
}
