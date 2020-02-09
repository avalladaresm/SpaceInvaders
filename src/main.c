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
    uint8_t bulletCBeforeMoving = 0;
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
                score = getDestroyedEnemies();
                displayScore(score);
                displayLives(lives);

                //If score = 15, game is won. It can be lowered to
                //score > 0 for testing purposes.
                if (score == 15){
                    delay_ms(500);
                    clear_screen();
                    set_cursor(13, 37);
                    set_color(GREEN, BLACK);
                    puts("YOU WON"); 
                    set_cursor(14, 37);
                    set_color(WHITE, BLACK);
                    puts("Score "); 
                    set_cursor(14, 42);
                    set_color(GREEN, BLACK);
                    put_char(TO_STR(getDestroyedEnemies() & 0xf));
                    break;
                }
                
                if (enemyC == 15){
                    goingRight = false;
                    //enemyR++;
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
                            put_char(TO_STR(getDestroyedEnemies() & 0xf));
                            break;
                        }
                        delay_ms(1500);
                        clear_screen();
                        enemyR = 10;
                    }
                }

                if (goingRight){
                    initSprites(enemyR, enemyC++, goingRight);
                }else{
                    initSprites(enemyR, enemyC--, goingRight);
                }

                if (isShooting){
                    if (isPlayerMoving){
                        shootBullet(bulletR--, bulletCBeforeMoving);
                        if (bulletR == 0){
                            isShooting = false;
                            isBulletGone = true;
                        }
                        if (isBulletGone == true){
                            set_cursor(1, bulletCBeforeMoving);
                            put_char(255);
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
                if (key == 8 && !isShooting){
                    isShooting = true;
                    bulletR = getShipRow()-2;                    
                    bulletCBeforeMoving = getShipCol()+1;
                    if (isBulletGone){
                        isBulletGone = false;
                    }
                }
                delay_ms(40);
            }
        }
    }
    
    return 0;
}
