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
#include "ENC28J60lib.h"


void ENC28J60_LIB_ALLRESET(void)
{
    ENC28J60_SYSTEM_RESET();
    ENC28J60_PHY_WRITE(ENC28J60_PHCON1,PHCON1_PRST);
    ENC28J60_REG_WRITE(ENC28J60_REG_ECON1,ECON1_TXRST|ECON1_RXRST);
    ENC28J60_REG_WRITE(ENC28J60_REG_ECON1,0x00);
}

void ENC28J60_LIB_INIT(void)
{
    ENC28J60_REG_WRITE(ENC28J60_REG_MACON1,MACON1_MARXEN |MACON1_PASSALL| MACON1_TXPAUS | MACON1_RXPAUS);
    //ENC28J60_REG_WRITE(ENC28J60_REG_MACON2,0x00);
    
    //ENC28J60_REG_WRITE(ENC28J60_REG_MACON3, MACON3_FULDPX| MACON3_PADCFG0 |  MACON3_TXCRCEN  );  
    ENC28J60_REG_WRITE(ENC28J60_REG_MACON3,  MACON3_PADCFG0 |  MACON3_TXCRCEN  );  
    
    ENC28J60_REG_WRITE(ENC28J60_REG_MACON4, 0x00);

     unsigned int limit = 1518;  // 6+6+2+1500+4
    // 1518 is the IEEE 802.3 specified limit    
    ENC28J60_REG_WRITE(ENC28J60_REG_MAMXFLL, 0x00FF&limit);  
    ENC28J60_REG_WRITE(ENC28J60_REG_MAMXFLH, 0x00FF&(limit>>8));
    ENC28J60_REG_WRITE(ENC28J60_REG_MABBIPG, 0x15);
    ENC28J60_REG_WRITE(ENC28J60_REG_MAIPGL, 0x12);
    ENC28J60_REG_WRITE(ENC28J60_REG_MAIPGH, 0x0C);
    //ENC28J60_PHY_WRITE(ENC28J60_PHCON1,PHCON1_PDPXMD);
    ENC28J60_PHY_WRITE(ENC28J60_PHCON1,0x00);
    
    //ENC28J60_PHY_WRITE(ENC28J60_REG_EFLOCON,0x02);
    ENC28J60_PHY_WRITE(ENC28J60_REG_EFLOCON,0x01);
    ENC28J60_PHY_WRITE(ENC28J60_PHCON2,PHCON2_HDLDIS);
}

void ENC28J60_LIB_MACADDR(uint8_t MACADDR[])
{
    ENC28J60_REG_WRITE(ENC28J60_REG_MAADR1, MACADDR[0]);
    ENC28J60_REG_WRITE(ENC28J60_REG_MAADR2, MACADDR[1]);
    ENC28J60_REG_WRITE(ENC28J60_REG_MAADR3, MACADDR[2]);
    ENC28J60_REG_WRITE(ENC28J60_REG_MAADR4, MACADDR[3]);
    ENC28J60_REG_WRITE(ENC28J60_REG_MAADR5, MACADDR[4]);
    ENC28J60_REG_WRITE(ENC28J60_REG_MAADR6, MACADDR[5]);
}

void ENC28J60_LIB_MEMORRY_SETTING(uint16_t rxstart,uint16_t rxstop,uint16_t txstart,uint16_t txstop)
{
    //--- Memory address Setting ====//
    ENC28J60_REG_WRITE(ENC28J60_REG_ERXSTL, rxstart);
    ENC28J60_REG_WRITE(ENC28J60_REG_ERXSTH, rxstart>>8);
    ENC28J60_REG_WRITE(ENC28J60_REG_ERXRDPTL,rxstart);    
    ENC28J60_REG_WRITE(ENC28J60_REG_ERXRDPTH,rxstart>>8);  
    ENC28J60_REG_WRITE(ENC28J60_REG_ERXNDL, rxstop);
    ENC28J60_REG_WRITE(ENC28J60_REG_ERXNDH, rxstop>>8);
    ENC28J60_REG_WRITE(ENC28J60_REG_ETXSTL, txstart);
    ENC28J60_REG_WRITE(ENC28J60_REG_ETXSTH, txstart>>8);
    ENC28J60_REG_WRITE(ENC28J60_REG_ETXNDL, 0x00FF&txstop);
    ENC28J60_REG_WRITE(ENC28J60_REG_ETXNDH, 0x00FF&(txstop>>8));
}
void ENC28J60_LIB_WRITE(uint16_t start,uint16_t stop,uint8_t buff[])
{
    ENC28J60_MEM_BUFFER_WRITE(TXSTART_INIT+1+start,TXSTART_INIT+1+stop,buff);        
}
void ENC28J60_LIB_SEND(void)
{
    ENC28J60_MEM_WRITE(TXSTART_INIT,PKTCTRL_POVERRIDE | PKTCTRL_PCRCEN|PKTCTRL_PPADEN|PKTCTRL_PHUGEEN);
    ENC28J60_REG_WRITE(ENC28J60_REG_ECON1, ECON1_CSUMEN|ECON1_TXRTS|ECON1_RXEN);
}
uint16_t ENC28J60_LIB_READ(uint16_t start,uint8_t buff[])
{
    uint8_t status_buff[7];
    ENC28J60_MEM_BUFFER_READ(start,start+6,status_buff);
    uint16_t next = (status_buff[1]<<8) | status_buff[0];
    
    uint16_t read_len;
    if(next!=0x00)
    {
        read_len= ((status_buff[3]<<8) | status_buff[2])-6-4;
        ENC28J60_MEM_BUFFER_READ(start+6,start+6+read_len,buff);
    }
    else
    {
        read_len = 0;
    }
    return read_len;
}



