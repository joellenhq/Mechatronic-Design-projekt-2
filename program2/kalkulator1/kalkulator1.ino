//zmienna przechowujaca znak dzialania
char dzialanie;
//zmienne odpowiadajace za odczytywane znaki z portu szeregowego
String b="b";
String a="a";
//zmienne a,b przekonwertowane na float
float a1, b1;

void setup(){
  //szybkosc transmisji 4800 bit/sekunda
  Serial.begin(4800);
  //wypisanie tekstu informujacego uzytkownika o dzialaniu programu
  Serial.print("Kalkulator pozwalajacy na wykonywanie podstawowych dzialan");
  Serial.println();
}


//zdefiniowanie funkcji odpowiadajacej za wykonanie dzialania
float rozwiaz(float a, float b, char dzialanie){
    //zdefiniowanie zmiennej, w ktorej przechowywany bedzie wynik  
    double wynik;
    //w zaleznosci od wybranego dzialania wykona sie dana instrukcja
    switch (dzialanie){
    //dodawanie
    case '+': 
      wynik = a + b;
      Serial.print("Wynik a + b = ");
    break;
    //odejmowanie  
    case '-':
      wynik = a - b;
      Serial.print("Wynik a - b = ");
    break;
    //mnozenie
    case '*':
      wynik = a*b;
      Serial.print("Wynik a * b = ");
    break;
    //dzielenie
    case '/':
      wynik=a/b;
      Serial.print("Wynik a / b = ");
    break;
  }
  //wypisanie wyniku
  Serial.print(wynik);
  Serial.println();
}

//funkcja sprawdzajaca czy padana wartosc jest liczba
boolean liczba(String str){
   //zmienna, ktora zostanie wykorzytana do zliczania poprawnych znakow
   byte i=0;
   byte j=1;
   while(i<(str.length())){
    if(i==0){
     //pierwszy znak moze byc minusem
      if(isDigit(str.charAt(i)) || str.charAt(i)=='-') j++;
      else j=0;
    }
    else{
      if(isDigit(str.charAt(i)) || str.charAt(i)=='.') j++;
    }
   i++;
   }
   //ilosc znakow powinna zgadzac sie z naliczonymi poprawnymi znakami
   if (j==i){ 
    return true;
   else{ 
    return false;
   }
} 

void loop(){
  //zmienne ustawiane aby pozbyc sie wartosci z poprzedniego rownania
  a="a";
  b="b";
  dzialanie='a';
     
  Serial.print("Pierwsza liczba, a= ");
    //petla sprawdzajaca poprawnosc wpisanej liczby, będzie się wykonywala dopoki nie zostanie wpisana liczba
    while(liczba(a)==false){
      while(!Serial.available());
      //odczytanie znakow z portu szeregowego
      a=Serial.readString();
     }
  //konwersja string na float   
  a1=a.toFloat();
  //wyswietlenie wpisanej wartosci w porcie szeregowym
  Serial.print(a);
  Serial.println();
  Serial.print(a1);
  Serial.println();
  
  Serial.print("Druga liczba: b= ");
  //petla sprawdzajaca poprawnosc wpisanej liczby, będzie się wykonywala dopoki nie zostanie wpisana liczba
  while(liczba(b)==false){
    while(!Serial.available());
    //odczytanie lancucha znakow z portu szeregowego
     b=Serial.readString();
  }
  //wyswietlenie wpisanej wartosci w serialu
  b1 = b.toFloat();
  //wyswietlenie wpisanej wartosci w porcie szeregowym
  Serial.print(b);
  Serial.println();
  Serial.print(b1);
  Serial.println();
  
  Serial.print("Dzialanie ( +, -, *, /), wybrano: "); 
  while(!Serial.available());
    //petla bedzie sie wykonywala dopoki nie zostanie wpisany jeden ze znakow
    while(dzialanie!='+' && dzialanie!='-' && dzialanie!='*' && dzialanie!='/'){
      //odczytanie znaku podanego przez uzytkownika
      dzialanie = Serial.read();
  }
  Serial.print(dzialanie);
  Serial.println();
  
  
  // Sprawdzenie czy nie wystapilo dzielenie przez 0
  if( b1 == 0 && dzialanie == '/')
  {
    Serial.print("Zabronione działanie dzielenia przez 0");
    Serial.println();
  }
  else 
  {
    //wywolanie funkcji, ktora oblicza rownanie
    rozwiaz(a1,b1,dzialanie);
    Serial.println();
  }    
delay(20);
}
