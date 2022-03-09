/*
 * Project Name: ST7735, 128 by 128, 1.44", red pcb,  SPI TFT module
 * File: ST7735_TFT.cpp
 * Description: library source file
 * Author: Gavin Lyons.
 * Created May 2021
 * Description: See URL for full details.
 * URL: https://github.com/gavinlyonsrepo/ST7735_TFT_RPI
 */

#include "ST7735_TFT.h"
 
 
ST7735_TFT :: ST7735_TFT()
{
}

// Desc : Init Hardware SPI
void ST7735_TFT::TFTSPIInitialize(void)
{
	bcm2835_spi_begin();
	bcm2835_spi_setBitOrder(BCM2835_SPI_BIT_ORDER_MSBFIRST);
	bcm2835_spi_setDataMode(BCM2835_SPI_MODE0);
	//SPI_CLOCK_DIVIDER_32 = 7.8125MHz on Rpi2, 12.5MHz on RPI3
	bcm2835_spi_setClockDivider(BCM2835_SPI_CLOCK_DIVIDER_32); 
	bcm2835_spi_chipSelect(BCM2835_SPI_CS0);
	bcm2835_spi_setChipSelectPolarity(BCM2835_SPI_CS0, LOW);
}


// Desc: Call when powering down TFT
// Turns off Display Sets GPIO low and turns off SPI 
// 	End SPI operations. SPI0 pins P1-19 (MOSI), P1-21 (MISO), P1-23 (CLK), 
// P1-24 (CE0) and P1-26 (CE1) 
// are returned to their default INPUT behavior.
void ST7735_TFT ::TFTPowerDown(void)
{
	TFTchangeMode(TFT_Display_off_mode);
	bcm2835_gpio_write(_TFT_DC, LOW);
	bcm2835_gpio_write(_TFT_RST, LOW);
	
if (_hardwareSPI == false)
{
	bcm2835_gpio_write(_TFT_SCLK, LOW);
	bcm2835_gpio_write(_TFT_SDATA, LOW);
	bcm2835_gpio_write(_TFT_CS, LOW);
}else{ 
	bcm2835_spi_end();
	} 
}

// Desc: Function for Hardware Reset pin control

void ST7735_TFT ::TFTResetPIN() {
	TFT_RST_SetDigitalOutput;
	TFT_RST_SetHigh;
	bcm2835_delay(10);
	TFT_RST_SetLow;
	bcm2835_delay(10);
	TFT_RST_SetHigh;
	bcm2835_delay(10);
}

// Desc : sets up TFT GPIO
// Param 1: reset GPIO 
// Param 2: data or command GPIO.
// Param 3: chip select GPIO -> Software SPI only set to -1 for HW SPI
// Param 4: Data clock GPIO  -> Software SPI only set to -1 for HW SPI
// Param 5: Data to TFT GPIO -> Software SPI only set to -1 for HW SPI

void ST7735_TFT ::TFTSetupGPIO(int8_t rst, int8_t dc, int8_t cs, int8_t sclk, int8_t din)
{
if((cs != -1) && (sclk != -1) && (din != -1))
{
	_TFT_CS = cs;
	_TFT_SDATA = din;  
	_TFT_SCLK = sclk;
	_hardwareSPI = false;
}else{
	_hardwareSPI = true;
}
	_TFT_RST= rst;
	_TFT_DC = dc;
}


// Desc: init sub-routine ST7735R Green Tab

void ST7735_TFT ::TFTGreenTabInitialize() {
	TFTResetPIN();
	TFT_DC_SetLow;
	TFT_DC_SetDigitalOutput;
if (_hardwareSPI == false){
	TFT_CS_SetHigh;
	TFT_CS_SetDigitalOutput;
	TFT_SCLK_SetLow;
	TFT_SDATA_SetLow;
	TFT_SCLK_SetDigitalOutput;
	TFT_SDATA_SetDigitalOutput;
}else{
	TFTSPIInitialize();
}
	Rcmd1();
	Rcmd2green();
	Rcmd3();
	TFT_PCBtype = TFT_ST7735R_Green;
}

// Desc: init sub-routine ST7735R Green Tab

void ST7735_TFT ::Rcmd2green() {
	writeCommand(ST7735_CASET);
	writeData(0x00);
	writeData(0x02);
	writeData(0x00);
	writeData(0x7F + 0x02);
	writeCommand(ST7735_RASET);
	writeData(0x00);
	writeData(0x01);
	writeData(0x00);
	writeData(0x9F + 0x01);
}


// Desc: ST7735R Red Tab Init Red PCB version

void ST7735_TFT ::TFTRedTabInitialize() {
	TFTResetPIN();
	TFT_DC_SetLow;
	TFT_DC_SetDigitalOutput;
if (_hardwareSPI == false)
{
	TFT_CS_SetHigh;
	TFT_CS_SetDigitalOutput;
	TFT_SCLK_SetLow;
	TFT_SDATA_SetLow;
	TFT_SCLK_SetDigitalOutput;
	TFT_SDATA_SetDigitalOutput;
}else{
	TFTSPIInitialize();
}
	Rcmd1();
	Rcmd2red();
	Rcmd3();
	TFT_PCBtype = TFT_ST7735R_Red;

}

// Desc: Init Routine ST7735R Black Tab (ST7735S)

void ST7735_TFT ::TFTBlackTabInitialize() {
	TFTResetPIN();
	TFT_DC_SetLow;
	TFT_DC_SetDigitalOutput;
if (_hardwareSPI == false)
{
	TFT_CS_SetHigh;
	TFT_CS_SetDigitalOutput;
	TFT_SCLK_SetLow;
	TFT_SDATA_SetLow;
	TFT_SCLK_SetDigitalOutput;
	TFT_SDATA_SetDigitalOutput;
}else{
	TFTSPIInitialize();
}
	Rcmd1();
	Rcmd2red();
	Rcmd3();
	writeCommand(ST7735_MADCTL);
	writeData(0xC0);
	TFT_PCBtype = TFT_ST7735S_Black ;
}

// Desc: init routine for ST7735B controller

void ST7735_TFT ::TFTST7735BInitialize() {
	TFTResetPIN();
	TFT_DC_SetLow;
	TFT_DC_SetDigitalOutput;
if (_hardwareSPI == false)
{
	TFT_CS_SetHigh;
	TFT_CS_SetDigitalOutput;
	TFT_SCLK_SetLow;
	TFT_SDATA_SetLow;
	TFT_SCLK_SetDigitalOutput;
	TFT_SDATA_SetDigitalOutput;
}else{
	TFTSPIInitialize();
}
	Bcmd();
	TFT_PCBtype = TFT_ST7735B ;
}


// Desc: init routine for ST7735B controller

void ST7735_TFT ::Bcmd() {
	writeCommand(ST7735_SWRESET);
	bcm2835_delay(50);
	writeCommand(ST7735_SLPOUT);
	bcm2835_delay(500);
	writeCommand(ST7735_COLMOD);
	writeData(0x05);
	bcm2835_delay(10);
	writeCommand(ST7735_FRMCTR1);
	writeData(0x00);
	writeData(0x06);
	writeData(0x03);
	bcm2835_delay(10);
	writeCommand(ST7735_MADCTL);
	writeData(0x08);
	writeCommand(ST7735_DISSET5);
	writeData(0x15);
	writeData(0x02);
	writeCommand(ST7735_INVCTR);
	writeData(0x00);
	writeCommand(ST7735_PWCTR1);
	writeData(0x02);
	writeData(0x70);
	bcm2835_delay(10);
	writeCommand(ST7735_PWCTR2);
	writeData(0x05);
	writeCommand(ST7735_PWCTR3);
	writeData(0x01);
	writeData(0x02);
	writeCommand(ST7735_VMCTR1);
	writeData(0x3C);
	writeData(0x38);
	bcm2835_delay(10);
	writeCommand(ST7735_PWCTR6);
	writeData(0x11);
	writeData(0x15);
	writeCommand(ST7735_GMCTRP1);
	writeData(0x09);
	writeData(0x16);
	writeData(0x09);
	writeData(0x20);
	writeData(0x21);
	writeData(0x1B);
	writeData(0x13);
	writeData(0x19);
	writeData(0x17);
	writeData(0x15);
	writeData(0x1E);
	writeData(0x2B);
	writeData(0x04);
	writeData(0x05);
	writeData(0x02);
	writeData(0x0E);
	writeCommand(ST7735_GMCTRN1);
	writeData(0x0B);
	writeData(0x14);
	writeData(0x08);
	writeData(0x1E);
	writeData(0x22);
	writeData(0x1D);
	writeData(0x18);
	writeData(0x1E);
	writeData(0x1B);
	writeData(0x1A);
	writeData(0x24);
	writeData(0x2B);
	writeData(0x06);
	writeData(0x06);
	writeData(0x02);
	writeData(0x0F);
	bcm2835_delay(10);
	writeCommand(ST7735_CASET);
	writeData(0x00);
	writeData(0x02);
	writeData(0x08);
	writeData(0x81);
	writeCommand(ST7735_RASET);
	writeData(0x00);
	writeData(0x01);
	writeData(0x08);
	writeData(0xA0);
	writeCommand(ST7735_NORON);
	bcm2835_delay(10);
	writeCommand(ST7735_DISPON);
	bcm2835_delay(500);
}


// Desc: init routine

void ST7735_TFT ::Rcmd1() {
	writeCommand(ST7735_SWRESET);
	bcm2835_delay(150);
	writeCommand(ST7735_SLPOUT);
	bcm2835_delay(500);
	writeCommand(ST7735_FRMCTR1);
	writeData(0x01);
	writeData(0x2C);
	writeData(0x2D);
	writeCommand(ST7735_FRMCTR2);
	writeData(0x01);
	writeData(0x2C);
	writeData(0x2D);
	writeCommand(ST7735_FRMCTR3);
	writeData(0x01);
	writeData(0x2C);
	writeData(0x2D);
	writeData(0x01);
	writeData(0x2C);
	writeData(0x2D);
	writeCommand(ST7735_INVCTR);
	writeData(0x07);
	writeCommand(ST7735_PWCTR1);
	writeData(0xA2);
	writeData(0x02);
	writeData(0x84);
	writeCommand(ST7735_PWCTR2);
	writeData(0xC5);
	writeCommand(ST7735_PWCTR3);
	writeData(0x0A);
	writeData(0x00);
	writeCommand(ST7735_PWCTR4);
	writeData(0x8A);
	writeData(0x2A);
	writeCommand(ST7735_PWCTR5);
	writeData(0x8A);
	writeData(0xEE);
	writeCommand(ST7735_VMCTR1);
	writeData(0x0E);
	writeCommand(ST7735_INVOFF);
	writeCommand(ST7735_MADCTL);
	writeData(0xC8);
	writeCommand(ST7735_COLMOD);
	writeData(0x05);
}

// Desc: init sub-routine

void ST7735_TFT ::Rcmd2red() {
	writeCommand(ST7735_CASET);
	writeData(0x00);
	writeData(0x00);
	writeData(0x00);
	writeData(0x7F);
	writeCommand(ST7735_RASET);
	writeData(0x00);
	writeData(0x00);
	writeData(0x00);
	writeData(0x9F);
}

// Desc: init sub-routine

void ST7735_TFT ::Rcmd3() {
	writeCommand(ST7735_GMCTRP1);
	writeData(0x02);
	writeData(0x1C);
	writeData(0x07);
	writeData(0x12);
	writeData(0x37);
	writeData(0x32);
	writeData(0x29);
	writeData(0x2D);
	writeData(0x29);
	writeData(0x25);
	writeData(0x2B);
	writeData(0x39);
	writeData(0x00);
	writeData(0x01);
	writeData(0x03);
	writeData(0x10);
	writeCommand(ST7735_GMCTRN1);
	writeData(0x03);
	writeData(0x1D);
	writeData(0x07);
	writeData(0x06);
	writeData(0x2E);
	writeData(0x2C);
	writeData(0x29);
	writeData(0x2D);
	writeData(0x2E);
	writeData(0x2E);
	writeData(0x37);
	writeData(0x3F);
	writeData(0x00);
	writeData(0x00);
	writeData(0x02);
	writeData(0x10);
	writeCommand(ST7735_NORON);
	bcm2835_delay(10);
	writeCommand(ST7735_DISPON);
	bcm2835_delay(100);
}


// Desc: This method defines the Vertical Scrolling Area of the display where:
// Param 1: top_fix_heightTFT: describes the Top Fixed Area,
// Param 2: bottom_fix_heightTFT: describes the Bottom Fixed Area and
// Param 3: _scroll_direction: is scroll direction (0 for top to bottom and 1 for bottom to top).

void ST7735_TFT ::TFTsetScrollDefinition(uint8_t top_fix_heightTFT, uint8_t bottom_fix_heightTFT, bool _scroll_direction) {
	uint8_t scroll_heightTFT;
	scroll_heightTFT = _heightTFT - top_fix_heightTFT - bottom_fix_heightTFT;
	writeCommand(ST7735_VSCRDEF);
	writeData(0x00);
	writeData(top_fix_heightTFT);
	writeData(0x00);
	writeData(scroll_heightTFT);
	writeData(0x00);
	writeData(bottom_fix_heightTFT);
	writeCommand(ST7735_MADCTL);
	if (_scroll_direction) {
		if ((TFT_PCBtype == TFT_ST7735R_Red)  || (TFT_PCBtype == TFT_ST7735R_Green)) {
			writeData(0xD8);
		}
		if (TFT_PCBtype == TFT_ST7735S_Black) {
			writeData(0xD0);
		}
		if (TFT_PCBtype == TFT_ST7735B ) {
			writeData(0x18);
		}
	} else {
		if (((TFT_PCBtype == TFT_ST7735R_Red)  || (TFT_PCBtype == TFT_ST7735R_Green))) {
			writeData(0xC8);
		}
		if (TFT_PCBtype == TFT_ST7735S_Black) {
			writeData(0xC0);
		}
		if (TFT_PCBtype == TFT_ST7735B ) {
			writeData(0x08);
		}
	}
}

// Desc: This method is used together with the TFTsetScrollDefinition.
// These two methods describe the scrolling area and the scrolling mode.

void ST7735_TFT ::TFTVerticalScroll(uint8_t _vsp) {
	writeCommand(ST7735_VSCRSADD);
	writeData(0x00);
	writeData(_vsp);
}

/*
Desc: This changes the mode of the display as:
	TFT_Normal_mode: Normal mode.
	TFT_Partial_mode: Enable partial mode to work in portions of display 
	TFT_Idle_mode: Idle_mode consume less current and shows less color
	TFT_Sleep_mode: Put display driver section in sleep but rest of the logic works.
	TFT_Invert_mode: invert the display
	TFT_Display_on_mode: Turn on display
	TFT_Display_off_mode: Turn off display
 */
void ST7735_TFT ::TFTchangeMode(TFT_modes_e mode) {
	switch (mode) {
		case TFT_Normal_mode:
			if (_currentMode ==  TFT_Display_off_mode) {//was in off display?
				writeCommand(ST7735_DISPON);
			}
			if (_currentMode == TFT_Idle_mode) {//was in idle?
				writeCommand(ST7735_TFT_Idle_modeOF);
			}
			if (_currentMode == TFT_Sleep_mode) {//was in sleep?
				writeCommand(ST7735_SLPOUT);
				bcm2835_delay(120);
			}
			if (_currentMode == TFT_Invert_mode) {//was inverted?
				_currentMode = TFT_Normal_mode;
				writeCommand(ST7735_INVOFF);
			}
			writeCommand(ST7735_NORON);
			_currentMode = TFT_Normal_mode;
			break;
		case TFT_Partial_mode:
			writeCommand(ST7735_PTLON);
			_currentMode = TFT_Partial_mode;
			break;
		case TFT_Idle_mode:
			writeCommand(ST7735_TFT_Idle_modeON);
			_currentMode = TFT_Idle_mode;
			break;
		case TFT_Sleep_mode:
			writeCommand(ST7735_SLPIN);
			_currentMode = TFT_Sleep_mode;
			bcm2835_delay(5);
			return;
		case TFT_Invert_mode:
			writeCommand(ST7735_INVON);
			_currentMode = TFT_Invert_mode;
			break;
		case TFT_Display_on_mode:
			writeCommand(ST7735_DISPON);
			_currentMode = TFT_Display_on_mode;
			break;
		case TFT_Display_off_mode:
			writeCommand(ST7735_DISPOFF);
			_currentMode =  TFT_Display_off_mode;
			break;
	}//switch
}


// Desc: change rotation of display.
// Param1 : TFT_modes_e enum
// 0 = Normal
// 1=  90 rotate
// 2 = 180 rotate
// 3 =  270 rotate
// Note: if on your display colors are wrong after rotate change
// ST7735_MADCTL_BGR to ST7735_MADCTL_RGB

void ST7735_TFT ::TFTsetRotation(TFT_rotate_e mode) {
	uint8_t madctl = 0;

	_rotation = mode % 4;
	switch (_rotation) {
		case TFT_Degress_0 :
			if (TFT_PCBtype == TFT_ST7735S_Black ){
				madctl = ST7735_MADCTL_MX | ST7735_MADCTL_MY | ST7735_MADCTL_RGB;
			}else{
				madctl = ST7735_MADCTL_MX | ST7735_MADCTL_MY | ST7735_MADCTL_BGR;
			}
			_widthTFT =_widthStartTFT;
			_heightTFT = _heightStartTFT;
			_XStart = _colstart;
			_YStart = _rowstart;
			break;
		case TFT_Degress_90:
			if (TFT_PCBtype == TFT_ST7735S_Black )
			{
				madctl = ST7735_MADCTL_MY | ST7735_MADCTL_MV | ST7735_MADCTL_RGB;
			}else{
				madctl = ST7735_MADCTL_MY | ST7735_MADCTL_MV | ST7735_MADCTL_BGR;
			}
			_YStart = _colstart;
			_XStart = _rowstart;
			_widthTFT  =_heightStartTFT;
			_heightTFT = _widthStartTFT;
			break;
		case TFT_Degress_180:
			if (TFT_PCBtype == TFT_ST7735S_Black)
			{
				madctl = ST7735_MADCTL_RGB;
			}else{
				madctl = ST7735_MADCTL_BGR;
			}
			_XStart = _colstart;
			_YStart = _rowstart;
			_widthTFT =_widthStartTFT;
			_heightTFT = _heightStartTFT;
			break;
		case TFT_Degress_270:
			if (TFT_PCBtype == TFT_ST7735S_Black){
				madctl = ST7735_MADCTL_MX | ST7735_MADCTL_MV | ST7735_MADCTL_RGB;
			}else{
				madctl = ST7735_MADCTL_MX | ST7735_MADCTL_MV | ST7735_MADCTL_BGR;
			}
			_YStart = _colstart;
			_XStart = _rowstart;
			_widthTFT =_heightStartTFT;
			_heightTFT = _widthStartTFT;
			break;
	}
	writeCommand(ST7735_MADCTL);
	writeData(madctl);
}

// Func Desc: initialise the variables that define the size of the screen
// These offsets can be adjusted for any issues with manufacture tolerance/defects
// Param 1: Column offset
// Param 2: Row offset
// Param 3: Screen width in pixels
// Param 4: Screen height in pixels
void ST7735_TFT  :: TFTInitScreenSize(uint8_t colOffset, uint8_t rowOffset, uint16_t width_TFT, uint16_t height_TFT)
{
	_colstart = colOffset; 
	_rowstart = rowOffset;
	_XStart = colOffset; 
	_YStart = rowOffset;
	
	_widthTFT = width_TFT;
	_heightTFT = height_TFT;
	_widthStartTFT = width_TFT;
	_heightStartTFT = height_TFT;
}

// Func Screen : intialise PCBtyep
// Param 1: Enum TFT_PCBtype_e , 4 choices 0-3
void ST7735_TFT  ::TFTInitPCBType(TFT_PCBtype_e pcbType)
{
	uint8_t choice = pcbType;
	switch(choice)
	{
		case TFT_ST7735R_Red : TFTRedTabInitialize(); break;
		case TFT_ST7735R_Green: TFTGreenTabInitialize(); break;
		case TFT_ST7735S_Black: TFTBlackTabInitialize(); break;
		case TFT_ST7735B : TFTST7735BInitialize(); break;
		default:
			printf("Error 1401 : Wrong input TFTInitPCBType \n");
		break;
	}
}
//**************** EOF *****************
