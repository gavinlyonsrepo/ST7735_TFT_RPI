/*! 
	@file src/Tests/main.cpp
	@brief Library test file, tests text,fonts, bitmaps and functions
	@author Gavin Lyons.
	@note See USER OPTIONS 1-3 in SETUP function
	@test
	-# Test 1  print out  fonts 1-6
	-# Test 1A defined 16-bit Colors, text
	-# Test 1B print entire ASCII font 0 to 254, default font
	-# Test 1C print numbers int and float using draw functions
	-# Test 1D print class methods
	-# Test 1E print out font 7 & 8 using draw functions
	-# Test 2  font sizes (2-5) + character draw using draw functions
	-# Test 3  pixels and lines
	-# Test 4  rectangles 
	-# Test 5  Circle
	-# Test 6  Triangles 
	-# Test 7  scroll
	-# Test 8  More shapes, media buttons graphic.
	-# Test 9  Rotate
	-# Test 10 change modes test -> Invert, display on/off and Sleep.
	-# Test 11 "clock demo" , icons, , font 7
	-# Test 12 bi-color full screen image 128x128
	-# Test 15 24 bit color image bitmaps from the file system
	-# Test 16 16 bit colorimage bitmaps from the file system

*/

// Section ::  libraries 
#include <bcm2835.h> // for SPI GPIO and delays.
#include <time.h> // for test 11
#include "ST7735_TFT.hpp"
#include "Bi_Color_Bitmap_Data.hpp" // Data for test 11 and 12.

// Section :: Defines   
//  Test timing related defines 
#define TEST_DELAY1 1000
#define TEST_DELAY2 2000
#define TEST_DELAY5 5000
#define CLOCK_DISPLAY_TIME 100

// Section :: Globals 
ST7735_TFT myTFT;

//  Section ::  Function Headers 

int8_t Setup(void); // setup + user options
void Test0(void);  // Print out all fonts 1-6
void Test1A(void); // defined 16-bit Colors, text
void Test1B(void); // print entire ASCII font 0 to 127, default font
void Test1C(void); // print numbers int and float using draw functions
void Test1D(void); // print numbers int and float using PRINT function
void Test1E(void); // Print out font 7-10 using drawFontNum functions
void Test2(void);  // font sizes(1-4) + character draw using draw functions
void Test3(void);  // pixels and lines
void Test4(void);  // rectangles 
void Test5(void);  // Circle
void Test6(void);  // Triangles 
void Test7(void);  // scroll
void Test8(void);  // More shapes, media buttons graphic.
void Test9(void);  // Rotate
void Test10(void); // change modes test -> Invert, display on/off and Sleep.
void Test11(void); // "clock demo" icons, small bi-color bitmaps, font 7-8
void Test12(void); // 2 color bitmap
void Test15(void); // 24 color bitmap
void Test16(void); // 16 color bitmap 
void EndTests(void);

//  Section ::  MAIN loop

int main(void) 
{

	if(!Setup())return -1;
	
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
	Test15();
	Test16();
	
	EndTests();
	return 0;
}
// *** End OF MAIN **


//  Section ::  Function Space 

int8_t Setup(void)
{

	TFT_MILLISEC_DELAY(TEST_DELAY1);
	std::cout << "TFT Start!" << std::endl;
	if(!bcm2835_init())
	{
		std::cout << "Error : Problem with init bcm2835 library" << std::endl;
		return -1;
	}
	
// ** USER OPTION 1 GPIO/SPI TYPE HW OR SW **
	int8_t RST_TFT  = 25;
	int8_t DC_TFT   = 24;
	int8_t SCLK_TFT = -1; // 5, change to GPIO no for sw spi, -1 hw spi
	int8_t SDIN_TFT = -1; // 6, change to GPIO no for sw spi, -1 hw spi
	int8_t CS_TFT   = -1 ;  // 8, change to GPIO no for sw spi, -1 hw spi
	myTFT.TFTSetupGPIO(RST_TFT, DC_TFT, CS_TFT, SCLK_TFT, SDIN_TFT);
//*********************************************

// ** USER OPTION 2 Screen Setup **
	uint8_t OFFSET_COL = 0;  // 2, These offsets can be adjusted for any issues->
	uint8_t OFFSET_ROW = 0; // 3, with manufacture tolerance/defects
	uint16_t TFT_WIDTH = 128;// Screen width in pixels
	uint16_t TFT_HEIGHT = 128; // Screen height in pixels
	myTFT.TFTInitScreenSize(OFFSET_COL, OFFSET_ROW , TFT_WIDTH , TFT_HEIGHT);
// ***********************************

// ** USER OPTION 3 PCB_TYPE + SPI baud rate + SPI_CE_PIN**
	uint32_t SCLK_FREQ =  8000000 ; // HW Spi freq in Hertz , MAX 125 Mhz MIN 30Khz
	uint8_t SPI_CE_PIN = 0; // which HW SPI chip enable pin to use,  0 or 1
	// pass enum to param1 ,4 choices,see README
	if(!myTFT.TFTInitPCBType(myTFT.TFT_ST7735R_Red, SCLK_FREQ, SPI_CE_PIN))return -1;
	// Note : if using SW SPI you do not have to pass anything for param 2&3, it will do nothing. 
//*****************************
	return 0;
}


void Test0(void) {

	std::cout << "Test 1: Print out  fonts 1-6" << std::endl;
	char teststr1[] = "Default 1";
	char teststr2[] = "THICK 2";
	char teststr3[] = "Seven 3";
	char teststr4[] = "WIDE 4";
	char teststr5[] = "Tiny 5";
	char teststr6[] = "Home 6";
	
	myTFT.TFTfillScreen(ST7735_BLACK);
	
	myTFT.TFTFontNum(myTFT.TFTFont_Default);
	myTFT.TFTdrawText(0, 4, teststr1, ST7735_WHITE, ST7735_BLACK, 2);
	myTFT.TFTFontNum(myTFT.TFTFont_Thick);
	myTFT.TFTdrawText(0, 20, teststr2, ST7735_GREEN, ST7735_BLACK, 2);
	myTFT.TFTFontNum(myTFT.TFTFont_Seven_Seg);
	myTFT.TFTdrawText(0, 36, teststr3, ST7735_BLUE, ST7735_BLACK, 2);
	myTFT.TFTFontNum(myTFT.TFTFont_Wide);
	myTFT.TFTdrawText(0, 52, teststr4, ST7735_CYAN, ST7735_BLACK, 2);
	myTFT.TFTFontNum(myTFT.TFTFont_Tiny);
	myTFT.TFTdrawText(0, 68, teststr5, ST7735_RED, ST7735_BLACK, 2);
	myTFT.TFTFontNum(myTFT.TFTFont_HomeSpun);
	myTFT.TFTdrawText(0, 84, teststr6, ST7735_YELLOW, ST7735_BLACK, 2);
	TFT_MILLISEC_DELAY(TEST_DELAY5);
	myTFT.TFTfillScreen(ST7735_BLACK);
	myTFT.TFTFontNum(myTFT.TFTFont_Default);
}

void Test1A(void) {
	std::cout << "Test 1A: Some of the Defined 16-bit Colors for text" << std::endl;
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
	char teststr11[] = "ORANGE";
	myTFT.TFTdrawText(5, 5, teststr1, ST7735_WHITE, ST7735_BLACK, 1);
	myTFT.TFTdrawText(5, 15, teststr2, ST7735_BLUE, ST7735_BLACK, 1);
	myTFT.TFTdrawText(5, 25, teststr3, ST7735_RED, ST7735_BLACK, 1);
	myTFT.TFTdrawText(5, 35, teststr4, ST7735_GREEN, ST7735_BLACK, 1);
	myTFT.TFTdrawText(5, 45, teststr5, ST7735_CYAN, ST7735_BLACK, 1);
	myTFT.TFTdrawText(5, 55, teststr6, ST7735_MAGENTA, ST7735_BLACK, 1);
	myTFT.TFTdrawText(5, 65, teststr7, ST7735_YELLOW, ST7735_BLACK, 1);
	myTFT.TFTdrawText(5, 75, teststr8, ST7735_GREY, ST7735_BLACK, 1);
	myTFT.TFTdrawText(5, 85, teststr9, ST7735_TAN, ST7735_BLACK, 1);
	myTFT.TFTdrawText(5, 95, teststr10 , ST7735_BROWN, ST7735_BLACK, 1);
	myTFT.TFTdrawText(5, 105, teststr11 , ST7735_ORANGE, ST7735_BLACK, 1);
	TFT_MILLISEC_DELAY(TEST_DELAY5);
	myTFT.TFTfillScreen(ST7735_BLACK);
}

void Test1B(void) {
	std::cout << "Test 1B: Print entire ASCII font 0 to 254, default font" << std::endl;
	uint8_t row = 5;
	uint8_t col = 5;
	for (char i = 0; i < 126; i++) {
		
		myTFT.TFTdrawChar(col, row, i, ST7735_GREEN, ST7735_BLACK, 1);
		col += 10;
		if (col > 115) {
			row += 10;
			col = 5;
		}
	}
	TFT_MILLISEC_DELAY(TEST_DELAY5);
	myTFT.TFTfillScreen(ST7735_BLACK);
	
	row = 5;
	col = 5;
	for (unsigned char j = 127; j < 254; j++) {
		
		myTFT.TFTdrawChar(col, row, j, ST7735_GREEN, ST7735_BLACK, 1);
		col += 10;
		if (col > 115) {
			row += 10;
			col = 5;
		}
	}
	TFT_MILLISEC_DELAY(TEST_DELAY5);
	myTFT.TFTfillScreen(ST7735_BLACK);
}


void Test1C(void)
{
	std::cout << "Test 1C: Print numbers, int and float using draw functions" << std::endl;
	int myInt=931;
	char myStr[5];
	myTFT.TFTFontNum(myTFT.TFTFont_Seven_Seg);
	sprintf(myStr, "%d", myInt);
	myTFT.TFTdrawText(5, 5, myStr, ST7735_BLUE, ST7735_BLACK, 3);

	float  myPI = 3.171592;
	char myStr2[8];
	sprintf(myStr2, "%0.3f", myPI); // 3.172
	myTFT.TFTdrawText(5, 65, myStr2, ST7735_RED, ST7735_BLACK, 3);
	
	TFT_MILLISEC_DELAY(TEST_DELAY2);
	myTFT.TFTfillScreen(ST7735_BLACK);

}


void Test1D(void){

	std::cout << "Test 1D: Print class methods" << std::endl;
	myTFT.setTextSize(1);  // Test a string with print 
	myTFT.TFTsetCursor(10,10);
	myTFT.TFTFontNum(myTFT.TFTFont_Default);
	myTFT.print("Hello ");
	
	myTFT.TFTFontNum(myTFT.TFTFont_Thick);
	myTFT.TFTsetCursor(50,10); // Test a int with print 
	myTFT.print(1243);
	
	myTFT.setTextSize(2); 	// Test a -int with print inverted size 2
	myTFT.setTextColor(ST7735_RED, ST7735_YELLOW);
	myTFT.TFTfillRectangle(5, 23, 120, 17, ST7735_YELLOW);
	myTFT.TFTsetCursor(5,25);
	myTFT.TFTFontNum(myTFT.TFTFont_Seven_Seg);
	myTFT.print(-49);
	
	myTFT.TFTsetCursor(45,25); // Test a float 
	myTFT.TFTFontNum(myTFT.TFTFont_Wide);
	myTFT.print(3.1745, 1); // print 3.2
	
	myTFT.TFTsetCursor(10,55); // Test float bignum font
	myTFT.TFTFontNum(myTFT.TFTFont_Bignum);
	myTFT.print(5.16);
	
	myTFT.TFTsetCursor(10,95); // Test float  mednum font
	myTFT.setTextColor(ST7735_WHITE, ST7735_BLACK);
	myTFT.TFTFontNum(myTFT.TFTFont_Mednum);
	myTFT.print(76.88);
	
	TFT_MILLISEC_DELAY(TEST_DELAY5);
	myTFT.TFTfillScreen(ST7735_BLACK);
	
	myTFT.TFTsetCursor(10,5); // Test Arial round font 9 
	myTFT.setTextColor(ST7735_WHITE, ST7735_BLACK);
	myTFT.TFTFontNum(myTFT.TFTFont_ArialRound);
	myTFT.print("A round");
	
	myTFT.TFTsetCursor(10,50); // Test Arial bold font 10 
	myTFT.setTextColor(ST7735_WHITE, ST7735_BLACK);
	myTFT.TFTFontNum(myTFT.TFTFont_ArialBold);
	myTFT.print("A bold");
	
	TFT_MILLISEC_DELAY(TEST_DELAY5);
	myTFT.TFTfillScreen(ST7735_BLACK);
	
	// Test print with DEC BIN OCT HEX 
	uint8_t numPos = 47;
	myTFT.TFTFontNum(myTFT.TFTFont_HomeSpun);
	myTFT.TFTsetCursor(5,5); 
	myTFT.print(numPos , DEC); // 47
	myTFT.TFTsetCursor(5,25); 
	myTFT.print(numPos , BIN); // 10111
	myTFT.TFTsetCursor(5,45); 
	myTFT.print(numPos , OCT); // 57
	myTFT.TFTsetCursor(5,65); 
	myTFT.print(numPos , HEX); // 2F
	
	TFT_MILLISEC_DELAY(TEST_DELAY5);
	myTFT.TFTfillScreen(ST7735_BLACK);
	
	// Test print a string object with print
	std::string timeInfo = "12:45";
	std::string newLine = "new l";
	myTFT.TFTsetCursor(5, 5);
	myTFT.print(timeInfo);
	// print a new line with println 
	myTFT.TFTsetCursor(5,40);
	myTFT.println(newLine); // print a new line feed with println
	myTFT.print(newLine);

	TFT_MILLISEC_DELAY(TEST_DELAY5);
	myTFT.TFTfillScreen(ST7735_BLACK);
}

void Test1E(void)
{
	std::cout << "Test 1E: print out font 7 - 10 using draw functions" << std::endl;
	// Note fonts 7 and 8 are numbers only + : 
	// Note Fonts 9 and 10 are Alphanumeric 
	char teststr1[] = "12:81";
	char teststr2[] = "72:83";
	char teststr3[] = "9 rnd";
	char teststr4[] = "10 bold";
	
	myTFT.TFTFontNum(myTFT.TFTFont_Bignum);
	myTFT.TFTdrawCharNumFont(2, 2, '7',  ST7735_RED, ST7735_BLACK);
	myTFT.TFTdrawTextNumFont(2, 40, teststr1, ST7735_YELLOW, ST7735_RED);
	
	myTFT.TFTFontNum(myTFT.TFTFont_Mednum);
	myTFT.TFTdrawCharNumFont(2, 75, '8',  ST7735_WHITE, ST7735_BLACK);
	myTFT.TFTdrawTextNumFont(2, 100, teststr2, ST7735_GREEN, ST7735_RED);
	
	TFT_MILLISEC_DELAY(TEST_DELAY5);
	myTFT.TFTfillScreen(ST7735_BLACK);
	
	myTFT.TFTFontNum(myTFT.TFTFont_ArialRound);
	myTFT.TFTdrawCharNumFont(2, 2, '9',  ST7735_RED, ST7735_BLACK);
	myTFT.TFTdrawTextNumFont(2, 26, teststr3, ST7735_YELLOW, ST7735_RED);
	
	myTFT.TFTFontNum(myTFT.TFTFont_ArialBold);
	myTFT.TFTdrawCharNumFont(2, 56, 'A',  ST7735_WHITE, ST7735_BLACK);
	myTFT.TFTdrawTextNumFont(2, 90, teststr4, ST7735_GREEN, ST7735_RED);
	
	TFT_MILLISEC_DELAY(TEST_DELAY5);
	myTFT.TFTfillScreen(ST7735_BLACK);
}

void Test2(void) {
	std::cout << "Test 2: font sizes (2-5) + character draw using draw functions" << std::endl;
	myTFT.TFTFontNum(myTFT.TFTFont_Default);
	char teststr1[] = "TEST";
	myTFT.TFTdrawText(0, 5, teststr1, ST7735_WHITE, ST7735_BLACK, 2);
	myTFT.TFTdrawText(0, 25, teststr1, ST7735_WHITE, ST7735_BLACK, 3);
	myTFT.TFTdrawText(0, 55, teststr1, ST7735_WHITE, ST7735_BLACK, 4);
	myTFT.TFTdrawChar(0, 85, 'G', ST7735_WHITE, ST7735_BLACK, 5);
	myTFT.TFTdrawChar(45, 85, 'L', ST7735_WHITE, ST7735_BLACK, 5);

	TFT_MILLISEC_DELAY(TEST_DELAY2);
	myTFT.TFTfillScreen(ST7735_BLACK);
}

void Test3(void)  
{
	std::cout << "Test 3: pixels and lines" << std::endl;
	myTFT.TFTdrawPixel(85, 5, ST7735_WHITE);
	myTFT.TFTdrawPixel(87, 7, ST7735_WHITE);
	myTFT.TFTdrawPixel(89, 9, ST7735_WHITE);
	myTFT.TFTdrawLine(10, 10, 30, 30, ST7735_RED);
	myTFT.TFTdrawFastVLine(40, 40, 40, ST7735_GREEN);
	myTFT.TFTdrawFastHLine(60, 60, 40, ST7735_YELLOW);

	TFT_MILLISEC_DELAY(TEST_DELAY2);
	myTFT.TFTfillScreen(ST7735_BLACK);
}

void Test4(void) {
	std::cout << "Test 4: rectangles " << std::endl;
	myTFT.TFTdrawRectWH(5, 5, 20, 20, ST7735_RED);
	myTFT.TFTfillRectangle(45, 5, 20, 20, ST7735_YELLOW);
	myTFT.TFTfillRect(85, 5, 20, 20, ST7735_GREEN);
	myTFT.TFTdrawRoundRect(15, 60, 50, 50, 5, ST7735_CYAN);
	myTFT.TFTfillRoundRect(70, 60, 50, 50, 10, ST7735_WHITE);

	TFT_MILLISEC_DELAY(TEST_DELAY2);
	myTFT.TFTfillScreen(ST7735_BLACK);
}

void Test5(void) {
	std::cout << "Test 5 & 6: Triangles and circles" << std::endl;
	myTFT.TFTdrawCircle(40, 20, 15, ST7735_GREEN);
	myTFT.TFTfillCircle(80, 20, 15, ST7735_YELLOW);
}

void Test6(void) {
	myTFT.TFTdrawTriangle(5, 80, 50, 40, 95, 80, ST7735_CYAN);
	myTFT.TFTfillTriangle(55, 120, 100, 90, 127, 120, ST7735_RED);

	TFT_MILLISEC_DELAY(TEST_DELAY2);
	myTFT.TFTfillScreen(ST7735_BLACK);
}


void Test7(void) 
{
	std::cout << "Test 7: Scroll" << std::endl;
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
		}
	TFT_MILLISEC_DELAY(TEST_DELAY1);
	}
	myTFT.TFTchangeMode(myTFT.TFT_Normal_mode); 
	myTFT.TFTfillScreen(ST7735_BLACK);
}

void Test8() 
{
	std::cout << "Test 8: More shapes, media buttons graphic." << std::endl;
	char teststr1[] = "Press Play";
	//Draw play button 
	myTFT.TFTfillRoundRect(25, 10, 78, 60, 8, ST7735_WHITE);
	myTFT.TFTfillTriangle(42, 20, 42, 60, 90, 40, ST7735_RED);
	myTFT.TFTdrawText(5, 80, teststr1, ST7735_GREEN, ST7735_BLACK, 2);
	TFT_MILLISEC_DELAY(TEST_DELAY1);
	
	// change play color
	myTFT.TFTfillTriangle(42, 20, 42, 60, 90, 40, ST7735_GREEN);
	TFT_MILLISEC_DELAY(TEST_DELAY1);
	// change play color
	myTFT.TFTfillTriangle(42, 20, 42, 60, 90, 40, ST7735_BLUE);
	TFT_MILLISEC_DELAY(TEST_DELAY1);
}

void Test9()
{
	std::cout << "Test 9: Rotate" << std::endl;
	char teststr0[] = "Rotate 0"; //normal
	char teststr1[] = "Rotate 90"; // 90
	char teststr2[] = "Rotate 180"; // 180
	char teststr3[] = "Rotate 270"; // 270
	
	myTFT.TFTfillScreen(ST7735_BLACK);
	myTFT.TFTsetRotation(myTFT.TFT_Degrees_0);
	myTFT.TFTdrawText(20, 20, teststr0, ST7735_GREEN, ST7735_BLACK, 1);
	TFT_MILLISEC_DELAY(TEST_DELAY2);
	
	myTFT.TFTfillScreen(ST7735_BLACK);
	myTFT.TFTsetRotation(myTFT.TFT_Degrees_90);
	myTFT.TFTdrawText(20, 20, teststr1, ST7735_GREEN, ST7735_BLACK, 1);
	TFT_MILLISEC_DELAY(TEST_DELAY2);
	
	myTFT.TFTfillScreen(ST7735_BLACK);
	myTFT.TFTsetRotation(myTFT.TFT_Degrees_180);
	myTFT.TFTdrawText(20, 20, teststr2, ST7735_GREEN, ST7735_BLACK, 1);
	TFT_MILLISEC_DELAY(TEST_DELAY2);
	
	myTFT.TFTfillScreen(ST7735_BLACK);
	myTFT.TFTsetRotation(myTFT.TFT_Degrees_270);
	myTFT.TFTdrawText(20, 20, teststr3, ST7735_GREEN, ST7735_BLACK, 1);
	TFT_MILLISEC_DELAY(TEST_DELAY2);
	
	myTFT.TFTsetRotation(myTFT.TFT_Degrees_0);
	myTFT.TFTchangeMode(myTFT.TFT_Normal_mode);
	myTFT.TFTfillScreen(ST7735_BLACK);
}

void Test10()
{
	std::cout << "Test 10-1: Mode Tests" << std::endl;
	char teststr1[] = "Mode test";
	myTFT.TFTfillRoundRect(25, 10, 78, 60, 8, ST7735_YELLOW);
	myTFT.TFTdrawText(30, 80, teststr1, ST7735_WHITE, ST7735_RED, 1);
	TFT_MILLISEC_DELAY(TEST_DELAY5);
	myTFT.TFTchangeMode(myTFT.TFT_Normal_mode);
	TFT_MILLISEC_DELAY(TEST_DELAY5);
	myTFT.TFTchangeMode(myTFT.TFT_Invert_mode);
	std::cout << "Test 10-2: Mode Invert" << std::endl;
	TFT_MILLISEC_DELAY(TEST_DELAY5);
	myTFT.TFTchangeMode(myTFT.TFT_Normal_mode);
	std::cout << "Test 10-3: Mode Normal" << std::endl;
	TFT_MILLISEC_DELAY(TEST_DELAY5);
	myTFT.TFTchangeMode(myTFT.TFT_Display_off_mode);
	std::cout << "Test 10-4: Mode Display off" << std::endl;
	TFT_MILLISEC_DELAY(TEST_DELAY5);
	myTFT.TFTchangeMode(myTFT.TFT_Display_on_mode);
	std::cout << "Test 10-5: Mode Display on" << std::endl;
	TFT_MILLISEC_DELAY(TEST_DELAY5);
	myTFT.TFTchangeMode(myTFT.TFT_Sleep_mode);
	std::cout << "Test 10-6: Mode Sleep on" << std::endl;
	TFT_MILLISEC_DELAY(TEST_DELAY5);
	myTFT.TFTchangeMode(myTFT.TFT_Normal_mode);
	std::cout << "Test 10-6: Mode Normal" << std::endl;
}

void Test11(void)
{
	std::cout << "Test 11: clock demo , icons, , font 7" << std::endl;
	time_t now;
	struct tm *timenow;
	char value[10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
	uint16_t count=CLOCK_DISPLAY_TIME;
	if (count > 999) count = 999; 
	char myStr[5];
	char teststr1[] = "G Lyons";
	
	myTFT.TFTfillScreen(ST7735_BLACK);
	
	myTFT.TFTdrawIcon(2, 2, 16, ST7735_BLACK, ST7735_WHITE, pSignalIcon);
	myTFT.TFTdrawIcon(20, 2, 16, ST7735_BLACK, ST7735_WHITE, pMsgIcon);
	myTFT.TFTdrawIcon(40, 2, 8, ST7735_BLACK, ST7735_WHITE, pAlarmIcon);
	myTFT.TFTdrawIcon(102, 2, 16, ST7735_BLACK, ST7735_WHITE, pBatIcon);
	
	myTFT.TFTdrawIcon(5, 20, 12, ST7735_GREEN , ST7735_BLACK, pPowerIcon);
	myTFT.TFTdrawIcon(20, 20, 12, ST7735_RED, ST7735_YELLOW, pSpeedIcon);
	myTFT.TFTdrawBitmap(105, 20, 20 , 20, ST7735_CYAN , ST7735_BLACK, (uint8_t *)pSmallImage);
	
	myTFT.TFTdrawText(80, 90, teststr1, ST7735_BLUE, ST7735_BLACK, 1);
	myTFT.TFTFontNum(myTFT.TFTFont_Bignum);
	while(1)
	{
		time(&now);
		timenow = localtime(&now); 
		count--; 
		snprintf(myStr, sizeof(myStr), "%03u", count);
		
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
	TFT_MILLISEC_DELAY(TEST_DELAY2);
	myTFT.TFTfillScreen(ST7735_BLACK);
	myTFT.TFTFontNum(myTFT.TFTFont_Default);
}

void Test12(void)
{
	std::cout << "Test 12: Bi-color bitmap" << std::endl;
	myTFT.TFTfillScreen(ST7735_BLACK);
	char teststr1[] = "Bitmap 2 ";
	myTFT.TFTdrawText(5, 5, teststr1, ST7735_WHITE, ST7735_BLACK, 2);
	TFT_MILLISEC_DELAY(TEST_DELAY2);
	myTFT.TFTdrawBitmap(0, 0, 128 , 128, ST7735_WHITE , ST7735_GREEN, (uint8_t *)pBackupMenuBitmap);
	TFT_MILLISEC_DELAY(TEST_DELAY5);
}

// bitmap 24 colour , All files format = Windows BITMAPINFOHEADER offset 54
void Test15(void)
{
	std::cout << "Test 15: 24 bit color image bitmaps from the file system" << std::endl;
	myTFT.TFTfillScreen(ST7735_BLACK);
	char teststr1[] = "Bitmap 24";
	myTFT.TFTdrawText(5, 5, teststr1, ST7735_WHITE, ST7735_BLACK, 2);
	TFT_MILLISEC_DELAY(TEST_DELAY1);
	
	FILE *pFile ;
	size_t pixelSize = 3;
	uint8_t* bmpBuffer = NULL;
	bmpBuffer = (uint8_t*)malloc((128 * 128) * pixelSize);
	if (bmpBuffer == NULL)
	{
		std::cout << "Error Test15 : MALLOC could not assign memory " << std::endl;
		return;
	}
	for (uint8_t i = 0 ; i < 3 ; i++)
	{
		switch (i) // select file
		{
			case 0: pFile = fopen("bitmap/bitmap24images/24pic1.bmp", "r"); break;
			case 1: pFile = fopen("bitmap/bitmap24images/24pic2.bmp", "r"); break;
			case 2: pFile = fopen("bitmap/bitmap24images/24pic3.bmp", "r"); break;
		}
		
		if (pFile == NULL)  // Check file exists
		{
			std::cout << "Error Test15: File does not exist" << std::endl;
			return;
		}
		
		fseek(pFile, 54, 0); // Put file in Buffer
		fread(bmpBuffer, pixelSize, 128 * 128, pFile);
		fclose(pFile);

		myTFT.TFTdrawBitmap24(0, 0, bmpBuffer, 128, 128); 
		TFT_MILLISEC_DELAY(TEST_DELAY5);
	}
	free(bmpBuffer);  // Free Up Buffer
}

// test function for 16 bit color bitmaps made in GIMP (RGB 565 16 bit color) 
// 3 files 
// File 1 16pic1.bmp BITMAPV5HEADER offset 132
// Color space information written 
// File 2&3 16pic2.bmp & 16pic3.bmp 
// OS/2 OS22XBITMAPHEADER (BITMAPINFOHEADER2) offset 72
// NO color space information written 

void Test16(void)
{
	std::cout << "Test 16: 16 bit color image bitmaps from the file system" << std::endl;
	myTFT.TFTfillScreen(ST7735_BLACK);
	char teststr1[] = "Bitmap 16";
	myTFT.TFTdrawText(5, 5, teststr1, ST7735_WHITE, ST7735_BLACK, 2);
	TFT_MILLISEC_DELAY(TEST_DELAY2);
	
	FILE *pFile ;
	size_t pixelSize = 2;
	uint8_t offsetBMPHeader = 0;
	uint8_t* bmpBuffer1 = NULL;
	bmpBuffer1 = (uint8_t*)malloc((128 * 128) * pixelSize);
	
	if (bmpBuffer1 == NULL)
	{
		std::cout << "Error Test16 : MALLOC could not assign memory " << std::endl;
		return;
	}
	
	for (uint8_t i = 0 ; i < 3 ; i++)
	{
		switch (i) // select file
		{
			case 0: 
				pFile = fopen("bitmap/bitmap16images/16pic1.bmp", "r"); 
				offsetBMPHeader = 132;
			break;
			case 1: pFile = fopen("bitmap/bitmap16images/16pic2.bmp", "r"); break;
			case 2: pFile = fopen("bitmap/bitmap16images/16pic3.bmp", "r"); break;
		}
		if (pFile == NULL) 
		{
			std::cout << "Error Test16 : File does not exist" << std::endl;
			return;
		}
		fseek(pFile, offsetBMPHeader, 0);
		fread(bmpBuffer1, pixelSize, 128 * 128, pFile);
		fclose(pFile);
		
		myTFT.TFTdrawBitmap16(0, 0, bmpBuffer1, 128, 128);
		TFT_MILLISEC_DELAY(TEST_DELAY5);
		offsetBMPHeader = 72;
	} // end of for loop
	
	free(bmpBuffer1); // Free Up Buffer
	myTFT.TFTfillScreen(ST7735_BLACK);
} // end of test 15


void EndTests(void)
{
	char teststr1[] = "Tests over";
	myTFT.TFTfillScreen(ST7735_BLACK);
	myTFT.TFTdrawText(5, 50, teststr1, ST7735_GREEN, ST7735_BLACK, 2);
	TFT_MILLISEC_DELAY(TEST_DELAY5);
	myTFT.TFTPowerDown(); // Power down device
	bcm2835_close(); // Close the bcm2835 library
	std::cout << "TFT End" << std::endl;
}

// *************** EOF ****************
