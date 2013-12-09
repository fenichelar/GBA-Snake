// Alec Fenichel

//
// Types
//

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;

typedef volatile unsigned char vu8;
typedef volatile unsigned short vu16;
typedef volatile unsigned long vu32;

typedef signed char s8;
typedef signed short s16;
typedef signed long s32;

typedef volatile signed char vs8;
typedef volatile signed short vs16;
typedef volatile signed long vs32;


//
// Colors
//

#define RED RGB(31,0,0)
#define GREEN RGB(0,31,0)
#define BLUE RGB(0,0,31)
#define MAGENTA RGB(31, 0, 31)
#define YELLOW RGB(31, 31, 0)
#define CYAN RGB(0,31,31)
#define WHITE RGB(31,31,31)
#define BLACK 0

#define OFFSET(x,y) ((y)*SCREEN_WIDTH+(x))
#define OFFSETS(x,y,z) ((y)*(z)+(x))

#define RGB(r,g,b) ((u16)(r | (g<<5) | (b<<10)))


//
// Keys
//

#define KEY_A 0x001
#define KEY_B 0x002
#define KEY_SELECT 0x004
#define KEY_START 0x008
#define KEY_RIGHT 0x010
#define KEY_LEFT 0x020
#define KEY_UP 0x040
#define KEY_DOWN 0x080
#define KEY_R 0x100
#define KEY_L 0x200

#define KEYS *(vu16*)0x04000130

#define keyDown(k) (~KEYS & (k))


//
// Video
//

#define SCREEN_WIDTH 240
#define SCREEN_HEIGHT 160
#define SCREEN_TOTAL 38400

#define MODE_0 0x0
#define MODE_1 0x1
#define MODE_2 0x2
#define MODE_3 0x3
#define MODE_4 0x4
#define MODE_5 0x5

#define BG0_ENABLE 0x100
#define BG1_ENABLE 0x200
#define BG2_ENABLE 0x400
#define BG3_ENABLE 0x800
#define OBJ_ENABLE 0x1000 

#define videoBuffer ((u16*)0x6000000)
#define REG_DISPCNT *(u16*)0x4000000

#define SetMode(mode) REG_DISPCNT = (mode)

#define SCANLINECOUNTER *(vu16 *)0x4000006


//
// DMA
//

typedef struct
{
    const volatile void *src;
    const volatile void *dst;
    u32                  cnt;
} DMA_CONTROLLER;

#define DMA ((volatile DMA_CONTROLLER *) 0x040000B0)

#define REG_DMA0SAD         *(const vu32*)0x40000B0
#define REG_DMA0DAD         *(vu32*)0x40000B4
#define REG_DMA0CNT         *(vu32*)0x40000B8

#define REG_DMA1SAD         *(const vu32*)0x40000BC
#define REG_DMA1DAD         *(vu32*)0x40000C0
#define REG_DMA1CNT         *(vu32*)0x40000C4

#define REG_DMA2SAD         *(const vu32*)0x40000C8
#define REG_DMA2DAD         *(vu32*)0x40000CC
#define REG_DMA2CNT         *(vu32*)0x40000D0

#define REG_DMA3SAD         *(vu32*)0x40000D4
#define REG_DMA3DAD         *(vu32*)0x40000D8
#define REG_DMA3CNT         *(vu32*)0x40000DC

#define DMA_CHANNEL_0 0
#define DMA_CHANNEL_1 1
#define DMA_CHANNEL_2 2
#define DMA_CHANNEL_3 3

#define DMA_DESTINATION_INCREMENT (0 << 21)
#define DMA_DESTINATION_DECREMENT (1 << 21)
#define DMA_DESTINATION_FIXED (2 << 21)
#define DMA_DESTINATION_RESET (3 << 21)

#define DMA_SOURCE_INCREMENT (0 << 23)
#define DMA_SOURCE_DECREMENT (1 << 23)
#define DMA_SOURCE_FIXED (2 << 23)

#define DMA_REPEAT (1 << 25)

#define DMA_16 (0 << 26)
#define DMA_32 (1 << 26)

#define DMA_NOW (0 << 28)
#define DMA_AT_VBLANK (1 << 28)
#define DMA_AT_HBLANK (2 << 28)
#define DMA_AT_REFRESH (3 << 28)

#define DMA_IRQ (1 << 30)
#define DMA_ON (1 << 31)


//
// Prototypes
//

void setPixel(int x, int y, u16 color);
void drawRect(int x, int y, int width, int height, u16 color);
void drawHollowRect(int x, int y, int width, int height, u16 color);
void fillScreen(vu16 color);
void drawImage3(int x, int y, int width, int height, const u16* image);
void waitForVblank();
void delay(int n);

//
// Includes
//

#include <stdio.h>
#include <stdlib.h>