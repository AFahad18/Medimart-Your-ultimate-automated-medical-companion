#include <Stepper.h>
#define STEPS 2048
Stepper stepper (STEPS,8,10,9,11);//in1,in3,in2,in4
void setup() {
  // put your setup code here, to run once:
  stepper.setSpeed(6);   //1 rpm speed 15 er beshi deoa jay na
}

void loop() {
  // put your main code here, to run repeatedly:
  stepper.step(2048);
  delay(1000);
  stepper.step(-2048);
  delay(1000);
  stepper.setSpeed(12);
  stepper.step(4096);
  delay(1000);
  stepper.step(-4096);
  delay(1000);
  
  
}
