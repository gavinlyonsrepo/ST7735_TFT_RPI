Table of contents
---------------------------

  * [Overview](#overview)
  * [Usage](#usage)
  * [Hardware](#hardware)
  * [Features](#features)


Overview
--------------------------------------------
* Name: ST7735_TFT_RPI
* Description: 

0. Library for TFT SPI LCD, ST7735 Driver, RED PCB v1.1, 1.44'', 128 x 128 pixels. 
no SD card holder.
1. Raspberry Pi C library, gcc complier.      
2. Inverse colour, rotate, sleep, idle mode & verticaly scroll methods supported. 
3. Five fonts 
4. Graphics class included.
5. Full Bitmap supported.
6. Hardware and Software SPI 
7. Dependency: bcm2835 Library

* Author: Gavin Lyons
* Port of my PIC library at [github link.](https://github.com/gavinlyonsrepo/pic_16F18346_projects)
* Created: May 2021


Usage
------------------------------

1. Make sure SPI bus is enabled on your raspberry PI

2. Install the bcm2835 Library (at time of writing latest version is 1.68.)
	* The bcm2835 libray is a dependency and provides SPI bus, delays and GPIO control.
	* Install the C libraries of bcm2835, [Installation instructions here](http://www.airspayce.com/mikem/bcm2835/)

3. Download the ST7735_TFT_RPI library 
	* Open a Terminal in a folder where you want to create your project.
	* Run following commands to do this.
```sh
curl -sL https://github.com/gavinlyonsrepo/ST7735_TFT_RPI/archive/1.0.tar.gz | tar xz
cd ST7735_TFT_RPI_1.0
```

4. Build the project, by running the makefile included.
	* Run make to run the makefile and build the project.
	* The makefile does NOT install to system at present, it builds the code in that folder.
	
```sh
make
```

5. Run the program
	* The makefile creates a executable binary test file at ./bin/test
 	* It runs a series of 15 tests on the TFT showing features of lib. 
	* Be sure to use "sudo" as the bcm2835 demands root permissions [ see here for more details](http://www.airspayce.com/mikem/bcm2835/) 

```sh
sudo ./bin/test
```

6. Copy the library code files into your project folder directory however you wish to organise it. 
	* The header files are in the include folder in my repo.
	* And the soucre files are in src in my repo.
	* If you are not using included makefile to build be sure to include -lbcm2835 flag in yours.
	
Features
----------------------

**TFT SPI LCD, ST7735 Driver, RED PCB v1.1, 1.44'', 128 x 128 pixels**

![ ig ](https://github.com/gavinlyonsrepo/pic_16F18346_projects/blob/master/images/st7735/pcb.jpg)
 
This Color TFT LCD display has 128 x 128 resolution.
It uses SPI interface to communicate with controller. Onboard LDO, support 5V/3.3V input voltage, 
the LED backlight, 3.3V input. Size 1.44 inch, visual area 1.1 inch. Version 1.1. 
Backlight control is left to user.

**PCB Version**

It should work on other TFT displays using the different init functions, but not tested.
In the header file in USER OPTION 1 PCB_TYPE select your PCB.
default is red. User can adjust pixel height, pixel width and screen offsets in the header file. 

There are 4 types of the ST7735 TFT display supported.

1. ST7735B controller 
2. ST7735R Green Tab
3. ST7735R Red Tab
4. ST7735S Black Tab 

**SPI**

This library supports both Hardware SPI and software SPI. 
Change the define a top of header file
to switch between the two. USER OPTION 3 SPI TYPE. 
Uses bcm2835 library. 
Tested at bcm2835 SPI_CLOCK_DIVIDER_32 = 7.8125MHz on Rpi2, 12.5MHz on RPI3
SPI settings can be viewed/changed in TFT_SPI_Initialize function.

**Files**

The Main.c file contains tests showing library functions.
There is also an TFT library (ST7735_TFT.c and ST7735_TFT.h),
and five fonts file that contains ASCII pixel fonts.
A bitmap data file contains data for bi-color bitmaps and icons.
The color bitmaps used in testing are in bitmap folder, 3 16-bit and 3 24-bit images.

**Fonts**

All Font fonts included by default to exclude unused font files see
USER OPTION 2 FONT at start of header file.

Five fonts available : 

| Font num | Font name | Pixel size |  Note |
| ------ | ------ | ------ | ------ |  
| 1 | Default | 5x8 |   ------ |
| 2 | Thick   | 7x8 |  no lowercase letters  |
| 3 | Seven segment | 4x8 | ------ |
| 4 | Wide | 8x8 | no lowercase letters |
| 5 | BigNums | 16x32 |  Numbers only , Cannot be scaled |

**Bitmap**

There are four functions to support drawing bitmaps
Note: The library was developed on a
TFT without built-in SD card feature, so no SD-card support
in this library. 

| Function Name | Colour support | Pixel size |  Note |
| ------ | ------ | ------ | ------ |  
| drawIcon | bi-colour | 8x(0-127) , 128 bytes max  | Data vertically addressed |  
| drawBitmap | bi-colour | 128*128 , 2048 bytes max | Data horizontally  addressed |  
| drawBitmap16 | 16 bit color 565 BMP files | 128*128 32K max | ------ |  
| drawBitmap24  | 24 bit color BMP files | 128*128 48K max | Converted by software to 16-bit color  |
  
Bitmap size in kiloBytes = (screenWidth * screenHeight * bitsPerPixel)/(1024 * 8)

**Connections**

Connections as setup in main.c test file.

| TFT PinNum | Pindesc | RPI SW SPI | RPI HW SPI |
| --- | --- | --- | --- | 
| 1 | LED | VCC |  VCC |
| 2 | SCLK | SPI_CLK | GPIO11 |
| 3 | SDA | SPI_MOSI | GPIO10 |
| 4 | A0/DC | GPIO23 | GPIO23  |
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
