/*Determinación de la velocidad de un motor*/
/*Código adaptado por: Juan Diego Elvis García Munayco*/
/*Fecha: Enero 2023*/

#include <Arduino.h>

#define ENCODER_A 2
#define ENCODER_B 3

void leerEncoder();

// Declaración de variables globales
volatile int pulsos = 0;
unsigned long tiempo_reg;
float resolution = 17*49;   // PPR

void setup() {
    Serial.begin(9600);
    pinMode(ENCODER_A, INPUT);
    pinMode(ENCODER_B, INPUT);
    tiempo_reg = 0;
    attachInterrupt(digitalPinToInterrupt(ENCODER_A), leerEncoder, RISING);
}

void loop() {
    float rpm;    
    if (millis()-tiempo_reg >= 1000){   // Cada segundo se realizará el cálculo de las rpm
        rpm = float((1000.0/(millis()-tiempo_reg)) * (pulsos/resolution) * 60.0);
        Serial.print("Pulsos: ");
        Serial.println(pulsos);
        Serial.print("RPM: ");
        Serial.println(rpm);
        tiempo_reg = millis();
        pulsos = 0;
    }
}

// Función que suma los pulsos detectados en una revolución, 
// cada vez que se detecte un flanco de subida en el ENCODER_A
void leerEncoder(){
    pulsos++;
}

/****** Adaptado de https://controlautomaticoeducacion.com/arduino/motor-dc-encoder/ ******/