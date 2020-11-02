int num = 0;
int a, b;
char dzialanie;

void setup()
{
  Serial.begin(9600);
  Serial.print("To jest kalkulator, liczb dwucyfrowych\n");
}


void rozwiaz( float a, float b, char dzialanie)
{
    float wynik;
    switch (dzialanie)
    {
    case '+': 
    wynik = a + b;
    Serial.print("Wynik a + b = ");
    Serial.println(wynik);
    break;
	
      
    case '-':
    wynik = a - b;
    Serial.print("Wynik a - b = ");
    Serial.println(wynik);
    break;

    case '*':
    wynik = a*b;
    Serial.print("Wynik a * b = ");
    Serial.println(wynik);
    break;

    case '/':
    wynik=a/b;
    Serial.print("Wynik a / b = ");
    Serial.println(wynik);
    break;

	}
}



void loop()
{

    
  
  Serial.print("Pierwsza liczba, a= ");
  while(!Serial.available()); 
  delay (100);
  a = Serial.parseInt();
  Serial.println(a);
  
  
  Serial.print("Druga liczba, b= ");
  while(!Serial.available());
  delay (100);
  b = Serial.parseInt();
  Serial.println(b);
  
  Serial.print("Dzialanie ( +, -, *, /), wybrano: "); 
  while(!Serial.available());
  delay (100);
  dzialanie = Serial.read();
  Serial.println(dzialanie);
  
  
  // Sprawdzenie czy nie wystapilo dzielenie przez 0
  if( b == 0 && dzialanie == '/')
  {
    Serial.println("Nie dziel przez 0");
  }
  
  // Sprawdzenie czy liczby są z zakresu 10-100
   else if ( (10 <= (a & b) && ( a & b ) <= 100 ) == false)
  {
  	Serial.println("Jedna lub obie liczby nie sa z zakresu - (10 - 100)");
  }
  
  else 
  {
    rozwiaz (a,b,dzialanie);
      
  }    
}