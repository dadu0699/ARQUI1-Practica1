#include "LedControl.h"
LedControl ledControl = LedControl(11, 13, 10, 1); // LedControl(DIN, CLK, CS / LOAD, # de dispositivos (cantidad de modulos) de 1 a 8)

#define retraso 750 // Lapso de espera

int filas[] = {0, 1, 2, 3, 4, 5, 6, 7}; // filas encienden con 0
int columnas[] = {8, 9, 10, 11, 12, 13, 14, 15}; // columnas encienden con 1

byte puntuacion[5][8] {
  {
    B00000000,
    B00011000,
    B00100100,
    B00100100,
    B00100100,
    B00100100,
    B00011000,
    B00000000
  },
  {
    B00000000,
    B00001100,
    B00010100,
    B00100100,
    B00000100,
    B00000100,
    B00000100,
    B00000000
  },
  {
    B00000000,
    B00011000,
    B00100100,
    B00000100,
    B00001000,
    B00010000,
    B00111100,
    B00000000
  },
  {
    B00000000,
    B00111100,
    B00000100,
    B00001000,
    B00000100,
    B00100100,
    B00011000,
    B00000000
  },
  {
    B00000000,
    B00001100,
    B00010100,
    B00100100,
    B00111110,
    B00000100,
    B00000100,
    B00000000
  }
};

void setup() {
  // inizializarMatrizDirecta();
  inicializarMatrizControlador();
  /*
    digitalWrite(columnas[0], HIGH);
    digitalWrite(filas[0], LOW);
    digitalWrite(filas[1], LOW);
    digitalWrite(columnas[2], HIGH);
  */
}

void loop() {
  for (int i = 0; i < 5; i++) {
    mostrarPunteoControlador(i);
    delay(retraso);
  }
}

void inizializarMatrizDirecta() {
  for (int i = 0; i <= 8; i++) {
    pinMode(columnas[i], OUTPUT);
  }
  for (int i = 0; i <= 8; i++) {
    pinMode(filas[i], OUTPUT);
  }

  // Limpiar Matriz
  for (int i = 0; i <= 8; i++) {
    digitalWrite(columnas[i], LOW);
  }
  for (int i = 0; i <= 8; i++) {
    digitalWrite(filas[i], HIGH);
  }
}

void inicializarMatrizControlador() {
  ledControl.shutdown(0, false); // shutdown(# de dispositivo (indice), estado)
  ledControl.setIntensity(0, 15); // setIntensity(# de dispositivo (indice), intensidad de brillo del led de 0 a 15)
  ledControl.clearDisplay(0); // clearDisplay(# de dispositivo)
}

void mostrarPunteoControlador(int punteo) {
  for (int i = 0; i < 8; i++) {
    ledControl.setRow(0, i, puntuacion[punteo][i]); // setRow(# de dispositivo, # fila, contenido)
  }
}
