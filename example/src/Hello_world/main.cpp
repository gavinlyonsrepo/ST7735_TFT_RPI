/*! 
	@file src/Hello_world/main.cpp
	@brief Hello World 
	@author Gavin Lyons.
	@note See USER OPTIONS 1-3 in SETUP function
*/

// Section ::  libraries 
#include <bcm2835.h> 
#include "ST7735_TFT.hpp"

// Section :: Globals 
ST7735_TFT myTFT;

//  Section ::  Function Headers 

int8_t Setup(void); // setup + user options
void HelloWorld(void);
void EndTests(void);


//  Section ::  MAIN loop

int main(void) 
{

	if(!Setup())return -1;
	HelloWorld();
	EndTests();
	return 0;
}
// *** End OF MAIN **


//  Section ::  Function Space 

int8_t Setup(void)
{

	TFT_MILLISEC_DELAY(500);
	std::cout << "TFT Start" << std::endl;
	if(!bcm2835_init())
	{
		std::cout << "Error : Problem with init bcm2835 library" << std::endl;
		return -1;
	}
	
// ** USER OPTION 1 GPIO/SPI TYPE HW OR SW **
	int8_t RST_TFT  = 25;
	int8_t DC_TFT   = 24;
	int8_t SCLK_TFT = -1;   // 5, change to any GPIO no for sw spi, -1 hw spi
	int8_t SDIN_TFT = -1;   // 6, change to any GPIO no for sw spi, -1 hw spi
	int8_t CS_TFT   = -1 ;  // 8, change to any GPIO no for sw spi, -1 hw spi
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
	uint32_t SCLK_FREQ =  8000000 ; // HW Spi only , freq in Hertz , MAX 125 Mhz MIN 30Khz
	uint8_t SPI_CE_PIN = 0; // HW Spi only which HW SPI chip enable pin to use,  0 or 1
	// pass enum to param1 ,4 choices,see README
	// NOTE: if using SW SPI you do not have to pass anything for param 2&3, it will do nothing.
	if(!myTFT.TFTInitPCBType(myTFT.TFT_ST7735R_Red, SCLK_FREQ, SPI_CE_PIN))return -1;
 
//*****************************
	return 0;
}

void HelloWorld(void) 
{
	char teststr1[] = "Hello World";
	std::cout << "Hello World" << std::endl;
	myTFT.TFTfillScreen(ST7735_BLACK);
	myTFT.TFTFontNum(myTFT.TFTFont_Default);
	myTFT.TFTdrawText(15, 30, teststr1, ST7735_WHITE, ST7735_BLACK, 1);
	TFT_MILLISEC_DELAY(5000);
}

void EndTests(void)
{
	myTFT.TFTPowerDown(); // Power down device
	bcm2835_close(); // Close the bcm2835 library
	std::cout << "TFT End" << std::endl;
}

// *************** EOF ****************
