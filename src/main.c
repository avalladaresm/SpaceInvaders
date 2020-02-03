#include <screen.h>
#include <keypad.h>

#define TO_STR(ch) ( ( ((ch) >= 0 ) && ((ch) <= 9) )? (48 + (ch)) : ('a' + ((ch) - 10)) )

int main() {
    clear_screen();    
    uint8_t r = 28;
    uint8_t c = 40;
    uint8_t enemyR = 2;
    uint8_t enemyC = 15;
    uint8_t bulletR = getShipRow();
    uint8_t bulletC = getShipCol();
    bool goingRight = true;
    keypad_init();
    menu();
    while (1) {
        uint8_t k = keypad_getkey();
        if (k == 6){
            clear_screen();
            while (1){
                uint8_t key = keypad_getkey();
                //displayTest();
                
                /*if (enemyC == 20){
                    goingRight = false;
                }else if(enemyC == 10){
                    goingRight = true;
                }

                if (goingRight){
                    initSprites(enemyR, enemyC++, goingRight);
                }else{
                    initSprites(enemyR, enemyC--, goingRight);
                }*/
                
                
                
                set_cursor(2, 1);
                put_char(TO_STR(key & 0xf));
                set_cursor(3, 1);
                put_char(TO_STR((key & 0xf0) >> 4));
                    // set_cursor(17, 60);
                    // puts("HELLO");
                if (key == 2){
                    c++;
                    if (c == 76){
                        c--;
                    }
                    moveShipRight(r,c);
                }
                if (key == 1){
                    c--;
                    if (c == 1){
                        c++;
                    }
                    moveShipLeft(r,c);
                }
                if (key == 8){
                    bulletR--;
                    if (bulletR == 1){
                        bulletR++;
                    }
                    set_cursor(12, 60);
                    put_char(TO_STR((bulletR & 0xf0) >> 4));
                    shootBullet(bulletR,bulletC);
                }
                // if (k != 0) {
                //     set_cursor(10, 15);
                //     puts("Key press");
                // }
            }
        }
        
    }
    
    return 0;
}
