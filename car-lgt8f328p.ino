#include <IRremote.hpp>

/* define IR sensor pin */
#define  IRsensorPin 13

/* define functions used by the library 
IRrecv irrecv(IRsensorPin);
decode_IrReceiver IrReceiver;*/

/* define L298N motor drive control pins */
int MainMotorLeftD0 = 2;   // IN1
int MainMotorLeftD1 = 3;   // IN2
int MainMotorRightD0 = 4;  // IN3
int MainMotorRightD1 = 5;  // IN4
int smokePin = 6;
int LedFrontPin = 7;
int LedBackPin = 8;
int SubMotorFrontD0 = 9;
int SubMotorFrontD1 = 10;
int SubMotorBackD0 = 11;
int SubMotorBackD1 = 12;



void setup() {

  /* initialize motor control pins as output */
  pinMode(MainMotorRightD0, OUTPUT);
  pinMode(MainMotorLeftD0, OUTPUT);
  pinMode(MainMotorRightD1, OUTPUT);
  pinMode(MainMotorLeftD1, OUTPUT);
  pinMode(smokePin, OUTPUT);
  pinMode(LedFrontPin, OUTPUT);
  pinMode(LedBackPin, OUTPUT);
  pinMode(SubMotorFrontD0, OUTPUT);
  pinMode(SubMotorFrontD1, OUTPUT);
  pinMode(SubMotorBackD0, OUTPUT);
  pinMode(SubMotorBackD1, OUTPUT);


  /* start serial communication to see hex codes */
  Serial.begin(9600);
  IrReceiver.begin(IRsensorPin,ENABLE_LED_FEEDBACK);
}

void loop() {

  /* if the sensor receives any signal */
  if (IrReceiver.decode()) {

    /* print hex code value on the serial monitor */
    Serial.println(IrReceiver.decodedIRData.decodedRawData,HEX);
    delay(5);

    /* resume function according to hex code */
    IrReceiver.resume();
  }

  /* if the incoming data is "defined hex code" then run the motors functions */
  /* instead of zeros "0000", write the hex codes of your remote control */
  if (IrReceiver.decodedIRData.decodedRawData == 0000) MotorForward();
  if (IrReceiver.decodedIRData.decodedRawData == 0000) MotorBackward();
  if (IrReceiver.decodedIRData.decodedRawData == 0000) TurnRight();
  if (IrReceiver.decodedIRData.decodedRawData == 0000) TurnLeft();
  if (IrReceiver.decodedIRData.decodedRawData == 0000) MotorStop();
  if (IrReceiver.decodedIRData.decodedRawData == 0000) LedFront();
  if (IrReceiver.decodedIRData.decodedRawData == 0000) LedBack();
  if (IrReceiver.decodedIRData.decodedRawData == 0000) Smoke();
  if (IrReceiver.decodedIRData.decodedRawData == 0000) SubForward();
  if (IrReceiver.decodedIRData.decodedRawData == 0000) SubBACKWARD();
  if (IrReceiver.decodedIRData.decodedRawData == 0000) SubFrontForwardOnly();
  if (IrReceiver.decodedIRData.decodedRawData == 0000) SubFrontBackwardOnly();
  if (IrReceiver.decodedIRData.decodedRawData == 0000) SubBackForwardOnly();
  if (IrReceiver.decodedIRData.decodedRawData == 0000) SubBackBAackwardOnly();
  if (IrReceiver.decodedIRData.decodedRawData == 0000) SubStop();
}


void MotorForward() {
  digitalWrite(MainMotorRightD0, HIGH);
  digitalWrite(MainMotorLeftD0, HIGH);
  digitalWrite(MainMotorRightD1, LOW);
  digitalWrite(MainMotorLeftD1, LOW);
}

/* BACKWARD */
void MotorBackward() {
  digitalWrite(MainMotorRightD1, HIGH);
  digitalWrite(MainMotorLeftD1, HIGH);
  digitalWrite(MainMotorRightD0, LOW);
  digitalWrite(MainMotorLeftD0, LOW);
}

/* TURN RIGHT */
void TurnRight() {
  digitalWrite(MainMotorRightD0, HIGH);
  digitalWrite(MainMotorLeftD0, LOW);
  digitalWrite(MainMotorRightD1, LOW);
  digitalWrite(MainMotorLeftD1, HIGH);
}

/* TURN LEFT */
void TurnLeft() {
  digitalWrite(MainMotorLeftD0, HIGH);
  digitalWrite(MainMotorRightD0, LOW);
  digitalWrite(MainMotorRightD1, HIGH);
  digitalWrite(MainMotorLeftD1, LOW);
}

/* STOP */
void MotorStop() {
  digitalWrite(MainMotorRightD1, LOW);
  digitalWrite(MainMotorLeftD1, LOW);
  digitalWrite(MainMotorRightD0, LOW);
  digitalWrite(MainMotorLeftD0, LOW);
}
void LedFront() {
  digitalWrite(LedFrontPin, !digitalRead(LedFrontPin));
}
void LedBack() {
  digitalWrite(LedBackPin, !digitalRead(LedBackPin));
}
void Smoke() {
  digitalWrite(smokePin, !digitalRead(smokePin));
}

void SubForward() {
  digitalWrite(SubMotorFrontD0, HIGH);
  digitalWrite(SubMotorBackD0, HIGH);
  digitalWrite(SubMotorFrontD1, LOW);
  digitalWrite(SubMotorBackD1, LOW);
}

/* BACKWARD */
void SubBACKWARD() {
  digitalWrite(SubMotorBackD1, HIGH);
  digitalWrite(SubMotorFrontD1, HIGH);
  digitalWrite(SubMotorBackD0, LOW);
  digitalWrite(SubMotorFrontD0, LOW);
}

/* TURN RIGHT */
void SubFrontForwardOnly() {
  digitalWrite(SubMotorFrontD0, HIGH);
  digitalWrite(SubMotorFrontD1, LOW);
  digitalWrite(SubMotorBackD0, LOW);
  digitalWrite(SubMotorBackD1, LOW);
} /* TURN RIGHT */
void SubFrontBackwardOnly() {
  digitalWrite(SubMotorFrontD1, HIGH);
  digitalWrite(SubMotorFrontD0, LOW);
  digitalWrite(SubMotorBackD0, LOW);
  digitalWrite(SubMotorBackD1, LOW);
}
/* TURN LEFT */
void SubBackForwardOnly() {
  digitalWrite(SubMotorFrontD0, LOW);
  digitalWrite(SubMotorFrontD1, LOW);
  digitalWrite(SubMotorBackD0, HIGH);
  digitalWrite(SubMotorBackD1, LOW);
} /* TURN LEFT */
void SubBackBAackwardOnly() {
  digitalWrite(SubMotorFrontD0, LOW);
  digitalWrite(SubMotorFrontD1, LOW);
  digitalWrite(SubMotorBackD0, LOW);
  digitalWrite(SubMotorBackD1, HIGH);
}

/* STOP */
void SubStop() {
  digitalWrite(SubMotorBackD0, LOW);
  digitalWrite(SubMotorFrontD1, LOW);
  digitalWrite(SubMotorBackD1, LOW);
  digitalWrite(SubMotorFrontD0, LOW);
}
