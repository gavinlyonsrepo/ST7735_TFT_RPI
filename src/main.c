/*
 * Project Name: ST7735, 128 by 128, 1.44", red pcb, v1.1 SPI TFT  
 * File: main.c
 * Description: library test file  
 * Author: Gavin Lyons.
 * Created May 2021
 * Description: See URL for full details.
 * URL: https://github.com/gavinlyonsrepo/ST7735_TFT_RPI
 */

// ************ libraries **************
#include <bcm2835.h> // for SPI GPIO and delays.
#include "ST7735_TFT.h"
#include <stdio.h> // for printf
#include "Bi_Color_Bitmap.h" // Data for test 11 and 12.
#include <time.h> // for test 11

// *********** Defines **************
#define TEST_DELAY1 1000
#define TEST_DELAY2 2000
#define TEST_DELAY5 5000
#define CLOCK_DISPLAY_TIME 100

// **************** GPIO ***************
#define  RST_TFT 25
#define DC_TFT 24
#ifndef TFT_SPI_HARDWARE  
	#define SCLK_TFT 11
	#define SDIN_TFT 10
	#define CS_TFT 8
#endif

// ************ Function Headers ****************
void Setup(void);

void Test0(void);  // Print out all five fonts, fonts must be enabled in header file for this to work
void Test1A(void); // defined 16-bit Colors, text
void Test1B(void); // print entire ASCII font 32 to 127
void Test1C(void); // print numbers int and float
void Test2(void);  // font sizes(1-4)+ character draw
void Test3(void);  // pixels and lines
void Test4(void);  // rectangles 
void Test5(void);  // Circle
void Test6(void);  // Triangles 
void Test7(void);  // scroll
void Test8(void);  // More shapes, media buttons graphic.
void Test9(void);  // Rotate
void Test10(void); // change modes test // Invert, display on/off and Sleep.
void Test11(void); // icons, small bi-color bitmaps, BigNum font (5)
void Test12(void); // two color bitmap
void Test14(void); // 24 color bitmap
void Test15(void); //16 color bitmap 

void EndTests(void);

// ************  MAIN ***************

int main(void) 
{
	if(!bcm2835_init())
	{
		printf("Error 1201 : Problem with init bcm2835 library\r\n");
		return -1;
	}
	Setup();

	while (1) 
	{
		
		Test0();
		Test1A();
		Test1B();
		Test1C();
		Test2();
		Test3();
		Test4();
		Test5();
		Test6();
		Test7();
		Test8();
		Test9();
		Test10();
		Test11();
		Test12();
		Test14();
		Test15();
		
		EndTests();
		return 0;
	}
}
// ********* End OF MAIN ********


// ******** Function Space *************

// Initialize the device

void Setup(void) 
{
	bcm2835_delay(TEST_DELAY2);
	printf("TFT Start\r\n");
	
#ifndef TFT_SPI_HARDWARE  
	TFT_Setup(RST_TFT, DC_TFT ,CS_TFT , SCLK_TFT, SDIN_TFT);
#else
	TFT_Setup(RST_TFT, DC_TFT ,-1 , -1, -1);
#endif

#ifdef TFT_PCB_RED
	TFT_RedTab_Initialize();
#endif
#ifdef TFT_PCB_GREEN
	TFT_GreenTab_Initialize();
#endif
#ifdef TFT_PCB_BLACK
	TFT_BlackTab_Initialize();
#endif
#ifdef  TFT_PCB_GENERIC
	TFT_ST7735B_Initialize();
#endif

	TFTsetRotation(0);
	TFTsetTextWrap(true);
	TFTFontNum(1);
	bcm2835_delay(TEST_DELAY1);
	TFTfillScreen(ST7735_BLACK);
}



void Test0(void) {

	TFTFontNum(1);
	TFTdrawText(0, 5, "Default 1", ST7735_WHITE, ST7735_BLACK, 2);
	TFTFontNum(2);
	TFTdrawText(0, 35, "THICK 2", ST7735_GREEN, ST7735_BLACK, 2);
	TFTFontNum(3);
	TFTdrawText(0, 65, "Seven 3", ST7735_BLUE, ST7735_BLACK, 2);
	TFTFontNum(4);
	TFTdrawText(0, 95, "WIDE 4", ST7735_CYAN, ST7735_BLACK, 2);
	bcm2835_delay(TEST_DELAY2);
	TFTfillScreen(ST7735_BLACK);
	TFTFontNum(1);
}

void Test1A(void) {
	char *txt = "WHITE";
	TFTdrawText(0, 5, txt, ST7735_WHITE, ST7735_BLACK, 1);
	TFTdrawText(0, 15, "BLUE", ST7735_BLUE, ST7735_BLACK, 1);
	TFTdrawText(0, 25, "RED", ST7735_RED, ST7735_BLACK, 1);
	TFTdrawText(0, 35, "GREEN", ST7735_GREEN, ST7735_BLACK, 1);
	TFTdrawText(0, 45, "CYAN", ST7735_CYAN, ST7735_BLACK, 1);
	TFTdrawText(0, 55, "MAGENTA", ST7735_MAGENTA, ST7735_BLACK, 1);
	TFTdrawText(0, 65, "YELLOW", ST7735_YELLOW, ST7735_BLACK, 1);
	TFTdrawText(0, 75, txt, ST7735_WHITE, ST7735_BLACK, 1);
	TFTdrawText(0, 85, "GREY", ST7735_GREY, ST7735_BLACK, 1);
	TFTdrawText(0, 95, "TAN", ST7735_TAN, ST7735_BLACK, 1);
	TFTdrawText(0, 105, "BROWN", ST7735_BROWN, ST7735_BLACK, 1);
	bcm2835_delay(TEST_DELAY2);
	TFTfillScreen(ST7735_BLACK);
}

void Test1B(void) {
	uint8_t row = 5;
	uint8_t col = 0;
	for (char i = TFT_ASCII_OFFSET; i < 126; i++) {
		TFTdrawChar(col, row, i, ST7735_GREEN, ST7735_BLACK, 1);
		col += 10;
		if (col > 100) {
			row += 10;
			col = 0;
		}
		bcm2835_delay(5);
	}

	bcm2835_delay(TEST_DELAY2);
	TFTfillScreen(ST7735_BLACK);
}


void Test1C(void)
{
		int myInt=931;
		char myStr[5];
		TFTFontNum(3);
		sprintf(myStr, "%d", myInt);
		TFTdrawText(5, 5, myStr, ST7735_BLUE, ST7735_BLACK, 3);

		float  myPI = 3.141592;
		char myStr2[8];
		sprintf(myStr2, "%0.2f", myPI);
		TFTdrawText(5, 65, myStr2, ST7735_RED, ST7735_BLACK, 3);
		
		bcm2835_delay(TEST_DELAY2);
		TFTfillScreen(ST7735_BLACK);
		TFTFontNum(1);
}

void Test2(void) {
	char *txttwo = "TEST";
	TFTdrawText(0, 5, txttwo, ST7735_WHITE, ST7735_BLACK, 2);
	TFTdrawText(0, 25, txttwo, ST7735_WHITE, ST7735_BLACK, 3);
	TFTdrawText(0, 55, txttwo, ST7735_WHITE, ST7735_BLACK, 4);
	TFTdrawChar(0, 85, 'G', ST7735_WHITE, ST7735_BLACK, 5);
	TFTdrawChar(45, 85, 'L', ST7735_WHITE, ST7735_BLACK, 5);

	bcm2835_delay(TEST_DELAY2);
	TFTfillScreen(ST7735_BLACK);
}

void Test3(void)  
{
	TFTdrawPixel(85, 5, ST7735_WHITE);
	TFTdrawPixel(87, 7, ST7735_WHITE);
	TFTdrawPixel(89, 9, ST7735_WHITE);
	TFTdrawLine(10, 10, 30, 30, ST7735_RED);
	TFTdrawFastVLine(40, 40, 40, ST7735_GREEN);
	TFTdrawFastHLine(60, 60, 40, ST7735_YELLOW);

	bcm2835_delay(TEST_DELAY2);
	TFTfillScreen(ST7735_BLACK);
}

void Test4(void) {
	drawRectWH(5, 5, 20, 20, ST7735_RED);
	fillRectangle(45, 5, 20, 20, ST7735_YELLOW);
	fillRect(85, 5, 20, 20, ST7735_GREEN);
	drawRoundRect(15, 60, 50, 50, 5, ST7735_CYAN);
	fillRoundRect(70, 60, 50, 50, 10, ST7735_WHITE);

	bcm2835_delay(TEST_DELAY2);
	TFTfillScreen(ST7735_BLACK);
}

void Test5(void) {
	drawCircle(40, 20, 15, ST7735_GREEN);
	fillCircle(80, 20, 15, ST7735_YELLOW);
}

void Test6(void) {
	drawTriangle(5, 80, 50, 40, 95, 80, ST7735_CYAN);
	fillTriangle(55, 120, 100, 90, 127, 120, ST7735_RED);

	bcm2835_delay(TEST_DELAY2);
	TFTfillScreen(ST7735_BLACK);
}


void Test7(void) 
{
  const uint8_t LINES = 10, LINE_SIZE = 10, LINE_OFFSET = 3, TOP_FIXED = 0, BOTTOM_FIXED = 0;
  
  for (uint8_t i = 0; i < LINES; i++)
  {
	TFTdrawText(0, LINE_OFFSET+i*LINE_SIZE,"Scroll test", ST7735_WHITE, ST7735_BLACK, 1);
  }
  setScrollDefinition(TOP_FIXED,BOTTOM_FIXED,1);  // bottom-to-top
  uint8_t pos = LINE_OFFSET;
  for (uint8_t i = 0; i < LINES; i++) 
  {
	for (uint8_t j = 0; j < LINE_SIZE; j++) 
	{
	  VerticalScroll(pos + TOP_FIXED);
	  pos++;
	  // check pos if necessary: must be < tft_height_TFT - TOP_FIXED - BOTTOM_FIXED
	  bcm2835_delay(20);  
	}
	bcm2835_delay(TEST_DELAY1);
  }
  TFTchangeMode(NORMAL); 
  TFTfillScreen(ST7735_BLACK);
}

void Test8() 
{
	//Draw play button 
	fillRoundRect(25, 10, 78, 60, 8, ST7735_WHITE);
	fillTriangle(42, 20, 42, 60, 90, 40, ST7735_RED);
	TFTdrawText(5, 80, "Press Play", ST7735_GREEN, ST7735_BLACK, 2);
	bcm2835_delay(TEST_DELAY1);
	
	// change play color
	fillTriangle(42, 20, 42, 60, 90, 40, ST7735_BLUE);
	bcm2835_delay(TEST_DELAY1);
	// change play color
	fillTriangle(42, 20, 42, 60, 90, 40, ST7735_GREEN);
	bcm2835_delay(TEST_DELAY1);
}

void Test9()
{
	TFTfillScreen(ST7735_BLACK);
	TFTsetRotation(0);
	TFTdrawText(20, 20, "Rotate 0", ST7735_GREEN, ST7735_BLACK, 1);
	bcm2835_delay(TEST_DELAY2);
	
	TFTfillScreen(ST7735_BLACK);
	TFTsetRotation(1);
	TFTdrawText(20, 20, "Rotate 1", ST7735_GREEN, ST7735_BLACK, 1);
	bcm2835_delay(TEST_DELAY2);
	
	TFTfillScreen(ST7735_BLACK);
	TFTsetRotation(2);
	TFTdrawText(20, 20, "Rotate 2", ST7735_GREEN, ST7735_BLACK, 1);
	bcm2835_delay(TEST_DELAY2);
	
	TFTfillScreen(ST7735_BLACK);
	TFTsetRotation(3);
	TFTdrawText(20, 20, "Rotate 3", ST7735_GREEN, ST7735_BLACK, 1);
	bcm2835_delay(TEST_DELAY2);
	
	TFTsetRotation(0);
	TFTchangeMode(NORMAL);
	TFTfillScreen(ST7735_BLACK);
}

void Test10()
{
	fillRoundRect(25, 10, 78, 60, 8, ST7735_YELLOW);
	TFTdrawText(30, 80, "Mode test", ST7735_WHITE, ST7735_RED, 1);
	bcm2835_delay(TEST_DELAY2);
	 TFTchangeMode(NORMAL);
	 bcm2835_delay(TEST_DELAY2);
	 TFTchangeMode(INVERT);
	 bcm2835_delay(TEST_DELAY2);
	 TFTchangeMode(NORMAL);
	 bcm2835_delay(TEST_DELAY2);
	 TFTchangeMode(DISP_OFF);
	 bcm2835_delay(TEST_DELAY2);
	 TFTchangeMode(DISP_ON);
	 bcm2835_delay(TEST_DELAY2);
	 TFTchangeMode(SLEEP);
	 bcm2835_delay(TEST_DELAY2);
	 TFTchangeMode(NORMAL);
}

void Test11(void)
{
	time_t now;
	struct tm *timenow;
	char value[10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
	uint16_t count=CLOCK_DISPLAY_TIME;
	char myStr[5];
	
	TFTfillScreen(ST7735_BLACK);
	
	TFTdrawIcon(2, 2, 16, ST7735_BLACK, ST7735_WHITE, SignalIcon);
	TFTdrawIcon(20, 2, 16, ST7735_BLACK, ST7735_WHITE, MsgIcon);
	TFTdrawIcon(40, 2, 8, ST7735_BLACK, ST7735_WHITE, AlarmIcon);
	TFTdrawIcon(102, 2, 16, ST7735_BLACK, ST7735_WHITE, BatIcon);
	
	TFTdrawIcon(5, 20, 12, ST7735_GREEN , ST7735_BLACK,powerIcon);
	TFTdrawIcon(20, 20, 12, ST7735_RED, ST7735_YELLOW, speedIcon);
	TFTdrawBitmap(105, 20, 20 , 20, ST7735_CYAN , ST7735_BLACK, smallImage);
	
	TFTdrawText(80, 90, "G Lyons", ST7735_BLUE, ST7735_BLACK, 1);
	TFTFontNum(5);
	while(1)
	{
		time(&now);
		timenow = localtime(&now); 
		count--; 
		sprintf(myStr, "%03d", count);
		
		TFTdrawCharBigNum(0, 45, value[timenow->tm_hour / 10],ST7735_RED, ST7735_BLACK);
		TFTdrawCharBigNum(16, 45, value[timenow->tm_hour % 10],ST7735_RED, ST7735_BLACK);
		TFTdrawCharBigNum(32, 45, ':' , ST7735_GREEN, ST7735_BLACK);
		TFTdrawCharBigNum(48, 45, value[timenow->tm_min / 10], ST7735_RED, ST7735_BLACK);
		TFTdrawCharBigNum(64, 45, value[timenow->tm_min % 10], ST7735_RED, ST7735_BLACK);
		TFTdrawCharBigNum(80, 45, ':' , ST7735_GREEN, ST7735_BLACK);
		TFTdrawCharBigNum(96, 45, value[timenow->tm_sec / 10],  ST7735_RED, ST7735_BLACK);
		TFTdrawCharBigNum(112, 45, value[timenow->tm_sec % 10],  ST7735_RED, ST7735_BLACK);
		TFTdrawTextBigNum(0, 85, myStr, ST7735_YELLOW, ST7735_RED);
		
		if(count==1)break;
	}
	bcm2835_delay(TEST_DELAY2);
	TFTfillScreen(ST7735_BLACK);
	TFTFontNum(1);
}

void Test12(void)
{
TFTdrawBitmap(0, 0, _width_TFT , _height_TFT, ST7735_WHITE , ST7735_GREEN, backupMenuBitmap);
bcm2835_delay(TEST_DELAY5);
}

//All files Windows BITMAPINFOHEADER offset 54
void Test14(void)
{
	FILE *pFile ;
	
	size_t pixelSize = 3;
	unsigned char bmpBuffer[(_width_TFT * _height_TFT) * pixelSize ];
	
	pFile = fopen("bitmap/24pic1.bmp", "r");
	if (pFile == NULL) 
	{
		printf("File does not exist\n");
		return;
	}
	fseek(pFile, 54, 0);
	fread(bmpBuffer, pixelSize, _width_TFT * _height_TFT, pFile);
	fclose(pFile);

	TFTdrawBitmap24(0, 0, bmpBuffer, _width_TFT, _height_TFT);

	bcm2835_delay(TEST_DELAY5);
	
	pFile = fopen("bitmap/24pic2.bmp", "r");
	if (pFile == NULL) {
		printf("File does not exist\n");
		return;
	}
	fseek(pFile, 54, 0);
	fread(bmpBuffer, pixelSize, _width_TFT * _height_TFT, pFile);
	fclose(pFile);

	TFTdrawBitmap24(0, 0, bmpBuffer, _width_TFT, _height_TFT);

	bcm2835_delay(TEST_DELAY5);
	
	pFile = fopen("bitmap/24pic3.bmp", "r");
	if (pFile == NULL) {
		printf("File does not exist\n");
		return;
	}
	fseek(pFile, 54, 0);
	fread(bmpBuffer, pixelSize, _width_TFT * _height_TFT, pFile);
	fclose(pFile);

	TFTdrawBitmap24(0, 0, bmpBuffer, _width_TFT, _height_TFT);
	
	bcm2835_delay(TEST_DELAY5);
	TFTfillScreen(ST7735_BLACK);
	
}


void Test15(void)
{
	FILE *pFile ;
	size_t pixelSize = 2;
	unsigned char bmpBuffer1[(_width_TFT * _height_TFT) * pixelSize ];
	
	// File 1  BITMAPV5HEADER offset 132
	// made in GIMP , Color space information written 
	// RGB 565 16 bit color
	pFile = fopen("bitmap/16pic1.bmp", "r");
	if (pFile == NULL) {
		printf("File does not exist\n");
		return;
	}
	fseek(pFile, 132, 0);
	fread(bmpBuffer1, pixelSize, _width_TFT * _height_TFT, pFile);
	fclose(pFile);
	TFTdrawBitmap16(0, 0, bmpBuffer1, _width_TFT, _height_TFT);
	
	bcm2835_delay(TEST_DELAY5);
	
	//file 2 OS/2 OS22XBITMAPHEADER (BITMAPINFOHEADER2) offset 72
	// made in GIMP Color,  NO color space information written 
	// RGB 565 16 bit color
	pFile = fopen("bitmap/16pic2.bmp", "r");
	if (pFile == NULL) {
		printf("File does not exist\n");
		return;
	}
	fseek(pFile, 72, 0);
	fread(bmpBuffer1, pixelSize, _width_TFT * _height_TFT, pFile);
	fclose(pFile);
	TFTdrawBitmap16(0, 0, bmpBuffer1, _width_TFT, _height_TFT);
	
	bcm2835_delay(TEST_DELAY5);
	
	// file 3 OS/2 OS22XBITMAPHEADER (BITMAPINFOHEADER2) offset 72
	// made in GIMP Color NO color space information written 
	// RGB 565 16 bit color
	pFile = fopen("bitmap/16pic3.bmp", "r");
	if (pFile == NULL) {
		printf("File does not exist\n");
		return;
	}
	fseek(pFile, 72, 0);
	fread(bmpBuffer1, pixelSize, _width_TFT * _height_TFT, pFile);
	fclose(pFile);
	TFTdrawBitmap16(0, 0, bmpBuffer1, _width_TFT, _height_TFT);
	
	bcm2835_delay(TEST_DELAY5);
	TFTfillScreen(ST7735_BLACK);
}

void EndTests(void)
{
	TFTfillScreen(ST7735_BLACK);
	TFTdrawText(5, 50, "Tests over", ST7735_GREEN, ST7735_BLACK, 2);
	bcm2835_delay(TEST_DELAY5);
	
	TFT_PowerDown(); // Power down device
#ifdef TFT_SPI_HARDWARE  
	TFT_SPIoff(); //Stop the hardware SPI
#endif
	bcm2835_close(); // Close the bcm2835 library
	printf("TFT End\r\n");
}
// *************** EOF ****************
