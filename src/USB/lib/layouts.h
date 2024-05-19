#include <stdint.h>
#include <pgmspace.h>

// Keylayouts: https://github.com/PaulStoffregen/cores/blob/master/teensy/keylayouts.h

struct ALT_GR_CHARS {
  char c;
  char k[3];
};

#define MODIFIERKEY_CTRL        ( 0x01 | 0xE000 )
#define MODIFIERKEY_SHIFT       ( 0x02 | 0xE000 )
#define MODIFIERKEY_ALT         ( 0x04 | 0xE000 )
#define MODIFIERKEY_GUI         ( 0x08 | 0xE000 )
#define MODIFIERKEY_LEFT_CTRL   ( 0x01 | 0xE000 )
#define MODIFIERKEY_LEFT_SHIFT  ( 0x02 | 0xE000 )
#define MODIFIERKEY_LEFT_ALT    ( 0x04 | 0xE000 )
#define MODIFIERKEY_LEFT_GUI    ( 0x08 | 0xE000 )
#define MODIFIERKEY_RIGHT_CTRL  ( 0x10 | 0xE000 )
#define MODIFIERKEY_RIGHT_SHIFT ( 0x20 | 0xE000 )
#define MODIFIERKEY_RIGHT_ALT   ( 0x40 | 0xE000 )
#define MODIFIERKEY_RIGHT_GUI   ( 0x80 | 0xE000 )

#define KEY_SYSTEM_POWER_DOWN   ( 0x81 | 0xE200 )
#define KEY_SYSTEM_SLEEP        ( 0x82 | 0xE200 )
#define KEY_SYSTEM_WAKE_UP      ( 0x83 | 0xE200 )

#define KEY_MEDIA_PLAY          ( 0xB0 | 0xE400 )
#define KEY_MEDIA_PAUSE         ( 0xB1 | 0xE400 )
#define KEY_MEDIA_RECORD        ( 0xB2 | 0xE400 )
#define KEY_MEDIA_FAST_FORWARD  ( 0xB3 | 0xE400 )
#define KEY_MEDIA_REWIND        ( 0xB4 | 0xE400 )
#define KEY_MEDIA_NEXT_TRACK    ( 0xB5 | 0xE400 )
#define KEY_MEDIA_PREV_TRACK    ( 0xB6 | 0xE400 )
#define KEY_MEDIA_STOP          ( 0xB7 | 0xE400 )
#define KEY_MEDIA_EJECT         ( 0xB8 | 0xE400 )
#define KEY_MEDIA_RANDOM_PLAY   ( 0xB9 | 0xE400 )
#define KEY_MEDIA_PLAY_PAUSE    ( 0xCD | 0xE400 )
#define KEY_MEDIA_PLAY_SKIP     ( 0xCE | 0xE400 )
#define KEY_MEDIA_MUTE          ( 0xE2 | 0xE400 )
#define KEY_MEDIA_VOLUME_INC    ( 0xE9 | 0xE400 )
#define KEY_MEDIA_VOLUME_DEC    ( 0xEA | 0xE400 )

#define KEY_A                   (   4  | 0xF000 )
#define KEY_B                   (   5  | 0xF000 )
#define KEY_C                   (   6  | 0xF000 )
#define KEY_D                   (   7  | 0xF000 )
#define KEY_E                   (   8  | 0xF000 )
#define KEY_F                   (   9  | 0xF000 )
#define KEY_G                   (  10  | 0xF000 )
#define KEY_H                   (  11  | 0xF000 )
#define KEY_I                   (  12  | 0xF000 )
#define KEY_J                   (  13  | 0xF000 )
#define KEY_K                   (  14  | 0xF000 )
#define KEY_L                   (  15  | 0xF000 )
#define KEY_M                   (  16  | 0xF000 )
#define KEY_N                   (  17  | 0xF000 )
#define KEY_O                   (  18  | 0xF000 )
#define KEY_P                   (  19  | 0xF000 )
#define KEY_Q                   (  20  | 0xF000 )
#define KEY_R                   (  21  | 0xF000 )
#define KEY_S                   (  22  | 0xF000 )
#define KEY_T                   (  23  | 0xF000 )
#define KEY_U                   (  24  | 0xF000 )
#define KEY_V                   (  25  | 0xF000 )
#define KEY_W                   (  26  | 0xF000 )
#define KEY_X                   (  27  | 0xF000 )
#define KEY_Y                   (  28  | 0xF000 )
#define KEY_Z                   (  29  | 0xF000 )
#define KEY_1                   (  30  | 0xF000 )
#define KEY_2                   (  31  | 0xF000 )
#define KEY_3                   (  32  | 0xF000 )
#define KEY_4                   (  33  | 0xF000 )
#define KEY_5                   (  34  | 0xF000 )
#define KEY_6                   (  35  | 0xF000 )
#define KEY_7                   (  36  | 0xF000 )
#define KEY_8                   (  37  | 0xF000 )
#define KEY_9                   (  38  | 0xF000 )
#define KEY_0                   (  39  | 0xF000 )
#define KEY_ENTER               (  40  | 0xF000 )
#define KEY_ESC                 (  41  | 0xF000 )
#define KEY_BACKSPACE           (  42  | 0xF000 )
#define KEY_TAB                 (  43  | 0xF000 )
#define KEY_SPACE               (  44  | 0xF000 )
#define KEY_MINUS               (  45  | 0xF000 )
#define KEY_EQUAL               (  46  | 0xF000 )
#define KEY_LEFT_BRACE          (  47  | 0xF000 )
#define KEY_RIGHT_BRACE         (  48  | 0xF000 )
#define KEY_BACKSLASH           (  49  | 0xF000 )
#define KEY_NON_US_NUM          (  50  | 0xF000 )
#define KEY_SEMICOLON           (  51  | 0xF000 )
#define KEY_QUOTE               (  52  | 0xF000 )
#define KEY_TILDE               (  53  | 0xF000 )
#define KEY_COMMA               (  54  | 0xF000 )
#define KEY_PERIOD              (  55  | 0xF000 )
#define KEY_SLASH               (  56  | 0xF000 )
#define KEY_CAPS_LOCK           (  57  | 0xF000 )
#define KEY_F1                  (  58  | 0xF000 )
#define KEY_F2                  (  59  | 0xF000 )
#define KEY_F3                  (  60  | 0xF000 )
#define KEY_F4                  (  61  | 0xF000 )
#define KEY_F5                  (  62  | 0xF000 )
#define KEY_F6                  (  63  | 0xF000 )
#define KEY_F7                  (  64  | 0xF000 )
#define KEY_F8                  (  65  | 0xF000 )
#define KEY_F9                  (  66  | 0xF000 )
#define KEY_F10                 (  67  | 0xF000 )
#define KEY_F11                 (  68  | 0xF000 )
#define KEY_F12                 (  69  | 0xF000 )
#define KEY_PRINTSCREEN         (  70  | 0xF000 )
#define KEY_SCROLL_LOCK         (  71  | 0xF000 )
#define KEY_PAUSE               (  72  | 0xF000 )
#define KEY_INSERT              (  73  | 0xF000 )
#define KEY_HOME                (  74  | 0xF000 )
#define KEY_PAGE_UP             (  75  | 0xF000 )
#define KEY_DELETE              (  76  | 0xF000 )
#define KEY_END                 (  77  | 0xF000 )
#define KEY_PAGE_DOWN           (  78  | 0xF000 )
#define KEY_RIGHT               (  79  | 0xF000 )
#define KEY_LEFT                (  80  | 0xF000 )
#define KEY_DOWN                (  81  | 0xF000 )
#define KEY_UP                  (  82  | 0xF000 )
#define KEY_NUM_LOCK            (  83  | 0xF000 )
#define KEYPAD_SLASH            (  84  | 0xF000 )
#define KEYPAD_ASTERIX          (  85  | 0xF000 )
#define KEYPAD_MINUS            (  86  | 0xF000 )
#define KEYPAD_PLUS             (  87  | 0xF000 )
#define KEYPAD_ENTER            (  88  | 0xF000 )
#define KEYPAD_1                (  89  | 0xF000 )
#define KEYPAD_2                (  90  | 0xF000 )
#define KEYPAD_3                (  91  | 0xF000 )
#define KEYPAD_4                (  92  | 0xF000 )
#define KEYPAD_5                (  93  | 0xF000 )
#define KEYPAD_6                (  94  | 0xF000 )
#define KEYPAD_7                (  95  | 0xF000 )
#define KEYPAD_8                (  96  | 0xF000 )
#define KEYPAD_9                (  97  | 0xF000 )
#define KEYPAD_0                (  98  | 0xF000 )
#define KEYPAD_PERIOD           (  99  | 0xF000 )
#define KEY_NON_US_BS           ( 100  | 0xF000 )
#define KEY_MENU        	      ( 101  | 0xF000 )
#define KEY_F13                 ( 104  | 0xF000 )
#define KEY_F14                 ( 105  | 0xF000 )
#define KEY_F15                 ( 106  | 0xF000 )
#define KEY_F16                 ( 107  | 0xF000 )
#define KEY_F17                 ( 108  | 0xF000 )
#define KEY_F18                 ( 109  | 0xF000 )
#define KEY_F19                 ( 110  | 0xF000 )
#define KEY_F20                 ( 111  | 0xF000 )
#define KEY_F21                 ( 112  | 0xF000 )
#define KEY_F22                 ( 113  | 0xF000 )
#define KEY_F23                 ( 114  | 0xF000 )
#define KEY_F24                 ( 115  | 0xF000 )
#define KEY_RIGHT_BRACE         (  48  | 0xF000 )
// RESERVED					                      0xA5-DF
#define HID_KEY_CONTROL_LEFT              0xE0
#define HID_KEY_SHIFT_LEFT                0xE1
#define HID_KEY_ALT_LEFT                  0xE2
#define HID_KEY_GUI_LEFT                  0xE3
#define HID_KEY_CONTROL_RIGHT             0xE4
#define HID_KEY_SHIFT_RIGHT               0xE5
#define HID_KEY_ALT_RIGHT                 0xE6
#define HID_KEY_GUI_RIGHT                 0xE7

// ITALIAN

#define SHIFT_MASK		0x40
#define ALTGR_MASK		0x80
#define KEYCODE_TYPE		uint8_t
#define KEYCODE_MASK		0x00FF
#define KEY_NON_US_100		63

ALT_GR_CHARS it_asciimap[128] =
{
{ ' ', {KEY_SPACE}}, 	        				            // 32' 'OK   
{ '!', {HID_KEY_SHIFT_LEFT, KEY_1}}, 	      			// 33 ! OK
{ '"', {HID_KEY_SHIFT_LEFT, KEY_2}}, 	            // 34 " OK
{ '#', {HID_KEY_ALT_RIGHT, KEY_QUOTE}}, 	    		// 35 # OK
{ '$', {HID_KEY_SHIFT_LEFT, KEY_4}}, 	        		// 36 $ OK
{ '%', {HID_KEY_SHIFT_LEFT, KEY_5}}, 	        		// 37 % OK
{ '&', {HID_KEY_SHIFT_LEFT, KEY_6}},        			// 38 & OK
{ '\'', {KEY_MINUS}}, 	                      		// 39 ' OK
{ '(', {HID_KEY_SHIFT_LEFT, KEY_8}}, 	      			// 40 ( OK
{ ')', {HID_KEY_SHIFT_LEFT, KEY_9}},			        // 41 ) OK
{ '*', {HID_KEY_SHIFT_LEFT, KEY_RIGHT_BRACE}},    // 42 * OK
{ '+', {KEY_RIGHT_BRACE}}, 	// 43 + OK
{ ',', {KEY_COMMA}}, 				// 44 , OK
{ '-', {KEY_SLASH}}, 				// 45 - OK
{ '.', {KEY_PERIOD}}, 			// 46 . OK
{ '/', {HID_KEY_SHIFT_LEFT, KEY_7}},    // 47 / OK
{ '0', {KEY_0}}, 						// 48 0 OK
{ '1', {KEY_1}}, 						// 49 1 OK
{ '2', {KEY_2}}, 						// 50 2 OK
{ '3', {KEY_3}}, 						// 51 3 OK
{ '4', {KEY_4}}, 						// 52 4 OK
{ '5', {KEY_5}}, 						// 53 5 OK
{ '6', {KEY_6}}, 						// 54 6 OK
{ '7', {KEY_7}}, 						// 55 7 OK
{ '8', {KEY_8}}, 						// 55 8 OK
{ '9', {KEY_9}}, 						// 57 9 OK
{ ':', {HID_KEY_SHIFT_LEFT, KEY_PERIOD}}, 	// 58 : OK
{ ';', {HID_KEY_SHIFT_LEFT, KEY_COMMA}}, 		// 59 ; OK
{ '<', {0x64}}, 				                    // 60 < OK {KEY_NON_US_100}
{ '=', {HID_KEY_SHIFT_LEFT, 0x27}}, 	  		// 61 = OK {HID_KEY_SHIFT_LEFT, KEY_0}
{ '>', {HID_KEY_SHIFT_LEFT, 0x64}},         // 62 > OK {HID_KEY_SHIFT_LEFT, KEY_NON_US_100}
{ '?', {HID_KEY_SHIFT_LEFT, KEY_MINUS}}, 		// 63 ? OK
{ '@', {HID_KEY_ALT_RIGHT, KEY_SEMICOLON}}, // 64 @ OK
{ 'A', {HID_KEY_SHIFT_LEFT, KEY_A}},  			// 65 A OK
{ 'B', {HID_KEY_SHIFT_LEFT, KEY_B}}, 				// 66 B OK
{ 'C', {HID_KEY_SHIFT_LEFT, KEY_C}}, 				// 67 C OK
{ 'D', {HID_KEY_SHIFT_LEFT, KEY_D}}, 				// 68 D OK
{ 'E', {HID_KEY_SHIFT_LEFT, KEY_E}}, 				// 69 E OK
{ 'F', {HID_KEY_SHIFT_LEFT, KEY_F}}, 				// 70 F OK
{ 'G', {HID_KEY_SHIFT_LEFT, KEY_G}},  			// 71 G OK
{ 'H', {HID_KEY_SHIFT_LEFT, KEY_H}}, 				// 72 H OK
{ 'I', {HID_KEY_SHIFT_LEFT, KEY_I}}, 				// 73 I OK
{ 'J', {HID_KEY_SHIFT_LEFT, KEY_J}}, 				// 74 J OK
{ 'K', {HID_KEY_SHIFT_LEFT, KEY_K}}, 				// 75 K OK
{ 'L', {HID_KEY_SHIFT_LEFT, KEY_L}}, 				// 76 L OK
{ 'M', {HID_KEY_SHIFT_LEFT, KEY_M}}, 				// 77 M OK
{ 'N', {HID_KEY_SHIFT_LEFT, KEY_N}}, 				// 78 N OK
{ 'O', {HID_KEY_SHIFT_LEFT, KEY_O}}, 				// 79 O OK
{ 'P', {HID_KEY_SHIFT_LEFT, KEY_P}}, 				// 80 P OK
{ 'Q', {HID_KEY_SHIFT_LEFT, KEY_Q}}, 				// 81 Q OK
{ 'R', {HID_KEY_SHIFT_LEFT, KEY_R}}, 				// 82 R OK
{ 'S', {HID_KEY_SHIFT_LEFT, KEY_S}}, 				// 83 S OK
{ 'T', {HID_KEY_SHIFT_LEFT, KEY_T}}, 				// 84 T OK
{ 'U', {HID_KEY_SHIFT_LEFT, KEY_U}}, 				// 85 U OK
{ 'V', {HID_KEY_SHIFT_LEFT, KEY_V}}, 				// 86 V OK
{ 'W', {HID_KEY_SHIFT_LEFT, KEY_W}},  			// 87 W OK
{ 'X', {HID_KEY_SHIFT_LEFT, KEY_X}}, 				// 88 X OK
{ 'Y', {HID_KEY_SHIFT_LEFT, KEY_Y}}, 				// 89 Y OK
{ 'Z', {HID_KEY_SHIFT_LEFT, KEY_Z}},        // 90 Z OK
{ '[', {HID_KEY_ALT_RIGHT, KEY_LEFT_BRACE}},    // 91 [ OK
{ '\\', {KEY_TILDE}}, 	                				// 92 \ OK
{ ']', {HID_KEY_ALT_RIGHT, KEY_RIGHT_BRACE}},   // 93 ] OK
{ '^', {HID_KEY_SHIFT_LEFT, KEY_EQUAL}},		// 94 ^ OK
{ '_', {HID_KEY_SHIFT_LEFT, KEY_SLASH}},    // 95 _ OK
{ '`', {0}},                                // 96 `  (how to type this on Italian?) KO
{ 'a', {KEY_A}}, 						// 97 a  OK
{ 'b', {KEY_B}}, 						// 98 b  OK
{ 'c', {KEY_C}}, 						// 99 c  OK
{ 'd', {KEY_D}}, 						// 100 d OK
{ 'e', {KEY_E}}, 						// 101 e OK
{ 'f', {KEY_F}}, 						// 102 f OK
{ 'g', {KEY_G}}, 						// 103 g OK
{ 'h', {KEY_H}}, 						// 104 h OK
{ 'i', {KEY_I}}, 						// 105 i Ok
{ 'j', {KEY_J}}, 						// 106 j OK
{ 'k', {KEY_K}}, 						// 107 k OK
{ 'l', {KEY_L}}, 						// 108 l OK
{ 'm', {KEY_M}}, 						// 109 m OK
{ 'n', {KEY_N}}, 						// 110 n OK
{ 'o', {KEY_O}}, 						// 111 o OK
{ 'p', {KEY_P}}, 						// 112 p OK
{ 'q', {KEY_Q}}, 						// 113 q Ok
{ 'r', {KEY_R}}, 						// 114 r OK
{ 's', {KEY_S}}, 						// 115 s OK
{ 't', {KEY_T}}, 						// 116 t OK
{ 'u', {KEY_U}}, 						// 117 u OK
{ 'v', {KEY_V}}, 						// 118 v OK
{ 'w', {KEY_W}}, 						// 119 w OK
{ 'x', {KEY_X}}, 						// 120 x OK
{ 'y', {KEY_Y}}, 						// 121 y OK
{ 'z', {KEY_Z}}, 						// 122 z OK
{ '{', {HID_KEY_ALT_RIGHT, HID_KEY_SHIFT_LEFT, KEY_LEFT_BRACE}},    // 123 { OK
{ '|', {HID_KEY_SHIFT_LEFT, KEY_TILDE}},                            // 124 | OK
{ '}', {HID_KEY_ALT_RIGHT, HID_KEY_SHIFT_LEFT, KEY_RIGHT_BRACE}},   // 125 } OK 
{ '~', {0}},                                                        // 126 ~   (how to type this on Italian?) KO
};

// UNITED STATES INTERNATIONAL

ALT_GR_CHARS us_asciimap[128] =
{
{ ' ', {0x2c}}, 	        	              // 32' 'OK   
{ '!', {HID_KEY_SHIFT_LEFT, 0x1e}}, 	    // 33 ! OK
{ '"', {HID_KEY_SHIFT_LEFT, 0x34}}, 	    // 34 " OK
{ '#', {HID_KEY_SHIFT_LEFT, 0x20}}, 	    // 35 # OK
{ '$', {HID_KEY_SHIFT_LEFT, 0x21}}, 	    // 36 $ OK
{ '%', {HID_KEY_SHIFT_LEFT, 0x22}}, 	    // 37 % OK
{ '&', {HID_KEY_SHIFT_LEFT, 0x24}},       // 38 & OK
{ '\'', {0x34}}, 	                        // 39 ' OK
{ '(', {HID_KEY_SHIFT_LEFT, 0x26}}, 	    // 40 ( OK
{ ')', {HID_KEY_SHIFT_LEFT, 0x27}},			  // 41 ) OK
{ '*', {HID_KEY_SHIFT_LEFT, 0x25}},       // 42 * OK
{ '+', {HID_KEY_SHIFT_LEFT, 0x2e}}, 	    // 43 + OK
{ ',', {0x36}}, 				    // 44 , OK
{ '-', {0x2d}}, 				    // 45 - OK
{ '.', {0x37}}, 			      // 46 . OK
{ '/', {0x38}},             // 47 / OK
{ '0', {0x27}}, 						// 48 0 OK
{ '1', {0x1e}}, 						// 49 1 OK
{ '2', {0x1f}}, 						// 50 2 OK
{ '3', {0x20}}, 						// 51 3 OK
{ '4', {0x21}}, 						// 52 4 OK
{ '5', {0x22}}, 						// 53 5 OK
{ '6', {0x23}}, 						// 54 6 OK
{ '7', {0x24}}, 						// 55 7 OK
{ '8', {0x25}}, 						// 55 8 OK
{ '9', {0x26}}, 						// 57 9 OK
{ ':', {HID_KEY_SHIFT_LEFT, 0x33}}, 	    // 58 : OK
{ ';', {0x33}}, 		        // 59 ; OK
{ '<', {HID_KEY_SHIFT_LEFT, 0x36}}, 			// 60 < OK
{ '=', {0x2e}}, 	  		    // 61 = OK 
{ '>', {HID_KEY_SHIFT_LEFT, 0x37}},       // 62 > OK 
{ '?', {HID_KEY_SHIFT_LEFT, 0x38}}, 		  // 63 ? OK
{ '@', {HID_KEY_SHIFT_LEFT, 0x1f}},       // 64 @ OK
{ 'A', {HID_KEY_SHIFT_LEFT, 0x04}},   		// 65 A OK
{ 'B', {HID_KEY_SHIFT_LEFT, 0x05}}, 			// 66 B OK
{ 'C', {HID_KEY_SHIFT_LEFT, 0x06}}, 			// 67 C OK
{ 'D', {HID_KEY_SHIFT_LEFT, 0x07}}, 			// 68 D OK
{ 'E', {HID_KEY_SHIFT_LEFT, 0x08}}, 			// 69 E OK
{ 'F', {HID_KEY_SHIFT_LEFT, 0x09}}, 			// 70 F OK
{ 'G', {HID_KEY_SHIFT_LEFT, 0x0a}},  		  // 71 G OK
{ 'H', {HID_KEY_SHIFT_LEFT, 0x0b}}, 			// 72 H OK
{ 'I', {HID_KEY_SHIFT_LEFT, 0x0c}}, 			// 73 I OK
{ 'J', {HID_KEY_SHIFT_LEFT, 0x0d}}, 			// 74 J OK
{ 'K', {HID_KEY_SHIFT_LEFT, 0x0e}}, 			// 75 K OK
{ 'L', {HID_KEY_SHIFT_LEFT, 0x0f}}, 			// 76 L OK
{ 'M', {HID_KEY_SHIFT_LEFT, 0x10}}, 			// 77 M OK
{ 'N', {HID_KEY_SHIFT_LEFT, 0x11}}, 			// 78 N OK
{ 'O', {HID_KEY_SHIFT_LEFT, 0x12}}, 			// 79 O OK
{ 'P', {HID_KEY_SHIFT_LEFT, 0x13}}, 			// 80 P OK
{ 'Q', {HID_KEY_SHIFT_LEFT, 0x14}}, 			// 81 Q OK
{ 'R', {HID_KEY_SHIFT_LEFT, 0x15}}, 			// 82 R OK
{ 'S', {HID_KEY_SHIFT_LEFT, 0x16}}, 			// 83 S OK
{ 'T', {HID_KEY_SHIFT_LEFT, 0x17}}, 			// 84 T OK
{ 'U', {HID_KEY_SHIFT_LEFT, 0x18}}, 			// 85 U OK
{ 'V', {HID_KEY_SHIFT_LEFT, 0x19}}, 			// 86 V OK
{ 'W', {HID_KEY_SHIFT_LEFT, 0x1a}},  		  // 87 W OK
{ 'X', {HID_KEY_SHIFT_LEFT, 0x1b}}, 			// 88 X OK
{ 'Y', {HID_KEY_SHIFT_LEFT, 0x1c}}, 			// 89 Y OK
{ 'Z', {HID_KEY_SHIFT_LEFT, 0x1d}},       // 90 Z OK
{ '[', {0x2f}},             // 91 [ OK
{ '\\', {0x31}}, 	          // 92 \ OK
{ ']', {0x30}},             // 93 ] OK
{ '^', {HID_KEY_SHIFT_LEFT, 0x23}},		    // 94 ^ OK
{ '_', {HID_KEY_SHIFT_LEFT, 0x2d}},       // 95 _ OK
{ '`', {0x35}},             // 96 ` OK
{ 'a', {0x04}}, 						// 97 a OK
{ 'b', {0x05}}, 						// 98 b OK
{ 'c', {0x06}}, 						// 99 c OK
{ 'd', {0x07}}, 						// 100 d OK
{ 'e', {0x08}}, 						// 101 e OK
{ 'f', {0x09}}, 						// 102 f OK
{ 'g', {0x0a}}, 						// 103 g OK
{ 'h', {0x0b}}, 						// 104 h OK
{ 'i', {0x0c}}, 						// 105 i Ok
{ 'j', {0x0d}}, 						// 106 j OK
{ 'k', {0x0e}}, 						// 107 k OK
{ 'l', {0x0f}}, 						// 108 l OK
{ 'm', {0x10}}, 						// 109 m OK
{ 'n', {0x11}}, 						// 110 n OK
{ 'o', {0x12}}, 						// 111 o OK
{ 'p', {0x13}}, 						// 112 p OK
{ 'q', {0x14}}, 						// 113 q OK
{ 'r', {0x15}}, 						// 114 r OK
{ 's', {0x16}}, 						// 115 s OK
{ 't', {0x17}}, 						// 116 t OK
{ 'u', {0x18}}, 						// 117 u OK
{ 'v', {0x19}}, 						// 118 v OK
{ 'w', {0x1a}}, 						// 119 w OK
{ 'x', {0x1b}}, 						// 120 x OK
{ 'y', {0x1c}}, 						// 121 y OK
{ 'z', {0x1d}}, 						// 122 z OK
{ '{', {HID_KEY_SHIFT_LEFT, 0x2f}},       // 123 { OK
{ '|', {HID_KEY_SHIFT_LEFT, 0x31}},       // 124 | OK
{ '}', {HID_KEY_SHIFT_LEFT, 0x30}},       // 125 } OK 
{ '~', {HID_KEY_SHIFT_LEFT, 0x35}},       // 126 ~ OK
};

// UK ENGLISH

#define SHIFT_MASK		0x0040
#define ALTGR_MASK		0x0080
#define KEYCODE_TYPE		uint8_t
#define KEYCODE_MASK		0x00FF
#define KEY_NON_US_100		63

ALT_GR_CHARS uk_asciimap[128] =
{
{ ' ', {KEY_SPACE}}, 	        	          // 32' 'OK   
{ '!', {HID_KEY_SHIFT_LEFT, KEY_1}}, 	    // 33 ! OK
{ '"', {HID_KEY_SHIFT_LEFT, KEY_2}}, 	    // 34 " OK
{ '#', {KEY_BACKSLASH}}, 	                // 35 # OK
{ '$', {HID_KEY_SHIFT_LEFT, KEY_4}}, 	    // 36 $ OK
{ '%', {HID_KEY_SHIFT_LEFT, KEY_5}}, 	    // 37 % OK
{ '&', {HID_KEY_SHIFT_LEFT, KEY_7}},      // 38 & OK
{ '\'', {KEY_QUOTE}}, 	                  // 39 ' OK
{ '(', {HID_KEY_SHIFT_LEFT, KEY_9}}, 	    // 40 ( OK
{ ')', {HID_KEY_SHIFT_LEFT, KEY_0}},			// 41 ) OK
{ '*', {HID_KEY_SHIFT_LEFT, KEY_8}},      // 42 * OK
{ '+', {HID_KEY_SHIFT_LEFT, KEY_EQUAL}}, 	// 43 + OK
{ ',', {KEY_COMMA}}, 				    // 44 , OK
{ '-', {KEY_MINUS}}, 				    // 45 - OK
{ '.', {KEY_PERIOD}}, 			    // 46 . OK
{ '/', {KEY_SLASH}},            // 47 / OK
{ '0', {KEY_0}}, 						// 48 0 OK
{ '1', {KEY_1}}, 						// 49 1 OK
{ '2', {KEY_2}}, 						// 50 2 OK
{ '3', {KEY_3}}, 						// 51 3 OK
{ '4', {KEY_4}}, 						// 52 4 OK
{ '5', {KEY_5}}, 						// 53 5 OK
{ '6', {KEY_6}}, 						// 54 6 OK
{ '7', {KEY_7}}, 						// 55 7 OK
{ '8', {KEY_8}}, 						// 55 8 OK
{ '9', {KEY_9}}, 						// 57 9 OK
{ ':', {HID_KEY_SHIFT_LEFT, KEY_SEMICOLON}}, // 58 : OK
{ ';', {KEY_SEMICOLON}}, 		              // 59 ; OK
{ '<', {HID_KEY_SHIFT_LEFT, KEY_COMMA}}, 	// 60 < OK
{ '=', {KEY_EQUAL}}, 	  		              // 61 = OK 
{ '>', {HID_KEY_SHIFT_LEFT, KEY_PERIOD}}, // 62 > OK 
{ '?', {HID_KEY_SHIFT_LEFT, KEY_SLASH}},  // 63 ? OK
{ '@', {HID_KEY_SHIFT_LEFT, KEY_QUOTE}},  // 64 @ OK
{ 'A', {HID_KEY_SHIFT_LEFT, KEY_A}},   		// 65 A OK
{ 'B', {HID_KEY_SHIFT_LEFT, KEY_B}}, 			// 66 B OK
{ 'C', {HID_KEY_SHIFT_LEFT, KEY_C}}, 			// 67 C OK
{ 'D', {HID_KEY_SHIFT_LEFT, KEY_D}}, 			// 68 D OK
{ 'E', {HID_KEY_SHIFT_LEFT, KEY_E}}, 			// 69 E OK
{ 'F', {HID_KEY_SHIFT_LEFT, KEY_F}}, 			// 70 F OK
{ 'G', {HID_KEY_SHIFT_LEFT, KEY_G}},  	  // 71 G OK
{ 'H', {HID_KEY_SHIFT_LEFT, KEY_H}}, 			// 72 H OK
{ 'I', {HID_KEY_SHIFT_LEFT, KEY_I}}, 			// 73 I OK
{ 'J', {HID_KEY_SHIFT_LEFT, KEY_J}}, 			// 74 J OK
{ 'K', {HID_KEY_SHIFT_LEFT, KEY_K}}, 			// 75 K OK
{ 'L', {HID_KEY_SHIFT_LEFT, KEY_L}}, 			// 76 L OK
{ 'M', {HID_KEY_SHIFT_LEFT, KEY_M}}, 			// 77 M OK
{ 'N', {HID_KEY_SHIFT_LEFT, KEY_N}}, 			// 78 N OK
{ 'O', {HID_KEY_SHIFT_LEFT, KEY_O}}, 			// 79 O OK
{ 'P', {HID_KEY_SHIFT_LEFT, KEY_P}}, 			// 80 P OK
{ 'Q', {HID_KEY_SHIFT_LEFT, KEY_Q}}, 			// 81 Q OK
{ 'R', {HID_KEY_SHIFT_LEFT, KEY_R}}, 			// 82 R OK
{ 'S', {HID_KEY_SHIFT_LEFT, KEY_S}}, 			// 83 S OK
{ 'T', {HID_KEY_SHIFT_LEFT, KEY_T}}, 			// 84 T OK
{ 'U', {HID_KEY_SHIFT_LEFT, KEY_U}}, 			// 85 U OK
{ 'V', {HID_KEY_SHIFT_LEFT, KEY_V}}, 			// 86 V OK
{ 'W', {HID_KEY_SHIFT_LEFT, KEY_W}},  		// 87 W OK
{ 'X', {HID_KEY_SHIFT_LEFT, KEY_X}}, 			// 88 X OK
{ 'Y', {HID_KEY_SHIFT_LEFT, KEY_Y}}, 			// 89 Y OK
{ 'Z', {HID_KEY_SHIFT_LEFT, KEY_Z}},      // 90 Z OK
{ '[', {KEY_LEFT_BRACE}},                 // 91 [ OK
{ '\\', {0x64}}, 	                        // 92 \ OK
{ ']', {KEY_RIGHT_BRACE}},                // 93 ] OK
{ '^', {HID_KEY_SHIFT_LEFT, KEY_6}},		  // 94 ^ OK
{ '_', {HID_KEY_SHIFT_LEFT, KEY_MINUS}},  // 95 _ OK
{ '`', {KEY_TILDE}},         // 96 ` OK
{ 'a', {KEY_A}}, 						// 97 a OK
{ 'b', {KEY_B}}, 						// 98 b OK
{ 'c', {KEY_C}}, 						// 99 c OK
{ 'd', {KEY_D}}, 						// 100 d OK
{ 'e', {KEY_E}}, 						// 101 e OK
{ 'f', {KEY_F}}, 						// 102 f OK
{ 'g', {KEY_G}}, 						// 103 g OK
{ 'h', {KEY_H}}, 						// 104 h OK
{ 'i', {KEY_I}}, 						// 105 i Ok
{ 'j', {KEY_J}}, 						// 106 j OK
{ 'k', {KEY_K}}, 						// 107 k OK
{ 'l', {KEY_L}}, 						// 108 l OK
{ 'm', {KEY_M}}, 						// 109 m OK
{ 'n', {KEY_N}}, 						// 110 n OK
{ 'o', {KEY_O}}, 						// 111 o OK
{ 'p', {KEY_P}}, 						// 112 p OK
{ 'q', {KEY_Q}}, 						// 113 q OK
{ 'r', {KEY_R}}, 						// 114 r OK
{ 's', {KEY_S}}, 						// 115 s OK
{ 't', {KEY_T}}, 						// 116 t OK
{ 'u', {KEY_U}}, 						// 117 u OK
{ 'v', {KEY_V}}, 						// 118 v OK
{ 'w', {KEY_W}}, 						// 119 w OK
{ 'x', {KEY_X}}, 						// 120 x OK
{ 'y', {KEY_Y}}, 						// 121 y OK
{ 'z', {KEY_Z}}, 						// 122 z OK
{ '{', {HID_KEY_SHIFT_LEFT, KEY_LEFT_BRACE}},       // 123 { OK
{ '|', {HID_KEY_SHIFT_LEFT, 0x64}},                 // 124 | OK
{ '}', {HID_KEY_SHIFT_LEFT, KEY_RIGHT_BRACE}},      // 125 } OK 
{ '~', {HID_KEY_SHIFT_LEFT, KEY_BACKSLASH}},        // 126 ~ OK
};

// FRENCH

#define SHIFT_MASK		0x0040
#define ALTGR_MASK		0x0080
#define DEADKEYS_MASK		0x0700
#define	CIRCUMFLEX_BITS		0x0100
#define GRAVE_ACCENT_BITS	0x0200
#define DIAERESIS_BITS		0x0300
#define TILDE_BITS		0x0400
#define KEYCODE_TYPE		uint16_t
#define KEYCODE_MASK		0x07FF
#define DEADKEY_CIRCUMFLEX	KEY_LEFT_BRACE
#define DEADKEY_GRAVE_ACCENT	KEY_7 + ALTGR_MASK
#define DEADKEY_DIAERESIS	KEY_LEFT_BRACE + SHIFT_MASK
#define DEADKEY_TILDE		KEY_2 + ALTGR_MASK
#define KEY_NON_US_100		63

ALT_GR_CHARS fr_asciimap[128] =
{
{ ' ', {KEY_SPACE}}, 	        				    // 32' 'OK   
{ '!', {KEY_SLASH}}, 	                    // 33 ! OK
{ '"', {KEY_3}}, 	                        // 34 " OK
{ '#', {HID_KEY_ALT_RIGHT, KEY_3}}, 	    // 35 # OK
{ '$', {KEY_RIGHT_BRACE}}, 	              // 36 $ OK
{ '%', {HID_KEY_SHIFT_LEFT, KEY_QUOTE}}, 	// 37 % OK
{ '&', {KEY_1}},                          // 38 & OK
{ '\'', {KEY_4}},                         // 39 ' OK
{ '(', {KEY_5}}, 	                        // 40 ( OK
{ ')', {KEY_MINUS}},			                // 41 ) OK
{ '*', {KEY_BACKSLASH}},                  // 42 * OK
{ '+', {HID_KEY_SHIFT_LEFT, KEY_EQUAL}}, 	// 43 + OK
{ ',', {KEY_M}}, 				                  // 44 , OK
{ '-', {KEY_6}}, 				                  // 45 - OK
{ '.', {HID_KEY_SHIFT_LEFT, KEY_COMMA}},  // 46 . OK
{ '/', {HID_KEY_SHIFT_LEFT, KEY_PERIOD}}, // 47 / OK
{ '0', {HID_KEY_SHIFT_LEFT, KEY_0}}, 						              // 48 0 OK
{ '1', {HID_KEY_SHIFT_LEFT, KEY_1}}, 						              // 49 1 OK
{ '2', {HID_KEY_SHIFT_LEFT, KEY_2}}, 						              // 50 2 OK
{ '3', {HID_KEY_SHIFT_LEFT, KEY_3}}, 						              // 51 3 OK
{ '4', {HID_KEY_SHIFT_LEFT, KEY_4}}, 						              // 52 4 OK
{ '5', {HID_KEY_SHIFT_LEFT, KEY_5}}, 						              // 53 5 OK
{ '6', {HID_KEY_SHIFT_LEFT, KEY_6}}, 						              // 54 6 OK
{ '7', {HID_KEY_SHIFT_LEFT, KEY_7}}, 						              // 55 7 OK
{ '8', {HID_KEY_SHIFT_LEFT, KEY_8}}, 						              // 55 8 OK
{ '9', {HID_KEY_SHIFT_LEFT, KEY_9}}, 						              // 57 9 OK
{ ':', {KEY_PERIOD}}, // 58 : OK
{ ';', {KEY_COMMA}},  // 59 ; OK
{ '<', {0x64}}, 	                        // 60 < OK
{ '=', {KEY_EQUAL}}, 	                    // 61 = OK 
{ '>', {HID_KEY_SHIFT_LEFT, 0x64}},       // 62 > OK
{ '?', {HID_KEY_SHIFT_LEFT, KEY_M}},      // 63 ? OK
{ '@', {HID_KEY_ALT_RIGHT, KEY_0}},       // 64 @ OK
{ 'A', {HID_KEY_SHIFT_LEFT, KEY_Q}},  		// 65 A OK
{ 'B', {HID_KEY_SHIFT_LEFT, KEY_B}}, 			// 66 B OK
{ 'C', {HID_KEY_SHIFT_LEFT, KEY_C}}, 			// 67 C OK
{ 'D', {HID_KEY_SHIFT_LEFT, KEY_D}}, 			// 68 D OK
{ 'E', {HID_KEY_SHIFT_LEFT, KEY_E}}, 			// 69 E OK
{ 'F', {HID_KEY_SHIFT_LEFT, KEY_F}}, 			// 70 F OK
{ 'G', {HID_KEY_SHIFT_LEFT, KEY_G}},  		// 71 G OK
{ 'H', {HID_KEY_SHIFT_LEFT, KEY_H}}, 			// 72 H OK
{ 'I', {HID_KEY_SHIFT_LEFT, KEY_I}}, 			// 73 I OK
{ 'J', {HID_KEY_SHIFT_LEFT, KEY_J}}, 			// 74 J OK
{ 'K', {HID_KEY_SHIFT_LEFT, KEY_K}}, 			// 75 K OK
{ 'L', {HID_KEY_SHIFT_LEFT, KEY_L}}, 			// 76 L OK
{ 'M', {HID_KEY_SHIFT_LEFT, KEY_SEMICOLON}}, // 77 M OK
{ 'N', {HID_KEY_SHIFT_LEFT, KEY_N}}, 			// 78 N OK
{ 'O', {HID_KEY_SHIFT_LEFT, KEY_O}}, 			// 79 O OK
{ 'P', {HID_KEY_SHIFT_LEFT, KEY_P}}, 			// 80 P OK
{ 'Q', {HID_KEY_SHIFT_LEFT, KEY_A}}, 			// 81 Q OK
{ 'R', {HID_KEY_SHIFT_LEFT, KEY_R}}, 			// 82 R OK
{ 'S', {HID_KEY_SHIFT_LEFT, KEY_S}}, 			// 83 S OK
{ 'T', {HID_KEY_SHIFT_LEFT, KEY_T}}, 			// 84 T OK
{ 'U', {HID_KEY_SHIFT_LEFT, KEY_U}}, 			// 85 U OK
{ 'V', {HID_KEY_SHIFT_LEFT, KEY_V}}, 			// 86 V OK
{ 'W', {HID_KEY_SHIFT_LEFT, KEY_Z}},  		// 87 W OK
{ 'X', {HID_KEY_SHIFT_LEFT, KEY_X}}, 			// 88 X OK
{ 'Y', {HID_KEY_SHIFT_LEFT, KEY_Y}}, 			// 89 Y OK
{ 'Z', {HID_KEY_SHIFT_LEFT, KEY_W}},      // 90 Z OK
{ '[', {HID_KEY_ALT_RIGHT, KEY_5}},       // 91 [ OK
{ '\\', {HID_KEY_ALT_RIGHT, KEY_8}}, 	    // 92 \ OK
{ ']', {HID_KEY_ALT_RIGHT, KEY_MINUS}},   // 93 ] OK
{ '^', {HID_KEY_ALT_RIGHT, KEY_9}},		    // 94 ^ OK
{ '_', {KEY_8}},                          // 95 _ OK
{ '`', {0}},                              // 96 ` KO
{ 'a', {KEY_Q}}, 						// 97 a  OK
{ 'b', {KEY_B}}, 						// 98 b  OK
{ 'c', {KEY_C}}, 						// 99 c  OK
{ 'd', {KEY_D}}, 						// 100 d OK
{ 'e', {KEY_E}}, 						// 101 e OK
{ 'f', {KEY_F}}, 						// 102 f OK
{ 'g', {KEY_G}}, 						// 103 g OK
{ 'h', {KEY_H}}, 						// 104 h OK
{ 'i', {KEY_I}}, 						// 105 i Ok
{ 'j', {KEY_J}}, 						// 106 j OK
{ 'k', {KEY_K}}, 						// 107 k OK
{ 'l', {KEY_L}}, 						// 108 l OK
{ 'm', {KEY_SEMICOLON}}, 		// 109 m OK
{ 'n', {KEY_N}}, 						// 110 n OK
{ 'o', {KEY_O}}, 						// 111 o OK
{ 'p', {KEY_P}}, 						// 112 p OK
{ 'q', {KEY_A}}, 						// 113 q Ok
{ 'r', {KEY_R}}, 						// 114 r OK
{ 's', {KEY_S}}, 						// 115 s OK
{ 't', {KEY_T}}, 						// 116 t OK
{ 'u', {KEY_U}}, 						// 117 u OK
{ 'v', {KEY_V}}, 						// 118 v OK
{ 'w', {KEY_Z}}, 						// 119 w OK
{ 'x', {KEY_X}}, 						// 120 x OK
{ 'y', {KEY_Y}}, 						// 121 y OK
{ 'z', {KEY_W}}, 						// 122 z OK
{ '{', {HID_KEY_ALT_RIGHT, KEY_4}},            // 123 { OK
{ '|', {HID_KEY_ALT_RIGHT, KEY_6}},            // 124 | OK
{ '}', {HID_KEY_ALT_RIGHT, KEY_EQUAL}},        // 125 } OK 
{ '~', {0}},                                   // 126 ~ KO
};

// GERMAN

#define SHIFT_MASK		0x0040
#define ALTGR_MASK		0x0080
#define DEADKEYS_MASK		0x0700
#define	CIRCUMFLEX_BITS		0x0300
#define ACUTE_ACCENT_BITS	0x0400
#define GRAVE_ACCENT_BITS	0x0500
#define KEYCODE_TYPE		uint16_t
#define KEYCODE_MASK		0x07FF
#define DEADKEY_CIRCUMFLEX	KEY_TILDE
#define DEADKEY_ACUTE_ACCENT	KEY_EQUAL
#define DEADKEY_GRAVE_ACCENT	KEY_EQUAL + SHIFT_MASK
#define KEY_NON_US_100		63

ALT_GR_CHARS de_asciimap[128] =
{
{ ' ', {KEY_SPACE}}, 	        				    // 32' 'OK   
{ '!', {HID_KEY_SHIFT_LEFT, KEY_1}}, 	    // 33 ! OK
{ '"', {HID_KEY_SHIFT_LEFT, KEY_2}}, 	    // 34 " OK
{ '#', {KEY_BACKSLASH}}, 	                // 35 # OK
{ '$', {HID_KEY_SHIFT_LEFT, KEY_4}}, 	    // 36 $ OK
{ '%', {HID_KEY_SHIFT_LEFT, KEY_5}}, 	    // 37 % OK
{ '&', {HID_KEY_SHIFT_LEFT, KEY_6}},      // 38 & OK
{ '\'', {HID_KEY_SHIFT_LEFT, KEY_BACKSLASH}},// 39 ' OK
{ '(', {HID_KEY_SHIFT_LEFT, KEY_8}}, 	    // 40 ( OK
{ ')', {HID_KEY_SHIFT_LEFT, KEY_9}},			// 41 ) OK
{ '*', {HID_KEY_SHIFT_LEFT, KEY_RIGHT_BRACE}},  // 42 * OK
{ '+', {KEY_RIGHT_BRACE}}, 	              // 43 + OK
{ ',', {KEY_COMMA}}, 				              // 44 , OK
{ '-', {KEY_SLASH}}, 				              // 45 - OK
{ '.', {KEY_PERIOD}}, 			              // 46 . OK
{ '/', {HID_KEY_SHIFT_LEFT, KEY_7}},      // 47 / OK
{ '0', {KEY_0}}, 						              // 48 0 OK
{ '1', {KEY_1}}, 						              // 49 1 OK
{ '2', {KEY_2}}, 						              // 50 2 OK
{ '3', {KEY_3}}, 						              // 51 3 OK
{ '4', {KEY_4}}, 						              // 52 4 OK
{ '5', {KEY_5}}, 						              // 53 5 OK
{ '6', {KEY_6}}, 						              // 54 6 OK
{ '7', {KEY_7}}, 						              // 55 7 OK
{ '8', {KEY_8}}, 						              // 55 8 OK
{ '9', {KEY_9}}, 						              // 57 9 OK
{ ':', {HID_KEY_SHIFT_LEFT, KEY_PERIOD}}, // 58 : OK
{ ';', {HID_KEY_SHIFT_LEFT, KEY_COMMA}},  // 59 ; OK
{ '<', {0x64}}, 	                        // 60 < OK
{ '=', {HID_KEY_SHIFT_LEFT, KEY_0}}, 	    // 61 = OK 
{ '>', {HID_KEY_SHIFT_LEFT, 0x64}},       // 62 > OK
{ '?', {HID_KEY_SHIFT_LEFT, KEY_MINUS}},  // 63 ? OK
{ '@', {HID_KEY_ALT_RIGHT, KEY_Q}},       // 64 @ OK
{ 'A', {HID_KEY_SHIFT_LEFT, KEY_A}},  		// 65 A OK
{ 'B', {HID_KEY_SHIFT_LEFT, KEY_B}}, 			// 66 B OK
{ 'C', {HID_KEY_SHIFT_LEFT, KEY_C}}, 			// 67 C OK
{ 'D', {HID_KEY_SHIFT_LEFT, KEY_D}}, 			// 68 D OK
{ 'E', {HID_KEY_SHIFT_LEFT, KEY_E}}, 			// 69 E OK
{ 'F', {HID_KEY_SHIFT_LEFT, KEY_F}}, 			// 70 F OK
{ 'G', {HID_KEY_SHIFT_LEFT, KEY_G}},  		// 71 G OK
{ 'H', {HID_KEY_SHIFT_LEFT, KEY_H}}, 			// 72 H OK
{ 'I', {HID_KEY_SHIFT_LEFT, KEY_I}}, 			// 73 I OK
{ 'J', {HID_KEY_SHIFT_LEFT, KEY_J}}, 			// 74 J OK
{ 'K', {HID_KEY_SHIFT_LEFT, KEY_K}}, 			// 75 K OK
{ 'L', {HID_KEY_SHIFT_LEFT, KEY_L}}, 			// 76 L OK
{ 'M', {HID_KEY_SHIFT_LEFT, KEY_M}}, 			// 77 M OK
{ 'N', {HID_KEY_SHIFT_LEFT, KEY_N}}, 			// 78 N OK
{ 'O', {HID_KEY_SHIFT_LEFT, KEY_O}}, 			// 79 O OK
{ 'P', {HID_KEY_SHIFT_LEFT, KEY_P}}, 			// 80 P OK
{ 'Q', {HID_KEY_SHIFT_LEFT, KEY_Q}}, 			// 81 Q OK
{ 'R', {HID_KEY_SHIFT_LEFT, KEY_R}}, 			// 82 R OK
{ 'S', {HID_KEY_SHIFT_LEFT, KEY_S}}, 			// 83 S OK
{ 'T', {HID_KEY_SHIFT_LEFT, KEY_T}}, 			// 84 T OK
{ 'U', {HID_KEY_SHIFT_LEFT, KEY_U}}, 			// 85 U OK
{ 'V', {HID_KEY_SHIFT_LEFT, KEY_V}}, 			// 86 V OK
{ 'W', {HID_KEY_SHIFT_LEFT, KEY_W}},  		// 87 W OK
{ 'X', {HID_KEY_SHIFT_LEFT, KEY_X}}, 			// 88 X OK
{ 'Y', {HID_KEY_SHIFT_LEFT, KEY_Y}}, 			// 89 Y OK
{ 'Z', {HID_KEY_SHIFT_LEFT, KEY_Z}},      // 90 Z OK
{ '[', {HID_KEY_ALT_RIGHT, KEY_8}},       // 91 [ OK
{ '\\', {HID_KEY_ALT_RIGHT, KEY_MINUS}}, 	// 92 \ OK
{ ']', {HID_KEY_ALT_RIGHT, KEY_9}},       // 93 ] OK
{ '^', {0}},		                          // 94 ^ KO
{ '_', {HID_KEY_SHIFT_LEFT, KEY_SLASH}},  // 95 _ OK
{ '`', {0}},                              // 96 ` KO
{ 'a', {KEY_A}}, 						// 97 a  OK
{ 'b', {KEY_B}}, 						// 98 b  OK
{ 'c', {KEY_C}}, 						// 99 c  OK
{ 'd', {KEY_D}}, 						// 100 d OK
{ 'e', {KEY_E}}, 						// 101 e OK
{ 'f', {KEY_F}}, 						// 102 f OK
{ 'g', {KEY_G}}, 						// 103 g OK
{ 'h', {KEY_H}}, 						// 104 h OK
{ 'i', {KEY_I}}, 						// 105 i Ok
{ 'j', {KEY_J}}, 						// 106 j OK
{ 'k', {KEY_K}}, 						// 107 k OK
{ 'l', {KEY_L}}, 						// 108 l OK
{ 'm', {KEY_M}}, 						// 109 m OK
{ 'n', {KEY_N}}, 						// 110 n OK
{ 'o', {KEY_O}}, 						// 111 o OK
{ 'p', {KEY_P}}, 						// 112 p OK
{ 'q', {KEY_Q}}, 						// 113 q Ok
{ 'r', {KEY_R}}, 						// 114 r OK
{ 's', {KEY_S}}, 						// 115 s OK
{ 't', {KEY_T}}, 						// 116 t OK
{ 'u', {KEY_U}}, 						// 117 u OK
{ 'v', {KEY_V}}, 						// 118 v OK
{ 'w', {KEY_W}}, 						// 119 w OK
{ 'x', {KEY_X}}, 						// 120 x OK
{ 'y', {KEY_Y}}, 						// 121 y OK
{ 'z', {KEY_Z}}, 						// 122 z OK
{ '{', {HID_KEY_ALT_RIGHT, KEY_7}},            // 123 { OK
{ '|', {HID_KEY_ALT_RIGHT, 0x64}},             // 124 | OK
{ '}', {HID_KEY_ALT_RIGHT, KEY_0}},            // 125 } OK 
{ '~', {HID_KEY_ALT_RIGHT, KEY_RIGHT_BRACE}},  // 126 ~ OK
};

// SPANISH

#define SHIFT_MASK		0x0040
#define ALTGR_MASK		0x0080
#define DEADKEYS_MASK		0x0700
#define	CIRCUMFLEX_BITS		0x0100
#define ACUTE_ACCENT_BITS	0x0200
#define GRAVE_ACCENT_BITS	0x0300
#define TILDE_BITS		0x0400
#define DIAERESIS_BITS		0x0500
#define KEYCODE_TYPE		uint16_t
#define KEYCODE_MASK		0x07FF
#define DEADKEY_CIRCUMFLEX	KEY_LEFT_BRACE + SHIFT_MASK
#define DEADKEY_ACUTE_ACCENT	KEY_QUOTE
#define DEADKEY_GRAVE_ACCENT	KEY_LEFT_BRACE
#define DEADKEY_TILDE		KEY_4 + ALTGR_MASK
#define DEADKEY_DIAERESIS	KEY_QUOTE + SHIFT_MASK
#define KEY_NON_US_100		63

ALT_GR_CHARS es_asciimap[128] =
{
{ ' ', {KEY_SPACE}}, 	        				    // 32' 'OK   
{ '!', {HID_KEY_SHIFT_LEFT, KEY_1}}, 	    // 33 ! OK
{ '"', {HID_KEY_SHIFT_LEFT, KEY_2}}, 	    // 34 " OK
{ '#', {HID_KEY_ALT_RIGHT, KEY_3}}, 	    // 35 # OK
{ '$', {HID_KEY_SHIFT_LEFT, KEY_4}}, 	    // 36 $ OK
{ '%', {HID_KEY_SHIFT_LEFT, KEY_5}}, 	    // 37 % OK
{ '&', {HID_KEY_SHIFT_LEFT, KEY_6}},      // 38 & OK
{ '\'', {KEY_MINUS}}, 	                  // 39 ' OK
{ '(', {HID_KEY_SHIFT_LEFT, KEY_8}}, 	    // 40 ( OK
{ ')', {HID_KEY_SHIFT_LEFT, KEY_9}},			// 41 ) OK
{ '*', {HID_KEY_SHIFT_LEFT, KEY_RIGHT_BRACE}},  // 42 * OK
{ '+', {KEY_RIGHT_BRACE}}, 	              // 43 + OK
{ ',', {KEY_COMMA}}, 				              // 44 , OK
{ '-', {KEY_SLASH}}, 				              // 45 - OK
{ '.', {KEY_PERIOD}}, 			              // 46 . OK
{ '/', {HID_KEY_SHIFT_LEFT, KEY_7}},      // 47 / OK
{ '0', {KEY_0}}, 						              // 48 0 OK
{ '1', {KEY_1}}, 						              // 49 1 OK
{ '2', {KEY_2}}, 						              // 50 2 OK
{ '3', {KEY_3}}, 						              // 51 3 OK
{ '4', {KEY_4}}, 						              // 52 4 OK
{ '5', {KEY_5}}, 						              // 53 5 OK
{ '6', {KEY_6}}, 						              // 54 6 OK
{ '7', {KEY_7}}, 						              // 55 7 OK
{ '8', {KEY_8}}, 						              // 55 8 OK
{ '9', {KEY_9}}, 						              // 57 9 OK
{ ':', {HID_KEY_SHIFT_LEFT, KEY_PERIOD}}, // 58 : OK
{ ';', {HID_KEY_SHIFT_LEFT, KEY_COMMA}},  // 59 ; OK
{ '<', {0x64}}, 	                        // 60 < OK
{ '=', {HID_KEY_SHIFT_LEFT, KEY_0}}, 	    // 61 = OK 
{ '>', {HID_KEY_SHIFT_LEFT, 0x64}},       // 62 > OK
{ '?', {HID_KEY_SHIFT_LEFT, KEY_MINUS}},  // 63 ? OK
{ '@', {HID_KEY_ALT_RIGHT, KEY_2}},       // 64 @ OK
{ 'A', {HID_KEY_SHIFT_LEFT, KEY_A}},  		// 65 A OK
{ 'B', {HID_KEY_SHIFT_LEFT, KEY_B}}, 			// 66 B OK
{ 'C', {HID_KEY_SHIFT_LEFT, KEY_C}}, 			// 67 C OK
{ 'D', {HID_KEY_SHIFT_LEFT, KEY_D}}, 			// 68 D OK
{ 'E', {HID_KEY_SHIFT_LEFT, KEY_E}}, 			// 69 E OK
{ 'F', {HID_KEY_SHIFT_LEFT, KEY_F}}, 			// 70 F OK
{ 'G', {HID_KEY_SHIFT_LEFT, KEY_G}},  		// 71 G OK
{ 'H', {HID_KEY_SHIFT_LEFT, KEY_H}}, 			// 72 H OK
{ 'I', {HID_KEY_SHIFT_LEFT, KEY_I}}, 			// 73 I OK
{ 'J', {HID_KEY_SHIFT_LEFT, KEY_J}}, 			// 74 J OK
{ 'K', {HID_KEY_SHIFT_LEFT, KEY_K}}, 			// 75 K OK
{ 'L', {HID_KEY_SHIFT_LEFT, KEY_L}}, 			// 76 L OK
{ 'M', {HID_KEY_SHIFT_LEFT, KEY_M}}, 			// 77 M OK
{ 'N', {HID_KEY_SHIFT_LEFT, KEY_N}}, 			// 78 N OK
{ 'O', {HID_KEY_SHIFT_LEFT, KEY_O}}, 			// 79 O OK
{ 'P', {HID_KEY_SHIFT_LEFT, KEY_P}}, 			// 80 P OK
{ 'Q', {HID_KEY_SHIFT_LEFT, KEY_Q}}, 			// 81 Q OK
{ 'R', {HID_KEY_SHIFT_LEFT, KEY_R}}, 			// 82 R OK
{ 'S', {HID_KEY_SHIFT_LEFT, KEY_S}}, 			// 83 S OK
{ 'T', {HID_KEY_SHIFT_LEFT, KEY_T}}, 			// 84 T OK
{ 'U', {HID_KEY_SHIFT_LEFT, KEY_U}}, 			// 85 U OK
{ 'V', {HID_KEY_SHIFT_LEFT, KEY_V}}, 			// 86 V OK
{ 'W', {HID_KEY_SHIFT_LEFT, KEY_W}},  		// 87 W OK
{ 'X', {HID_KEY_SHIFT_LEFT, KEY_X}}, 			// 88 X OK
{ 'Y', {HID_KEY_SHIFT_LEFT, KEY_Y}}, 			// 89 Y OK
{ 'Z', {HID_KEY_SHIFT_LEFT, KEY_Z}},      // 90 Z OK
{ '[', {HID_KEY_ALT_RIGHT, KEY_LEFT_BRACE}},  // 91 [ OK
{ '\\', {HID_KEY_ALT_RIGHT, KEY_TILDE}}, 	// 92 \ OK
{ ']', {HID_KEY_ALT_RIGHT, KEY_RIGHT_BRACE}}, // 93 ] OK
{ '^', {0}},		                          // 94 ^ KO
{ '_', {HID_KEY_SHIFT_LEFT, KEY_SLASH}},  // 95 _ OK
{ '`', {0}},                              // 96 ` KO
{ 'a', {KEY_A}}, 						// 97 a  OK
{ 'b', {KEY_B}}, 						// 98 b  OK
{ 'c', {KEY_C}}, 						// 99 c  OK
{ 'd', {KEY_D}}, 						// 100 d OK
{ 'e', {KEY_E}}, 						// 101 e OK
{ 'f', {KEY_F}}, 						// 102 f OK
{ 'g', {KEY_G}}, 						// 103 g OK
{ 'h', {KEY_H}}, 						// 104 h OK
{ 'i', {KEY_I}}, 						// 105 i Ok
{ 'j', {KEY_J}}, 						// 106 j OK
{ 'k', {KEY_K}}, 						// 107 k OK
{ 'l', {KEY_L}}, 						// 108 l OK
{ 'm', {KEY_M}}, 						// 109 m OK
{ 'n', {KEY_N}}, 						// 110 n OK
{ 'o', {KEY_O}}, 						// 111 o OK
{ 'p', {KEY_P}}, 						// 112 p OK
{ 'q', {KEY_Q}}, 						// 113 q Ok
{ 'r', {KEY_R}}, 						// 114 r OK
{ 's', {KEY_S}}, 						// 115 s OK
{ 't', {KEY_T}}, 						// 116 t OK
{ 'u', {KEY_U}}, 						// 117 u OK
{ 'v', {KEY_V}}, 						// 118 v OK
{ 'w', {KEY_W}}, 						// 119 w OK
{ 'x', {KEY_X}}, 						// 120 x OK
{ 'y', {KEY_Y}}, 						// 121 y OK
{ 'z', {KEY_Z}}, 						// 122 z OK
{ '{', {HID_KEY_ALT_RIGHT, KEY_QUOTE}},    // 123 { OK
{ '|', {HID_KEY_ALT_RIGHT, KEY_1}},        // 124 | OK
{ '}', {HID_KEY_ALT_RIGHT, KEY_BACKSLASH}},// 125 } OK 
{ '~', {0}},                               // 126 ~ KO
};

// PORTUGUESE BRAZILIAN

#define SHIFT_MASK		0x0040
#define ALTGR_MASK		0x0080
#define DEADKEYS_MASK		0x0700
#define	CIRCUMFLEX_BITS		0x0100
#define ACUTE_ACCENT_BITS	0x0200
#define GRAVE_ACCENT_BITS	0x0300
#define TILDE_BITS		0x0400
#define DIAERESIS_BITS		0x0500
#define KEYCODE_TYPE		uint16_t
#define KEYCODE_MASK		0x07FF
#define DEADKEY_CIRCUMFLEX	KEY_QUOTE + SHIFT_MASK
#define DEADKEY_ACUTE_ACCENT	KEY_LEFT_BRACE
#define DEADKEY_GRAVE_ACCENT	KEY_LEFT_BRACE + SHIFT_MASK
#define DEADKEY_TILDE		KEY_QUOTE
#define DEADKEY_DIAERESIS	KEY_6 + SHIFT_MASK
#define KEY_NON_US_100		63

ALT_GR_CHARS pt_br_asciimap[128] =
{
{ ' ', {KEY_SPACE}}, 	        				    // 32' 'OK   
{ '!', {HID_KEY_SHIFT_LEFT, KEY_1}}, 	    // 33 ! OK
{ '"', {HID_KEY_SHIFT_LEFT, KEY_TILDE}}, 	// 34 " OK
{ '#', {HID_KEY_SHIFT_LEFT, KEY_3}}, 	    // 35 # OK
{ '$', {HID_KEY_SHIFT_LEFT, KEY_4}}, 	    // 36 $ OK
{ '%', {HID_KEY_SHIFT_LEFT, KEY_5}}, 	    // 37 % OK
{ '&', {HID_KEY_SHIFT_LEFT, KEY_7}},      // 38 & OK
{ '\'', {KEY_TILDE}}, 	                  // 39 ' OK
{ '(', {HID_KEY_SHIFT_LEFT, KEY_9}}, 	    // 40 ( OK
{ ')', {HID_KEY_SHIFT_LEFT, KEY_0}},			// 41 ) OK
{ '*', {HID_KEY_SHIFT_LEFT, KEY_8}},      // 42 * OK
{ '+', {HID_KEY_SHIFT_LEFT, KEY_EQUAL}}, 	// 43 + OK
{ ',', {KEY_COMMA}}, 				              // 44 , OK
{ '-', {KEY_MINUS}}, 				              // 45 - OK
{ '.', {KEY_PERIOD}}, 			              // 46 . OK
{ '/', {HID_KEY_ALT_RIGHT, KEY_Q}},       // 47 / OK
{ '0', {KEY_0}}, 						              // 48 0 OK
{ '1', {KEY_1}}, 						              // 49 1 OK
{ '2', {KEY_2}}, 						              // 50 2 OK
{ '3', {KEY_3}}, 						              // 51 3 OK
{ '4', {KEY_4}}, 						              // 52 4 OK
{ '5', {KEY_5}}, 						              // 53 5 OK
{ '6', {KEY_6}}, 						              // 54 6 OK
{ '7', {KEY_7}}, 						              // 55 7 OK
{ '8', {KEY_8}}, 						              // 55 8 OK
{ '9', {KEY_9}}, 						              // 57 9 OK
{ ':', {HID_KEY_SHIFT_LEFT, KEY_SLASH}}, 	// 58 : OK
{ ';', {KEY_SLASH}}, 		                  // 59 ; OK
{ '<', {HID_KEY_SHIFT_LEFT, KEY_COMMA}}, 	// 60 < OK
{ '=', {KEY_EQUAL}}, 	  		              // 61 = OK 
{ '>', {HID_KEY_SHIFT_LEFT, KEY_PERIOD}}, // 62 > OK
{ '?', {HID_KEY_ALT_RIGHT, KEY_W}}, 		  // 63 ? OK
{ '@', {HID_KEY_SHIFT_LEFT, KEY_2}},      // 64 @ OK
{ 'A', {HID_KEY_SHIFT_LEFT, KEY_A}},  		// 65 A OK
{ 'B', {HID_KEY_SHIFT_LEFT, KEY_B}}, 			// 66 B OK
{ 'C', {HID_KEY_SHIFT_LEFT, KEY_C}}, 			// 67 C OK
{ 'D', {HID_KEY_SHIFT_LEFT, KEY_D}}, 			// 68 D OK
{ 'E', {HID_KEY_SHIFT_LEFT, KEY_E}}, 			// 69 E OK
{ 'F', {HID_KEY_SHIFT_LEFT, KEY_F}}, 			// 70 F OK
{ 'G', {HID_KEY_SHIFT_LEFT, KEY_G}},  		// 71 G OK
{ 'H', {HID_KEY_SHIFT_LEFT, KEY_H}}, 			// 72 H OK
{ 'I', {HID_KEY_SHIFT_LEFT, KEY_I}}, 			// 73 I OK
{ 'J', {HID_KEY_SHIFT_LEFT, KEY_J}}, 			// 74 J OK
{ 'K', {HID_KEY_SHIFT_LEFT, KEY_K}}, 			// 75 K OK
{ 'L', {HID_KEY_SHIFT_LEFT, KEY_L}}, 			// 76 L OK
{ 'M', {HID_KEY_SHIFT_LEFT, KEY_M}}, 			// 77 M OK
{ 'N', {HID_KEY_SHIFT_LEFT, KEY_N}}, 			// 78 N OK
{ 'O', {HID_KEY_SHIFT_LEFT, KEY_O}}, 			// 79 O OK
{ 'P', {HID_KEY_SHIFT_LEFT, KEY_P}}, 			// 80 P OK
{ 'Q', {HID_KEY_SHIFT_LEFT, KEY_Q}}, 			// 81 Q OK
{ 'R', {HID_KEY_SHIFT_LEFT, KEY_R}}, 			// 82 R OK
{ 'S', {HID_KEY_SHIFT_LEFT, KEY_S}}, 			// 83 S OK
{ 'T', {HID_KEY_SHIFT_LEFT, KEY_T}}, 			// 84 T OK
{ 'U', {HID_KEY_SHIFT_LEFT, KEY_U}}, 			// 85 U OK
{ 'V', {HID_KEY_SHIFT_LEFT, KEY_V}}, 			// 86 V OK
{ 'W', {HID_KEY_SHIFT_LEFT, KEY_W}},  		// 87 W OK
{ 'X', {HID_KEY_SHIFT_LEFT, KEY_X}}, 			// 88 X OK
{ 'Y', {HID_KEY_SHIFT_LEFT, KEY_Y}}, 			// 89 Y OK
{ 'Z', {HID_KEY_SHIFT_LEFT, KEY_Z}},      // 90 Z OK
{ '[', {KEY_RIGHT_BRACE}},                // 91 [ OK
{ '\\', {0x64}}, 	                        // 92 \ OK
{ ']', {KEY_BACKSLASH}},                  // 93 ] OK
{ '^', {0}},		                          // 94 ^ KO
{ '_', {HID_KEY_SHIFT_LEFT, KEY_MINUS}},  // 95 _ OK
{ '`', {0}},                              // 96 ` KO
{ 'a', {KEY_A}}, 						// 97 a  OK
{ 'b', {KEY_B}}, 						// 98 b  OK
{ 'c', {KEY_C}}, 						// 99 c  OK
{ 'd', {KEY_D}}, 						// 100 d OK
{ 'e', {KEY_E}}, 						// 101 e OK
{ 'f', {KEY_F}}, 						// 102 f OK
{ 'g', {KEY_G}}, 						// 103 g OK
{ 'h', {KEY_H}}, 						// 104 h OK
{ 'i', {KEY_I}}, 						// 105 i Ok
{ 'j', {KEY_J}}, 						// 106 j OK
{ 'k', {KEY_K}}, 						// 107 k OK
{ 'l', {KEY_L}}, 						// 108 l OK
{ 'm', {KEY_M}}, 						// 109 m OK
{ 'n', {KEY_N}}, 						// 110 n OK
{ 'o', {KEY_O}}, 						// 111 o OK
{ 'p', {KEY_P}}, 						// 112 p OK
{ 'q', {KEY_Q}}, 						// 113 q Ok
{ 'r', {KEY_R}}, 						// 114 r OK
{ 's', {KEY_S}}, 						// 115 s OK
{ 't', {KEY_T}}, 						// 116 t OK
{ 'u', {KEY_U}}, 						// 117 u OK
{ 'v', {KEY_V}}, 						// 118 v OK
{ 'w', {KEY_W}}, 						// 119 w OK
{ 'x', {KEY_X}}, 						// 120 x OK
{ 'y', {KEY_Y}}, 						// 121 y OK
{ 'z', {KEY_Z}}, 						// 122 z OK
{ '{', {HID_KEY_SHIFT_LEFT, KEY_RIGHT_BRACE}},    // 123 { OK
{ '|', {HID_KEY_SHIFT_LEFT, 0x64}},               // 124 | OK
{ '}', {HID_KEY_SHIFT_LEFT, KEY_BACKSLASH}},      // 125 } OK 
{ '~', {0}},                                      // 126 ~ KO
};

// current layout variables

#define SHIFT 0x80

uint8_t _asciimap[128] =
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

ALT_GR_CHARS asciimap[128] =
{
{ ' ', {0x2c}}, 	        	              // 32' 'OK   
{ '!', {HID_KEY_SHIFT_LEFT, 0x1e}}, 	    // 33 ! OK
{ '"', {HID_KEY_SHIFT_LEFT, 0x34}}, 	    // 34 " OK
{ '#', {HID_KEY_SHIFT_LEFT, 0x20}}, 	    // 35 # OK
{ '$', {HID_KEY_SHIFT_LEFT, 0x21}}, 	    // 36 $ OK
{ '%', {HID_KEY_SHIFT_LEFT, 0x22}}, 	    // 37 % OK
{ '&', {HID_KEY_SHIFT_LEFT, 0x24}},       // 38 & OK
{ '\'', {0x34}}, 	                        // 39 ' OK
{ '(', {HID_KEY_SHIFT_LEFT, 0x26}}, 	    // 40 ( OK
{ ')', {HID_KEY_SHIFT_LEFT, 0x27}},			  // 41 ) OK
{ '*', {HID_KEY_SHIFT_LEFT, 0x25}},       // 42 * OK
{ '+', {HID_KEY_SHIFT_LEFT, 0x2e}}, 	    // 43 + OK
{ ',', {0x36}}, 				    // 44 , OK
{ '-', {0x2d}}, 				    // 45 - OK
{ '.', {0x37}}, 			      // 46 . OK
{ '/', {0x38}},             // 47 / OK
{ '0', {0x27}}, 						// 48 0 OK
{ '1', {0x1e}}, 						// 49 1 OK
{ '2', {0x1f}}, 						// 50 2 OK
{ '3', {0x20}}, 						// 51 3 OK
{ '4', {0x21}}, 						// 52 4 OK
{ '5', {0x22}}, 						// 53 5 OK
{ '6', {0x23}}, 						// 54 6 OK
{ '7', {0x24}}, 						// 55 7 OK
{ '8', {0x25}}, 						// 55 8 OK
{ '9', {0x26}}, 						// 57 9 OK
{ ':', {HID_KEY_SHIFT_LEFT, 0x33}}, 	    // 58 : OK
{ ';', {0x33}}, 		        // 59 ; OK
{ '<', {HID_KEY_SHIFT_LEFT, 0x36}}, 			// 60 < OK
{ '=', {0x2e}}, 	  		    // 61 = OK 
{ '>', {HID_KEY_SHIFT_LEFT, 0x37}},       // 62 > OK 
{ '?', {HID_KEY_SHIFT_LEFT, 0x38}}, 		  // 63 ? OK
{ '@', {HID_KEY_SHIFT_LEFT, 0x1f}},       // 64 @ OK
{ 'A', {HID_KEY_SHIFT_LEFT, 0x04}},   		// 65 A OK
{ 'B', {HID_KEY_SHIFT_LEFT, 0x05}}, 			// 66 B OK
{ 'C', {HID_KEY_SHIFT_LEFT, 0x06}}, 			// 67 C OK
{ 'D', {HID_KEY_SHIFT_LEFT, 0x07}}, 			// 68 D OK
{ 'E', {HID_KEY_SHIFT_LEFT, 0x08}}, 			// 69 E OK
{ 'F', {HID_KEY_SHIFT_LEFT, 0x09}}, 			// 70 F OK
{ 'G', {HID_KEY_SHIFT_LEFT, 0x0a}},  		  // 71 G OK
{ 'H', {HID_KEY_SHIFT_LEFT, 0x0b}}, 			// 72 H OK
{ 'I', {HID_KEY_SHIFT_LEFT, 0x0c}}, 			// 73 I OK
{ 'J', {HID_KEY_SHIFT_LEFT, 0x0d}}, 			// 74 J OK
{ 'K', {HID_KEY_SHIFT_LEFT, 0x0e}}, 			// 75 K OK
{ 'L', {HID_KEY_SHIFT_LEFT, 0x0f}}, 			// 76 L OK
{ 'M', {HID_KEY_SHIFT_LEFT, 0x10}}, 			// 77 M OK
{ 'N', {HID_KEY_SHIFT_LEFT, 0x11}}, 			// 78 N OK
{ 'O', {HID_KEY_SHIFT_LEFT, 0x12}}, 			// 79 O OK
{ 'P', {HID_KEY_SHIFT_LEFT, 0x13}}, 			// 80 P OK
{ 'Q', {HID_KEY_SHIFT_LEFT, 0x14}}, 			// 81 Q OK
{ 'R', {HID_KEY_SHIFT_LEFT, 0x15}}, 			// 82 R OK
{ 'S', {HID_KEY_SHIFT_LEFT, 0x16}}, 			// 83 S OK
{ 'T', {HID_KEY_SHIFT_LEFT, 0x17}}, 			// 84 T OK
{ 'U', {HID_KEY_SHIFT_LEFT, 0x18}}, 			// 85 U OK
{ 'V', {HID_KEY_SHIFT_LEFT, 0x19}}, 			// 86 V OK
{ 'W', {HID_KEY_SHIFT_LEFT, 0x1a}},  		  // 87 W OK
{ 'X', {HID_KEY_SHIFT_LEFT, 0x1b}}, 			// 88 X OK
{ 'Y', {HID_KEY_SHIFT_LEFT, 0x1c}}, 			// 89 Y OK
{ 'Z', {HID_KEY_SHIFT_LEFT, 0x1d}},       // 90 Z OK
{ '[', {0x2f}},             // 91 [ OK
{ '\\', {0x31}}, 	          // 92 \ OK
{ ']', {0x30}},             // 93 ] OK
{ '^', {HID_KEY_SHIFT_LEFT, 0x23}},		    // 94 ^ OK
{ '_', {HID_KEY_SHIFT_LEFT, 0x2d}},       // 95 _ OK
{ '`', {0x35}},             // 96 ` OK
{ 'a', {0x04}}, 						// 97 a OK
{ 'b', {0x05}}, 						// 98 b OK
{ 'c', {0x06}}, 						// 99 c OK
{ 'd', {0x07}}, 						// 100 d OK
{ 'e', {0x08}}, 						// 101 e OK
{ 'f', {0x09}}, 						// 102 f OK
{ 'g', {0x0a}}, 						// 103 g OK
{ 'h', {0x0b}}, 						// 104 h OK
{ 'i', {0x0c}}, 						// 105 i Ok
{ 'j', {0x0d}}, 						// 106 j OK
{ 'k', {0x0e}}, 						// 107 k OK
{ 'l', {0x0f}}, 						// 108 l OK
{ 'm', {0x10}}, 						// 109 m OK
{ 'n', {0x11}}, 						// 110 n OK
{ 'o', {0x12}}, 						// 111 o OK
{ 'p', {0x13}}, 						// 112 p OK
{ 'q', {0x14}}, 						// 113 q OK
{ 'r', {0x15}}, 						// 114 r OK
{ 's', {0x16}}, 						// 115 s OK
{ 't', {0x17}}, 						// 116 t OK
{ 'u', {0x18}}, 						// 117 u OK
{ 'v', {0x19}}, 						// 118 v OK
{ 'w', {0x1a}}, 						// 119 w OK
{ 'x', {0x1b}}, 						// 120 x OK
{ 'y', {0x1c}}, 						// 121 y OK
{ 'z', {0x1d}}, 						// 122 z OK
{ '{', {HID_KEY_SHIFT_LEFT, 0x2f}},       // 123 { OK
{ '|', {HID_KEY_SHIFT_LEFT, 0x31}},       // 124 | OK
{ '}', {HID_KEY_SHIFT_LEFT, 0x30}},       // 125 } OK 
{ '~', {HID_KEY_SHIFT_LEFT, 0x35}},       // 126 ~ OK
};