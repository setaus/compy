/* Compact TFT Graphics Library v4 - see http://www.technoblogy.com/show?2LMJ
   David Johnson-Davies - www.technoblogy.com - 9th May 2022
   
   CC BY 4.0
   Licensed under a Creative Commons Attribution 4.0 International license: 
   http://creativecommons.org/licenses/by/4.0/
*/

//#include <SPI.h>
#include <stdint.h>
#include <stdBOOL.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <ST7735Hal.h>

// Arduino pin numbers. Change these for your display connections
//int const cs = 0; // TFT display SPI chip select pin
//int const dc = 1; // TFT display data/command select pin

// Display parameters - uncomment the line for the one you want to use

// Adafruit 1.44" 128x128 display
// int const xsize = 128, ysize = 128, xoff = 2, yoff = 1, invert = 0, rotate = 3, bgr = 1;

// AliExpress 1.44" 128x128 display
// int const xsize = 128, ysize = 128, xoff = 2, yoff = 1, invert = 0, rotate = 3, bgr = 1;

// Adafruit 0.96" 160x80 display
// int const xsize = 160, ysize = 80, xoff = 0, yoff = 24, invert = 0, rotate = 6, bgr = 1;

// AliExpress 0.96" 160x80 display
// int const xsize = 160, ysize = 80, xoff = 1, yoff = 26, invert = 1, rotate = 0, bgr = 1;

// Adafruit 1.8" 160x128 display
// int const xsize = 160, ysize = 128, xoff = 0, yoff = 0, invert = 0, rotate = 0, bgr = 1;

// AliExpress 1.8" 160x128 display (red PCB)
// int const xsize = 160, ysize = 128, xoff = 0, yoff = 0, invert = 0, rotate = 0, bgr = 1;

// AliExpress 1.8" 160x128 display (blue PCB)
int const xsize = 160, ysize = 128, xoff = 1, yoff = 2, invert = 0, rotate = 6, bgr = 0;

// Adafruit 1.14" 240x135 display
// int const xsize = 240, ysize = 135, xoff = 40, yoff = 53, invert = 1, rotate = 6, bgr = 0;

// AliExpress 1.14" 240x135 display
// int const xsize = 240, ysize = 135, xoff = 40, yoff = 52, invert = 1, rotate = 0, bgr = 0;

// Adafruit 1.3" 240x240 display
// int const xsize = 240, ysize = 240, xoff = 0, yoff = 80, invert = 1, rotate = 5, bgr = 0;

// Adafruit 1.54" 240x240 display
// int const xsize = 240, ysize = 240, xoff = 0, yoff = 80, invert = 1, rotate = 5, bgr = 0;

// AliExpress 1.54" 240x240 display
//int const xsize = 240, ysize = 240, xoff = 0, yoff = 80, invert = 1, rotate = 5, bgr = 0;

// Adafruit 1.9" 320x170 display
// int const xsize = 320, ysize = 170, xoff = 0, yoff = 35, invert = 1, rotate = 0, bgr = 0;

// Adafruit 2.0" 320x240 display
// int const xsize = 320, ysize = 240, xoff = 0, yoff = 0, invert = 1, rotate = 6, bgr = 0;

// Adafruit 2.2" 320x240 display
// int const xsize = 320, ysize = 240, xoff = 0, yoff = 0, invert = 0, rotate = 4, bgr = 1;

// AliExpress 2.4" 320x240 display
// int const xsize = 320, ysize = 240, xoff = 0, yoff = 0, invert = 0, rotate = 2, bgr = 1;

// Character set for text - stored in program memory
const uint8_t CharMap[96][6] = {
{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, 
{ 0x00, 0x00, 0x5F, 0x00, 0x00, 0x00 }, 
{ 0x00, 0x07, 0x00, 0x07, 0x00, 0x00 }, 
{ 0x14, 0x7F, 0x14, 0x7F, 0x14, 0x00 }, 
{ 0x24, 0x2A, 0x7F, 0x2A, 0x12, 0x00 }, 
{ 0x23, 0x13, 0x08, 0x64, 0x62, 0x00 }, 
{ 0x36, 0x49, 0x56, 0x20, 0x50, 0x00 }, 
{ 0x00, 0x08, 0x07, 0x03, 0x00, 0x00 }, 
{ 0x00, 0x1C, 0x22, 0x41, 0x00, 0x00 }, 
{ 0x00, 0x41, 0x22, 0x1C, 0x00, 0x00 }, 
{ 0x2A, 0x1C, 0x7F, 0x1C, 0x2A, 0x00 }, 
{ 0x08, 0x08, 0x3E, 0x08, 0x08, 0x00 }, 
{ 0x00, 0x80, 0x70, 0x30, 0x00, 0x00 }, 
{ 0x08, 0x08, 0x08, 0x08, 0x08, 0x00 }, 
{ 0x00, 0x00, 0x60, 0x60, 0x00, 0x00 }, 
{ 0x20, 0x10, 0x08, 0x04, 0x02, 0x00 }, 
{ 0x3E, 0x51, 0x49, 0x45, 0x3E, 0x00 }, 
{ 0x00, 0x42, 0x7F, 0x40, 0x00, 0x00 }, 
{ 0x72, 0x49, 0x49, 0x49, 0x46, 0x00 }, 
{ 0x21, 0x41, 0x49, 0x4D, 0x33, 0x00 }, 
{ 0x18, 0x14, 0x12, 0x7F, 0x10, 0x00 }, 
{ 0x27, 0x45, 0x45, 0x45, 0x39, 0x00 }, 
{ 0x3C, 0x4A, 0x49, 0x49, 0x31, 0x00 }, 
{ 0x41, 0x21, 0x11, 0x09, 0x07, 0x00 }, 
{ 0x36, 0x49, 0x49, 0x49, 0x36, 0x00 }, 
{ 0x46, 0x49, 0x49, 0x29, 0x1E, 0x00 }, 
{ 0x00, 0x00, 0x14, 0x00, 0x00, 0x00 }, 
{ 0x00, 0x40, 0x34, 0x00, 0x00, 0x00 }, 
{ 0x00, 0x08, 0x14, 0x22, 0x41, 0x00 }, 
{ 0x14, 0x14, 0x14, 0x14, 0x14, 0x00 }, 
{ 0x00, 0x41, 0x22, 0x14, 0x08, 0x00 }, 
{ 0x02, 0x01, 0x59, 0x09, 0x06, 0x00 }, 
{ 0x3E, 0x41, 0x5D, 0x59, 0x4E, 0x00 }, 
{ 0x7C, 0x12, 0x11, 0x12, 0x7C, 0x00 }, 
{ 0x7F, 0x49, 0x49, 0x49, 0x36, 0x00 }, 
{ 0x3E, 0x41, 0x41, 0x41, 0x22, 0x00 }, 
{ 0x7F, 0x41, 0x41, 0x41, 0x3E, 0x00 }, 
{ 0x7F, 0x49, 0x49, 0x49, 0x41, 0x00 }, 
{ 0x7F, 0x09, 0x09, 0x09, 0x01, 0x00 }, 
{ 0x3E, 0x41, 0x41, 0x51, 0x73, 0x00 }, 
{ 0x7F, 0x08, 0x08, 0x08, 0x7F, 0x00 }, 
{ 0x00, 0x41, 0x7F, 0x41, 0x00, 0x00 }, 
{ 0x20, 0x40, 0x41, 0x3F, 0x01, 0x00 }, 
{ 0x7F, 0x08, 0x14, 0x22, 0x41, 0x00 }, 
{ 0x7F, 0x40, 0x40, 0x40, 0x40, 0x00 }, 
{ 0x7F, 0x02, 0x1C, 0x02, 0x7F, 0x00 }, 
{ 0x7F, 0x04, 0x08, 0x10, 0x7F, 0x00 }, 
{ 0x3E, 0x41, 0x41, 0x41, 0x3E, 0x00 }, 
{ 0x7F, 0x09, 0x09, 0x09, 0x06, 0x00 }, 
{ 0x3E, 0x41, 0x51, 0x21, 0x5E, 0x00 }, 
{ 0x7F, 0x09, 0x19, 0x29, 0x46, 0x00 }, 
{ 0x26, 0x49, 0x49, 0x49, 0x32, 0x00 }, 
{ 0x03, 0x01, 0x7F, 0x01, 0x03, 0x00 }, 
{ 0x3F, 0x40, 0x40, 0x40, 0x3F, 0x00 }, 
{ 0x1F, 0x20, 0x40, 0x20, 0x1F, 0x00 }, 
{ 0x3F, 0x40, 0x38, 0x40, 0x3F, 0x00 }, 
{ 0x63, 0x14, 0x08, 0x14, 0x63, 0x00 }, 
{ 0x03, 0x04, 0x78, 0x04, 0x03, 0x00 }, 
{ 0x61, 0x59, 0x49, 0x4D, 0x43, 0x00 }, 
{ 0x00, 0x7F, 0x41, 0x41, 0x41, 0x00 }, 
{ 0x02, 0x04, 0x08, 0x10, 0x20, 0x00 }, 
{ 0x00, 0x41, 0x41, 0x41, 0x7F, 0x00 }, 
{ 0x04, 0x02, 0x01, 0x02, 0x04, 0x00 }, 
{ 0x40, 0x40, 0x40, 0x40, 0x40, 0x00 }, 
{ 0x00, 0x03, 0x07, 0x08, 0x00, 0x00 }, 
{ 0x20, 0x54, 0x54, 0x78, 0x40, 0x00 }, 
{ 0x7F, 0x28, 0x44, 0x44, 0x38, 0x00 }, 
{ 0x38, 0x44, 0x44, 0x44, 0x28, 0x00 }, 
{ 0x38, 0x44, 0x44, 0x28, 0x7F, 0x00 }, 
{ 0x38, 0x54, 0x54, 0x54, 0x18, 0x00 }, 
{ 0x00, 0x08, 0x7E, 0x09, 0x02, 0x00 }, 
{ 0x18, 0xA4, 0xA4, 0x9C, 0x78, 0x00 }, 
{ 0x7F, 0x08, 0x04, 0x04, 0x78, 0x00 }, 
{ 0x00, 0x44, 0x7D, 0x40, 0x00, 0x00 }, 
{ 0x20, 0x40, 0x40, 0x3D, 0x00, 0x00 }, 
{ 0x7F, 0x10, 0x28, 0x44, 0x00, 0x00 }, 
{ 0x00, 0x41, 0x7F, 0x40, 0x00, 0x00 }, 
{ 0x7C, 0x04, 0x78, 0x04, 0x78, 0x00 }, 
{ 0x7C, 0x08, 0x04, 0x04, 0x78, 0x00 }, 
{ 0x38, 0x44, 0x44, 0x44, 0x38, 0x00 }, 
{ 0xFC, 0x18, 0x24, 0x24, 0x18, 0x00 }, 
{ 0x18, 0x24, 0x24, 0x18, 0xFC, 0x00 }, 
{ 0x7C, 0x08, 0x04, 0x04, 0x08, 0x00 }, 
{ 0x48, 0x54, 0x54, 0x54, 0x24, 0x00 }, 
{ 0x04, 0x04, 0x3F, 0x44, 0x24, 0x00 }, 
{ 0x3C, 0x40, 0x40, 0x20, 0x7C, 0x00 }, 
{ 0x1C, 0x20, 0x40, 0x20, 0x1C, 0x00 }, 
{ 0x3C, 0x40, 0x30, 0x40, 0x3C, 0x00 }, 
{ 0x44, 0x28, 0x10, 0x28, 0x44, 0x00 }, 
{ 0x4C, 0x90, 0x90, 0x90, 0x7C, 0x00 }, 
{ 0x44, 0x64, 0x54, 0x4C, 0x44, 0x00 }, 
{ 0x00, 0x08, 0x36, 0x41, 0x00, 0x00 }, 
{ 0x00, 0x00, 0x77, 0x00, 0x00, 0x00 }, 
{ 0x00, 0x41, 0x36, 0x08, 0x00, 0x00 }, 
{ 0x00, 0x06, 0x09, 0x06, 0x00, 0x00 },  // degree symbol = '~'
{ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00 }
};

// TFT colour display **********************************************

int const CASET = 0x2A; // Define column address
int const RASET = 0x2B; // Define row address
int const RAMWR = 0x2C; // Write to display RAM

// Globals - current plot position and colours
int xpos, ypos;
int fore = 0xFFFF; // White
int back = 0;      // Black
int scale = 1;     // Text scale

static uint8_t spi_buf[128*3];

void SetFore(int f)
{
	fore = f;
}

// Send a byte to the display
void Data (uint8_t d) {
  digitalWrite(CS, LOW);
  SPI_transfer(&d, 1);
  digitalWrite(CS, HIGH);
}

// Send a byte to the display
void Datas (int len)
{
  digitalWrite(CS, LOW);
  SPI_transfer(spi_buf, len);
  digitalWrite(CS, HIGH);
}

// Send a command to the display
void Command (uint8_t c) {
  digitalWrite(DC, LOW);
  Data(c);
  digitalWrite(DC, HIGH);
}

// Send a command followed by two data words
void Command2 (uint8_t c, uint16_t d1, uint16_t d2) {
  digitalWrite(DC, LOW);
  Data(c);
  digitalWrite(DC, HIGH);
  spi_buf[0] = d1>>8;
  spi_buf[1] = d1;
  spi_buf[2] = d2>>8;
  spi_buf[3] = d2;
  Datas(4);
}
  
void InitDisplay () {
	printf("%s\n", __FUNCTION__);
  pinMode(DC, OUTPUT);
  pinMode(CS, OUTPUT);
  digitalWrite(CS, HIGH);
  digitalWrite(DC, HIGH);                  // Data
  SPI_begin();
  Command(0x01);                           // Software reset
  delay(250);                              // delay 250 ms
  Command(0x36); Data(rotate<<5 | bgr<<3); // Set orientation and rgb/bgr
  Command(0x3A); Data(0x55);               // Set color mode - 16-bit color
  Command(0x20+invert);                    // Invert
  Command(0x11);                           // Out of sleep mode
  delay(150);
}

void DisplayOn () {
	printf("%s\n", __FUNCTION__);
  Command(0x29);                           // Display on
  delay(150);
}

void ClearDisplay () {
	printf("%s\n", __FUNCTION__);
  Command2(CASET, yoff, yoff + ysize - 1);
  Command2(RASET, xoff, xoff + xsize - 1);
  Command(0x3A); Data(0x03);               // 12-bit colour
  Command(RAMWR);
  for (int i=0; i<xsize/2; i++)
  {
	  bzero(spi_buf,ysize*3);
	  Datas(ysize*3);
  }
  Command(0x3A); Data(0x05);               // Back to 16-bit colour
}

unsigned int Colour (int r, int g, int b) {
  return (r & 0xf8)<<8 | (g & 0xfc)<<3 | b>>3;
}

// Move current plot position to x,y
void MoveTo (int x, int y)
{
  xpos = x; ypos = y;
}

// Plot point at x,y
void PlotPoint (int x, int y) {
  Command2(CASET, yoff+y, yoff+y);
  Command2(RASET, xoff+x, xoff+x);
  Command(RAMWR);
  spi_buf[0]=fore>>8;
  spi_buf[1]=fore & 0xff;
  Datas(2);
}

// Draw a line to x,y
void DrawTo (int x, int y) {
  int sx, sy, e2, err;
  int dx = abs(x - xpos);
  int dy = abs(y - ypos);
  if (xpos < x)
	  sx = 1;
  else
	  sx = -1;
  if (ypos < y)
	  sy = 1;
  else
	  sy = -1;
  err = dx - dy;
  for (;;) {
    PlotPoint(xpos, ypos);
    if (xpos==x && ypos==y)
    	return;
    e2 = err<<1;
    if (e2 > -dy)
    {
    	err = err - dy;
    	xpos = xpos + sx;
    }
    if (e2 < dx)
    {
    	err = err + dx;
    	ypos = ypos + sy;
    }
  }
}

void FillRect (int w, int h)
{
	Command2(CASET, ypos+yoff, ypos+yoff+h-1);
	Command2(RASET, xpos+xoff, xpos+xoff+w-1);
	Command(RAMWR);
	for (int i=0; i<w; i++)
	{
		for (int j=0; j<h; j++)
		{
			spi_buf[j*2]=fore>>8;
			spi_buf[j*2+1]=fore&0xff;
		}
		Datas(h*2);
/*
		for (int j=0; j<h; j++)
		{
			spi_buf[0]=fore>>8;
			spi_buf[1]=fore&0xff;
			Datas(2);
		}
		*/
	}
}

// Plot an ASCII character with bottom left corner at x,y
void PlotChar (char c)
{
	int colour;
	Command2(CASET, yoff+ypos, yoff+ypos+8*scale-1);
	Command2(RASET, xoff+xpos, xoff+xpos+6*scale-1);
	Command(RAMWR);
	for (int xx=0; xx<6; xx++)
	{
		int bits = pgm_read_byte(&CharMap[c-32][xx]);
		int idx=0;
		for (int xr=0; xr<scale; xr++)
		{
			for (int yy=0; yy<8; yy++)
			{
				if (bits>>(7-yy) & 1)
				{
					colour = fore;
				}
				else
				{
					colour = back;
				}
				for (int yr=0; yr<scale; yr++)
				{
					spi_buf[idx++]=colour>>8;
					spi_buf[idx++]=colour&0xff;
				}
			}
		}
		Datas(scale*scale*8*2);
	}
	xpos = xpos + 6*scale;
}

// Plot text starting at the current plot position
void PlotText(PGM_P p) {
  while (1) {
    char c = pgm_read_byte(p++);
    if (c == 0) return;
    PlotChar(c);
  }
}

void PlotInt(int n, bool plus)
{
	if (n<0)
	{
		PlotChar('-');
		n=-n;
	}
	else if (n>0 && plus)
	{
		PlotChar('+');
	}

	bool lead = false;
	for (int d=10000; d>0; d = d/10)
	{
		char j = (n/d) % 10;
		if (j!=0 || lead || d==1)
		{
			PlotChar(j + '0');
			lead = true;
		}
	}
}

void TestChart () {
  MoveTo(0,0);
  DrawTo(xsize-1, 0); DrawTo(xsize-1, ysize-1);
  DrawTo(0, ysize-1); DrawTo(0, 0);
  scale = 8;
  MoveTo((xsize-40)/2, (ysize-64)/2); PlotChar('F');
  scale = 1;
}

// Demos **********************************************
void BarChart ()
{
	int x1 = 15, y1 = 11; // Origin
	// Text
	MoveTo((xsize-x1-90)/2+x1, ysize-8);
	PlotText((uint8_t *)PSTR("Sensor Readings"));
	// Horizontal axis
	int xinc = (xsize-x1)/20;
	MoveTo(x1, y1);
	DrawTo(xsize-1, y1);
	for (int i=0; i<=20; i=i+4)
	{
		int mark = x1+i*xinc;
		MoveTo(mark, y1);
		DrawTo(mark, y1-2);
		// Draw histogram
		if (i != 20)
		{
			int bar = xinc*4/3;
			fore = 0x001F;
			for (int b=2; b>=0; b--)
			{
				MoveTo(mark+bar*b-b+1,y1+1); FillRect(bar, 5+random_up_to(ysize-y1-20));
				fore = fore<<6;
			}
			fore = 0xFFFF;
		}
		if (i > 9) MoveTo(mark-7, y1-11); else MoveTo(mark-3, y1-11);
		PlotInt(i, false);
	}
	// Vertical axis
	int yinc = (ysize-y1)/20;
	MoveTo(x1, y1); DrawTo(x1, ysize-1);
	for (int i=0; i<=20; i=i+5)
	{
		int mark = y1+i*yinc;
		MoveTo(x1, mark); DrawTo(x1-2, mark);
		if (i > 9)
			MoveTo(x1-15, mark-4);
		else
			MoveTo(x1-9, mark-4);
		PlotInt(i, false);
	}
}

// Setup **********************************************

void setup() {
  InitDisplay();
  ClearDisplay();
  DisplayOn();
  MoveTo(0,0);
}

void loop ()
{
	  BarChart();
}
