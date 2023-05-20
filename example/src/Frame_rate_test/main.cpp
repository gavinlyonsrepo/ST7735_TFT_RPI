/*! 
	@file src/Frame_rate_test/main.cpp
	@brief Frame rate test FPS  
	@author Gavin Lyons.
	@note See USER OPTIONS 1-3 in SETUP function
	@test Test 20: Frame rate test FPS test
*/

// Section ::  libraries 
#include <bcm2835.h> // for SPI GPIO and delays.
#include <time.h> // for test FPS
#include "ST7735_TFT.hpp"

// Section :: Defines   
//  Test timing related defines 
#define TEST_DELAY1 1000
#define TEST_DELAY2 2000
#define TEST_DELAY5 5000

// Section :: Globals 
ST7735_TFT myTFT;

//  Section ::  Function Headers 

int8_t Setup(void); // setup + user options
void TestFPS(void); // Frames per second 24 color bitmap test,
void EndTests(void);

int64_t getTime(); // Utility for FPS test
uint8_t* loadImage(char* name); // Utility for FPS test

//  Section ::  MAIN loop

int main(void) 
{

	if(!Setup())return -1;
	TestFPS();
	EndTests();
	return 0;
}
// *** End OF MAIN **


//  Section ::  Function Space 

int8_t Setup(void)
{

	TFT_MILLISEC_DELAY(TEST_DELAY1);
	std::cout << "TFT FPS Test Start!" << std::endl;
	if(!bcm2835_init())
	{
		std::cout << "Error : Problem with init bcm2835 library" << std::endl;
		return -1;
	}
	
// ** USER OPTION 1 GPIO/SPI TYPE HW OR SW **
	int8_t RST_TFT  =  25;
	int8_t DC_TFT   =  24;
	int8_t SCLK_TFT =  -1; // 5, change to GPIO no for sw spi, -1 hw spi
	int8_t SDIN_TFT =  -1; // 6, change to GPIO no for sw spi, -1 hw spi
	int8_t CS_TFT   =  -1; // 8, change to GPIO no for sw spi, -1 hw spi
	myTFT.TFTSetupGPIO(RST_TFT, DC_TFT, CS_TFT, SCLK_TFT, SDIN_TFT);
//*********************************************

// ** USER OPTION 2 Screen Setup **
	uint8_t OFFSET_COL = 0;  // 2, These offsets can be adjusted for any issues->
	uint8_t OFFSET_ROW = 0; // 3, with manufacture tolerance/defects
	uint16_t TFT_WIDTH = 128;// Screen width in pixels
	uint16_t TFT_HEIGHT = 160; // Screen height in pixels
	myTFT.TFTInitScreenSize(OFFSET_COL, OFFSET_ROW , TFT_WIDTH , TFT_HEIGHT);
// ***********************************

// ** USER OPTION 3 PCB_TYPE + SPI baud rate + SPI_CE_PIN**
	uint32_t SCLK_FREQ =  8000000 ; // HW Spi freq in Hertz , MAX 125 Mhz MIN 30Khz
	uint8_t SPI_CE_PIN = 0; // which HW SPI chip enable pin to use,  0 or 1
	// pass enum to param1 ,4 choices,see README
	if(!myTFT.TFTInitPCBType(myTFT.TFT_ST7735S_Black, SCLK_FREQ, SPI_CE_PIN))return -1;
	// Note : if using SW SPI you do not have to pass anything for param 2&3, it will do nothing. 
//*****************************
	return 0;
}

/*!
 *@brief Frames per second test , 24 color bitmap test, 
*/
void TestFPS(void) {

	myTFT.TFTfillScreen(ST7735_BLACK);
	myTFT.TFTsetRotation(myTFT.TFT_Degrees_90);
	
	// Load images into buffers
	uint8_t* img[5] = { 
		loadImage((char*)"bitmap/bitmapFPSimages/title.bmp"),
		loadImage((char*)"bitmap/bitmapFPSimages/menu.bmp"),
		loadImage((char*)"bitmap/bitmapFPSimages/game1.bmp"),
		loadImage((char*)"bitmap/bitmapFPSimages/game2.bmp"),
		loadImage((char*)"bitmap/bitmapFPSimages/game3.bmp")
	};
	for (uint8_t i=0; i<5 ;i++) // Did any loadImage call return NULL
	{
		if (img[i] == NULL){ 
			for(uint8_t j=0; j<5; j++) free(img[j]); // Free Up Buffer if set
			TFT_MILLISEC_DELAY(TEST_DELAY1);
			return;
		}
	}
	int64_t start = getTime(), duration = 0;
	uint32_t frames = 0;
	double fps = 0;

	// Run for ~10sec
	while(duration < 10000000) {
		myTFT.TFTdrawBitmap24(0, 0, img[frames % 5], 160, 80);

		duration = getTime() - start;

		if((++frames % 50) == 0) {
			fps = (double)frames / ((double)duration / 1000000);
			std::cout << fps << std::endl;
		}
	}

	// Get final Stats and print
	duration = getTime() - start;
	fps = (double)frames / ((double)duration / 1000000);
	std::cout << frames << " frames, " << duration / 1000000 << " sec, " << fps << " fps" << std::endl;

	// Free Up Buffers
	for(int i=0; i<5; i++) free(img[i]);
}


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
		std::cout << "Error TestFPS : File does not exist" << std::endl;
		return NULL;
	} else {
		bmpBuffer1 = (uint8_t*)malloc((160 * 80) * pixelSize);
		if (bmpBuffer1 == NULL)
		{
			std::cout << "Error TestFPS : MALLOC could not assign memory " << std::endl;
			return NULL;
		}
		fseek(pFile, 132, 0);
		fread(bmpBuffer1, pixelSize, 160 * 80, pFile);
		fclose(pFile);
	}
	
	return bmpBuffer1;
}

// *************** EOF ****************
