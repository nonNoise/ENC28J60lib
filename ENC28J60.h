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

#ifndef ENC28J60_H
#define ENC28J60_H

//#include "mcc_generated_files/mcc.h"
#include <stdio.h>
#include <string.h> 
#include <stdlib.h>
#include <math.h>
#include <sys/attribs.h>
#include "mcc_generated_files/mcc.h"

#define ENC28J60_OPC_RCR (0x00)
#define ENC28J60_OPC_RBM (0x3A)
#define ENC28J60_OPC_WCR (0x40)
#define ENC28J60_OPC_WBM (0x7A)
#define ENC28J60_OPC_BFS (0x80)
#define ENC28J60_OPC_BFC (0xA0)
#define ENC28J60_OPC_SRC (0xFF)

#define ENC28J60_BANK0      0x00
#define ENC28J60_BANK1      0x20
#define ENC28J60_BANK2      0x40
#define ENC28J60_BANK3      0x60
#define ENC28J60_MREG       0x80

#define ENC28J60_REG_EIE             0x1B
#define ENC28J60_REG_EIR             0x1C
#define ENC28J60_REG_ESTAT           0x1D
#define ENC28J60_REG_ECON2           0x1E
#define ENC28J60_REG_ECON1           0x1F
//---- Bank 0 ------------------------------------------
#define ENC28J60_REG_ERDPTL          (0x00| ENC28J60_BANK0)
#define ENC28J60_REG_ERDPTH          (0x01| ENC28J60_BANK0)
#define ENC28J60_REG_EWRPTL          (0x02| ENC28J60_BANK0)
#define ENC28J60_REG_EWRPTH          (0x03| ENC28J60_BANK0)
#define ENC28J60_REG_ETXSTL          (0x04| ENC28J60_BANK0)
#define ENC28J60_REG_ETXSTH          (0x05| ENC28J60_BANK0)
#define ENC28J60_REG_ETXNDL          (0x06| ENC28J60_BANK0)
#define ENC28J60_REG_ETXNDH          (0x07| ENC28J60_BANK0)
#define ENC28J60_REG_ERXSTL          (0x08| ENC28J60_BANK0)
#define ENC28J60_REG_ERXSTH          (0x09| ENC28J60_BANK0)
#define ENC28J60_REG_ERXNDL          (0x0A| ENC28J60_BANK0)
#define ENC28J60_REG_ERXNDH          (0x0B| ENC28J60_BANK0)
#define ENC28J60_REG_ERXRDPTL        (0x0C| ENC28J60_BANK0)
#define ENC28J60_REG_ERXRDPTH        (0x0D| ENC28J60_BANK0)
#define ENC28J60_REG_ERXWRPTL        (0x0E| ENC28J60_BANK0)
#define ENC28J60_REG_ERXWRPTH        (0x0F| ENC28J60_BANK0)
#define ENC28J60_REG_EDMASTL         (0x10| ENC28J60_BANK0)
#define ENC28J60_REG_EDMASTH         (0x11| ENC28J60_BANK0)
#define ENC28J60_REG_EDMANDL         (0x12| ENC28J60_BANK0)
#define ENC28J60_REG_EDMANDH         (0x13| ENC28J60_BANK0)
#define ENC28J60_REG_EDMADSTL        (0x14| ENC28J60_BANK0)
#define ENC28J60_REG_EDMADSTH        (0x15| ENC28J60_BANK0)
#define ENC28J60_REG_EDMACSL         (0x16| ENC28J60_BANK0)
#define ENC28J60_REG_EDMACSH         (0x17| ENC28J60_BANK0)
//---- Bank 1 ------------------------------------------
#define ENC28J60_REG_EHT0             (0x00| ENC28J60_BANK1)
#define ENC28J60_REG_EHT1             (0x01| ENC28J60_BANK1)
#define ENC28J60_REG_EHT2             (0x02| ENC28J60_BANK1)
#define ENC28J60_REG_EHT3             (0x03| ENC28J60_BANK1)
#define ENC28J60_REG_EHT4             (0x04| ENC28J60_BANK1)
#define ENC28J60_REG_EHT5             (0x05| ENC28J60_BANK1)
#define ENC28J60_REG_EHT6             (0x06| ENC28J60_BANK1)
#define ENC28J60_REG_EHT7             (0x07| ENC28J60_BANK1)
#define ENC28J60_REG_EPMM0            (0x08| ENC28J60_BANK1)
#define ENC28J60_REG_EPMM1            (0x09| ENC28J60_BANK1)
#define ENC28J60_REG_EPMM2            (0x0A| ENC28J60_BANK1)
#define ENC28J60_REG_EPMM3            (0x0B| ENC28J60_BANK1)
#define ENC28J60_REG_EPMM4            (0x0C| ENC28J60_BANK1)
#define ENC28J60_REG_EPMM5            (0x0D| ENC28J60_BANK1)
#define ENC28J60_REG_EPMM6            (0x0E| ENC28J60_BANK1)
#define ENC28J60_REG_EPMM7            (0x0F| ENC28J60_BANK1)
#define ENC28J60_REG_EPMCSL           (0x10| ENC28J60_BANK1)
#define ENC28J60_REG_EPMCSH           (0x11| ENC28J60_BANK1)
#define ENC28J60_REG_EPMOL            (0x14| ENC28J60_BANK1)
#define ENC28J60_REG_EPMOH            (0x15| ENC28J60_BANK1)
#define ENC28J60_REG_EWOLIE           (0x16| ENC28J60_BANK1)
#define ENC28J60_REG_EWOLIR           (0x17| ENC28J60_BANK1)
#define ENC28J60_REG_ERXFCON          (0x18| ENC28J60_BANK1)
#define ENC28J60_REG_EPKTCNT          (0x19| ENC28J60_BANK1)
//---- Bank 2 ------------------------------------------
#define ENC28J60_REG_MACON1           (0x00| ENC28J60_BANK2| ENC28J60_MREG)
#define ENC28J60_REG_MACON2           (0x01| ENC28J60_BANK2| ENC28J60_MREG)
#define ENC28J60_REG_MACON3           (0x02| ENC28J60_BANK2| ENC28J60_MREG)
#define ENC28J60_REG_MACON4           (0x03| ENC28J60_BANK2| ENC28J60_MREG)
#define ENC28J60_REG_MABBIPG          (0x04| ENC28J60_BANK2| ENC28J60_MREG)
#define ENC28J60_REG_MAIPGL           (0x06| ENC28J60_BANK2| ENC28J60_MREG)
#define ENC28J60_REG_MAIPGH           (0x07| ENC28J60_BANK2| ENC28J60_MREG)
#define ENC28J60_REG_MACLCON1         (0x08| ENC28J60_BANK2| ENC28J60_MREG)
#define ENC28J60_REG_MACLCON2         (0x09| ENC28J60_BANK2| ENC28J60_MREG)
#define ENC28J60_REG_MAMXFLL          (0x0A| ENC28J60_BANK2| ENC28J60_MREG)
#define ENC28J60_REG_MAMXFLH          (0x0B| ENC28J60_BANK2| ENC28J60_MREG)
#define ENC28J60_REG_MAPHSUP          (0x0D| ENC28J60_BANK2| ENC28J60_MREG)
#define ENC28J60_REG_MICON            (0x11| ENC28J60_BANK2| ENC28J60_MREG)
#define ENC28J60_REG_MICMD            (0x12| ENC28J60_BANK2| ENC28J60_MREG)
#define ENC28J60_REG_MIREGADR         (0x14| ENC28J60_BANK2| ENC28J60_MREG)
#define ENC28J60_REG_MIWRL            (0x16| ENC28J60_BANK2| ENC28J60_MREG)
#define ENC28J60_REG_MIWRH            (0x17| ENC28J60_BANK2| ENC28J60_MREG)
#define ENC28J60_REG_MIRDL            (0x18| ENC28J60_BANK2| ENC28J60_MREG)
#define ENC28J60_REG_MIRDH            (0x19| ENC28J60_BANK2| ENC28J60_MREG)
//---- Bank 3 ------------------------------------------
#define ENC28J60_REG_MAADR5           (0x00| ENC28J60_BANK3| ENC28J60_MREG)
#define ENC28J60_REG_MAADR6           (0x01| ENC28J60_BANK3| ENC28J60_MREG)
#define ENC28J60_REG_MAADR3           (0x02| ENC28J60_BANK3| ENC28J60_MREG)
#define ENC28J60_REG_MAADR4           (0x03| ENC28J60_BANK3| ENC28J60_MREG)
#define ENC28J60_REG_MAADR1           (0x04| ENC28J60_BANK3| ENC28J60_MREG)
#define ENC28J60_REG_MAADR2           (0x05| ENC28J60_BANK3| ENC28J60_MREG)
#define ENC28J60_REG_EBSTSD           (0x06| ENC28J60_BANK3)
#define ENC28J60_REG_EBSTCON          (0x07| ENC28J60_BANK3)
#define ENC28J60_REG_EBSTCSL          (0x08| ENC28J60_BANK3)
#define ENC28J60_REG_EBSTCSH          (0x09| ENC28J60_BANK3)
#define ENC28J60_REG_MISTAT           (0x0A| ENC28J60_BANK3| ENC28J60_MREG)
#define ENC28J60_REG_EREVID           (0x12| ENC28J60_BANK3)
#define ENC28J60_REG_ECOCON           (0x15| ENC28J60_BANK3)
#define ENC28J60_REG_EFLOCON          (0x17| ENC28J60_BANK3)
#define ENC28J60_REG_EPAUSL           (0x18| ENC28J60_BANK3)
#define ENC28J60_REG_EPAUSH           (0x19| ENC28J60_BANK3)
//---- PHY REG ------------------------------------------
#define ENC28J60_PHCON1		0x00
#define ENC28J60_PHSTAT1	0x01
#define ENC28J60_PHHID1		0x02
#define ENC28J60_PHHID2		0x03
#define ENC28J60_PHCON2		0x10
#define ENC28J60_PHSTAT2	0x11
#define ENC28J60_PHIE		0x12
#define ENC28J60_PHIR		0x13
#define ENC28J60_PHLCON     0x14

//---- ERXFCON REG BIT -------------------------------------
#define ERXFCON_UCEN     0x80
#define ERXFCON_ANDOR    0x40
#define ERXFCON_CRCEN    0x20
#define ERXFCON_PMEN     0x10
#define ERXFCON_MPEN     0x08
#define ERXFCON_HTEN     0x04
#define ERXFCON_MCEN     0x02
#define ERXFCON_BCEN     0x01
//---- EIE REG BIT -------------------------------------
#define EIE_INTIE        0x80
#define EIE_PKTIE        0x40
#define EIE_DMAIE        0x20
#define EIE_LINKIE       0x10
#define EIE_TXIE         0x08
#define EIE_WOLIE        0x04
#define EIE_TXERIE       0x02
#define EIE_RXERIE       0x01
//---- EIR REG BIT -------------------------------------
#define EIR_PKTIF        0x40
#define EIR_DMAIF        0x20
#define EIR_LINKIF       0x10
#define EIR_TXIF         0x08
#define EIR_WOLIF        0x04
#define EIR_TXERIF       0x02
#define EIR_RXERIF       0x01
//---- ESTAT REG BIT -------------------------------------
#define ESTAT_INT        0x80
#define ESTAT_LATECOL    0x10
#define ESTAT_RXBUSY     0x04
#define ESTAT_TXABRT     0x02
#define ESTAT_CLKRDY     0x01
//---- ECON2 REG BIT -------------------------------------
#define ECON2_AUTOINC    0x80
#define ECON2_PKTDEC     0x40
#define ECON2_PWRSV      0x20
#define ECON2_VRPS       0x08
// ENC28J60 ECON1 Register Bit Definitions
#define ECON1_TXRST      0x80
#define ECON1_RXRST      0x40
#define ECON1_DMAST      0x20
#define ECON1_CSUMEN     0x10
#define ECON1_TXRTS      0x08
#define ECON1_RXEN       0x04
#define ECON1_BSEL1      0x02
#define ECON1_BSEL0      0x01
//---- MACON1 REG BIT -------------------------------------
#define MACON1_LOOPBK    0x10
#define MACON1_TXPAUS    0x08
#define MACON1_RXPAUS    0x04
#define MACON1_PASSALL   0x02
#define MACON1_MARXEN    0x01
//---- MACON3 REG BIT -------------------------------------
#define MACON3_PADCFG2   0x80
#define MACON3_PADCFG1   0x40
#define MACON3_PADCFG0   0x20
#define MACON3_TXCRCEN   0x10
#define MACON3_PHDRLEN   0x08
#define MACON3_HFRMLEN   0x04
#define MACON3_FRMLNEN   0x02
#define MACON3_FULDPX    0x01
//---- MACON4 REG BIT -------------------------------------
#define	MACON4_DEFER	0x40
#define	MACON4_BPEN		0x20
#define	MACON4_NOBKOFF	0x10

//---- MICMD REG BIT -------------------------------------
#define MICMD_MIISCAN    0x02
#define MICMD_MIIRD      0x01
//---- MISTAT REG BIT -------------------------------------
#define MISTAT_NVALID    0x04
#define MISTAT_SCAN      0x02
#define MISTAT_BUSY      0x01
//---- EBSTCON REG BIT -------------------------------------
#define EBSTCON_PSV2     0x80
#define EBSTCON_PSV1     0x40
#define EBSTCON_PSV0     0x20
#define EBSTCON_PSEL     0x10
#define EBSTCON_TMSEL1   0x08
#define EBSTCON_TMSEL0   0x04
#define EBSTCON_TME      0x02
#define EBSTCON_BISTST    0x01
//---- PHCON1 REG BIT -------------------------------------
#define PHCON1_PRST      0x8000
#define PHCON1_PLOOPBK   0x4000
#define PHCON1_PPWRSV    0x0800
#define PHCON1_PDPXMD    0x0100
//---- PHSTAT1 REG BIT -------------------------------------
#define PHSTAT1_PFDPX    0x1000
#define PHSTAT1_PHDPX    0x0800
#define PHSTAT1_LLSTAT   0x0004
#define PHSTAT1_JBSTAT   0x0002
//---- PHCON2 REG BIT -------------------------------------
#define PHCON2_FRCLINK   0x4000
#define PHCON2_TXDIS     0x2000
#define PHCON2_JABBER    0x0400
#define PHCON2_HDLDIS    0x0100
//---- PKTCTRL REG BIT -------------------------------------
#define PKTCTRL_PHUGEEN  0x08
#define PKTCTRL_PPADEN   0x04
#define PKTCTRL_PCRCEN   0x02
#define PKTCTRL_POVERRIDE 0x01


#define RXSTART_INIT        0x0
// receive buffer end
#define RXSTOP_INIT         0x800       //0x7FF   //(0x1FFF-0x0600-1)
// start TX buffer at 0x1FFF-0x0600,
// space for one full ethernet frame (~1500 bytes)
#define TXSTART_INIT        0x0900   //(0x1FFF-0x0600)
// stp TX buffer at end of mem
#define TXSTOP_INIT         0x1000  //0x1FFF

#define RXSIZE (RXSTOP_INIT - RXSTART_INIT + 1)
#define TXSIZE (TXSTOP_INIT - TXSTART_INIT + 1)

uint8_t SPI_8bit_Read(void);
void SPI_8bit_Write(uint8_t wdata);
uint8_t ENC28J60_CONTROL_READ(uint8_t addr);
void  ENC28J60_CONTROL_WRITE(uint8_t addr,uint8_t wdata);

#endif