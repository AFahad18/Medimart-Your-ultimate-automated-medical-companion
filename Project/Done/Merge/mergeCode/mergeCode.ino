#include <Servo.h>
int myInt, chooice;
Servo mServo, mServo1, myservo, myServo;


// Sanitizer
const int trPin = 6;
const int ecPin = 5;

// Dustbin
const int trigPin = 10;
const int echoPin = 11;

// defines variables
// Sanitozer
long dur;
int dis;

// dustbin
long duration;
int distance;

void setup() {
  Serial.begin(9600);  
  mServo.attach(9);
  mServo1.attach(8);
  // sanitizer
  pinMode(trPin, OUTPUT);  // Sets the trigPin as an Output
  pinMode(ecPin, INPUT);   // Sets the echoPin as an Input
  myServo.attach(12);

  // dustbin
  pinMode(trigPin, OUTPUT);  // Sets the trigPin as an Output
  pinMode(echoPin, INPUT);   // Sets the echoPin as an Input
  myservo.attach(7);
}
void loop() {
  mServo.write(30);
  mServo1.write(30);
  for (int i = 0; i <= 15; i++) {
    // dustbin
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    // Reads the echoPin, returns the sound wave travel time in microseconds
    duration = pulseIn(echoPin, HIGH);
    // Calculating the distance
    distance = duration * 0.034 / 2;
    // Prints the distance on the Serial Monitor
   
    
    Serial.print("D_Distance: ");
    Serial.println(distance);
    // // Sanitizer
    // Serial.print(" S_distance: ");
    // Serial.println(dis);
    // Dustbin
    if (distance <= 4 && distance > 0) {
      m_servo_open();
    } else {
      m_servo_close();
    }
    delay(300);
  }


  for (int i = 0; i <= 15; i++) {

    // sanitizer
    digitalWrite(trPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trPin, LOW);
    // Reads the echoPin, returns the sound wave travel time in microseconds
    dur = pulseIn(ecPin, HIGH);
    // Calculating the distance
    dis = dur * 0.034 / 2;
    // Prints the distance on the Serial Monitor
    if (dis <= 6 && dis > 0) {
      m_servo();
    } else {
      myServo.write(180);
    }
    Serial.print("\tS_distance: ");
    Serial.println(dis);
    delay(300);
  }  
  delay(50);
  chooiceMedicine();
}

void chooiceMedicine() {

  Serial.println("Which medicine you want to buy: ");
  Serial.println("\t1.Napa");
  Serial.println("\t2.Monas 10");
  Serial.read();
  int x = 0;
  while (Serial.available() == 0) {  // wait until there is data available on the serial port
    // delay(100);      // delay for 100 milliseconds
    x++;
    if (x == 4000) {
      return;
    }
    delay(1);  // delay for 100 milliseconds
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
    delay(1500);
  }
}


void pushMonasMedicine(int n) {
  for (int i = 0; i < n; i++) {
    mServo1.write(30);
    delay(1000);
    for (int j = 30; j <= 140; j++) {
      mServo1.write(j);
      delay(10);
    }

    // mServo1.write(120);
    // delay(5000);
    mServo1.write(30);
    delay(1500);
  }
}


void m_servo_close() {
  myservo.write(0);  // tell servo to go to position in variable 'pos'
}
void m_servo_open() {
  myservo.write(60);  // tell servo to go to position in variable 'pos'
  delay(3000);
}

void m_servo() {
  myServo.write(100);
  delay(4000);
}