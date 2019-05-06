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

#ifndef ENC28J60LIB_H
#define	ENC28J60LIB_H
void ENC28J60_LIB_ALLRESET(void);
void ENC28J60_LIB_INIT(void);
void ENC28J60_LIB_MACADDR(uint8_t MACADDR[]);
void ENC28J60_LIB_MEMORRY_SETTING(uint16_t rxstart,uint16_t rxstop,uint16_t txstart,uint16_t txstop);
void ENC28J60_LIB_WRITE(uint16_t start,uint16_t stop,uint8_t buff[]);
void ENC28J60_LIB_SEND(void);

uint16_t ENC28J60_LIB_READ(uint16_t start,uint8_t buff[]);


#endif	

