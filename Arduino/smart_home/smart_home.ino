
#include <LiquidCrystal.h> // LCD Kütüphanesi
#include <Servo.h> //Servo Kütüphanesi
#include <math.h> // Matematiksel İşlem Kütüphanesi

// Değişkenlerim
Servo myservo0;
char veri;
int salon_lamba = 13;
int yatakodasi_lamba = 10;
int mutfak_lamba = 8;
int dis_lamba = 3;
int dis_lamba_durum = 0;
int buzzer = 11;
int fan = 2;
int derece = 0;
int ldr_deger = 0;
int esikdeger = 350;
int gazdeger;

void setup() {
  // Kurulum
  pinMode(buzzer, OUTPUT);
  pinMode(mutfak_lamba, OUTPUT);
  pinMode(yatakodasi_lamba, OUTPUT);
  pinMode(salon_lamba, OUTPUT);
  pinMode(dis_lamba, OUTPUT);
  pinMode(fan, OUTPUT);
  tone(buzzer, OUTPUT);
  delay(500);
  noTone(buzzer);
  delay(3000);
  Serial.begin(9600);
  myservo0.attach(9);
  myservo0.write(0);
}

// Buzzer Çalma Fonksiyonu
void BuzzerCal(){
  tone(buzzer, 294);
  delay(400);
  noTone(buzzer);
}

void loop() {
  // Sonsuz Döngü...
   veri = Serial.read();
  // Dış Aydınlatma LDR
  ldr_deger = analogRead(A1);
  if(dis_lamba_durum == 0 && ldr_deger <= 300){
    dis_lamba_durum = 1;
    digitalWrite(dis_lamba, HIGH);
  }
  
  if(dis_lamba_durum == 1 && ldr_deger >= 700){
    dis_lamba_durum = 0;
    digitalWrite(dis_lamba, LOW);
  }
  
  // Gelen Değer 0 İse Kapıyı Kapat
  if(veri=='0'){
    for(derece = 180; derece >= 0; derece -= 1){
      myservo0.write(derece);//Motor Döner..
    }
    delay(1000);
  }
  
  // Gelen Değer 1 İse Kapıyı Aç
  if(veri=='1'){
    for(derece = 0; derece <= 180; derece += 1){
      myservo0.write(derece); //Motor Döner..
    }
    delay(1000);
  }
  
  // Gelen Değer 3 İse Salon Lambasını Aç
  if(veri=='3'){
    digitalWrite(salon_lamba, HIGH);
    delay(1000);
  }
  
  //Gelen Değer 4 İse Salon Lambasını Söndür
  if(veri=='4'){
    digitalWrite(salon_lamba, LOW);
    delay(1000);
  }

  //Gelen Değer 5 İse Mutfak Lambası Aç
  if(veri=='5'){
    digitalWrite(mutfak_lamba, HIGH);
    delay(1000);
  }

  //Gelen Değer 6 İse Mutfak Lambası Söndür
  if(veri=='6'){
    digitalWrite(mutfak_lamba, LOW);
    delay(1000);
  }

  //Gelen Değer 7 İse Yatak Odası Lambası Aç
  if(veri=='7'){
    digitalWrite(yatakodasi_lamba, HIGH);
    delay(1000);
  }
  
  //Gelen Değer 8 İse Yatak Odası Lambası Söndür
  if(veri=='8'){
    digitalWrite(yatakodasi_lamba, LOW);
    delay(1000);
  }

  // Gelen Değer 9 İse Fanı Çalıştır
  if(veri=='A'){
    digitalWrite(fan, HIGH);
    delay(1000);
  }

  //Gelen Değer 10 İse Fanı Kapat
  if(veri=='B'){
    digitalWrite(fan, LOW);
    delay(1000);
  }
  //Gaz alarmı 
  gazdeger = analogRead(A2);
  if (gazdeger > esikdeger) {
    digitalWrite(buzzer, HIGH);
    delay(100); 
    
    digitalWrite(buzzer, LOW);
    delay(100);
  }
  else {
    digitalWrite(buzzer, LOW);
  }
  
  delay(100);
}
