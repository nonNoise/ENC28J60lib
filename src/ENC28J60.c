//****************************************************************************************//
//	MIT License
//
//	Copyright (c) 2019 Yuta Kitagami
//
//	Permission is hereby granted, free of charge, to any person obtaining a copy
//	of this software and associated documentation files (the "Software"), to deal
//	in the Software without restriction, including without limitation the rights
//	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//	copies of the Software, and to permit persons to whom the Software is
//	furnished to do so, subject to the following conditions:
//
//	The above copyright notice and this permission notice shall be included in all
//	copies or substantial portions of the Software.
//
//	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//	SOFTWARE.
//**************************************************************************************//

#include "ENC28J60.h"
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
//********************************************************************//


//********************************************************************//
// ENC28J60 Interface
//********************************************************************//
uint8_t ENC28J60_SYSTEM_RESET(void)
{
    uint8_t rdata;
    SPI_CS_LOW();
    SPI_8bit_Write(ENC28J60_OPC_SRC);
    SPI_CS_HIGH();
    
    return rdata;
}
uint8_t ENC28J60_CONTROL_READ(uint8_t addr)
{
    uint8_t rdata;
    SPI_CS_LOW();
    SPI_8bit_Write(ENC28J60_OPC_RCR |(0x1F&addr));
    rdata = SPI_8bit_Read();
    SPI_CS_HIGH();
    return rdata;
}
uint8_t ENC28J60_CONTROL_READ2(uint8_t addr)
{
    uint8_t rdata;
    SPI_CS_LOW();
    SPI_8bit_Write(ENC28J60_OPC_RCR |(0x1F&addr));
    SPI_8bit_Read();
    rdata = SPI_8bit_Read();
    SPI_CS_HIGH();
    return rdata;
}
void  ENC28J60_CONTROL_WRITE(uint8_t addr,uint8_t wdata)
{
    SPI_CS_LOW();
    SPI_8bit_Write(ENC28J60_OPC_WCR | (0x1F&addr));
    SPI_8bit_Write(wdata);
    SPI_CS_HIGH();
}
uint8_t ENC28J60_BUFFER_READ(void)
{
    uint8_t rdata;
    SPI_CS_LOW();
    SPI_8bit_Write(ENC28J60_OPC_RBM );
    rdata = SPI_8bit_Read();
    SPI_CS_HIGH();
    return rdata;
}
uint8_t ENC28J60_BUFFER_WRITE(uint8_t wdata)
{
    uint8_t rdata;
    SPI_CS_LOW();
    SPI_8bit_Write(ENC28J60_OPC_WBM);
    SPI_8bit_Write(wdata);
    SPI_CS_HIGH();
    return rdata;
}
uint8_t G_ENC28J60_BANK=0;
void ENC28J60_CONTROL_BankChange(uint8_t ch)
{
    if(G_ENC28J60_BANK!=ch)
        ENC28J60_CONTROL_WRITE(0x1F,ch);
    G_ENC28J60_BANK = ch;
}
uint8_t ENC28J60_REG_READ(uint8_t addr)
{
    uint8_t rdata=0;

    ENC28J60_CONTROL_BankChange( ( addr & 0x60 ) >> 5);
    if(addr&ENC28J60_MREG==ENC28J60_MREG)
        rdata = ENC28J60_CONTROL_READ2(addr);
    else
        rdata = ENC28J60_CONTROL_READ(addr);
        
    return rdata;
}
void  ENC28J60_REG_WRITE(uint8_t addr,uint8_t wdata)
{
    ENC28J60_CONTROL_BankChange( ( addr & 0x60 ) >> 5);
    ENC28J60_CONTROL_WRITE(addr,wdata);
}

uint16_t ENC28J60_PHY_READ(uint8_t addr)
{
    uint16_t rdata=0x0000;
    ENC28J60_REG_WRITE(ENC28J60_REG_MIREGADR,addr);
    ENC28J60_REG_WRITE(ENC28J60_REG_MICMD,0x01);
    while(ENC28J60_CONTROL_READ(ENC28J60_REG_MISTAT)&MISTAT_BUSY != 0);
    ENC28J60_REG_WRITE(ENC28J60_REG_MICMD,0x00);
    rdata =  ENC28J60_REG_READ(ENC28J60_REG_MIRDH)<<8;
    rdata = rdata | ENC28J60_REG_READ(ENC28J60_REG_MIRDL);
    return rdata;
}
void ENC28J60_PHY_WRITE(uint8_t addr,uint16_t data)
{
    uint8_t rdata;
    ENC28J60_REG_WRITE(ENC28J60_REG_MIREGADR,addr);
    ENC28J60_REG_WRITE(ENC28J60_REG_MIWRL,(uint8_t)(0x00FF&data));
    ENC28J60_REG_WRITE(ENC28J60_REG_MIWRH,(uint8_t)(data>>8));
    while(ENC28J60_CONTROL_READ(ENC28J60_REG_MISTAT)&MISTAT_BUSY != 0);
}
uint8_t ENC28J60_MEM_READ(uint16_t addr)
{
    ENC28J60_REG_WRITE(ENC28J60_REG_ERDPTL,0xFF& addr);
    ENC28J60_REG_WRITE(ENC28J60_REG_ERDPTH,0xFF&(addr>>8));
    return ENC28J60_BUFFER_READ();
}
void ENC28J60_MEM_WRITE(uint16_t addr,uint8_t buff)
{
    ENC28J60_REG_WRITE(ENC28J60_REG_EWRPTL,0xFF & addr);
    ENC28J60_REG_WRITE(ENC28J60_REG_EWRPTH,0xFF&(addr >> 8));
    ENC28J60_BUFFER_WRITE(buff);
}
void ENC28J60_MEM_BUFFER_READ(uint16_t addrmin,uint16_t addrmax,uint8_t buff[])
{
    int i = addrmin;
    for(i=addrmin ;i<addrmax+1;i++)
    {
        buff[i-addrmin] = ENC28J60_MEM_READ(i);
    }    
}
void ENC28J60_MEM_BUFFER_WRITE(uint16_t addrmin,uint16_t addrmax,uint8_t buff[])
{
    int i;
    for(i=addrmin;i<addrmax+1;i++)
    {
        ENC28J60_MEM_WRITE(i,buff[i-addrmin]);
    }    
}




















