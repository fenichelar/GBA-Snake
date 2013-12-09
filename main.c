#include "mylib.h"

#include "startScreen.h"
#include "gameOver.h"
#include "retry.h"

// Alec Fenichel

// This is a Snake game.

int main(void) {

    SetMode(MODE_3 | BG2_ENABLE);
    
    fillScreen(BLACK);
    
    drawImage3(0, 0, STARTSCREEN_WIDTH, STARTSCREEN_HEIGHT, &startScreen[0]);
    int i = 1;
    while(i) {
        if(keyDown(KEY_START)) {
            i = 0;
        }
    }
    
    fillScreen(BLACK);
    
    int x = 120;
    int y = 60;
    int d = 0;
    int t = 20;
    int m = 10;
    int s = 0;
    int p = 0;
    int c = 1;
    u16 color = WHITE;
    
    drawHollowRect(0,0,SCREEN_WIDTH-1, SCREEN_HEIGHT-10, color);
    setPixel(x,y,color);
    
    while(c) {
        
        // Reset
        if(keyDown(KEY_SELECT)) {
            c = 0;
            main();
        }
        
        // Set Direction
        if(keyDown(KEY_DOWN) && (d != 2)){
            d = 0;
        } else if(keyDown(KEY_RIGHT) && (d != 3)) {
            d = 1;
        } else if(keyDown(KEY_UP) && (d != 0)) {
            d = 2;
        } else if(keyDown(KEY_LEFT) && (d != 1)) {
            d = 3;
        }
        
        // Move snake
        if(d==0) {
            y++;
        } else if(d==1) {
            x++;
        } else if(d==2) {
            y--;
        } else if(d==3) {
            x--;
        }
        
        // Check for collisions
        if(videoBuffer[OFFSET(x,y)] != BLACK) {
            fillScreen(BLACK);
            drawImage3(0, 0, GAMEOVER_WIDTH, GAMEOVER_HEIGHT, &gameOver[0]);
            drawImage3(100, 70, RETRY_WIDTH, RETRY_HEIGHT, &retry[0]);
            int i = 1;
            while(i) {
                if(keyDown(KEY_START)) {
                    while(keyDown(KEY_START)) {
                        
                    }
                    i = 0;
                }
            }
            
            c = 0;
            main();
        }
        
        // Draw snake
        setPixel(x,y,color);
        delay(t);
        
        // Increase score
        s++;
        s = s%m;
        
        // Set Speed
        if(s == 0) {
            t--;
            m = m + m/3;
            drawRect(1 + p,152,2,6,WHITE);
            p = p + 4;
        }
        
        // Wait for V blank
        waitForVblank();
    }

    return 0;
}