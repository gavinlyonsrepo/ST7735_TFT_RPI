/*!
	@file src/Bitmap_Tests/main.cpp
	@brief Library test file, bitmaps
	@author Gavin Lyons.
	@note See USER OPTIONS 1-3 in SETUP function
	@test
	-# Test 401 "clock demo" , icons, small bitmap, font 7
	-# Test 402 bi-color full screen image 128x128
	-# Test 403 24 bit color image bitmaps from the file system
	-# Test 404 16 bit colorimage bitmaps from the file system

*/

// Section ::  libraries
#include <bcm2835.h> // for SPI GPIO and delays.
#include <ctime> // for test 401
#include "Bi_Color_Bitmap_Data.hpp" // Data for test 401-402
#include "ST7735_TFT.hpp"

// Section :: Defines
//  Test timing related defines
#define TEST_DELAY1 1000
#define TEST_DELAY2 2000
#define TEST_DELAY5 5000
#define CLOCK_DISPLAY_TIME 100

// Section :: Globals
ST7735_TFT myTFT;

//  Section ::  Function Headers

uint8_t Setup(void); // setup + user options
void Test401(void); // "clock demo" icons, small bi-color bitmaps, font 7-8
void Test402(void); // 2 color bitmap
void Test403(void); // 24 color bitmap
void Test404(void); // 16 color bitmap
void EndTests(void);

//  Section ::  MAIN loop

int main(void)
{

	if(Setup() != 0)return -1;

	Test401();
	Test402();
	Test403();
	Test404();

	EndTests();
	return 0;
}
// *** End OF MAIN **


//  Section ::  Function Space

uint8_t Setup(void)
{
	std::cout << "TFT Start" << std::endl;
	if(!bcm2835_init())
	{
		std::cout << "Error 1201 Problem with init bcm2835 library" << std::endl;
		return 2;
	}else{
		std::cout <<"bcm2835 library version :" << bcm2835_version() << std::endl;
	}

// ** USER OPTION 1 GPIO/SPI TYPE HW SPI **
	int8_t RST_TFT  = 25;
	int8_t DC_TFT   = 24;
	myTFT.TFTSetupGPIO(RST_TFT, DC_TFT);
//*********************************************

// ** USER OPTION 2 Screen Setup **
	uint8_t OFFSET_COL = 0;  // 2, These offsets can be adjusted for any issues->
	uint8_t OFFSET_ROW = 0; // 3, with manufacture tolerance/defects
	uint16_t TFT_WIDTH = 128;// Screen width in pixels
	uint16_t TFT_HEIGHT = 128; // Screen height in pixels
	myTFT.TFTInitScreenSize(OFFSET_COL, OFFSET_ROW , TFT_WIDTH , TFT_HEIGHT);
// ***********************************

// ** USER OPTION 3 PCB_TYPE + SPI baud rate + SPI_CE_PIN**
	uint32_t SCLK_FREQ =  8000000 ; //  freq in Hertz , MAX 125 Mhz MIN 30Khz
	uint8_t SPI_CE_PIN = 0; // which HW SPI chip enable pin to use,  0 or 1
	// pass enum to param1 ,4 choices,see README
	if(myTFT.TFTInitPCBType(myTFT.TFT_ST7735R_Red, SCLK_FREQ, SPI_CE_PIN) != 0)
	{
		bcm2835_close(); //Close lib & /dev/mem, deallocating mem
		return 3;
	}
//*****************************
	std::cout << "ST7735 library version : " << myTFT.TFTLibVerNumGet()<< std::endl;
	TFT_MILLISEC_DELAY(50);
	return 0;
}


void Test401(void)
{
	std::cout << "Test 401: clock demo , icons, small bitmap, font 7" << std::endl;
	time_t now;
	struct tm *timenow;
	char value[10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
	uint16_t count=CLOCK_DISPLAY_TIME;
	if (count > 999) count = 999;
	char myStr[7];
	char teststr1[] = "G Lyons";

	myTFT.TFTfillScreen(ST7735_BLACK);

	myTFT.TFTdrawIcon(2, 2, 16, ST7735_BLACK, ST7735_WHITE, pSignalIcon);
	myTFT.TFTdrawIcon(20, 2, 16, ST7735_BLACK, ST7735_WHITE, pMsgIcon);
	myTFT.TFTdrawIcon(40, 2, 8, ST7735_BLACK, ST7735_WHITE, pAlarmIcon);
	myTFT.TFTdrawIcon(102, 2, 16, ST7735_BLACK, ST7735_WHITE, pBatIcon);

	myTFT.TFTdrawIcon(5, 20, 12, ST7735_GREEN , ST7735_BLACK, pPowerIcon);
	myTFT.TFTdrawIcon(20, 20, 12, ST7735_RED, ST7735_YELLOW, pSpeedIcon);
	myTFT.TFTsetCursor(40,20);
	myTFT.print(myTFT.TFTLibVerNumGet());
	if (myTFT.TFTdrawBitmap(80, 20, 40 , 16, ST7735_CYAN , ST7735_BLACK, (uint8_t *)pSunText) != 0)
	{
		std::cout << "Warning an Error occurred in TFTdrawBitmap." << std::endl;
		return ;
	}

	myTFT.TFTdrawText(80, 90, teststr1, ST7735_BLUE, ST7735_BLACK, 1);
	myTFT.TFTFontNum(myTFT.TFTFont_Bignum);
	while(1)
	{
		time(&now);
		timenow = localtime(&now);
		count--;
		snprintf(myStr, sizeof(myStr), "%03u", count);

		myTFT.TFTdrawChar(0, 45, value[timenow->tm_hour / 10],ST7735_RED, ST7735_BLACK);
		myTFT.TFTdrawChar(16, 45, value[timenow->tm_hour % 10],ST7735_RED, ST7735_BLACK);
		myTFT.TFTdrawChar(32, 45, ':' , ST7735_GREEN, ST7735_BLACK);
		myTFT.TFTdrawChar(48, 45, value[timenow->tm_min / 10], ST7735_RED, ST7735_BLACK);
		myTFT.TFTdrawChar(64, 45, value[timenow->tm_min % 10], ST7735_RED, ST7735_BLACK);
		myTFT.TFTdrawChar(80, 45, ':' , ST7735_GREEN, ST7735_BLACK);
		myTFT.TFTdrawChar(96, 45, value[timenow->tm_sec / 10],  ST7735_RED, ST7735_BLACK);
		myTFT.TFTdrawChar(112, 45, value[timenow->tm_sec % 10],  ST7735_RED, ST7735_BLACK);
		myTFT.TFTdrawText(0, 85, myStr, ST7735_YELLOW, ST7735_RED);

		if(count==1)break;
	}
	TFT_MILLISEC_DELAY(TEST_DELAY2);
	myTFT.TFTfillScreen(ST7735_BLACK);
	myTFT.TFTFontNum(myTFT.TFTFont_Default);
}

void Test402(void)
{
	std::cout << "Test 402: Bi-color bitmap" << std::endl;
	myTFT.TFTfillScreen(ST7735_BLACK);
	char teststr1[] = "Bitmap 2 ";
	myTFT.TFTdrawText(5, 5, teststr1, ST7735_WHITE, ST7735_BLACK, 2);
	TFT_MILLISEC_DELAY(TEST_DELAY2);
	
	if(myTFT.TFTdrawBitmap(0, 0, 128 , 128, ST7735_WHITE , ST7735_GREEN, (uint8_t *)pBackupMenuBitmap) != 0)
		return;
	TFT_MILLISEC_DELAY(TEST_DELAY5);
}

// bitmap 24 colour , All files format = Windows BITMAPINFOHEADER offset 54
void Test403(void)
{
	std::cout << "Test 403: 24 bit color image bitmaps from the file system" << std::endl;
	myTFT.TFTfillScreen(ST7735_BLACK);
	char teststr1[] = "Bitmap 24";
	myTFT.TFTdrawText(5, 5, teststr1, ST7735_WHITE, ST7735_BLACK, 2);
	TFT_MILLISEC_DELAY(TEST_DELAY1);

	FILE *pFile ;
	size_t pixelSize = 3;
	uint8_t* bmpBuffer = nullptr;
	bmpBuffer = (uint8_t*)malloc((128 * 128) * pixelSize);
	if (bmpBuffer == nullptr)
	{
		std::cout << "Error Test 403 : MALLOC could not assign memory " << std::endl;
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

		if (pFile == nullptr)  // Check file exists
		{
			std::cout << "Error Test 403: File does not exist" << std::endl;
			free(bmpBuffer);
			return;
		}

		fseek(pFile, 54, 0); // Put file in Buffer
		fread(bmpBuffer, pixelSize, 128 * 128, pFile);
		fclose(pFile);

		if(myTFT.TFTdrawBitmap24(0, 0, bmpBuffer, 128, 128) != 0)
		{// Check for success 0x00
			free(bmpBuffer);
			return;
		}
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

void Test404(void)
{
	std::cout << "Test 404: 16 bit color image bitmaps from the file system" << std::endl;
	myTFT.TFTfillScreen(ST7735_BLACK);
	char teststr1[] = "Bitmap 16";
	myTFT.TFTdrawText(5, 5, teststr1, ST7735_WHITE, ST7735_BLACK, 2);
	TFT_MILLISEC_DELAY(TEST_DELAY2);

	FILE *pFile ;
	size_t pixelSize = 2;
	uint8_t offsetBMPHeader = 0;
	uint8_t* bmpBuffer1 = nullptr;
	bmpBuffer1 = (uint8_t*)malloc((128 * 128) * pixelSize);

	if (bmpBuffer1 == nullptr)
	{
		std::cout << "Error Test 404 : MALLOC could not assign memory " << std::endl;
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
		if (pFile == nullptr)
		{
			std::cout << "Error Test 404 : File does not exist" << std::endl;
			free(bmpBuffer1);
			return;
		}
		fseek(pFile, offsetBMPHeader, 0);
		fread(bmpBuffer1, pixelSize, 128 * 128, pFile);
		fclose(pFile);

		if (myTFT.TFTdrawBitmap16(0, 0, bmpBuffer1, 128, 128) != 0) 
		{
		// Check for success 0x00
			free(bmpBuffer1);
			return;
		}
		TFT_MILLISEC_DELAY(TEST_DELAY5);
		offsetBMPHeader = 72;
	} // end of for loop

	free(bmpBuffer1); // Free Up Buffer
	myTFT.TFTfillScreen(ST7735_BLACK);
} // end of test 


void EndTests(void)
{
	char teststr1[] = "Tests over";
	myTFT.TFTfillScreen(ST7735_BLACK);
	myTFT.TFTdrawText(5, 50, teststr1, ST7735_GREEN, ST7735_BLACK, 2);
	TFT_MILLISEC_DELAY(TEST_DELAY5);
	myTFT.TFTfillScreen(ST7735_BLACK);
	myTFT.TFTPowerDown(); // Power down device
	bcm2835_close(); // Close the bcm2835 library
	std::cout << "TFT End" << std::endl;
}

// *************** EOF ****************
