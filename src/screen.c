#include "../include/screen.h"
#include "../include/keypad.h"

#define TO_STR(ch) ( ( ((ch) >= 0 ) && ((ch) <= 9) )? (48 + (ch)) : ('a' + ((ch) - 10)) )

struct Player{
    uint8_t row;
    uint8_t col;
    char *sprites;
} player;

struct Enemy1{
    uint8_t row;
    uint8_t col;
    bool isDestroyed;
    char *sprites;
};

struct Bullet{
    uint8_t row;
    uint8_t col;
    char *sprite;
} bullet;

struct shipPosition{
    uint8_t row;
    uint8_t col;
};

struct bulletPosition{
    uint8_t row;
    uint8_t col;
    bool ifImpact;
};

void menu(){
    uint8_t f, b;
    get_color(&f, &b);
    set_color(WHITE, BLACK);
    set_cursor(10, 32);
    puts("SPACE INVADERS");
    set_cursor(13, 31);
    puts("Press p to play");
    set_cursor(14, 31);
    puts("Press q to quit");
    set_cursor(29, 55);
    puts("By: Alejandro Valladares");
}

void displayTest(){    
    set_cursor(5, 10);
    uint8_t f, b;
    get_color(&f, &b);

    set_color(GREEN, BLACK);
    puts("\x2\x3\x4");
    set_color(f, b);
    
    set_color(WHITE, BLACK);
    set_cursor(10, 10);
    puts("\x5\x6\x7");
    set_color(f, b);

    set_color(WHITE, BLACK);
    set_cursor(10, 18);
    puts("\x8\x6\x9");
    set_color(f, b);

    set_color(WHITE, BLACK);
    set_cursor(15, 10);
    puts("\x19\xb\xc");
    set_color(f, b);

    set_color(WHITE, BLACK);
    set_cursor(15, 18);
    puts("\xd\xe\xf");
    set_color(f, b);

    set_color(WHITE, BLACK);
    set_cursor(20, 10);
    puts("\x10\x11\x12");
    set_color(f, b);

    set_color(WHITE, BLACK);
    set_cursor(20, 18);
    puts("\x13\x14\x15");
    set_color(f, b);

    set_color(RED, BLACK);
    set_cursor(25, 10);
    puts("\x16\x17\x18");
    set_color(f, b);
}

void moveShipRight(uint8_t row, uint8_t col){
    player.row = row;
    player.col = col;
    player.sprites = "\x2\x3\x4";
    uint8_t f, b;
    get_color(&f, &b);

    set_color(GREEN, BLACK);
    set_cursor(player.row, player.col);
    puts(player.sprites);
    set_cursor(player.row, player.col-1);
    put_char(255);
    set_cursor(player.row, player.col-2);
    put_char(255);
    set_color(f, b);
    setShipPosition(player.row, player.col);
}

void moveShipLeft(uint8_t row, uint8_t col){
    player.row = row;
    player.col = col;
    player.sprites = "\x2\x3\x4";
    uint8_t f, b;
    get_color(&f, &b);

    set_color(GREEN, BLACK);
    set_cursor(player.row, player.col);
    puts(player.sprites);
    set_cursor(player.row, player.col+3);
    put_char(255);
    set_cursor(player.row, player.col+4);
    put_char(255);
    set_color(f, b);
    setShipPosition(player.row, player.col);
}

void initSprites(uint8_t row, uint8_t col, bool goingRight){
    struct Enemy1 enemy1[5];
    struct Enemy1 enemy2[5];
    struct Enemy1 enemy3[5];

    uint8_t basePositions1[] = {col, col+12, col+24, col+36, col+48};
    uint8_t basePositions2[] = {col+4, col+16, col+28, col+40, col+52};
    uint8_t basePositions3[] = {col+8, col+20, col+32, col+44, col+56};

    for (uint8_t i = 0; i < 5; i++){
        enemy1[i].row = row;
        enemy1[i].col = basePositions1[i];
        enemy1[i].isDestroyed = false;
        enemy1[i].sprites = "\x5\x6\x7";

        enemy2[i].row = row+2;
        enemy2[i].col = basePositions2[i];
        enemy2[i].isDestroyed = false;
        enemy2[i].sprites = "\x19\xb\xc";

        enemy3[i].row = row+4;
        enemy3[i].col = basePositions3[i];
        enemy3[i].isDestroyed = false;
        enemy3[i].sprites = "\x10\x11\x12";
    }
    uint8_t f, b;
    get_color(&f, &b);

    for (uint8_t i = 0; i < 5; i++){
        if (enemy1[i].isDestroyed){
            set_cursor(4, 40);
            puts("asdasd"); //hacer funcion
            continue;
        }else{
            if (goingRight){
                set_color(WHITE, BLACK);
                set_cursor(enemy1[i].row, enemy1[i].col-1);
                put_char(255);
                set_cursor(enemy1[i].row, enemy1[i].col);
                puts(enemy1[i].sprites);

                set_cursor(enemy2[i].row, enemy2[i].col-1);
                put_char(255);
                set_cursor(enemy2[i].row, enemy2[i].col);
                puts(enemy2[i].sprites);

                set_cursor(enemy3[i].row, enemy3[i].col-1);
                put_char(255);
                set_cursor(enemy3[i].row, enemy3[i].col);
                puts(enemy3[i].sprites);
                set_color(f, b);
                for (uint8_t j = 0; j < 5; j++){
                    if (enemy1[j].col == 5 || enemy1[j].col == col + 5){
                        set_cursor(enemy1[i].row-1, enemy1[i].col+1);
                        puts("\xff\xff\xff");
                        set_cursor(enemy2[i].row-1, enemy2[i].col+1);
                        puts("\xff\xff\xff");
                        set_cursor(enemy3[i].row-1, enemy3[i].col+1);
                        puts("\xff\xff\xff");
                    }
                }
                if (enemy1[i].row == getBulletRow() && 
                    (enemy1[i].col == getBulletCol() || 
                    enemy1[i].col+1 == getBulletCol() ||
                    enemy1[i].col+2 == getBulletCol())){
                    enemy1[i].isDestroyed = true;
                    set_cursor(5, 40);
                    puts("HIT"); //hacer funcion
                }
            }
            else{
                set_color(WHITE, BLACK);
                set_cursor(enemy1[i].row, enemy1[i].col+3);
                put_char(255);
                set_cursor(enemy1[i].row, enemy1[i].col);
                puts(enemy1[i].sprites);

                set_cursor(enemy2[i].row, enemy2[i].col+3);
                put_char(255);
                set_cursor(enemy2[i].row, enemy2[i].col);
                puts(enemy2[i].sprites);

                set_cursor(enemy3[i].row, enemy3[i].col+3);
                put_char(255);
                set_cursor(enemy3[i].row, enemy3[i].col);
                puts(enemy3[i].sprites);

                for (uint8_t j = 0; j < 5; j++){
                    if (enemy1[j].col == 12 || enemy1[j].col == col + 5){
                        set_cursor(enemy1[i].row-1, enemy1[i].col-1);
                        puts("\xff\xff\xff");
                        set_cursor(enemy2[i].row-1, enemy2[i].col-1);
                        puts("\xff\xff\xff");
                        set_cursor(enemy3[i].row-1, enemy3[i].col-1);
                        puts("\xff\xff\xff");
                    }
                }
            }
        }
    }
    set_color(f, b);
}

void shootBullet(uint8_t row, uint8_t col){
    bullet.row = row;
    bullet.col = col;
    bullet.sprite = "\x1";
    uint8_t f, b;
    get_color(&f, &b);

    set_color(YELLOW, BLACK);
    set_cursor(bullet.row--, bullet.col);
    puts(bullet.sprite);
    set_cursor(bullet.row+2, bullet.col);
    put_char(255);
    set_color(f, b);
    setBulletPosition(bullet.row, bullet.col);
}

void setShipPosition(uint8_t row, uint8_t col){
    player.row = row;
    player.col = col;
}

uint8_t getShipRow(){
    return player.row;
}

uint8_t getShipCol(){
    return player.col;
}

void setBulletPosition(uint8_t row, uint8_t col){
    bullet.row = row;
    bullet.col = col;
}

uint8_t getBulletRow(){
    return bullet.row;
}

uint8_t getBulletCol(){
    return bullet.col;
}

void displayScore(uint8_t score){
    set_cursor(1, 1);
    set_color(WHITE, BLACK);
    puts("Score");
    uint8_t f, b;
    get_color(&f, &b);
    
    set_color(GREEN, BLACK);
    set_cursor(1, 7);
    put_char(TO_STR(score & 0xf));
}

void displayLives(uint8_t lives){
    set_cursor(1, 60);
    set_color(WHITE, BLACK);
    puts("Lives");
    uint8_t f, b;
    get_color(&f, &b);
    
    set_color(GREEN, BLACK);
    if (lives == 2) {
        set_cursor(1, 66);
        puts("\x2\x3\x4");
        set_cursor(1, 70);
        puts("\x2\x3\x4");
    } else if(lives == 1){
        set_cursor(1, 66);
        puts("\x2\x3\x4");
        set_cursor(1, 70);
        puts("\xff\xff\xff");
    } else if(lives == 0){
        set_cursor(1, 66);
        puts("\xff\xff\xff");
        set_cursor(1, 70);
        puts("\xff\xff\xff");
    }
}