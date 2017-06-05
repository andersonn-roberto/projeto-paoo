#include <LiquidCrystal.h>
#include "pitches.h"

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

/*  PulseSensor™ Starter Project   http://www.pulsesensor.com

  This an Arduino project. It's Best Way to Get Started with your PulseSensor™ & Arduino.
  -------------------------------------------------------------
  1) This shows a live human Heartbeat Pulse.
  2) Live visualization in Arduino's Cool "Serial Plotter".
  3) Blink an LED on each Heartbeat.
  4) This is the direct Pulse Sensor's Signal.
  5) A great first-step in troubleshooting your circuit and connections.
  6) "Human-readable" code that is newbie friendly."
*/

//  Variables
int PulseSensorPurplePin = 0;        // Pulse Sensor PURPLE WIRE connected to ANALOG PIN 0
int LED13 = 13;   //  The on-board Arduion LED
int btnLigaDesliga = 9;
int buzzer = 8;
int ledVermelho = 6;
int ledVerde = 7;
int efetuarLeitura = 0;

int Signal;                // holds the incoming raw data. Signal value can range from 0-1024
int Threshold = 550;            // Determine which Signal to "count as a beat", and which to ingore.

// The SetUp Function:
void setup() {
  lcd.begin(16, 2);
  pinMode(LED13, OUTPUT);        // pin that will blink to your heartbeat!
  pinMode(buzzer, OUTPUT);
  pinMode(btnLigaDesliga, INPUT_PULLUP);
  pinMode(ledVermelho, OUTPUT);
  pinMode(ledVerde, OUTPUT);
  Serial.begin(9600);         // Set's up Serial Communication at certain speed.
  digitalWrite(ledVermelho, LOW);
  digitalWrite(ledVerde, LOW);
}

// The Main Loop Function
void loop() {

  // Check if the btnLigaDesliga was pressed
  if (digitalRead(btnLigaDesliga) == HIGH) {
    
    if (efetuarLeitura == 0) {      
      
      efetuarLeitura = 1;
      Serial.println("Pressionou: Ligar " + (String)efetuarLeitura);
      digitalWrite(ledVerde, HIGH);
      delay(500);
      
    } else {      
      
      efetuarLeitura = 0;      
      digitalWrite(ledVerde, LOW);
      delay(500);
      
    }
    
  }
  
  if (efetuarLeitura == 1) {
     
    Signal = analogRead(PulseSensorPurplePin);  // Read the PulseSensor's value.
    // Assign this value to the "Signal" variable.

    Serial.println(Signal);                    // Send the Signal value to Serial Plotter.

    if (Signal > Threshold) {                        // If the signal is above "550", then "turn-on" Arduino's on-Board LED.
      
      digitalWrite(ledVermelho, HIGH);
      lcd.clear();
      lcd.setCursor(3, 0);
      lcd.print((String)Signal + " S");
      
    } else {
      
      digitalWrite(ledVermelho, LOW);               //  Else, the sigal must be below "550", so "turn-off" this LED.
      
    }

    tone(buzzer, 262, 100);
    
  } else {
    
    noTone(buzzer);
    
  }
  
  delay(20);
  
}
