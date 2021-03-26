#include <ArduinoBLE.h>


#define serviceUUID "8da4f63e-a937-47ba-9b68-a162b44e6a01"
#define charUUID "9da4f63e-a937-47ba-9b68-a162b44e6a01"

#define AI1 12 
#define AI2 11
#define BI1 10
#define BI2 9
#define pwmA A7
#define pwmB A6
#define stdby 4


BLEService moveCar(serviceUUID);
BLEIntCharacteristic dir(charUUID, BLERead | BLEWrite);

void setup() {
  Serial.begin(9600);



  pinMode(AI1, OUTPUT);
  pinMode(AI2, OUTPUT);
  pinMode(BI1, OUTPUT);
  pinMode(BI2, OUTPUT);
  
  pinMode(stdby, OUTPUT);
  
  pinMode(pwmB, OUTPUT);
  pinMode(pwmA, OUTPUT);
  
  analogWrite(pwmA, 255);
  analogWrite(pwmB, 255);
  digitalWrite(stdby, HIGH);


  
  while (!BLE.begin()) {
    Serial.println("Error initializing BLE...");
    delay(3000);
  }
  BLE.setLocalName("Yony's RC Car");
  BLE.setAdvertisedService(moveCar);
  moveCar.addCharacteristic(dir);
  BLE.addService(moveCar);
  dir.writeValue(0);
  BLE.advertise();



}

bool centralConnected = false;

void loop() {
  BLEDevice central = BLE.central();
  if (central && !centralConnected) {
    Serial.print("Connected to central: ");
    Serial.println(central.address());
    centralConnected = true;
  } else if (!central && centralConnected) {
    Serial.println("Disconnected from central.");
    centralConnected = false;
  }
  if (central.connected() && central) {
    if (dir.written()) {
      driveCar(dir.value());
      Serial.println(dir.value());
    }
  }
  
}


void driveCar(int dirNum) {
  switch (dirNum) {
    case 0:
      carStop();
      break;
    case 1:
      carForward();
      break;
    case 2:
      carBack();
      break;
    case 3:
      carLeft();
      break;
    case 4:
      carRight();
      break;
  }
}

void carBack() {
  digitalWrite(AI1, HIGH);
  digitalWrite(AI2, LOW);
  digitalWrite(BI1, HIGH);
  digitalWrite(BI2, LOW);
}

void carForward() {
  digitalWrite(AI1, LOW);
  digitalWrite(AI2, HIGH);
  digitalWrite(BI1, LOW);
  digitalWrite(BI2, HIGH);
}

void carRight() {
  digitalWrite(AI1, HIGH);
  digitalWrite(AI2, LOW);
  digitalWrite(BI1, LOW);
  digitalWrite(BI2, HIGH);
}

void carLeft() {
  digitalWrite(AI1, LOW);
  digitalWrite(AI2, HIGH);
  digitalWrite(BI1, HIGH);
  digitalWrite(BI2, LOW);
}

void carStop() {
  digitalWrite(AI1, LOW);
  digitalWrite(AI2, LOW);
  digitalWrite(BI1, LOW);
  digitalWrite(BI2, LOW);
}
