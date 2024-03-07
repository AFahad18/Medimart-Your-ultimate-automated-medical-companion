#include <Servo.h>
int myInt, chooice;
Servo mServo, mServo1;
void setup() {
  Serial.begin(9600);
  mServo.attach(9);
  mServo1.attach(8);
}
void loop() {
  mServo.write(30);
  mServo1.write(30);
  chooiceMedicine();
}

void chooiceMedicine() {
  Serial.println("Which medicine you want to buy: ");
  Serial.println("\t1.Napa");
  Serial.println("\t2.Monas 10");
  while (Serial.available() == 0) {  // wait until there is data available on the serial port
    delay(100);                      // delay for 100 milliseconds
  }



  // if (Serial.available() > 0) {
  chooice = Serial.parseInt();
  Serial.read();
  Serial.println("How much medicine you want to buy: ");
  Serial.read();
  while (Serial.available() == 0) {  // wait until there is data available on the serial port
    delay(100);                      // delay for 100 milliseconds
  }
  myInt = Serial.parseInt();
  Serial.read();  // Read and discard the newline character
  if (chooice == 1) {
    pushNapaMedicine(myInt);
  }
  if (chooice == 2) {
    pushMonasMedicine(myInt);
  }
  // }
}



void pushNapaMedicine(int n) {
  for (int i = 0; i < n; i++) {
    mServo.write(30);
    delay(1000);
    for (int j = 30; j <= 130; j++) {
      mServo.write(j);
      delay(1);
    }    
    // mServo.write(120);
    // delay(2000);
    mServo.write(30);
    delay(2000);    
  }
}


void pushMonasMedicine(int n) {
  for (int i = 0; i < n; i++) {
        mServo1.write(30);
    delay(1000);
    for (int j = 30; j <= 120; j++) {
      mServo1.write(j);
      delay(10);
    }

    // mServo1.write(120);
    // delay(5000);
    mServo1.write(30);
    delay(1000);
  }
}
