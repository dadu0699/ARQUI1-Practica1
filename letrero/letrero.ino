#include "LedControl.h"
LedControl ledControl = LedControl(51, 53, 49, 1); // LedControl(DIN, CLK, CS / LOAD, # de dispositivos (cantidad de modulos) de 1 a 8)

int filas[] = {0, 1, 2, 3, 4, 5, 6, 7}; // filas encienden con 0
int columnas[] = {8, 9, 10, 11, 12, 13, 23, 25}; // columnas encienden con 1

void setup() {
  inizializarMatrizDirecta();
  inicializarMatrizControlador();
}

void loop() {
  moverCartelIZQ();
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

String letrero[8] {
  "00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
  "01111101111000100000111101111010010111101111011110000011110111101111011110111110111101000100000011000000",
  "00010001001001100000100001001010010100101001000010000010000100001000010000001000100101100100000100100000",
  "00010001111010101110100001111010010111101001000100111011110111101000010000001000100101110101110100100000",
  "00010001000000100000101101100010010100001001000010000000010100001000010000001000100101011100000111100000",
  "00010001000000100000100101010010010100001001010010000000010100001000010000001000100101001100000100100000",
  "00010001000000100000111101001011110100001111001100000011110111101111011110111110111101000100000100100000",
  "00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
};

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
  for (int i = 0; i <= 103; i++) {
    encenderfilas(0, 0 + i);
    encenderfilas(1, 1 + i);
    encenderfilas(2, 2 + i);
    encenderfilas(3, 3 + i);
    encenderfilas(4, 4 + i);
    encenderfilas(5, 5 + i);
    encenderfilas(6, 6 + i);
    encenderfilas(7, 7 + i);
    delay(250);
    ledControl.clearDisplay(0);
    delay(25);
  }
}
