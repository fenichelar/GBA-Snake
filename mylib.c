#include "mylib.h"

// Alec Fenichel

// A function to set pixel (x, y) to the color passed in. 
void setPixel(int x, int y, u16 color) {
	videoBuffer[OFFSET(x,y)] = color;
}

// A function to draw a FILLED rectangle starting at (x, y) 
void drawRect(int x, int y, int width, int height, u16 color) {
	for (int i = y; i <= y + height; i ++) {
		for (int j = x; j <= x + width; j ++) {
			setPixel(j, i, color);
		}
	}
} 

// A function to draw a HOLLOW rectangle starting at (x, y) 
void drawHollowRect(int x, int y, int width, int height, u16 color) {
	for (int i = x; i <= x + width; i ++) {
		setPixel(i, y, color);
		setPixel(i, y + height, color);
	}
	for (int i = y; i <= y + height; i ++) {
		setPixel(x, i, color);
		setPixel(x + width, i, color);
	}
}

// Fill entire screen with a color
void fillScreen(vu16 color) {
    DMA[3].src = &color;
    DMA[3].dst = videoBuffer;
    DMA[3].cnt = (SCREEN_TOTAL) | DMA_SOURCE_FIXED | DMA_DESTINATION_INCREMENT | DMA_ON;
}

// A function that will draw an arbitrary sized image onto the screen (with DMA).
void drawImage3(int x, int y, int width, int height, const u16* image) { 
        for(int r=0; r<height; r++) {
            DMA[3].src = &image[OFFSETS(0, r, width)];
            DMA[3].dst = &videoBuffer[OFFSET(x, r+y)];
            DMA[3].cnt = width | DMA_SOURCE_INCREMENT | DMA_DESTINATION_INCREMENT | DMA_ON;
        }
}

// Wait for vertical blank
void waitForVblank() {
    while(SCANLINECOUNTER > 160);
    while(SCANLINECOUNTER < 160);
}

// Delay function
void delay(int n) {
    volatile int x = 0;
    for(int i = 0; i < n*1000; i++) {
        x++;
    }
}