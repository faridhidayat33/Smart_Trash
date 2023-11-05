#include <Servo.h>

Servo myservo;  // create servo object to control a servo

void setup() {
  myservo.attach(D8);  // (pin, min, max)
}

void loop() {
  myservo.write(90);  // tell servo to go to a particular angle
  delay(1000);

  int logam = check_logam();
  Serial.println(logam);

  Serial.print("running");
  
  // myservo.write(0);              
  // delay(500); 
  
  // myservo.write(180);              
  // delay(500);
  
  // myservo.write(180);              
  // delay(1500);                     
}

int check_logam() {
  int prox_logam = digitalRead(D13); //pembacaan data dari sensor proximity
  Serial.println("check logam");
  return prox_logam;
}