#include "LedControl.h"
LedControl ledControl = LedControl(51, 53, 49, 1); // LedControl(DIN, CLK, CS / LOAD, # de dispositivos (cantidad de modulos) de 1 a 8)

int filas[] = {24, 22, 2, 3, 4, 5, 6, 7}; // filas encienden con 0
int columnas[] = {8, 9, 10, 11, 12, 13, 23, 25}; // columnas encienden con 1

/*  LETRERO */
int UP = 52, DW = 50, DIR = 48;
boolean direccion = true;
int velocidadCartel = 250;
int posicionControlador = 106;
String letrero[8] {
  "000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
  "011111011110001000001111011110100101111011110111100000111101111011110111101111101111010001000000110",
  "000100010010011000001000010010100101001010010000100000100001000010000100000010001001011001000001001",
  "000100011110101011101000011110100101111010010001001110111101111010000100000010001001011101011101001",
  "000100010000001000001011011000100101000010010000100000000101000010000100000010001001010111000001111",
  "000100010000001000001001010100100101000010010100100000000101000010000100000010001001010011000001001",
  "000100010000001000001111010010111101000011110011000000111101111011110111101111101111010001000001001",
  "000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
};


/* JUEGO  */
int U1 = 27, D1 = 29, U2 = 33, D2 = 35, S =  37;
//Paleta Izquierda
int CI1 = 0, CI2 = 1, CI3 = 2;
//Paleta Derecha
int CD1 = 0, CD2 = 1, CD3 = 2;
//Escoger posición de Inicio de la pelota
int lado;
int columna = 7;
int fila;
boolean juego = false;


void setup() {
  //Serial.begin(9600);
  inizializarMatrizDirecta();
  inicializarMatrizControlador();
  pinMode(UP, INPUT); // Botón Subir
  pinMode(DW, INPUT); // Botón Bajar
  pinMode(DIR, INPUT); // Botón Rapido/Lento
  randomSeed(8);
  randomSeed(3);
}

void loop() {
  if (juego == false) {

    //LETRERO
    //Cambio de Dirección
    if (digitalRead(DIR) == HIGH) {
      direccion = !direccion;
    }

    if (digitalRead(UP) == HIGH) {
      velocidadCartel -= 50;
      //Serial.println(velocidadCartel);
    }

    if (digitalRead(DW) == HIGH) {
      velocidadCartel += 50;
      //Serial.println(velocidadCartel);
    }

    delay(velocidadCartel);
    if (direccion == false) {
      moverCartelIZQ();
    } else  {
      moverCartelDCH();
    }
    //Hay que arreglar esto :c
    if (digitalRead(S) == HIGH) {
      unsigned long pulso;
      pulso = pulseInLong(S, HIGH, 6000000);
      if (pulso > 3000000) {
        juego = true;
      }
    }
  } else {
    inizializarMatrizDirecta();
    ledControl.clearDisplay(0);
    iniciarJuego();
  }

}

void inizializarMatrizDirecta() {
  for (int i = 0; i < 8; i++) {
    pinMode(columnas[i], OUTPUT);
  }
  for (int i = 0; i < 8; i++) {
    pinMode(filas[i], OUTPUT);
  }

  // Limpiar Matriz
  for (int i = 0; i < 8; i++) {
    digitalWrite(columnas[i], LOW);
  }
  for (int i = 0; i < 8; i++) {
    digitalWrite(filas[i], HIGH);
  }
}

void inicializarMatrizControlador() {
  ledControl.shutdown(0, false); // shutdown(# de dispositivo (indice), estado)
  ledControl.setIntensity(0, 15); // setIntensity(# de dispositivo (indice), intensidad de brillo del led de 0 a 15)
  ledControl.clearDisplay(0); // clearDisplay(# de dispositivo)
}

void encenderfilas(int valorColumna, int valor) {
  for (int valorFila = 0; valorFila < 8; valorFila++) {
    if (letrero[valorFila].charAt(valor) == '1') {
      ledControl.setLed(0, valorFila, valorColumna, true);
    } else {
      ledControl.setLed(0, valorFila, valorColumna, false);
    }
  }
}

void moverCartelIZQ() {
  for (posicionControlador; posicionControlador <= 98; posicionControlador++) {
    polarizar(posicionControlador - 8, posicionControlador - 1);

    encenderfilas(0, 0 + posicionControlador);
    encenderfilas(1, 1 + posicionControlador);
    encenderfilas(2, 2 + posicionControlador);
    encenderfilas(3, 3 + posicionControlador);
    encenderfilas(4, 4 + posicionControlador);
    encenderfilas(5, 5 + posicionControlador);
    encenderfilas(6, 6 + posicionControlador);
    encenderfilas(7, 7 + posicionControlador);

    if (posicionControlador == 98) {
      posicionControlador = -7;
    }

    posicionControlador++;
    return;
  }
}

void moverCartelDCH() {
  for (posicionControlador; posicionControlador >= -7; posicionControlador--) {
    polarizar (posicionControlador - 8, posicionControlador - 1);

    encenderfilas(0, 0 + posicionControlador);
    encenderfilas(1, 1 + posicionControlador);
    encenderfilas(2, 2 + posicionControlador);
    encenderfilas(3, 3 + posicionControlador);
    encenderfilas(4, 4 + posicionControlador);
    encenderfilas(5, 5 + posicionControlador);
    encenderfilas(6, 6 + posicionControlador);
    encenderfilas(7, 7 + posicionControlador);

    if (posicionControlador == -7) {
      posicionControlador = 106;
    }

    posicionControlador--;
    return;
  }
}

void polarizar(int inicio, int fin) {
  int aux = 0;
  for (int posFila = 0; posFila < 8; posFila++) {
    digitalWrite(filas[posFila], LOW);

    for (int j = inicio; j <= fin; j++) {
      if (letrero[posFila].charAt(j) == '1') {
        digitalWrite(columnas[aux], HIGH);
      } else {
        digitalWrite(columnas[aux], LOW);
      }
      aux++;
    }

    delay(1);
    digitalWrite(filas[posFila], HIGH);
    aux = 0;
  }
}

void iniciarJuego() {
  //Escoger posición de Inicio de la pelota
  lado = random(1, 3); // 1-izquierda, 2-derecha
  columna = 7; // No.columna
  fila = random(8); //No. Fila

  while (true) {
    paletaIzquierda();
    pelota();
    paletaDerecha();
  }
}

void paletaIzquierda() {

  digitalWrite(columnas[0], HIGH);
  digitalWrite(filas[CI1], LOW);
  digitalWrite(filas[CI2], LOW);
  digitalWrite(filas[CI3], LOW);
  delay(200);
  if (digitalRead(D1) == HIGH && CI3 < 7) {
    delay(300);
    digitalWrite(filas[CI1], HIGH);
    digitalWrite(filas[CI2], HIGH);
    digitalWrite(filas[CI3], HIGH);
    CI1++;
    CI2++;
    CI3++;
  }
  if (digitalRead(U1) == HIGH && CI1 > 0) {
    delay(300);
    digitalWrite(filas[CI1], HIGH);
    digitalWrite(filas[CI2], HIGH);
    digitalWrite(filas[CI3], HIGH);
    CI1--;
    CI2--;
    CI3--;
  }
  digitalWrite(columnas[0], LOW);
  digitalWrite(filas[CI1], HIGH);
  digitalWrite(filas[CI2], HIGH);
  digitalWrite(filas[CI3], HIGH);
}
void paletaDerecha() {
  ledControl.setLed(0, CD1, 7, true);
  ledControl.setLed(0, CD2, 7, true);
  ledControl.setLed(0, CD3, 7, true);
  //Control
  if (digitalRead(D2) == HIGH && CD3 < 7) {
    delay(200);
    ledControl.setLed(0, CD1, 7, false);
    CD1++;
    CD2++;
    CD3++;
  }
  if (digitalRead(U2) == HIGH && CD1 > 0) {
    delay(200);
    ledControl.setLed(0, CD3, 7, false);
    CD1--;
    CD2--;
    CD3--;
  }
}
void pelota() {
  if (lado == 1) {
    digitalWrite(columnas[columna], HIGH);
    digitalWrite(filas[fila], LOW);
    delay(200);
    digitalWrite(columnas[columna], LOW);
    digitalWrite(filas[fila], HIGH);
  } else {
    ledControl.setLed(0, fila, 0, true);
    delay(200);
    ledControl.setLed(0, fila, 0, false);
  }

}
