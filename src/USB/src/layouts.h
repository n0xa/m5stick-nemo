#include <stdint.h>
#include <pgmspace.h>

#define SHIFT 0x80
const uint8_t _it_asciimap[128] =
{
    0x00,          // NUL
    0x00,          // SOH
    0x00,          // STX
    0x00,          // ETX
    0x00,          // EOT
    0x00,          // ENQ
    0x00,          // ACK  
    0x00,          // BEL
    0x2a,          // BS   Backspace
    0x2b,          // TAB  Tab
    0x28,          // LF   Enter
    0x00,          // VT 
    0x00,          // FF 
    0x00,          // CR 
    0x00,          // SO 
    0x00,          // SI 
    0x00,          // DEL
    0x00,          // DC1
    0x00,          // DC2
    0x00,          // DC3
    0x00,          // DC4
    0x00,          // NAK
    0x00,          // SYN
    0x00,          // ETB
    0x00,          // CAN
    0x00,          // EM 
    0x00,          // SUB
    0x00,          // ESC
    0x00,          // FS 
    0x00,          // GS 
    0x00,          // RS 
    0x00,          // US 
    0x2c,          //' ' OK
    0x9E,          // !  OK   
    0x9F,          // "  OK
    0x74,          // #  KO (ALT_GR)
    0xA1,          // $  OK    
    0xA2,          // %  OK
    0xA3,          // &  OK
    0x2D,          // '  OK
    0xA5,          // (  OK
    0xA6,          // )  OK
    0xB0,          // *  OK
    0x30,          // +  OK
    0x36,          // ,  OK
    0x38,          // -  OK
    0x37,          // .  OK
    0xA4,          // /  OK
    0x27,          // 0  OK
    0x1E,          // 1  OK
    0x1F,          // 2  OK
    0x20,          // 3  OK
    0x21,          // 4  OK
    0x22,          // 5  OK
    0x23,          // 6  OK
    0x24,          // 7  OK
    0x25,          // 8  OK
    0x26,          // 9  OK
    0xB7,          // :  OK
    0xB6,          // ;  OK
    0x64,          // <  OK
    0xA7,          // =  OK
    0xE4,          // >  OK
    0xAD,          // ?  OK
    0x73,          // @  KO (ALT_GR)
    0x04|SHIFT,    // A  OK
    0x05|SHIFT,    // B  OK
    0x06|SHIFT,    // C  OK
    0x07|SHIFT,    // D  OK
    0x08|SHIFT,    // E  OK
    0x09|SHIFT,    // F  OK
    0x0a|SHIFT,    // G  OK
    0x0b|SHIFT,    // H  OK
    0x0c|SHIFT,    // I  OK
    0x0d|SHIFT,    // J  OK
    0x0e|SHIFT,    // K  OK
    0x0f|SHIFT,    // L  OK
    0x10|SHIFT,    // M  OK
    0x11|SHIFT,    // N  OK
    0x12|SHIFT,    // O  OK
    0x13|SHIFT,    // P  OK
    0x14|SHIFT,    // Q  OK
    0x15|SHIFT,    // R  OK
    0x16|SHIFT,    // S  OK
    0x17|SHIFT,    // T  OK
    0x18|SHIFT,    // U  OK
    0x19|SHIFT,    // V  OK
    0x1a|SHIFT,    // W  OK
    0x1b|SHIFT,    // X  OK
    0x1c|SHIFT,    // Y  OK
    0x1d|SHIFT,    // Z  OK
    0xAF,          // [  KO (ALT_GR)
    0x35,          // \  OK
    0xB0,          // ]  KO (ALT_GR)
    0xAE,          // ^  OK
    0xB8,          // _  OK
    0x35,          // `  KO
    0x04,          // a  OK
    0x05,          // b  OK
    0x06,          // c  OK
    0x07,          // d  OK
    0x08,          // e  OK
    0x09,          // f  OK
    0x0a,          // g  OK
    0x0b,          // h  OK
    0x0c,          // i  OK
    0x0d,          // j  OK
    0x0e,          // k  OK
    0x0f,          // l  OK
    0x10,          // m  OK
    0x11,          // n  OK
    0x12,          // o  OK
    0x13,          // p  OK
    0x14,          // q  OK
    0x15,          // r  OK
    0x16,          // s  OK
    0x17,          // t  OK
    0x18,          // u  OK
    0x19,          // v  OK
    0x1a,          // w  OK
    0x1b,          // x  OK
    0x1c,          // y  OK
    0x1d,          // z  OK
    0x1AF,         // {  KO (ALT_GR)
    0xB5,          // |  OK
    0x1B0,         // }  KO (ALT_GR)
    0x35|SHIFT,    // ~  KO
    0              //DEL OK
};

const uint8_t _es_asciimap[128] =
{
    0x00,          // NUL
    0x00,          // SOH
    0x00,          // STX
    0x00,          // ETX
    0x00,          // EOT
    0x00,          // ENQ
    0x00,          // ACK  
    0x00,          // BEL
    0x2a,          // BS   Backspace
    0x2b,          // TAB  Tab
    0x28,          // LF   Enter
    0x00,          // VT 
    0x00,          // FF 
    0x00,          // CR 
    0x00,          // SO 
    0x00,          // SI 
    0x00,          // DEL
    0x00,          // DC1
    0x00,          // DC2
    0x00,          // DC3
    0x00,          // DC4
    0x00,          // NAK
    0x00,          // SYN
    0x00,          // ETB
    0x00,          // CAN
    0x00,          // EM 
    0x00,          // SUB
    0x00,          // ESC
    0x00,          // FS 
    0x00,          // GS 
    0x00,          // RS 
    0x00,          // US 

    0x2c,          //  ' '
    0x1e|SHIFT,    // !
    0x34|SHIFT,    // "
    0x20|SHIFT,    // #
    0x21|SHIFT,    // $
    0x22|SHIFT,    // %
    0x24|SHIFT,    // &
    0x34,          // '
    0x26|SHIFT,    // (
    0x27|SHIFT,    // )
    0x25|SHIFT,    // *
    0x2e|SHIFT,    // +
    0x36,          // ,
    0x2d,          // -
    0x37,          // .
    0x38,          // /
    0x27,          // 0
    0x1e,          // 1
    0x1f,          // 2
    0x20,          // 3
    0x21,          // 4
    0x22,          // 5
    0x23,          // 6
    0x24,          // 7
    0x25,          // 8
    0x26,          // 9
    0x33|SHIFT,    // :
    0x33,          // ;
    0x36|SHIFT,    // <
    0x2e,          // =
    0x37|SHIFT,    // >
    0x38|SHIFT,    // ?
    0x1f|SHIFT,    // @
    0x04|SHIFT,    // A
    0x05|SHIFT,    // B
    0x06|SHIFT,    // C
    0x07|SHIFT,    // D
    0x08|SHIFT,    // E
    0x09|SHIFT,    // F
    0x0a|SHIFT,    // G
    0x0b|SHIFT,    // H
    0x0c|SHIFT,    // I
    0x0d|SHIFT,    // J
    0x0e|SHIFT,    // K
    0x0f|SHIFT,    // L
    0x10|SHIFT,    // M
    0x11|SHIFT,    // N
    0x12|SHIFT,    // O
    0x13|SHIFT,    // P
    0x14|SHIFT,    // Q
    0x15|SHIFT,    // R
    0x16|SHIFT,    // S
    0x17|SHIFT,    // T
    0x18|SHIFT,    // U
    0x19|SHIFT,    // V
    0x1a|SHIFT,    // W
    0x1b|SHIFT,    // X
    0x1c|SHIFT,    // Y
    0x1d|SHIFT,    // Z
    0x2f,          // [
    0x31,          // bslash
    0x30,          // ]
    0x23|SHIFT,    // ^
    0x2d|SHIFT,    // _
    0x35,          // `
    0x04,          // a
    0x05,          // b
    0x06,          // c
    0x07,          // d
    0x08,          // e
    0x09,          // f
    0x0a,          // g
    0x0b,          // h
    0x0c,          // i
    0x0d,          // j
    0x0e,          // k
    0x0f,          // l
    0x10,          // m
    0x11,          // n
    0x12,          // o
    0x13,          // p
    0x14,          // q
    0x15,          // r
    0x16,          // s
    0x17,          // t
    0x18,          // u
    0x19,          // v
    0x1a,          // w
    0x1b,          // x
    0x1c,          // y
    0x1d,          // z
    0x2f|SHIFT,    // {
    0x31|SHIFT,    // |
    0x30|SHIFT,    // }
    0x35|SHIFT,    // ~
    0              // DEL
};

const uint8_t _us_asciimap[128] =
{
    0x00,          // NUL
    0x00,          // SOH
    0x00,          // STX
    0x00,          // ETX
    0x00,          // EOT
    0x00,          // ENQ
    0x00,          // ACK  
    0x00,          // BEL
    0x2a,          // BS   Backspace
    0x2b,          // TAB  Tab
    0x28,          // LF   Enter
    0x00,          // VT 
    0x00,          // FF 
    0x00,          // CR 
    0x00,          // SO 
    0x00,          // SI 
    0x00,          // DEL
    0x00,          // DC1
    0x00,          // DC2
    0x00,          // DC3
    0x00,          // DC4
    0x00,          // NAK
    0x00,          // SYN
    0x00,          // ETB
    0x00,          // CAN
    0x00,          // EM 
    0x00,          // SUB
    0x00,          // ESC
    0x00,          // FS 
    0x00,          // GS 
    0x00,          // RS 
    0x00,          // US 

    0x2c,          //  ' '
    0x1e|SHIFT,    // !
    0x34|SHIFT,    // "
    0x20|SHIFT,    // #
    0x21|SHIFT,    // $
    0x22|SHIFT,    // %
    0x24|SHIFT,    // &
    0x34,          // '
    0x26|SHIFT,    // (
    0x27|SHIFT,    // )
    0x25|SHIFT,    // *
    0x2e|SHIFT,    // +
    0x36,          // ,
    0x2d,          // -
    0x37,          // .
    0x38,          // /
    0x27,          // 0
    0x1e,          // 1
    0x1f,          // 2
    0x20,          // 3
    0x21,          // 4
    0x22,          // 5
    0x23,          // 6
    0x24,          // 7
    0x25,          // 8
    0x26,          // 9
    0x33|SHIFT,    // :
    0x33,          // ;
    0x36|SHIFT,    // <
    0x2e,          // =
    0x37|SHIFT,    // >
    0x38|SHIFT,    // ?
    0x1f|SHIFT,    // @
    0x04|SHIFT,    // A
    0x05|SHIFT,    // B
    0x06|SHIFT,    // C
    0x07|SHIFT,    // D
    0x08|SHIFT,    // E
    0x09|SHIFT,    // F
    0x0a|SHIFT,    // G
    0x0b|SHIFT,    // H
    0x0c|SHIFT,    // I
    0x0d|SHIFT,    // J
    0x0e|SHIFT,    // K
    0x0f|SHIFT,    // L
    0x10|SHIFT,    // M
    0x11|SHIFT,    // N
    0x12|SHIFT,    // O
    0x13|SHIFT,    // P
    0x14|SHIFT,    // Q
    0x15|SHIFT,    // R
    0x16|SHIFT,    // S
    0x17|SHIFT,    // T
    0x18|SHIFT,    // U
    0x19|SHIFT,    // V
    0x1a|SHIFT,    // W
    0x1b|SHIFT,    // X
    0x1c|SHIFT,    // Y
    0x1d|SHIFT,    // Z
    0x2f,          // [
    0x31,          // bslash
    0x30,          // ]
    0x23|SHIFT,    // ^
    0x2d|SHIFT,    // _
    0x35,          // `
    0x04,          // a
    0x05,          // b
    0x06,          // c
    0x07,          // d
    0x08,          // e
    0x09,          // f
    0x0a,          // g
    0x0b,          // h
    0x0c,          // i
    0x0d,          // j
    0x0e,          // k
    0x0f,          // l
    0x10,          // m
    0x11,          // n
    0x12,          // o
    0x13,          // p
    0x14,          // q
    0x15,          // r
    0x16,          // s
    0x17,          // t
    0x18,          // u
    0x19,          // v
    0x1a,          // w
    0x1b,          // x
    0x1c,          // y
    0x1d,          // z
    0x2f|SHIFT,    // {
    0x31|SHIFT,    // |
    0x30|SHIFT,    // }
    0x35|SHIFT,    // ~
    0              // DEL
};