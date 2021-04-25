#include <Adafruit_SoftServo.h>

#define SERVOPIN 0
#define LEDPIN 1
#define POSBEG 1
#define POSEND 179
#define TIMEOUT0 1
#define TIMEOUT1 300
#define TIMEOUT2 10000
#define TIMEOUT3 60000
#define MINUTES 30
#define NO 1000

Adafruit_SoftServo myServo;

void setup() {
  OCR0A = 0xAF;
  TIMSK |= _BV(OCIE0A);

  myServo.attach(SERVOPIN);
  myServo.write(POSBEG);
  
  pinMode(LEDPIN, OUTPUT);
  digitalWrite(LEDPIN, HIGH);
  delay(TIMEOUT2);
}

void loop() {
  for(int i = 0; i < NO; i++) {
    digitalWrite(LEDPIN, LOW);
    for(int k = POSBEG; k <= POSEND; k++) {
      myServo.write(k);
      delay(TIMEOUT0); 
    }
    delay(TIMEOUT1); 
    digitalWrite(LEDPIN, HIGH);
    for(int k = POSEND; k >= POSBEG; k--) {
      myServo.write(k);
      delay(TIMEOUT0); 
    }
    delay(TIMEOUT1);
  }
  digitalWrite(LEDPIN, LOW);
  for(int k = 0; k < MINUTES; k++) {
    delay(TIMEOUT3);
  }
}

volatile uint8_t counter = 0;
SIGNAL(TIMER0_COMPA_vect) {
  counter += 2;
  if (counter >= 20) {
    counter = 0;
    myServo.refresh();
  }
}
