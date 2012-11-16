#ifndef GLOBAL_INCLUDED
#define GLOBAL_INCLUDED

#define BASE32_CHARSET (LPSTR)"ABCDEFHIKLMNPQRSTVWXYZ0123456789"

#define MAX_PARTLEN 4
#define MAX_KEYLEN 16

#define BASE_HEX 16

#define LWORD(lValue) (int)(lValue & 0xFFFF)
#define UWORD(lValue) (int)((lValue & 0xFFFF0000) >> 16)

#define PAD_KEY (char)'0'
#define PAD_PART "00000000"

#define OFF_DATETIME 0
#define OFF_ID (MAX_PARTLEN * 1 + OFF_DATETIME + 1)
#define OFF_CAPS (MAX_PARTLEN * 2 + OFF_DATETIME + 2)

#endif // #ifndef GLOBAL_INCLUDED