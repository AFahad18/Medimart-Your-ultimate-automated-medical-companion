#include <Servo.h>

Servo myservo;  // create servo object to control a servo


// defines pins numbers
const int trigPin = 10;
const int echoPin = 11;

// defines variables
long duration;
int distance;
void setup() {
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  Serial.begin(9600); // Starts the serial communication
  myservo.attach(7);
}
void loop() {
  // myservo.write(0);
  //Clears the trigPin
//  digitalWrite(trigPin, LOW);
//  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2;
  // Prints the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.println(distance);
  if(distance<=4 && distance>0){
    m_servo_open();
  }
  else{
    m_servo_close();
  }
  delay(50);
}


void m_servo_close(){
  myservo.write(0);              // tell servo to go to position in variable 'pos'
}
void m_servo_open(){
  myservo.write(60);              // tell servo to go to position in variable 'pos'
    delay(3000);
}
