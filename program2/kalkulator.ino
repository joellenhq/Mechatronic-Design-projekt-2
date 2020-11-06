//zmienna przechowujaca znak dzialanie
char dzialanie;
float a1, b1;

void setup()
{
  //szybkosc transmisji 9600 bit/sekunda
  Serial.begin(1200);
  //wypianie tekstu informujacego uzytkownika o dzialaniu programu
  Serial.print("Kalkulator pozwalajacy na wykonywanie podstawowych dzialan");
  Serial.println();
}


//zdefiniowanie funkcji odpowiadajacej za wykoanie dzialania
void rozwiaz(float x, float y, char dzialanie1)
{
    //zdefiniowanie zmiennej, w ktorej przechowywany bedzie wynik  
    double wynik;
    switch (dzialanie1)
    {
    case '+': 
      wynik = x + y;
      Serial.print("Wynik a + b = ");
    break;
  
    case '-':
      wynik = x - y;
      Serial.print("Wynik a - b = ");
    break;

    case '*':
      wynik = x*y;
      Serial.print("Wynik a * b = ");
    break;

    case '/':
      wynik=x/y;
      Serial.print("Wynik a / b = ");
    break;
  }
     
     Serial.println(wynik);
     if(y==0 && dzialanie1=="/"){
      Serial.println("nie dziel cholero przez zero");
     }
     Serial.println();
     if(Serial.available()){
      Serial.read();
     }
}


void loop()
{
Serial.println("Wpisz dzialanie (bez spacji, jednym ciagiem)");
while(!Serial.available());
  if(Serial.available()>0){
    
      a1=Serial.parseFloat()   ;
      dzialanie=Serial.read();
      b1=Serial.parseFloat();
      Serial.print(a1);
      Serial.print(dzialanie);
      Serial.println(b1);
      rozwiaz(a1,b1,dzialanie);
      
  }

}
