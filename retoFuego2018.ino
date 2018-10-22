/*
  Autor: Johan Esteban Higuita T.
  e-mail: higuitajohan@gmail.com
  Descripción: Calibración de los sensores de flama instalados

  Pines matrizFuego:


  | X     A3     2     3     X  |
  |                             |
  | 11    13    A4     8     9  |
  |                             |
  | X     A1    A5    10     X  |

*/

int matrizFuego[3][5];
int umbral = 850; //blanco-negro
int dist_obstaculo = 10;
int dist;
int contV = 0; //contador de intentos de activar el ventilador
void setup() {

  //Entradas digitales para los sensores de flama:
  
  pinMode(1, INPUT);
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(8, INPUT);
  pinMode(9, INPUT);
  pinMode(10, INPUT);
  pinMode(11, INPUT);
  pinMode(12, INPUT);
  pinMode(13, INPUT);
  pinMode(A5, INPUT);
  pinMode(A2, INPUT);
  pinMode(A4, INPUT);
  //Pin de salida a la otra tarjeta que activa el ventilador
  pinMode(0, OUTPUT);

  motorSpeed(M1 , 54);
  motorSpeed(M2 , 51);
  //Avanzar a la primera vela:
  goForward(M1 , M2);
  delay(6000);
  motorsOff(M1 , M2);

}

void loop() {
  leerFuego(); //Actualizar matriz de fuego

  if (hayFuego()) {
    centrarFuego();
    goForward(M1 , M2);
    if (sensorRead(J1) > umbral) { //sí lee blanco
      motorsOff(M1 , M2);
      leerFuego();
      while (hayFuego() && contV < 4) { // sí en 4 intentos no ha apagado la vela, vuelve a la pista
        activarVentilador();
        leerFuego();
        contV++;
      }
      contV = 0; //reiniciar contador
      rebotar();
    }
  } else {

    goForward(M1 , M2);
    dist = ultrasoundRead(J3);
    //Rebotar obstáculos:
    if ( dist < dist_obstaculo || sensorRead(J1) > umbral) { //obstáculo o linea blanca
      rebotar();
    }

  }
}



/*********************************************************** Funciones: ********************************************************************/



void leerFuego() {
  matrizFuego[0][0] = 0;//No conectado
  matrizFuego[0][1] = digitalRead(A3);
  matrizFuego[0][2] = digitalRead(2);
  matrizFuego[0][3] = digitalRead(3);
  matrizFuego[0][4] = 0; //No conectado
  //Fila 1:
  matrizFuego[1][0] = digitalRead(11);
  matrizFuego[1][1] = digitalRead(13);
  matrizFuego[1][2] = digitalRead(A4);
  matrizFuego[1][3] = digitalRead(8);
  matrizFuego[1][4] = digitalRead(9);
  //Fila 2:
  matrizFuego[2][0] = 0;//No conectado
  matrizFuego[2][1] = digitalRead(A1);
  matrizFuego[2][2] = digitalRead(A5);
  matrizFuego[2][3] = digitalRead(10);
  matrizFuego[2][4] = 0; //No conectado
}

boolean hayFuego() {
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 5; j++) {
      if (matrizFuego[i][j]) {
        return true; //encontró un 1 en la matriz
      }
    }
  }
  return false; //no encontró almenos un 1 en la matriz

}

void centrarFuego() {
  boolean fuego_centro = matrizFuego[0][2] || matrizFuego[1][2] || matrizFuego[2][2]; //posiciones centrales de la matriz
  boolean fuego_izq = matrizFuego[0][0] || matrizFuego[0][1] || matrizFuego[1][0] || matrizFuego[1][1] || matrizFuego[2][0] || matrizFuego[2][1]; //posiciones del lado izquierda
  boolean fuego_der = matrizFuego[0][3] || matrizFuego[0][4] || matrizFuego[1][3] || matrizFuego[1][4] || matrizFuego[2][3] || matrizFuego[2][4]; //posiciones del lado derechp

  if ((fuego_centro && !fuego_der && !fuego_izq) || (fuego_centro && fuego_der && fuego_izq)) { //Fuego solo en el centro o, en el centro y ambos lados
    //goForward(M1 , M2);
  } else {

    //fuego en la derecha
    while (fuego_der) {
      turnRight(M2 , M1);
      delay(50);
      //actualizar valores para evitar ciclo infinito
      leerFuego();
      fuego_centro = matrizFuego[0][2] || matrizFuego[1][2] || matrizFuego[2][2];
      fuego_izq = matrizFuego[0][0] || matrizFuego[0][1] || matrizFuego[1][0] || matrizFuego[1][1] || matrizFuego[2][0] || matrizFuego[2][1];
      fuego_der = matrizFuego[0][3] || matrizFuego[0][4] || matrizFuego[1][3] || matrizFuego[1][4] || matrizFuego[2][3] || matrizFuego[2][4];
      //verificar si lee centro y girar con base a ello

    }

    //fuego en la izquierda
    while (fuego_izq) {
      turnLeft(M2 , M1);
      delay(50);
      //actualizar valores para evitar ciclo infinito
      leerFuego();
      fuego_centro = matrizFuego[0][2] || matrizFuego[1][2] || matrizFuego[2][2];
      fuego_izq = matrizFuego[0][0] || matrizFuego[0][1] || matrizFuego[1][0] || matrizFuego[1][1] || matrizFuego[2][0] || matrizFuego[2][1];
      fuego_der = matrizFuego[0][3] || matrizFuego[0][4] || matrizFuego[1][3] || matrizFuego[1][4] || matrizFuego[2][3] || matrizFuego[2][4];
      //verificar si lee centro y girar con base a ello
    }
  }

}


void inicializarMatriz() { //inciar la matriz de fuego (para Pruebas)
  matrizFuego[0][0] = 0;
  matrizFuego[0][1] = 0;
  matrizFuego[0][2] = 0;
  matrizFuego[0][3] = 0;
  matrizFuego[0][4] = 0;

  //Fila 1:
  matrizFuego[1][0] = 0;
  matrizFuego[1][1] = 0;
  matrizFuego[1][2] = 0;
  matrizFuego[1][3] = 0;
  matrizFuego[1][4] = 0;

  //Fila 2:
  matrizFuego[2][0] = 0;
  matrizFuego[2][1] = 0;
  matrizFuego[2][2] = 0;
  matrizFuego[2][3] = 0;
  matrizFuego[2][4] = 0;
}

void activarVentilador() {
  digitalWrite(0, HIGH); //Envía un 1 a la otra tarjeta para que active el motor del ventilador
  delay(2000);
  digitalWrite(0, LOW);
}

void rebotar() {
  goReverse(M1 , M2);
  delay(400);
  byte giro;
  giro = random(0, 2);//para que el giro sea aleatorio
  if (giro == 0) {
    turnRight(M2 , M1);
  } else {
    turnLeft(M2 , M1);
  }
  delay(600);//tiempo de giro
}


