# Changelog

* version 1.0.0 May 2021
	* first release.
* Version 1.1 June 2021
	* packaged library files as a dynamic C install-able system level library.
* Version 1.2 July 2021
	* Added fonts. 
* Version 1.3 March 2022
	* Converted from C to C++
	* Added Print class for printing numerical variables
	* Added "tiny" font 
	* Extended default font data set to full ASCII range
* Version 1.4 November 2022
	* github Pull request #1 merged , Separate Invert Control, SPI Clock Frequency Control, Buffered Writes
		main:
		* void TFTInitSPIClockFrequency(uint32_t hertz) - set the SPI clock frequency
		* void TFTchangeInvertMode(bool invertModeOn) - set the invert mode separately from the driver mode
		graphics:
		* void writeDataBuffer(uint8_t* data_, uint32_t len)
		* void spiWrite(uint8_t) - write byte to SPI using either hardware SPI or software, calls spiWriteSoftware
		* void spiWriteSoftware(uint8_t spidata) - write byte to SPI explicitly using bitbanging
		* void spiWriteBuffer(uint8_t* spidata, uint32_t len)  - write an array of bytes to SPI
		* TFTfillRectangle - modified to use writeDataBuffer
		* TFTdrawBitmap24 - modified to use writeDataBuffer 
* Version 1.5 November 2022
	* methods TFTdrawBitmap and TFTdrawBitmap16 modified to use writeDataBuffer
	* delay statements defined in library header file
	* added font "homespun"
	* merged method "TFTInitSPIClockFrequency" with "TFTInitPCBType" and 
		added option to select chip enable line(0 or 1)
	* methods spiWriteBuffer & writeDataBuffer merged to single method spiWriteDataBuffer
	* replaced printf with cout
	
