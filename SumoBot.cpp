#include <Arduino.h>
#include <Servo.h>

Servo servoIzq;
Servo servoDer;


int VALOR_ADELANTE_DER = 0;
int VALOR_ADELANTE_IZQ = 180;

int VALOR_ATRAS_DER = 180;
int VALOR_ATRAS_IZQ = 0;

int VALOR_DETENER = 90;

int SERVO_IZQ_PIN = 9;
int SERVO_DER_PIN = 10;

// sensores IR (infrarrojo)
const int sensorDer = 4;
const int sensorIzq = 5;
const int sensorAtras = 6;
int sensorStateDer = 0;
int sensorStateIzq = 0;
int sensorStateAtras = 0;

// sensor ultrasonido
int sensorUltrasonido = 3;
unsigned long time;
unsigned long sizeofpulse;

float dist;

void atacar() {
	servoIzq.write(120);
	servoDer.write(60);
}


void adelante() {
	servoIzq.write(VALOR_ADELANTE_IZQ);
	servoDer.write(VALOR_ADELANTE_DER);
}

void detener() {
	servoIzq.write(VALOR_DETENER);
	servoDer.write(VALOR_DETENER);
}

void atras() {
	servoIzq.write(VALOR_ATRAS_IZQ);
	servoDer.write(VALOR_ATRAS_DER);
}

void izquierda() {
//	servoIzq.write(VALOR_ATRAS_IZQ);
//	servoDer.write(VALOR_ADELANTE_DER);
	servoIzq.write(100);
	servoDer.write(100);
}

void girar() {
	servoIzq.write(97);
	servoDer.write(85);
}


void derecha() {
	servoIzq.write(VALOR_ADELANTE_IZQ);
	servoDer.write(VALOR_ATRAS_DER);
}

// Sensores
float medirDistancia() {
	float cm;
	pinMode(sensorUltrasonido, OUTPUT);
	digitalWrite(sensorUltrasonido, LOW);
	delayMicroseconds(25);
	digitalWrite(sensorUltrasonido, HIGH);
	time = micros();
	pinMode(sensorUltrasonido, INPUT);
	sizeofpulse = pulseIn(sensorUltrasonido, LOW, 18000);
	time = micros() - time - sizeofpulse;
	cm = (time * 340.29 / 2 / 10000) - 3;
	return cm;
}

void setup() {
	Serial.begin(115200);
	Serial.println("SUMOBOT SETUP");

	// sensores IR
	pinMode(sensorDer, INPUT);
	pinMode(sensorIzq, INPUT);
	pinMode(sensorAtras, INPUT);

	// sensor ultrasonido
	pinMode(sensorUltrasonido, OUTPUT);
	digitalWrite(sensorUltrasonido, HIGH);

	// motores
	servoIzq.attach(SERVO_IZQ_PIN);
	servoDer.attach(SERVO_DER_PIN);

	// esperar 5 seg
	delay(5000);
}


void loop() {
	Serial.println("SUMOBOT LOOP");

	izquierda();
	delay(100);

//	dist = medirDistancia();

	sensorStateDer = digitalRead(sensorDer);
//	if (dist < 40.0) {
	if (sensorStateDer == LOW) {
		Serial.println("enemigo detectado atacar!!");
		adelante();
		delay(600);
		detener();
	}

	delay(100);

	// sensores Ir/Der

	sensorStateIzq = digitalRead(sensorIzq);

	if (sensorStateIzq == LOW) {
		Serial.println("estoy por salir retrocedo!! :(");
		atras();
		delay(600);
	}
	delay(100);

	sensorStateAtras = digitalRead(sensorAtras);
	// sensores Ir
	if (sensorStateAtras == LOW) {
		Serial.println("estoy por salir (atras) me adelanto!! :(");
		adelante();
		delay(600);
	}
	delay(100);
}

