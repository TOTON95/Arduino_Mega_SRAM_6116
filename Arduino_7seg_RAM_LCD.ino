//@TOTON95
#include <LiquidCrystal.h>
//Controles RAM
#define CS 22
#define RW 23
//Bus de Direcciones
#define A0 13
#define A1 12
#define A2 11
#define A3 10
//Bus de Datos
#define D0 9
#define D1 8
#define D2 7
#define D3 6

int i = 0;
int dir = 0;
byte iA0;
byte iA1;
byte iA2;
byte iA3;
byte mask = B00000000;
int valor;

char c;
String buff;

int modo = -1;
int cambio = -1;
int operacion = -1;

String str1;
String str2;
int num1;
int num2;
float aux1;
float aux2;
float resultado;

LiquidCrystal lcd(24, 25, 26, 27, 28, 29);

void setup() {
  Serial.begin(19200);
  pinMode(CS, OUTPUT);
  pinMode(RW, OUTPUT);
  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(A3, OUTPUT);
  digitalWrite(CS, HIGH);
  digitalWrite(RW, LOW);
  delay(5);
  lcd.begin(16, 2);
  lcd.setCursor(0,0);
  lcd.print("PREPARADO");
}
void loop() {
  /*for(int i = 0; i<10;i++)
    {
    direccion(i);
    grabarRAM(i);
    delay(1000);
    }
    for(int i = 0; i<10;i++)
    {
    direccion(i);
    leerRAM();
    prntLCD();
    delay(1000);
    }*/
  if (Serial.available() > 0)
  {
    c = ((byte)Serial.read());
    buff += c;
    //Serial.println(buff);
    delay(5);

    if (c == '*')
    {
      //Serial.print("Dato recibido: ");
      for (int i = 0; i < buff.length(); i++)
      {
        if (buff[i] == 'W')
        {
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Grabando...");
          modo = 0;
        }
        if (buff[i] == 'R')
        {
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Leyendo...");
          modo = 1;
        }
        if (buff[i] == 'O')
        {
          lcd.clear();
          lcd.setCursor(0, 0);
          //lcd.print("Operaciones...");
          modo = 2;
        }
        if (buff[i] == 'A' && modo == 0)
        {
          //Escritura (direccion)
          cambio = 0;
        }
        if (buff[i] == 'B' && modo == 0)
        {
          //Escritura (dato)
          cambio = 1;
        }
        if (buff[i] == 'A' && modo == 1)
        {
          //Lectura (direccion)
          cambio = 2;
        }
        if (buff[i] == 'A' && modo == 2)
        {
          //Lectura (direccion)
          cambio = 3;
        }
        if (buff[i] == 'B' && modo == 2)
        {
          //Lectura (direccion)
          cambio = 4;
        }
        if (isDigit(buff[i]))
        {
          if (cambio == 0)
          {
            //Escritura (direccion)
            str1 += buff[i];
            num1 = str1.toInt();
          }
          if (cambio == 1)
          {
            //Escritura (dato)
            str2 += buff[i];
            num2 = str2.toInt();
          }
          if (cambio == 2)
          {
            //Lectura (direccion)
            str1 += buff[i];
            num1 = str1.toInt();
          }
          if (cambio == 3)
          {
            //Operaciones (direccion 1)
            str1 += buff[i];
            num1 = str1.toInt();
          }
          if (cambio == 4)
          {
            //Operaciones (direccion 2)
            str2 += buff[i];
            num2 = str2.toInt();
          }
        }
        if (buff[i] == '+')
        {
          //Suma
          operacion = 0;
        }
        if (buff[i] == '-')
        {
          //Resta
          operacion = 1;
        }
        if (buff[i] == '/')
        {
          //Division
          operacion = 2;
        }
        if (buff[i] == 'X')
        {
          //Multiplicacion
          operacion = 3;
        }
      }
      if (modo == 0)
      {
        //Escritura
        lcd.setCursor(0, 1);
        lcd.print("-> Grabando");
        lcd.setCursor(0, 2);
        lcd.print("Dir: ");
        lcd.print(num1);
        lcd.print(" Num: ");
        lcd.print(num2);
        direccion(num1);
        grabarRAM(num2);
      }
      if (modo == 1)
      {
        //Lectura
        lcd.setCursor(0, 1);
        lcd.print("-> Leyendo");
        lcd.setCursor(0, 2);
        lcd.print("Dir: ");
        lcd.print(num1);
        lcd.print(" Num: ");
        direccion(num1);
        leerRAM();
        lcd.print(valor);
      }
      if (modo == 2)
      {
        //Operaciones
        lcd.setCursor(0, 0);
        lcd.print("Dir1:");
        lcd.print(num1);
        lcd.print(" Dir2:");
        lcd.print(num2);

        if (operacion == 0)
        {
          //Suma
          lcd.setCursor(0, 2);
          direccion(num1);
          leerRAM();
          aux1 = valor;
          lcd.print(aux1);
          delay(750);
          lcd.print("+");
          direccion(num2);
          leerRAM();
          aux2 = valor;
          lcd.print(aux2);
          lcd.print("=");
          delay(750);
          resultado = aux1 + aux2;
          lcd.print(resultado, 2);
        }
        if (operacion == 1)
        {
          //Resta
          lcd.setCursor(0, 2);
          direccion(num1);
          leerRAM();
          aux1 = valor;
          lcd.print(aux1);
          delay(750);
          lcd.print("-");
          direccion(num2);
          leerRAM();
          aux2 = valor;
          lcd.print(aux2);
          lcd.print("=");
          delay(750);
          resultado = aux1 - aux2;
          lcd.print(resultado, 2);
        }
        if (operacion == 2)
        {
          //Division
          lcd.setCursor(0, 2);
          direccion(num1);
          leerRAM();
          aux1 = valor;
          lcd.print(aux1);
          delay(750);
          lcd.print("/");
          direccion(num2);
          leerRAM();
          aux2 = valor;
          lcd.print(aux2);
          lcd.print("=");
          delay(750);
          resultado = aux1 / aux2;
          lcd.print(resultado, 2);
        }
        if (operacion == 3)
        {
          //Multiplicacion
          lcd.setCursor(0, 2);
          direccion(num1);
          leerRAM();
          aux1 = valor;
          lcd.print(aux1);
          delay(750);
          lcd.print("*");
          direccion(num2);
          leerRAM();
          aux2 = valor;
          lcd.print(aux2);
          lcd.print("=");
          delay(750);
          resultado = aux1 * aux2;
          lcd.print(resultado, 2);
        }
      }
      buff = "";
    }
    //Serial.print(buff);
    str1 = "";
    str2 = "";
  }

}

void grabarRAM(int k) {
  digitalWrite(CS, HIGH);
  delay(10);
  digitalWrite(RW, LOW);
  //se escribe dato, modificar pinMode
  outPin();
  delay(5);
  dato(k);
  //Termina prueba
  delay(5);
  digitalWrite(CS, LOW);
  delay(10);
  digitalWrite(CS, HIGH);
  delay(10);
}

void leerRAM() {
  digitalWrite(CS, HIGH);
  delay(10);
  //poner Bus de dirección
  digitalWrite(RW, HIGH);
  //se retiran datos en el bus
  inPin();
  delay(5);
  digitalWrite(CS, LOW);
  delay(10);
  valor = bcd();
}
void direccion(int u)
{
  dir = u;
  switch (u) {
    case 0:
      digitalWrite(A0, LOW);
      digitalWrite(A1, LOW);
      digitalWrite(A2, LOW);
      digitalWrite(A3, LOW);
      break;
    case 1:
      digitalWrite(A0, HIGH);
      digitalWrite(A1, LOW);
      digitalWrite(A2, LOW);
      digitalWrite(A3, LOW);
      break;
    case 2:
      digitalWrite(A0, LOW);
      digitalWrite(A1, HIGH);
      digitalWrite(A2, LOW);
      digitalWrite(A3, LOW);
      break;
    case 3:
      digitalWrite(A0, HIGH);
      digitalWrite(A1, HIGH);
      digitalWrite(A2, LOW);
      digitalWrite(A3, LOW);
      break;
    case 4:
      digitalWrite(A0, LOW);
      digitalWrite(A1, LOW);
      digitalWrite(A2, HIGH);
      digitalWrite(A3, LOW);
      break;
    case 5:
      digitalWrite(A0, HIGH);
      digitalWrite(A1, LOW);
      digitalWrite(A2, HIGH);
      digitalWrite(A3, LOW);
      break;
    case 6:
      digitalWrite(A0, LOW);
      digitalWrite(A1, HIGH);
      digitalWrite(A2, HIGH);
      digitalWrite(A3, LOW);
      break;
    case 7:
      digitalWrite(A0, HIGH);
      digitalWrite(A1, HIGH);
      digitalWrite(A2, HIGH);
      digitalWrite(A3, LOW);
      break;
    case 8:
      digitalWrite(A0, LOW);
      digitalWrite(A1, LOW);
      digitalWrite(A2, LOW);
      digitalWrite(A3, HIGH);
      break;
    case 9:
      digitalWrite(A0, HIGH);
      digitalWrite(A1, LOW);
      digitalWrite(A2, LOW);
      digitalWrite(A3, HIGH);
      break;
    case 10:
      digitalWrite(A0, LOW);
      digitalWrite(A1, HIGH);
      digitalWrite(A2, LOW);
      digitalWrite(A3, HIGH);
      break;
    case 11:
      digitalWrite(A0, HIGH);
      digitalWrite(A1, HIGH);
      digitalWrite(A2, LOW);
      digitalWrite(A3, HIGH);
      break;
    case 12:
      digitalWrite(A0, LOW);
      digitalWrite(A1, LOW);
      digitalWrite(A2, HIGH);
      digitalWrite(A3, HIGH);
      break;
    case 13:
      digitalWrite(A0, HIGH);
      digitalWrite(A1, LOW);
      digitalWrite(A2, HIGH);
      digitalWrite(A3, HIGH);
      break;
    case 14:
      digitalWrite(A0, LOW);
      digitalWrite(A1, HIGH);
      digitalWrite(A2, HIGH);
      digitalWrite(A3, HIGH);
      break;
    case 15:
      digitalWrite(A0, HIGH);
      digitalWrite(A1, HIGH);
      digitalWrite(A2, HIGH);
      digitalWrite(A3, HIGH);
      break;

  }
}
void dato(int t)
{
  switch (t) {
    case 0:
      digitalWrite(D0, LOW);
      digitalWrite(D1, LOW);
      digitalWrite(D2, LOW);
      digitalWrite(D3, LOW);
      break;
    case 1:
      digitalWrite(D0, HIGH);
      digitalWrite(D1, LOW);
      digitalWrite(D2, LOW);
      digitalWrite(D3, LOW);
      break;
    case 2:
      digitalWrite(D0, LOW);
      digitalWrite(D1, HIGH);
      digitalWrite(D2, LOW);
      digitalWrite(D3, LOW);
      break;
    case 3:
      digitalWrite(D0, HIGH);
      digitalWrite(D1, HIGH);
      digitalWrite(D2, LOW);
      digitalWrite(D3, LOW);
      break;
    case 4:
      digitalWrite(D0, LOW);
      digitalWrite(D1, LOW);
      digitalWrite(D2, HIGH);
      digitalWrite(D3, LOW);
      break;
    case 5:
      digitalWrite(D0, HIGH);
      digitalWrite(D1, LOW);
      digitalWrite(D2, HIGH);
      digitalWrite(D3, LOW);
      break;
    case 6:
      digitalWrite(D0, LOW);
      digitalWrite(D1, HIGH);
      digitalWrite(D2, HIGH);
      digitalWrite(D3, LOW);
      break;
    case 7:
      digitalWrite(D0, HIGH);
      digitalWrite(D1, HIGH);
      digitalWrite(D2, HIGH);
      digitalWrite(D3, LOW);
      break;
    case 8:
      digitalWrite(D0, LOW);
      digitalWrite(D1, LOW);
      digitalWrite(D2, LOW);
      digitalWrite(D3, HIGH);
      break;
    case 9:
      digitalWrite(D0, HIGH);
      digitalWrite(D1, LOW);
      digitalWrite(D2, LOW);
      digitalWrite(D3, HIGH);
      break;
  }
}
void outPin()
{
  pinMode(D0, OUTPUT);
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
}
void inPin()
{
  pinMode(D0, INPUT);
  pinMode(D1, INPUT);
  pinMode(D2, INPUT);
  pinMode(D3, INPUT);
}
void prntLCD()
{
  lcd.setCursor(0, 0);
  lcd.print("Direccion: ");
  lcd.print(dir);
  lcd.setCursor(0, 1);
  lcd.print("Valor: ");
  lcd.print(valor);
  valor = 0;
}
int bcd()
{
  int ivalue;
  byte out;
  if (digitalRead(D0) == HIGH)
  {
    iA0 = B00000001;
  }
  if (digitalRead(D0) == LOW)
  {
    iA0 = B00000000;
  }
  if (digitalRead(D1) == HIGH)
  {
    iA1 = B00000010;
  }
  if (digitalRead(D1) == LOW)
  {
    iA1 = B00000000;
  }
  if (digitalRead(D2) == HIGH)
  {
    iA2 = B00000100;
  }
  if (digitalRead(D2) == LOW)
  {
    iA2 = B00000000;
  }
  if (digitalRead(D3) == HIGH)
  {
    iA3 = B00001000;
  }
  if (digitalRead(D3) == LOW)
  {
    iA3 = B00000000;
  }
  out = (iA0 | mask);
  out = (iA1 | out);
  out = (iA2 | out);
  out = (iA3 | out);

  ivalue = int(out);
  return ivalue;
}
//@TOTON95

