/*
  Autor: Johan Esteban Higuita T.
  e - mail: higuitajohan@gmail.com
  Descripción: Calibración de los 15 sensores de flama instalados

  matrizFuego:

  | X     A3     2     3     X  |
  |                             |
  | 11    13    A4     8     9  |
  |                             |
  | X     A1    A5    10    X   |

*/

int matrizFuego[3][5];

void setup() {

  Serial.begin(9600);
  pinMode(0, OUTPUT);
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
  pinMode(A1, INPUT);
  pinMode(A5, INPUT);
  pinMode(A3, INPUT);
  pinMode(A4, INPUT);

  //inicializarMatriz();

}

void loop() {
  leerFuego(); //Actualiza los valores de la matriz fuego
  printMatrizFuego(); //Mostrar valores de la matrizFuego por serial
  delay(300);
}


void leerFuego() {
  //Fila 0:
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

void printMatrizFuego() {

  for (int i = 0; i < 3; i++) {
    Serial.print("              ");
    for (int j = 0; j < 5; j++) {
      Serial.print(matrizFuego[i][j]);
      Serial.print("      ");
    }
    Serial.println("");

  }
  Serial.println("________________________________________________________");
}



void inicializarMatriz() {
  matrizFuego[0][0] = 0;
  matrizFuego[0][1] = 1;
  matrizFuego[0][2] = 2;
  matrizFuego[0][3] = 3;
  matrizFuego[0][4] = 4;

  //Fila 1:
  matrizFuego[1][0] = 5;
  matrizFuego[1][1] = 6;
  matrizFuego[1][2] = 7;
  matrizFuego[1][3] = 8;
  matrizFuego[1][4] = 9;

  //Fila 2:
  matrizFuego[2][0] = 0;
  matrizFuego[2][1] = 1;
  matrizFuego[2][2] = 2;
  matrizFuego[2][3] = 3;
  matrizFuego[2][4] = 4;
}


