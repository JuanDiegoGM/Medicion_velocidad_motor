/****** Determinación de la velocidad de un motor, a través del Rotary encoder LPD3806-600BM-G5-24C ******/
// Adaptado de https://controlautomaticoeducacion.com/arduino/motor-dc-encoder/

// this library includes the ATOMIC_BLOCK macro.
#include <util/atomic.h>
#define ENCODER_A       2 // Verde
#define ENCODER_B       3 // Blanco

//Variable global de pulsos compartida con la interrupción
volatile int pulsos = 0;
unsigned long timeold;
float resolution = 600;

void setup(){
  Serial.begin(9600);
  //Encoders como entradas
  pinMode(ENCODER_A, INPUT_PULLUP);
  pinMode(ENCODER_B, INPUT_PULLUP);
  digitalWrite(ENCODER_A, HIGH);
  digitalWrite(ENCODER_B, HIGH);
  //Configurar Interrupción
  timeold = 0;
  attachInterrupt(digitalPinToInterrupt(ENCODER_A),leerEncoder,RISING);
}

void loop(){
  float rpm;
  int pulsos_aux;
  //Espera un segundo para el calculo de las RPM
  if (millis() - timeold >= 1000)
  {
    //Modifica las variables de la interrupción forma atómica
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE){
      rpm = float(pulsos * 60.0 / resolution); //RPM
      //rpm = float((60.0 * 1000.0 / resolution ) / (millis() - timeold) * pulsos);
      timeold = millis();
      pulsos_aux = pulsos;
      pulsos = 0;
    }
    Serial.print("PULSOS: ");
    Serial.println(pulsos_aux);
    Serial.print("RPM: ");
    Serial.println(rpm);
  }
  
}

//Función para la lectura del encoder
void leerEncoder(){
  //Lectura de Velocidad
  pulsos++; //Incrementa una revolución  
}
