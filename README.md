# oclock
The oclock program displays time on an oled display.  This project works on rc2014 z80 processor with an RTC board.

The options I have are RTC/RAM-ROM/CF/SD/FRAM/ENET/Z180 and the oled display.

The liboled.c code is based on oled.s from Quazar.  The sysface code, interfaces to the RomWBW system code and CP/M.
Font.c is distilled from an X11 fixed font and paired down to the symbols needed for the clock.

When  reporting bugs, please include the contents of date.h, that really helps in figuring out where to look for
a bug.

