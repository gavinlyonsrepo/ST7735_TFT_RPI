main:
* void TFTInitSPIClockFrequency(uint32_t hertz) - set the SPI clock frequency
* void TFTchangeInvertMode(bool invertModeOn) - set the invert mode separately from the driver mode

graphics:
* void writeDataBuffer(uint8_t* data_, uint32_t len)
* void spiWrite(uint8_t) - write byte to SPI using either hardware SPI or software, calls spiWriteSoftware
* void spiWriteSoftware(uint8_t spidata) - write byte to SPI explicitly using bitbanging
* void spiWriteBuffer(uint8_t* spidata, uint32_t len)  - write an array of bytes to SPI (100x faster when using hardware SPI)

* TFTfillRectangle - modified to use writeDataBuffer
* TFTdrawBitmap24 - modified to use writeDataBuffer 