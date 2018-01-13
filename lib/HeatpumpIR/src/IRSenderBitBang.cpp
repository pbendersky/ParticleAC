#include <Arduino.h>
#include <IRSender.h>

// Send IR using the 'bit banging' on ESP8266 etc.


IRSenderBitBang::IRSenderBitBang(uint8_t pin) : IRSender(pin)
{
  // pinMode(_pin, OUTPUT);
  
  // Enables IR output.  The khz value controls the modulation frequency in kilohertz.
  // MAX frequency is 166khz.
  pinMode(pin, OUTPUT);
  digitalWrite(pin, LOW);

  
}


void IRSenderBitBang::setFrequency(int frequency)
{
  // Enables IR output.  The khz value controls the modulation frequency in kilohertz.
  // _halfPeriodicTime = 500/frequency; // T = 1/f but we need T/2 in microsecond and f is in kHz
  // (void)frequency;


  // This is the time to wait with the IR LED on and off to make the frequency, in microseconds.
  // The - 3.0 at the end is because digitalWrite() takes about 3 microseconds. Info from:
  // https://github.com/eflynch/sparkcoreiremitter/blob/master/ir_emitter/ir_emitter.ino
  burstWait = round(1.0 / frequency * 1000.0 / 2.0 - 3.0);
  // This is the total time of a period, in microseconds.
  burstLength = round(1.0 / frequency * 1000.0);
}


// Send an IR 'mark' symbol, i.e. transmitter ON
void IRSenderBitBang::mark(int time)
{
  // long beginning = micros();
  //
  // while((int)(micros() - beginning) < markLength){
  //   digitalWrite(_pin, HIGH);
  //   delayMicroseconds(_halfPeriodicTime);
  //   digitalWrite(_pin, LOW);
  //   delayMicroseconds(_halfPeriodicTime); //38 kHz -> T = 26.31 microsec (periodic time), half of it is 13
  // }

  // Sends an IR mark (frequency burst output) for the specified number of microseconds.
  noInterrupts();
  
  while (time > 0) {
    digitalWrite(_pin, HIGH); // this takes about 3 microseconds to happen
    delayMicroseconds(burstWait);
    digitalWrite(_pin, LOW); // this also takes about 3 microseconds
    delayMicroseconds(burstWait);
 
    time -= burstLength;
  }
  
  interrupts();
}


// Send an IR 'space' symbol, i.e. transmitter OFF
void IRSenderBitBang::space(int time)
{
  // digitalWrite(_pin, LOW);
  //
  // if (spaceLength < 16383) {
  //   delayMicroseconds(spaceLength);
  // } else {
  //   delay(spaceLength/1000);
  // }
  
  
  // Sends an IR space (no output) for the specified number of microseconds.
  digitalWrite(_pin, LOW); // Takes about 3 microsecondes
  if (time > 3) {
    delayMicroseconds(time - 3);
  }
}