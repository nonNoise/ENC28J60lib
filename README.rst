==================================================
ENC28J60 original Liblary
==================================================



ENC28J60.c = Hardware peripheral source code

ENC28J60lib.c = ENC28J60 API leyer source code



Please change the following contents in each environment at "ENC28J60.c"

::
	//********************************************************************//
	// HardWare Interface
	//********************************************************************//
	#include "mcc_generated_files/mcc.h"
	#define SPI_CS_LOW()        SS1_Toggle()//SS1_SetLow()
	#define SPI_CS_HIGH()       SS1_SetHigh()
	uint8_t SPI_8bit_Read(void)
	{
        	return SPI1_Exchange8bit(0x00);
	}
	void SPI_8bit_Write(uint8_t wdata)
	{
        	SPI1_Exchange8bit(wdata);
	}

This source code is test PIC32MX.