# GridEye Camera

This is a 8x8 pixels IR camera based on the **Panasonic AMG88XX GridEye** sensors.
It uses a **WS2812 8x8 matrix** as camera display, an **128x32 uOLED display** for data and
a **Moteino** board with an ATMega328P microcontroller as controller.
It is powered by a **LiPo battery** connected to a **TP4056 based LiPO charger**.
There is also a **Pololu Adjustable Boost Regulator 2.5-9.5V** to power the LED matrix.

The AMG8833 is an 8x8 IR sensor by Panasonic with an I2C interface that reports concact-less temperature values from -20 to 80 celsius with a 2.5C accuracy and 0.25C resolution. It has a field view of ~60º and a max detection distance of 5 meters.

![GridEye Camera](/docs/20170528_105511x.jpg)

This is part of my "Slices" project, basically a sliced laser cut series of enclosures to house electronic projects.

## Hardware

### The electronics

The project relies on different discreet modules wired together. All the components (or compatible alternatives) are widely available. Only the AMG88XX board is custom made. Check the "amg8833" fordel in this repo for the Eagle files of the board.

![GridEye Camera Schema Drawing](/docs/schema.jpg)

All the dotted black lines in the drawing are connected together.

### The housing

The housing has been created using OpenSCAD and inspired by Pimoroni  PiBow enclosures for the RaspBerry Pi. I've been using this same technique lately on different project and I call them all under a common name: "Project Slices".

The enclosure is based on layers or "slices" of different materials.

* Transparent acrylic front-face
* Black cardboard mask
* White paper diffusor
* 4mm MDF grid that houses each LED in its own cubicle
* 2.5mm MDF cast for the LED matrix PCB
* 2.5mm MDF as support for the matrix PCB and uOLED board
* several (5) 4mm MDF hollow layers to house the electronics
* 2.5mm MDF as support for the AMG88XX board
* 4mm MDF hollow layers to house the AMG88XX board
* 2.5mm MDF as a back pane with a hole for the IR sensor

![GridEye Camera Housing 1](/models/model_01.png)

![GridEye Camera Housing 2](/models/model_02.png)

![GridEye Camera Housing 3](/models/model_04.png)

## Firmware

The project is ready to be build using [PlatformIO](http://www.platformio.org).
Please refer to their web page for instructions on how to install the builder.
Once installed:

```bash
> cd code
> platformio run
> platformio run --target upload
```

Library dependencies are automatically managed via PlatformIO Library Manager.
