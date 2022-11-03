/*
 * Project Name: ST7735, 128 by 128, 1.44", red pcb, v1.1 SPI TFT  
 * File: main.cpp
 * Description: library test file  
 * Author: Gavin Lyons.
 * Created May 2021
 * Description: See URL for full details.
 * URL: https://github.com/gavinlyonsrepo/ST7735_TFT_RPI
 */

// Section ::  libraries 
#include <bcm2835.h> // for SPI GPIO and delays.
#include <stdio.h> // for printf
#include <time.h> // for test 11

#include "ST7735_TFT.h"
#include "Bi_Color_Bitmap.h" // Data for test 11 and 12.

// Section :: Defines   
//  Test timing related defines 
#define TEST_DELAY1 1000
#define TEST_DELAY2 2000
#define TEST_DELAY5 5000
#define CLOCK_DISPLAY_TIME 100

// Section :: Globals 
ST7735_TFT myTFT;

//  Section ::  Function Headers 

void Setup(void);  // setup + user options
void Test0(void);  // Print out all fonts 1-5
void Test1A(void); // defined 16-bit Colors, text
void Test1B(void); // print entire ASCII font 0 to 127, default font
void Test1C(void); // print numbers int and float using draw functions
void Test1D(void); // print numbers int and float using PRINT function
void Test1E(void); // Print out font 6 & 7 using draw functions
void Test2(void);  // font sizes(1-4) + character draw using draw functions
void Test3(void);  // pixels and lines
void Test4(void);  // rectangles 
void Test5(void);  // Circle
void Test6(void);  // Triangles 
void Test7(void);  // scroll
void Test8(void);  // More shapes, media buttons graphic.
void Test9(void);  // Rotate
void Test10(void); // change modes test -> Invert, display on/off and Sleep.
void Test11(void); // "clock demo" icons, small bi-color bitmaps, font 6 & 7
void Test12(void); // 2  color bitmap
void Test14(void); // 24 color bitmap
void Test15(void); // 16 color bitmap 
void TestFPS(void); // Frames per second
void EndTests(void);

// Utility
int64_t getTime();
uint8_t* loadImage(char* name);

//  Section ::  MAIN loop



int main(void) 
{
	if(!bcm2835_init())
	{
		printf("Error 1201 : Problem with init bcm2835 library\r\n");
		return -1;
	}
	
	Setup();

	Test0();
	Test1A();
	Test1B();
	Test1C();
	Test1D();
	Test1E();
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
	TestFPS();

	// EndTests();
	return 0;
}
// *** End OF MAIN **


//  Section ::  Function Space 

void Setup(void)
{
	
// ****** USER OPTION 1 Screen Setup ****** 
	uint8_t OFFSET_COL = 26;  // 2, These offsets can be adjusted for any issues->
	uint8_t OFFSET_ROW = 1; // 3, with manufacture tolerance/defects
	uint16_t TFT_WIDTH = 80;// Screen width in pixels
	uint16_t TFT_HEIGHT = 160; // Screen height in pixels
// ******************************************

// ******** USER OPTION 2 GPIO/SPI TYPE *************************
	int8_t RST_TFT = 25;
	int8_t DC_TFT = 24;
	int8_t SCLK_TFT = -1; // 11,  change to GPIO no for software spi
	int8_t SDIN_TFT = -1; // 10, change to GPIO no for software spi
	int8_t CS_TFT = -1 ;  // 8, change to GPIO no for software spi
	int32_t SCLK_FREQ = 50000000;
//**********************************************************
	bcm2835_delay(TEST_DELAY1);
	printf("TFT Start\r\n");
	myTFT.TFTSetupGPIO(RST_TFT, DC_TFT, CS_TFT, SCLK_TFT, SDIN_TFT);
	myTFT.TFTInitSPIClockFrequency(SCLK_FREQ);
	myTFT.TFTInitScreenSize(OFFSET_COL, OFFSET_ROW , TFT_WIDTH , TFT_HEIGHT);
// ******** USER OPTION 3 PCB_TYPE **************************
// init PCB type , pass enum 4 choices, see readme
	myTFT.TFTInitPCBType(TFT_ST7735R_Red);
	myTFT.TFTsetRotation(TFT_Degress_270);
	myTFT.TFTchangeInvertMode(true);
//**********************************************************

}

void Test0(void) {

	char teststr1[] = "Default 1";
	char teststr2[] = "THICK 2";
	char teststr3[] = "Seven 3";
	char teststr4[] = "WIDE 4";
	char teststr5[] = "Tiny 5";
	
	myTFT.TFTfillScreen(ST7735_BLACK);
	
	myTFT.TFTFontNum(TFTFont_Default);
	myTFT.TFTdrawText(0, 5, teststr1, ST7735_WHITE, ST7735_BLACK, 2);
	myTFT.TFTFontNum(TFTFont_Thick);
	myTFT.TFTdrawText(0, 35, teststr2, ST7735_GREEN, ST7735_BLACK, 2);
	myTFT.TFTFontNum(TFTFont_Seven_Seg);
	myTFT.TFTdrawText(0, 55, teststr3, ST7735_BLUE, ST7735_BLACK, 2);
	myTFT.TFTFontNum(TFTFont_Wide);
	myTFT.TFTdrawText(0, 75, teststr4, ST7735_CYAN, ST7735_BLACK, 2);
	myTFT.TFTFontNum(TFTFont_Tiny);
	myTFT.TFTdrawText(0, 100, teststr5, ST7735_RED, ST7735_BLACK, 2);
	bcm2835_delay(TEST_DELAY5);
	myTFT.TFTfillScreen(ST7735_BLACK);
	myTFT.TFTFontNum(TFTFont_Default);
}

void Test1A(void) {
	char teststr1[] = "WHITE";
	char teststr2[] = "BLUE";
	char teststr3[] = "RED";
	char teststr4[] = "GREEN";
	char teststr5[] = "CYAN";
	char teststr6[] = "MAGENTA";
	char teststr7[] = "YELLOW";
	char teststr8[] = "GREY";
	char teststr9[] = "TAN";
	char teststr10[] = "BROWN";
	myTFT.TFTdrawText(0, 5, teststr1, ST7735_WHITE, ST7735_BLACK, 1);
	myTFT.TFTdrawText(0, 15, teststr2, ST7735_BLUE, ST7735_BLACK, 1);
	myTFT.TFTdrawText(0, 25, teststr3, ST7735_RED, ST7735_BLACK, 1);
	myTFT.TFTdrawText(0, 35, teststr4, ST7735_GREEN, ST7735_BLACK, 1);
	myTFT.TFTdrawText(0, 45, teststr5, ST7735_CYAN, ST7735_BLACK, 1);
	myTFT.TFTdrawText(0, 55, teststr6, ST7735_MAGENTA, ST7735_BLACK, 1);
	myTFT.TFTdrawText(0, 65, teststr7, ST7735_YELLOW, ST7735_BLACK, 1);
	myTFT.TFTdrawText(0, 75, teststr1, ST7735_WHITE, ST7735_BLACK, 1);
	myTFT.TFTdrawText(0, 85, teststr8, ST7735_GREY, ST7735_BLACK, 1);
	myTFT.TFTdrawText(0, 95, teststr9, ST7735_TAN, ST7735_BLACK, 1);
	myTFT.TFTdrawText(0, 105, teststr10 , ST7735_BROWN, ST7735_BLACK, 1);
	bcm2835_delay(TEST_DELAY5);
	myTFT.TFTfillScreen(ST7735_BLACK);
}

void Test1B(void) {
	uint8_t row = 5;
	uint8_t col = 0;
	for (char i = 0; i < 126; i++) {
		
		myTFT.TFTdrawChar(col, row, i, ST7735_GREEN, ST7735_BLACK, 1);
		col += 10;
		if (col > 100) {
			row += 10;
			col = 0;
		}
		bcm2835_delay(20);
	}

	bcm2835_delay(TEST_DELAY5);
	myTFT.TFTfillScreen(ST7735_BLACK);
}


void Test1C(void)
{
	int myInt=931;
	char myStr[5];
	myTFT.TFTFontNum(TFTFont_Seven_Seg);
	sprintf(myStr, "%d", myInt);
	myTFT.TFTdrawText(5, 5, myStr, ST7735_BLUE, ST7735_BLACK, 3);

	float  myPI = 3.141592;
	char myStr2[8];
	sprintf(myStr2, "%0.3f", myPI);
	myTFT.TFTdrawText(5, 65, myStr2, ST7735_RED, ST7735_BLACK, 3);
	
	bcm2835_delay(TEST_DELAY2);
	myTFT.TFTfillScreen(ST7735_BLACK);
		
}


void Test1D(void){

	myTFT.setTextSize(1);  // Test a string with print 
	myTFT.TFTsetCursor(10,10);
	myTFT.TFTFontNum(TFTFont_Default);
	myTFT.print("Hello ");
	
	myTFT.TFTFontNum(TFTFont_Thick);
	myTFT.TFTsetCursor(50,10); // Test a int with print 
	myTFT.print(1243);
	
	// Test a int with print inverted size 2
	myTFT.setTextSize(2);
	myTFT.setTextColor(ST7735_RED, ST7735_YELLOW);
	myTFT.TFTfillRectangle(5, 25, 120, 20, ST7735_YELLOW);
	myTFT.TFTsetCursor(5,25);
	myTFT.TFTFontNum(TFTFont_Seven_Seg);
	myTFT.print(492);
	
	myTFT.TFTsetCursor(45,25); // Test a float 
	myTFT.TFTFontNum(TFTFont_Wide);
	myTFT.print(3.14);
	
	myTFT.TFTsetCursor(10,55); // Test float bignum font
	myTFT.TFTFontNum(TFTFont_Bignum);
	myTFT.print(5.16);
	
	myTFT.TFTsetCursor(10,95); // Test float  mednum font
	myTFT.setTextColor(ST7735_WHITE, ST7735_BLACK);
	myTFT.TFTFontNum(TFTFont_Mednum);
	myTFT.print(76.88);
	
	bcm2835_delay(TEST_DELAY5);
	myTFT.TFTfillScreen(ST7735_BLACK);
}

void Test1E(void)
{
	// Note fonts 6 and 7 are numbers only + : 
	char teststr1[] = "12:81";
	char teststr2[] = "72:83";
	
	myTFT.TFTFontNum(TFTFont_Bignum);
	myTFT.TFTdrawCharNumFont(0, 0, '6',  ST7735_RED, ST7735_BLACK);
	myTFT.TFTdrawTextNumFont(0, 40, teststr1, ST7735_YELLOW, ST7735_RED);
	
	myTFT.TFTFontNum(TFTFont_Mednum);
	myTFT.TFTdrawCharNumFont(0, 75, '7',  ST7735_WHITE, ST7735_BLACK);
	myTFT.TFTdrawTextNumFont(0, 100, teststr2, ST7735_GREEN, ST7735_RED);
	
	bcm2835_delay(TEST_DELAY5);
	myTFT.TFTfillScreen(ST7735_BLACK);
}

void Test2(void) {
	myTFT.TFTFontNum(TFTFont_Default);
	char teststr1[] = "TEST";
	myTFT.TFTdrawText(0, 5, teststr1, ST7735_WHITE, ST7735_BLACK, 2);
	myTFT.TFTdrawText(0, 25, teststr1, ST7735_WHITE, ST7735_BLACK, 3);
	myTFT.TFTdrawText(0, 55, teststr1, ST7735_WHITE, ST7735_BLACK, 4);
	myTFT.TFTdrawChar(0, 85, 'G', ST7735_WHITE, ST7735_BLACK, 5);
	myTFT.TFTdrawChar(45, 85, 'L', ST7735_WHITE, ST7735_BLACK, 5);

	bcm2835_delay(TEST_DELAY2);
	myTFT.TFTfillScreen(ST7735_BLACK);
}

void Test3(void)  
{
	myTFT.TFTdrawPixel(85, 5, ST7735_WHITE);
	myTFT.TFTdrawPixel(87, 7, ST7735_WHITE);
	myTFT.TFTdrawPixel(89, 9, ST7735_WHITE);
	myTFT.TFTdrawLine(10, 10, 30, 30, ST7735_RED);
	myTFT.TFTdrawFastVLine(40, 40, 40, ST7735_GREEN);
	myTFT.TFTdrawFastHLine(60, 60, 40, ST7735_YELLOW);

	bcm2835_delay(TEST_DELAY2);
	myTFT.TFTfillScreen(ST7735_BLACK);
}

void Test4(void) {
	myTFT.TFTdrawRectWH(5, 5, 20, 20, ST7735_RED);
	myTFT.TFTfillRectangle(45, 5, 20, 20, ST7735_YELLOW);
	myTFT.TFTfillRect(85, 5, 20, 20, ST7735_GREEN);
	myTFT.TFTdrawRoundRect(15, 60, 50, 50, 5, ST7735_CYAN);
	myTFT.TFTfillRoundRect(70, 60, 50, 50, 10, ST7735_WHITE);

	bcm2835_delay(TEST_DELAY2);
	myTFT.TFTfillScreen(ST7735_BLACK);
}

void Test5(void) {
	myTFT.TFTdrawCircle(40, 20, 15, ST7735_GREEN);
	myTFT.TFTfillCircle(80, 20, 15, ST7735_YELLOW);
}

void Test6(void) {
	myTFT.TFTdrawTriangle(5, 80, 50, 40, 95, 80, ST7735_CYAN);
	myTFT.TFTfillTriangle(55, 120, 100, 90, 127, 120, ST7735_RED);

	bcm2835_delay(TEST_DELAY2);
	myTFT.TFTfillScreen(ST7735_BLACK);
}


void Test7(void) 
{
	const uint8_t LINES = 10, LINE_SIZE = 10, LINE_OFFSET = 3, TOP_FIXED = 0, BOTTOM_FIXED = 0;
	char teststr1[] = "Scroll test";
	
	for (uint8_t i = 0; i < LINES; i++)
	{
	myTFT.TFTdrawText(0, LINE_OFFSET+i*LINE_SIZE,teststr1 , ST7735_WHITE, ST7735_BLACK, 1);
	}
	myTFT.TFTsetScrollDefinition(TOP_FIXED,BOTTOM_FIXED,1);  // bottom-to-top
	uint8_t pos = LINE_OFFSET;
	for (uint8_t i = 0; i < LINES; i++) 
	{
	for (uint8_t j = 0; j < LINE_SIZE; j++) 
	{
		myTFT.TFTVerticalScroll(pos + TOP_FIXED);
		pos++;
		// check pos if necessary: must be < tftTFT_HEIGHT - TOP_FIXED - BOTTOM_FIXED
		bcm2835_delay(20);  
	}
	bcm2835_delay(TEST_DELAY1);
	}
	myTFT.TFTchangeMode(TFT_Normal_mode); 
	myTFT.TFTfillScreen(ST7735_BLACK);
}

void Test8() 
{
	char teststr1[] = "Press Play";
	//Draw play button 
	myTFT.TFTfillRoundRect(25, 10, 78, 60, 8, ST7735_WHITE);
	myTFT.TFTfillTriangle(42, 20, 42, 60, 90, 40, ST7735_RED);
	myTFT.TFTdrawText(5, 80, teststr1, ST7735_GREEN, ST7735_BLACK, 2);
	bcm2835_delay(TEST_DELAY1);
	
	// change play color
	myTFT.TFTfillTriangle(42, 20, 42, 60, 90, 40, ST7735_BLUE);
	bcm2835_delay(TEST_DELAY1);
	// change play color
	myTFT.TFTfillTriangle(42, 20, 42, 60, 90, 40, ST7735_GREEN);
	bcm2835_delay(TEST_DELAY1);
}

void Test9()
{
	char teststr0[] = "Rotate 0"; //normal
	char teststr1[] = "Rotate 90"; // 90
	char teststr2[] = "Rotate 180"; // 180
	char teststr3[] = "Rotate 270"; // 270
	
	myTFT.TFTfillScreen(ST7735_BLACK);
	myTFT.TFTsetRotation(TFT_Degress_0);
	myTFT.TFTdrawText(20, 20, teststr0, ST7735_GREEN, ST7735_BLACK, 1);
	bcm2835_delay(TEST_DELAY2);
	
	myTFT.TFTfillScreen(ST7735_BLACK);
	myTFT.TFTsetRotation(TFT_Degress_90);
	myTFT.TFTdrawText(20, 20, teststr1, ST7735_GREEN, ST7735_BLACK, 1);
	bcm2835_delay(TEST_DELAY2);
	
	myTFT.TFTfillScreen(ST7735_BLACK);
	myTFT.TFTsetRotation(TFT_Degress_180);
	myTFT.TFTdrawText(20, 20, teststr2, ST7735_GREEN, ST7735_BLACK, 1);
	bcm2835_delay(TEST_DELAY2);
	
	myTFT.TFTfillScreen(ST7735_BLACK);
	myTFT.TFTsetRotation(TFT_Degress_270);
	myTFT.TFTdrawText(20, 20, teststr3, ST7735_GREEN, ST7735_BLACK, 1);
	bcm2835_delay(TEST_DELAY2);
	
	myTFT.TFTsetRotation(TFT_Degress_0);
	myTFT.TFTchangeMode(TFT_Normal_mode);
	myTFT.TFTfillScreen(ST7735_BLACK);
}

void Test10()
{
	char teststr1[] = "Mode test";
	myTFT.TFTfillRoundRect(25, 10, 78, 60, 8, ST7735_YELLOW);
	myTFT.TFTdrawText(30, 80, teststr1, ST7735_WHITE, ST7735_RED, 1);
	bcm2835_delay(TEST_DELAY2);
	myTFT.TFTchangeMode(TFT_Normal_mode);
	 bcm2835_delay(TEST_DELAY2);
	 myTFT.TFTchangeMode(TFT_Invert_mode);
	 bcm2835_delay(TEST_DELAY2);
	 myTFT.TFTchangeMode(TFT_Normal_mode);
	 bcm2835_delay(TEST_DELAY2);
	 myTFT.TFTchangeMode(TFT_Display_off_mode);
	 bcm2835_delay(TEST_DELAY2);
	 myTFT.TFTchangeMode(TFT_Display_on_mode);
	 bcm2835_delay(TEST_DELAY2);
	 myTFT.TFTchangeMode(TFT_Sleep_mode);
	 bcm2835_delay(TEST_DELAY2);
	 myTFT.TFTchangeMode(TFT_Normal_mode);
}

void Test11(void)
{
	time_t now;
	struct tm *timenow;
	char value[10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
	uint16_t count=CLOCK_DISPLAY_TIME;
	char myStr[5];
	char teststr1[] = "G Lyons";
	
	myTFT.TFTfillScreen(ST7735_BLACK);
	
	myTFT.TFTdrawIcon(2, 2, 16, ST7735_BLACK, ST7735_WHITE, SignalIcon);
	myTFT.TFTdrawIcon(20, 2, 16, ST7735_BLACK, ST7735_WHITE, MsgIcon);
	myTFT.TFTdrawIcon(40, 2, 8, ST7735_BLACK, ST7735_WHITE, AlarmIcon);
	myTFT.TFTdrawIcon(102, 2, 16, ST7735_BLACK, ST7735_WHITE, BatIcon);
	
	myTFT.TFTdrawIcon(5, 20, 12, ST7735_GREEN , ST7735_BLACK,powerIcon);
	myTFT.TFTdrawIcon(20, 20, 12, ST7735_RED, ST7735_YELLOW, speedIcon);
	myTFT.TFTdrawBitmap(105, 20, 20 , 20, ST7735_CYAN , ST7735_BLACK, smallImage);
	
	myTFT.TFTdrawText(80, 90, teststr1, ST7735_BLUE, ST7735_BLACK, 1);
	myTFT.TFTFontNum(TFTFont_Bignum);
	while(1)
	{
		time(&now);
		timenow = localtime(&now); 
		count--; 
		sprintf(myStr, "%03d", count);
		
		myTFT.TFTdrawCharNumFont(0, 45, value[timenow->tm_hour / 10],ST7735_RED, ST7735_BLACK);
		myTFT.TFTdrawCharNumFont(16, 45, value[timenow->tm_hour % 10],ST7735_RED, ST7735_BLACK);
		myTFT.TFTdrawCharNumFont(32, 45, ':' , ST7735_GREEN, ST7735_BLACK);
		myTFT.TFTdrawCharNumFont(48, 45, value[timenow->tm_min / 10], ST7735_RED, ST7735_BLACK);
		myTFT.TFTdrawCharNumFont(64, 45, value[timenow->tm_min % 10], ST7735_RED, ST7735_BLACK);
		myTFT.TFTdrawCharNumFont(80, 45, ':' , ST7735_GREEN, ST7735_BLACK);
		myTFT.TFTdrawCharNumFont(96, 45, value[timenow->tm_sec / 10],  ST7735_RED, ST7735_BLACK);
		myTFT.TFTdrawCharNumFont(112, 45, value[timenow->tm_sec % 10],  ST7735_RED, ST7735_BLACK);
		myTFT.TFTdrawTextNumFont(0, 85, myStr, ST7735_YELLOW, ST7735_RED);
		
		if(count==1)break;
	}
	bcm2835_delay(TEST_DELAY2);
	myTFT.TFTfillScreen(ST7735_BLACK);
	myTFT.TFTFontNum(TFTFont_Default);
}

void Test12(void)
{
myTFT.TFTdrawBitmap(0, 0, 128 , 128, ST7735_WHITE , ST7735_GREEN, backupMenuBitmap);
bcm2835_delay(TEST_DELAY5);
}

// All files Windows BITMAPINFOHEADER offset 54
void Test14(void)
{
	FILE *pFile ;
	
	size_t pixelSize = 3;
	unsigned char bmpBuffer[(128 * 128) * pixelSize ];
	
	pFile = fopen("bitmap/24pic1.bmp", "r");
	if (pFile == NULL) 
	{
		printf("File does not exist\n");
		return;
	}
	fseek(pFile, 54, 0);
	fread(bmpBuffer, pixelSize, 128 * 128, pFile);
	fclose(pFile);

	myTFT.TFTdrawBitmap24(0, 0, bmpBuffer, 128, 128);

	bcm2835_delay(TEST_DELAY5);
	
	pFile = fopen("bitmap/24pic2.bmp", "r");
	if (pFile == NULL) {
		printf("File does not exist\n");
		return;
	}
	fseek(pFile, 54, 0);
	fread(bmpBuffer, pixelSize, 128 * 128, pFile);
	fclose(pFile);

	myTFT.TFTdrawBitmap24(0, 0, bmpBuffer, 128, 128);

	bcm2835_delay(TEST_DELAY5);
	
	pFile = fopen("bitmap/24pic3.bmp", "r");
	if (pFile == NULL) {
		printf("File does not exist\n");
		return;
	}
	fseek(pFile, 54, 0);
	fread(bmpBuffer, pixelSize, 128 * 128, pFile);
	fclose(pFile);

	myTFT.TFTdrawBitmap24(0, 0, bmpBuffer, 128, 128);
	
	bcm2835_delay(TEST_DELAY5);
	myTFT.TFTfillScreen(ST7735_BLACK);
	
}


void Test15(void)
{
	FILE *pFile ;
	size_t pixelSize = 2;
	unsigned char bmpBuffer1[(128 * 128) * pixelSize ];
	
	// File 1  BITMAPV5HEADER offset 132
	// made in GIMP , Color space information written 
	// RGB 565 16 bit color
	pFile = fopen("bitmap/16pic1.bmp", "r");
	if (pFile == NULL) {
		printf("File does not exist\n");
		return;
	}
	fseek(pFile, 132, 0);
	fread(bmpBuffer1, pixelSize, 128 * 128, pFile);
	fclose(pFile);
	myTFT.TFTdrawBitmap16(0, 0, bmpBuffer1, 128, 128);
	
	bcm2835_delay(TEST_DELAY5);
	
	// file 2 OS/2 OS22XBITMAPHEADER (BITMAPINFOHEADER2) offset 72
	// made in GIMP Color,  NO color space information written 
	// RGB 565 16 bit color
	pFile = fopen("bitmap/16pic2.bmp", "r");
	if (pFile == NULL) {
		printf("File does not exist\n");
		return;
	}
	fseek(pFile, 72, 0);
	fread(bmpBuffer1, pixelSize, 128 * 128, pFile);
	fclose(pFile);
	myTFT.TFTdrawBitmap16(0, 0, bmpBuffer1, 128, 128);
	
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
	fread(bmpBuffer1, pixelSize, 128 * 128, pFile);
	fclose(pFile);
	myTFT.TFTdrawBitmap16(0, 0, bmpBuffer1, 128, 128);
	
	bcm2835_delay(TEST_DELAY5);
	myTFT.TFTfillScreen(ST7735_BLACK);
	
}

void TestFPS(void) {
	// Clear The Screen
	myTFT.TFTfillRectangle(0, 0, 160, 80, ST7735_BLACK);

	// Load images into buffers
	uint8_t* img[5] = { 
		loadImage((char*)"bitmap/title.bmp"),
		loadImage((char*)"bitmap/menu.bmp"),
		loadImage((char*)"bitmap/game1.bmp"),
		loadImage((char*)"bitmap/game2.bmp"),
		loadImage((char*)"bitmap/game3.bmp")
	};

	int64_t start = getTime(), duration = 0;
	uint32_t frames = 0;
	double fps = 0;

	// Run for ~10sec
	while(duration < 10000000) {
		myTFT.TFTdrawBitmap24(0, 0, img[frames % 5], 160, 80);

		duration = getTime() - start;

		if((++frames % 50) == 0) {
			fps = (double)frames / ((double)duration / 1000000);
			printf("%.2ffps\n", fps);
		}
	}

	// Get final Stats and print
	duration = getTime() - start;
	fps = (double)frames / ((double)duration / 1000000);
	printf("%d frames, %lld sec, %.2f fps\n", frames, duration / 1000000, fps);

	// Free Up Buffers
	for(int i=0; i<5; i++) free(img[i]);
}


void EndTests(void)
{
	char teststr1[] = "Tests over";
	myTFT.TFTfillScreen(ST7735_BLACK);
	myTFT.TFTdrawText(5, 50, teststr1, ST7735_GREEN, ST7735_BLACK, 2);
	bcm2835_delay(TEST_DELAY5);
	myTFT.TFTPowerDown(); // Power down device
	bcm2835_close(); // Close the bcm2835 library
	printf("TFT End\r\n");
}

int64_t getTime() {
	struct timespec tms;
    if (clock_gettime(CLOCK_REALTIME,&tms)) return -1;
    int64_t micros = tms.tv_sec * 1000000;
    micros += tms.tv_nsec/1000;
    if (tms.tv_nsec % 1000 >= 500) ++micros;
    return micros;
}

uint8_t* loadImage(char* name) {
	FILE *pFile ;
	size_t pixelSize = 3;
	uint8_t* bmpBuffer1 = NULL;

	pFile = fopen(name, "r");
	if (pFile == NULL) {
		printf("File does not exist\n");
	} else {
		bmpBuffer1 = (uint8_t*)malloc((160 * 80) * pixelSize);
		fseek(pFile, 132, 0);
		fread(bmpBuffer1, pixelSize, 160 * 80, pFile);
		fclose(pFile);
	}
	
	return bmpBuffer1;
}

// *************** EOF ****************
