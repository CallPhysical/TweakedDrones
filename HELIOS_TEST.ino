
/*
Test program for checking Pots, switches and Audio circuit

The program is designed to read the 6 volume controls and the 2 switches(LFO/WAV).

Yes I could have down this program cleaner with FOR loops, arrays etc - but it is only test program and took 20 minutes to knock up

Please feel to modify and improve on it.

Key elements the tester output will show on the monitor display

Note make sure switch is set to LOAD.

Switches
Wave Switch select0 Sq or Saw
LFO Switch select0 ON or OFF

Pots - set all Pots fully counter clockwise looking straight on to front panel

LFO RATE - Rate- clockwise increase volatage
LFO Rate - Amount - clockwies Voltage decreases

Filter-- Cutoff - clockwies Voltage decreases
Filter-- Res - clockwies Voltage increases

Envekope - Attack - clockwies Voltage decreases
Envelope - Release - Filter- clockwies Voltage increases


Audio output generates a Signal every

*/

float Volt0; // LFO Amount
float Volt1; // LFO Rate
float Volt2; // Filter cutoff
float Volt3; // Filter Res
float Volt4; // Envelope Release
float Volt5; // Envelope Attack
float Volt6; // Envelope Release
float Volt7; // Envelope Attack

//wiring pins defined for the NANO version

int LFO;
int WAV;
int LFOPin = 3;
int WAVPin = 2;


void setup() {
// initialize serial communication at 9600 bits per second:
Serial.begin(9600);
pinMode(A0, INPUT);
pinMode(A1, INPUT);
pinMode(A2, INPUT);
pinMode(A3, INPUT);
pinMode(A4, INPUT);
pinMode(A5, INPUT);
pinMode(A6, INPUT);
pinMode(A7, INPUT);

pinMode(LFOPin, INPUT);
pinMode(WAVPin, INPUT);


pinMode(9,OUTPUT);

}

// the loop routine runs over and over again forever:

void loop()
{
// read the input on analog pin 0-5:

Volt0 = analogRead(A0);
Volt1 = analogRead(A1);
Volt2 = analogRead(A2);
Volt3 = analogRead(A3);
Volt4 = analogRead(A4);
Volt5 = analogRead(A5);
Volt6 = analogRead(A6);
Volt7 = analogRead(A7);

// Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):

//Volt0 = Volt0 * (5.0 / 1023.0); //LFO amount
//Volt1 = Volt1 * (5.0 / 1023.0); // LFO Rate
//Volt2 = Volt2 * (5.0 / 1023.0); //Filter Cutoff
//Volt3 = Volt3 * (5.0 / 1023.0); //Filter Res
//Volt4 = Volt4 * (5.0 / 1023.0); // Envelope Release
//Volt5 = Volt5 * (5.0 / 1023.0); // Envelope Attack
//Volt6 = Volt6 * (5.0 / 1023.0); // A6
//Volt7 = Volt7 * (5.0 / 1023.0); // A7

LFO = digitalRead(LFOPin); // on/oFF
WAV = digitalRead(WAVPin); // Square or Saw wave

// print out the value
// Serial.println(" LFO SW WAV SW LFO Rate LFO Amt Filter Cutoff Filter Res Env Rel Env Attack");
Serial.println(" LFO WAV LRat LAmt FCut FRes ERel EAtt A6 A7");
//Print switches

if ( LFO == 0) {
Serial.print(" OFF ");
}
else
{ Serial.print(" ON ");
}

if ( WAV == 0) {
Serial.print("SQR ");
}
else
{ Serial.print("SAW ");
}

Serial.print(Volt1);
Serial.print(" ");
Serial.print(Volt0);
Serial.print(" ");
Serial.print(Volt2);
Serial.print(" ");
Serial.print(Volt3);
Serial.print(" ");
Serial.print(Volt4);
Serial.print(" ");
Serial.print(Volt5);
Serial.print(" ");
Serial.print(Volt6);
Serial.print(" ");
Serial.print(Volt7);
Serial.println();
Serial.println();

tone(9,50,1000); //sound tone for short burst.-

delay(2000); // 2 seoond update on screen


// No test routing for the MIDI at this time - easy wiring so easy to troubleshoot

}
