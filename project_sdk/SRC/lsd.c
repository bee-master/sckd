#include "aduc812.h"
#include "max.h"

void delay(unsigned short x)
{
	unsigned short i = 0;
        for(i = 0; i < x; i++)
	{
		i*i*i*i*i*i;
	}
}

unsigned char get_bf_ac()
{
	unsigned char result;
	write_max(8, C_IND, 0x03);
	result = read_max(8, DATA_IND);
	write_max(8, C_IND, 0x02);
	return result;
}

unsigned char bf_clear()
{
        unsigned char buff;
        buff = get_bf_ac();

	if ((buff & 0x7f) == 0x10)
	{
		write_max(8, DATA_IND, 0xC0);
		write_max(8, C_IND, 0x01);
		write_max(8, C_IND, 0x00);
	}

	if ((buff & 0x7f) == 0x50)
	{
		write_max(8, DATA_IND, 0x80);
		write_max(8, C_IND, 0x01);
		write_max(8, C_IND, 0x00);
	}

        if (buff >= 128)
                return 0;
        else
                return 1;
}

void goto_x (unsigned char position)
{
		position = position | 0x80;
		write_max(8, DATA_IND, position);
		write_max(8, C_IND, 0x01);
		write_max(8, C_IND, 0x00);
}

unsigned char utf2sdk (unsigned int ch)
{
	switch(ch)
	{
		case ' ': return 32;
		case '!': return 33;
		case '"': return 34;
		case '#': return 35;
		case '$': return 36;
		case '%': return 37;
		case '&': return 38;
		case '\'': return 39;
		case '(': return 40;
		case ')': return 41;
		case '*': return 42;
		case '+': return 43;
		case ',': return 44;
		case '-': return 45;
		case '.': return 46;
		case '/': return 47;
		case '0': return 48;
		case '1': return 49;
		case '2': return 50;
		case '3': return 51;
		case '4': return 52;
		case '5': return 53;
		case '6': return 54;
		case '7': return 55;
		case '8': return 56;
		case '9': return 57;
		case ':': return 58;
		case ';': return 59;
		case '<': return 60;
		case '=': return 61;
		case '>': return 62;
		case '?': return 63;
		case '@': return 64;
		case 'A': return 65;
		case '�': return 65;
		case 'B': return 66;
		case '�': return 66;
		case 'C': return 67;
		case '�': return 67;
		case 'D': return 68;
		case 'E': return 69;
		case '�': return 69;
		case 'F': return 70;
		case 'G': return 71;
		case 'H': return 72;
		case '�': return 72;
		case 'I': return 73;
		case 'J': return 74;
		case 'K': return 75;
		case '�': return 75;
		case 'L': return 76;
		case 'M': return 77;
		case '�': return 77;
		case 'N': return 78;
		case 'O': return 79;
		case '�': return 79;
		case 'P': return 80;
		case '�': return 80;
		case 'Q': return 81;
		case 'R': return 82;
		case 'S': return 83;
		case 'T': return 84;
		case '�': return 84;
		case 'U': return 85;
		case 'V': return 86;
		case 'W': return 87;
		case 'X': return 88;
		case '�': return 88;
		case 'Y': return 89;
		case 'Z': return 90;
		case '[': return 91;
		case ']': return 93;
		case '^': return 94;
		case '_': return 95;
		case '`': return 96;
		case 'a': return 97;
		case '�': return 97;
		case 'b': return 98;
		case '�': return 98;
		case 'c': return 99;
		case '�': return 99;
		case 'd': return 100;
		case 'e': return 101;
		case '�': return 101;
		case 'f': return 102;
		case 'g': return 103;
		case 'h': return 104;
		case 'i': return 105;
		case 'j': return 106;
		case 'k': return 107;
		case 'l': return 108;
		case 'm': return 109;
		case 'n': return 110;
		case 'o': return 111;
		case '�': return 111;
		case 'p': return 112;
		case '�': return 112;
		case 'q': return 113;
		case 'r': return 114;
		case 's': return 115;
		case 't': return 116;
		case 'u': return 117;
		case 'v': return 118;
		case 'w': return 119;
		case 'x': return 120;
		case '�': return 120;
		case 'y': return 121;
		case '�': return 121;
		case 'z': return 122;
		case '�': return 160;
		case '�': return 161;
		case '�': return 162;
		case '�': return 163;
		case '�': return 164;
		case '�': return 165;
		case '�': return 166;
		case '�': return 167;
		case '�': return 168;
		case '�': return 169;
		case '�': return 170;
		case '�': return 171;
		case '�': return 172;
		case '�': return 173;
		case '�': return 174;
		case '�': return 175;
		case '�': return 176;
		case '�': return 177;
		case '�': return 178;
		case '�': return 179;
		case '�': return 180;
		case '�': return 181;
		case '�': return 182;
		case '�': return 183;
		case '�': return 184;
		case '�': return 185;
		case '�': return 186;
		case '�': return 187;
		case '�': return 188;
		case '�': return 189;
		case '�': return 190;
		case '�': return 191;
		case '�': return 192;
		case '�': return 193;
		case '�': return 194;
		case '�': return 195;
		case '�': return 196;
		case '�': return 197;
		case '�': return 198;
		case '�': return 199;
		case '�': return 224;
		case '�': return 225;
		case '�': return 226;
		case '�': return 227;
		case '�': return 228;
		case '�': return 229;
		case '�': return 230;
		case '~': return 233;
		case '|': return 255;
		default: return 16;
	}
}

void char_out_sdk(unsigned char ch)
{
	while(!bf_clear());
	write_max(8, DATA_IND, ch);
	write_max(8, C_IND, 0x05);
	write_max(8, C_IND, 0x04);
}

void char_out_utf(unsigned char ch)
{
	unsigned char buff;
	buff = utf2sdk(ch);
	char_out_sdk(buff);
}


void print_str (unsigned char * str)
{
	while(*str)
	{
		char_out_utf(*str);
		str++;
	}
}

void clrscr()
{
        while(!bf_clear());
        write_max(8, DATA_IND, 0x01);
        write_max(8, C_IND, 0x01);
        write_max(8, C_IND, 0x00);
}

void home()
{
        while(!bf_clear());
        write_max(8, DATA_IND, 0x02);
        write_max(8, C_IND, 0x01);
        write_max(8, C_IND, 0x00);
	
        while(!bf_clear());
        write_max(8, DATA_IND, 0x0f);
        write_max(8, C_IND, 0x01);
        write_max(8, C_IND, 0x00);
}

