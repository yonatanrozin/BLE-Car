# BLE-Car Prototype
A remote-controlled car operated through Bluetooth LE on an HTML page.
Please visit [my blog](https://wp.nyu.edu/yonatanrozin/ble-car/) for an in-depth look at the programming process!

## Introduction

BLE Car was created as my midterm assignment for my device networking class, whose guidelines can be found [here](https://itp.nyu.edu/classes/connected-devices/syllabus-spring-2021/assignments-spring-2021/#Device-to-Device_Communication). The project must receive user input and communicate it to another device through a wireless protocol.

I decided to revisit my [Space-Mapper Car](https://github.com/yonatanrozin/Space-Mapper-Car) project from last semester, as I regrettably had to abandon the wireless Bluetooth LE controls I had initially planned for that projec for the sake of time. This midterm assignment was a perfect opportunity to finally outfit the car from last semester with the wireless BLE controls it deserves. For the sake of focusing on the aspects of the project that are the most relevant to the topics of the course, I've decided not to revive the space-mapping functionality of the original car, and just focus on the wireless controls for now, though I absolutely intend on combining the two features in the near future.

The car uses an Arduino Nano 33 IoT, which has BLE peripheral functionality built in. The device has a single characteristic for the direction of the car, which will have 5 possible values: one for each direction and one to stop the car. The central device will be an HTML page hosted on [Glitch](https://glitch.com/) that will contain the controller GUI, comprised of buttons that write to the direction characteristic automatically.

The main benefit to these wireless controls, as opposed to the wired serial connection of its predecessor, is that the functionality of the remote controlled car is significantly improved, or rather it is no longer severely impeded as it was before. Since there is no longer a bulky cable tethering the car to the PC, the distance between the two devices, whereas it was previously limited to the length of the USB cable, is now expanded to the range of a Bluetooth signal, which can reach distances of around 10 meters.

Additionally, the accessibility of the controller to a prospective user is vastly improved by using a BLE controller on an HTML page, as opposed to a p5.js web sketch and the serial control PC app. This is most apparent when comparing the software requirements for users between both projects. Whereas the former project required a lengthy and often fickle setup process and was limited to PC use only, accessing and using this new version is as simple as loading the controller on a compatible browser on any mobile device and initializing the bluetooth connection. Beyond being much more fun and easy to use, these controls are infinitely more suitable for playtesting and public access, with no prior knowledge of the details of the connection protocol required.

The single limitation to the accessibility is browser compatibility. The Web Bluetooth API is currently not supported on most mobile browsers on iOS, requiring any potential users to load the controller on a BLE-compatible mobile browser such as Bluefy. Despite this, the setup required by any user is minimal, and much more closely resembles what would be expected of any product created for public disbribution.

## Materials

### Hardware

- An [Arduino Nano 33 IoT](https://store.arduino.cc/usa/nano-33-iot) 
- A [TB6612FNG Motor Driver](https://www.digikey.com/catalog/en/partgroup/sparkfun-motor-driver-dual-tb6612fng/77350?utm_adgroup=General&utm_source=google&utm_medium=cpc&utm_campaign=Dynamic%20Search_EN_RLSA_Cart&utm_term=&utm_content=General&gclid=CjwKCAjw6fCCBhBNEiwAem5SOxlKTUwhOICaOWppYjjd_7NRXeuuupc6Qg5i4EwhrP_Fxs8bAraEchoCxeYQAvD_BwE)
- 2 of any kind of DC motor (I used the same [N20 Encoded Gearmotors](https://www.adafruit.com/product/4641) that I used in the previous project)

### Software

For developers:
- The [Arduino IDE](https://www.arduino.cc/en/software) with the [ArduinoBLE library](https://www.arduino.cc/en/Reference/ArduinoBLE) installed

For users:
- The [Bluefy mobile browser](https://apps.apple.com/us/app/bluefy-web-ble-browser/id1492822055)

## Assembly Instructions

### Schematic Diagram:

![A schematic diagram of an Arduino Nano 33 IoT hooked up to 2 DC motors through a TB6612FNG motor driver](https://github.com/yonatanrozin/BLE-Car/blob/main/Images/BLE%20Car%20Schematic.jpg)

Software requirements for both developer and user are minimal. Developers simply need to upload the [Arduino Code](https://github.com/yonatanrozin/BLE-Car/blob/main/BLE_car.ino) to the board. Users can then access the BLE controller by loading [https://blecar.glitch.me](https://blecar.glitch.me) on the mobile Bluefy browser.

## Code and Process
An in-depth look at the code and the programming process can be found on [my blog](https://wp.nyu.edu/yonatanrozin/ble-car/).
