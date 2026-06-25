volatile int seconds = 0;
volatile bool ledOn = false;

const int inputPin = 2;
const int ledPin = 8;

void setup() {
  pinMode(inputPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);

  // Timer1 setup
  cli(); // disable interrupts

  TCCR1A = 0;
  TCCR1B = 0;

  TCNT1 = 0;

  // Compare match value for 1 second
  OCR1A = 15624;  

  TCCR1B |= (1 << WGM12);  // CTC mode
  TCCR1B |= (1 << CS12) | (1 << CS10); // prescaler 1024

  TIMSK1 |= (1 << OCIE1A); // enable timer compare interrupt

  sei(); // enable interrupts
}

void loop() {
  if (digitalRead(inputPin) == LOW && !ledOn) {
    ledOn = true;
    seconds = 0;
    digitalWrite(ledPin, HIGH);
  }
}

// Timer1 interrupt
ISR(TIMER1_COMPA_vect) {
  if (ledOn) {
    seconds++;

    if (seconds >= 6) {
      digitalWrite(ledPin, LOW);
      ledOn = false;
    }
  }
}