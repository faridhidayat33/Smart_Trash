#include <Servo.h>

Servo myservo;  // create servo object to control a servo

const int prox_pin = D13; //sensor proximity
const int sensor_jarak_pin = D3; //sensor ultrasonik jarak objek
const int echo_jarak_pin = D2; //sensor ultrasonik jarak objek
unsigned int dur_jarak; //sensor ultrasonik jarak objek
unsigned int dis_jarak; //sensor ultrasonik jarak objek
const int sensor_sampah_pin = D15; //sensor ultrasonik jarak objek
const int echo_sampah_pin = D14; //sensor ultrasonik jarak objek
unsigned int dur_sampah; //sensor ultrasonik jarak objek
unsigned int dis_sampah; //sensor ultrasonik jarak objek
const int nlogam_pin = D5; //sensor ultrasonik volume sampah organik
const int echo_nlogam_pin = D4; //sensor ultrasonik volume sampah organik
unsigned int dur_nlogam; //sensor ultrasonik volume sampah organik
unsigned int dis_nlogam;//sensor ultrasonik volume sampah organik
const int logam_pin = D7; //sensor ultrasonik volume sampah anorganik
const int echo_logam_pin = D6; //sensor ultrasonik volume sampah anorganik
unsigned int dur_logam; //sensor ultrasonik volume sampah anorganik
unsigned int dis_logam; //sensor ultrasonik volume sampah anorganik

void setup() {
  myservo.attach(D8);  // (pin, min, max)

  pinMode(sensor_jarak_pin, OUTPUT);
  pinMode(echo_jarak_pin, INPUT);
  pinMode(sensor_sampah_pin, OUTPUT);
  pinMode(echo_sampah_pin, INPUT);
  pinMode(nlogam_pin, OUTPUT);
  pinMode(echo_nlogam_pin, INPUT);
  pinMode(logam_pin, OUTPUT);
  pinMode(echo_logam_pin, INPUT);

  digitalWrite(sensor_jarak_pin, LOW);
  digitalWrite(echo_jarak_pin, LOW);
  digitalWrite(sensor_sampah_pin, LOW);
  digitalWrite(echo_sampah_pin, LOW);
  digitalWrite(nlogam_pin, LOW);
  digitalWrite(echo_nlogam_pin, LOW);
  digitalWrite(logam_pin, LOW);
  digitalWrite(echo_logam_pin, LOW);

  pinMode(prox_pin, INPUT);
  digitalWrite(prox_pin, LOW);
}

void loop() {
  myservo.write(90);  // tell servo to go to a particular angle
  delay(1000);

  int logam = check_logam();
  Serial.println(logam);

  read_depan();
  read_sampah();
  read_logam();
  read_nlogam();
  
  delay(2000000);
  
  // myservo.write(0);              
  // delay(500); 
  
  // myservo.write(180);              
  // delay(500);
  
  // myservo.write(180);              
  // delay(1500);                     
}

int check_logam() {
  int prox_logam = digitalRead(prox_pin); //pembacaan data dari sensor proximity
  Serial.println("check logam");
  return prox_logam;
}

int read_depan() {
  digitalWrite(sensor_jarak_pin, LOW);
  delayMicroseconds(2);
  digitalWrite(sensor_jarak_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(sensor_jarak_pin, LOW);
  dur_jarak = pulseIn(echo_jarak_pin, HIGH, 700);
  dis_jarak = (dur_jarak / 2) / 28.5;
  Serial.print("Sensor Orang = ");
  Serial.print(dis_jarak);
  Serial.println(" cm");
  return dis_jarak;
  
}

int read_sampah() {
  digitalWrite(sensor_sampah_pin, LOW);
  delayMicroseconds(2);
  digitalWrite(sensor_sampah_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(sensor_sampah_pin, LOW);
  dur_sampah = pulseIn(echo_sampah_pin, HIGH, 700);
  dis_sampah = (dur_sampah / 2) / 28.5;
  Serial.print("Sensor Sampah = ");
  Serial.print(dis_sampah);
  Serial.println(" cm");
  return dis_sampah;
}

int read_nlogam() {  //perintah baca sensor 2
  digitalWrite(nlogam_pin, LOW);
  delayMicroseconds(2);
  digitalWrite(nlogam_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(nlogam_pin, LOW);
  dur_nlogam = pulseIn(echo_nlogam_pin, HIGH, 700);
  dis_nlogam = (dur_nlogam / 2) / 28.5;
  Serial.print("Sensor Non Logam = ");
  Serial.print(dis_nlogam);
  Serial.println(" cm");
  return dis_nlogam;
}

int read_logam() {  //perintah baca sensor 3
  digitalWrite(logam_pin, LOW);
  delayMicroseconds(2);
  digitalWrite(logam_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(logam_pin, LOW);
  dur_logam = pulseIn(echo_logam_pin, HIGH, 700);
  dis_logam = (dur_logam / 2) / 28.5;
  Serial.print("Sensor Logam = ");
  Serial.print(dis_logam);
  Serial.println(" cm");
  return dis_logam;
}
