#define TRIG 2                
#define ECHO 3
#define prawo 4
#define lewo 5
#define P 10             //wzmocnienie
#define I 5               //czas zdwojenia
#define D 1             //czas wyprzedzenia
#define PWM 9
//deklaracja zmiennych globalnych
unsigned long poprzedniczas,aktualnyczas;
float odleglosc,poprz_odl,zad_odl,uchyb,poprz_uchyb,calka;
int sygnal;

void setup() {
  // ustawianie wyjsc w odpowiernich trybach
 pinMode(TRIG,OUTPUT);
 pinMode(ECHO,INPUT);
 pinMode(PWM,OUTPUT);
 //rozpoczęcie odliczania czasu
 poprzedniczas=millis();
 //ustawienie zadanej odleglosci
 zad_odl=20.0;
}

void loop() {
  aktualnyczas=millis();                              //ustawienie aktualnego czasu
  if(aktualnyczas-poprzedniczas>=100){  //konstrukcja millis do zapewnienia stałego czasu próbkowania Tp=100ms
    poprzedniczas=aktualnyczas;
  
    //program regulatora;
    odleglosc=4*odleglosc/5+(pomiar()/5); //odleglosc jako srednia rekurencyjna wskazań z ostatnich 0.5s
    poprz_uchyb=uchyb;
    uchyb=zad_odl-odleglosc;                     //obliczenie uchybu
    sygnal=regulator(uchyb);                      //obliczenie sygnalu sterujacego
    analogWrite(PWM,abs(sygnal));                    //ustawienie prędkosci
    if(sygnal>40) {                                         //ustawienie kierunku obrotow #deadzone
      digitalWrite(prawo,HIGH);
      digitalWrite(lewo,LOW);
    }
    else if(sygnal<-40){
      digitalWrite(lewo,HIGH);
      digitalWrite(prawo,LOW);    
    }
    else {
      digitalWrite(prawo,LOW);
      digitalWrite(lewo,LOW);
    }

    //koniec programu regulatora;
  }
}

float pomiar(){
  unsigned long czas;
  digitalWrite(TRIG,HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG,LOW);
  czas = pulseIn(ECHO,HIGH);
  return czas/58.00;
}

int regulator(float uchyb) {
  //wartosc od 0-255 uwzglednic saturacje
  //P
  float prop=uchyb*P/10;
  //anti-windup
  if(sygnal=255){      
    calka=calka;
  }else{
    calka=calka+uchyb;
  }
  //I
  float integ=calka*I/10;  
  //D
  float derr=uchyb-poprz_uchyb*D/10;
  //Saturacja
  float suma=prop+integ+derr;
  if(suma>255){
    suma=255;
  }else if(suma<-255){
    suma=-255;
  }
return round(suma);
}
