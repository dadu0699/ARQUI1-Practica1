#include "LedControl.h"

// LedControl(DIN, CLK, CS / LOAD, # de dispositivos (cantidad de modulos) de 1 a 8)
LedControl ledControl = LedControl(11, 13, 10, 1);

#define retraso 1000

// Punteos
byte cero[8] {
  B00000000,
  B00011000,
  B00100100,
  B00100100,
  B00100100,
  B00100100,
  B00011000,
  B00000000
};

byte uno[8] {
  B00000000,
  B00001100,
  B00010100,
  B00100100,
  B00000100,
  B00000100,
  B00000100,
  B00000000
};

byte dos[8] {
  B00000000,
  B00011000,
  B00100100,
  B00000100,
  B00001000,
  B00010000,
  B00111100,
  B00000000
};

byte tres[8] {
  B00000000,
  B00111100,
  B00000100,
  B00001000,
  B00000100,
  B00100100,
  B00011000,
  B00000000
};

byte cuatro[8] {
  B00000000,
  B00001100,
  B00010100,
  B00100100,
  B00111110,
  B00000100,
  B00000100,
  B00000000
};

void setup() {
  // shutdown(# de dispositivo (indice), estado)
  ledControl.shutdown(0, false);
  // setIntensity(# de dispositivo (indice), intensidad de brillo del led de 0 a 15)
  ledControl.setIntensity(0, 15);
  // clearDisplay(# de dispositivo)
  ledControl.clearDisplay(0);
}

void loop() {
  mostrar_ceroControlador();
  delay(retraso);
  mostrar_unoControlador();
  delay(retraso);
  mostrar_dosControlador();
  delay(retraso);
  mostrar_tresControlador();
  delay(retraso);
  mostrar_cuatroControlador();
  delay(retraso);
}

void mostrar_ceroControlador() {
  for (int i = 0; i < 8; i++) {
    // setRow(# de dispositivo, # fila, contenido)
    ledControl.setRow(0, i, cero[i]);
  }
}

void mostrar_unoControlador() {
  for (int i = 0; i < 8; i++) {
    // setRow(# de dispositivo, # fila, contenido)
    ledControl.setRow(0, i, uno[i]);
  }
}

void mostrar_dosControlador() {
  for (int i = 0; i < 8; i++) {
    // setRow(# de dispositivo, # fila, contenido)
    ledControl.setRow(0, i, dos[i]);
  }
}

void mostrar_tresControlador() {
  for (int i = 0; i < 8; i++) {
    // setRow(# de dispositivo, # fila, contenido)
    ledControl.setRow(0, i, tres[i]);
  }
}

void mostrar_cuatroControlador() {
  for (int i = 0; i < 8; i++) {
    // setRow(# de dispositivo, # fila, contenido)
    ledControl.setRow(0, i, cuatro[i]);
  }
}
