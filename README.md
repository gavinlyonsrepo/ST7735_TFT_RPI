![ ig ](https://github.com/gavinlyonsrepo/pic_16F18346_projects/blob/master/images/st7735/pcb.jpg)

Table of contents
---------------------------

  * [Overview](#overview)
  * [Installation](#installation)
  * [Features](#features)  
  * [Hardware](#hardware)
  * [Output](#output)

Overview
--------------------------------------------
* Name: ST7735_TFT_RPI
* Description:

0. C Library for TFT SPI LCD, ST7735 Driver, RED PCB v1.1, 1.44'', 128 x 128 pixels.
1. Dynamic install-able Raspberry Pi C library.
2. Inverse colour, rotate, sleep, idle mode & verticaly scroll methods supported.
3. Five fonts
4. Graphics class included.
5. 24 bit colour , 16 bit color & bi-color Bitmaps supported.
6. Hardware and Software SPI
7. Dependency: bcm2835 Library

* Author: Gavin Lyons
* Port of my PIC library at [github link.](https://github.com/gavinlyonsrepo/pic_16F18346_projects)
* Created: May 2021
* Developed on
    1. Raspberry PI 3 model b,
    2. C complier gcc (Raspbian 6.3.0-18)
    3. Raspbian 9.13 stretch OS
    4. bcm2835 Library 1.68

Installation
------------------------------

1. Make sure SPI bus is enabled on your raspberry PI

2. Install the dependency bcm2835 Library if not installed (at time of writing latest version is 1.68.)
	* The bcm2835 library  provides SPI bus, delays and GPIO control.
	* Install the C libraries of bcm2835, [Installation instructions here](http://www.airspayce.com/mikem/bcm2835/)

3. Download the STT735_TFT_RPI library
	* Open a Terminal in a folder where you want to download,build & test library
	* Run following command to download from github.

```sh
curl -sL https://github.com/gavinlyonsrepo/ST7735_TFT_RPI/archive/1.2.tar.gz | tar xz
```

4. Run "make" to run the makefile to install library, it will be
    installed to usr/lib and usr/include

```sh
cd ST7735_TFT_RPI-1.2
sudo make
```

5. Next step is to test TFT and installed library with the main.c test file.
Wire up your TFT. Next enter the example folder and run the makefile in THAT folder,
This second makefile builds the examples file using the just installed library.
and creates a test exe file in "bin". Be sure to use "sudo" as the bcm2835 requires root permissions by default [ see here for more details on that](http://www.airspayce.com/mikem/bcm2835/)
you should now see the test routines in that file running on TFT.

```sh
cd example/
make
sudo bin/test
```


Features
----------------------

There are three sections in header file where user can make adjustments
to select for SPI type used, PCB type used and screen size.

1. USER OPTION 1 PCB_TYPE 
2. USER OPTION 2 SPI TYPE
3. USER OPTION 3 SCREEN SECTION 

**TFT SPI LCD, ST7735 Driver, RED PCB v1.1, 1.44'', 128 x 128 pixels**

This Color TFT LCD display has 128 x 128 resolution.
It uses SPI interface to communicate with controller. Onboard LDO, support 5V/3.3V input voltage,
the LED backlight, 3.3V input. Size 1.44 inch, visual area 1.1 inch. Version 1.1.
Backlight control is left to user.

**Screen size Offsets**

In the header file, in USER OPTION 3 SCREEN SECTION 
User can adjust screen pixel height, screen pixel width and x&y screen offsets

**PCB Version**

It should work in theory on other TFT displays using the different init functions, 
but not tested.
In the header file in USER OPTION 1 PCB_TYPE select your PCB. default is "red tab". 

There are 4 types of the ST7735 TFT display supported.

1. ST7735B controller
2. ST7735R Green Tab
3. ST7735R Red Tab
4. ST7735S Black Tab

**SPI**

This library supports both Hardware SPI and software SPI.
Change the define a top of header file
to switch between the two. USER OPTION 2 SPI TYPE.
Uses bcm2835 library.
Tested at bcm2835 SPI_CLOCK_DIVIDER_32 = 7.8125MHz on Rpi2, 12.5MHz on RPI3
SPI settings can be viewed/changed in TFT_SPI_Initialize function.

**Files**

There is a TFT library (ST7735_TFT.c and ST7735_TFT.h),
and a fonts file that contains ASCII pixel fonts.

In example folder:
The Main.c file contains tests showing library functions.
A bitmap data file contains data for bi-color bitmaps and icons tests.
The color bitmaps used in testing are in bitmap folder, 3 16-bit and 3 24-bit images.

There are two makefiles

    1. Makefile at root directory builds and installs library at a system level.
    2. Makefile in example directory build example file to an executable.


**Fonts**

Six fonts available : 

| Font num | Font name | Font size xbyy |  Note |
| ------ | ------ | ------ | ------ |  
| 1 | Default | 5x8 | Full Extended ASCII 0x00 - 0xFF |
| 2 | Thick   | 7x8 | ASCII  0x20 - 0x5A  ,no lowercase letters |
| 3 | Seven segment | 4x8 | ASCII  0x20 - 0x7A |
| 4 | Wide | 8x8 | ASCII 0x20 - 0x5A , no lowercase letters |
| 5 | Big Nums | 16x32 | ASCII 0x2E-0x3A , Numbers + : . only |
| 6 | Med Nums | 16x16 | ASCII 0x2E-0x3A , Numbers + : . only |

The fonts 1-4 are byte high(at text size 1) scale-able fonts,
The large numerical Fonts 5 & 6 cannot be scaled.

**Bitmap**

There are four functions to support drawing bitmaps
Note: The library was developed on a
TFT without built-in SD card feature, so no SD-card support
in this library.

| Function Name | Colour support | Pixel size |  Note |
| ------ | ------ | ------ | ------ |
| drawIcon | bi-colour | 8 x(0-127) , 128 bytes max  | Data vertically addressed |
| drawBitmap | bi-colour | 128 by 128 , 2048 bytes max | Data horizontally  addressed |
| drawBitmap16 | 16 bit color 565 BMP files | 128 by 128 = 32K max | ------ |
| drawBitmap24  | 24 bit color BMP files | 128 by 128 = 48K max | Converted by software to 16-bit color  |

Bitmap size in kiloBytes = (screenWidth * screenHeight * bitsPerPixel)/(1024 * 8)

Hardware
----------------------

Connections as setup in main.c test file.

| TFT PinNum | Pindesc | RPI SW SPI | RPI HW SPI |
| --- | --- | --- | --- |
| 1 | LED | VCC |  VCC |
| 2 | SCLK | SPI_CLK | GPIO11 |
| 3 | SDA | SPI_MOSI | GPIO10 |
| 4 | A0/DC | GPIO24 | GPIO24  |
| 5 | RESET | GPI025  | GPIO25 |
| 6 | SS/CS | SPI_CE0 | GPIO8 |
| 7 | GND | GND | GND |
| 8 | VCC | VCC | VCC  |

1. NOTE connect LED backlight pin 1 thru a 150R/220R ohm resistor to 3.3/5V VCC.
2. This is a 3.3V logic device do NOT connect the I/O logic lines to 5V logic device.
3. You can connect VCC to 5V if there is a 3.3 volt regulator on back of TFT module.
4. Pick any GPIO you want for HW SPI for SW SPI: reset and DC lines are flexible.

![ wiring ](https://github.com/gavinlyonsrepo/ST7735_TFT_RPI/blob/main/extra/images/wiring.jpg)

Output
-----------------------

Output of some of the test routine's. Left to right, top to bottom.

1. Different defined colors at default font size 1. Full 16 bit colour 565 available
2. Different sizes of default font. Size 2 3 4 & 5 shown.
3. Different Fonts at font size 2, fonts 1-4. Are these fonts are scale-able
4. Shapes
5. Shapes
6. Bitmap (bi-color) A background and a foreground.
7. Clock Demo showing icons, small bitmaps and font 5 "BigNums"
8. 24-bit color bitmap test image
9. 16-bit color bitmap test image

![ pic ](https://github.com/gavinlyonsrepo/pic_16F18346_projects/blob/master/images/st7735/9.jpg)
![ pic1 ](https://github.com/gavinlyonsrepo/ST7735_TFT_RPI/blob/main/extra/images/4.jpg)
