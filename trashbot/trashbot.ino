#define BLYNK_TEMPLATE_ID "TMPL6Vws4pd5_"
#define BLYNK_TEMPLATE_NAME "Smart Trash"
#define BLYNK_AUTH_TOKEN "wBQ11SKvkEniZwLd-sRu8D_my4VrB1O9"
#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <Servo.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "Mau ?";
char pass[] = "farid333";

Servo servo_pintu; 
Servo servo_divider;
int pintupos = 0; //motor servo
int dividerpos = 90;  
int led_metal_red = D10;
int led_metal_green = D11;

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
int logam;
int nlogam;

BlynkTimer timer;



void setup() {  //mulai awal progam
  
  servo_pintu.attach(D9); //letak motor servo di D9
  servo_divider.attach(D8);
  servo_pintu.write(pintupos);
  servo_divider.write(dividerpos);
  delay(30);
  
  pinMode(D9, OUTPUT);
  pinMode(D8, OUTPUT);
  pinMode(led_metal_red, OUTPUT);
  pinMode(led_metal_green, OUTPUT);
  pinMode(sensor_jarak_pin, OUTPUT);
  pinMode(echo_jarak_pin, INPUT);
  pinMode(sensor_sampah_pin, OUTPUT);
  pinMode(echo_sampah_pin, INPUT);
  pinMode(nlogam_pin, OUTPUT);
  pinMode(echo_nlogam_pin, INPUT);
  pinMode(logam_pin, OUTPUT);
  pinMode(echo_logam_pin, INPUT);
  pinMode(prox_pin, INPUT);

  digitalWrite(led_metal_red, LOW);
  digitalWrite(led_metal_green, LOW);
  digitalWrite(sensor_jarak_pin, LOW);
  digitalWrite(echo_jarak_pin, LOW);
  digitalWrite(sensor_sampah_pin, LOW);
  digitalWrite(echo_sampah_pin, LOW);
  digitalWrite(nlogam_pin, LOW);
  digitalWrite(echo_nlogam_pin, LOW);
  digitalWrite(logam_pin, LOW);
  digitalWrite(echo_logam_pin, LOW);
  digitalWrite(prox_pin, LOW);

  digitalWrite(D8, LOW);
  digitalWrite(D9, LOW);
  
  Serial.begin(115200); //RW system
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(1000L, myTimer);

}
  
void loop() {  //perintah perulangan
  Blynk.run();
  int orang = read_depan();
  Serial.print("jarak orang : ");
  Serial.print(orang);
  Serial.println(" cm");
  if(orang<=6){
    open_gate();
    int sampah = read_sampah();
    delay(300);
    Serial.print("jarak sampah :");
    Serial.print(sampah);
    Serial.println(" cm");
    if(sampah<=3) {
      int apakah_logam = check_logam();
      Serial.println(apakah_logam);
      if (apakah_logam == 0) {
        buang_logam();
      }
      else {
        buang_non_logam();
      }
    }
    close_gate();
  }

  logam = read_logam();
  if(logam<=1){
//    Serial.println("sampah logam penuh");
    digitalWrite(led_metal_green, HIGH);
  }
  else{
//    Serial.println("sampah logam kosong");
    digitalWrite(led_metal_green, LOW);
    nlogam = read_nlogam();
    if(nlogam<=1){
  //    Serial.println("sampah non-logam penuh");
      digitalWrite(led_metal_red, HIGH);
    }
    else{
  //    Serial.println("sampah non-logam kosong");
      digitalWrite(led_metal_red, LOW);
    }        
  }

  timer.run();        

//  delay(10000);

}

void myTimer() {
  logam = 37 - logam;
  nlogam = 37 - nlogam;

  Blynk.virtualWrite(V7, logam);
  Blynk.virtualWrite(V5, nlogam);

  if (logam > 32) {
    Blynk.virtualWrite(V0, 1);
  }
  else {
    Blynk.virtualWrite(V0, 0);
  }
  
  if (nlogam > 32) {
    Blynk.virtualWrite(V1, 1);
  }
  else {
    Blynk.virtualWrite(V1, 0);
  }
}

// ------------------------------------------------------------------------

int read_depan() {
  digitalWrite(sensor_jarak_pin, LOW);
  delayMicroseconds(2);
  digitalWrite(sensor_jarak_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(sensor_jarak_pin, LOW);
  dur_jarak = pulseIn(echo_jarak_pin, HIGH);
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
  dur_sampah = pulseIn(echo_sampah_pin, HIGH);
  dis_sampah = (dur_sampah / 2) / 28.5;
  Serial.print("Sensor Sampah = ");
  Serial.print(dis_sampah);
  Serial.println(" cm");
  return dis_sampah;
}

void close_gate() {
  for(pintupos=180;pintupos>=0;pintupos-=1){
    servo_pintu.write(pintupos);
    Serial.print("5");
    delay(15);
  }
  Serial.println();
}

void open_gate() {
  for(pintupos=0;pintupos<180;pintupos+=1){
    servo_pintu.write(pintupos);
    Serial.print("5");
    delay(15);
  }
  Serial.println();
}

int check_logam() {
  int prox_logam = digitalRead(prox_pin); //pembacaan data dari sensor proximity
  Serial.println("check logam");
  return prox_logam;
}

void buang_logam() {
  for(dividerpos=90;dividerpos>=0;dividerpos-=1){
    servo_divider.write(dividerpos);
    Serial.print("1");
    delay(15);
  }
  Serial.println();
  for(dividerpos=0;dividerpos<90;dividerpos+=1){
    servo_divider.write(dividerpos);
    Serial.print("2");
    delay(15);
  }
  Serial.println();
}

void buang_non_logam() {
  for(dividerpos=90;dividerpos<=180;dividerpos+=1){
    servo_divider.write(dividerpos);
    Serial.print("3");
    delay(15);
  }
  Serial.println();
  for(dividerpos=180;dividerpos>=90;dividerpos-=1){
    servo_divider.write(dividerpos);
    Serial.print("4");
    delay(15);
  }
  Serial.println();
}

int read_nlogam() {  //perintah baca sensor 2
  digitalWrite(nlogam_pin, LOW);
  delayMicroseconds(2);
  digitalWrite(nlogam_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(nlogam_pin, LOW);
  dur_nlogam = pulseIn(echo_nlogam_pin, HIGH);
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
  dur_logam = pulseIn(echo_logam_pin, HIGH);
  dis_logam = (dur_logam / 2) / 28.5;
  Serial.print("Sensor Logam = ");
  Serial.print(dis_logam);
  Serial.println(" cm");
  return dis_logam;
}

// -------------------------------------------------------------------------------------

void read_proximity() {
  digitalWrite(sensor_sampah_pin, LOW);
  delayMicroseconds(2);
  digitalWrite(sensor_sampah_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(sensor_sampah_pin, LOW);
  dur_sampah = pulseIn(echo_sampah_pin, HIGH);
  dis_sampah = (dur_sampah / 2) / 28.5;
  Serial.print("Sensor Sampah = ");
  Serial.print(dis_sampah);
  Serial.println(" cm");
  if(dis_sampah<=6){
    int proxin = digitalRead(prox_pin); //pembacaan data dari sensor proximity
//    Serial.println("ada sampah");
    for(pintupos=90;pintupos>0;pintupos-=1){
      servo_pintu.write(pintupos);
      Serial.print("6");
      delay(15);
    }
    if(proxin==HIGH){ 
//      Serial.println("sampah non logam");
      for(dividerpos=180;dividerpos>=0;dividerpos-=1){
        servo_divider.write(dividerpos);
        Serial.print("1");
        delay(15);
      }
      for(dividerpos=0;dividerpos<=180;dividerpos+=1){
        servo_divider.write(dividerpos);
        Serial.print("2");
        delay(15);
      }
    }
    else{
//      Serial.println("sampah logam");
      for(dividerpos=180;dividerpos<=180;dividerpos+=1){
        servo_divider.write(dividerpos);
        Serial.print("3");
        delay(15);
      }
      for(dividerpos=180;dividerpos>=180;dividerpos-=1){
        servo_divider.write(dividerpos);
        Serial.print("4");
        delay(15);
      }
    }
  }
}
 
void read_jarak() {  //perintah baca sensor 1
  digitalWrite(sensor_jarak_pin, LOW);
  delayMicroseconds(2);
  digitalWrite(sensor_jarak_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(sensor_jarak_pin, LOW);
  dur_jarak = pulseIn(echo_jarak_pin, HIGH);
  dis_jarak = (dur_jarak / 2) / 28.5;
    Serial.print("Sensor Orang = ");
    Serial.print(dis_jarak);
    Serial.println(" cm");
    if(dis_jarak<=6){
//      Serial.println("ada pengguna mendekat");
      for(pintupos=0;pintupos<90;pintupos+=1){
        servo_pintu.write(pintupos);
        Serial.print("5");
        delay(15);
      }
      read_proximity();
    }
}

