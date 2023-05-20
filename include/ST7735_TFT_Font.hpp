/*!
	@file     ST7735_TFT_Font.hpp
	@author   Gavin Lyons
	@brief    Library header file for ST7735_TFT_RPI library font data
              This file contains the font definitions and data.	
              8 fonts see main readme file for details
*/

#include <stdint.h>

#pragma once

extern const unsigned char * pFontDefaultptr; /**< Pointer to default font data which is in cpp file */
extern const unsigned char * pFontThickptr; /**< Pointer to thick font data which is in cpp file */
extern const unsigned char * pFontSevenSegptr; /**< Pointer to seven segment font data which is in cpp file */
extern const unsigned char * pFontWideptr; /**< Pointer to wide font data which is in cpp file */
extern const unsigned char * pFontTinyptr; /**< Pointer to tiny font data which is in cpp file */
extern const unsigned char * pFontHomeSpunptr; /**< Pointer to homespun font data which is in cpp file */
extern const uint8_t (* pFontBigNumptr)[64]; /**< Pointer to big numbers font data which is in cpp file */
extern const uint8_t (* pFontMedNumptr)[32]; /**< Pointer to medium numbers font data which is in cpp file */
