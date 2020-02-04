#include <screen.h>
#include <keypad.h>

#define TO_STR(ch) ( ( ((ch) >= 0 ) && ((ch) <= 9) )? (48 + (ch)) : ('a' + ((ch) - 10)) )

int main() {
    clear_screen();    
    uint8_t r = 28;
    uint8_t c = 40;
    uint8_t enemyR = 3;
    uint8_t enemyC = 10;
    uint8_t bulletR = getShipRow();
    uint8_t bulletC = getShipCol();
    uint8_t points = 0;

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
                set_cursor(1, 1);
                puts("Points: ");
                
                if (enemyC == 20){
                    goingRight = false;
                    enemyR++;
                }else if(enemyC == 10){
                    goingRight = true;
                    enemyR++;
                    if (enemyR == 28){
                        set_cursor(15, 40);
                        puts("Game over1"); //hacer funcion
                    }
                }

                if (goingRight){
                    initSprites(enemyR, enemyC++, goingRight);
                }else{
                    initSprites(enemyR, enemyC--, goingRight);
                }

                // set_cursor(2, 1);
                // put_char(TO_STR(key & 0xf));
                // set_cursor(3, 1);
                // put_char(TO_STR((key & 0xf0) >> 4));

                if (key == 1){
                    c--;
                    if (c == 1){
                        c++;
                    }
                    moveShipLeft(r,c);
                }
                if (key == 2){
                    c++;
                    if (c == 76){
                        c--;
                    }
                    moveShipRight(r,c);
                }
                if (key == 7){
                    points++;
                    set_cursor(4, 9);
                    put_char(TO_STR(points & 0xf));
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

                delay_ms(50);
            }
        }
        
    }
    
    return 0;
}
