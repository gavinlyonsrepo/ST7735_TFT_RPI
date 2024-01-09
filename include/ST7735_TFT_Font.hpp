/*!
	@file     ST7735_TFT_Font.hpp
	@author   Gavin Lyons
	@brief    Library header file for ST7735_TFT_RPI library font data
						This file contains pointer to the fonts, the data is in cpp file.
						12 fonts see main readme file for details
*/

#include <cstdint>

#pragma once

extern const unsigned char * pFontDefaultptr; /**< Pointer to default font data  */
extern const unsigned char * pFontThickptr; /**< Pointer to thick font data  */
extern const unsigned char * pFontSevenSegptr; /**< Pointer to seven segment font data  */
extern const unsigned char * pFontWideptr; /**< Pointer to wide font data  */
extern const unsigned char * pFontTinyptr; /**< Pointer to tiny font data  */
extern const unsigned char * pFontHomeSpunptr; /**< Pointer to homespun font data  */
extern const uint8_t (* pFontBigNum16x32ptr)[64]; /**< Pointer to big numbers font data  */
extern const uint8_t (* pFontMedNum16x16ptr)[32]; /**< Pointer to medium numbers font data  */
extern const uint8_t (* pFontArial16x24ptr)[48]; /**< Pointer to Arial Round font data */
extern const uint8_t (* pFontArial16x16ptr)[32]; /**< Pointer to Arial bold font data */
extern const uint8_t (* pFontMia8x16ptr)[16]; /**< Pointer to Mia  font data */
extern const uint8_t (* pFontDedica6x12ptr)[12]; /**< Pointer to dedica font data */
