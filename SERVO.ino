#include <Adafruit_SoftServo.h>

#define SERVOPIN 0
#define LEDPIN 1
#define POSBEG 10
#define POSEND 170
#define TIMEOUT1 2000
#define TIMEOUT2 60000
#define MINUTES 10
#define NO 100

Adafruit_SoftServo myServo;

void setup() {
  OCR0A = 0xAF;
  TIMSK |= _BV(OCIE0A);

  myServo.attach(SERVOPIN);
  myServo.write(POSBEG);
  
  pinMode(LEDPIN, OUTPUT);
  digitalWrite(LEDPIN, HIGH);
  delay(5*TIMEOUT1);
}

void loop() {
  for(int i = 0; i < NO; i++) {
    digitalWrite(LEDPIN, LOW);
    myServo.write(POSBEG);
    delay(TIMEOUT1); 
    digitalWrite(LEDPIN, HIGH);
    myServo.write(POSEND); 
    delay(TIMEOUT1);
  }
  digitalWrite(LEDPIN, LOW);
  for(int k = 0; k < MINUTES; k++) {
    delay(TIMEOUT2);
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
