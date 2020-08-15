int U1 = 27;
int D1 = 29;
int U2 = 33;
int D2 = 35;
int S =  37;
int Sal = 41;


void setup() {
 pinMode(U1,INPUT); //Botón arriba Jugador 1
 pinMode(D1,INPUT); //Botón abajo Jugador 1 
 pinMode(U2,INPUT); //Botón arriba Jugador 2
 pinMode(D2,INPUT); //Botón abajo Jugador 2
 pinMode(S,INPUT); //Botón START
 pinMode(Sal,OUTPUT); //Botón START Indicador

 //COLUMNAS M1
  pinMode(0,OUTPUT);
  pinMode(1,OUTPUT);
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  //FILAS M1
  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT);
  pinMode(12,OUTPUT);
  pinMode(13,OUTPUT);
  pinMode(23,OUTPUT);
  pinMode(25,OUTPUT);
  
}

void loop() {
//3s para empezar Juego
unsigned long pulso;
pulso = pulseInLong(S, HIGH,6000000);
if(pulso > 3000000){
    digitalWrite(Sal,HIGH);
    iniciarJuego();
  }else{
    digitalWrite(Sal,LOW);
  }
}

void iniciarJuego(){
  int PI1 = 0;
  int PI2 = 1;
  int PI3 = 2;
  //Escoger posición de Inicio de la pelota
  int lado = random(1,3); // 1-izquierda, 2-derecha
  int columna = 25; // No.columna
  int fila = random(8); //No. Fila
  while(true){
     digitalWrite(0,HIGH);
     digitalWrite(1,HIGH);
     digitalWrite(2,HIGH);
     digitalWrite(3,HIGH);
     digitalWrite(4,HIGH);
     digitalWrite(5,HIGH);
     digitalWrite(6,HIGH);
     digitalWrite(7,HIGH);
    
    //PALETA
    digitalWrite(8,HIGH);
    digitalWrite(PI1,LOW);
    digitalWrite(PI2,LOW);
    digitalWrite(PI3,LOW);
    
    if(digitalRead(D1)==HIGH && PI3<7){
      delay(300);
      PI1++;
      PI2++;
      PI3++;
     }
    if(digitalRead(U1)==HIGH && PI1>0){
      delay(300);
      PI1--;
      PI2--;
      PI3--;
     }
    
    digitalWrite(8,LOW);
    digitalWrite(PI1,HIGH);
    digitalWrite(PI2,HIGH);
    digitalWrite(PI3,HIGH);
    //delay(1000);
    //PELOTA
    digitalWrite(columna,HIGH);
    digitalWrite(fila,LOW);
    //delay(1000);
    digitalWrite(columna,LOW);
    digitalWrite(fila,HIGH);
    //delay(1000);
    }
    columna--;
    fila++;
  
  }
