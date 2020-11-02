#define wl 7            //przycisk wlaczajacy
#define pr 6            //przycisk w prawo
#define lw 5           //przycisk w lewo
#define led_wl 4    //led do sygnalizacji pracy
#define wy_pr 3    //ruch w prawo
#define wy_lw 2    //ruch w lewo
#define PWM 9      //ustawienie predkosci podpiąc pod pin w PWM~

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);

float licznik=0;

void setup() {
  // deklaracja tyrybu pracy wejść/wyjsc
 
  pinMode(led_wl,OUTPUT);
  pinMode(wy_pr,OUTPUT);
  pinMode(wy_lw,OUTPUT);
  pinMode(wl,INPUT);
  pinMode(pr,INPUT);
  pinMode(lw,INPUT);
  pinMode(PWM,OUTPUT);
  //ustawienie predkosci silnika
  analogWrite(PWM,128);
  //inicjalizacja pracy wyswietlacza
  lcd.init();
  lcd.backlight();
  lcd.setCursor(3,0);
}

void loop() {
  //warunki przelaczania się w tryb pracy i wyłączenia
if(digitalRead(wl)){
    digitalWrite(led_wl,!digitalRead(led_wl));
    if(digitalRead(led_wl)) licznik++;
    lcd.print(licznik);
    lcd.setCursor(3,0);
    delay(40);
    while(digitalRead(wl)){}
    delay(40);
    }
  //warunki zalaczenia orotow w prawo
if(digitalRead(led_wl) && digitalRead(pr)){
  digitalWrite(wy_pr,!digitalRead(wy_pr));
  delay(40);
  while(digitalRead(pr)){}
  delay(40);
  digitalWrite(wy_lw,LOW);
}
  //warunki zalaczenia obrotow w lewo
if(digitalRead(led_wl) && digitalRead(lw)){
  digitalWrite(wy_lw,!digitalRead(wy_lw));
  delay(40);
  while(digitalRead(lw)){}
  delay(40);
  digitalWrite(wy_pr,LOW);
}
  //warunek wylaczenia silnika
if(!digitalRead(led_wl)){
  digitalWrite(wy_lw,LOW);
  digitalWrite(wy_pr,LOW);
}

}
