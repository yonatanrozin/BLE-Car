#include <ArduinoBLE.h>
#include <Adafruit_SSD1327.h>
#include <qrcode.h>

#define serviceUUID "8da4f63e-a937-47ba-9b68-a162b44e6a01"
#define charUUID "9da4f63e-a937-47ba-9b68-a162b44e6a01"

#define AI1 12 
#define AI2 11
#define BI1 10
#define BI2 9
#define pwmA A7
#define pwmB A6
#define stdby 4

Adafruit_SSD1327 display(128, 128, &Wire, -1, 1000000);

BLEService moveCar(serviceUUID);
BLEIntCharacteristic dir(charUUID, BLERead | BLEWrite);

void setup() {
  Serial.begin(9600);
  display.begin();
  display.clearDisplay();
  display.display();


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

  displayQRCode("bleCar.glitch.me");

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

void displayQRCode(String message) {
  Serial.print("Message length: ");
  Serial.println(message.length());

  // Create the QR code
  QRCode qrcode;
  // See table at https://github.com/ricmoo/QRCode
  // or https://www.qrcode.com/en/about/version.html for
  // calculation of data capacity of a QR code. Current
  // settings will support a string of about 100 bytes:
  int qrVersion = 3;
  // can be ECC_LOW, ECC_MEDIUM, ECC_QUARTILE and ECC_HIGH (0-3, respectively):
  int qrErrorLevel = ECC_HIGH;

  // allocate QR code memory:
  byte qrcodeBytes[qrcode_getBufferSize(qrVersion)];
  qrcode_initText(&qrcode, qrcodeBytes, qrVersion, qrErrorLevel, message.c_str());

  // QR Code block characteristics will depend on the display:
  // QR code needs a "quiet zone" of background color around it, hence the offset:
  int offset = 1;
  int blockSize = (display.height() - (offset * 2)) / qrcode.size;
  // fill with the background color:

  // read the bytes of the QR code and set the blocks light or dark, accordingly:
  // vertical loop:
  for (byte y = 0; y < qrcode.size; y++) {
    // horizontal loop:
    for (byte x = 0; x < qrcode.size; x++) {
      // caculate the block's X and Y positions:
      int blockX = (x * blockSize) + offset;
      int blockY = (y * blockSize) + offset;
      // read the block value from the QRcode:
      int blockValue = qrcode_getModule(&qrcode, x, y);
      // set the default block color:
      int blockColor = SSD1327_BLACK;
      // if the block value is 1, set color to foreground color instead:
      if (blockValue == 1) {
        blockColor = SSD1327_WHITE;
      }
      // display the block on the screen:
      display.fillRect(blockX, blockY, blockSize, blockSize, blockColor);
    }
  }
  // print the message and display it:
  Serial.println(message);
  display.display();
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
