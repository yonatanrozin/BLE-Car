const serviceUUID = "8da4f63e-a937-47ba-9b68-a162b44e6a01";


let myBLE;
let myCharacteristic;

let isConnected = false;

function setup() {
  myBLE = new p5ble();
  let onBluefy = navigator.userAgent.includes("Bluefy");
  let BLEButton = document.getElementById("BLEButton");
  if (!onBluefy) {
    BLEButton.disabled = true;
    BLEButton.style.fontSize = "20px";
    BLEButton.innerHTML = "Controller must be launched on Bluefy browser."
  } else {
    BLEButton.innerHTML = "Connect to BLE"
  }
}

function sendVal(buttonNum) {
  myBLE.write(myCharacteristic, buttonNum)
}

function BLEConnect() {
  console.log("Attempting to connect to BLE...")
  myBLE.connect(serviceUUID, BLEConnected);
}

function BLEConnected(error, characteristics) {
  if (error) console.log('error: ', error);
  console.log('characteristics: ', characteristics);
  // Set the first characteristic as myCharacteristic
  myCharacteristic = characteristics[0];
  enableButtons();
}

function enableButtons() {
  let buttons = document.getElementsByTagName("button");
  for (let b = 0; b < buttons.length; b++) {
    buttons[b].disabled = false;
  }
}

window.addEventListener('DOMContentLoaded', setup);
