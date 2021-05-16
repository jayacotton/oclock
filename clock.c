#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <string.h>

#include "sysface.h"
#include "font.h"

extern void oled_test();
extern void oled_draw_image(char *, int);
extern void oled_clean();
extern void oled_set_full_screen();
extern void oled_clear();
extern void oled_init();

#define O_Year 0
#define O_Month 1
#define O_Date 2
#define O_Hour 3
#define O_Minute 4
#define O_Second 5

#define MAXBUF 600
unsigned char image[MAXBUF];


#define CELLSIZE (132/8)
#define CELLSPACE CELLSIZE

/*  se have the display divided into 8 cells.
each cell holds a digit of the clock
offset is the character position 0 to 8

*/
//  work space dimensions
//  --> 128 columns
//  +----------------------------------~ ~ -----------+ v 32 bits
//  |----------------------------------~ ~ -----------|
//  |----------------------------------~ ~ -----------|
//  +----------------------------------~ ~ -----------+
//   ^ each column is a 32 bit work broken into 4 bytes.
//
// dx v
// dy >
//    bit 0      V
// scanline  0 > 1 0 0 0 0  etc.  v 8 bits      makes a \
//               0 1 0 0 0
//               0 0 1 0 0
//               0 0 0 1 0
//               0 0 0 0 1
//               0 0 0 0 0
//               0 0 0 0 0
//    bit 7   >  0 0 0 0 0      -> 127 bytes

// font returns a pointer to a bitmap of a character that is 6 wide and 10 high.
//
/* Character 49 (0x31):
   width 6
   +------+
   |      |
   |   *  |
   |  **  |
   |   *  |
   |   *  |
   |   *  |
   |   *  |
   |   *  |
   |      |
   |      |
   +------+ */

void placebits(unsigned char b, int row, int col)
{
	image[row+col] = b;
}

extern char *getbitmap(int);

void draw(char c, int o)
{
    int offset = CELLSIZE * o;
    unsigned char *pf;
    int width, height;
    char curbyte;
    int i;
    int j;

/* offset is number of pixels from left side of display */
    pf = (unsigned char *)getbitmap(c);
    for (j = 0; j < 8; j++) {
	for (i = 0; i < 8; i++) {
	    placebits(pf[i], i, offset + j);
	}
    }
}

void refresh()
{
    oled_draw_image(image, MAXBUF);
}

unsigned char *bcd_buffer;
void main()
{
    oled_init();
    oled_clear();
    oled_set_full_screen();
    memset(image, 0, MAXBUF);
    while (1) {
	bcd_buffer = GetTOD();
	draw(((bcd_buffer[O_Hour] >> 4) & 0xf) + 0x30, 0);
	draw(((bcd_buffer[O_Hour]) & 0xf) + 0x30, 1);
	draw(0x3a, 2);
	draw(((bcd_buffer[O_Minute] >> 4) & 0xf) + 0x30, 3);
	draw(((bcd_buffer[O_Minute]) & 0xf) + 0x30, 4);
	draw(0x3a, 5);
	draw(((bcd_buffer[O_Second] >> 4) & 0xf) + 0x30, 6);
	draw(((bcd_buffer[O_Second]) & 0xf) + 0x30, 7);
	if (bdos(CPM_ICON, 0))
	    exit(0);
// display time using bitmap font
	oled_set_full_screen();
	refresh();
	memset(image, 0, MAXBUF);
    }
}
