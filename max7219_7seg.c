#include "max7219_7seg.h"

void max7219_mem(struct max7219_conf* conf, const char* c) {
	uint8_t col = 0;
	while((col<8)&&(pgm_read_byte(c)!=0)) {
		max7219_chr(conf,col,pgm_read_byte(c));
		col++;
		c++;
	}
}

void max7219_str(struct max7219_conf* conf, char* c) {
	uint8_t col = 0;
	while((col<8)&&(*c!=0)) {
		max7219_chr(conf,col,*c);
		col++;
		c++;
	}
}

void max7219_chr(struct max7219_conf* conf, uint8_t col, char c) {
	// correct column
	col = 8 - col;
	// invalid column exit
	if(col>8) return;
	// deal with out of range chars
	if((c<32)||(c>127)) {
		c = '#';
	}
	// send to display
	max7219_col(conf, col, pgm_read_byte(&(max7219_font[c-32])));
}

const uint8_t max7219_font[95] PROGMEM = {
	0b00000000, // 00 - 032 0x20  
	0b10110000, // 01 - 033 0x21 !
	0b00100010, // 02 - 034 0x22 “
	0b11111111, // 03 - 035 0x23 #
	0b01011011, // 04 - 036 0x24 $
	0b11111111, // 05 - 037 0x25 %
	0b11111111, // 06 - 038 0x26 &
	0b00000010, // 07 - 039 0x27 '
	0b01001110, // 08 - 040 0x28 (
	0b01111000, // 09 - 041 0x29 )
	0b00110111, // 10 - 042 0x2A *
	0b00110001, // 11 - 043 0x2B +
	0b10000000, // 12 - 044 0x2C ,
	0b00000001, // 13 - 045 0x2D -
	0b10000000, // 14 - 046 0x2E .
	0b00100101, // 15 - 047 0x2F /
	0b01111110, // 16 - 048 0x30 0
	0b00110000, // 17 - 049 0x31 1
	0b01101101, // 18 - 050 0x32 2
	0b01111001, // 19 - 051 0x33 3
	0b00110011, // 20 - 052 0x34 4
	0b01011011, // 21 - 053 0x35 5
	0b01011111, // 22 - 054 0x36 6
	0b01110000, // 23 - 055 0x37 7
	0b01111111, // 24 - 056 0x38 8
	0b01111011, // 25 - 057 0x39 9
	0b10010000, // 26 - 058 0x3A :
	0b10010000, // 27 - 059 0x3B ;
	0b00001101, // 28 - 060 0x3C <
	0b00001001, // 29 - 061 0x3D =
	0b00011001, // 30 - 062 0x3E >
	0b01100101, // 31 - 063 0x3F ?
	0b01110111, // 32 - 064 0x40 @
	0b01110111, // 33 - 065 0x41 A
	0b00011111, // 34 - 066 0x42 B
	0b01001110, // 35 - 067 0x43 C
	0b00111101, // 36 - 068 0x44 D
	0b01001111, // 37 - 069 0x45 E
	0b01000111, // 38 - 070 0x46 F
	0b01011110, // 39 - 071 0x47 G
	0b00100111, // 40 - 072 0x48 H
	0b00110000, // 41 - 073 0x49 I
	0b00111000, // 42 - 074 0x4A J
	0b00110111, // 43 - 075 0x4B K
	0b00001110, // 44 - 076 0x4C L
	0b00010101, // 45 - 077 0x4D M
	0b00010101, // 46 - 078 0x4E N
	0b00011101, // 47 - 079 0x4F O
	0b01100111, // 48 - 080 0x50 P
	0b11110011, // 49 - 081 0x51 Q
	0b00000101, // 50 - 082 0x52 R
	0b01011011, // 51 - 083 0x53 S
	0b00110001, // 52 - 084 0x54 T
	0b00011100, // 53 - 085 0x55 U
	0b00011100, // 54 - 086 0x56 V
	0b00011100, // 55 - 087 0x57 W
	0b00110111, // 56 - 088 0x58 X
	0b00110011, // 57 - 089 0x59 Y
	0b01101101, // 58 - 090 0x5A Z
	0b01001110, // 59 - 091 0x5B [
	0b00110011, // 60 - 092 0x5C ¥
	0b01111000, // 61 - 093 0x5D ]
	0b01100010, // 62 - 094 0x5E ^
	0b00001000, // 63 - 095 0x5F _
	0b00100000, // 64 - 096 0x60 `
	0b01110111, // 65 - 097 0x61 a
	0b00011111, // 66 - 098 0x62 b
	0b01001110, // 67 - 099 0x63 c
	0b00111101, // 68 - 100 0x64 d
	0b01001111, // 69 - 101 0x65 e
	0b01000111, // 70 - 102 0x66 f
	0b01011110, // 71 - 103 0x67 g
	0b00100111, // 72 - 104 0x68 h
	0b00110000, // 73 - 105 0x69 I
	0b00111000, // 74 - 106 0x6A j
	0b00110111, // 75 - 107 0x6B k
	0b00001110, // 76 - 108 0x6C l
	0b00010101, // 77 - 109 0x6D m
	0b00010101, // 78 - 110 0x6E n
	0b00011101, // 79 - 111 0x6F o
	0b01100111, // 80 - 112 0x70 p
	0b11110011, // 81 - 113 0x71 q
	0b00000101, // 82 - 114 0x72 r
	0b01011011, // 83 - 115 0x73 s
	0b00110001, // 84 - 116 0x74 t
	0b00011100, // 85 - 117 0x75 u
	0b00011100, // 86 - 118 0x76 v
	0b00011100, // 87 - 119 0x77 w
	0b00110111, // 88 - 120 0x78 x
	0b00110011, // 89 - 121 0x79 y
	0b01101101, // 90 - 122 0x7A z
	0b01001110, // 91 - 123 0x7B {
	0b00110000, // 92 - 124 0x7C |
	0b01111000, // 93 - 125 0x7D }
	0b00000001  // 94 - 126 0x7E ~
};
