extern void oled_init();
extern void oled_test();
extern void oled_normal();
extern void oled_invert();
extern void oled_clear();
extern void oled_set_full_screen();
extern void oled_draw_image(char *, int);
extern void oled_command(char);
extern void oled_data(char);

char Sequence[] = {
    0xAE, 0xD5, 0xA0, 0xA8,
    0x1F, 0xD3, 0x00, 0xAD,
    0x8E, 0xD8, 0x05, 0xA1,
    0xC8, 0xDA, 0x12, 0x91,
    0x3F, 0x3F, 0x3F, 0x3F,
    0x81, 0x80, 0xD9, 0xD2,
    0xDB, 0x34, 0xA6, 0xA4,
    0xAF, 0xFF
};

char lchar;

void oled_clearrow()
{
    int i;
    oled_command(0x10);
    oled_command(4);
    for (i = 0; i < 0x80; i++) {
	oled_data(0);
    }

}

void oled_clear()
{
    oled_command(0xb0);
    oled_clearrow();
    oled_command(0xb1);
    oled_clearrow();
    oled_command(0xb2);
    oled_clearrow();
    oled_command(0xb3);
    oled_clearrow();
}

void oled_set_full_screen()
{
    oled_command(0x20);
    oled_command(0x0);
    oled_command(0x20);
    oled_command(0x4);
    oled_command(0x83);
    oled_command(0x22);
    oled_command(0x0);
    oled_command(0x3);
    oled_command(0xb0);
    oled_command(0x10);
    oled_command(0x4);
}

void oled_draw_image(char *data, size)
{
    int i;
    i = size;
    do {
	oled_data(*data);
	++data;
	--i;
    } while (i);
}

void oled_data(char c)
{
    lchar = c;
//*INDENT-OFF*
#asm
	ld 	c,050h
	ld	b,1
	ld	a,(_lchar)
	out	(c),a
	nop
	nop
	nop
	nop
	set	1,b
	out	(c),a
	nop
	nop
#endasm
//*INDENT-ON*
}

void oled_test()
{
    int i;
    oled_command(0xb0);
    oled_command(0x10);
    oled_command(4);
    i = 0;
    while (i <= 0x80) {
	oled_data(i++);
    }
}

void oled_command(char c)
{
    lchar = c;
//*INDENT-OFF*
#asm
	ld	c,050h
	ld	b,0
	ld	a,(_lchar)
	out	(c),a
	nop
	nop
	nop
	nop
	set	1,b		;  no idea why
	out	(c),a
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
#endasm
//*INDENT-ON*
}

void oled_reset()
{
//*INDENT-OFF*
#asm
	ld	c,050h
	ld	b,6
	out	(c),a	; dont understand what is being written 
	nop
	nop
	nop
	nop
	res	2,b
	out	(c),a
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
#endasm
//*INDENT-ON*
}

void oled_init()
{
    char *p;
    oled_reset();
    p = Sequence;
    while (*p != 0xFF)
	oled_command(*p++);
}
