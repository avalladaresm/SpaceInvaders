#include <screen.h>
#include <keypad.h>

#define TO_STR(ch) ( ( ((ch) >= 0 ) && ((ch) <= 9) )? (48 + (ch)) : ('a' + ((ch) - 10)) )

int main() {
    clear_screen();    
    uint8_t r = 28;
    uint8_t c = 40;
    uint8_t enemyR = 3;
    uint8_t enemyC = 5;
    uint8_t bulletR = 0;
    uint8_t bulletC = 0;
    uint8_t bulletCBeforeMoving = 0;
    uint8_t points = 0;
    uint8_t lives = 2;
    uint8_t score = 0;
    bool goingRight = true;
    bool isShooting = false;
    bool isPlayerMoving = false;
    bool isBulletGone = true;

    keypad_init();
    menu();
    while (1) {
        uint8_t k = keypad_getkey();
        if(k==7){
            break;
        }
        else if (k == 6){
            clear_screen();
            while (1){
                uint8_t key = keypad_getkey();
                displayScore(score);
                displayLives(lives);

                if (enemyC == 12){
                    goingRight = false;
                    enemyR++;
                }else if(enemyC == 5){
                    goingRight = true;
                    enemyR++;
                    if (enemyR == 24){
                        lives--;
                        if (lives == 0){
                            delay_ms(500);
                            clear_screen();
                            set_cursor(13, 35);
                            set_color(RED, BLACK);
                            puts("Game over"); 
                            set_cursor(14, 36);
                            set_color(WHITE, BLACK);
                            puts("Score"); 
                            set_cursor(14, 42);
                            put_char(TO_STR(score & 0xf));
                            break;
                        }
                        delay_ms(1500);
                        enemyR = 10;
                    }
                            set_cursor(16, 77);
                            put_char(TO_STR(lives & 0xf));
                }

                if (goingRight){
                    initSprites(enemyR, enemyC++, goingRight);
                }else{
                    initSprites(enemyR, enemyC--, goingRight);
                }

                if (isShooting){
                    if (isPlayerMoving){
                        shootBullet(bulletR--, bulletCBeforeMoving);
                        set_cursor(16, 70);
                        put_char(178);
                        if (bulletR == 0){
                            isShooting = false;
                            isBulletGone = true;
                        }
                        if (isBulletGone == true){
                            set_cursor(1, bulletCBeforeMoving);
                            put_char(255);
                            set_cursor(17, 70);
                            put_char(179);
                        }
                    }
                }

                if (key == 1){
                    isPlayerMoving = true;
                    c-=2;
                    if (c == 2){
                        c+=2;
                    }
                    moveShipLeft(r,c);
                }
                if (key == 2){
                    isPlayerMoving = true;
                    c+=2;
                    if (c == 74){
                        c-=2;
                    }
                    moveShipRight(r,c);
                }
                if (key == 7){
                    points++;
                }
                if (key == 8 && !isShooting){
                    isShooting = true;
                    bulletR = getShipRow()-2;                    
                    bulletCBeforeMoving = getShipCol()+1;
                    if (isBulletGone){
                        isBulletGone = false;
                    }
                }
                delay_ms(50);
            }
        }
    }
    
    return 0;
}
