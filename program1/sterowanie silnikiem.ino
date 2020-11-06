#define wl 7            //przycisk wlaczajacy
#define pr 6            //przycisk w prawo
#define lw 5           //przycisk w lewo
#define led_wl 4    //led do sygnalizacji pracy
#define wy_pr 3    //ruch w prawo
#define wy_lw 2    //ruch w lewo
#define PWM 9      //ustawienie predkosci podpiąc pod pin w PWM~
//zalaczenie bibliotek
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
//utworzenie obiektu typu lcd
LiquidCrystal_I2C lcd(0x27,16,2);
//inicjalizacja zmiennej globalnej
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
  //inicjalizacja portu szeregowego
  Serial.begin();
}

void loop() {
  //warunki przelaczania się w tryb pracy i wyłączenia
if(digitalRead(wl)){
    digitalWrite(led_wl,!digitalRead(led_wl));    //negacja wyjscia sygnalizacji
    if(digitalRead(led_wl)) licznik++;                  //inkrementacja licznika w przypadku  włączenia
    lcd.print(licznik);                                            //wpisanie stanu licznika na lcd
    lcd.setCursor(3,0);
   Serial.println(licznik);                                      //wpisanie stanu licznika w serialu
    delay(40);                                                        //oczekiwanie na drgania styku (dobrane doświadczalnie)
    while(digitalRead(wl)){}                                //wykrywanie puszczenia przycisku
    delay(40);                                                        //oczekiwanie na drgania styku (dobrane doświadczalnie)
    }
  //warunki zalaczenia orotow w prawo
if(digitalRead(led_wl) && digitalRead(pr)){     
  digitalWrite(wy_pr,!digitalRead(wy_pr));      //negacja wyjscia obrotów w prawo
  delay(40);                                                        ////oczekiwanie na drgania styku (dobrane doświadczalnie)
  while(digitalRead(pr)){}                                //wykrywanie puszczenia przycisku
  delay(40);                                                        //oczekiwanie na drgania styku (dobrane doświadczalnie)
  digitalWrite(wy_lw,LOW);                            //wylaczenie wyjscia odpowiedzialnego za ruch w przeciwnym kierunku
}
  //warunki zalaczenia obrotow w lewo - analogicznie jak poprzedni warunek
if(digitalRead(led_wl) && digitalRead(lw)){
  digitalWrite(wy_lw,!digitalRead(wy_lw));
  delay(40);
  while(digitalRead(lw)){}
  delay(40);
  digitalWrite(wy_pr,LOW);
}
  //warunek wylaczenia silnika
if(!digitalRead(led_wl)){
  digitalWrite(wy_lw,LOW);              //wylaczenie wyjsc odpowiedzialnych za ruch
  digitalWrite(wy_pr,LOW);
}

}
