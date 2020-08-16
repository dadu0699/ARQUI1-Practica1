#include "LedControl.h"
LedControl ledControl = LedControl(51, 53, 49, 1); // LedControl(DIN, CLK, CS / LOAD, # de dispositivos (cantidad de modulos) de 1 a 8)

int filas[] = {24, 22, 2, 3, 4, 5, 6, 7}; // filas encienden con 0
int columnas[] = {8, 9, 10, 11, 12, 13, 23, 25}; // columnas encienden con 1

/*  LETRERO */
int UP = 52, DW = 50, DIR = 48;
boolean direccion = true;
int velocidadCartel = 250;
int posicionControlador = 8;
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

void setup() {
  //Serial.begin(9600);
  inizializarMatrizDirecta();
  inicializarMatrizControlador();
  pinMode(UP, INPUT); // Botón Subir
  pinMode(DW, INPUT); // Botón Bajar
  pinMode(DIR, INPUT); // Botón Rapido/Lento
}

void loop() {
  if (digitalRead(DIR) == HIGH) {
    direccion = !direccion;
  }

  if (digitalRead(UP) == HIGH){
    velocidadCartel -= 50;
    //Serial.println(velocidadCartel);
  }

   if (digitalRead(DW) == HIGH){
    velocidadCartel += 50;
    //Serial.println(velocidadCartel);
  }

  delay(velocidadCartel);
  if (direccion == true) {
    moverCartelIZQ();
  } else  {
    moverCartelDCH();
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
    encenderfilas(0, 0 + posicionControlador);
    encenderfilas(1, 1 + posicionControlador);
    encenderfilas(2, 2 + posicionControlador);
    encenderfilas(3, 3 + posicionControlador);
    encenderfilas(4, 4 + posicionControlador);
    encenderfilas(5, 5 + posicionControlador);
    encenderfilas(6, 6 + posicionControlador);
    encenderfilas(7, 7 + posicionControlador);

    if (posicionControlador == -7) {
      posicionControlador = 98;
    }

    posicionControlador--;
    return;
  }
}
